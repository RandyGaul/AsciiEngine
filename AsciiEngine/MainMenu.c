////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// The various functions for a demonstration state called "MainMenu"
// The MainMenu state isn't actually a menu though...
// More information: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#include <stdio.h>
#include <stdlib.h>

#include "GameStateManager.h"
#include "GameStateList.h"
#include "GlobalDefines.h"
#include "Random.h"
#include "FrameRateController.h"
#include "TileMap.h"          // Various tile mapping functions
#include "Graphics.h"         // Various graphics functions
#include "Input.h"            // Various input functions
#include "ConsoleFuncs.h"     // RenderScreen;
#include "ObjectFactory.h"    // GameObject management system
#include "OpenFile.h"         // LoadAllArtAssets;

// Allows for management of GameObjects without including
// all the various game object headers to this file
#include "ObjectFactory.h"

int MainMenuLoad( void )
{
  MapSystemInit( "../MapAssets/TEST_MAP.txt" );
  LoadAllArtAssets( "../ArtAssets/" );
	return RETURN_SUCCESS;
}

int MainMenuInitialize( void )
{
  // Run the default initializer on all objects, any custom
  // initialization of an object will use the object's set
  // function, and should be done after this function call.
  AE_CreateObject( GO_REDSQUARE );
  AE_InitObjects( );
	return RETURN_SUCCESS;
}

int MainMenuUpdate( void )
{
  // You should use dt in this form whenever you require it
  float dt = GetDT( );
  ClearBuffer( ); // Clears the DOUBLE_BUFFER for redraw

  // Run all objects' update functions.
  AE_UpdateObjects( );
	return RETURN_SUCCESS;
}

int MainMenuDraw( )
{
  DrawMap( ); // draws tiles

  // Demonstration of mouse input
  if(IsKeyPressed( VK_LBUTTON ))
  {
    WriteImageToScreen( "WhiteSquare.AEArt", GLOBAL_INPUTS.xPosAtLastLeftClick, GLOBAL_INPUTS.yPosAtLastLeftClick );
  }
  if(IsKeyPressed( VK_RBUTTON ))
  {
    WriteImageToScreen( "BlueSquare.AEArt", GLOBAL_INPUTS.xPosAtLastRightClick, GLOBAL_INPUTS.yPosAtLastRightClick );
  }

  AE_DrawObjects( ); // draws all active objects
  // Renders the double buffer to the screen, only call this once per game loop!
  RenderScreen( );
	return RETURN_SUCCESS;
}

int MainMenuFree( void )
{
  AE_DestroyObjects( );
	return RETURN_SUCCESS;
}

int MainMenuUnload( void )
{
	return RETURN_SUCCESS;
}