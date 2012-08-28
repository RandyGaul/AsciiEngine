////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "CollisionComponent.h"
#include "Entity.h"
#include "Vector2D.h"
#include "Math2D.h"
#include "Shapes.h"

//
// SQUARE class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _SQUARE_COMPONENT
{
  COLLISION_COMPONENT base;
  AE_RECT rect;
} SQUARE;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SquareCOM_PROC( SQUARE *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SquareCreate( SQUARE *self, float *var1, float *var2 );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SquareInit( const char *className );

//
// ClassSetWidthHeight
// Purpose: Sets the width and height of the class. Takes two floats.
//
void SquareSetWidthHeight( SQUARE *self, float *var1, float *var2 );

//
// ClassGetWidthHeight
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void SquareGetWidthHeight( SQUARE *self, float *var1, float *var2 );


//
// ClassSendHitTest
// Purpose: 
// Notes  : 
//
void SquareSendHitTest( SQUARE *self, float *dt );

//
// ClassHitTest
// Purpose: 
//
void SquareHitTest( SQUARE *self, COL_DATA *data );

//
// ClassIHitYou
// Purpose: A response message sent to the sender of a EM_HITTEST message
//          var1 is pointer to the sender (ENTITY *)
//          var2 is BOOL for x(true) or y(false) axis collision
//
void SquareIHitYou( SQUARE *self, ENTITY *collidee, BOOL axis );
