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

millisecond previousTime;
millisecond timeAtFrameStart;
millisecond stateStartTime = -1;
int firstRun = 1; // to see if the application just started
static float dt;

void SetDT( float deltaTime )
{
  dt = deltaTime;
}
void dtCap( float *dt );

float GetDT( void )
{
  dtCap( &dt );
  return dt;
}

//  
//  Name: SetStateStartTime
//  Purpose: Records the time at function call.
// 
void SetStateStartTime( void )
{
	stateStartTime = timeGetTime( );
}

//  
//  Name: GetStateStartTime
//  Purpose: Returns the recorded state start time.
// 
millisecond GetStateStartTime( void )
{
	return stateStartTime;
}

//  
//  Name: FrameStart
//  Purpose: Catch the time of when the frame first starts
// 
void FrameStart( void )
{
	timeAtFrameStart = timeGetTime( );
}

//  
//  Name: dtCalculate
//  Purpose: Calculates the change in time since the last calculation of dt
// 
float dtCalculate( )
{
	millisecond currentTime = (millisecond)timeGetTime(); // record current time
	float dt = (float)(currentTime - previousTime); // calculate dt
	previousTime = currentTime; // set previousTime for the next call
	
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
		if(*dt > DT_MAX)
		{
			*dt = DT_MAX;
		}
	}
}

//  
//  Name: FPSLimit
//  Purpose: Limit the FPS in terms of drawing to a specific speed
//  Parameters: FPS - Amount of milliseconds to wait for
// 
int FPSLimit( millisecond FPS )
{
	enum
	{
		DONTDRAW,
		DRAW
	};

	if (timeGetTime( ) - timeAtFrameStart > FPS) // If we are not over our threshold
	{
		return DONTDRAW;
	}
	else
	{
		return DRAW;
	}
}