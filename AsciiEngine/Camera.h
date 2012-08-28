////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/20/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef CAMERAH
#define CAMERAH

#include "GlobalDefines.h"
#include "Shapes.h"
#include "Entity.h"
#include "EntityManager.h"

#define CAM_SCROLL_BOUND 5.0f

typedef struct _PLAYER_CAMERA
{
  VECTOR2D center;
  ENTITY *followThis;
} CAMERA;

//
// GlobalCamInit
// Purpose: Initializes the camera's various data members.
// Notes  : The followMe param can be NULL if you don't wish the camera to
//          follow any object.
//
RETURN_TYPE GlobalCamInit( float xoffset, float yoffset, ENTITY *followMe );

//
// GlobalCamUpdate
// Purpose: Updates the camera, for use when following a game entity.
//
void GlobalCamUpdate( float dt );

//
// GlobalCamDisable
// Purpose: Clears the data members for the next state, to be used during free.
//
void GlobalCamDisable( void );

extern CAMERA GLOBAL_CAM;

#endif  CAMERAH