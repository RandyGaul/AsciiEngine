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

#define CHAR unsigned char 
#define COL unsigned char 

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
void WriteStringToScreen( char string[], int x, int y );

#endif  GRAPHICSH