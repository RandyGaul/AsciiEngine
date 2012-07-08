////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "GlobalDefines.h"
#include "ObjectFactory.h"
#include "FrameRateController.h"

// Object headers
#include "RedSquare.h"

//
// The object factory allows easy handling of creation,
// deletion, updating, initializing, and drawing of all
// game objects. Simply include ObjectFactory.h to start
// creating your objects from a state file.
// Additional documentation on how object oriented C
// works: http://cecilsunkure.blogspot.com/2012/04/object-oriented-c-class-like-structures.html
//

// Start of linked list of objects.
// Linked list documentation: http://cecilsunkure.blogspot.com/2010/11/memory-allocation-and-linked-lists.html
GAMEOBJECT_NODE *OBJECT_LIST = NULL;

//
// AE_ObjectListPush
// Purpose: Adds a new node to the end of the OBJECT_LIST.
//
RETURN_TYPE AE_ObjectListPush( GAMEOBJECT *object )
{
  GAMEOBJECT_NODE *scan = OBJECT_LIST;
  GAMEOBJECT_NODE *newNode = (GAMEOBJECT_NODE *)malloc( sizeof( GAMEOBJECT_NODE ) );

  newNode->data_ = object;
  newNode->next_ = NULL;
  newNode->prev_ = NULL;

  // Check for proper allocation
  if(!newNode)
  {
    return RETURN_FAILURE;
  }

  if(scan) // if list is not empty
  {
    while(!(scan->next_))
    {
      scan = scan->next_;
    }
    scan->next_ = newNode;
    newNode->prev_ = scan;
  }
  else // if list is empty
  {
    OBJECT_LIST = newNode;
  }

  // Let object have pointer to its node
  object->node_ = newNode;

  return RETURN_SUCCESS;
}

//
// AE_ObjectNodeDelete
// Purpose: Deletes a specific node from the OBJECT_LIST
//
RETURN_TYPE AE_ObjectNodeDelete( GAMEOBJECT_NODE *toDelete )
{
  // Disconnect node from list
  toDelete->prev_->next_ = toDelete->next_;
  toDelete->next_->prev_ = toDelete->prev_;

  free( toDelete );
  return RETURN_SUCCESS;
}

//
// AE_CreateObject
// Purpose: Creates a game object from an ID. This is useful since
//          the factory abstracts the necessity of including many
//          various object files in order to just create different
//          kinds of objects. The GAMEOBJECT_TYPE enumeration is
//          within GameObject.h.
// Notes  : This function relies on some fancy typecasting to keep
//          from producing warnings. Every time a new type of object
//          is created a new GAMEOBJECT_TYPE will need to be created,
//          and this function will require an aditional case.
//
GAMEOBJECT *AE_CreateObject( GAMEOBJECT_TYPE ID )
{
  void *object = NULL;

  switch(ID)
  {
  case GO_REDSQUARE:
    object = malloc( sizeof( REDSQUARE ) );
    ((GAMEOBJECT *)object)->vtable_ = (const _GAMEOBJECT_VTABLE *)(&REDSQUARE_VTABLE);
    ((REDSQUARE *)object)->base_.ID_ = GO_REDSQUARE;
    AE_ObjectListPush( object );
    return object;
  }

  // ID mismatch (shouldn't ever get here! D:)
  return object;
}

//
// AE_DeleteObject
// Purpose: Deletes an object from the object list and deallocates
//          its memory.
//
RETURN_TYPE AE_DeleteObject( GAMEOBJECT *toDelete )
{
  AE_ObjectNodeDelete( toDelete->node_ );
  toDelete->vtable_->Destroy( toDelete );
  return RETURN_SUCCESS;
}

//
// AE_UpdateObjects
// Purpose: Cycles the object list and calls their update functions.
//
RETURN_TYPE AE_UpdateObjects( void )
{
  GAMEOBJECT_NODE *scan = OBJECT_LIST;

  while(scan)
  {
    scan->data_->vtable_->Update( scan->data_ );
    scan = scan->next_;
  }
  return RETURN_SUCCESS;
}

//
// AE_DrawObjects
// Purpose: Cycles the object list and calls their draw functions.
//
RETURN_TYPE AE_DrawObjects( void )
{
  GAMEOBJECT_NODE *scan = OBJECT_LIST;

  while(scan)
  {
    scan->data_->vtable_->Draw( scan->data_ );
    scan = scan->next_;
  }
  return RETURN_SUCCESS;
}

//
// AE_DestroyObjects
// Purpose: Cycles the object list and calls their destroy functions.
//
RETURN_TYPE AE_DestroyObjects( void )
{
  GAMEOBJECT_NODE *scan = OBJECT_LIST;

  while(scan)
  {
    AE_DeleteObject( scan->data_ );
    scan = scan->next_;
  }
  return RETURN_SUCCESS;
}

//
// AE_InitObjects
// Purpose: Cycles the object list and calls their init functions.
// Notes  : The init functions act as "default initializers". To init
//          an object with specific initialization values you must
//          use that object's specific set function. This will require
//          an inclusion of that object type's header file to have
//          proper access to the set function.
//
RETURN_TYPE AE_InitObjects( void )
{
  GAMEOBJECT_NODE *scan = OBJECT_LIST;

  while(scan)
  {
    scan->data_->vtable_->Init( scan->data_ );
    scan = scan->next_;
  }
  return RETURN_SUCCESS;
}
