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
    case VK_A:
      return GLOBAL_INPUTS.Key_A;
    case VK_B:
      return GLOBAL_INPUTS.Key_B;
    case VK_C:
      return GLOBAL_INPUTS.Key_C;
    case VK_D:
      return GLOBAL_INPUTS.Key_D;
    case VK_E:
      return GLOBAL_INPUTS.Key_E;
    case VK_F:
      return GLOBAL_INPUTS.Key_F;
    case VK_G:
      return GLOBAL_INPUTS.Key_G;
    case VK_H:
      return GLOBAL_INPUTS.Key_H;
    case VK_I:
      return GLOBAL_INPUTS.Key_I;
    case VK_J:
      return GLOBAL_INPUTS.Key_J;
    case VK_K:
      return GLOBAL_INPUTS.Key_K;
    case VK_L:
      return GLOBAL_INPUTS.Key_L;
    case VK_M:
      return GLOBAL_INPUTS.Key_M;
    case VK_N:
      return GLOBAL_INPUTS.Key_N;
    case VK_O:
      return GLOBAL_INPUTS.Key_O;
    case VK_P:
      return GLOBAL_INPUTS.Key_P;
    case VK_Q:
      return GLOBAL_INPUTS.Key_Q;
    case VK_R:
      return GLOBAL_INPUTS.Key_R;
    case VK_S:
      return GLOBAL_INPUTS.Key_S;
    case VK_T:
      return GLOBAL_INPUTS.Key_T;
    case VK_U:
      return GLOBAL_INPUTS.Key_U;
    case VK_V:
      return GLOBAL_INPUTS.Key_V;
    case VK_W:
      return GLOBAL_INPUTS.Key_W;
    case VK_X:
      return GLOBAL_INPUTS.Key_X;
    case VK_Y:
      return GLOBAL_INPUTS.Key_Y;
    case VK_Z:
      return GLOBAL_INPUTS.Key_Z;
      return GLOBAL_INPUTS.Key_I;
    case VK_0:
      return GLOBAL_INPUTS.Key_0;
    case VK_1:
      return GLOBAL_INPUTS.Key_1;
    case VK_2:
      return GLOBAL_INPUTS.Key_2;
    case VK_3:
      return GLOBAL_INPUTS.Key_3;
    case VK_4:
      return GLOBAL_INPUTS.Key_4;
    case VK_5:
      return GLOBAL_INPUTS.Key_5;
    case VK_6:
      return GLOBAL_INPUTS.Key_6;
    case VK_7:
      return GLOBAL_INPUTS.Key_7;
    case VK_8:
      return GLOBAL_INPUTS.Key_8;
    case VK_9:
      return GLOBAL_INPUTS.Key_9;
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
            case VK_A:
              GLOBAL_INPUTS.Key_A = TRUE;
              break;
            case VK_B:
              GLOBAL_INPUTS.Key_B = TRUE;
              break;
            case VK_C:
              GLOBAL_INPUTS.Key_C = TRUE;
              break;
            case VK_D:
              GLOBAL_INPUTS.Key_D = TRUE;
              break;
            case VK_E:
              GLOBAL_INPUTS.Key_E = TRUE;
              break;
            case VK_F:
              GLOBAL_INPUTS.Key_F = TRUE;
              break;
            case VK_G:
              GLOBAL_INPUTS.Key_G = TRUE;
              break;
            case VK_H:
              GLOBAL_INPUTS.Key_H = TRUE;
              break;
            case VK_I:
              GLOBAL_INPUTS.Key_I = TRUE;
              break;
            case VK_J:
              GLOBAL_INPUTS.Key_J = TRUE;
              break;
            case VK_K:
              GLOBAL_INPUTS.Key_K = TRUE;
              break;
            case VK_L:
              GLOBAL_INPUTS.Key_L = TRUE;
              break;
            case VK_M:
              GLOBAL_INPUTS.Key_M = TRUE;
              break;
            case VK_N:
              GLOBAL_INPUTS.Key_N = TRUE;
              break;
            case VK_O:
              GLOBAL_INPUTS.Key_O = TRUE;
              break;
            case VK_P:
              GLOBAL_INPUTS.Key_P = TRUE;
              break;
            case VK_Q:
              GLOBAL_INPUTS.Key_Q = TRUE;
              break;
            case VK_R:
              GLOBAL_INPUTS.Key_R = TRUE;
              break;
            case VK_S:
              GLOBAL_INPUTS.Key_S = TRUE;
              break;
            case VK_T:
              GLOBAL_INPUTS.Key_T = TRUE;
              break;
            case VK_U:
              GLOBAL_INPUTS.Key_U = TRUE;
              break;
            case VK_V:
              GLOBAL_INPUTS.Key_V = TRUE;
              break;
            case VK_W:
              GLOBAL_INPUTS.Key_W = TRUE;
              break;
            case VK_X:
              GLOBAL_INPUTS.Key_X = TRUE;
              break;
            case VK_Y:
              GLOBAL_INPUTS.Key_Y = TRUE;
              break;
            case VK_Z:
              GLOBAL_INPUTS.Key_Z = TRUE;
              break;
            case VK_0:
              GLOBAL_INPUTS.Key_0 = TRUE;
              break;
            case VK_1:
              GLOBAL_INPUTS.Key_1 = TRUE;
              break;
            case VK_2:
              GLOBAL_INPUTS.Key_2 = TRUE;
              break;
            case VK_3:
              GLOBAL_INPUTS.Key_3 = TRUE;
              break;
            case VK_4:
              GLOBAL_INPUTS.Key_4 = TRUE;
              break;
            case VK_5:
              GLOBAL_INPUTS.Key_5 = TRUE;
              break;
            case VK_6:
              GLOBAL_INPUTS.Key_6 = TRUE;
              break;
            case VK_7:
              GLOBAL_INPUTS.Key_7 = TRUE;
              break;
            case VK_8:
              GLOBAL_INPUTS.Key_8 = TRUE;
              break;
            case VK_9:
              GLOBAL_INPUTS.Key_9 = TRUE;
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
              break;case VK_A:
              GLOBAL_INPUTS.Key_A = FALSE;
              break;
            case VK_B:
              GLOBAL_INPUTS.Key_B = FALSE;
              break;
            case VK_C:
              GLOBAL_INPUTS.Key_C = FALSE;
              break;
            case VK_D:
              GLOBAL_INPUTS.Key_D = FALSE;
              break;
            case VK_E:
              GLOBAL_INPUTS.Key_E = FALSE;
              break;
            case VK_F:
              GLOBAL_INPUTS.Key_F = FALSE;
              break;
            case VK_G:
              GLOBAL_INPUTS.Key_G = FALSE;
              break;
            case VK_H:
              GLOBAL_INPUTS.Key_H = FALSE;
              break;
            case VK_I:
              GLOBAL_INPUTS.Key_I = FALSE;
              break;
            case VK_J:
              GLOBAL_INPUTS.Key_J = FALSE;
              break;
            case VK_K:
              GLOBAL_INPUTS.Key_K = FALSE;
              break;
            case VK_L:
              GLOBAL_INPUTS.Key_L = FALSE;
              break;
            case VK_M:
              GLOBAL_INPUTS.Key_M = FALSE;
              break;
            case VK_N:
              GLOBAL_INPUTS.Key_N = FALSE;
              break;
            case VK_O:
              GLOBAL_INPUTS.Key_O = FALSE;
              break;
            case VK_P:
              GLOBAL_INPUTS.Key_P = FALSE;
              break;
            case VK_Q:
              GLOBAL_INPUTS.Key_Q = FALSE;
              break;
            case VK_R:
              GLOBAL_INPUTS.Key_R = FALSE;
              break;
            case VK_S:
              GLOBAL_INPUTS.Key_S = FALSE;
              break;
            case VK_T:
              GLOBAL_INPUTS.Key_T = FALSE;
              break;
            case VK_U:
              GLOBAL_INPUTS.Key_U = FALSE;
              break;
            case VK_V:
              GLOBAL_INPUTS.Key_V = FALSE;
              break;
            case VK_W:
              GLOBAL_INPUTS.Key_W = FALSE;
              break;
            case VK_X:
              GLOBAL_INPUTS.Key_X = FALSE;
              break;
            case VK_Y:
              GLOBAL_INPUTS.Key_Y = FALSE;
              break;
            case VK_Z:
              GLOBAL_INPUTS.Key_Z = FALSE;
              break;
            case VK_0:
              GLOBAL_INPUTS.Key_0 = FALSE;
              break;
            case VK_1:
              GLOBAL_INPUTS.Key_1 = FALSE;
              break;
            case VK_2:
              GLOBAL_INPUTS.Key_2 = FALSE;
              break;
            case VK_3:
              GLOBAL_INPUTS.Key_3 = FALSE;
              break;
            case VK_4:
              GLOBAL_INPUTS.Key_4 = FALSE;
              break;
            case VK_5:
              GLOBAL_INPUTS.Key_5 = FALSE;
              break;
            case VK_6:
              GLOBAL_INPUTS.Key_6 = FALSE;
              break;
            case VK_7:
              GLOBAL_INPUTS.Key_7 = FALSE;
              break;
            case VK_8:
              GLOBAL_INPUTS.Key_8 = FALSE;
              break;
            case VK_9:
              GLOBAL_INPUTS.Key_9 = FALSE;
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

void ClearLastMouseClick( void )
{
  GLOBAL_INPUTS.xPosAtLastRightClick = -1;
  GLOBAL_INPUTS.yPosAtLastRightClick = -1;
}
