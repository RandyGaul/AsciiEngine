////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "SmallInventory.h"
#include "Component.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "Item.h"
#include "Camera.h"
#include "ImageTable.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SmallInventoryCOM_PROC( SI *self, EM msg, int var1, int var2 )
{
  // GENERAL
  switch(msg)
  {
  case EM_CLSINIT:
    SmallInventoryInit( (const char *)var1 );
    break;
  case EM_CREATE:
    SmallInventoryCreate( self );
    break;
  case EM_DRAW:
    SmallInventoryDraw( self );
    break;
  case EM_UPDATE:
    SmallInventoryUpdate( self );
    break;

  // DATA ACCESS
  case EM_GETINV:
    SmallInventoryGet( self, (int *)var1, var2 );
    break;
  case EM_SETINV:
    SmallInventorySet( self, (ITEM_ID)var1, var2 );
    break;
  case EM_INSINV:
    SmallInventoryInsert( self, (ITEM_ID)var1 );
    break;
  case EM_GETINVSZ:
    SmallInventoryGetSize( (int *)var1 );
    break;
  case EM_INVEJECT:
    SmallInventoryEject( self );
    break;
  case EM_INVGDRAW:
    SmallInventoryGetDrawMe( self, (BOOL *)var1 );
    break;
  case EM_INVSDRAW:
    SmallInventorySetDrawMe( self, var1 );
    break;
  case EM_INVTDRAW:
    SmallInventoryToggleDrawMe( self );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SmallInventoryCreate( SI *self )
{
  int i;

  for(i = 0; i < SI_SLOT_NUM; ++i)
    self->data[i] = (ITEM_ID)0;

  self->base.CLASS_NAME = CLASS_NAME;
  self->drawMe = FALSE;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SmallInventoryInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ClassDraw
// Purpose: Draws a visual representation of the class.
//
void SmallInventoryDraw( SI *self )
{
  int i, y = 3, x = 3;

  if(self->drawMe)
  {
    WriteImageToScreen( "SmallInventoryBack.AEArt", (int)-GLOBAL_CAM.center.x_ + 1, (int)-GLOBAL_CAM.center.y_ + 1 );

    for(i = 0; i < SI_SLOT_NUM; ++i, x += 2)
    {
      if(i == 9)
      {
        y += 2;
        x = 3;
      }
      if(self->data[i] != NONE)
        WriteImageToScreen( ItemIDToString( self->data[i] ), x - (int)GLOBAL_CAM.center.x_, y - (int)GLOBAL_CAM.center.y_ );
    }
  }
}

//
// SmallInventoryUpdate
// Purpose: Disables and enables NO_PICKUP_ITEMS.
//
void SmallInventoryUpdate( SI *self )
{
  if(self->data[SI_SLOT_NUM - 1] == NONE)
    self->base.owner->properties &= ~NO_PICKUP_ITEMS;
  else
    self->base.owner->properties |= NO_PICKUP_ITEMS;
}

//
// SmallInventoryGet
// Purpose: Copies value of inventory at index var2 into int *var1
//
void SmallInventoryGet( SI *self, int *copyToMe, int index )
{
  *copyToMe = self->data[index];
}

//
// SmallInventorySet
// Purpose: Copies value of ITEM_ID var1 into slot var2
//
void SmallInventorySet( SI *self, ITEM_ID replaceWithMe, int index )
{
  self->data[index] = replaceWithMe;
}

//
// SmallInventoryGetSize
// Purpose: Copies the size in number of elements of the inventory array into int *var1
//
void SmallInventoryGetSize( int *size )
{
  *size = SI_SLOT_NUM;
}

//
// SmallInventoryInsert
// Purpose: Inserts an item into the first available empty slot.
//
RETURN_TYPE SmallInventoryInsert( SI *self, ITEM_ID id )
{
  int i;
  
  for(i = 0; i < SI_SLOT_NUM; ++i)
  {
    if(!self->data[i])
    {
      self->data[i] = id;
      return RETURN_SUCCESS;
    }
  }
  return RETURN_FAILURE;
}

//
// SmallInventoryEject
// Purpose: Creates an item entity for each item in the inventory, and empties the inventory.
//
void SmallInventoryEject( SI *self )
{
  int i;
  VECTOR2D pos = { 0 };
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  
  for(i = 0; i < SI_SLOT_NUM; ++i)
    if(self->data[i])
    {
      CreateEntity( "ITEM", (int)&pos, self->data[i] );
      self->data[i] = NONE;
    }
}

//
// SmallInventoryToggleDrawMe
// Purpose: Toggles boolean drawMe of SI class
//
void SmallInventoryToggleDrawMe( SI *self )
{
  if(self->drawMe)
    self->drawMe = FALSE;
  else
    self->drawMe = TRUE;
}

//
// SmallInventoryGetDrawMe
// Purpose: Copies drawMe into BOOL *var1
//
void SmallInventoryGetDrawMe( SI *self, BOOL *drawMe )
{
  *drawMe = self->drawMe;
}

//
// SmallInventorySetDrawMe
// Purpose: Copies content of BOOL *var1 into drawMe
//
void SmallInventorySetDrawMe( SI *self, BOOL drawMe )
{
  self->drawMe = drawMe;
}
