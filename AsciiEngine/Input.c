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

GlobalInputs GLOBAL_INPUTS = { 0 };

//
// IsKeyPressed
// Purpose: Checks to see if a specific key is pressed or not; returns BOOL
//
BOOL IsKeyPressed( VIRTUAL_KEY key )
{
  switch(key)
  {
    case VK_RETURN:
      return GLOBAL_INPUTS.Enter;
	  case VK_BACK:
      return GLOBAL_INPUTS.Backspace;
	  case VK_CONTROL:
      return GLOBAL_INPUTS.Control;
	  case VK_SHIFT:
      return GLOBAL_INPUTS.Shift;
	  case VK_UP:
      return GLOBAL_INPUTS.Arrow_Up;
	  case VK_LEFT:
      return GLOBAL_INPUTS.Arrow_Left;
	  case VK_DOWN:
      return GLOBAL_INPUTS.Arrow_Down;
	  case VK_RIGHT:
      return GLOBAL_INPUTS.Arrow_Right;
	  case VK_SPACE:
      return GLOBAL_INPUTS.Key_Space;
    case VK_LBUTTON:
      return GLOBAL_INPUTS.L_Button;
    case VK_RBUTTON:
      return GLOBAL_INPUTS.R_Button;
    default:
      return FALSE;
  }
}

//
// UpdateInput
// Purpose: Reads the console's input buffer and updates all keys within
// the GLOBAL_INPUTS struct
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
    
    // Loop through the events
    for (i_events = 0; i_events < numEventsRead; i_events++)
    {
      switch(eventBuffer[i_events].EventType)
      {
      case KEY_EVENT:
        if(eventBuffer[i_events].Event.KeyEvent.bKeyDown == TRUE)
        {
          switch (eventBuffer[i_events].Event.KeyEvent.wVirtualKeyCode)
          {
            case VK_RETURN:
					    GLOBAL_INPUTS.Enter = TRUE;
					    break;
				    case VK_BACK:
					    GLOBAL_INPUTS.Backspace = TRUE;
					    break;
				    case VK_CONTROL:
					    GLOBAL_INPUTS.Control = TRUE;
					    break;
				    case VK_SHIFT:
					    GLOBAL_INPUTS.Shift = TRUE;
					    break;
				    case VK_UP:
					    GLOBAL_INPUTS.Arrow_Up = TRUE;
					    break;
				    case VK_LEFT:
					    GLOBAL_INPUTS.Arrow_Left = TRUE;
					    break;
				    case VK_DOWN:
					    GLOBAL_INPUTS.Arrow_Down = TRUE;
					    break;
				    case VK_RIGHT:
					    GLOBAL_INPUTS.Arrow_Right = TRUE;
					    break;
				    case VK_SPACE:
					    GLOBAL_INPUTS.Key_Space = TRUE;
              break;
          }
        }
        else
        {
          switch (eventBuffer[i_events].Event.KeyEvent.wVirtualKeyCode)
          {
            case VK_RETURN:
					    GLOBAL_INPUTS.Enter = FALSE;
					    break;
				    case VK_BACK:
					    GLOBAL_INPUTS.Backspace = FALSE;
					    break;
				    case VK_CONTROL:
					    GLOBAL_INPUTS.Control = FALSE;
					    break;
				    case VK_SHIFT:
					    GLOBAL_INPUTS.Shift = FALSE;
					    break;
				    case VK_UP:
					    GLOBAL_INPUTS.Arrow_Up = FALSE;
					    break;
				    case VK_LEFT:
					    GLOBAL_INPUTS.Arrow_Left = FALSE;
					    break;
				    case VK_DOWN:
					    GLOBAL_INPUTS.Arrow_Down = FALSE;
					    break;
				    case VK_RIGHT:
					    GLOBAL_INPUTS.Arrow_Right = FALSE;
					    break;
				    case VK_SPACE:
					    GLOBAL_INPUTS.Key_Space = FALSE;
              break;
          }
        }
        break;
      case MOUSE_EVENT:
        GLOBAL_INPUTS.L_Button = eventBuffer[i_events].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;
        GLOBAL_INPUTS.R_Button = eventBuffer[i_events].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED;
        if( eventBuffer[i_events].Event.MouseEvent.dwEventFlags == MOUSE_MOVED )
        {
          GLOBAL_INPUTS.xPos = eventBuffer[i_events].Event.MouseEvent.dwMousePosition.X;
          GLOBAL_INPUTS.yPos = eventBuffer[i_events].Event.MouseEvent.dwMousePosition.Y;
        }
        if(GLOBAL_INPUTS.L_Button)
        {
          GLOBAL_INPUTS.xPosAtLastLeftClick = GLOBAL_INPUTS.xPos;
          GLOBAL_INPUTS.yPosAtLastLeftClick = GLOBAL_INPUTS.yPos;
        }
        if(GLOBAL_INPUTS.R_Button)
        {
          GLOBAL_INPUTS.xPosAtLastRightClick = GLOBAL_INPUTS.xPos;
          GLOBAL_INPUTS.yPosAtLastRightClick = GLOBAL_INPUTS.yPos;
        }
        break;
      }
    }
    FlushConsoleInputBuffer( INPUT_HANDLE );
    free( eventBuffer );
  }
}
