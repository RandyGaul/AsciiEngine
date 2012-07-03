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

#include <stdio.h>
#include "StringHash.h"

#define DELETED ((IMAGE *)(0xFFFFFFFF))

// Checks to see if an entry is empty
#define IsEmpty( table, index ) \
  (table[index] == NULL) ? TRUE : FALSE

// Checks to see if an entry can be placed in the index
#define CanPlace( table, index ) \
  (IsEmpty( table, index ) || table[index] == DELETED) ? TRUE : FALSE

// Checks to see if an index has an entry
#define HasEntry( table, index ) \
  (table[index] != NULL && table[index] != DELETED) ? TRUE : FALSE

// Modify this value to be able to hold more or less images
// Value should be prime
#define TABLESIZE 7919

// Hash table for images
IMAGE *IMABE_TABLE[TABLESIZE] = { 0 };
BOOL isTableFull = FALSE;

// Attempt to insert an entry into the table
// Will fail if no room or a duplicate key is found.
RETURN_TYPE InsertEntry( IMAGE *image )
{
  // Retrieve hashed index from string
  unsigned index = UHashMod( image->ID );
  unsigned indexStart = index;

  // Search for empty or deleted location in table with linear probing
  while(!CanPlace( IMABE_TABLE, index ))
  {
    // Break from the loop if a duplicate is found
    if(strcmp( IMABE_TABLE[index]->ID, image->ID ) == 0)
      break;

    ++index;

    // wraparound to beginning of table instead of index beyond table
    if(index == TABLESIZE)
    {
      index = 0;
    }

    // If searched entire table (means table is full)
    if(indexStart == index)
    {
      isTableFull = TRUE; // set the isTableFull flag
      break;
    }
  }

  // Skip the allocation process if a duplicate entry is found
  if(HasEntry( IMABE_TABLE, index ))
  {
    if(strcmp( IMABE_TABLE[index]->ID, image->ID ) == 0)
    {
      return RETURN_FAILURE;
    }
  }

  // Skip the alloction process if there's no room in the table.
  if(isTableFull == TRUE)
    return RETURN_FAILURE;

  IMABE_TABLE[index] = image;
  return RETURN_SUCCESS;
}

// Hashing function from Program 14.2 in the Sedgewick book
unsigned UHashMod( const char *Key )
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

  return hash % TABLESIZE;
}

// Looks up data given a specific key -- the whole point of using a hash map.
// Instead of linearly searching, or doing a binary search in an ordered array,
// you can use a hash function to generate an index and subsequently cut down
// searh complexity to O(1 + nlk). Returns NULL if string is not found.
IMAGE *TableLookup( const char *Key )
{
  unsigned index = UHashMod( Key );
  unsigned indexStart = index;

  // Only search through clusters, don't hop over empty entries
  while(!IsEmpty( IMABE_TABLE, index ))
  {
    // Break from loop if found matching entry
    if(IMABE_TABLE[index] != DELETED)
    {
      if(strcmp(IMABE_TABLE[index]->ID, Key) == 0)
        break;
    }

    ++index;

    // wraparound to beginning of table
    if(index == TABLESIZE)
    {
      index = 0;
    }

    // If searched entire table
    if(indexStart == index)
    {
      printf("ERROR: Table is full\n");
      return NULL;
    }
  }

  return IMABE_TABLE[index];
}

// Attempts to mark an entry as deleted
RETURN_TYPE DeleteEntry( char *Key )
{
  unsigned index = UHashMod( Key );
  unsigned indexStart = index;

  // Only search through clusters, don't hop over empty entries
  while(!IsEmpty( IMABE_TABLE, index ))
  {
    // Break from loop if found matching entry
    if(IMABE_TABLE[index] != DELETED)
    {
      if(strcmp(IMABE_TABLE[index]->ID, Key) == 0)
      {
        DeallocateImage( IMABE_TABLE[index]->ID );
        IMABE_TABLE[index] = DELETED;
        isTableFull = FALSE;
        return RETURN_SUCCESS;
      }
    }

    ++index;

    // wraparound to beginning of table
    if(index == TABLESIZE)
    {
      index = 0;
    }

    // If searched entire table
    if(indexStart == index)
    {
      break;
    }
  }

  printf("ERROR: Failed to delete: %s; (entry not found).\n", Key);

  return RETURN_FAILURE;
}
