////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "RedSquare.h"
#include "Math2D.h"
#include "Input.h"
#include "Random.h"

// Defines for readability
#define REDSQUARE_WIDTH 3
#define REDSQUARE_HEIGHT REDSQUARE_WIDTH

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
  rect.center_.x_ = (float)RandomInt( 0, BUFFERWIDTH );
  rect.center_.y_ = (float)RandomInt( 0, BUFFERHEIGHT );
  rect.height_ = REDSQUARE_HEIGHT;
  rect.width_ = REDSQUARE_WIDTH;
  rect.halfWidth_ = 1;
  rect.halfHeight_ = 1;
  RedSquareSet( self, rect, AE_FindImage( "REDSQUARE" ) );
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
  if(IsKeyPressed( VK_RIGHT ))
  {
    self->rect_.center_.x_ += 1.f;
  }
  if(IsKeyPressed( VK_LEFT ))
  {
    self->rect_.center_.x_ -= 1.f;
  }
  if(IsKeyPressed( VK_UP ))
  {
    self->rect_.center_.y_ -= 1.f;
  }
  if(IsKeyPressed( VK_DOWN ))
  {
    self->rect_.center_.y_ += 1.f;
  }
}

// Draw function for this object type
void RedSquareDraw     ( REDSQUARE *self )
{
  WriteImageToScreen( "REDSQUARE",
    FloatToInt( self->rect_.center_.x_ ) - self->rect_.halfWidth_,
    FloatToInt( self->rect_.center_.y_ ) - self->rect_.halfHeight_ );
}

// Destructor for this object type
// Notes: Only free things in this function that were allocated in the
//        construtor! The object factory actually handles deallocation
//        of the object itself.
void RedSquareDestroy  ( REDSQUARE *self )
{
}
