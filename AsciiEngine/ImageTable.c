////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////


// This file is used to maintain a hash table of IMAGE structs
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#include "ImageTable.h"

GET_TABLE_TYPE( P_IMAGE ) *IMAGE_TABLE = NULL;

DEFINE_TABLE( P_IMAGE, DeallocateImage );
