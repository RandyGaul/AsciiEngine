////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "ImageTable.h"
#include "Component.h"
#include "EntityCreatorTable.h" // Map entity creators to string IDs
#include "EntityManager.h"      // SendEntityMessage
#include "Animation.h"
#include "Loci.h"
#include "Player.h" // PLAYER_ATTACK_SPEED_SECONDS
#include "SmallInventory.h"
#include "Camera.h"

static const char *CLASS_NAME = NULL;

void HeroConstruct( ENTITY *self, int hp );
void HeroInit     ( const char *className );
void HeroSet      ( ENTITY *self );
void HeroUpdate   ( ENTITY *self, float *dt );
void HeroDraw     ( ENTITY *self );
void HeroDestroy  ( ENTITY *self );
ENTITY *HeroCreate( int var1, int var2 );

//
// HeroEM_PROC
// Purpose; Processes entity messages.
//
void HeroEM_PROC( ENTITY *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // General
  case EM_CREATE:
    HeroConstruct( self, var1 );
    break;
  case EM_DESTROY:
    HeroDestroy( self );
    break;
  case EM_CLSINIT:
    HeroInit( (const char *)var1 );
    break;
  case EM_UPDATE:
    HeroUpdate( self, (float *)var1 );
    break;
  case EM_DRAW:
    HeroDraw( self );
    break;
  case EM_INACTIVE:
    EntityInactive( self );
    break;
    
    // Position
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

    // PLAYERCOMPONENT
  case EM_SETJUMP:
    SendComEM( self->comps.PLAC, EM_SETJUMP, (BOOL *)var1, 0 );
    break;
  case EM_GETJUMP:
    SendComEM( self->comps.PLAC, EM_GETJUMP, (BOOL *)var1, 0 );
    break;
  case EM_GETINVEC:
    SendComEM( self->comps.PLAC, EM_GETINVEC, (VECTOR2D *)var1, 0 );
    break;
  case EM_SETINVEC:
    SendComEM( self->comps.PLAC, EM_SETINVEC, (VECTOR2D *)var1, 0 );
    break;
  case EM_SETJUMPN:
    SendComEM( self->comps.PLAC, EM_SETJUMPN, var1, 0 );
    break;
  case EM_GETJUMPN:
    SendComEM( self->comps.PLAC, EM_GETJUMPN, (BOOL *)var1, 0 );
    break;
  case EM_GETHTBTM:
    SendComEM( self->comps.PLAC, EM_GETHTBTM, (BOOL *)var1, 0 );
    break;
  case EM_SETHTBTM:
    SendComEM( self->comps.PLAC, EM_SETHTBTM, var1, 0 );
    break;

    // LOCI
  case EM_GETLOCUS:
    SendComEM( self->comps.GC, EM_GETLOCUS, (const char *)var1, (LOCUS *)var2 );
    break;
  case EM_CLDSETIM:
    SendComEM( self->comps.GC, EM_CLDSETIM, (const char *)var1, (IMAGE *)var2 );
    break;
  case EM_CLDSETAN:
    SendComEM( self->comps.GC, EM_CLDSETAN, (const char *)var1, (ANIMATION *)var2 );
    break;
  case EM_INSLOCUS:
    SendComEM( self->comps.GC, EM_INSLOCUS, (LOCUS *)var1, 0 );
    break;
  case EM_CLDFREAN:
    SendComEM( self->comps.GC, EM_CLDFREAN, (const char *)var1, 0 );
    break;
  case EM_CLDTGLLC:
    SendComEM( self->comps.GC, EM_CLDTGLLC, (const char *)var1, 0 );
    break;
  case EM_CLDSETLC:
    SendComEM( self->comps.GC, EM_CLDSETLC, (const char *)var1, (BOOL *)var2 );
    break;
  case EM_CLDOFFLC:
    SendComEM( self->comps.GC, EM_CLDOFFLC, (const char *)var1, 0 );
    break;
  case EM_CLDONLC:
    SendComEM( self->comps.GC, EM_CLDONLC, (const char *)var1, 0 );
    break;

    // HITPOINTS
  case EM_GETHP:
    SendComEM( self->comps.HP, EM_GETHP, (int *)var1, 0 );
    break;
  case EM_SETHP:
    SendComEM( self->comps.HP, EM_SETHP, var1, 0 );
    break;
  case EM_DAMAGEHP:
    SendComEM( self->comps.HP, EM_DAMAGEHP, var1, 0 );
    break;
  case EM_HEALHP:
    SendComEM( self->comps.HP, EM_HEALHP, var1, 0 );
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
  case EM_GETINVSZ:
    SendComEM( self->comps.IC, EM_GETINVSZ, (int *)var1, 0 );
    break;
  case EM_INVEJECT:
    SendComEM( self->comps.IC, EM_INVEJECT, 0, 0 );
    break;
  case EM_INVGDRAW:
     SendComEM( self->comps.IC, EM_INVGDRAW, (BOOL *)var1, 0 );
    break;
  case EM_INVSDRAW:
     SendComEM( self->comps.IC, EM_INVSDRAW, var1, 0 );
    break;
  case EM_INVTDRAW:
     SendComEM( self->comps.IC, EM_INVTDRAW, 0, 0 );
    break;
  }
}

// Constructor for this entity type
// Notes: Do not allocate space for the entity itself! This is handled
//        by the entity factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this entity.
void HeroConstruct( ENTITY *self, int hp )
{
  VECTOR2D vel = { 0.f, 0.f }, accel = { 0 }, pos = { 5.0f, 20.0f }, widthHeight = { 4.f, 9.f };

  GlobalCamInit( 0, 0, self );

  // Add cloud component
  AddCloudComponent( self, 101, ENABLE_CAM );
  
  // Insert loci into cloud
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateAnimationLocus( "RUNNING_RIGHT", 0.f, 0.f, 0, .15f, "ManRun1.AEArt",
    "ManRun2.AEArt",
    "ManRun3.AEArt",
    "ManRun4.AEArt",
    "ManRun5.AEArt",
    "ManRun6.AEArt", 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateImageLocus( "JUMPING_RIGHT", 0.f, 0.f, FIND_DATA( P_IMAGE, IMAGE_TABLE, "ManJump.AEArt" ), 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateImageLocus( "JUMPING_LEFT", 2.f, 0.f, FIND_DATA( P_IMAGE, IMAGE_TABLE, "ManJumpFlipX.AEArt" ), 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateAnimationLocus( "RUNNING_LEFT", -2.f, 0.f, 0, .15f, "ManRun1FlipX.AEArt",
    "ManRun2FlipX.AEArt",
    "ManRun3FlipX.AEArt",
    "ManRun4FlipX.AEArt",
    "ManRun5FlipX.AEArt",
    "ManRun6FlipX.AEArt", 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateAnimationLocus( "ATTACK_1_RIGHT", -3.f, 0.f, 0, PLAYER_ATTACK_SPEED_SECONDS / 7.f, "ManSwing1.AEArt",
    "ManSwing2.AEArt",
    "ManSwing3.AEArt",
    "ManSwing4.AEArt",
    "ManSwing5.AEArt",
    "ManSwing6.AEArt",
    "ManSwing7.AEArt", 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateAnimationLocus( "ATTACK_1_LEFT", -2.f, 0.f, 0, PLAYER_ATTACK_SPEED_SECONDS / 7.f, "ManSwing1FlipX.AEArt",
    "ManSwing2FlipX.AEArt",
    "ManSwing3FlipX.AEArt",
    "ManSwing4FlipX.AEArt",
    "ManSwing5FlipX.AEArt",
    "ManSwing6FlipX.AEArt",
    "ManSwing7FlipX.AEArt", 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS, 
    (int)AllocateImageLocus( "IDLE_RIGHT", 1.f, 0.f, FIND_DATA( P_IMAGE, IMAGE_TABLE, "WeaponMan.AEArt" ), 0 ), 0 );
  SendComEM( self->comps.GC, EM_INSLOCUS,
    (int)AllocateImageLocus( "IDLE_LEFT", 1.f, 0.f, FIND_DATA( P_IMAGE, IMAGE_TABLE, "WeaponManFlipX.AEArt" ), 0 ), 0 );

  // Set the properties flag of this object
  self->properties = PLAYER | DRAWME | GRAVITYME;

  // Add in additional components
  AddPositionComponent( self, (int)&pos.x_, (int)&pos.y_ );
  AddPhysicsComponent( self, (int)&vel, (int)&accel );
  AddSquareComponent( self, (int)&widthHeight.x_, (int)&widthHeight.y_ );
  AddPlaCComponent( self );
  AddHitPointsComponent( self, hp );
  AddSmallInventoryComponent( self );

  // Any other required initializations
  self->CLASS_NAME = CLASS_NAME;
}

// Default initializer for this entity type
// Notes: This function calls the Set function for this entity type.
//        The purpose of the set function is to set the values of the
//        self entity to those of the parameters. However the Init
//        function of an entity acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void HeroInit     ( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1, className );
}

// Initializer function for this entity type
// Notes: This function is the one to be called if you wish to at any
//        time initialize the entity with customized data. If you desire
//        a default initialization, call the Init function instead.
void HeroSet      ( ENTITY *self )
{
}

// Update function for this entity type
void HeroUpdate   ( ENTITY *self, float *dt )
{
  // Update the various components
  // Order of update is rather important
  SendComEM( self->comps.IC, EM_UPDATE, 0, 0 );
  SendComEM( self->comps.GC, EM_UPDATE, dt, 0 );
  if(self->properties & GRAVITYME)
    SendComEM( self->comps.PC, EM_GRAVITY, dt, 0 );
  SendComEM( self->comps.PLAC, EM_UPDATE, dt, 0 );
  SendComEM( self->comps.CC, EM_UPDATE, dt, 0 );
  SendComEM( self->comps.PC, EM_UPDATE, dt, 0 );
}

// Draw function for this entity type
void HeroDraw     ( ENTITY *self )
{
  if(self->properties & DRAWME)
  {
    SendComEM( self->comps.GC, EM_DRAW, 0, 0 );
    SendComEM( self->comps.IC, EM_DRAW, 0, 0 );
  }
}

// Destructor for this entity type
// Notes: Only free things in this function that were allocated in the
//        construtor! The entity factory actually handles deallocation
//        of the entity itself.
void HeroDestroy  ( ENTITY *self )
{
  RemoveGraphicsComponent( self );
  RemovePositionComponent( self );
  RemovePhysicsComponent( self );
  RemovePlayerComponent( self );
  RemoveCollisionComponent( self );
  RemoveHitPointsComponent( self );
}

// Creator for this entity, assign a string ID and a creator function
// For use with the EntityFactory -- allows simple dynamicly maintained
// method for creation of entitys without necessity to maintain explicit
// code
ENTITY_CREATOR HERO_CREATOR = {
  "HERO",
  (ENTITY *(*)( int var1, int var2 ))HeroCreate
};

//
// HeroCreate
// Purpose: Creates a specific type of entity
//          var1 is zOrder; var2 is starting HP
//
ENTITY *HeroCreate( int var1, int var2 )
{
  ENTITY *entity = (ENTITY *)malloc( sizeof( ENTITY ) );
  memset( entity, 0, sizeof( ENTITY ) );
  HeroInit( HERO_CREATOR.ID ); // Register class name
  entity->EM_PROC = HeroEM_PROC;
  SendEntityMessage( entity, EM_CREATE, var2, 0 );
  CLASS_NAME = HERO_CREATOR.ID;
  entity->zOrder = var1;
  return entity;
}
