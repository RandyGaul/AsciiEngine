////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "ImageTable.h"
#include "Component.h"
#include "EntityCreatorTable.h" // Map entity creators to string IDs
#include "EntityManager.h"      // SendEntityMessage

static const char *CLASS_NAME = NULL;

void PointConstruct( ENTITY *self, float *x, float *y );
void PointInit     ( const char *className );
void PointUpdate   ( ENTITY *self, float *dt );
void PointDestroy  ( ENTITY *self );
ENTITY *PointCreate( int x, int y );

//
// PointEM_PROC
// Purpose; Processes entity messages.
//
void PointEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    PointConstruct( self, (float *)var1, (float *)var2 );
    break;
  case EM_DESTROY:
    PointDestroy( self );
    break;
  case EM_UPDATE:
    PointUpdate( self, (float *)var1 );
    break;
  case EM_CLSINIT:
    PointInit( (const char *)var1 );
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

    // Physics
  case EM_SETVEL:
    SendComEM( self->comps.PC, EM_SETVEL, var1, var2 );
    break;
  case EM_GETVEL:
    SendComEM( self->comps.PC, EM_GETVEL, var1, var2 );
    break;
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void PointConstruct( ENTITY *self, float *x, float *y )
{
  VECTOR2D vel = { 0 }, accel = { 0 }, pos = { 0 };
  AddPositionComponent( self, (int)x, (int)y );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  self->CLASS_NAME = CLASS_NAME;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void PointInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

//
// PointUpdate
// Purpose:
//
void PointUpdate   ( ENTITY *self, float *dt )
{
  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void PointDestroy  ( ENTITY *self )
{
  RemovePositionComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR POINT_CREATOR = {
  "POINT",
  PointCreate
};

//
// PointCreate
// Purpose: Creates a specific type of entity
//
ENTITY *PointCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  PointInit( POINT_CREATOR.ID ); // Register class name
  entity->EM_PROC = PointEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = POINT_CREATOR.ID;
  return entity;
}
