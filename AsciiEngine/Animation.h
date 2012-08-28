////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/19/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Graphics.h"
#include "GraphicsComponent.h"

//
// ANIMATION class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _ANIMATION_COMPONENT
{
  GRAPHICS_COMPONENT base;
  ANIMATION *animation;
} ANI;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void AnimationCOM_PROC( ANI *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void AnimationCreate( ANI *self, ANIMATION *animation );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void AnimationInit( const char *className );

//
// ComponentDraw
// Purpose: Simply renders the animation.
//
void AnimationDraw( ANI *self );

//
// AnimationUpdate
// Purpose: Updates the animation's internal timer, allowing to flip through the frames.
//
void AnimationUpdate( ANI *self, float *dt );

//
// AnimationSetPlayCount
// Purpose: Sets the playcount of the animation and copies into int *var1
//
void AnimationSetPlayCount( ANI *self, int *var1 );

//
// AnimationGetPlayCount
// Purpose: Gets the playcount of the animation and copies into int *var1
//
void AnimationGetPlayCount( ANI *self, int *var1 );

//
// AnimationGetCurrentFrame
// Purpose: Gets the currentFrame of the animation and copies into int *var1
//
void AnimationGetCurrentFrame( ANI *self, int *var1 );

//
// AnimationSetCurrentFrame
// Purpose: Sets the currentFrame from the data within int *var1
//
void AnimationSetCurrentFrame( ANI *self, int *var1 );

//
// AnimationGetFrameDelay
// Purpose: Gets the currentFrame of the animation and copies into float *var1
//
void AnimationGetFrameDelay( ANI *self, float *var1 );

//
// AnimationSetFrameDelay
// Purpose: Sets the currentFrame from the data within float *var1
//
void AnimationSetFrameDelay( ANI *self, float *var1 );

//
// AnimationGetGetIsPaused
// Purpose: Gets the isPaused from the animation and copies into BOOL *var1
//
void AnimationGetIsPaused( ANI *self, BOOL *var1 );

//
// AnimationSetGetIsPaused
// Purpose: Copies the isPaused in the animation to value of BOOL *var1
//
void AnimationSetIsPaused( ANI *self, BOOL *var1 );