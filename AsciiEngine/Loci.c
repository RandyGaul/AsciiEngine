////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "Loci.h"
#include "ImageTable.h"

unsigned HIGHEST_ZORDER = 10;

DEFINE_TABLE( P_LOCUS, DeallocateLocus );

//
// AllocateImageLocus
// Purpose: Allocates a locus with an image inside.
//
LOCUS *AllocateImageLocus( const char *name, float x, float y, IMAGE *image, unsigned zOrder )
{
  LOCUS *locus = (LOCUS *)malloc( sizeof( LOCUS ) + strlen( name ) + 1 );
  locus->ID = PtrAdd( locus, sizeof( LOCUS ) );
  strcpy_s( (char *)locus->ID, strlen( name ) + 1, (char *)name );
  locus->coord.x_ = x;
  locus->coord.y_ = y;
  locus->image = image;
  locus->isActive = TRUE;
  locus->animation = NULL;
  locus->zOrder = zOrder;

  // Keep track of highest zOrder for use in Cloud.c in drawing
  if(HIGHEST_ZORDER < zOrder)
  {
    HIGHEST_ZORDER = zOrder;
  }

  return locus;
}

//
// AllocateAnimationLocus
// Purpose: Allocates a locus with an animation inside.
//
LOCUS *AllocateAnimationLocus( const char *name, float x, float y, unsigned zOrder, float frameDelay, const char *firstFrame, ... )
{
  va_list args;
  ANIMATION *animation = NULL;
  const char *next = firstFrame;
  int frameIterator = 0, numFrames = 0;
  LOCUS *locus = (LOCUS *)malloc( sizeof( LOCUS ) + strlen( name ) + 1 );
  locus->ID = PtrAdd( locus, sizeof( LOCUS ) );
  va_start( args, firstFrame );

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

  strcpy_s( (char *)locus->ID, strlen( name ) + 1, (char *)name );
  locus->coord.x_ = x;
  locus->coord.y_ = y;
  locus->animation = animation;
  locus->isActive = TRUE;
  locus->image = NULL;
  locus->zOrder = zOrder;

  // Keep track of highest zOrder for use in Cloud.c in drawing
  if(HIGHEST_ZORDER < zOrder)
  {
    HIGHEST_ZORDER = zOrder;
  }

  return locus;
}

//
// DeallocateLocus
// Purpose: Deallocates a locus.
//
RETURN_TYPE DeallocateLocus( LOCUS *locus )
{
  if(locus->image)
  {
    free( locus );
  }
  else if(locus->animation)
  {
    free( locus->animation );
    free( locus );
  }

  return RETURN_SUCCESS;
}
