////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "GlobalDefines.h"
#include "LinkedList.h"
#include "Shapes.h"

// Pause time defines in seconds
#define STANDARD_BUTTON_DEBOUNCE 1.0f
#define BRUSH_BUTTON_DEBOUNCE    0.0001f

typedef struct BUTTON_STRUCTURE
{
  struct BUTTON_STRUCTURE *self;
  char *buttonName;
  int order;
  BOOL isActive;
  BOOL isBlocking;
  float dt;
  AE_RECT rect;
  void (*exec)( struct BUTTON_STRUCTURE * );
  RETURN_TYPE (*update)( struct BUTTON_STRUCTURE *, float );
} BUTTON;

typedef BUTTON *P_BUTTON;
DECLARE_LIST( P_BUTTON );

extern LIST_TYPE( P_BUTTON ) *BUTTON_LIST;

//
// CreateButton
// Purpose: Creates a button class with a specified exec and update functionality.
//
BUTTON *CreateButton( char *name, void (*exec)( BUTTON * ), RETURN_TYPE (*update)( BUTTON *, float ), AE_RECT rect, int order );

//
// DeleteButton
// Purpose: Deletes a button from existence.
//
void DeleteButton( BUTTON *button );

//
// DeleteButtons
// Purpose: Deletes all buttons using the CallbackUpdate function.
//
void DeleteButtons( void );

//
// UpdateButton
// Purpose: Updates all buttons using the CallbackUpdate function.
//
RETURN_TYPE UpdateButton( BUTTON *button, float dt );

//
// UpdateButtons
// Purpose: Updates all buttons using the CallbackUpdate function.
//
void UpdateButtons( float dt );

//
// ButtonUpdateStandard
// Purpose: Standard update function for a generic button.
//
RETURN_TYPE ButtonUpdateStandard( BUTTON *self, float dt );

//
// ButtonUpdateBrush
// Purpose: Standard update function for a generic button.
//
RETURN_TYPE ButtonUpdateBrush( BUTTON *self, float dt );

void ExecTest( BUTTON *self );
