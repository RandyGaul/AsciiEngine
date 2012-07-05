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
                                  + width * height * sizeof( unsigned char ) );

  image->width = width;
  image->height = height;

  // Initialize the ID pointer to directly after the IMAGE struct
  image->ID = PtrAdd( image, sizeof( IMAGE ) );
  strcpy( image->ID, string );

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
  CHAR charArray2[3 * 3] = {
    0xDB, 0xDB, 0xDB,
    0xDB, 0xDB, 0xDB,
    0xDB, 0xDB, 0xDB,
  };
  COL colorArray2[3 * 3] = {
    0x04, 0x04, 0x04,
    0x04, 0x04, 0x04,
    0x04, 0x04, 0x04,
  };
  IMAGE *image2;

  // Create the double buffer in memory, zero it, and set the BUFFER constants
  DOUBLE_BUFFER = (CHAR_INFO *)malloc( sizeof( CHAR_INFO ) * width * height );
  memset( DOUBLE_BUFFER, '\0', sizeof( CHAR_INFO ) * width * height );
  BUFFERHEIGHT = height;
  BUFFERWIDTH = width;

  // Load all the various images used throughout the project
  image2 = AllocateImage( "REDSQUARE", 3, 3 );
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
