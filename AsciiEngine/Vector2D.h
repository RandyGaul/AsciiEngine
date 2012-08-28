////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef VECTOR2DH
#define VECTOR2DH

#include "math.h"

typedef struct _VECTOR2D
{
	float x_, y_;
} VECTOR2D;

typedef struct _INT_VECTOR2D
{
	int x_, y_;
} INT_VECTOR2D;

//
// Vector2DZero
// Purpose: Zeros the x_ and y_ data members of a vector
//
void Vector2DZero( VECTOR2D *vector );

//
// Vector2DSet
// Purpose: Sets the x_ and y_ data members of a vector to
//          provided values x and y
//
void Vector2DSet( VECTOR2D *vector, float x, float y );

//
// Vector2DNeg
// Purpose: Sets a vector to the opposite of another vector
//
void Vector2DNeg( VECTOR2D *vector, VECTOR2D *opposite );

//
// Vector2DAdd
// Purpose: Sets a vector to the sum of two vectors
//
void Vector2DAdd( VECTOR2D *vector, VECTOR2D *addend1, VECTOR2D *addend2);

//
// Vector2DSub
// Purpose: Sets a vector to the difference of two vectors
//
void Vector2DSub( VECTOR2D *vector, VECTOR2D *addend1, VECTOR2D *addend2);

//
// Vector2DNormalize
// Purpose: Sets a vector to the unit vector of another vector
// Notes  : This function should be used mainly to initialize values; since
//          it uses the sqrt function, calling it each game cycle will be
//          rather costly.
//
void Vector2DNormalize( VECTOR2D *vector, VECTOR2D *toNorm );

//
// Vector2DScale
// Purpose: Scales vector toScale by value c and stores the result in vector
//
void Vector2DScale( VECTOR2D *vector, VECTOR2D *toScale, float c );

//
// Vector2DLength
// Purpose: Returns the absolute length of a vector
// Notes  : Due to the use of sqrt, this function can be much
//          more innefficient than Vector2DSquareLength.
//
float	Vector2DLength( const VECTOR2D *vector );

//
// Vector2DSquareLength
// Purpose: Returns the length of a vector squared
// Notes  : This function should be used as an optimization to
//          the Vector2DLength function to avoid the use of the
//          sqrt function.
//
float Vector2DSquareLength( const VECTOR2D *vector );

//
// Vector2DDistance
// Purpose: Returns the absolute distance between two points
// Notes  : This function can be highly innefficient compared to
//          Vector2DSquareDistance due to the use of the sqrt
//          function.
//
float Vector2DDistance( const VECTOR2D *pointA, const VECTOR2D *pointB );

//
// Vector2DSquareDistance
// Purpose: Returns the absolute distance between two points squared
// Notes  : This function can be highly efficient compared to
//          Vector2DSquareDistance due to the use of the sqrt
//          function in its counterpart.
//
float Vector2DSquareDistance( const VECTOR2D *pointA, const VECTOR2D *pointB );

//
// Vector2DDotProduct
// Purpose: Returns the dot product of two vectors.
//
float Vector2DDotProduct( const VECTOR2D *vectorA, const VECTOR2D *vectorB );

//
// Vector2DCrossProduct
// Purpose: Returns the dot product of two vectors.
//
float Vector2DCrossProduct( const VECTOR2D *vectorA, const VECTOR2D *vectorB );

//
// Vector2DFromAngle
// Purpose: Returns a normal vector in the direction of an angle (radians)
//
void Vector2DFromAngle( VECTOR2D *vector, float angle);

//
// SpeedClamp
// Purpose: Clamps a velocity vector within a maximum speed
//
void SpeedClamp( float *vel, float maxSpeed );

#endif  VECTOR2DH