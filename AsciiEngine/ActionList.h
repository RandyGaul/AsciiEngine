////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/21/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "ActionListComponent.h"

#define BLOCKING        0x00000001

typedef enum ACTION_LIST_ACTION_TYPE
{
  ALT_PAUSE,
  ALT_DESTROY,
  ALT_SET_PROPERTIES,
  ALT_CREATE_ENTITY,
  ALT_SET_VEL,
} ALT;

typedef struct ACTION_LIST_DATA
{
  float dt;       // Starting time
  float timerEnd; // End time
  int flag;       // Multi-purpose flags
  int var1;       // General data
  int var2;       // General data
  int var3;       // General data
  ALT ID;         // Type of action
} ALD;

struct _ACTION_LIST_COMPONENT;

typedef struct _AL_NODE
{
  ALT ID;                               // Type of action
  float dt;                             // Used to store accumulated time
  float timerEnd;                       // Used to compare with dt
  int flag;                             // Bitfield for flags : SEE TOP OF FILE FOR DEFINES
  int var1;                             // General purpose data
  int var2;                             // General purpose data
  int var3;                             // General purpose data
  struct _ACTION_LIST *ownerComp; // Pointer to the owner component
  void (*Update)( struct _AL_NODE *self, float * );  // Update function for this action
  struct _AL_NODE *next;                // Pointer to next in list
  struct _AL_NODE *prev;                // Pointer to the previous in list
} AL_NODE;

typedef struct _ACTION_LIST
{
  ACTIONLIST_COMPONENT base;
  AL_NODE *actionList;
} AL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void ActionListCOM_PROC( AL *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void ActionListCreate( AL *self );

//
// ActionListRemoveAction
// Purpose: Removes a specific action from an actionList.
//
void ActionListRemoveAction( AL_NODE *self );

//
// ActionListDestroy
// Purpose: Frees an action list's actions.
//
void ActionListDestroy( AL *self );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void ActionListInit( const char *className );


//
// ActionListUpdate
// Purpose: Updates the action list.
//
void ActionListUpdate( AL *self, float *dt );

//
// ActionListAddAction
// Purpose: Adds a specific action and allows customized flag to be set, to an actionList
//          on a game object.
//
void ActionListAddAction( AL *self, ALD *data );

//
// ActionListPause
// Purpose: Creates a blocking pause for an amount of seconds.
//
void ActionListPause( AL_NODE *self, float *dt );

//
// ActionListSetProperties
// Purpose: Sets the properties of an entity to the flags data member with |=.
//
void ActionListSetProperties( AL_NODE *self, float *dt );

//
// ActionListDestroySelf
// Purpose: Sends an EM_DESTROY message to the owner entity.
//
void ActionListDestroySelf( AL_NODE *self, float *dt );

//
// ActionListCreateEntity
// Purpose: Creates an entity.
//
void ActionListCreateEntity( AL_NODE *self, float *dt );

//
// ActionListSetVel
// Purpose: Sets the velocity of an object to var1
//
void ActionListSetVel( AL_NODE *self, float *dt );
