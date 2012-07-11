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
#include "StringHash.h"

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

  for(y = 0; y < image->height; y++)
  {
    for(x = 0; x < image->width; x++)
    {
      thisChar = CharAt( image, x, y );
      *thisChar = 0;
    }
  }

  for(y = 0; y < image->height; y++)
  {
    for(x = 0; x < image->width; x++)
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
  IMAGE *image = (IMAGE *)malloc( sizeof( IMAGE )
                                  + strlen( string ) + 1
                                  + width * height * sizeof( unsigned char )
                                  + width * height * sizeof( unsigned char ) + 4 +
                                  (sizeof( IMAGE )
                                  + strlen( string ) + 1
                                  + width * height * sizeof( unsigned char )
                                  + width * height * sizeof( unsigned char ) + 4) % 4);

  image->width = width;
  image->height = height;

  // Initialize the ID pointer to directly after the IMAGE struct
  image->ID = PtrAdd( image, sizeof( IMAGE ) );
  strcpy_s( image->ID, strlen( string ) + 1, string );

  // Initialize chars pointer to directly after the ID string
  image->chars = PtrAdd( image->ID, strlen( image->ID ) + 1 );

  // Initialize colors pointer to directly after chars array
  image->colors = PtrAdd( image->chars, width * height * sizeof( CHAR ));

  // Initialize the chars and colors arrays to zero in the image
  ZeroImage( image );

  // Insert the image into the hash table of images  
  AE_LoadImage( image );

  return image;
}

// Deallocates an image. Be sure to check the return type to see
// if success or failure. Failure most likely means your imageID
// was not found.
RETURN_TYPE DeallocateImage( const char *imageID )
{
  IMAGE *image = AE_FindImage( imageID );

  if(!image)
  {
    return RETURN_FAILURE;
  }

  free( image );
  return RETURN_SUCCESS;
}

// This is called once to initialize the graphics system.
void InitGraphics( int width, int height )
{
  // Setup various images in memory for use throughout the program
  CHAR charArray2[1 * 1] = {
    0xDB,
  };
  COL colorArray2[1 * 1] = {
    0x04,
  };
  IMAGE *image2;

  // Create the double buffer in memory, zero it, and set the BUFFER constants
  DOUBLE_BUFFER = (CHAR_INFO *)malloc( sizeof( CHAR_INFO ) * width * height );
  memset( DOUBLE_BUFFER, '\0', sizeof( CHAR_INFO ) * width * height );
  BUFFERHEIGHT = height;
  BUFFERWIDTH = width;

  // Load all the various images used throughout the project
  image2 = AllocateImage( "REDSQUARE", 1, 1 );
  ImageSet( image2, charArray2, colorArray2 );
}

// Checks to make sure a coordinate is within the boundaries of the screen or not
BOOL ScreenBoundCheck( int x, int y )
{
  return (x < BUFFERWIDTH && x > -1 && y < BUFFERHEIGHT && y > -1) ? TRUE : FALSE;
}

// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
RETURN_TYPE WriteImageToScreen( const char *imageID, int xoffset, int yoffset )
{
  int x, y;
  IMAGE *image = AE_FindImage( imageID ); // Get image pointer

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  for(y = 0; y < image->height; ++y)
  {
    for(x = 0; x < image->width; ++x)
    {
      if(ScreenBoundCheck( x + xoffset, y + yoffset ) && image->chars[x + image->width * y] != 255)
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
// Only draws from the coordinates of topLeft and topRight on the source image
RETURN_TYPE WritePortionOfImageToScreen( const char *imageID, AE_COORD topLeft, AE_COORD bottomRight, int xoffset, int yoffset )
{
  int x, y;
  IMAGE *image = AE_FindImage( imageID ); // Get image pointer

  // Return failure if image not found in lookup
  if(!image)
  {
    return RETURN_FAILURE;
  }

  for(y = topLeft.y_; y < bottomRight.y_; ++y)
  {
    for(x = topLeft.x_; x < bottomRight.x_; ++x)
    {
      if(ScreenBoundCheck( x + xoffset, y + yoffset ) && image->chars[x + image->width * y] != 255)
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

//
// WriteImageToImage
// Purpose: Draws an image onto another image
//
RETURN_TYPE WriteImageToImage( const char *drawOnMe, const char *drawWithMe, int xOffset, int yOffset )
{
  int x, y;
  CHAR *thisChar;
  COL *thisColor;
  IMAGE *drawOnMeImage = AE_FindImage( drawOnMe );
  IMAGE *drawWithMeImage = AE_FindImage( drawWithMe );
  
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
      *thisChar = *(CharAt( drawWithMeImage, x, y ));
      *thisColor = *(ColorAt( drawWithMeImage, x, y ));
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
  DOUBLE_BUFFER[x + BUFFERWIDTH * y].Char.AsciiChar = character;
  DOUBLE_BUFFER[x + BUFFERWIDTH * y].Attributes = color;
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
  
  for (i = 0; string[i] != 0; ++i, ++x)
  {
    DOUBLE_BUFFER[x + BUFFERWIDTH * y].Char.AsciiChar = string[i];
    DOUBLE_BUFFER[x + BUFFERWIDTH * y].Attributes = 7;
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
