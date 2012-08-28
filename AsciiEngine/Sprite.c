////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Sprite.h"
#include "EntityManager.h"
#include "Camera.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void SpriteCOM_PROC( SPRITE *self, EM msg, int var1, int var2 )
{
  switch(msg)
  {
  case EM_CLSINIT:
    SpriteInit( (const char *)var1 );
    break;
  case EM_CREATE:
    SpriteCreate( self, (IMAGE *)var1 );
    break;
  case EM_DRAW:
    SpriteDraw( self );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void SpriteCreate( SPRITE *self, IMAGE *image )
{
  self->image = image;
  self->base.CLASS_NAME = CLASS_NAME;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void SpriteInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ComponentDraw
// Purpose: Simply renders the sprite
//
void SpriteDraw( SPRITE *self )
{
  float x, y;
  VECTOR2D WH = { 0 };
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&x, (int)&y );
  SendEntityMessage( self->base.owner, EM_GETWH, (int)&WH.x_, (int)&WH.y_ );
  if(self->image)
  {
    WriteImageToScreen( self->image->ID,
      FloatToInt( x - CAMOFFX - WH.x_ / 2.f + DimensionOffset( WH.x_ ) ),
      FloatToInt( y - CAMOFFY - WH.y_ / 2.f + 1.f ) );
  }
}
