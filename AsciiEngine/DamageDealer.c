////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Component.h"
#include "ImageTable.h"
#include "DamageDealer.h"
#include "EntityManager.h" // SendEntityMessage
#include "ImageTable.h" // FindImage

static const char *CLASS_NAME = NULL;

void DamageDealerConstruct( ENTITY *self, DDD *data, IMAGE *image );
void DamageDealerInit     ( const char *className );
void DamageDealerDraw( ENTITY *self );
void DamageDealerUpdate   ( ENTITY *self, float *dt );
void DamageDealerDestroy  ( ENTITY *self );
ENTITY *DamageDealerCreate( int var1, int var2 );

//
// DamageDealerEM_PROC
// Purpose; Processes entity messages.
//
void DamageDealerEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CREATE:
    DamageDealerConstruct( self, (DDD *)var1, (IMAGE *)var2 );
    break;
  case EM_DESTROY:
    DamageDealerDestroy( self );
    break;
  case EM_CLSINIT:
    DamageDealerInit( (const char *)var1 );
    break;
  case EM_UPDATE:
    DamageDealerUpdate( self, (float *)var1 );
    break;
  case EM_DRAW:
    DamageDealerDraw( self );
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
    SendComEM( self->comps.AL, EM_ALADDACT, (ALD *)var1, 0 );
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
void DamageDealerConstruct( ENTITY *self, DDD *data, IMAGE *image )
{
  VECTOR2D accel = { 0 };
  ALD ALdata = { 0 };

  // Add various components
  AddPositionComponent( self, (int)&data->pos.x_, (int)&data->pos.y_ );
  if(image)
  {
    AddSpriteComponent( self, image, TRUE );
    self->properties |= DRAWME;
  }
  AddPhysicsComponent( self, (int)&data->vel, (int)&accel );
  AddSquareComponent( self, (int)&data->WH.x_, (int)&data->WH.y_ );
  AddActionListComponent( self );

  // Set the properties flag of this object
  self->properties |= data->properties;
  self->properties |= DONT_COLLIDE_WITH_ME;

  // Initialize any components or other things
  self->CLASS_NAME = CLASS_NAME;
  self->zOrder = 0;
  self->data = data->damage;
  ALdata.flag |= BLOCKING;
  ALdata.ID = ALT_PAUSE;
  ALdata.timerEnd = data->delay;
  ActionListAddAction( (AL *)self->comps.AL, &ALdata );
  ALdata.ID = ALT_SET_PROPERTIES;
  ALdata.var1 |= DAMAGE_DEALER;
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
void DamageDealerInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

void DamageDealerDraw( ENTITY *self )
{
  if(self->properties & DRAWME)
  {
    SendComEM( self->comps.GC, EM_DRAW, 0, 0 );
  }
}

// Update function for this entity type
void DamageDealerUpdate   ( ENTITY *self, float *dt )
{
  // Apply Gravity to Physics vel data member
  if(self->properties & GRAVITYME)
    SendComEM( self->comps.PC, EM_GRAVITY, dt, 0 );

  // Update collision
  SendComEM( self->comps.CC, EM_UPDATE, dt, 0 );

  // Update physics
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );

  // Update the actionList (must do last)
  SendComEM( self->comps.AL, EM_UPDATE, dt, 0 );
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void DamageDealerDestroy  ( ENTITY *self )
{
  RemovePositionComponent( self );
  RemovePhysicsComponent( self );
  RemoveCollisionComponent( self );
  SendComEM( self->comps.AL, EM_DESTROY, 0, 0 );
  RemoveActionListComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR DAMAGE_DEALER_CREATOR = {
  "DAMAGE_DEALER",
  DamageDealerCreate
};

//
// DamageDealer
// Purpose: Creates a specific type of entity
//
ENTITY *DamageDealerCreate( int var1, int var2 )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  DamageDealerInit( DAMAGE_DEALER_CREATOR.ID ); // Register class name
  entity->EM_PROC = DamageDealerEM_PROC;
  SendEntityMessage( entity, EM_CREATE, var1, var2 );
  CLASS_NAME = DAMAGE_DEALER_CREATOR.ID;
  return entity;
}
