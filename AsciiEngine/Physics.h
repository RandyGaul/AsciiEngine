////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "PhysicsComponent.h"
#include "Entity.h"
#include "Vector2D.h"

//
// PHYSICS class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _PHYS_COMPONENT
{
  PHYSICS_COMPONENT base;
  VECTOR2D vel;
  VECTOR2D accel;
} PHYS;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PhysCOM_PROC( PHYS *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PhysCreate( PHYS *self, VECTOR2D *vel, VECTOR2D *accel );

//
// ClassUpdate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PhysUpdate( PHYS *self, float *dt );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PhysInit( const char *className );

//
// ClassSetVel
// Purpose: Sets the velocity of the class. Takes two floats.
//
void PhysSetVel( PHYS *self, float *var1, float *var2 );

//
// ClassStepXPos
// Purpose: Copies the stepped value of vel into float *var1, var2 is (float *)dt provided for step
//          Does not actually modify anything, only retrieves values stepped by dt
//
void PhysStepXPos( PHYS *self, float *var1, float *dt );


//
// ClassStepYPos
// Purpose: Copies the stepped value of vel into float *var1, var2 is (float *)dt provided for step
//          Does not actually modify anything, only retrieves values stepped by dt
//
void PhysStepYPos( PHYS *self, float *var1, float *dt );

//
// ClassSetAccel
// Purpose: Sets the velocity of the class. Takes two floats.
//
void PhysSetAccel( PHYS *self, float *var1, float *var2 );

//
// ClassGetVel
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PhysGetVel( PHYS *self, float *var1, float *var2 );

//
// ClassGetAccel
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PhysGetAccel( PHYS *self, float *var1, float *var2 );

//
// ClassApplyGravity
// Purpose: Applies gravity to the vel y component.
//
void PhysApplyGravity( PHYS *self, float *dt );
