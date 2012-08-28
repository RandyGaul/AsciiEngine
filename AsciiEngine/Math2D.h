////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef MATH2DH
#define MATH2DH

// This is used to reverse clamp floating values to zero for
// effective floating point usage
#define EPSILON 0.0001f

#include "Vector2D.h"
#include "Shapes.h"
#include "GlobalDefines.h"

//
// StaticCircleToStaticRectangle
// Purpose: Detects collision between a static circle and static
//          rectangle
//
BOOL StaticCircleToStaticRectangle( const AE_CIRCLE *circle, const AE_RECT *rect );

//
// StaticPointToStaticCircle
// Purpose: Detects collision between a static point and static
//          circle
//
BOOL StaticPointToStaticCircle( const VECTOR2D *point, const AE_CIRCLE *circle );

//
// StaticPointToStaticRect
// Purpose: Detects collision between a static point and static
//          rectangle
//
BOOL StaticPointToStaticRect( const VECTOR2D *point, const AE_RECT *rect );

//
// StaticCircleToStaticCircle
// Purpose: Detects collision between a static circleA and static
//          circleB
//
BOOL StaticCircleToStaticCircle( const AE_CIRCLE *circleA, const AE_CIRCLE *circleB );

//
// StaticRectToStaticRect
// Purpose: Detects collision between a static rectangleA and static
//          rectangleB
//    
BOOL StaticRectToStaticRect( const AE_RECT *rectA, const AE_RECT *rectB );

//
// FloatToInt
// Purpose: Truncates all of the floating point value
//   
int FloatToInt( float val );

//
// FloatToIntRoundUp
// Purpose: Returns an integer representation of a
//          float rounded to the nearest integer, upwards
//   
int FloatToIntRoundUp( float val );

//
// SnapToCell
// Purpose: Snaps a floating point value to the nearest cell
// 
void SnapToCell( float *coordinate );

//
// BoundCheck
// Purpose: Checks to make sure a coordinate is within a specific bound
//
BOOL BoundCheck( AE_COORD coord, int boundTop, int boundLeft, int boundBottom, int boundRight );

//
// BoundCheck
// Purpose: Checks to make sure a coordinate is within a specific bound
//
BOOL BoundCheck2( AE_COORD coord, AE_COORD topLeft, AE_COORD bottomRight );

//
// SnapVectorToRect
// Purpose: Snaps a point within a rectangle boundary.
//
void SnapVectorToRect( VECTOR2D *vec, AE_RECT *rect );

#endif  MATH2DH
