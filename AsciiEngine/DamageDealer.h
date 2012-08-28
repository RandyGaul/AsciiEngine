////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "EntityCreator.h"

typedef struct DAMAGE_DEALER_DATA
{
  VECTOR2D pos;
  VECTOR2D vel;
  VECTOR2D WH;
  int damage;
  int properties;
  float delay;    // Delay in seconds till automatic destruction
} DDD;

// Definition of the creator of this entity
extern ENTITY_CREATOR DAMAGE_DEALER_CREATOR;
