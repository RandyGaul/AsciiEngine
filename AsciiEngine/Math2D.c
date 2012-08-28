////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Math2D.h"
#include "GlobalDefines.h"

// Used to snap to nearest cell
#define SNAPPING_COMPARITOR 0.5f

//
// StaticCircleToStaticRectangle
// Purpose: Detects collision between a static circle and static
//          rectangle
//
BOOL StaticCircleToStaticRectangle( const AE_CIRCLE *circle, const AE_RECT *rect )
{
  // Gather some values with pre-computation for readability
  float halfW = (0.5f * rect->width_);
  float halfH = (0.5f * rect->height_);
  float distance = 0.f;

  // Copy the circle center for later comparison
  VECTOR2D centerCopy = circle->center_;

  // Various checks outlined in documentation (see top of file)
	if(centerCopy.x_ > rect->center_.x_ + halfW)
	{
		centerCopy.x_ = rect->center_.x_ + halfW;
	}
	else if(centerCopy.x_ < rect->center_.x_ - halfW)
	{
		centerCopy.x_ = rect->center_.x_ - halfW;
	}

	if(centerCopy.y_ > rect->center_.y_ + halfH)
	{
		centerCopy.y_ = rect->center_.y_ + halfH;
	}
	else if(centerCopy.y_ < rect->center_.y_ - halfH)
	{
		centerCopy.y_ = rect->center_.y_ - halfH;
	}

  // Compute distance squared to avoid sqrt function
	distance = (circle->center_.x_ - centerCopy.x_) * (circle->center_.x_ - centerCopy.x_) +
					   (circle->center_.y_ - centerCopy.y_) * (circle->center_.y_ - centerCopy.y_);

  // Compare distance squared with radius squared for final comparison
  if(distance > (circle->radius_ * circle->radius_) / 4.f)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//
// StaticPointToStaticCircle
// Purpose: Detects collision between a static point and static
//          circle
//
BOOL StaticPointToStaticCircle( const VECTOR2D *point, const AE_CIRCLE *circle )
{
  // Compare radius squared with the square distance between the points
	return (circle->radius_ * circle->radius_ >
         (point->x_ - circle->center_.x_) * (point->x_ - circle->center_.x_) +
         (point->y_ - circle->center_.y_) * (point->y_ - circle->center_.y_)) ? TRUE : FALSE;
}

//
// StaticPointToStaticRect
// Purpose: Detects collision between a static point and static
//          rectangle
//
BOOL StaticPointToStaticRect( const VECTOR2D *point, const AE_RECT *rect )
{
  float halfW = (0.5f * rect->width_);
  float halfH = (0.5f * rect->height_);

  // Perform various checks required as detailed in documentation (see top of file)
  return (point->x_ < (rect->center_.x_ + halfW) &&
          point->x_ > (rect->center_.x_ - halfW) &&
          point->y_ < (rect->center_.y_ + halfH) &&
          point->y_ > (rect->center_.y_ - halfH)) ? TRUE : FALSE;
}

//
// StaticCircleToStaticCircle
// Purpose: Detects collision between a static circleA and static
//          circleB
//
BOOL StaticCircleToStaticCircle( const AE_CIRCLE *circleA, const AE_CIRCLE *circleB )
{
  // Compute squared distance to avoid sqrt function
  float dist = (circleA->center_.x_ - circleB->center_.x_) * (circleA->center_.x_ - circleB->center_.x_) +
               (circleA->center_.y_ - circleB->center_.y_) * (circleA->center_.y_ - circleB->center_.y_);

  // Compute squared radius to avoid sqrt function
  float radii = circleA->radius_ + circleB->radius_;

	return (radii * radii >= dist) ? TRUE : FALSE;
}

//
// StaticRectToStaticRect
// Purpose: Detects collision between a static rectangleA and static
//          rectangleB
//    
BOOL StaticRectToStaticRect( const AE_RECT *rectA, const AE_RECT *rectB )
{
  float leftA = rectA->center_.x_ - 0.5f * rectA->width_;
  float leftB = rectB->center_.x_ - 0.5f * rectB->width_;
	float rightA = rectA->center_.x_ + 0.5f * rectA->width_;
	float rightB = rectB->center_.x_ + 0.5f * rectB->width_;
  float topA = rectA->center_.y_ + 0.5f * rectA->height_;
  float topB = rectB->center_.y_ + 0.5f * rectB->height_;
  float bottomA = rectA->center_.y_ - 0.5f * rectA->height_;
  float bottomB = rectB->center_.y_ - 0.5f * rectB->height_;

  // Perform various checks required, see documentation for details (top of file)
  return (leftA >= rightB || leftB >= rightA || topA <= bottomB || topB <= bottomA) ? FALSE : TRUE;
}

//
// FloatToInt
// Purpose: Truncates all of the floating point value
//   
int FloatToInt( float val )
{
	return (int)val;
}

//
// FloatToIntRoundUp
// Purpose: Returns an integer representation of a
//          float rounded to the nearest integer, upwards
//   
int FloatToIntRoundUp( float val )
{
	return (int)(val + .5f);
}

//
// SnapToCell
// Purpose: Snaps a floating point value to the nearest cell
// 
void SnapToCell( float *coordinate )
{
	*coordinate = (float)((int)(*coordinate + 0.5f));
}

//
// BoundCheck
// Purpose: Checks to make sure a coordinate is within a specific bound
//
BOOL BoundCheck( AE_COORD coord, int boundTop, int boundLeft, int boundBottom, int boundRight )
{
  return (coord.x_ <= boundRight && coord.x_ >= boundLeft && coord.y_ <= boundBottom && coord.y_ >= boundTop) ? TRUE : FALSE;
}

//
// BoundCheck
// Purpose: Checks to make sure a coordinate is within a specific bound
//
BOOL BoundCheck2( AE_COORD coord, AE_COORD topLeft, AE_COORD bottomRight )
{
  return (coord.x_ <= bottomRight.x_ &&
    coord.x_ >= topLeft.x_ &&
    coord.y_ <= bottomRight.y_ &&
    coord.y_ >= topLeft.y_) ? TRUE : FALSE;
}

//
// SnapVectorToRect
// Purpose: Snaps a point within a rectangle boundary.
//
void SnapVectorToRect( VECTOR2D *vec, AE_RECT *rect )
{
  float left = rect->center_.x_ - 0.5f * rect->width_;
	float right = rect->center_.x_ + 0.5f * rect->width_;
  float top = rect->center_.y_ + 0.5f * rect->height_;
  float bottom = rect->center_.y_ - 0.5f * rect->height_;

  if(vec->x_ > right)
    vec->x_ = right;
  else if(vec->x_ < left)
    vec->x_ = left;

  if(vec->y_ < bottom)
    vec->y_ = bottom;
  else if(vec->y_ > top)
    vec->y_ = top;
}
