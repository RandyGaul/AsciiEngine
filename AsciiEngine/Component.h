////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include <stdarg.h>
#include "Graphics.h"

// Include the various component types
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "ActionListComponent.h"
#include "InventoryComponent.h"
#include "Animation.h"
#include "ActionList.h"
#include "Hitpoints.h"
#include "BrainComponent.h"

// Sends an entity's component an entity message
#define SendComEM( Com, EM, var1, var2 ) \
  if(Com) \
    Com->COM_PROC( Com, EM, (int)var1, (int)var2 )

struct _ENTITY;

//
// Collection of pointers to various types of components. Every entity
// contains this structure of pointers, and when one is null that entity
// does not contain that specific type of component.
//
typedef struct _ENTITY_COMPONENTS
{
  GRAPHICS_COMPONENT *GC;     // Graphics component
  POSITION_COMPONENT *POSC;   // Position component
  PHYSICS_COMPONENT *PC;      // Physics component
  COLLISION_COMPONENT *CC;    // Collision component
  PLAYER_COMPONENT *PLAC;     // Player component
  ACTIONLIST_COMPONENT *AL;   // ActionList component
  HITPOINTS_COMPONENT *HP;    // Hitpoints component
  INVENTORY_COMPONENT *IC;    // Inventory component
  BRAIN_COMPONENT *BC;        // Brain component
} EN_COMPS;

//
// AddSpriteComponent
// Purpose: Adds a sprite component to an entity to the graphics
//          component slot.
//
void AddSpriteComponent( struct _ENTITY *self, IMAGE *image, BOOL enableCam );

//
// AddAnimationComponent
// Purpose: Adds a animation component to an entity to the graphics
//          component slot.
//
void AddAnimationComponent( struct _ENTITY *self, ANIMATION *animation, BOOL enableCam );

//
// AddCloudComponent
// Purpose: Adds a cloud component to an entity to the graphics
//          component slot.
//
void AddCloudComponent( struct _ENTITY *self, int var1, BOOL enableCam );

//
// AddPositionComponent
// Purpose: Adds a position component to an entity to the position
//          component slot.
//
void AddPositionComponent( struct _ENTITY *self, int var1, int var2 );

//
// AddPhysicsComponent
// Purpose: Adds a position component to an entity to the position
//          component slot.
//
void AddPhysicsComponent( struct _ENTITY *self, int var1, int var2 );

//
// AddSquareComponent
// Purpose: Adds a collision component to an entity to the collision
//          component slot.
//
void AddSquareComponent( struct _ENTITY *self, int var1, int var2 );

//
// AddPlaCComponent
// Purpose: Adds a player component to an entity to the player
//          component slot.
//
void AddPlaCComponent( struct _ENTITY *self );

//
// AddActionListComponent
// Purpose: Adds an actionList component to an entity to the actionList
//          component slot.
//
void AddActionListComponent( struct _ENTITY *self );

//
// AddHitPointsComponent
// Purpose: Adds an hitpoints component to an entity to the hitpoints
//          component slot.
//
void AddHitPointsComponent( struct _ENTITY *self, int var1 );

//
// AddSmallInventoryComponent
// Purpose: Adds an small inventory component to an entity to the inventory
//          component slot.
//
void AddSmallInventoryComponent( struct _ENTITY *self );

//
// AddJumperLittleComponent
// Purpose: Adds an jumperlittle component to an entity to the brain
//          component slot.
//
void AddJumperLittleComponent( struct _ENTITY *self );

/////////////////////////////////////////////////////////////////////////

//
// RemoveGraphicsComponent
// Purpose: Removes any graphics component from the graphics
//          component slot.
//
void RemoveGraphicsComponent( struct _ENTITY *self );

//
// RemovePositionComponent
// Purpose: Removes any position component from the position
//          component slot.
//
void RemovePositionComponent( struct _ENTITY *self );

//
// RemovePhysicsComponent
// Purpose: Removes any physics component from the physics
//          component slot.
//
void RemovePhysicsComponent( struct _ENTITY *self );

//
// RemovePlayerComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemovePlayerComponent( struct _ENTITY *self );


//
// RemoveCollisionComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemoveCollisionComponent( struct _ENTITY *self );

//
// RemoveActionListComponent
// Purpose: Removes any collision component from the collision
//          component slot.
//
void RemoveActionListComponent( struct _ENTITY *self );

//
// RemoveHitPointsComponent
// Purpose: Removes any hitpoints component from the hitpoints
//          component slot.
//
void RemoveHitPointsComponent( struct _ENTITY *self );

//
// RemoveInventoryComponent
// Purpose: Removes any hitpoints component from the hitpoints
//          component slot.
//
void RemoveInventoryComponent( struct _ENTITY *self );

//
// RemoveBrainComponent
// Purpose: Removes any brain component from the brain component slot.
//
void RemoveBrainComponent( struct _ENTITY *self );

////////////////////////////////////////////////////////////////////////////

//
// HasAComponent
// Purpose: These functions are used to check to see if a specific
//          type of component exists within an object.
//
BOOL HasAPC( struct _ENTITY *self );
BOOL HasAGC( struct _ENTITY *self );
BOOL HasAPOSC( struct _ENTITY *self );
BOOL HasACC( struct _ENTITY *self );
BOOL HasAPLAC( struct _ENTITY *self );
BOOL HasAAL( struct _ENTITY *self );
BOOL HasAHP( struct _ENTITY *self );
BOOL HasAIC( struct _ENTITY *self );
BOOL HasABC( struct _ENTITY *self );
