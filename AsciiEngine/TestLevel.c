////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/10/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "GameStateManager.h"
#include "GameStateList.h"
#include "GlobalDefines.h"
#include "Graphics.h"             // Various graphics functions
#include "Input.h"                // Various input functions
#include "ConsoleFuncs.h"         // RenderScreen;
#include "EntityFactory.h"        // Entity creation system
#include "EntityManager.h"        // Entity management system
#include "OpenFile.h"             // LoadAllArtAssets;
#include "Camera.h"               // GlobalCamInit; GlobalCamDisable
#include "FrameRateController.h"  // GetDT
#include "Serialize.h"

RETURN_TYPE TestLevelLoad( void )
{
  // Loads all art assets from a specific folder
  LoadAllArtAssets( "../ArtAssets/" );

  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevelInit( void )
{
  ENTITY_LIST = LIST_CONSTRUCT( P_ENTITY );

  FileToEntities( "../MapAssets/TestLevel.txt" );

  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevelUpdate( void )
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

RETURN_TYPE TestLevelDraw( void )
{
  ClearBuffer( );

  // draws all active entitys
  DrawEntities( );

  RenderScreen( ); // Renders the DOUBLE_BUFFER to the screen
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevelFree( void )
{
  SerializeAllEntities( "../MapAssets/test.txt" );

  // Frees all entitys within the EntityFactory system
  LIST_DESTROY( P_ENTITY, ENTITY_LIST );

  // Reset camera for next state
  GlobalCamDisable( );
  return RETURN_SUCCESS;
}

RETURN_TYPE TestLevelUnload( void )
{
  return RETURN_SUCCESS;
}
