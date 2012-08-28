////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Graphics.h"
#include "GraphicsComponent.h"
#include "Shapes.h"

//
// SPRITE class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _SPRITE_COMPONENT
{
  GRAPHICS_COMPONENT base;
  IMAGE *image;
} SPRITE;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SpriteCOM_PROC( struct _SPRITE_COMPONENT *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SpriteCreate( struct _SPRITE_COMPONENT *self, IMAGE *image );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SpriteInit( const char *className );

//
// ComponentDraw
// Purpose: Simply renders the sprite
//
void SpriteDraw( SPRITE *self );

