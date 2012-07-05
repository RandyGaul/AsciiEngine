////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Vector2D.h"

//
// Vector2DZero
// Purpose: Zeros the x_ and y_ data members of a vector
//
void Vector2DZero( VECTOR2D *vector )
{
	vector->x_ = 0;
	vector->y_ = 0;
}

//
// Vector2DSet
// Purpose: Sets the x_ and y_ data members of a vector to
//          provided values x and y
//
void Vector2DSet( VECTOR2D *vector, float x, float y )
{
	vector->x_ = x;
	vector->y_ = y;
}

//
// Vector2DNeg
// Purpose: Sets a vector to the opposite of another vector
//
void Vector2DNeg( VECTOR2D *vector, VECTOR2D *opposite )
{
	vector->x_ = opposite->x_ * -1;
	vector->y_ = opposite->y_ * -1;
}

//
// Vector2DAdd
// Purpose: Sets a vector to the sum of two vectors
//
void Vector2DAdd( VECTOR2D *vector, VECTOR2D *addend1, VECTOR2D *addend2)
{
	vector->x_ = addend1->x_ + addend2->x_;
	vector->y_ = addend1->y_ + addend2->y_;
}

//
// Vector2DSub
// Purpose: Sets a vector to the difference of two vectors
//
void Vector2DSub( VECTOR2D *vector, VECTOR2D *addend1, VECTOR2D *addend2)
{
	vector->x_ = addend1->x_ - addend2->x_;
	vector->y_ = addend1->y_ - addend2->y_;
}

//
// Vector2DNormalize
// Purpose: Sets a vector to the unit vector of another vector
// Notes  : This function should be used mainly to initialize values; since
//          it uses the sqrt function, calling it each game cycle will be
//          rather costly.
//
void Vector2DNormalize( VECTOR2D *vector, VECTOR2D *toNorm )
{
	VECTOR2D temp;
  float sqrtVal = (float)sqrt((toNorm->x_ * toNorm->x_) + (toNorm->y_ * toNorm->y_));
	temp.x_ = toNorm->x_ / sqrtVal;
	temp.y_ = toNorm->y_ / sqrtVal;

	vector->x_ = temp.x_;
	vector->y_ = temp.y_;
}

//
// Vector2DScale
// Purpose: Scales vector toScale by value c and stores the result in vector
//
void Vector2DScale( VECTOR2D *vector, VECTOR2D *toScale, float c )
{
  vector->x_ = toScale->x_ * c;
  vector->y_ = toScale->y_ * c;
}

//
// Vector2DLength
// Purpose: Returns the absolute length of a vector
// Notes  : Due to the use of sqrt, this function can be much
//          more innefficient than Vector2DSquareLength.
//
float	Vector2DLength( const VECTOR2D *vector )
{
  return sqrtf( (vector->x_ * vector->x_) + (vector->y_ * vector->y_) );
}

//
// Vector2DSquareLength
// Purpose: Returns the length of a vector squared
// Notes  : This function should be used as an optimization to
//          the Vector2DLength function to avoid the use of the
//          sqrt function.
//
float Vector2DSquareLength( const VECTOR2D *vector )
{
	return (vector->x_ * vector->x_) + (vector->y_ * vector->y_);
}

//
// Vector2DDistance
// Purpose: Returns the absolute distance between two points
// Notes  : This function can be highly innefficient compared to
//          Vector2DSquareDistance due to the use of the sqrt
//          function.
//
float Vector2DDistance( const VECTOR2D *pointA, const VECTOR2D *pointB )
{
  return sqrtf( (pointA->x_ - pointB->x_) * (pointA->x_ - pointB->x_) +
                (pointA->y_ - pointB->y_) * (pointA->y_ - pointB->y_) );
}

//
// Vector2DSquareDistance
// Purpose: Returns the absolute distance between two points squared
// Notes  : This function can be highly efficient compared to
//          Vector2DSquareDistance due to the use of the sqrt
//          function in its counterpart.
//
float Vector2DSquareDistance( const VECTOR2D *pointA, const VECTOR2D *pointB )
{
  return (pointA->x_ - pointB->x_) * (pointA->x_ - pointB->x_) +
         (pointA->y_ - pointB->y_) * (pointA->y_ - pointB->y_);
}

//
// Vector2DDotProduct
// Purpose: Returns the dot product of two vectors.
//
float Vector2DDotProduct( const VECTOR2D *vectorA, const VECTOR2D *vectorB )
{
  return vectorA->x_ * vectorB->x_ + vectorA->y_ * vectorB->y_;
}

//
// Vector2DCrossProduct
// Purpose: Returns the dot product of two vectors.
//
float Vector2DCrossProduct( const VECTOR2D *vectorA, const VECTOR2D *vectorB )
{
	return vectorA->x_ * vectorB->y_ - vectorA->y_ * vectorB->x_;
}

//
// Vector2DFromAngle
// Purpose: Returns a normal vector in the direction of an angle (radians)
//
void Vector2DFromAngle( VECTOR2D *vector, float angle)
{
  vector->x_ = cosf(angle);
  vector->y_ = sinf(angle);
}
