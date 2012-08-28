////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/21/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "ActionList.h"
#include "EntityManager.h"
#include "EntityFactory.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void ActionListCOM_PROC( AL *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
    // GENERAL
  case EM_CLSINIT:
    ActionListInit( (const char *)var1 );
    break;
  case EM_CREATE:
    ActionListCreate( self );
    break;
  case EM_UPDATE:
    ActionListUpdate( self, (float *)var1 );
    break;
  case EM_DESTROY:
    ActionListDestroy( self );
    break;

    // ACTIONLIST
  case EM_ALADDACT:
    ActionListAddAction( self, (ALD *)var1 );
    break;
  case EM_ALREMACT:
    ActionListRemoveAction( (AL_NODE *)var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void ActionListCreate( AL *self )
{
  self->actionList = NULL;
  self->base.CLASS_NAME = CLASS_NAME;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void ActionListInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ActionListUpdate
// Purpose: Updates the action list.
//
void ActionListUpdate( AL *self, float *dt )
{
  AL_NODE *scan = self->actionList;

  // Cycle through each action and call its Update function
  // If find a blocking action, stop the cycle
  if(scan)
  {
    do
    {
      int flag = scan->flag;
      scan->Update( scan, dt );
      if(flag & BLOCKING)
        break;
      if(!scan)
        break;
    } while(scan->next);
  }
}

//
// ActionListDestroy
// Purpose: Frees an action list's actions.
//
void ActionListDestroy( AL *self )
{
  AL_NODE *scan = self->actionList;

  // Cycle through each action and free it from memory
  while(scan)
  {
    AL_NODE *temp = NULL;
    if(scan->next)
      temp = scan->next;
    ActionListRemoveAction( scan );
    scan = temp;
  }
}

//
// ActionListAddAction
// Purpose: Adds a specific action and allows customized flag to be set, to an actionList
//          on a game object.
//
void ActionListAddAction( AL *self, ALD *data )
{
  AL_NODE *node = NULL;

  switch(data->ID)
  {
  case ALT_PAUSE:
  case ALT_DESTROY:
  case ALT_SET_PROPERTIES:
  case ALT_CREATE_ENTITY:
  case ALT_SET_VEL:
    // Set data from provided ALD pointer
    node = (AL_NODE *)malloc( sizeof( AL_NODE ) );
    memset( node, 0, sizeof( AL_NODE ) );
    // Initialize data
    node->ownerComp = self;
    node->flag = data->flag;
    node->timerEnd = data->timerEnd;
    node->var1 = data->var1;
    node->var2 = data->var2;
    node->var3 = data->var3;
    node->ID = data->ID;
    node->dt = data->dt;

    // Assign individualized data
    switch(node->ID)
    {
    case ALT_PAUSE:
      node->Update = ActionListPause;
      break;
    case ALT_DESTROY:
      node->Update = ActionListDestroySelf;
      break;
    case ALT_SET_PROPERTIES:
      node->Update = ActionListSetProperties;
      break;
    case ALT_CREATE_ENTITY:
      node->Update = ActionListCreateEntity;
      break;
    case ALT_SET_VEL:
      node->Update = ActionListSetVel;
    }
    break;
  default:
    return;
  }

  // Add action to the actionList
  if(node)
  {
    AL_NODE *scan = self->actionList;

    if(scan)
    {
      while(scan->next)
      {
        scan = scan->next;
      }

      scan->next = node;
      node->prev = scan;
    }
    else
    {
      self->actionList = node;
    }
  }
}

//
// ActionListRemoveAction
// Purpose: Removes a specific action from an actionList.
//
void ActionListRemoveAction( AL_NODE *self )
{
  // Disconnect from list
  if(self)
  {
    if(self->prev)
    {
      self->prev->next = self->next;
      if(self->next)
      {
        self->next->prev = self->prev;
      }
    }
    else
    {
      if(self->next)
      {
        self->next->prev = NULL;
        self->ownerComp->actionList = self->next;
      }
      else
      {
        self->ownerComp->actionList = NULL;
      }
    }
  }

  free( self );
}

//
// ActionListPause
// Purpose: Creates a blocking pause for an amount of seconds.
//
void ActionListPause( AL_NODE *self, float *dt )
{
  self->dt += *dt;

  if(self->dt > self->timerEnd)
  {
    ActionListRemoveAction( self );
  }
}

//
// ActionListSetProperties
// Purpose: Sets the properties of an entity to the flags data member with |=
//          to the value of var1.
//
void ActionListSetProperties( AL_NODE *self, float *dt )
{
  self->ownerComp->base.owner->properties |= self->var1;
  ActionListRemoveAction( self );
}

//
// ActionListDestroySelf
// Purpose: Sends an EM_DESTROY message to the owner entity.
//
void ActionListDestroySelf( AL_NODE *self, float *dt )
{
  SendEntityMessage( self->ownerComp->base.owner, EM_INACTIVE, 0, 0 );
}

//
// ActionListCreateEntity
// Purpose: Creates an entity.
//
void ActionListCreateEntity( AL_NODE *self, float *dt )
{
  CreateEntity( (const char *)self->var1, self->var2, self->var3 );
  ActionListRemoveAction( self );
}

//
// ActionListSetVel
// Purpose: Sets the velocity of an object to var1
//
void ActionListSetVel( AL_NODE *self, float *dt )
{
  VECTOR2D vel = { (float)self->var1, (float)self->var2 };
  SendEntityMessage( self->ownerComp->base.owner, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
  ActionListRemoveAction( self );
}
