////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2011/11/windows-console-game-event-handling.html

#ifndef INPUTH
#define INPUTH

typedef int VIRTUAL_KEY;

//
// UpdateInput
// Purpose: Reads the console's input buffer and updates all keys within
// the GlobalInputs struct
//
void UpdateInput( void );

//
// IsKeyPressed
// Purpose: Checks to see if a specific key is pressed or not; returns BOOL
//
BOOL IsKeyPressed( VIRTUAL_KEY key );

#endif  INPUTH