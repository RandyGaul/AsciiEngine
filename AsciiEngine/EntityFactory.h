////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

//
// The entity factory allows easy handling of creation,
// deletion, updating, initializing, and drawing of all
// game entitys. Simply include EntityFactory.h to start
// creating your entitys from a state file.
// Additional documentation on how entity oriented C
// works: http://cecilsunkure.blogspot.com/2012/04/entity-oriented-c-class-like-structures.html
//

#include "Entity.h"
#include "EntityCreator.h"

//
// CreateEntity
// Purpose: Creates a game entity from an ID. This is useful since
//          the factory abstracts the necessity of including many
//          various entity files in order to just create different
//          kinds of entitys. The factory is also key in entity
//          serialization.
//
ENTITY *CreateEntity( const char *ID, int var1, int var2 );

//
// CreateEntities
// Purpose: Calles CreateEntity a number of times specified by count.
//
RETURN_TYPE CreateEntities( const char *ID, int var1, int var2, int count );
