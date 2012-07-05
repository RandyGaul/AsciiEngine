////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef OBJECTFACTORYH
#define OBJECTFACTORYH

#include "GameObject.h"

// Macros that simply make maintainance in ObjectFactory.c easier
#define DRAW_TYPECAST( pointer, type ) \
  (((type *)(pointer))->vtable->Draw( (type *)pointer ))

#define DESTROY_TYPECAST( pointer, type ) \
  (((type *)(pointer))->vtable->Destroy( (type *)pointer ))

#define UPDATE_TYPECAST( pointer, type ) \
  (((type *)(pointer))->vtable->Update( (type *)pointer ))

#define INIT_TYPECAST( pointer, type ) \
  (((type *)(pointer))->vtable->Init( (type *)pointer ))

//
// AE_CreateObject
// Purpose: Creates a game object from an ID. This is useful since
//          the factory abstracts the necessity of including many
//          various object files in order to just create different
//          kinds of objects. The GAMEOBJECT_TYPE enumeration is
//          within GameObject.h.
//
GAMEOBJECT *AE_CreateObject( GAMEOBJECT_TYPE ID );

//
// AE_DeleteObject
// Purpose: Deletes an object from the object list and deallocates
//          its memory.
//
RETURN_TYPE AE_DeleteObject( GAMEOBJECT *toDelete );

//
// AE_UpdateObjects
// Purpose: Cycles the object list and calls their update functions.
//
RETURN_TYPE AE_UpdateObjects( void );

//
// AE_DrawObjects
// Purpose: Cycles the object list and calls their draw functions.
//
RETURN_TYPE AE_DrawObjects( void );

//
// AE_DestroyObjects
// Purpose: Cycles the object list and calls their destroy functions.
//
RETURN_TYPE AE_DestroyObjects( void );

//
// AE_InitObjects
// Purpose: Cycles the object list and calls their init functions.
//
RETURN_TYPE AE_InitObjects( void );

#endif  OBJECTFACTORYH