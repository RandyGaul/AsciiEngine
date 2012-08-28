////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "Button.h"
#include "Math2D.h" // Point to Rects
#include "Input.h"  // Mouse x and y
#include "EntityManager.h"
#include "Camera.h"

DEFINE_LIST( P_BUTTON );
LIST_TYPE( P_BUTTON ) *BUTTON_LIST = NULL;

//
// CreateButton
// Purpose: Creates a button class with a specified exec and update functionality.
//
BUTTON *CreateButton( char *name, void (*exec)( BUTTON * ), RETURN_TYPE (*update)( BUTTON *, float ), AE_RECT rect, int order )
{
  BUTTON *button = (BUTTON *)malloc( sizeof( BUTTON  ) + strlen( name ) + 1 );
  NODE_TYPE( P_BUTTON ) *node = NODE_CREATE( P_BUTTON, button, DeleteButton, button->order );
  button->buttonName = PtrAdd( button, sizeof( BUTTON ) );
  strcpy_s( button->buttonName, strlen( name ) + 1, name );
  button->isActive = TRUE;
  button->self = button;
  button->exec = exec;
  button->update = update;
  button->order = order;
  button->isBlocking = TRUE;
  button->dt = 0;
  button->rect = rect;
  LIST_INSERT( P_BUTTON, BUTTON_LIST, node );
  return button;
}

//
// DeleteButton
// Purpose: Deletes a button from existence.
//
void DeleteButton( BUTTON *button )
{
  free( button );
}

//
// CallbackDeleteButtons
// Purpose: Used to delete all nodes.
//
RETURN_TYPE CallbackDeleteButtons( NODE_TYPE( P_BUTTON ) *node, void *param )
{
  DeleteButton( node->data );
  LIST_REMOVE( P_BUTTON, BUTTON_LIST, node );
  return RETURN_SUCCESS;
}

//
// DeleteButtons
// Purpose: Deletes all buttons using the CallbackUpdate function.
//
void DeleteButtons( void )
{
  LIST_CALLER( P_BUTTON, BUTTON_LIST, CallbackDeleteButtons, 0 );
}

//
// UpdateButton
// Purpose: Updates all buttons using the CallbackUpdate function.
//
RETURN_TYPE UpdateButton( BUTTON *button, float dt )
{
  return button->update( button,  dt );
}

//
// CallbackUpdate
// Purpose: Used to update all nodes.
//
RETURN_TYPE CallbackUpdate( NODE_TYPE( P_BUTTON ) *node, void *param )
{
  return UpdateButton( node->data, *(float *)param );
}

//
// UpdateButtons
// Purpose: Updates all buttons using the CallbackUpdate function.
//
void UpdateButtons( float dt )
{
  LIST_CALLER( P_BUTTON, BUTTON_LIST, CallbackUpdate, &dt );
}

//
// ButtonUpdateStandard
// Purpose: Standard update function for a generic button.
//
RETURN_TYPE ButtonUpdateStandard( BUTTON *self, float dt )
{
  // Update dt only if non-zero.
  // For example when exec is called, set dt to 0.001 (seconds)
  // to begin debounce timer.
  if(self->dt != 0)
  {
    self->dt += dt;
  }
  
  // Debounce
  if(self->dt > STANDARD_BUTTON_DEBOUNCE && !IsKeyPressed( VK_LBUTTON ))
  {
    self->dt = 0;
  }

  if(self->dt == 0)
  {
    VECTOR2D pos = { 0 };
    pos.x_ = (float)GLOBAL_INPUTS.xPos;
    pos.y_ = (float)GLOBAL_INPUTS.yPos;

    // Test for button press
    if(IsKeyPressed( VK_LBUTTON ))
    {
      if(StaticPointToStaticRect( &pos, &self->rect ))
      {
        {
          self->exec( self );

          // Initiate debounce
          self->dt = 0.0001f;

          // End list caller routine if blocking
          if(self->isBlocking)
            return RETURN_FAILURE;
        }
      }
    }
  }
  
  return RETURN_SUCCESS;
}

//
// ButtonUpdateBrush
// Purpose: Standard update function for a generic button.
//
RETURN_TYPE ButtonUpdateBrush( BUTTON *self, float dt )
{
  // Update dt only if non-zero.
  // For example when exec is called, set dt to 0.001 (seconds)
  // to begin debounce timer.
  if(self->dt != 0)
  {
    self->dt += dt;
  }
  
  // Debounce
  if(self->dt > BRUSH_BUTTON_DEBOUNCE)
  {
    self->dt = 0;
  }

  if(self->dt == 0)
  {
    VECTOR2D pos = { 0 };
    pos.x_ = (float)GLOBAL_INPUTS.xPos;
    pos.y_ = (float)GLOBAL_INPUTS.yPos;

    // Test for button press
    if(IsKeyPressed( VK_LBUTTON ))
    {
      if(StaticPointToStaticRect( &pos, &self->rect ))
      {
        {
          self->exec( self );

          // Initiate debounce
          self->dt = 0.000001f;

          // End list caller routine if blocking
          if(self->isBlocking)
            return RETURN_FAILURE;
        }
      }
    }
  }
  
  return RETURN_SUCCESS;
}

void ExecTest( BUTTON *self )
{
  VECTOR2D pos = { (float)GLOBAL_INPUTS.xPos - GLOBAL_CAM.center.x_,
                   (float)GLOBAL_INPUTS.yPos - GLOBAL_CAM.center.y_ };
  CreateEntity( "TILE", (int)&pos.x_, (int)&pos.y_ );
}
