////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef REDSQUAREH
#define REDSQUAREH

#include "GameObject.h"
#include "Shapes.h"
#include "Graphics.h"
#include "StringHash.h"
#include "FrameRateController.h"

// Forward declaration for proper compilation
struct _REDSQUARE;

// Prototype of the five functions for this object type
void RedSquareConstruct( struct _REDSQUARE *self );
void RedSquareInit     ( struct _REDSQUARE *self );
void RedSquareSet      ( struct _REDSQUARE *self, const AE_RECT rect, const IMAGE *image );
void RedSquareUpdate   ( struct _REDSQUARE *self );
void RedSquareDraw     ( struct _REDSQUARE *self );
void RedSquareDestroy  ( struct _REDSQUARE *self );

// Virtual table of methods for this object type. This vtable
// is pointed to by the base class. The base classe's vtable pointer
// is assigned by the ObjectFactory.
typedef struct _REDSQUARE_VTABLE
{
  void (*Construct)( struct _REDSQUARE *self );
  void (*Init)     ( struct _REDSQUARE *self );
  void (*set)      ( struct _REDSQUARE *self, const AE_RECT rect, const IMAGE *image );
  void (*Update)   ( struct _REDSQUARE *self );
  void (*Draw)     ( struct _REDSQUARE *self );
  void (*Destroy)  ( struct _REDSQUARE *self );
} _REDSQUARE_VTABLE;

// This external declaration is required for the object factory to assign
// the vtable of this file's object to itself upon creation.
extern const _REDSQUARE_VTABLE REDSQUARE_VTABLE;

// Definition of the object
typedef struct _REDSQUARE
{
  GAMEOBJECT base_;       // Contains base class
  AE_RECT rect_;          // Represents the rectangle data
  const IMAGE *image_;    // Pointer to the image to represent this object
  VECTOR2D vel_;          // Velocity vector for this object
  float accel_;           // Acceleration scalar for this object
} REDSQUARE;

#endif  REDSQUAREH
