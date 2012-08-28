////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file is used to maintain a hash table of ENTITY_CREATOR structs
// Documentation: http://cecilsunkure.blogspot.com/2012/07/hash-tables.html

#include "EntityCreatorTable.h"

DEFINE_TABLE( P_ENTITY_CREATOR, NULL );

GET_TABLE_TYPE( P_ENTITY_CREATOR ) *ENTITY_CREATOR_TABLE = NULL;

//
// CreatorTableGetEntryKeys
// Purpose: Returns an array of string pointers pointing to strings representing all
//          the various types of ID keys in the TABLE. The last key will be null to
//          detect when to end loop. No string is longer than maxStrLen (not counting null).
//
char **CreatorTableGetEntryKeys( unsigned maxStrLen )
{
  unsigned i = 0, count = 0;
  char **entries = NULL;

  for(; i < ENTITY_CREATOR_TABLE->TABLESIZE; ++i)
  {
    if(HT_HAS_ENTRY( P_ENTITY_CREATOR, ENTITY_CREATOR_TABLE->ARRAY, i ))
    {
      ++count;
    }
  }

  entries = (char **)malloc( sizeof( char *) * (count + 1) );
  memset( entries, 0, sizeof( char *) * (count + 1) );

  for(i = 0; i < ENTITY_CREATOR_TABLE->TABLESIZE; ++i)
  {
    if(HT_HAS_ENTRY( P_ENTITY_CREATOR, ENTITY_CREATOR_TABLE->ARRAY, i ))
    {
      unsigned len = strlen( ENTITY_CREATOR_TABLE->ARRAY[i].ID ) + 1;
      int size = (len < maxStrLen + 1) ? len : maxStrLen + 1;
      --count;
      entries[count] = (char *)malloc( size + 1 );
      memcpy( entries[count], ENTITY_CREATOR_TABLE->ARRAY[i].ID, size );
      entries[count][size] = 0;
    }
  }

  return entries;
}
