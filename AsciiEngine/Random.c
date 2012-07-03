////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2010/11/prngs-psuedo-random-number-generator.html

#include <stdlib.h>
#include <time.h>
#include "Random.h"

// Seeds the PRNG
void InitRandSeed( void )
{
  srand( (unsigned int)time( 0 ) );
}

// Returns random int from range of low to high (inclusive)
int RandomInt( int low, int high )
{
  return (rand() % (high - low + 1) + low);
}
