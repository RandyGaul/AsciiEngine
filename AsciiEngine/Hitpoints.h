////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "HitpointsComponent.h"

#define PLAYER_MAX_HP 20

//
// HP class
// This class is derived from the HITPOINTS_COMPONENT base, and represents
// normal HP.
//
typedef struct _NORMAL_HITPOINTS_COMPONENT
{
  HITPOINTS_COMPONENT base;
  int hp;
  int maxHP;
} HP;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void HitPointsCOM_PROC( HP *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void HitPointsCreate( HP *self, int hp );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void HitPointsInit( const char *className );

//
// AnimationUpdate
// Purpose: 
//
void HitPointsUpdate( HP *self, float *dt );

//
// HitPointsGet
// Purpose: Retrieves int HP and copies into int *var1
//
void HitPointsGet( HP *self, int *hp );

//
// HitPointsSet
// Purpose: Retrieves int HP and copies into int *var1
//
void HitPointsSet( HP *self, int hp );

//
// HitPointsDamage
// Purpose: Subtracts an int var1 from the hp data member, but does not go lower than zero
//
void HitPointsDamage( HP *self, int damage );

//
// HitPointsHeal
// Purpose: adds an int var1 from the hp data member, but does not go above than self->maxHP
//
void HitPointsHeal( HP *self, int heal );
