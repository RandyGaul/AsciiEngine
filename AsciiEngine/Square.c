////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "Square.h"
#include "EntityManager.h"
#include "Component.h"
#include "Math2D.h"
#include "FrameRateController.h"
#include "Input.h"
#include "EntityFactory.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SquareCOM_PROC( SQUARE *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
  case EM_CLSINIT:
    SquareInit( (const char *)var1 );
    break;
  case EM_CREATE:
    SquareCreate( self, (float *)var1, (float *)var2 );
    break;
    
    // COLLISION
  case EM_UPDATE:
    SquareSendHitTest( self, (float *)var1 );
    break;
  case EM_HITTEST:
    SquareHitTest( self, (COL_DATA *)var1 );
    break;
  case EM_IHITYOU:
    SquareIHitYou( self, (ENTITY *)var1, var2 );
    break;

    // DATA ACCESS
  case EM_SETWH:
    SquareSetWidthHeight( self, (float *)var1, (float *)var2 );
    break;
  case EM_GETWH:
    SquareGetWidthHeight( self, (float *)var1, (float *)var2 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SquareCreate( SQUARE *self, float *width, float *height )
{
  self->base.CLASS_NAME = CLASS_NAME;
  SendEntityMessage( self->base.owner, EM_SETWH, (int)width, (int)height );
}

//
// ClassSetWidthHeight
// Purpose: Sets the width and height of the class. Takes two floats.
//
void SquareSetWidthHeight( SQUARE *self, float *var1, float *var2 )
{
  self->rect.width_ = *var1;
  self->rect.height_ = *var2;
}

//
// ClassGetWidthHeight
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void SquareGetWidthHeight( SQUARE *self, float *var1, float *var2 )
{
  *var1 = self->rect.width_;
  *var2 = self->rect.height_;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SquareInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ClassSendHitTest
// Purpose: 
// Notes  : 
//
void SquareSendHitTest( SQUARE *self, float *dt )
{
  COL_DATA data = { 0 };

  // Customize settings
  if(self->base.owner->properties & DAMAGE_DEALER)
    data.flag = DONT_COLLIDE_WITH_OTHERS | DAMAGE_DEALER_COLLISION;
  if(self->base.owner->properties & PICK_ME_UP_ITEM)
    data.flag = ITEM_COLLISION;

  // Fill out the collision data structure with appropriate information
  data.entity = self->base.owner;
  SendEntityMessage( data.entity, EM_GETPOS, (int)&data.rect.center_.x_, (int)&data.rect.center_.y_ );
  SendEntityMessage( data.entity, EM_GETWH, (int)&data.rect.width_, (int)&data.rect.height_ );

  // Step x and test for collision on x axis
  SendEntityMessage( data.entity, EM_STEPXPOS, (int)&data.rect.center_.x_, (int)dt );

  // Send test message for x axis, record shortest distance found
  SendEntitiesMessage( EM_HITTEST, (int)&data, 0 );
  if(data.closestEntity)
  {
    data.flag |= AXIS;
    SendEntityMessage( data.entity, EM_IHITYOU, (int)data.closestEntity, data.flag );
  }

  // Reset data from last test
  SendEntityMessage( data.entity, EM_GETPOS, (int)&data.rect.center_.x_, (int)&data.rect.center_.y_ );
  data.closestEntity = NULL;
  data.shortestDist = 0;
  data.flag &= ~AXIS;

  // Step y and test for collision on the y axis
  SendEntityMessage( data.entity, EM_STEPYPOS, (int)&data.rect.center_.y_, (int)dt );

  // Send test message for y axis
  SendEntitiesMessage( EM_HITTEST, (int)&data, 0 );
  if(data.closestEntity)
    SendEntityMessage( data.entity, EM_IHITYOU, (int)data.closestEntity, data.flag );
}

//
// ClassHitTest
// Purpose: 
//
void SquareHitTest( SQUARE *self, COL_DATA *data )
{
  AE_RECT selfRect = { 0 };

  // Skip collision with self or if DONT_COLLIDE_WITH_ME flag is set
  if(self->base.owner == data->entity || self->base.owner->properties & DONT_COLLIDE_WITH_ME)
    return;

  // Skip collision of ITEM_COLLISION with NO_PICKUP_ITEMS
  if(data->flag & ITEM_COLLISION && self->base.owner->properties & NO_PICKUP_ITEMS)
    return;

  // Skip if inactive
  if(self->base.owner->inactive || data->entity->inactive)
    return;

  // Get width and height from self and construct a rect structure
  SendEntityMessage( self->base.owner, EM_GETWH, (int)&selfRect.width_, (int)&selfRect.height_ );
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&selfRect.center_.x_, (int)&selfRect.center_.y_ );

  // Conduct collision test, if true get distance. Compare distance with
  // current distance within the COL_DATA, if smaller then record to find
  // the shortest collision distance.
  if(StaticRectToStaticRect( &selfRect, &data->rect ))
  {
    float distance = Vector2DSquareDistance( &selfRect.center_, &data->rect.center_ );
    if(distance < data->shortestDist || data->shortestDist == 0)
    {
      data->shortestDist = distance;
      data->closestEntity = self->base.owner;
    }
  }
}

//
// ClassIHitYou
// Purpose: A response message sent to the sender of a EM_HITTEST message
//          var1 is pointer to the sender (ENTITY *)
//          var2 is a bitfield flag of properties from Properties.h
//
void SquareIHitYou( SQUARE *self, ENTITY *collidee, int flags )
{
  VECTOR2D vel = { 0 }, inputVec = { 0 }, selfPos = { 0 }, collideePos = { 0 }, selfWH = { 0 }, collideeWH = { 0 }, collideeVel = { 0 };

  if(self->base.owner == collidee)
    return;

  // Gather data for inputVec, vel, selfPos, collideePos, selfWH, collideeWH
  SendEntityMessage( self->base.owner, EM_GETVEL, (int)&vel.x_, (int)&vel.y_ );
  SendEntityMessage( self->base.owner, EM_GETINVEC, (int)&inputVec.x_, (int)&inputVec.y_ );
  SendEntityMessage( self->base.owner, EM_GETWH, (int)&selfWH.x_, (int)&selfWH.y_ );
  SendEntityMessage( collidee, EM_GETWH, (int)&collideeWH.x_, (int)&collideeWH.y_ );
  SendEntityMessage( collidee, EM_GETVEL, (int)&collideeVel.x_, (int)&collideeVel.y_ );
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&selfPos.x_, (int)&selfPos.y_ );
  SendEntityMessage( collidee, EM_GETPOS, (int)&collideePos.x_, (int)&collideePos.y_ );
   
  
  // If generic collision type
  if(!(flags & DONT_COLLIDE_WITH_OTHERS) &&
    !(collidee->properties & PLAYER && flags & ITEM_COLLISION) // Special case of item to player
    )
  {
    // TRUE == x axis
    if(flags & AXIS)
    {
      // Going right
      if(vel.x_ + inputVec.x_ > 0)
      {
        // Zero velocity and inputVec on proper axis
        vel.x_ = 0;
        inputVec.x_ = 0;
        SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
        SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVec.x_, (int)&inputVec.y_ );

        // Set right side of self to left side of collidee
        selfPos.x_ = collideePos.x_ - collideeWH.x_ / 2.f - selfWH.x_ / 2.f;
        SendEntityMessage( self->base.owner, EM_SETPOS, (int)&selfPos.x_, (int)&selfPos.y_ );
      }
      // Going left
      if(vel.x_ + inputVec.x_ < 0)
      {
        // Zero velocity and inputVec on proper axis
        vel.x_ = 0;
        inputVec.x_ = 0;
        SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
        SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVec.x_, (int)&inputVec.y_ );

        // Set left side of self to right side of collidee
        selfPos.x_ = collideePos.x_ + collideeWH.x_ / 2.f + selfWH.x_ / 2.f;
        SendEntityMessage( self->base.owner, EM_SETPOS, (int)&selfPos.x_, (int)&selfPos.y_ );
      }
    }
    // FALSE == y axis
    else
    {
      // Going down
      if(vel.y_ + inputVec.y_ > 0)
      {
        // Zero velocity and inputVec on proper axis
        vel.y_ = 0;
        inputVec.y_ = 0;
        if(flags & ITEM_COLLISION) // Make items stick to ground
        {
        vel.x_ = 0;
        inputVec.x_ = 0;
        }
        SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
        SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVec.x_, (int)&inputVec.y_ );

        // Set bottom of self to top of collidee
        selfPos.y_ = collideePos.y_ - collideeWH.y_ / 2.f - selfWH.y_ / 2.f;
        SendEntityMessage( self->base.owner, EM_SETPOS, (int)&selfPos.x_, (int)&selfPos.y_ );

        // Send message to tell self that it's not jumping anymore
        SendEntityMessage( self->base.owner, EM_SETJUMPN, 0, 0 );
      }
      // Going up
      else if(vel.y_ + inputVec.y_ < 0)
      {
        // Zero velocity and inputVec on proper axis
        vel.y_ = 0;
        inputVec.y_ = 0;
        SendEntityMessage( self->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
        SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVec.x_, (int)&inputVec.y_ );

        // Set top of self to bottom of collidee
        selfPos.y_ = collideePos.y_ + collideeWH.y_ / 2.f + selfWH.y_ / 2.f;
        SendEntityMessage( self->base.owner, EM_SETPOS, (int)&selfPos.x_, (int)&selfPos.y_ );
      }
    }
  }
  // Damage dealer collision
  else if(flags & DAMAGE_DEALER_COLLISION && flags & AXIS)
  {
    SendEntityMessage( collidee, EM_DAMAGEHP, self->base.owner->data, 0 );
    // FIXME : ADD IN CREATION OF THE PRETTY DAMAGE NUMBERS HEHE
  }
  // Item to player, but not full inventory
  else if(collidee->properties & PLAYER && flags & ITEM_COLLISION)
  {
    SendEntityMessage( collidee, EM_INSINV, self->base.owner->data, 0 );
    SendEntityMessage( self->base.owner, EM_INACTIVE, 0, 0 );
    CreateEntities( "ITEM_PARTICLE", (int)&selfPos.x_, (int)&selfPos.y_, ITEM_PARTICLE_SPAWN_COUNT );
  }
}
