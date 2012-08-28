////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// A loci is a collection of points that perform a specific task.
// A locus is a single point within a loci. In this engine loci are
// used as collections of mid-points of various images to draw in order
// to represent entitys with multiple images. Each locus is mapped
// within a loci by a unique to the loci string key.

#ifndef LOCIH
#define LOCIH

#include <stdarg.h>
#include "GlobalDefines.h"
#include "StringHash.h"
#include "Graphics.h"
#include "Vector2D.h"
#include "HashTable.h"

extern unsigned HIGHEST_ZORDER;

typedef struct _LOCUS
{
  unsigned zOrder;
  const char *ID;
  VECTOR2D coord;
  BOOL isActive;
  IMAGE *image;
  ANIMATION *animation;
} LOCUS;

typedef LOCUS *P_LOCUS;

DECLARE_TABLE( P_LOCUS, MAX_KEY_LEN );

//
// AllocateImageLocus
// Purpose: Allocates a locus with an image inside.
//
LOCUS *AllocateImageLocus( const char *name, float x, float y, IMAGE *image, unsigned zOrder );

//
// AllocateAnimationLocus
// Purpose: Allocates a locus with an animation inside.
//
LOCUS *AllocateAnimationLocus( const char *name, float x, float y, unsigned zOrder, float frameDelay, const char *firstFrame, ... );

//
// DeallocateLocus
// Purpose: Deallocates a locus.
//
RETURN_TYPE DeallocateLocus( LOCUS *locus );


#endif  LOCIH