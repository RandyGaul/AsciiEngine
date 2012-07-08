////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdio.h>
#include "RedSquare.h"
#include "Math2D.h"
#include "Input.h"
#include "Random.h"
#include "TileMap.h"
#include "Graphics.h"

// Definition of the REDSQUARE's virtual table
const _REDSQUARE_VTABLE REDSQUARE_VTABLE = {
  RedSquareConstruct,
  RedSquareInit,
  RedSquareSet,
  RedSquareUpdate,
  RedSquareDraw,
  RedSquareDestroy
};

// Constructor for this object type
// Notes: Do not allocate space for the object itself! This is handled
//        by the object factory. This function is for allocation of
//        any other necessary memory. Perhaps a dynamically allocated
//        string, or other various memory allocations that are to be
//        pointed to by this object.
void RedSquareConstruct( REDSQUARE *self )
{
}

// Default initializer for this object type
// Notes: This function calls the Set function for this object type.
//        The purpose of the set function is to set the values of the
//        self object to those of the parameters. However the Init
//        function of an object acts as "default parameters" for the
//        set function. Since parameter defaults are not apart of the C
//        standard this workaround becomes necessary.
void RedSquareInit     ( REDSQUARE *self )
{
  AE_RECT rect = { 0 };
  rect.center_.x_ = 2;
  rect.center_.y_ = 2;
  rect.height_ = 1.f;
  rect.width_ = 1.f;
  rect.halfWidth_ = .5f;
  rect.halfHeight_ = .5f;
  RedSquareSet( self, rect, AE_FindImage( "REDSQUARE" ) );
  self->vel_.x_ = 0.f;
  self->vel_.y_ = 0.f;
  self->accel_ = 0.0001f;
  self->base_.queue_ = NULL;
}

// Initializer function for this object type
// Notes: This function is the one to be called if you wish to at any
//        time initialize the object with customized data. If you desire
//        a default initialization, call the Init function instead.
void RedSquareSet      ( REDSQUARE *self, const AE_RECT rect, const IMAGE *image )
{
  self->image_ = image;
  self->rect_ = rect;
}

// Update function for this object type
void RedSquareUpdate   ( REDSQUARE *self )
{
  COLLISION_FLAG flag = CheckHotspotCollision( self->rect_ );
  char buffer[100] = { 0 };

  // Apply acceleration for keystrokes
  // Documentation for physics:    http://cecilsunkure.blogspot.com/2012/02/basic-2d-vector-physics.html
  // Documentation for collisions: http://cecilsunkure.blogspot.com/2012/07/collision-basic-2d-collision-detection.html
  //                               http://cecilsunkure.blogspot.com/2012/04/binary-collision-maps-platformer.html
  if(IsKeyPressed( VK_RIGHT ))
  {
    self->vel_.x_ += self->accel_ * GetDT( );
  }
  if(IsKeyPressed( VK_LEFT ))
  {
    self->vel_.x_ += -self->accel_ * GetDT( );
  }
  if(IsKeyPressed( VK_UP ))
  {
    self->vel_.y_ += -self->accel_ * GetDT( );
  }
  if(IsKeyPressed( VK_DOWN ))
  {
    self->vel_.y_ += self->accel_ * GetDT( );
  }

  // Clamp velocity within a max/min range
  VelocityClamp( &self->vel_, .02f );

  self->rect_.center_.x_ += self->vel_.x_ * GetDT( );
  self->rect_.center_.y_ += self->vel_.y_ * GetDT( );

  sprintf( buffer, "%.3f, %.3f", self->vel_.x_, self->vel_.y_ );
  WriteStringToScreen( buffer, 30, 30 );

  if(flag & COLLISION_BOTTOM)
  {
    SnapToCell( &self->rect_.center_.y_ );
    self->vel_.y_ = 0.f;
  }
  if(flag & COLLISION_TOP)
  {
    SnapToCell( &self->rect_.center_.y_ );
    self->vel_.y_ = 0.f;
  }
  if(flag & COLLISION_LEFT)
  {
    SnapToCell( &self->rect_.center_.x_ );
    self->vel_.x_ = 0.f;
  }
  if(flag & COLLISION_RIGHT)
  {
    SnapToCell( &self->rect_.center_.x_ );
    self->vel_.x_ = 0.f;
  }
}

// Draw function for this object type
void RedSquareDraw     ( REDSQUARE *self )
{
  WriteImageToScreen( "REDSQUARE",
    FloatToInt( self->rect_.center_.x_ + EPSILON ),
    FloatToInt( self->rect_.center_.y_ + EPSILON) );
}

// Destructor for this object type
// Notes: Only free things in this function that were allocated in the
//        construtor! The object factory actually handles deallocation
//        of the object itself.
void RedSquareDestroy  ( REDSQUARE *self )
{
}
