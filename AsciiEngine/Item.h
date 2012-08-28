////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/24/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "EntityCreator.h"
#include "ItemList.h"

// Definition of the creator of this entity
extern ENTITY_CREATOR ITEM_CREATOR;

//
// ItemIDToImage
// Purpose: Maps item id's to image pointers.
//
IMAGE *ItemIDToImage( ITEM_ID id );

//
// ItemIDToImage
// Purpose: Maps item id's to string identifiers.
//
const char *ItemIDToString( ITEM_ID id );
