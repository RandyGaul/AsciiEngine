////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Message.h"
#include "ItemList.h"
#include "InventoryComponent.h"

#define SI_SLOT_NUM 18

//
// HP class
// This class is derived from the SmallInventory_COMPONENT base, and represents
// normal HP.
//
typedef struct _SMALL_INVENTORY_COMPONENT
{
  INVENTORY_COMPONENT base;
  BOOL drawMe;
  ITEM_ID data[SI_SLOT_NUM];
} SI;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SmallInventoryCOM_PROC( SI *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SmallInventoryCreate( SI *self );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SmallInventoryInit( const char *className );

//
// ClassDraw
// Purpose: Draws a visual representation of the class.
//
void SmallInventoryDraw( SI *self );

//
// SmallInventoryUpdate
// Purpose: Disables and enables PICK_ME_UP_ITEM.
//
void SmallInventoryUpdate( SI *self );

//
// SmallInventoryGet
// Purpose: Copies value of inventory at index var2 into int *var1
//
void SmallInventoryGet( SI *self, int *copyToMe, int index );

//
// SmallInventorySet
// Purpose: Copies value of ITEM_ID var1 into slot var2
//
void SmallInventorySet( SI *self, ITEM_ID replaceWithMe, int index );

//
// SmallInventoryGetSize
// Purpose: Copies the size in number of elements of the inventory array into int *var1
//
void SmallInventoryGetSize( int *size );

//
// SmallInventoryInsert
// Purpose: Inserts an item into the first available empty slot.
//
RETURN_TYPE SmallInventoryInsert( SI *self, ITEM_ID id );

//
// SmallInventoryEject
// Purpose: Creates an item entity for each item in the inventory, and empties the inventory.
//
void SmallInventoryEject( SI *self );

//
// SmallInventoryToggleDrawMe
// Purpose: Toggles boolean drawMe of SI class
//
void SmallInventoryToggleDrawMe( SI *self );

//
// SmallInventoryGetDrawMe
// Purpose: Copies drawMe into BOOL *var1
//
void SmallInventoryGetDrawMe( SI *self, BOOL *drawMe );

//
// SmallInventorySetDrawMe
// Purpose: Copies content of BOOL *var1 into drawMe
//
void SmallInventorySetDrawMe( SI *self, BOOL drawMe );
