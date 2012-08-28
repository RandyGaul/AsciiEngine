////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/17/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Position.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void PosCOM_PROC( POSITION_COMPONENT *self, EM msg, int var1, int var2 )
{
  // Only respond to Draw, Init, and Destroy msgs
  switch(msg)
  {
  case EM_CLSINIT:
    PosInit( (const char *)var1 );
    break;
  case EM_CREATE:
    PosCreate( (POS *)self, (float *)var1, (float *)var2 );
    break;
  case EM_SETPOS:
    PosSetPos( (POS *)self, (float *)var1, (float *)var2 );
    break;
  case EM_GETPOS:
    PosGetPos( (POS *)self, (float *)var1, (float *)var2 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void PosCreate( POS *self, float *x, float *y )
{
  self->base.CLASS_NAME = CLASS_NAME;
  self->base.COM_PROC( (POSITION_COMPONENT *)self, EM_SETPOS, (int)x, (int)y );
}

//
// ClassSetPos
// Purpose: Sets the position of the class. Takes two floats.
//
void PosSetPos( POS *self, float *var1, float *var2 )
{
  if(var1)
  {
    self->pos.x_ = *var1;
    self->pos.y_ = *var2;
  }
  else
  {
    self->pos.x_ = 0;
    self->pos.y_ = 0;
  }
}

//
// ClassGetPos
// Purpose: Copiess values of x and y position into var1 and var2
//          respectively.
//
void PosGetPos( POS *self, float *var1, float *var2 )
{
  *var1 = self->pos.x_;
  *var2 = self->pos.y_;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void PosInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}
