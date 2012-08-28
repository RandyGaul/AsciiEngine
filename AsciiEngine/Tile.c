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

void TileConstruct( ENTITY *self, float *x, float *y );
void TileInit     ( const char *className );
void TileDraw     ( ENTITY *self );
void TileDestroy  ( ENTITY *self );
ENTITY *TileCreate( int x, int y );

//
// TileEM_PROC
// Purpose; Processes entity messages.
//
void TileEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    TileConstruct( self, (float *)var1, (float *)var2 );
    break;
  case EM_DESTROY:
    TileDestroy( self );
    break;
  case EM_CLSINIT:
    TileInit( (const char *)var1 );
    break;
  case EM_DRAW:
    TileDraw( self );
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
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void TileConstruct( ENTITY *self, float *x, float *y )
{
  float width = 1.f, height = 1.f;
  AddSpriteComponent( self,  FIND_DATA( P_IMAGE, IMAGE_TABLE, "Tile.AEArt" ), ENABLE_CAM );
  AddPositionComponent( self, (int)x, (int)y );
  AddSquareComponent( self, (int)&width, (int)&height );
  self->properties |= DRAWME;
  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 9;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void TileInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Draw function for this entity type
void TileDraw     ( ENTITY *self )
{
  if(self->properties & DRAWME)
    SendComEM( self->comps.GC, EM_DRAW, 0, 0 );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void TileDestroy  ( ENTITY *self )
{
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR TILE_CREATOR = {
  "TILE",
  TileCreate
};

//
// TileCreate
// Purpose: Creates a specific type of entity
//
ENTITY *TileCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  TileInit( TILE_CREATOR.ID ); // Register class name
  entity->EM_PROC = TileEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = TILE_CREATOR.ID;
  return entity;
}
