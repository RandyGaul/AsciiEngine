////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file contains functions for various graphics related tasks
// Documentation: http://cecilsunkure.blogspot.com/2011/12/windows-console-game-painters-algorithm.html
//                http://cecilsunkure.blogspot.com/2012/02/windows-console-game-variable-sized.html

#include <stdlib.h>
#include <stdio.h>
#include "Graphics.h"
#include "ImageTable.h"
#include "Camera.h"

// Buffer for double buffering to the screen
// Perform all writing here during game logic. This way we can
// pass a single "finished" buffer to the WriteConsoleOutput
// function (since it's so darn slow)
CHAR_INFO *DOUBLE_BUFFER;

// Constants (after initialization from the InitGraphics function)
int BUFFERHEIGHT = 0;
int BUFFERWIDTH = 0;

void ClearBuffer( void )
{
  int x, y;

  for(y = 0; y < BUFFERHEIGHT; y++)
  {
    for(x = 0; x < BUFFERWIDTH; x++)
    {
      DOUBLE_BUFFER[(y * BUFFERWIDTH) + x].Char.AsciiChar = 0;
      DOUBLE_BUFFER[(y * BUFFERWIDTH) + x].Attributes = 0;
    }
  }
}

// Initializes the chars and colors arrays of an image to zero
void ZeroImage( IMAGE *image )
{
  int x, y;
  CHAR *thisChar;
  COL *thisColor;

  for(y = 0; y < image->height; ++y)
  {
    for(x = 0; x < image->width; ++x)
    {
      thisChar = CharAt( image, x, y );
      *thisChar = 0;
    }
  }

  for(y = 0; y < image->height; ++y)
  {
    for(x = 0; x < image->width; ++x)
    {
      thisColor = ColorAt( image, x, y );
      *thisColor = 0;
    }
  }
}

// Sets an IMAGE struct's chars and colors arrays to provided data
void ImageSet( IMAGE *image, CHAR *charData, COL *colorData )
{
  int x, y;
  CHAR *thisChar;
  COL *thisColor;

  for(y = 0; y < image->height; y++)
  {
    for(x = 0; x < image->width; x++)
    {
      thisChar = CharAt( image, x, y );
      *thisChar = charData[(y * image->width) + x];
    }
  }

  for(y = 0; y < image->height; y++)
  {
    for(x = 0; x < image->width; x++)
    {
      thisColor = ColorAt( image, x, y );
      *thisColor = colorData[(y * image->width) + x];
    }
  }
}

// Allocates and initializes a new IMAGE struct
// Width and height are the width and height of the image in character spaces
IMAGE *AllocateImage( const char *string, int width, int height )
{
  // Allocate space for the image struct + the size of the string + the width and height
  // of the image->chars array + the width and height of the image-> colors array
  int size = sizeof( IMAGE ) + strlen( string ) + 1
                             + width * height * sizeof( CHAR )
                             + width * height * sizeof( COL );
  IMAGE *image = (IMAGE *)malloc( size );

  image->width = width;
  image->height = height;

  // Initialize the ID pointer to directly after the IMAGE struct
  image->ID = PtrAdd( image, sizeof( IMAGE ) );
  strcpy_s( image->ID, strlen( string ) + 1, string );

  // Initialize chars pointer to directly after the ID string
  image->chars = (unsigned char *)PtrAdd( image->ID, strlen( image->ID ) + 1 );

  // Initialize colors pointer to directly after chars array
  image->colors = (unsigned char *)PtrAdd( image->chars, width * height * sizeof( CHAR ));

  // Initialize the chars and colors arrays to zero in the image
  ZeroImage( image );

  // Insert the image into the hash table of images  
  INSERT_DATA( P_IMAGE, IMAGE_TABLE, image, string );

  return image;
}

//
// AllocateAnimation
// Purpose: Allocates and initializes a new ANIMATION struct
// Notes  : The last parameter must be NULL. Example:
//                                           AllocateAnimation( frameDelay, "FirstFrame", "SecondFrame", NULL );
//          frameDelay is a float representing SECONDS
//
ANIMATION *AllocateAnimation( float frameDelay, const char *firstFrame, ... )
{
  va_list args;
  const char *next = firstFrame;
  ANIMATION *animation = NULL;
  int frameIterator = 0, numFrames = 0;
  //ANIMATION *animation = (ANIMATION *)malloc( sizeof( ANIMATION ) )

  // Count number of arguments
  va_start( args, firstFrame );
  while(next != 0)
  {
    ++numFrames;
    next = va_arg( args, const char * );
  }
  va_end( args );

  // Allocate image + size of animation frame array
  animation = (ANIMATION *)malloc( sizeof( ANIMATION ) + sizeof( IMAGE ) * numFrames );

  // Initialize frames pointer to directly after the ID string
  animation->frames = (IMAGE **)PtrAdd( animation, sizeof( ANIMATION ) );

  animation->isPaused = FALSE;
  animation->numFrames = numFrames;
  animation->playCount = 0;
  animation->frameDelay = frameDelay;
  animation->dt = 0.f;
  animation->currentFrame = 0;

  // Restart the argument loop
  next = firstFrame;
  va_start( args, firstFrame );

  // Loop through arguments and assign images to the frame array
  while(frameIterator < numFrames)
  {
    animation->frames[frameIterator] = FIND_DATA( P_IMAGE, IMAGE_TABLE, next );
    ++frameIterator;
    next = va_arg( args, const char * );
  }
  
  va_end( args );

  return animation;
}

// Deallocates an image. Be sure to check the return type to see
// if success or failure. Failure most likely means your imageID
// was not found.
RETURN_TYPE DeallocateImage( IMAGE *image )
{
  if(!image)
  {
    return RETURN_FAILURE;
  }

  free( image );
  return RETURN_SUCCESS;
}

// Deallocates an image. Be sure to check the return type to see
// if success or failure. Failure most likely means your imageID
// was not found.
RETURN_TYPE DeallocateAnimation( ANIMATION *animation )
{
  free( animation );
  return RETURN_SUCCESS;
}

// This is called once to initialize the graphics system.
void InitGraphics( int width, int height )
{
  BUFFERHEIGHT = height;
  BUFFERWIDTH = width;
  
  DOUBLE_BUFFER = (CHAR_INFO *)malloc( sizeof( CHAR_INFO ) * width * height );
  memset( DOUBLE_BUFFER, 0, sizeof( CHAR_INFO ) * width * height );
  
  IMAGE_TABLE = CREATE_TABLE( P_IMAGE, 311 );
}

// Checks to make sure a coordinate is within the boundaries of the screen or not
BOOL ScreenBoundCheck( int x, int y )
{
  return (x < BUFFERWIDTH && x > -1 && y < BUFFERHEIGHT && y > -1) ? TRUE : FALSE;
}

// Integer to string
void inttostr(int number, char string[])
{
  int i, j, dig;
  
  for (dig = 0, i = (number > 0) ? number : number * -1; i > 0; i /= 10, dig++)
  {
    ;
  }
    
  string[(number > 0) ? dig : dig + 1] = '\0';
  dig--;
  
  if (number > 0)
  {
    for (i = 0, j = dig; i <= j; i++, dig--, number /= 10)
    {
      string[dig] = (number % 10) + '0';
    }
  }
  else if (number < 0)
  {
    for (i = 0, j = dig; i <= j; i++, dig--, number /= 10)
    {
      string[dig + 1] = ((number % 10) * -1) + '0';
    }
    string[0] = '-';
  }
  else
  {
    string[0] = '0';
    string[1] = '\0';
  }
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
RETURN_TYPE RenderPImageToScreen( IMAGE *image, int xoffset, int yoffset )
{
  int x, y;
  int camX = (int)GLOBAL_CAM.center.x_;
  int camY = (int)GLOBAL_CAM.center.y_;

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  for(y = 0; y < image->height; ++y)
  {
    for(x = 0; x < image->width; ++x)
    {
      if(ScreenBoundCheck( x + xoffset + camX, y + yoffset + camY ) && image->chars[x + image->width * y] != TRANSPERANT)
      {
        DOUBLE_BUFFER[(x + xoffset + camX) + BUFFERWIDTH * (y + yoffset + camY)].Char.AsciiChar =
          image->chars[x + image->width * y];
        DOUBLE_BUFFER[(x + xoffset + camX) + BUFFERWIDTH * (y + yoffset + camY)].Attributes =
          image->colors[x + image->width * y];
      }
    }
  }

  return RETURN_SUCCESS;
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
// Does NOT take cam coordinates into consideration
RETURN_TYPE RenderPImageToScreenNoCam( IMAGE *image, int xoffset, int yoffset )
{
  int x, y;

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  for(y = 0; y < image->height; ++y)
  {
    for(x = 0; x < image->width; ++x)
    {
      if(ScreenBoundCheck( x + xoffset, y + yoffset ) && image->chars[x + image->width * y] != TRANSPERANT)
      {
        DOUBLE_BUFFER[(x + xoffset) + BUFFERWIDTH * (y + yoffset)].Char.AsciiChar =
          image->chars[x + image->width * y];
        DOUBLE_BUFFER[(x + xoffset) + BUFFERWIDTH * (y + yoffset)].Attributes =
          image->colors[x + image->width * y];
      }
    }
  }

  return RETURN_SUCCESS;
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
RETURN_TYPE WriteImageToScreen( const char *imageID, int xoffset, int yoffset )
{
  IMAGE *image = FIND_DATA( P_IMAGE, IMAGE_TABLE, imageID ); // Get image pointer

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  return RenderPImageToScreen( image, xoffset, yoffset );
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
// Does NOT take cam coordinates into consideration
RETURN_TYPE WriteImageToScreenNoCam( const char *imageID, int xoffset, int yoffset )
{
  IMAGE *image = FIND_DATA( P_IMAGE, IMAGE_TABLE, imageID ); // Get image pointer

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  return RenderPImageToScreenNoCam( image, xoffset, yoffset );
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
// Only draws from the coordinates of topLeft and topRight on the source image
RETURN_TYPE WritePortionOfImageToScreen( const char *imageID, AE_COORD topLeft, AE_COORD bottomRight, int xoffset, int yoffset )
{
  int x, y;
  IMAGE *image = FIND_DATA( P_IMAGE, IMAGE_TABLE, imageID ); // Get image pointer
  int camX = (int)GLOBAL_CAM.center.x_;
  int camY = (int)GLOBAL_CAM.center.y_;

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  for(y = topLeft.y_; y < bottomRight.y_; ++y)
  {
    for(x = topLeft.x_; x < bottomRight.x_; ++x)
    {
      if(ScreenBoundCheck( x + xoffset + camX, y + yoffset + camY ) && image->chars[x + image->width * y] != TRANSPERANT)
      {
        DOUBLE_BUFFER[(x + xoffset + camX) + BUFFERWIDTH * (y + yoffset + camY)].Char.AsciiChar =
          image->chars[x + image->width * y];
        DOUBLE_BUFFER[(x + xoffset + camX) + BUFFERWIDTH * (y + yoffset + camY)].Attributes =
          image->colors[x + image->width * y];
      }
    }
  }

  return RETURN_SUCCESS;
}

//
// WriteImageToImage
// Purpose: Draws an image onto another image
//
RETURN_TYPE WriteImageToImage( const char *drawOnMe, const char *drawWithMe, int xOffset, int yOffset )
{
  int x, y;
  CHAR *thisChar;
  COL *thisColor;
  IMAGE *drawOnMeImage = FIND_DATA( P_IMAGE, IMAGE_TABLE, drawOnMe );
  IMAGE *drawWithMeImage = FIND_DATA( P_IMAGE, IMAGE_TABLE, drawWithMe );
  
  // Return failure if images not found in lookup
  if(!drawOnMeImage || !drawWithMeImage)
  {
    return RETURN_FAILURE;
  }

  // Make sure there's actually room to perform writing
  if(!(drawOnMeImage->height >= drawWithMeImage->height + yOffset &&
       drawOnMeImage->width  >= drawWithMeImage->width  + xOffset))
  {
    // The draw with me image + offset went out of bounds of the
    // draw on me image!
    return RETURN_FAILURE;
  }

  for(y = 0; y < drawWithMeImage->height; ++y)
  {
    for(x = 0; x < drawWithMeImage->width; ++x)
    {
      thisChar = CharAt( drawOnMeImage, x + xOffset, y + yOffset );
      thisColor = ColorAt( drawOnMeImage, x + xOffset, y + yOffset );
      if(*(CharAt( drawWithMeImage, x, y )) != TRANSPERANT) // Do not draw transparency!
      {
        *thisChar = *(CharAt( drawWithMeImage, x, y ));
        *thisColor = *(ColorAt( drawWithMeImage, x, y ));
      }
    }
  }

  return RETURN_SUCCESS;
}

//
// WriteCharToBuffer
// Purpose: Writes a single character to the buffer
//
void WriteCharToBuffer( CHAR character, COL color, int x, int y )
{
  int camX = (int)GLOBAL_CAM.center.x_;
  int camY = (int)GLOBAL_CAM.center.y_;

  DOUBLE_BUFFER[x + camX + BUFFERWIDTH * (y + camY)].Char.AsciiChar = character;
  DOUBLE_BUFFER[x + camX + BUFFERWIDTH * (y + camY)].Attributes = color;
  return;
}

//
// WriteStringToScreen
// Purpose: Writes a null terminated string to the buffer, with
//          designated starting point and ending point.
//
void WriteStringToScreen( char string[], int x, int y )
{
  int i;
  int camX = (int)GLOBAL_CAM.center.x_;
  int camY = (int)GLOBAL_CAM.center.y_;
  
  for (i = 0; string[i] != 0; ++i, ++x)
  {
    if(ScreenBoundCheck( x, y ))
    {
      DOUBLE_BUFFER[(x + camX) + BUFFERWIDTH * (y + camY)].Char.AsciiChar = string[i];
      DOUBLE_BUFFER[(x + camX) + BUFFERWIDTH * (y + camY)].Attributes = 7;
    }
  }
}

//
// WriteStringToScreen
// Purpose: Writes a null terminated string to the buffer, with
//          designated starting point and ending point.
//
void WriteStringToScreenNoCam( char string[], int x, int y )
{
  int i;
  
  for (i = 0; string[i] != 0; ++i, ++x)
  {
    if(ScreenBoundCheck( x, y ))
    {
      DOUBLE_BUFFER[(x) + BUFFERWIDTH * (y)].Char.AsciiChar = string[i];
      DOUBLE_BUFFER[(x) + BUFFERWIDTH * (y)].Attributes = 7;
    }
  }
}

//
// WriteCharToImage
// Purpose: Writes a character at a coordinate to an image.
//
RETURN_TYPE WriteCharToImage( IMAGE *image, CHAR character, COL color, int x, int y )
{
  CHAR *thisChar = CharAt( image, x, y );
  COL *thisCol = ColorAt( image, x, y );
  *thisChar = character;
  *thisCol = color;
  return RETURN_SUCCESS;
}

//
// DimensionOffset
// Purpose: Returns EPSILON or 1.f depending on odd/even
//
float DimensionOffset( float dimension )
{
  return ((int)dimension % 2) ? 1.f : EPSILON;
}

//
// UpdateAnimation
// Purpose: Updates an animation
// Notes  : Returns the current frame of the animation, returns -1 if
//          animation is not found
//
int UpdateAnimation( ANIMATION *animation, float dt )
{
  // Animation not found! BAD
  assert( animation );
  
  if(animation)
  {
    animation->dt += dt;

    // If over our delay reset the dt, increment the playcount (if wrapped)
    // and the current frame, wrap frame within numFrames
    if(animation->dt > animation->frameDelay)
    {
      ++animation->currentFrame;
      animation->dt = 0;

      if(animation->currentFrame == animation->numFrames)
      {
        animation->currentFrame = 0;
        ++animation->playCount;
      }
    }
    return animation->currentFrame;
  }

  return -1;
}
