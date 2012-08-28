////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/18/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "PlayerComponent.h"
#include "Entity.h"

#define PLAYER_ATTACK_SPEED_SECONDS .75f

typedef enum _PLAYER_STATE
{
  PLAYER_STATE_IDLE,
  PLAYER_STATE_MOVING,
  PLAYER_STATE_ATTACKING_1,
  PLAYER_STATE_HIT,
} PLAYER_STATE;

//
// PLAYER class
// This class is derived from the PLAYER_COMPONENT base, and enables player input
//
typedef struct _PLAC_COMPONENT
{
  PLAYER_COMPONENT base;
  BOOL canJump;
  BOOL jumping; // TRUE YES : FALSE NO
  BOOL faceDir; // TRUE RIGHT : FALSE LEFT
  BOOL hitBottom;
  float dt;     // General purpose timer
  float inventoryDT;  // Timer for inventory button debounce
  PLAYER_STATE playerState; // Walking/Running/Jumping/Idle/Hit/Attacking
  VECTOR2D inputVector;
} PLAC;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PlaCCOM_PROC( PLAC *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PlaCCreate( PLAC *self );

//
// ClassUpdate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PlaCUpdate( PLAC *self, float *dt );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PlaCInit( const char *className );

//
// SetCanJump
// Purpose: Sets the canJump flag of the PlayerComponent to the provided param.
//
void PlaCSetCanJump( PLAC *self, BOOL *var1 );

//
// GetCanJump
// Purpose: Gets the canJump flag of the PlayerComponent to the provided param.
//
void PlaCGetCanJump( PLAC *self, BOOL *var1 );

//
// PlaCGetInputVector
// Purpose: Copies the input vector contents into VECTOR2D var1
//
void PlaCGetInputVector( PLAC *self, VECTOR2D *var1 );

//
// PlaCSetInputVector
// Purpose: Copies VECTOR2D var1 contents into the input vector
//
void PlaCSetInputVector( PLAC *self, VECTOR2D *var1 );

//
// PlaCGetJumping
// Purpose: Copies the jumping contents into BOOL *var1
//
void PlaCGetJumping( PLAC *self, BOOL *var1 );

//
// PlaCSetJumping
// Purpose: Places the value of var1 into jumping
//
void PlaCSetJumping( PLAC *self, BOOL var1 );

//
// PlaCGetHitBottom
// Purpose: 
//
void PlaCGetHitBottom( PLAC *self, BOOL *var1 );

//
// PlaCSetHitBottom
// Purpose: 
//
void PlaCSetHitBottom( PLAC *self, BOOL var1 );
