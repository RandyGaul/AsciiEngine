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

void StaticBGConstruct( ENTITY *self, float *x, float *y );
void StaticBGInit     ( const char *className );
void StaticBGSet      ( ENTITY *self, va_list args );
void StaticBGUpdate   ( ENTITY *self, float *dt );
void StaticBGDraw     ( ENTITY *self );
void StaticBGDestroy  ( ENTITY *self );
ENTITY *StaticBGCreate( int x, int y );

//
// StaticBGEM_PROC
// Purpose; Processes entity messages.
//
void StaticBGEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    StaticBGConstruct( self, (float *)var1, (float *)var2 );
    break;
  case EM_DESTROY:
    StaticBGDestroy( self );
    break;
  case EM_CLSINIT:
    StaticBGInit( (const char *)var1 );
    break;
  case EM_DRAW:
    StaticBGDraw( self );
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
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void StaticBGConstruct( ENTITY *self, float *x, float *y )
{
  AddSpriteComponent( self, FIND_DATA( P_IMAGE, IMAGE_TABLE, "CloudBG.AEArt" ), DISABLE_CAM );
  AddPositionComponent( self, (int)x, (int)y );
  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 20;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void StaticBGInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Draw function for this entity type
void StaticBGDraw     ( ENTITY *self )
{
  float x, y;
  SendComEM( self->comps.POSC, EM_GETPOS, &x, &y );
  SendComEM( self->comps.GC, EM_DRAW, x, y );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void StaticBGDestroy  ( ENTITY *self )
{
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR STATICBG_CREATOR = {
  "STATICBG",
  StaticBGCreate
};

//
// StaticBG
// Purpose: Creates a specific type of entity
//
ENTITY *StaticBGCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  StaticBGInit( STATICBG_CREATOR.ID ); // Register class name
  entity->EM_PROC = StaticBGEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = STATICBG_CREATOR.ID;
  return entity;
}
