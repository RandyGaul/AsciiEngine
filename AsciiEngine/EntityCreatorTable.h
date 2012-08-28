////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file is used to maintain a hash table of ENTITY_CREATOR structs
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#pragma once

#include "GlobalDefines.h"
#include "EntityCreator.h"
#include "HashTable.h"

typedef ENTITY_CREATOR *P_ENTITY_CREATOR;

DECLARE_TABLE( P_ENTITY_CREATOR, MAX_KEY_LEN );

extern GET_TABLE_TYPE( P_ENTITY_CREATOR ) *ENTITY_CREATOR_TABLE;

//
// CreatorTableGetEntryKeys
// Purpose: Returns an array of string pointers pointing to strings representing all
//          the various types of ID keys in the TABLE. The last key will be null to
//          detect when to end loop.
//
char **CreatorTableGetEntryKeys( unsigned maxStrLen );
