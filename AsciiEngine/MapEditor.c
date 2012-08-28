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
#include "TileMap.h"              // Various tile mapping functions
#include "Graphics.h"             // Various graphics functions
#include "Input.h"                // Various input functions
#include "ConsoleFuncs.h"         // RenderScreen;
#include "EntityFactory.h"        // Entity creation system
#include "EntityManager.h"        // Entity management system
#include "OpenFile.h"             // LoadAllArtAssets;
#include "Camera.h"               // GlobalCamInit; GlobalCamDisable
#include "FrameRateController.h"  // GetDT
#include "EntityCreatorTable.h"   // CreatorTableGetEntryKeys;
#include "Button.h"

static ENTITY *camera = NULL;
static AE_RECT camBound = { 0 };
static AE_COORD verticalScroller = { 0 }, horizontalScroller = { 0 };
static VECTOR2D origin = { -10000.0f, -10000.0f };
static char **ENTITY_TYPES = NULL;
static char *Brush = "TILE";

RETURN_TYPE MapEditorLoad( void )
{
  ENTITY_LIST = LIST_CONSTRUCT( P_ENTITY );
  BUTTON_LIST = LIST_CONSTRUCT( P_BUTTON );

  // Initialize the map system with a map file
  FileToEntities( "../MapAssets/MapEditorSave.txt" );

  // Gather all entity types
  ENTITY_TYPES = CreatorTableGetEntryKeys( 9 );

  return RETURN_SUCCESS;
}

RETURN_TYPE MapEditorInit( void )
{
  // Create buttons
  AE_RECT buttonRect = { { 44.5f, 18.f }, VIEWPORT_WIDTH - 1.0f, VIEWPORT_HEIGHT + 2.0f };
  BUTTON *button = CreateButton( "VIEWPORT_PAINT", ExecTest, ButtonUpdateBrush, buttonRect, 0 );

  // Init camera
  camera = CreateEntity( "POINT", 0, 0 );
  GlobalCamInit( 0, 0, camera );

  // Set up scroll bars
  verticalScroller.x_ = 16;
  horizontalScroller.y_ = 1;
  camBound.center_.x_ = (float)TILE_MAP_SYSTEM.MAP_WIDTH / 2.f + VIEWPORT_OFFSET_X;
  camBound.center_.y_ = (float)TILE_MAP_SYSTEM.MAP_HEIGHT / 2.f + VIEWPORT_OFFSET_Y;
  camBound.width_ = (float)TILE_MAP_SYSTEM.MAP_WIDTH;
  camBound.height_ = (float)TILE_MAP_SYSTEM.MAP_HEIGHT;
  SnapVectorToRect( &origin, &camBound );
  
  return RETURN_SUCCESS;
}

RETURN_TYPE MapEditorUpdate( void )
{
  VECTOR2D vel = { 0 }, pos = { 0 };
  float dt = GetDT( );
  float conv = 0;
  SendEntityMessage( camera, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );

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

  if(IsKeyPressed( VK_UP ))
  {
    vel.y_ = -VIEWPORT_SCROLL_SPEED;
    SendEntityMessage( camera, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
  }

  if(IsKeyPressed( VK_DOWN ))
  {
    vel.y_ = VIEWPORT_SCROLL_SPEED;
    SendEntityMessage( camera, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
  }

  if(IsKeyPressed( VK_LEFT ))
  {
    vel.x_ = -VIEWPORT_SCROLL_SPEED;
    SendEntityMessage( camera, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
  }

  if(IsKeyPressed( VK_RIGHT ))
  {
    vel.x_ = VIEWPORT_SCROLL_SPEED;
    SendEntityMessage( camera, EM_SETVEL, (int)&vel.x_, (int)&vel.y_ );
  }

  UpdateButtons( dt );

  // Update camera
  SendEntityMessage( camera, EM_UPDATE, (int)&dt, 0 );
  SendEntityMessage( camera, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  SnapVectorToRect( &pos, &camBound );
  SendEntityMessage( camera, EM_SETPOS, (int)&pos.x_, (int)&pos.y_ );
  GlobalCamUpdate( dt );
  
  // Update scroll bars
  SendEntityMessage( camera, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  verticalScroller.y_ = FloatToIntRoundUp( (float)fabs(origin.y_ - pos.y_) /
    (float)TILE_MAP_SYSTEM.MAP_HEIGHT * VIEWPORT_HEIGHT + 2.0f );
  horizontalScroller.x_ = FloatToIntRoundUp( (float)fabs(origin.x_ - pos.x_) /
    (float)TILE_MAP_SYSTEM.MAP_WIDTH * (VIEWPORT_WIDTH - 2.0f) + 17.0f );

  return RETURN_SUCCESS;
}

RETURN_TYPE MapEditorDraw( void )
{
  int i = 0;
  ClearBuffer( );
  
  // draws all active entitys
  DrawEntities( );

  // draw map editor UI
  WriteImageToScreenNoCam( "MapEditorMockup.AEArt", 0, 0 );
  WriteImageToScreenNoCam( "BlueSquare.AEArt", verticalScroller.x_, verticalScroller.y_ );
  WriteImageToScreenNoCam( "BlueSquare.AEArt", verticalScroller.x_ + (int)VIEWPORT_WIDTH, verticalScroller.y_ );
  WriteImageToScreenNoCam( "BlueSquare.AEArt", horizontalScroller.x_, horizontalScroller.y_ );
  WriteImageToScreenNoCam( "BlueSquare.AEArt", horizontalScroller.x_, horizontalScroller.y_ + (int)VIEWPORT_HEIGHT + 2 );

  while(ENTITY_TYPES[i])
  {
    WriteStringToScreenNoCam( ENTITY_TYPES[i], 3, 17 + i );
    ++i;
  }

  RenderScreen( ); // Renders the DOUBLE_BUFFER to the screen
  return RETURN_SUCCESS;
}

RETURN_TYPE MapEditorFree( void )
{
  //SerializeAllEntities( "../MapAssets/MapEditorSave.txt" );
  
  // Frees all entitys within the EntityFactory system
  LIST_DESTROY( P_ENTITY, ENTITY_LIST );
  LIST_DESTROY( P_BUTTON, BUTTON_LIST );

  // Reset camera for next state
  GlobalCamDisable( );
  return RETURN_SUCCESS;
}

RETURN_TYPE MapEditorUnload( void )
{
  return RETURN_SUCCESS;
}
