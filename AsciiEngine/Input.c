////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file handles all input. Support for more buttons and various
// tasks (like mouse coordinates or clicking) can easily be added.
// Documentation: http://cecilsunkure.blogspot.com/2011/11/windows-console-game-event-handling.html

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "GlobalDefines.h"
#include "ConsoleFuncs.h"
#include "Input.h"

// Various KeyStates
enum KEY_STATES
{
	RELEASED,
	PRESSED,
	HELDDOWN
};

// Debounce keystrokes
#define PressedDebounce( key ) \
	key = RELEASED

// Flag for the any key
static int anyKey = RELEASED;

struct
{
	int L_Button; // Mouse
	int R_Button; // Mouse
	int xPos; // Mouse (within window)
	int yPos; // Mouse (within window)
	int xPosAtLastClick; // x position of cursor relative to draw area (client rect) during last left or right click
	int yPosAtLastClick; // y position of cursor relative to draw area (client rect) during last left or right click
} MouseGlobals = { 0 };

//  
//  Structure containing all the keys, refer to these in the program to see if something is
//  pressed or not.
//  
struct
{
	int Key_A;
	int Key_B;
	int Key_C;
	int Key_D;
	int Key_E;
	int Key_F;
	int Key_G;
	int Key_H;
	int Key_I;
	int Key_J;
	int Key_K;
	int Key_L;
	int Key_M;
	int Key_N;
	int Key_O;
	int Key_P;
	int Key_Q;
	int Key_R;
	int Key_S;
	int Key_T;
	int Key_U;
	int Key_V;
	int Key_W;
	int Key_X;
	int Key_Y;
	int Key_Z;
	int Key_1;
	int Key_2;
	int Key_3;
	int Key_4;
	int Key_5;
	int Key_6;
	int Key_7;
	int Key_8;
	int Key_9;
	int Key_0;
	int Key_Space;
	int Key_Ctrl;
	int Key_Shift;
	int Arrow_Up;
	int Arrow_Left;
	int Arrow_Down;
	int Arrow_Right;
	int Control;
	int Backspace;
	int Shift;
	int Enter;
} GlobalInputs = { 0 };

BOOL IsKeyPressed( VIRTUAL_KEY key )
{
  switch(key)
  {
    case VK_RETURN:
      return (GlobalInputs.Enter == PRESSED || GlobalInputs.Enter == HELDDOWN) ? TRUE : FALSE;
	  case VK_BACK:
      return (GlobalInputs.Backspace == PRESSED || GlobalInputs.Backspace == HELDDOWN) ? TRUE : FALSE;
	  case VK_CONTROL:
      return (GlobalInputs.Control == PRESSED || GlobalInputs.Control == HELDDOWN) ? TRUE : FALSE;
	  case VK_SHIFT:
      return (GlobalInputs.Shift == PRESSED || GlobalInputs.Shift == HELDDOWN) ? TRUE : FALSE;
	  case VK_UP:
      return (GlobalInputs.Arrow_Up == PRESSED || GlobalInputs.Arrow_Up == HELDDOWN) ? TRUE : FALSE;
	  case VK_LEFT:
      return (GlobalInputs.Arrow_Left == PRESSED || GlobalInputs.Arrow_Left == HELDDOWN) ? TRUE : FALSE;
	  case VK_DOWN:
      return (GlobalInputs.Arrow_Down == PRESSED || GlobalInputs.Arrow_Down == HELDDOWN) ? TRUE : FALSE;
	  case VK_RIGHT:
      return (GlobalInputs.Arrow_Right == PRESSED || GlobalInputs.Arrow_Right == HELDDOWN) ? TRUE : FALSE;
	  case VK_SPACE:
      return (GlobalInputs.Key_Space == PRESSED || GlobalInputs.Key_Space == HELDDOWN) ? TRUE : FALSE;
    default:
      return TRUE;
  }
}

//  
//  Name:       DebounceAllKeys
//  Purpose:    Debounces all of the keys so multiple presses are not detected (spammed)
//  
void DebounceAllKeys( void )
{
	PressedDebounce( GlobalInputs.Key_A );
	PressedDebounce( GlobalInputs.Key_B );
	PressedDebounce( GlobalInputs.Key_C );
	PressedDebounce( GlobalInputs.Key_D );
	PressedDebounce( GlobalInputs.Key_E );
	PressedDebounce( GlobalInputs.Key_F );
	PressedDebounce( GlobalInputs.Key_G );
	PressedDebounce( GlobalInputs.Key_H );
	PressedDebounce( GlobalInputs.Key_I );
	PressedDebounce( GlobalInputs.Key_J );
	PressedDebounce( GlobalInputs.Key_K );
	PressedDebounce( GlobalInputs.Key_L );
	PressedDebounce( GlobalInputs.Key_M );
	PressedDebounce( GlobalInputs.Key_N );
	PressedDebounce( GlobalInputs.Key_O );
	PressedDebounce( GlobalInputs.Key_P );
	PressedDebounce( GlobalInputs.Key_Q );
	PressedDebounce( GlobalInputs.Key_R );
	PressedDebounce( GlobalInputs.Key_S );
	PressedDebounce( GlobalInputs.Key_T );
	PressedDebounce( GlobalInputs.Key_U );
	PressedDebounce( GlobalInputs.Key_V );
	PressedDebounce( GlobalInputs.Key_W );
	PressedDebounce( GlobalInputs.Key_X );
	PressedDebounce( GlobalInputs.Key_Y );
	PressedDebounce( GlobalInputs.Key_Z );
	PressedDebounce( GlobalInputs.Key_1 );
	PressedDebounce( GlobalInputs.Key_2 );
	PressedDebounce( GlobalInputs.Key_3 );
	PressedDebounce( GlobalInputs.Key_4 );
	PressedDebounce( GlobalInputs.Key_5 );
	PressedDebounce( GlobalInputs.Key_6 );
	PressedDebounce( GlobalInputs.Key_7 );
	PressedDebounce( GlobalInputs.Key_8 );
	PressedDebounce( GlobalInputs.Key_9 );
	PressedDebounce( GlobalInputs.Key_0 );
	PressedDebounce( GlobalInputs.Key_Space );
	PressedDebounce( GlobalInputs.Key_Ctrl );
	PressedDebounce( GlobalInputs.Key_Shift );
	PressedDebounce( GlobalInputs.Arrow_Up );
	PressedDebounce( GlobalInputs.Arrow_Left );
	PressedDebounce( GlobalInputs.Arrow_Down );
	PressedDebounce( GlobalInputs.Arrow_Right );
	PressedDebounce( GlobalInputs.Control );
	PressedDebounce( GlobalInputs.Backspace );
	PressedDebounce( GlobalInputs.Shift );
	PressedDebounce( GlobalInputs.Enter );
	PressedDebounce( anyKey );
	PressedDebounce( MouseGlobals.L_Button ); // Mouse
	PressedDebounce( MouseGlobals.R_Button ); // Mouse
}

// Reads the console's input buffer and updates all keys within the GlobalInputs struct
void GetInput( void )
{
  /* Iterator used to read through a record of events obtained from the console buffer */
  DWORD i_events;
  
  /* Variable for holding the number of current events, and a point to it */
  DWORD numEvents = 0, *pnumEvents = &numEvents, numEventsRead = 0, *pnumEventsRead = &numEventsRead;
  
  /* Pointer used to dynamically allocate space for an array of input records obtained from the console buffer */
  INPUT_RECORD *eventBuffer;
  
  GetNumberOfConsoleInputEvents(INPUT_HANDLE, pnumEvents);
  
  if (numEvents != 0)
  {
    eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);
    ReadConsoleInput(INPUT_HANDLE, eventBuffer, numEvents, pnumEventsRead);
    
    for (i_events = 0; i_events < numEventsRead; i_events++)
    {
      if (eventBuffer[i_events].EventType == 1 && eventBuffer[i_events].Event.KeyEvent.bKeyDown == 1)
      {
        switch (eventBuffer[i_events].Event.KeyEvent.wVirtualKeyCode)
        {
          case VK_RETURN:
					  GlobalInputs.Enter = PRESSED;
					  break;
				  case VK_BACK:
					  GlobalInputs.Backspace = PRESSED;
					  break;
				  case VK_CONTROL:
					  GlobalInputs.Control = PRESSED;
					  break;
				  case VK_SHIFT:
					  GlobalInputs.Shift = PRESSED;
					  break;
				  case VK_UP:
					  GlobalInputs.Arrow_Up = PRESSED;
					  break;
				  case VK_LEFT:
					  GlobalInputs.Arrow_Left = PRESSED;
					  break;
				  case VK_DOWN:
					  GlobalInputs.Arrow_Down = PRESSED;
					  break;
				  case VK_RIGHT:
					  GlobalInputs.Arrow_Right = PRESSED;
					  break;
				  case VK_SPACE:
					  GlobalInputs.Key_Space = PRESSED;
            break;
        }
      }
    }
    free(eventBuffer);
  }
}
