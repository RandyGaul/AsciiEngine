////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "ItemParticle.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ImageTable.h"
#include "Component.h"
#include "Random.h"

static const char *CLASS_NAME = NULL;

void ItemParticleConstruct( ENTITY *self, float *x, float *y );
void ItemParticleInit     ( const char *className );
void ItemParticleUpdate   ( ENTITY *self, float *dt );
void ItemParticleDraw     ( ENTITY *self );
void ItemParticleDestroy  ( ENTITY *self );
ENTITY *ItemParticleCreate( int x, int y );

//
// ItemParticleEM_PROC
// Purpose; Processes entity messages.
//
void ItemParticleEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    ItemParticleConstruct( self, (float *)var1, (float *)var2 );
    break;
  case EM_DESTROY:
    ItemParticleDestroy( self );
    break;
  case EM_CLSINIT:
    ItemParticleInit( (const char *)var1 );
    break;
  case EM_DRAW:
    ItemParticleDraw( self );
    break;
  case EM_UPDATE:
    ItemParticleUpdate( self, (float *)var1 );
    break;
  case EM_INACTIVE:
    EntityInactive( self );
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

    // ACTIONLIST
  case EM_ALADDACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (ALT)var1, var2 );
    break;
  case EM_ALREMACT:
    SendComEM( self->comps.AL, EM_ALADDACT, (AL_NODE *)var1, 0 );
    break;
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void ItemParticleConstruct( ENTITY *self, float *x, float *y )
{
  VECTOR2D vel = {
    (float)RandomInt( -ITEM_PARTICLE_VELOCITY_RANGE, ITEM_PARTICLE_VELOCITY_RANGE ),
    (float)RandomInt( -ITEM_PARTICLE_VELOCITY_RANGE, ITEM_PARTICLE_VELOCITY_RANGE ) },
    accel = { 0 };
  ALD ALdata = { 0 };

  // Add various components
  AddSpriteComponent( self, FIND_DATA( P_IMAGE, IMAGE_TABLE, "ItemParticle.AEArt" ), ENABLE_CAM );
  AddPositionComponent( self, (int)x, (int)y );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  AddActionListComponent( self );

  // Set the properties flag of this object
  self->properties = 0;

  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 1;
  ALdata.flag |= BLOCKING;
  ALdata.ID = ALT_PAUSE;
  ALdata.timerEnd = ITEM_PARTICLE_DELAY;
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
void ItemParticleInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Update function for this entity type
void ItemParticleUpdate   ( ENTITY *self, float *dt )
{
  // Update Graphics
  SendComEM( self->comps.GC, EM_UPDATE, dt, 0 );

  // Apply Gravity to Physics vel data member
  if(self->properties & GRAVITYME)
    SendComEM( self->comps.PC, EM_GRAVITY, dt, 0 );

  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );

  // Update the actionList (must do last)
  SendComEM( self->comps.AL, EM_UPDATE, dt, 0 );
}

// Draw function for this entity type
void ItemParticleDraw     ( ENTITY *self )
{
  float x, y;
  SendComEM( self->comps.POSC, EM_GETPOS, &x, &y );
  SendComEM( self->comps.GC, EM_DRAW, x, y );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void ItemParticleDestroy  ( ENTITY *self )
{
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
  RemovePhysicsComponent( self );
  SendComEM( self->comps.AL, EM_DESTROY, 0, 0 );
  RemoveActionListComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR ITEM_PARTICLE_CREATOR = {
  "ITEM_PARTICLE",
  ItemParticleCreate
};

//
// ItemParticle
// Purpose: Creates a specific type of entity
//
ENTITY *ItemParticleCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  ItemParticleInit( ITEM_PARTICLE_CREATOR.ID ); // Register class name
  entity->EM_PROC = ItemParticleEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = ITEM_PARTICLE_CREATOR.ID;
  return entity;
}
