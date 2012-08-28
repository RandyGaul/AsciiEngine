////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "GlobalDefines.h"
#include "ConsoleFuncs.h"
#include "Graphics.h"
#include "GameStateManager.h"
#include "FrameRateController.h"
#include "Input.h"
#include "Random.h"
#include "Registration.h" // Register entity classes and entity components

int main(void)
{
  // Initializes the graphics settings.
  InitGraphics( CLIENT_WIDTH, CLIENT_HEIGHT );

  // Initializes the console.
  // The first string is the name of your window. The second string is the
  // name of the font you want to use. Blank uses the default raster font,
  // though you can try strings "Lucida Console" or "Consolas" as they are
  // optional fonts in Windows 7 and Vista. A custom font can be created and
  // implemented if you're so inclined.
  initConsole(TEXT("Ascii Engine v1.02"), TEXT("Sunkure Font"), 8, 8 ); 

  // Seed PRNG
  // http://cecilsunkure.blogspot.com/2010/11/prngs-psuedo-random-number-generator.html
  InitRandSeed( );

  // Set the starting state
  // http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html
  GSM_Initialize( TestLevel );

  InitFrameRateController( );

  // Registration of creators to the creator table
  // http://cecilsunkure.blogspot.com/2012/08/game-object-factory-distributed-factory.html
  RegisterEntityClasses( );
  RegisterEntityComponents( );

	while (currentState != Quit)
	{
		if (currentState == Quit)
		{
			break;
		}

		if (currentState == Restart)
		{
			currentState = previousState;
			nextState = previousState;
		}
		else
		{
			GSM_Update( );
			Load( );
		}
    
		Initialize( );
		SetStateStartTime( );

		while (currentState == nextState)
		{
			FrameStart( ); // get time frame started

			UpdateInput( ); // Capture input

			for (;;)
			{
        assert(_CrtCheckMemory());
				SetDT( dtCalculate( ) ); // Set's dt for the function GetDT
				Update( ); // calculate change in time since last call, for update
				if (FPSLimit( ))
				{
					Draw( );
					break;
				}
			}
		}
		
		Free( );

		if (nextState == Restart)
		{
			previousState = currentState;
			currentState = nextState;
		}
		else
		{
			Unload( );
			previousState = currentState;
			currentState = nextState;
		}
	}

  return RETURN_SUCCESS;
}
