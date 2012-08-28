////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/25/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "JumperLittle.h"
#include "Component.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "Random.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void JumperLittleCOM_PROC( BJL *self, EM msg, int var1, int var2 )
{
  // GENERAL
  switch(msg)
  {
  case EM_CLSINIT:
    JumperLittleInit( (const char *)var1 );
    break;
  case EM_CREATE:
    JumperLittleCreate( self );
    break;
  case EM_UPDATE:
    JumperLittleUpdate( self, (float *)var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void JumperLittleCreate( BJL *self )
{
  self->dt = 0;
  self->timeToWait = (float)RandomInt( 2, 5 );
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void JumperLittleInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// JumperLittleUpdate
// Purpose: Creates various actions for the actionList of this object.
//
void JumperLittleUpdate( BJL *self, float *dt )
{
  self->dt += *dt;

  if(self->dt > self->timeToWait)
  {
    VECTOR2D vel = { (float)RandomInt( -10, 10 ), -(float)RandomInt( 20, 40 ) };
    ALD ALdata = { 0 };
    self->dt = 0;
    ALdata.flag |= BLOCKING;
    ALdata.ID = ALT_SET_VEL;
    ALdata.var1 = (int)vel.x_;
    ALdata.var2 = (int)vel.y_;
    SendEntityMessage( self->base.owner, EM_ALADDACT, (int)&ALdata, 0 );
  }
}

