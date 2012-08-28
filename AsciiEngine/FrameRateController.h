////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#ifndef FRAMERATECONTROLLERH
#define FRAMERATECONTROLLERH

#include "GlobalDefines.h"

void FrameStart( void );
float dtCalculate( void );
BOOL FPSLimit( void );
void dtCap( float *dt );
void SetStateStartTime( void );
float GetStateStartTime( void );
void SetDT( float deltaTime );
float GetDT( void );
float GetTimeAtFrameStart( void );
float GetCurrentGameTime( void );
RETURN_TYPE InitFrameRateController( void );

#endif  FRAMERATECONTROLLERH