#ifndef IMAGETABLEH
#define IMAGETABLEH

// This file is used to maintain a hash table of IMAGE structs
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#include "HashTable.h"
#include "Graphics.h"

typedef IMAGE *P_IMAGE;

DECLARE_TABLE( P_IMAGE, MAX_KEY_LEN );

extern GET_TABLE_TYPE( P_IMAGE ) *IMAGE_TABLE;


#endif  IMAGETABLEH