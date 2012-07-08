////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef GAMEOBJECTH
#define GAMEOBJECTH

#include "Message.h"

// Contains all the various IDs for every type of
// game object object in the game
typedef enum
{
  GO_NONE = 0,
  GO_REDSQUARE,
}GAMEOBJECT_TYPE;

// Forward declaration for proper compile
struct _GAMEOBJECT_NODE;
struct _GAMEOBJECT;

// Generalized vtable for generalized function calls to all derived
// classes. The set function for derived classes will almost always
// have a unique parameter list, so typecasting will be required to
// properly access it manually.
typedef struct _GAMEOBJECT_VTABLE
{
  void (*Construct)( struct _GAMEOBJECT *self );
  void (*Init)     ( struct _GAMEOBJECT *self );
  void (*set)      ( struct _GAMEOBJECT *self );
  void (*Update)   ( struct _GAMEOBJECT *self );
  void (*Draw)     ( struct _GAMEOBJECT *self );
  void (*Destroy)  ( struct _GAMEOBJECT *self );
} _GAMEOBJECT_VTABLE;

// Base class for a generic game object.
typedef struct _GAMEOBJECT
{
  GAMEOBJECT_TYPE ID_;               // Type of object this object is
  AE_MESSAGE *queue_;                // Queue of all messages recieved by this object
  struct _GAMEOBJECT_NODE *node_;    // Pointer to this object's node for easy deletion
  const _GAMEOBJECT_VTABLE *vtable_; // Generalized vtable of various object functions
} GAMEOBJECT;

// A simple doubly node for a linked list.
// Linked list documentation: http://cecilsunkure.blogspot.com/2010/11/memory-allocation-and-linked-lists.html
// Object oriented C: http://cecilsunkure.blogspot.com/2012/04/object-oriented-c-class-like-structures.html
typedef struct _GAMEOBJECT_NODE
{
  GAMEOBJECT *data_;              // Pointer to the actual game object
  struct _GAMEOBJECT_NODE *next_;
  struct _GAMEOBJECT_NODE *prev_;
} GAMEOBJECT_NODE;

#endif  GAMEOBJECTH