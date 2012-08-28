////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Entity.h"

typedef struct _ENTITY_CREATOR
{
  const char *ID;                           // Type of entity to create
  ENTITY *(*Create)( int var1, int var2 );  // Pointer to the creation function for this entity
} ENTITY_CREATOR;
