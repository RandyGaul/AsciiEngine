////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file contains a single function for easy maintaince of
// the initialization of all entity creators

#include "Registration.h"
#include "EntityFactory.h"
#include "EntityCreatorTable.h"

// Includes for different entity types
#include "Hero.h"
#include "Tile.h"
#include "StaticBackground.h"
#include "SimpleEnemy.h"
#include "DamageDealer.h"
#include "DamageText.h"
#include "Item.h"
#include "ItemParticle.h"
#include "Point.h"

// Includes for different component types
#include "Sprite.h"
#include "Cloud.h"
#include "Animation.h"
#include "Square.h"
#include "ActionList.h"
#include "Physics.h"
#include "Player.h"
#include "Hitpoints.h"
#include "SmallInventory.h"
#include "JumperLittle.h"

#define REGISTER_CREATOR( TYPE ) \
  INSERT_DATA( P_ENTITY_CREATOR, ENTITY_CREATOR_TABLE, &TYPE##_CREATOR, TYPE##_CREATOR.ID )


//
// RegisterEntityClasses
// Purpose: Register all entity class types by entering their creators
//          into the creator map, and initialize class resources/names.
//
RETURN_TYPE RegisterEntityClasses( void )
{
  ENTITY_CREATOR_TABLE = CREATE_TABLE( P_ENTITY_CREATOR, 101 );
  REGISTER_CREATOR( HERO );
  REGISTER_CREATOR( TILE );
  REGISTER_CREATOR( STATICBG );
  REGISTER_CREATOR( SIMPLE_ENEMY );
  REGISTER_CREATOR( DAMAGE_DEALER );
  REGISTER_CREATOR( DAMAGE_TEXT);
  REGISTER_CREATOR( ITEM );
  REGISTER_CREATOR( ITEM_PARTICLE );
  REGISTER_CREATOR( POINT );
  return RETURN_SUCCESS;
}

//
// RegisterEntityComponents
// Purpose: Register all component classes by initializes class
//          resources and names.
//
RETURN_TYPE RegisterEntityComponents( void )
{
  SpriteInit( "Sprite" );
  CloudInit( "Cloud" );
  AnimationInit( "Animation" );
  SquareInit( "Square" );
  ActionListInit( "ActionList" );
  PhysInit( "Physics" );
  PlaCInit( "Player" );
  HitPointsInit( "HitPoints" );
  SmallInventoryInit( "SmallInventory" );
  JumperLittleInit( "JumperLittle" );
  return RETURN_SUCCESS;
}