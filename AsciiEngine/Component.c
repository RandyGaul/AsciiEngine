////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Component.h"
#include "Entity.h"

// Component includes
#include "Sprite.h"
#include "Animation.h"
#include "Cloud.h"
#include "Physics.h"
#include "Position.h"
#include "Square.h"
#include "Player.h"
#include "ActionList.h"
#include "Hitpoints.h"
#include "SmallInventory.h"
#include "JumperLittle.h"

//
// AddSpriteComponent
// Purpose: Adds a sprite component to an entity to the graphics
//          component slot.
//
void AddSpriteComponent( ENTITY *self, IMAGE *image, BOOL enableCam )
{
  self->comps.GC = (GRAPHICS_COMPONENT *)malloc( sizeof( SPRITE ) );
  self->comps.GC->owner = self;
  self->comps.GC->COM_PROC = (void (*)( GRAPHICS_COMPONENT *self, EM msg, int var1, int var2 ))SpriteCOM_PROC;
  self->comps.GC->COM_PROC( self->comps.GC, EM_CREATE, (int)image, 0 );
  self->comps.GC->enableCam = enableCam;
}

//
// AddAnimationComponent
// Purpose: Adds a animation component to an entity to the graphics
//          component slot.
//
void AddAnimationComponent( ENTITY *self, ANIMATION *animation, BOOL enableCam )
{
  self->comps.GC = (GRAPHICS_COMPONENT *)malloc( sizeof( ANIMATION ) );
  self->comps.GC->owner = self;
  self->comps.GC->COM_PROC = (void (*)( GRAPHICS_COMPONENT *self, EM msg, int var1, int var2 ))AnimationCOM_PROC;
  self->comps.GC->COM_PROC( self->comps.GC, EM_CREATE, (int)animation, 0 );
  self->comps.GC->enableCam = enableCam;
}

//
// AddCloudComponent
// Purpose: Adds a cloud component to an entity to the graphics
//          component slot.
//
void AddCloudComponent( struct _ENTITY *self, int var1, BOOL enableCam )
{
  self->comps.GC = (GRAPHICS_COMPONENT *)malloc( sizeof( CLOUD ) );
  self->comps.GC->owner = self;
  self->comps.GC->COM_PROC = (void (*)( GRAPHICS_COMPONENT *self, EM msg, int var1, int var2 ))CloudCOM_PROC;
  self->comps.GC->COM_PROC( self->comps.GC, EM_CREATE, var1, 0 );
  self->comps.GC->enableCam = enableCam;
}

//
// AddPositionComponent
// Purpose: Adds a position component to an entity to the position
//          component slot.
//
void AddPositionComponent( ENTITY *self, int var1, int var2 )
{
  self->comps.POSC = (POSITION_COMPONENT *)malloc( sizeof( POS ) );
  self->comps.POSC->owner = self;
  self->comps.POSC->COM_PROC = (void (*)( POSITION_COMPONENT *self, EM msg, int var1, int var2 ))PosCOM_PROC;
  self->comps.POSC->COM_PROC( self->comps.POSC, EM_CREATE, var1, var2 );
}

//
// AddPhysicsComponent
// Purpose: Adds a position component to an entity to the position
//          component slot.
//
void AddPhysicsComponent( ENTITY *self, int var1, int var2 )
{
  self->comps.PC = (PHYSICS_COMPONENT *)malloc( sizeof( PHYS ) );
  self->comps.PC->owner = self;
  self->comps.PC->COM_PROC = (void (*)( PHYSICS_COMPONENT *self, EM msg, int var1, int var2 ))PhysCOM_PROC;
  self->comps.PC->COM_PROC( self->comps.PC, EM_CREATE, var1, var2 );
}

//
// AddSquareComponent
// Purpose: Adds a collision component to an entity to the collision
//          component slot.
//
void AddSquareComponent( ENTITY *self, int var1, int var2 )
{
  self->comps.CC = (COLLISION_COMPONENT *)malloc( sizeof( SQUARE ) );
  self->comps.CC->owner = self;
  self->comps.CC->COM_PROC = (void (*)( COLLISION_COMPONENT *self, EM msg, int var1, int var2 ))SquareCOM_PROC;
  self->comps.CC->COM_PROC( self->comps.CC, EM_CREATE, var1, var2 );
}

//
// AddPlaCComponent
// Purpose: Adds a player component to an entity to the player
//          component slot.
//
void AddPlaCComponent( ENTITY *self )
{
  self->comps.PLAC = (PLAYER_COMPONENT *)malloc( sizeof( PLAC ) );
  self->comps.PLAC->owner = self;
  self->comps.PLAC->COM_PROC = (void (*)( PLAYER_COMPONENT *self, EM msg, int var1, int var2 ))PlaCCOM_PROC;
  self->comps.PLAC->COM_PROC( self->comps.PLAC, EM_CREATE, 0, 0 );
}

//
// AddActionListComponent
// Purpose: Adds an actionList component to an entity to the actionList
//          component slot.
//
void AddActionListComponent( ENTITY *self )
{
  self->comps.AL = (ACTIONLIST_COMPONENT *)malloc( sizeof( AL ) );
  self->comps.AL->owner = self;
  self->comps.AL->COM_PROC = (void (*)( ACTIONLIST_COMPONENT *self, EM msg, int var1, int var2 ))ActionListCOM_PROC;
  self->comps.AL->COM_PROC( self->comps.AL, EM_CREATE, 0, 0 );
}

//
// AddHitPointsComponent
// Purpose: Adds an hitpoints component to an entity to the hitpoints
//          component slot.
//
void AddHitPointsComponent( ENTITY *self, int var1 )
{
  self->comps.HP = (HITPOINTS_COMPONENT *)malloc( sizeof( HP ) );
  self->comps.HP->owner = self;
  self->comps.HP->COM_PROC = (void (*)( HITPOINTS_COMPONENT *self, EM msg, int var1, int var2 ))HitPointsCOM_PROC;
  self->comps.HP->COM_PROC( self->comps.HP, EM_CREATE, var1, 0 );
}

//
// AddSmallInventoryComponent
// Purpose: Adds an small inventory component to an entity to the inventory
//          component slot.
//
void AddSmallInventoryComponent( ENTITY *self )
{
  self->comps.IC = (INVENTORY_COMPONENT *)malloc( sizeof( SI ) );
  self->comps.IC->owner = self;
  self->comps.IC->COM_PROC = (void (*)( INVENTORY_COMPONENT *self, EM msg, int var1, int var2 ))SmallInventoryCOM_PROC;
  self->comps.IC->COM_PROC( self->comps.IC, EM_CREATE, 0, 0 );
}

//
// AddJumperLittleComponent
// Purpose: Adds an small little jumper component to an entity to the brain
//          component slot.
//
void AddJumperLittleComponent( ENTITY *self )
{
  self->comps.BC = (BRAIN_COMPONENT *)malloc( sizeof( BJL ) );
  self->comps.BC->owner = self;
  self->comps.BC->COM_PROC = (void (*)( BRAIN_COMPONENT *self, EM msg, int var1, int var2 ))JumperLittleCOM_PROC;
  self->comps.BC->COM_PROC( self->comps.BC, EM_CREATE, 0, 0 );
}

////////////////////////////////////////////////////////////////////////////

//
// RemoveGraphicsComponent
// Purpose: Removes any graphics component from the graphics
//          component slot.
// FIXME : I CAUSE MEMORY LEAKS HAHAHA
void RemoveGraphicsComponent( ENTITY *self )
{
  if(self->comps.POSC)
    free( self->comps.GC );
  self->comps.GC = NULL;
}

//
// RemovePositionComponent
// Purpose: Removes any position component from the position
//          component slot.
//
void RemovePositionComponent( ENTITY *self )
{
  if(self->comps.POSC)
    free( self->comps.POSC );
  self->comps.POSC = NULL;
}

//
// RemovePhysicsComponent
// Purpose: Removes any physics component from the physics
//          component slot.
//
void RemovePhysicsComponent( ENTITY *self )
{
  if(self->comps.PC)
    free( self->comps.PC );
  self->comps.PC = NULL;
}

//
// RemoveCollisionComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemoveCollisionComponent( ENTITY *self )
{
  if(self->comps.CC)
    free( self->comps.CC );
  self->comps.CC = NULL;
}

//
// RemovePlayerComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemovePlayerComponent( ENTITY *self )
{
  if(self->comps.PLAC)
    free( self->comps.PLAC );
  self->comps.PLAC = NULL;
}

//
// RemoveActionListComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemoveActionListComponent( ENTITY *self )
{
  if(self->comps.AL)
    free( self->comps.AL );
  self->comps.AL = NULL;
}

//
// RemoveHitPointsComponent
// Purpose: Removes any hitpoints component from the hitpoints
//          component slot.
//
void RemoveHitPointsComponent( ENTITY *self )
{
  if(self->comps.HP)
    free( self->comps.HP );
  self->comps.HP = NULL;
}

//
// RemoveInventoryComponent
// Purpose: Removes any hitpoints component from the hitpoints
//          component slot.
//
void RemoveInventoryComponent( ENTITY *self )
{
  if(self->comps.IC)
    free( self->comps.IC );
  self->comps.IC = NULL;
}

//
// RemoveBrainComponent
// Purpose: Removes any brain component from the brain
//          component slot.
//
void RemoveBrainComponent( ENTITY *self )
{
  if(self->comps.BC)
    free( self->comps.BC );
  self->comps.BC = NULL;
}

////////////////////////////////////////////////////////////////////////////

//
// HasAComponent
// Purpose: These functions are used to check to see if a specific
//          type of component exists within an object.
//
BOOL HasAPC( ENTITY *self )
{
  return (self->comps.PC) ? TRUE : FALSE;
}

BOOL HasAGC( ENTITY *self )
{
  return (self->comps.GC) ? TRUE : FALSE;
}

BOOL HasAPOSC( ENTITY *self )
{
  return (self->comps.POSC) ? TRUE : FALSE;
}

BOOL HasACC( ENTITY *self )
{
  return (self->comps.CC) ? TRUE : FALSE;
}

BOOL HasAPLAC( ENTITY *self )
{
  return (self->comps.PLAC) ? TRUE : FALSE;
}

BOOL HasAAL( ENTITY *self )
{
  return (self->comps.AL) ? TRUE : FALSE;
}

BOOL HasAHP( ENTITY *self )
{
  return (self->comps.HP) ? TRUE : FALSE;
}

BOOL HasAIC( ENTITY *self )
{
  return (self->comps.IC) ? TRUE : FALSE;
}

BOOL HasABC( ENTITY *self )
{
  return (self->comps.BC) ? TRUE : FALSE;
}
