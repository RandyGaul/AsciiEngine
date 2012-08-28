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
#include "GlobalDefines.h"

// These three states are global variables for holding the values of states.
stateIndicator nextState;
stateIndicator previousState;
stateIndicator currentState;

// Globals for function pointers for any state. To point at functions in other files.
RETURN_TYPE (*Load)( void );
RETURN_TYPE (*Initialize)( void );
RETURN_TYPE (*Update)( );
RETURN_TYPE (*Draw)( void );
RETURN_TYPE (*Free)( void );
RETURN_TYPE (*Unload)( void );

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
	case TestLevel:
		Load = &TestLevelLoad;
		Initialize = &TestLevelInit;
		Update = &TestLevelUpdate;
		Draw = &TestLevelDraw;
		Free = &TestLevelFree;
		Unload = &TestLevelUnload;
		break;
	case TestLevel2:
		Load = &TestLevel2Load;
		Initialize = &TestLevel2Init;
		Update = &TestLevel2Update;
		Draw = &TestLevel2Draw;
		Free = &TestLevel2Free;
		Unload = &TestLevel2Unload;
		break;
	case MapEditor:
		Load = &MapEditorLoad;
		Initialize = &MapEditorInit;
		Update = &MapEditorUpdate;
		Draw = &MapEditorDraw;
		Free = &MapEditorFree;
		Unload = &MapEditorUnload;
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