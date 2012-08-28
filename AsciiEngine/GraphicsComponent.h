////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Message.h"

// Forward decl
struct _ENTITY;

//
// Common interface for all graphics components.
//
typedef struct _GRAPHICS_COMPONENT
{
  const char *CLASS_NAME;
  void (*COM_PROC)( struct _GRAPHICS_COMPONENT *self, EM msg, int var1, int var2 );
  BOOL enableCam;
  struct _ENTITY *owner;
} GRAPHICS_COMPONENT;
