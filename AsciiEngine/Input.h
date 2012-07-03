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

void GetInput( void );
void DebounceAllKeys( void );
BOOL IsKeyPressed( VIRTUAL_KEY key );
BOOL IsAnyKeyPressed( VIRTUAL_KEY key );

#endif  INPUTH