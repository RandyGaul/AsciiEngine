////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/1/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "GameStateManager.h"
#include "GameStateList.h"
#include "GlobalDefines.h"
#include "Input.h"                // Various input functions
#include "ConsoleFuncs.h"         // RenderScreen;
#include "EntityFactory.h"        // Entity creation system
#include "EntityManager.h"        // Entity management system
#include "OpenFile.h"             // LoadAllArtAssets;
#include "Camera.h"               // GlobalCamInit; GlobalCamDisable
#include "FrameRateController.h"  // GetDT

static ENTITY *character = NULL;

RETURN_TYPE TestLevel2Load( void )
{
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevel2Init( void )
{
  ENTITY_LIST = LIST_CONSTRUCT( P_ENTITY );

  FileToEntities( "../MapAssets/test.txt" );
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevel2Update( void )
{
  if(IsKeyPressed( VK_1 ))
  {
    nextState = TestLevel;
  }

  if(IsKeyPressed( VK_2 ))
  {
    nextState = TestLevel2;
  }

  if(IsKeyPressed( VK_3 ))
  {
    nextState = MapEditor;
  }

  // Run all entitys' update functions.
  UpdateEntities( );
  GlobalCamUpdate( GetDT( ) );
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevel2Draw( void )
{
  ClearBuffer( );

  // draws all active entitys
  DrawEntities( );

  RenderScreen( ); // Renders the DOUBLE_BUFFER to the screen
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevel2Free( void )
{
  SerializeAllEntities( "../MapAssets/test2.txt" );
  
  // Frees all entitys within the EntityFactory system
  LIST_DESTROY( P_ENTITY, ENTITY_LIST );

  // Reset camera for next state
  GlobalCamDisable( );
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevel2Unload( void )
{
  return RETURN_SUCCESS;
}
