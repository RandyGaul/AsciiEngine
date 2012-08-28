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
//  Structure containing all the keys, refer to these in the program to see if something is
//  pressed or not.
//  
typedef struct
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
	BOOL L_Button; // Mouse
	BOOL R_Button; // Mouse
	int xPos; // Mouse (within window)
	int yPos; // Mouse (within window)
	int xPosAtLastLeftClick; // x position of cursor relative to draw area during last left or right click
	int yPosAtLastLeftClick; // y position of cursor relative to draw area during last left or right click
	int xPosAtLastRightClick; // x position of cursor relative to draw area during last left or right click
	int yPosAtLastRightClick; // y position of cursor relative to draw area during last left or right click
} GlobalInputs;

extern GlobalInputs GLOBAL_INPUTS;

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

void ClearLastMouseClick( void );

#endif  INPUTH