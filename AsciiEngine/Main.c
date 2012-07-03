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
#include "GameStateManager.h"
#include "FrameRateController.h"
#include "Input.h"
#include "Random.h"

int main(void)
{
  // Various initialization tasks such as graphics, setting up
  // the windows console, etc.
  // The first string is the name of your window. The second string is the
  // name of the font you want to use. Blank uses the default raster font,
  // though you can try strings "Lucida Console" or "Consolas" as they are
  // optional fonts in Windows 7 and Vista. A custom font can be created and
  // implemented if you're so inclined.
  initConsole(TEXT("AsciiEngine V1.00"), TEXT(""), 8, 8, 70, 30);

  // Seed PRNG
  // http://cecilsunkure.blogspot.com/2010/11/prngs-psuedo-random-number-generator.html
  InitRandSeed( );

  // Set the starting state
  // http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html
  GSM_Initialize( MainMenu );

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

			GetInput( ); // Capture input

			for (;;)
			{
				SetDT( dtCalculate( ) ); // Set's dt for the function GetDT
				Update( ); // calculate change in time since last call, for update
				DebounceAllKeys( );
				if (FPSLimit( TIME_BETWEEN_FRAMES_IN_MILLISECONDS ))
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
