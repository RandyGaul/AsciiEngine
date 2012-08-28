////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/21/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "ImageTable.h"
#include "Component.h"
#include "EntityCreatorTable.h" // Map entity creators to string IDs
#include "EntityManager.h"      // SendEntityMessage
#include "EntityFactory.h"
#include "Item.h"

static const char *CLASS_NAME = NULL;

void SimpleEnemyConstruct( ENTITY *self, float *x, float *y );
void SimpleEnemyInit     ( const char *className );
void SimpleEnemyUpdate   ( ENTITY *self, float *dt );
void SimpleEnemyDraw     ( ENTITY *self );
void SimpleEnemyDestroy  ( ENTITY *self );
void SimpleEnemyInactive( ENTITY *self );
ENTITY *SimpleEnemyCreate( int x, int y );

//
// SimpleEnemyEM_PROC
// Purpose; Processes entity messages.
//
void SimpleEnemyEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    SimpleEnemyConstruct( self, (float *)var1, (float *)var2 );
    break;
  case EM_DESTROY:
    SimpleEnemyDestroy( self );
    break;
  case EM_CLSINIT:
    SimpleEnemyInit( (const char *)var1 );
    break;
  case EM_DRAW:
    SimpleEnemyDraw( self );
    break;
  case EM_UPDATE:
    SimpleEnemyUpdate( self, (float *)var1 );
    break;
  case EM_INACTIVE:
    SimpleEnemyInactive( self );
    break;
    
    // DATA ACCESS
  case EM_SETPOS:
    SendComEM( self->comps.POSC, EM_SETPOS, var1, var2 );
    break;
  case EM_GETPOS:
    SendComEM( self->comps.POSC, EM_GETPOS, var1, var2 );
    break;
    
    // Physics
  case EM_SETVEL:
    SendComEM( self->comps.PC, EM_SETVEL, var1, var2 );
    break;
  case EM_GETVEL:
    SendComEM( self->comps.PC, EM_GETVEL, var1, var2 );
    break;
  case EM_SETACCEL:
    SendComEM( self->comps.PC, EM_SETACCEL, var1, var2 );
    break;
  case EM_GETACCEL:
    SendComEM( self->comps.PC, EM_GETACCEL, var1, var2 );
    break;
  case EM_STEPXPOS:
    SendComEM( self->comps.PC, EM_STEPXPOS, var1, var2 );
    break;
  case EM_STEPYPOS:
    SendComEM( self->comps.PC, EM_STEPYPOS, var1, var2 );
    break;
  case EM_GRAVITY:
    SendComEM( self->comps.PC, EM_GRAVITY, var1, 0 );
    break;

    // COLLISION
  case EM_GETWH:
    SendComEM( self->comps.CC, EM_GETWH, var1, var2 );
    break;
  case EM_SETWH:
    SendComEM( self->comps.CC, EM_SETWH, var1, var2 );
    break;
  case EM_HITTEST:
    SendComEM( self->comps.CC, EM_HITTEST, var1, var2 );
    break;
  case EM_IHITYOU:
    SendComEM( self->comps.CC, EM_IHITYOU, var1, var2 );
    break;

    // ACTIONLIST
  case EM_ALADDACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (ALT)var1, var2 );
    break;
  case EM_ALREMACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (AL_NODE *)var1, 0 );
    break;

    // HITPOINTS
  case EM_DAMAGEHP:
    SendComEM( self->comps.HP, EM_DAMAGEHP, var1, 0 );
    break;

    // INVENTORY
  case EM_GETINV:
    SendComEM( self->comps.IC, EM_GETINV, (int *)var1, var2 );
    break;
  case EM_SETINV:
    SendComEM( self->comps.IC, EM_SETINV, (ITEM_ID)var1, var2 );
    break;
  case EM_INSINV:
    SendComEM( self->comps.IC, EM_INSINV, (ITEM_ID)var1, 0 );
    break;
  case EM_INVEJECT:
    SendComEM( self->comps.IC, EM_INVEJECT, 0, 0 );
    break;
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void SimpleEnemyConstruct( ENTITY *self, float *x, float *y )
{
  VECTOR2D vel = { 0.f, 0.f }, accel = { 0 }, widthHeight = { 5.f, 5.f };

  // Add various components
  AddSpriteComponent( self, FIND_DATA( P_IMAGE, IMAGE_TABLE, "SimpleEnemy.AEArt" ), ENABLE_CAM );
  AddPositionComponent( self, (int)x, (int)y );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  AddSquareComponent( self, (int)&widthHeight.x_, (int)&widthHeight.y_ );
  AddHitPointsComponent( self, 10 );
  AddSmallInventoryComponent( self );
  AddActionListComponent( self );
  AddJumperLittleComponent( self );

  // Set the properties flag of this object
  self->properties = ENEMIES | GRAVITYME | NO_PICKUP_ITEMS;
  SendComEM( self->comps.IC, EM_INSINV, TestItem1, 0 );

  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 1;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void SimpleEnemyInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Update function for this entity type
void SimpleEnemyUpdate   ( ENTITY *self, float *dt )
{
  // Update brain
  SendComEM( self->comps.BC, EM_UPDATE, dt, 0 );

  // Update the actionList (must do last)
  SendComEM( self->comps.AL, EM_UPDATE, dt, 0 );

  // Update Graphics
  SendComEM( self->comps.GC, EM_UPDATE, dt, 0 );

  // Apply Gravity to Physics vel data member
  if(self->properties & GRAVITYME)
    SendComEM( self->comps.PC, EM_GRAVITY, dt, 0 );

  // Update collision
  SendComEM( self->comps.CC, EM_UPDATE, dt, 0 );

  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );

  // Update hitpoints
  SendComEM( self->comps.HP, EM_UPDATE, dt, 0 );
}

// Draw function for this entity type
void SimpleEnemyDraw     ( ENTITY *self )
{
  float x, y;
  SendComEM( self->comps.POSC, EM_GETPOS, &x, &y );
  SendComEM( self->comps.GC, EM_DRAW, x, y );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void SimpleEnemyDestroy  ( ENTITY *self )
{
  RemoveBrainComponent( self );
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
  RemovePhysicsComponent( self );
  RemoveCollisionComponent( self );
  RemoveHitPointsComponent( self );
  SendComEM( self->comps.AL, EM_DESTROY, 0, 0 );
  RemoveActionListComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR SIMPLE_ENEMY_CREATOR = {
  "SIMPLE_ENEMY",
  SimpleEnemyCreate
};

//
// SimpleEnemy
// Purpose: Creates a specific type of entity
//
ENTITY *SimpleEnemyCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  SimpleEnemyInit( SIMPLE_ENEMY_CREATOR.ID ); // Register class name
  entity->EM_PROC = SimpleEnemyEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = SIMPLE_ENEMY_CREATOR.ID;
  return entity;
}

//
// SimpleEnemyInactive
// Purpose: Runs on inactive message.
//
void SimpleEnemyInactive( ENTITY *self )
{
  VECTOR2D pos = { 0 };
  SendEntityMessage( self, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  SendComEM( self->comps.IC, EM_INVEJECT, 0, 0 );
  self->inactive = TRUE;
}
