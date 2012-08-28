////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Item.h"
#include "ImageTable.h"
#include "Component.h"
#include "EntityCreatorTable.h" // Map entity creators to string IDs
#include "EntityManager.h"      // SendEntityMessage
#include "Random.h"

static const char *CLASS_NAME = NULL;

void ItemConstruct( ENTITY *self, VECTOR2D *pos, ITEM_ID id );
void ItemInit     ( const char *className );
void ItemSet      ( ENTITY *self, va_list args );
void ItemUpdate   ( ENTITY *self, float *dt );
void ItemDraw     ( ENTITY *self );
void ItemDestroy  ( ENTITY *self );
ENTITY *ItemCreate( int x, int y );

//
// ItemEM_PROC
// Purpose; Processes entity messages.
//
void ItemEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    ItemConstruct( self, (VECTOR2D *)var1, (ITEM_ID)var2 );
    break;
  case EM_DESTROY:
    ItemDestroy( self );
    break;
  case EM_CLSINIT:
    ItemInit( (const char *)var1 );
    break;
  case EM_DRAW:
    ItemDraw( self );
    break;
  case EM_UPDATE:
    ItemUpdate( self, (float *)var1 );
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
void ItemConstruct( ENTITY *self, VECTOR2D *pos, ITEM_ID id )
{
  VECTOR2D vel = { (float)RandomInt( -5, 5 ), -(float)RandomInt( 10, 15 ) }, accel = { 0 }, widthHeight = { 1.f, 1.f };

  // Add various components
  AddSpriteComponent( self, ItemIDToImage( id ), ENABLE_CAM );
  AddPositionComponent( self, (int)&pos->x_, (int)&pos->y_ );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  AddSquareComponent( self, (int)&widthHeight.x_, (int)&widthHeight.y_ );

  // Set the properties flag of this object
  self->properties = GRAVITYME | PICK_ME_UP_ITEM | DONT_COLLIDE_WITH_ME | DRAWME;

  // Set up all other initializations
  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 1;
  self->data = id;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void ItemInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Update function for this entity type
void ItemUpdate   ( ENTITY *self, float *dt )
{
  // Update Graphics
  SendComEM( self->comps.GC, EM_UPDATE, dt, 0 );

  // Apply Gravity to Physics vel data member
  if(self->properties & GRAVITYME)
    SendComEM( self->comps.PC, EM_GRAVITY, dt, 0 );

  // Update collision
  SendComEM( self->comps.CC, EM_UPDATE, dt, 0 );

  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );
}

// Draw function for this entity type
void ItemDraw     ( ENTITY *self )
{
  float x, y;
  SendComEM( self->comps.POSC, EM_GETPOS, &x, &y );
  SendComEM( self->comps.GC, EM_DRAW, x, y );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void ItemDestroy  ( ENTITY *self )
{
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
  RemovePhysicsComponent( self );
  RemoveCollisionComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR ITEM_CREATOR = {
  "ITEM",
  ItemCreate
};

//
// Item
// Purpose: Creates a specific type of entity
//
ENTITY *ItemCreate( int x, int y )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  ItemInit( ITEM_CREATOR.ID ); // Register class name
  entity->EM_PROC = ItemEM_PROC;
  SendEntityMessage( entity, EM_CREATE, x, y );
  CLASS_NAME = ITEM_CREATOR.ID;
  return entity;
}

//
// ItemIDToImage
// Purpose: Maps item id's to image pointers.
//
IMAGE *ItemIDToImage( ITEM_ID id )
{
  return FIND_DATA( P_IMAGE, IMAGE_TABLE, ItemIDToString( id ) );
}

//
// ItemIDToImage
// Purpose: Maps item id's to string identifiers.
//
const char *ItemIDToString( ITEM_ID id )
{
  switch(id)
  {
  case TestItem1:
    return "BlueSquare.AEArt";
  default:
    return "WhiteSquare.AEArt";
  }
}
