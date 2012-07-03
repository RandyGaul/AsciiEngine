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

typedef unsigned int millisecond;

void FrameStart( void );
float dtCalculate( void );
int FPSLimit( unsigned int FPS );
void dtCap( float *dt );
void SetStateStartTime( void );
unsigned int GetStateStartTime( void );
void SetDT( float deltaTime );
float GetDT( void );

#endif  FRAMERATECONTROLLERH