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

struct
{
	BOOL L_Button; // Mouse
	BOOL R_Button; // Mouse
	BOOL xPos; // Mouse (within window)
	BOOL yPos; // Mouse (within window)
	BOOL xPosAtLastClick; // x position of cursor relative to draw area (client rect) during last left or right click
	BOOL yPosAtLastClick; // y position of cursor relative to draw area (client rect) during last left or right click
} MouseGlobals = { 0 };

//  
//  Structure containing all the keys, refer to these in the program to see if something is
//  pressed or not.
//  
struct
{
	BOOL Key_A;
	BOOL Key_B;
	BOOL Key_C;
	BOOL Key_D;
	BOOL Key_E;
	BOOL Key_F;
	BOOL Key_G;
	BOOL Key_H;
	BOOL Key_I;
	BOOL Key_J;
	BOOL Key_K;
	BOOL Key_L;
	BOOL Key_M;
	BOOL Key_N;
	BOOL Key_O;
	BOOL Key_P;
	BOOL Key_Q;
	BOOL Key_R;
	BOOL Key_S;
	BOOL Key_T;
	BOOL Key_U;
	BOOL Key_V;
	BOOL Key_W;
	BOOL Key_X;
	BOOL Key_Y;
	BOOL Key_Z;
	BOOL Key_1;
	BOOL Key_2;
	BOOL Key_3;
	BOOL Key_4;
	BOOL Key_5;
	BOOL Key_6;
	BOOL Key_7;
	BOOL Key_8;
	BOOL Key_9;
	BOOL Key_0;
	BOOL Key_Space;
	BOOL Key_Ctrl;
	BOOL Key_Shift;
	BOOL Arrow_Up;
	BOOL Arrow_Left;
	BOOL Arrow_Down;
	BOOL Arrow_Right;
	BOOL Control;
	BOOL Backspace;
	BOOL Shift;
	BOOL Enter;
} GlobalInputs = { 0 };

//
// IsKeyPressed
// Purpose: Checks to see if a specific key is pressed or not; returns BOOL
//
BOOL IsKeyPressed( VIRTUAL_KEY key )
{
  switch(key)
  {
    case VK_RETURN:
      return GlobalInputs.Enter;
	  case VK_BACK:
      return GlobalInputs.Backspace;
	  case VK_CONTROL:
      return GlobalInputs.Control;
	  case VK_SHIFT:
      return GlobalInputs.Shift;
	  case VK_UP:
      return GlobalInputs.Arrow_Up;
	  case VK_LEFT:
      return GlobalInputs.Arrow_Left;
	  case VK_DOWN:
      return GlobalInputs.Arrow_Down;
	  case VK_RIGHT:
      return GlobalInputs.Arrow_Right;
	  case VK_SPACE:
      return GlobalInputs.Key_Space;
    default:
      return TRUE;
  }
}

//
// UpdateInput
// Purpose: Reads the console's input buffer and updates all keys within
// the GlobalInputs struct
//
void UpdateInput( void )
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
    PeekConsoleInput(INPUT_HANDLE, eventBuffer, numEvents, pnumEventsRead);
    
    for (i_events = 0; i_events < numEventsRead; i_events++)
    {
      if (eventBuffer[i_events].EventType == 1 && eventBuffer[i_events].Event.KeyEvent.bKeyDown == TRUE)
      {
        switch (eventBuffer[i_events].Event.KeyEvent.wVirtualKeyCode)
        {
          case VK_RETURN:
					  GlobalInputs.Enter = TRUE;
					  break;
				  case VK_BACK:
					  GlobalInputs.Backspace = TRUE;
					  break;
				  case VK_CONTROL:
					  GlobalInputs.Control = TRUE;
					  break;
				  case VK_SHIFT:
					  GlobalInputs.Shift = TRUE;
					  break;
				  case VK_UP:
					  GlobalInputs.Arrow_Up = TRUE;
					  break;
				  case VK_LEFT:
					  GlobalInputs.Arrow_Left = TRUE;
					  break;
				  case VK_DOWN:
					  GlobalInputs.Arrow_Down = TRUE;
					  break;
				  case VK_RIGHT:
					  GlobalInputs.Arrow_Right = TRUE;
					  break;
				  case VK_SPACE:
					  GlobalInputs.Key_Space = TRUE;
            break;
        }
      }
      else
      {
        switch (eventBuffer[i_events].Event.KeyEvent.wVirtualKeyCode)
        {
          case VK_RETURN:
					  GlobalInputs.Enter = FALSE;
					  break;
				  case VK_BACK:
					  GlobalInputs.Backspace = FALSE;
					  break;
				  case VK_CONTROL:
					  GlobalInputs.Control = FALSE;
					  break;
				  case VK_SHIFT:
					  GlobalInputs.Shift = FALSE;
					  break;
				  case VK_UP:
					  GlobalInputs.Arrow_Up = FALSE;
					  break;
				  case VK_LEFT:
					  GlobalInputs.Arrow_Left = FALSE;
					  break;
				  case VK_DOWN:
					  GlobalInputs.Arrow_Down = FALSE;
					  break;
				  case VK_RIGHT:
					  GlobalInputs.Arrow_Right = FALSE;
					  break;
				  case VK_SPACE:
					  GlobalInputs.Key_Space = FALSE;
            break;
        }
      }
    }
    FlushConsoleInputBuffer( INPUT_HANDLE );
    free( eventBuffer );
  }
}
