////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/19/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Animation.h"
#include "EntityManager.h"
#include "Camera.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void AnimationCOM_PROC( ANI *self, EM msg, int var1, int var2 )
{
  // GENERAL
  switch(msg)
  {
  case EM_CLSINIT:
    AnimationInit( (const char *)var1 );
    break;
  case EM_CREATE:
    AnimationCreate( self, (ANIMATION *)var1 );
    break;
  case EM_DRAW:
    AnimationDraw( self );
    break;
  case EM_UPDATE:
    AnimationUpdate( self, (float *)var1 );
    break;

  // DATA ACCESS
  case EM_GETPLAYC:
    AnimationGetPlayCount( self, (int *)var1 );
    break;
  case EM_SETPLAYC:
    AnimationSetPlayCount( self, (int *)var1 );
    break;
  case EM_GETFRAME:
    AnimationGetCurrentFrame( self, (int *)var1 );
    break;
  case EM_SETFRAME:
    AnimationSetCurrentFrame( self, (int *)var1 );
    break;
  case EM_GETFRAMD:
    AnimationGetFrameDelay( self, (float *)var1 );
    break;
  case EM_SETFRAMD:
    AnimationSetFrameDelay( self, (float *)var1 );
    break;
  case EM_GETISPAS:
    AnimationGetIsPaused( self, (BOOL *)var1 );
    break;
  case EM_SETISPAS:
    AnimationSetIsPaused( self, (BOOL *)var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void AnimationCreate( ANI *self, ANIMATION *animation )
{
  self->animation = animation;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void AnimationInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ComponentDraw
// Purpose: Simply renders the animation.
//
void AnimationDraw( ANI *self )
{
  float x, y;
  VECTOR2D WH;
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&x, (int)&y );
  SendEntityMessage( self->base.owner, EM_GETWH, (int)&WH.x_, (int)&WH.y_ );
  WriteImageToScreen( self->animation->frames[self->animation->currentFrame]->ID,
    FloatToInt( x - CAMOFFX - WH.x_ / 2.f + DimensionOffset( WH.x_ ) ),
    FloatToInt( y - CAMOFFY - WH.y_ / 2.f + 1.f ) );
}

//
// AnimationUpdate
// Purpose: Updates the animation's internal timer, allowing to flip through the frames.
//
void AnimationUpdate( ANI *self, float *dt )
{
  UpdateAnimation( self->animation, *dt );
}

//
// AnimationGetPlayCount
// Purpose: Gets the playcount of the animation and copies into int *var1
//
void AnimationGetPlayCount( ANI *self, int *var1 )
{
  *var1 = self->animation->playCount;
}

//
// AnimationSetPlayCount
// Purpose: Sets the playcount from the data within int *var1
//
void AnimationSetPlayCount( ANI *self, int *var1 )
{
  self->animation->playCount = *var1;
}

//
// AnimationGetCurrentFrame
// Purpose: Gets the currentFrame of the animation and copies into int *var1
//
void AnimationGetCurrentFrame( ANI *self, int *var1 )
{
  *var1 = self->animation->currentFrame;
}

//
// AnimationSetCurrentFrame
// Purpose: Sets the currentFrame from the data within int *var1
//
void AnimationSetCurrentFrame( ANI *self, int *var1 )
{
  self->animation->currentFrame = *var1;
}

//
// AnimationGetFrameDelay
// Purpose: Gets the frameDelay from the animation and copies into float *var1
//
void AnimationGetFrameDelay( ANI *self, float *var1 )
{
  *var1 = self->animation->frameDelay;
}

//
// AnimationSetFrameDelay
// Purpose: Copis the frameDelay in the animation to value of float *var1
//
void AnimationSetFrameDelay( ANI *self, float *var1 )
{
  self->animation->frameDelay = *var1;
}

//
// AnimationGetGetIsPaused
// Purpose: Gets the isPaused from the animation and copies into BOOL *var1
//
void AnimationGetIsPaused( ANI *self, BOOL *var1 )
{
  *var1 = self->animation->isPaused;
}

//
// AnimationSetGetIsPaused
// Purpose: Copies the isPaused in the animation to value of BOOL *var1
//
void AnimationSetIsPaused( ANI *self, BOOL *var1 )
{
  self->animation->isPaused = *var1;
}
