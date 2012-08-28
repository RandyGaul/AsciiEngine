////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Physics.h"
#include "PositionComponent.h"
#include "EntityManager.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PhysCOM_PROC( PHYS *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CLSINIT:
    PhysInit( (const char *)var1 );
    break;
  case EM_CREATE:
    PhysCreate( self, (VECTOR2D *)var1, (VECTOR2D *)var2 );
    break;
  case EM_UPDATE:
    PhysUpdate( self, (float *)var1 );
    break;
  case EM_GRAVITY:
    PhysApplyGravity( self, (float *)var1 );
    break;

    // DATA ACCESS
  case EM_SETVEL:
    PhysSetVel( self, (float *)var1, (float *)var2 );
    break;
  case EM_SETACCEL:
    PhysSetAccel( self, (float *)var1, (float *)var2 );
    break;
  case EM_GETVEL:
    PhysGetVel( self, (float *)var1, (float *)var2 );
    break;
  case EM_GETACCEL:
    PhysGetAccel( self, (float *)var1, (float *)var2 );
    break;
  case EM_STEPXPOS:
    PhysStepXPos( self, (float *)var1, (float *)var2 );
    break;
  case EM_STEPYPOS:
    PhysStepYPos( self, (float *)var1, (float *)var2 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PhysCreate( PHYS *self, VECTOR2D *vel, VECTOR2D *accel )
{
  self->base.CLASS_NAME = CLASS_NAME;
  self->base.COM_PROC( (PHYSICS_COMPONENT *)self, EM_SETVEL,   (int)&vel->x_, (int)&vel->y_ );
  self->base.COM_PROC( (PHYSICS_COMPONENT *)self, EM_SETACCEL, (int)&accel->x_, (int)&accel->y_ );
}

//
// ClassUpdate
// Purpose: Upates the class. In this case Euler integration is performed.
//
void PhysUpdate( PHYS *self, float *dt )
{
  VECTOR2D vel = { 0 }, accel = { 0 }, pos= { 0 }, inputVector = { 0 };

  // Get accel and vel and inputVector
  SendEntityMessage( self->base.owner, EM_GETVEL, (int)&vel.x_, (int)&vel.y_ );
  SendEntityMessage( self->base.owner, EM_GETACCEL, (int)&accel.x_, (int)&accel.y_ );
  SendEntityMessage( self->base.owner, EM_GETINVEC, (int)&inputVector, 0 );

  // Integrate
  vel.x_ += accel.x_ * *dt;
  vel.y_ += accel.y_ * *dt;

  // Set vel
  SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );

  // Get pos
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );

  // Integrate
  pos.x_ += (vel.x_ + inputVector.x_) * *dt;
  pos.y_ += (vel.y_ + inputVector.y_) * *dt;

  // Set pos
  SendEntityMessage( self->base.owner, EM_SETPOS, (int)&pos.x_, (int)&pos.y_ );
}

//
// ClassApplyGravity
// Purpose: Applies gravity to the vel y component.
//
void PhysApplyGravity( PHYS *self, float *dt )
{
  VECTOR2D vel;
  SendEntityMessage( self->base.owner, EM_GETVEL, (int)&vel.x_, (int)&vel.y_ );

  vel.y_ += GRAVITY * *dt;

  SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
}

//
// ClassSetVel
// Purpose: Sets the velocity of the class. Takes two floats.
//
void PhysSetVel( PHYS *self, float *var1, float *var2 )
{
  self->vel.x_ = *var1;
  self->vel.y_ = *var2;
}

//
// ClassSetAccel
// Purpose: Sets the acceleration of the class. Takes two floats.
//
void PhysSetAccel( PHYS *self, float *var1, float *var2 )
{
  self->accel.x_ = *var1;
  self->accel.y_ = *var2;
}

//
// ClassGetPos
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PhysGetPos( PHYS *self, float *var1, float *var2 )
{
  *var1 = self->vel.x_;
  *var2 = self->vel.y_;
}

//
// ClassGetVel
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PhysGetVel( PHYS *self, float *var1, float *var2 )
{
  *var1 = self->vel.x_;
  *var2 = self->vel.y_;
}

//
// ClassStepXPos
// Purpose: Copies the stepped value of vel into float *var1, var2 is (float *)dt provided for step
//          Does not actually modify anything, only retrieves values stepped by dt
//
void PhysStepXPos( PHYS *self, float *var1, float *dt )
{
  VECTOR2D posCopy = { 0 }, velCopy = { 0 }, inputVec = { 0 };
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&posCopy.x_, (int)&posCopy.y_ );
  SendEntityMessage( self->base.owner, EM_GETINVEC, (int)&inputVec, 0 );

  // Create a copy of the stepped velocity
  velCopy.x_ = self->vel.x_ + inputVec.x_ + self->accel.x_ * *dt;

  // Step the copy of position and place it into var1
  *var1 = posCopy.x_ + velCopy.x_ * *dt;
}

//
// ClassStepYPos
// Purpose: Copies the stepped value of vel into float *var1, var2 is (float *)dt provided for step
//          Does not actually modify anything, only retrieves values stepped by dt
//
void PhysStepYPos( PHYS *self, float *var1, float *dt )
{
  VECTOR2D posCopy = { 0 }, velCopy = { 0 }, inputVec = { 0 };
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&posCopy.x_, (int)&posCopy.y_ );
  SendEntityMessage( self->base.owner, EM_GETINVEC, (int)&inputVec, 0 );

  // Create a copy of the stepped velocity
  velCopy.y_ = self->vel.y_ + inputVec.y_ + self->accel.y_ * *dt;

  // Step the copy of position and place it into var1
  *var1 = posCopy.y_ + velCopy.y_ * *dt;
}


//
// ClassGetAccel
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PhysGetAccel( PHYS *self, float *var1, float *var2 )
{
  *var1 = self->accel.x_;
  *var2 = self->accel.y_;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PhysInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}