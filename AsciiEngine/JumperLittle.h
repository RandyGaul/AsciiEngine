////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/25/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Message.h"
#include "BrainComponent.h"

typedef struct _BRAIN_JUMPER_LITTLE_COMPONENT
{
  BRAIN_COMPONENT base;
  float dt;
  float timeToWait;
} BJL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void JumperLittleCOM_PROC( BJL *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void JumperLittleCreate( BJL *self );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void JumperLittleInit( const char *className );

//
// JumperLittleUpdate
// Purpose: Creates various actions for the actionList of this object.
//
void JumperLittleUpdate( BJL *self, float *dt );
