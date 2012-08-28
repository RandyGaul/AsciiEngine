////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Entity.h"
#include "Message.h"
#include "Serialize.h"
#include "LinkedList.h"

typedef ENTITY *P_ENTITY;
DECLARE_LIST( P_ENTITY );

extern LIST_TYPE( P_ENTITY ) *ENTITY_LIST;

//
// SendEntityMessage
// Purpose: Sends a message to an entity via pointer to the entity.
//
void SendEntityMessage( ENTITY *entity, EM msg, int var1, int var2 );

//
// DeleteEntity
// Purpose: Used in the NODE_CREATE macro in the DeleteData param.
//
void DeleteEntity( P_ENTITY entity );

//
// DestroyEntities
// Purpose: Cycles the entity list and calls their destroy functions.
//
RETURN_TYPE DestroyEntities( void );

//
// SendEntitiesMessage
// Purpose: Sends a message to all live entities.
//
void SendEntitiesMessage( EM msg, int var1, int var2 );

//
// AE_UpdateEntities
// Purpose: Cycles the entity list and calls their update functions.
//
RETURN_TYPE UpdateEntities( void );

//
// AE_DrawEntities
// Purpose: Cycles the entity list and calls their draw functions.
//
RETURN_TYPE DrawEntities( void );

//
// SerializeAllEntities
// Purpose: Serializes all active entities into a text file.
//
void SerializeAllEntities( const char *fileName );
