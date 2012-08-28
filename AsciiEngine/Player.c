////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/18/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Player.h"
#include "Physics.h"
#include "PositionComponent.h"
#include "EntityManager.h"
#include "Input.h"
#include "Camera.h"
#include "Math2D.h" // StaticRectToStaticRect
#include "DamageDealer.h" // DDD data packet
#include "EntityFactory.h" // CreateEntity
#include "ImageTable.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PlaCCOM_PROC( PLAC *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CLSINIT:
    PlaCInit( (const char *)var1 );
    break;
  case EM_CREATE:
    PlaCCreate( self );
    break;
  case EM_UPDATE:
    PlaCUpdate( self, (float *)var1 );
    break;

    // DATA ACCESS
  case EM_SETJUMP:
    PlaCSetCanJump( self, (BOOL *)var1 );
    break;
  case EM_GETJUMP:
    PlaCGetCanJump( self, (BOOL *)var1 );
    break;
  case EM_GETINVEC:
    PlaCGetInputVector( self, (VECTOR2D *)var1 );
    break;
  case EM_SETINVEC:
    PlaCSetInputVector( self, (VECTOR2D *)var1 );
    break;
  case EM_SETJUMPN:
    PlaCSetJumping( self, var1 );
    break;
  case EM_GETJUMPN:
    PlaCGetJumping( self, (BOOL *)var1 );
    break;
  case EM_GETHTBTM:
    PlaCGetHitBottom( self, (BOOL *)var1 );
    break;
  case EM_SETHTBTM:
    PlaCSetHitBottom( self, var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PlaCCreate( PLAC *self )
{
  VECTOR2D pos = { 0 };
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  self->base.CLASS_NAME = CLASS_NAME;
  self->canJump = TRUE;
  self->faceDir = TRUE;
  self->hitBottom = FALSE;
  self->jumping = FALSE;
  self->inputVector.x_ = 0;
  self->inputVector.y_ = 0;
  self->dt = 0;
  self->inventoryDT = 0;
  self->playerState = PLAYER_STATE_IDLE;
}

//
// ClassUpdate
// Purpose: This update function modifies the owner's current velocity
//          by the component's constants if specific input conditions are met
//
void PlaCUpdate( PLAC *self, float *dt )
{
  VECTOR2D inputVector = { 0 }, pos = { 0 };
  SendEntityMessage( self->base.owner, EM_GETINVEC, (int)&inputVector, 0 );
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );

  // Initiate jump if canJump currently
  if(IsKeyPressed( VK_UP ) && self->canJump && self->playerState != PLAYER_STATE_ATTACKING_1)
  {
    self->canJump = FALSE;
    inputVector.y_ = PLAYER_JUMP_HEIGHT;
    self->jumping = TRUE;
    SendEntityMessage( self->base.owner, EM_SETHTBTM, FALSE, 0 );
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );
  }

  // Enable jumping if hit a tile on bottom of player
  if(!self->jumping && !IsKeyPressed( VK_UP ) && self->canJump == FALSE)
  {
    inputVector.y_ = 0;
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );
    self->canJump = TRUE;
  }

  // Move left
  if(IsKeyPressed( VK_LEFT ) && self->playerState != PLAYER_STATE_ATTACKING_1)
  {
    inputVector.x_ = -LEFT_RIGHT_SPEED;
    self->playerState = PLAYER_STATE_MOVING;
    self->faceDir = FALSE;
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );
  }
  // Move right
  if(IsKeyPressed( VK_RIGHT ) && self->playerState != PLAYER_STATE_ATTACKING_1)
  {
    inputVector.x_ = LEFT_RIGHT_SPEED;
    self->playerState = PLAYER_STATE_MOVING;
    self->faceDir = TRUE;
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );
  }
  // Zero input vector x if left or right key not pressed
  else if(!IsKeyPressed( VK_RIGHT ) && !IsKeyPressed( VK_LEFT ))
  {
    inputVector.x_ = 0;
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );
  }

  // Space bar for attacking!
  if(IsKeyPressed( VK_SPACE ) && !self->jumping && self->playerState != PLAYER_STATE_ATTACKING_1)
  {
    DDD data = { 0 };
    data.damage = 10;
    data.WH.x_ = 1.f;
    data.WH.y_ = 1.f;
    data.delay = .30f;
    SendEntityMessage( self->base.owner, EM_GETPOS, (int)&data.pos.x_, (int)&data.pos.y_ );
    self->playerState = PLAYER_STATE_ATTACKING_1;
    inputVector.x_ = 0;
    SendEntityMessage( self->base.owner, EM_SETINVEC, (int)&inputVector, 0 );

    if(self->faceDir)
      data.pos.x_ += 4.f;
    else
      data.pos.x_ -= 5.f; 
    
    CreateEntity( "DAMAGE_DEALER", (int)&data, (int)FIND_DATA( P_IMAGE, IMAGE_TABLE, "TestDamage.AEArt" ) );
  }

  if(IsKeyPressed( VK_I ) && self->inventoryDT == 0)
  {
    self->inventoryDT += *dt;
    SendEntityMessage( self->base.owner, EM_INVTDRAW, 0, 0 );
  }
  if(self->inventoryDT < INVENTORY_BUTTON_DEBOUNCE_TIME && self->inventoryDT != 0 && !IsKeyPressed( VK_I ))
  {
    self->inventoryDT += *dt;
  }
  if(self->inventoryDT >= INVENTORY_BUTTON_DEBOUNCE_TIME)
  {
    self->inventoryDT = 0;
  }

  // Update player's attack
  if(self->playerState == PLAYER_STATE_ATTACKING_1)
  {
    self->dt += *dt;

    // Reset timer + player state if time threshold met + not press space
    if(self->dt > PLAYER_ATTACK_SPEED_SECONDS && !IsKeyPressed( VK_SPACE ))
    {
      self->dt = 0;
      self->playerState = PLAYER_STATE_IDLE;
    }
  }

  // Idle the player if no keys are pressed and not jumping or attacking
  if(!IsKeyPressed( VK_LEFT ) && !IsKeyPressed( VK_RIGHT ) && !IsKeyPressed( VK_SPACE )
    && !self->jumping && self->playerState != PLAYER_STATE_ATTACKING_1)
  {
    self->playerState = PLAYER_STATE_IDLE;
  }

  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"RUNNING_RIGHT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"RUNNING_LEFT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"JUMPING_RIGHT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"JUMPING_LEFT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"ATTACK_1_LEFT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"ATTACK_1_RIGHT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"IDLE_RIGHT", 0 );
  SendEntityMessage( self->base.owner, EM_CLDOFFLC, (int)"IDLE_LEFT", 0 );

  switch(self->playerState)
  {
  case PLAYER_STATE_IDLE:
    if(self->faceDir && !self->jumping) // facing right
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"IDLE_RIGHT", 0 );
    else if(!self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"IDLE_LEFT", 0 );
    if(self->faceDir && self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"JUMPING_RIGHT", 0 );
    else if(self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"JUMPING_LEFT", 0 );
    break;
  case PLAYER_STATE_MOVING:
    if(self->faceDir && !self->jumping) // facing right
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"RUNNING_RIGHT", 0 );
    else if(!self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"RUNNING_LEFT", 0 );
    if(self->faceDir && self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"JUMPING_RIGHT", 0 );
    else if(self->jumping)
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"JUMPING_LEFT", 0 );
    break;
  case PLAYER_STATE_ATTACKING_1:
    if(self->faceDir) // facing right
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"ATTACK_1_RIGHT", 0 );
    else
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"ATTACK_1_LEFT", 0 );
    break;
  case PLAYER_STATE_HIT:
    if(self->faceDir) // facing right
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"HIT_RIGHT", 0 );
    else
      SendEntityMessage( self->base.owner, EM_CLDONLC, (int)"HIT_LEFT", 0 );
    break;
  }
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PlaCInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// SetCanJump
// Purpose: Sets the canJump flag of the PlayerComponent to the provided param.
//
void PlaCSetCanJump( PLAC *self, BOOL *var1 )
{
  self->canJump = *var1;
}

//
// GetCanJump
// Purpose: Gets the canJump flag of the PlayerComponent to the provided param.
//
void PlaCGetCanJump( PLAC *self, BOOL *var1 )
{
  *var1 = self->canJump;
}

//
// PlaCGetInputVector
// Purpose: Copies the input vector contents into VECTOR2D var1
//
void PlaCGetInputVector( PLAC *self, VECTOR2D *var1 )
{
  *var1 = self->inputVector;
}

//
// PlaCSetInputVector
// Purpose: Copies VECTOR2D var1 contents into the input vector
//
void PlaCSetInputVector( PLAC *self, VECTOR2D *var1 )
{
  self->inputVector = *var1;
}

//
// PlaCGetJumping
// Purpose: Copies the jumping contents into BOOL *var1
//
void PlaCGetJumping( PLAC *self, BOOL *var1 )
{
  *var1 = self->jumping;
}

//
// PlaCSetJumping
// Purpose: Places the value of var1 into jumping
//
void PlaCSetJumping( PLAC *self, BOOL var1 )
{
  self->jumping = var1;
}

//
// PlaCGetHitBottom
// Purpose: 
//
void PlaCGetHitBottom( PLAC *self, BOOL *var1 )
{
  *var1 = self->hitBottom;
}

//
// PlaCSetHitBottom
// Purpose: 
//
void PlaCSetHitBottom( PLAC *self, BOOL var1 )
{
  self->hitBottom = var1;
}
