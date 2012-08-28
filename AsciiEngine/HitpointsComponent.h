////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Message.h"

// Forward decl
struct _ENTITY;

//
// Common interface for all hitpoints components.
//
typedef struct _HITPOINTS_COMPONENT
{
  const char *CLASS_NAME;
  void (*COM_PROC)( struct _HITPOINTS_COMPONENT *self, EM msg, int var1, int var2 );
  struct _ENTITY *owner;
} HITPOINTS_COMPONENT;
