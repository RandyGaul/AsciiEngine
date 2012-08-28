////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "ImageTable.h"
#include "Component.h"
#include "EntityCreatorTable.h" // Map entity creators to string IDs
#include "EntityManager.h"      // SendEntityMessage
#include "Random.h"

static const char *CLASS_NAME = NULL;

void DamageTextConstruct( ENTITY *self, ENTITY *spawnAtMe, int damage );
void DamageTextInit     ( const char *className );
void DamageTextDraw     ( ENTITY *self );
void DamageTextUpdate( ENTITY *self, float *var1 );
void DamageTextDestroy  ( ENTITY *self );
ENTITY *DamageTextCreate( int x, int y );

//
// DamageTextEM_PROC
// Purpose; Processes entity messages.
//
void DamageTextEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    DamageTextConstruct( self, (ENTITY *)var1, var2 );
    break;
  case EM_DESTROY:
    DamageTextDestroy( self );
    break;
  case EM_CLSINIT:
    DamageTextInit( (const char *)var1 );
    break;
  case EM_UPDATE:
    DamageTextUpdate( self, (float *)var1 );
    break;
  case EM_DRAW:
    DamageTextDraw( self );
    break;
  case EM_INACTIVE:
    EntityInactive( self );
    break;
    
    // POSITION
  case EM_SETPOS:
    SendComEM( self->comps.POSC, EM_SETPOS, var1, var2 );
    break;
  case EM_GETPOS:
    SendComEM( self->comps.POSC, EM_GETPOS, var1, var2 );
    break;

    // ACTIONLIST
  case EM_ALADDACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (ALT)var1, var2 );
    break;
  case EM_ALREMACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (AL_NODE *)var1, 0 );
    break;
    
    // Physics
  case EM_SETVEL:
    SendComEM( self->comps.PC, EM_SETVEL, var1, var2 );
    break;
  case EM_GETVEL:
    SendComEM( self->comps.PC, EM_GETVEL, var1, var2 );
    break;
  case EM_GRAVITY:
    SendComEM( self->comps.PC, EM_GRAVITY, var1, 0 );
    break;
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void DamageTextConstruct( ENTITY *self, ENTITY *spawnAtMe, int damage )
{
  VECTOR2D vel = { 0, DAMAGE_TEXT_FLOAT_VEL }, accel = { 0 }, pos = { 0 };
  ALD ALdata = { 0 };

  // Initialize data
  SendEntityMessage( spawnAtMe, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  pos.x_ -= (float)RandomInt( -1, 1 );
  pos.y_ -= (float)RandomInt( 3, 5 );

  // Add necessary components
  AddPositionComponent( self, (int)&pos.x_, (int)&pos.y_ );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  AddActionListComponent( self );

  // Additional properties and initialization
  self->properties |= DRAWME;
  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 0;
  self->data = damage;
  ALdata.flag |= BLOCKING;
  ALdata.ID = ALT_PAUSE;
  ALdata.timerEnd = 1.f;
  ActionListAddAction( (AL *)self->comps.AL, &ALdata );
  ALdata.ID = ALT_DESTROY;
  ActionListAddAction( (AL *)self->comps.AL, &ALdata );
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void DamageTextInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

//
// DamageTextUpdate
// Purpose: Updates the floating text and makes it dissappear.
//
void DamageTextUpdate( ENTITY *self, float *dt )
{
  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );

  // Update the actionList (must do last)
  SendComEM( self->comps.AL, EM_UPDATE, dt, 0 );
}

// Draw function for this entity type
void DamageTextDraw     ( ENTITY *self )
{
  VECTOR2D pos = { 0 };
  char string[100] = { 0 };
  int damage = self->data;
  inttostr( damage, string );
  SendEntityMessage( self, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  if(self->properties & DRAWME)
    WriteStringToScreen( string, FloatToInt( pos.x_ ), FloatToInt( pos.y_ ) );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void DamageTextDestroy  ( ENTITY *self )
{
  RemovePositionComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR DAMAGE_TEXT_CREATOR = {
  "DAMAGE_TEXT",
  DamageTextCreate
};

//
// DamageTextCreate
// Purpose: Creates a specific type of entity
//
ENTITY *DamageTextCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  DamageTextInit( DAMAGE_TEXT_CREATOR.ID ); // Register class name
  entity->EM_PROC = DamageTextEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = DAMAGE_TEXT_CREATOR.ID;
  return entity;
}
