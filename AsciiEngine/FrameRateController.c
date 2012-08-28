////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include "GlobalDefines.h" // DT_MAX
#include "FrameRateController.h"

float previousTime;
float timeAtFrameStart;
float stateStartTime;
LARGE_INTEGER FREQUENCY;
float F_FREQUENCY = 1.0f / FPS_LIMIT; // Used to limit FPS
int firstRun = 1; // to see if the application just started
static float dt;

//
// SetDT
// Purpose: Sets DT to a specific value
//
void SetDT( float deltaTime )
{
  dt = deltaTime;
}
void dtCap( float *dt );

//
// GetDT
// Purpose: Retrieves and caps the current DT
//
float GetDT( void )
{
  dtCap( &dt );
  return dt;
}

//
// GetTimeAtFrameStart
// Purpose: Retrieves the current game time at frame start in high resolution seconds
//
float GetTimeAtFrameStart( void )
{
  return timeAtFrameStart;
}

//
// GetCurrentGameTime
// Purpose: Retrieves the current game time in high resolution seconds
//
float GetCurrentGameTime( void )
{
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter( &currentTime );
  return (float)(currentTime.QuadPart) / (float)(FREQUENCY.QuadPart);
}

//  
//  Name: SetStateStartTime
//  Purpose: Records the time at function call.
// 
void SetStateStartTime( void )
{
	stateStartTime = GetCurrentGameTime( );
}

//  
//  Name: GetStateStartTime
//  Purpose: Returns the recorded state start time.
// 
float GetStateStartTime( void )
{
	return stateStartTime;
}

//  
//  Name: FrameStart
//  Purpose: Catch the time of when the frame first starts
// 
void FrameStart( void )
{
	timeAtFrameStart = GetCurrentGameTime( );
}

//  
//  Name: dtCalculate
//  Purpose: Calculates the change in time since the last calculation of dt
// 
float dtCalculate( )
{
	float currentTime = GetCurrentGameTime( );  // record current time
	float dt = currentTime - previousTime;      // calculate dt
	previousTime = currentTime;                 // set previousTime for the next call
	
	if(firstRun)
	{
		dt = 0.f;
		firstRun = 0;
	}
	return dt;
}

//  
//  Name: dtCap
//  Purpose: Caps dt to a specified amount. This ensures that a really
//           huge timestep won't occur of the computer lags, or the window
//           is paused.
// 
void dtCap( float *dt )
{
	if(dt)
	{
		if(*dt > F_FREQUENCY)
		{
			*dt = F_FREQUENCY;
		}
	}
}

//  
//  Name: FPSLimit
//  Purpose: Limit the FPS in terms of drawing to a specific speed
//  Parameters: FPS - Max amount of frames per second
// 
BOOL FPSLimit( void )
{
	enum
	{
		DONTDRAW,
		DRAW
	};

	if (GetCurrentGameTime( ) - timeAtFrameStart < F_FREQUENCY) // If we are not over our threshold
	{
		return DONTDRAW;
	}
	else
	{
		return DRAW;
	}
}

//
// InitFrameRateController
// Purpose: Initializes various values for the framerate controller
//
RETURN_TYPE InitFrameRateController( void )
{
  F_FREQUENCY = (float)((int)(F_FREQUENCY * 1000.0f)) / 1000.0f;
  return QueryPerformanceFrequency( &FREQUENCY );
}