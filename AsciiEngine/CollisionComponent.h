////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Message.h"
#include "Shapes.h"

// Forward decl
struct _ENTITY;

//
// Common interface for all collision components.
//
typedef struct _COLLISION_COMPONENT
{
  const char *CLASS_NAME;
  void (*COM_PROC)( struct _COLLISION_COMPONENT *self, EM msg, int var1, int var2 );
  struct _ENTITY *owner;
} COLLISION_COMPONENT;

typedef struct COLLISION_DATA
{
  AE_RECT rect;
  int flag;
  float shortestDist;
  struct _ENTITY *closestEntity;
  struct _ENTITY *entity; 
} COL_DATA;

#define DAMAGE_DEALER_COLLISION   0x00000001
#define DONT_COLLIDE_WITH_OTHERS  0x00000002
#define ITEM_COLLISION            0x00000004
