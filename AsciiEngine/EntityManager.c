////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "EntityManager.h"
#include "FrameRateController.h"

// Start of linked list of Entities.
// Linked list documentation: http://cecilsunkure.blogspot.com/2010/11/memory-allocation-and-linked-lists.html
DEFINE_LIST( P_ENTITY );
LIST_TYPE( P_ENTITY ) *ENTITY_LIST = NULL;

//
// SendEntityMessage
// Purpose: Sends a message to an entity via pointer to the entity.
//
void SendEntityMessage( ENTITY *entity, EM msg, int var1, int var2 )
{
  entity->EM_PROC( entity, msg, var1, var2 );
}

//
// DeleteEntity
// Purpose: Used in the NODE_CREATE macro in the DeleteData param.
//
void DeleteEntity( P_ENTITY entity )
{
  entity->EM_PROC( (ENTITY *)entity, EM_DESTROY, 0, 0 );
}

//
// CallbackSendEntityMessage
// Purpose: Used to send all entities a message.
//
RETURN_TYPE CallbackSendEntityMessage( NODE_TYPE( P_ENTITY ) *node, void *param )
{
  typedef struct
  {
    EM msg;
    int var1;
    int var2;
  } paramType;

  paramType *parameter = (paramType *)param;

  // Skip inactive entities
  if(node->data->inactive)
    return RETURN_SUCCESS;

  SendEntityMessage( node->data, parameter->msg, parameter->var1, parameter->var2 );
  return RETURN_SUCCESS;
}

//
// SendEntitiesMessage
// Purpose: Sends a message to all live entities.
//
void SendEntitiesMessage( EM msg, int var1, int var2 )
{
  typedef struct
  {
    EM msg;
    int var1;
    int var2;
  } paramType;

  paramType parameter = {
    msg,
    var1,
    var2
  };

  LIST_CALLER( P_ENTITY, ENTITY_LIST, CallbackSendEntityMessage, &parameter );
}

//
// UpdateEntities
// Purpose: Cycles the entity list and calls their update functions.
//
RETURN_TYPE UpdateEntities( void )
{
  float dt = GetDT( );
  SendEntitiesMessage( EM_UPDATE, (int)&dt, 0 );
  return RETURN_SUCCESS;
}

//
// DrawEntities
// Purpose: Cycles the Entity list and calls their draw functions.
//
RETURN_TYPE DrawEntities( void )
{
  SendEntitiesMessage( EM_DRAW, 0, 0 );
  return RETURN_SUCCESS;
}

//
// CallbackDeleteNode
// Purpose: Used to delete all nodes.
//
RETURN_TYPE CallbackDeleteNode( NODE_TYPE( P_ENTITY ) *node, void *param )
{
  SendEntityMessage( node->data, EM_DESTROY, 0, 0 );
  free( node->data );
  LIST_REMOVE( P_ENTITY, ENTITY_LIST, node );
  return RETURN_SUCCESS;
}

//
// DestroyEntities
// Purpose: Cycles the entity list and calls their destroy functions.
//
RETURN_TYPE DestroyEntities( void )
{
  LIST_CALLER( P_ENTITY, ENTITY_LIST, CallbackDeleteNode, 0 );
  return RETURN_SUCCESS;
}

//
// CallbackSerializeEntity
// Purpose: Used to serialize all nodes.
//
RETURN_TYPE CallbackSerializeEntity( NODE_TYPE( P_ENTITY ) *node, void *param )
{
  EntityToFile( node->data );
  return RETURN_SUCCESS;
}

//
// SerializeAllEntities
// Purpose: Serializes all active entities into a text file.
//
void SerializeAllEntities( const char *fileName )
{
  SerializerSetFile( fileName );

  SerializeMapDimensions( );
  
  LIST_CALLER( P_ENTITY, ENTITY_LIST, CallbackSerializeEntity, 0 );

  SerializerCloseFile( );
}
