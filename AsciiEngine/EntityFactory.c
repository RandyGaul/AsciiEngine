////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "GlobalDefines.h"
#include "EntityFactory.h"
#include "FrameRateController.h"
#include "EntityCreatorTable.h"   // Map Entity creators to string IDs
#include "EntityManager.h"        // EntityListPush

//
// The Entity factory allows easy handling of creation,
// deletion, updating, initializing, and drawing of all
// game entities. Simply include EntityFactory.h to start
// creating your entities from a state file.
// Additional documentation on how Entity oriented C
// works: http://cecilsunkure.blogspot.com/2012/04/entity-oriented-c-class-like-structures.html
//

//
// CreateEntity
// Purpose: Creates a game entity from an ID. This is useful since
//          the factory abstracts the necessity of including many
//          various entity files in order to just create different
//          kinds of entities. The factory is also key in entity
//          serialization.
//
ENTITY *CreateEntity( const char *ID, int var1, int var2 )
{
  ENTITY *entity = NULL;
  NODE_TYPE( P_ENTITY ) *node = NULL;
  ENTITY_CREATOR *entityCreator = FIND_DATA( P_ENTITY_CREATOR, ENTITY_CREATOR_TABLE, ID );

  if(!entityCreator)
    return NULL; // ID mismatch (shouldn't ever get here! D:)

  entity = entityCreator->Create( var1, var2 );

  node = NODE_CREATE( P_ENTITY, entity, DeleteEntity, entity->zOrder );
  LIST_INSERT( P_ENTITY, ENTITY_LIST, node );

  return entity;
}

//
// CreateEntities
// Purpose: Calles CreateEntity a number of times specified by count.
//
RETURN_TYPE CreateEntities( const char *ID, int var1, int var2, int count )
{
  int i;

  for(i = 0; i < count; ++i)
    CreateEntity( ID, var1, var2 );

  return RETURN_SUCCESS;
}
