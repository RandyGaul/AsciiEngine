////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file contains functionality for hashing strings
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#include "StringHash.h"

// Hashing function from Program 14.2 in the Sedgewick book
unsigned UHashMod( const char *Key, unsigned tableSize )
{
  unsigned hash = 0;      // Initial value of hash
  unsigned rand1 = 31415; // "Random" 1
  unsigned rand2 = 27183; // "Random" 2

  while (*Key)
  {
    hash = hash * rand1;     // Multiply hash by random
    hash = (hash + *Key);    // Add in current char, keep within TableSize
    rand1 = (rand1 * rand2); // Update rand1 for next "random" number
    Key++;
  }

  return hash % tableSize;
}
