////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file is used to maintain a hash table of IMAGE structs
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#ifndef STRINGHASHH
#define STRINGHASHH

#include "Graphics.h"
#include "GlobalDefines.h"

unsigned UHashMod( const char *Key );
IMAGE *TableLookup( const char *Key );
RETURN_TYPE InsertEntry( IMAGE *image );
RETURN_TYPE DeleteEntry( char *Key );

#endif  STRINGHASHH