////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2011/12/windows-console-game-painters-algorithm.html
//                http://cecilsunkure.blogspot.com/2012/02/windows-console-game-variable-sized.html

#ifndef GRAPHICSH
#define GRAPHICSH

#include <windows.h>
#include "GlobalDefines.h"
#include "Math2D.h"

#define CHAR unsigned char 
#define COL unsigned char 

#define FOREGROUND_COLOR_1    0x0001
#define FOREGROUND_COLOR_2    0x0002
#define FOREGROUND_COLOR_3    0x0004
#define FOREGROUND_INTENSITY  0x0008
#define BACKGROUND_COLOR_1    0x0010
#define BACKGROUND_COLOR_2    0x0020
#define BACKGROUND_COLOR_3    0x0040
#define BACKGROUND_INTENSITY  0x0080

#define CharAt( image, x, y ) \
  (CHAR *)(PtrAdd( image->chars, ((y) * image->width + (x)) * sizeof( CHAR ) ))

#define ColorAt( image, x, y ) \
  (COL *)(PtrAdd( image->colors, ((y) * image->width + (x)) * sizeof( COL ) ))

extern CHAR_INFO *DOUBLE_BUFFER;
extern int BUFFERHEIGHT;
extern int BUFFERWIDTH;

typedef struct _IMAGE
{
  char *ID; // Image name string, must be unique identifier
  int width; 
  int height;
  unsigned char *chars;
  unsigned char *colors;
} IMAGE;

void ClearBuffer( void );
IMAGE *AllocateImage( const char *string, int width, int height );
RETURN_TYPE DeallocateImage( const char *imageID );
void ImageSet( IMAGE *image, CHAR *charData, COL *colorData );
void ZeroImage( IMAGE *image );
void InitGraphics( int width, int height );
RETURN_TYPE DeallocateImage( const char *imageID );
RETURN_TYPE WriteImageToScreen( const char *imageID, int xoffset, int yoffset );
RETURN_TYPE WriteCharToImage( IMAGE *image, CHAR character, COL color, int x, int y );
void WriteStringToScreen( char string[], int x, int y );
RETURN_TYPE WriteImageToImage( const char *drawOnMe, const char *drawWithMe, int xOffset, int yOffset );// Writes an image onto the DOUBLE_BUFFER
// Does NOT render the DOUBLE_BUFFER to the screen
// Only draws from the coordinates of topLeft and topRight on the source image
RETURN_TYPE WritePortionOfImageToScreen( const char *imageID, AE_COORD topLeft, AE_COORD bottomRight, int xoffset, int yoffset );

#endif  GRAPHICSH