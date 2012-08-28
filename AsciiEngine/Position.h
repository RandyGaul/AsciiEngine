////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Shapes.h"
#include "PositionComponent.h"

//
// Position class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _POS_COMPONENT
{
  POSITION_COMPONENT base;
  VECTOR2D pos;
} POS;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PosCOM_PROC( POSITION_COMPONENT *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PosCreate( POS *self, float *x, float *y );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PosInit( const char *className );

//
// ClassSetPos
// Purpose: Sets the position of the class. Takes two floats.
//
void PosSetPos( POS *self, float *var1, float *var2 );

//
// ClassGetPos
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PosGetPos( POS *self, float *var1, float *var2 );
