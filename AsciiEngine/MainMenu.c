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
#include "Input.h"
#include "Graphics.h"
#include "Random.h"
#include "ConsoleFuncs.h"
#include "FrameRateController.h"
#include "TileMap.h"

// Allows for management of GameObjects without including
// all the various game object headers to this file
#include "ObjectFactory.h"

int MainMenuLoad( void )
{
  AE_CreateObject( GO_REDSQUARE );
  MapSystemInit( "TEST_MAP.txt" );
	return RETURN_SUCCESS;
}

int MainMenuInitialize( void )
{
  // Run the default initializer on all objects, any custom
  // initialization of an object will use the object's set
  // function, and should be done after this function call.
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