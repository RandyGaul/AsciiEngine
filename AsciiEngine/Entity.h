////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "GlobalDefines.h"
#include "Graphics.h"
#include "Message.h"
#include "Action.h"
#include "Component.h"

// Forward declaration for proper compile
struct _ENTITY_NODE;
struct _ENTITY;

// Base class for a generic game entity.
typedef struct _ENTITY
{
  const char *CLASS_NAME;
  void (*EM_PROC)( struct _ENTITY *self, EM msg, int var1, int var2 );
  EN_COMPS comps;
  unsigned zOrder;
  int properties;               // See Properties.h for various properties
  int data;                     // General purpose data holder
  BOOL inactive;                // If TRUE entity is deleted and removed from list during update
  struct _ENTITY_NODE *node;    // Pointer to this entity's node for easy deletion
} ENTITY;

// A simple doubly node for a linked list.
// Linked list documentation: http://cecilsunkure.blogspot.com/2010/11/memory-allocation-and-linked-lists.html
// Object oriented C: http://cecilsunkure.blogspot.com/2012/04/entity-oriented-c-class-like-structures.html
typedef struct _ENTITY_NODE
{
  ENTITY *data_;              // Pointer to the actual game entity
  struct _ENTITY_NODE *next_;
  struct _ENTITY_NODE *prev_;
} ENTITY_NODE;

void EntityInactive( ENTITY *self );
