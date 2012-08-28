////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/20/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "Camera.h"
#include "Math2D.h"
#include "Graphics.h"
#include "TileMap.h"
#include "Input.h"

CAMERA GLOBAL_CAM = { 0 };

//
// GlobalCamInit
// Purpose: Initializes the camera's various data members.
// Notes  : The followMe param can be NULL if you don't wish the camera to
//          follow any object.
//
RETURN_TYPE GlobalCamInit( float xoffset, float yoffset, ENTITY *followMe )
{
  GLOBAL_CAM.center.x_ = xoffset;
  GLOBAL_CAM.center.y_ = yoffset;
  GLOBAL_CAM.followThis = followMe;
  return RETURN_SUCCESS;
}

//
// GlobalCamUpdate
// Purpose: Updates the camera, for use when following a game entity.
//
void GlobalCamUpdate( float dt )
{
  VECTOR2D pos = { 0 };

  // If have entity to follow, go in opposite direction it goes, if it moves
  if(GLOBAL_CAM.followThis)
  {
    SendEntityMessage( GLOBAL_CAM.followThis, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );

    GLOBAL_CAM.center.x_ = -FloatToInt( pos.x_ ) + (float)BUFFERWIDTH / 2.f;
    GLOBAL_CAM.center.y_ = -(float)FloatToIntRoundUp( pos.y_ ) + (float)BUFFERHEIGHT / 2.f;

  }
}

//
// GlobalCamDisable
// Purpose: Clears the data members for the next state, to be used during free.
//
void GlobalCamDisable( void )
{
  GLOBAL_CAM.center.x_ = 0;
  GLOBAL_CAM.center.y_ = 0;
  GLOBAL_CAM.followThis = NULL;
}
