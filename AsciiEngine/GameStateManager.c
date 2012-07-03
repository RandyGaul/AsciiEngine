////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file manages the states of the game
// Documentation: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#include "GameStateList.h"
#include "GameStateManager.h"
#include "MainMenu.h"
#include "GlobalDefines.h"

// These three states are global variables for holding the values of states.
stateIndicator nextState;
stateIndicator previousState;
stateIndicator currentState;

// Globals for function pointers for any state. To point at functions in other files.
int (*Load)( void );
int (*Initialize)( void );
int (*Update)( );
int (*Draw)( void );
int (*Free)( void );
int (*Unload)( void );

// Initialize the Game State Manager by pointing the three states at an initial state.
int GSM_Initialize( stateIndicator initVal )
{
	nextState = initVal;
	previousState = initVal;
	currentState = initVal;

	return RETURN_SUCCESS;
}

// Update the Game State Manager by syncing the three state indicators to their
// corresponding function pointers (all six of them).
int GSM_Update( void )
{
	switch(currentState)
	{
	case MainMenu:
		Load = &MainMenuLoad;
		Initialize = &MainMenuInitialize;
		Update = &MainMenuUpdate;
		Draw = &MainMenuDraw;
		Free = &MainMenuFree;
		Unload = &MainMenuUnload;
		break;
		/*
	case Template:
		Load = &Load;
		Initialize = &Initialize;
		Update = &Update;
		Draw = &Draw;
		Free = &Free;
		Unload = &Unload;
		break;*/
	case Restart:
		break;
	case Quit:
		break;
	}

	return RETURN_SUCCESS;
}