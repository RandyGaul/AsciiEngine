////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include "StringHash.h"

//
// This file contains macros for declaring and defining a typeless generic hash table.
// http://cecilsunkure.blogspot.com/2012/08/generic-programming-in-c.html
// http://cecilsunkure.blogspot.com/2012/07/hash-tables.html
//

#define HT_DELETED( type ) (type)(0xFFFFFFFF)

// Checks to see if an entry is empty
#define HT_IS_EMPTY( table, index ) \
  (table[index].data == NULL) ? TRUE : FALSE

// Checks to see if an entry can be placed in the index
#define HT_CAN_PLACE( TYPE, table, index ) \
  (HT_IS_EMPTY( table, index ) || table[index].data == HT_DELETED( TYPE )) ? TRUE : FALSE

// Checks to see if an index has an entry
#define HT_HAS_ENTRY( TYPE, table, index ) \
  (table[index].data != NULL && table[index].data != HT_DELETED( TYPE )) ? TRUE : FALSE

//
// DECLARE_TABLE
// Purpose: Declares a hash table of a specific type on the stack.
// Notes: MAX_NAME_LENGTH must be a constant unsigned int for stack declaration.
//
#define DECLARE_TABLE( TYPE, MAX_NAME_LENGTH ) \
  typedef struct TABLE_SLOT_##TYPE \
  { \
  char *ID; \
  TYPE data; \
  } SLOT_##TYPE; \
  \
  typedef struct TYPE##_TABLE \
  { \
    unsigned TABLESIZE; \
    BOOL isTableFull; \
    SLOT_##TYPE *ARRAY; \
  } TYPE##_TABLE; \
  \
  TYPE Find##TYPE( TYPE##_TABLE *TABLE, const char *Key ); \
  RETURN_TYPE Insert##TYPE( TYPE##_TABLE *TABLE, TYPE data, const char *ID ); \
  RETURN_TYPE Delete##TYPE( TYPE##_TABLE *TABLE, char *Key ); \
  TYPE##_TABLE *Allocate##TYPE##_TABLE( unsigned tableSize ); \
  RETURN_TYPE Deallocate##TYPE##_TABLE( TYPE##_TABLE *table )

//
// DEFINE_TABLE
// Purpose: Defines a hash table of a specific type on the stack.
// Notes: TABLESIZE must be a constant unsigned int for stack declaration.
//        MAX_NAME_LENGTH must be a constant unsigned int for stack declaration.
//        DELETE_DATA_FUNC is a pointer to the destructor for the data provided during,
//        insertion. No function will be called if this parameter is NULL.
//
#define DEFINE_TABLE( TYPE, DELETE_DATA_FUNC ) \
  \
  RETURN_TYPE (*DestructData##TYPE)( TYPE ) = DELETE_DATA_FUNC; \
  \
  /* Create Table */ \
  TYPE##_TABLE *Allocate##TYPE##_TABLE( unsigned tableSize ) \
  { \
    TYPE##_TABLE *table = (TYPE##_TABLE *)malloc( sizeof( TYPE##_TABLE ) + sizeof( SLOT_##TYPE ) * tableSize ); \
    table->isTableFull = FALSE; \
    table->TABLESIZE = tableSize; \
    table->ARRAY = (SLOT_##TYPE *)PtrAdd( table, sizeof( TYPE##_TABLE ) ); \
    memset( table->ARRAY, 0, sizeof( SLOT_##TYPE ) * table->TABLESIZE ); \
    return table; \
  } \
  \
  /* Destroy Table */ \
  RETURN_TYPE Deallocate##TYPE##_TABLE( TYPE##_TABLE *table ) \
  { \
    unsigned i = 0, count = 0; \
     \
    for(; i < table->TABLESIZE; ++i) \
    { \
      if(HT_HAS_ENTRY( TYPE, table->ARRAY, i )) \
      { \
        ++count; \
      } \
    } \
     \
    for(i = 0; i < table->TABLESIZE; ++i) \
    { \
      if(HT_HAS_ENTRY( TYPE, table->ARRAY, i )) \
      { \
        --count; \
        DestructData##TYPE( table->ARRAY[i].data ); \
        free( table->ARRAY[i].data ); \
      } \
    } \
     \
    free( table ); \
    return RETURN_SUCCESS; \
  } \
  \
  /* Attempt to insert an entry into the table */ \
  /* Will fail if no room or a duplicate key is found. */ \
  RETURN_TYPE Insert##TYPE( TYPE##_TABLE *TABLE, TYPE data, const char *ID ) \
  { \
    /* Retrieve hashed index from string */ \
    unsigned index = UHashMod( ID, TABLE->TABLESIZE ); \
    unsigned indexStart = index; \
    int len = strlen( ID ) + 1; \
     \
    /* Search for empty or deleted location in table with linear probing */ \
    while(!HT_CAN_PLACE( TYPE, TABLE->ARRAY, index )) \
    { \
      /* Break from the loop if a duplicate is found */ \
      if(strcmp( TABLE->ARRAY[index].ID, ID ) == 0) \
        break; \
         \
      ++index; \
       \
      /* wraparound to beginning of table instead of index beyond table */ \
      if(index == TABLE->TABLESIZE) \
      { \
        index = 0; \
      } \
       \
      /* If searched entire table (means table is full) */ \
      if(indexStart == index) \
      { \
        TABLE->isTableFull = TRUE; /* set the is##TYPE##TableFull flag */ \
        break; \
      } \
    } \
     \
    /* Skip the allocation process if a duplicate entry is found */ \
    if(HT_HAS_ENTRY( TYPE, TABLE->ARRAY, index )) \
    { \
      if(strcmp( TABLE->ARRAY[index].ID, ID ) == 0) \
      { \
        return RETURN_FAILURE; \
      } \
    } \
     \
    /* Skip the alloction process if there's no room in the table. */ \
    if(TABLE->isTableFull == TRUE) \
      return RETURN_FAILURE; \
       \
    TABLE->ARRAY[index].data = data; \
    TABLE->ARRAY[index].ID = (char *)malloc( len ); \
    memcpy( TABLE->ARRAY[index].ID, ID, len ); \
    return RETURN_SUCCESS; \
  } \
  \
  /* Looks up data given a specific key -- the whole point of using a hash map. */ \
  /* Instead of linearly searching, or doing a binary search in an ordered array, */ \
  /* you can use a hash function to generate an index and subsequently cut down */ \
  /* searh complexity to O(1 + nlk). Returns NULL if string is not found. */ \
  TYPE Find##TYPE( TYPE##_TABLE *TABLE, const char *Key ) \
  { \
    unsigned index = UHashMod( Key, TABLE->TABLESIZE ); \
    unsigned indexStart = index; \
     \
    /* Only search through clusters, don't hop over empty entries */ \
    while(!HT_IS_EMPTY( TABLE->ARRAY, index )) \
    { \
      /* Break from loop if found matching entry */ \
      if(TABLE->ARRAY[index].data != HT_DELETED( TYPE )) \
      { \
        if(strcmp(TABLE->ARRAY[index].ID, Key) == 0) \
          break; \
      } \
       \
      ++index; \
       \
      /* wraparound to beginning of table */ \
      if(index == TABLE->TABLESIZE) \
      { \
        index = 0; \
      } \
       \
      /* If searched entire table */ \
      if(indexStart == index) \
      { \
        printf("ERROR: Table is full\n"); \
        return NULL; \
      } \
    } \
     \
    return TABLE->ARRAY[index].data; \
  } \
  \
  /* Attempts to mark an entry as deleted */ \
  RETURN_TYPE Delete##TYPE( TYPE##_TABLE *TABLE, char *Key ) \
  { \
    unsigned index = UHashMod( Key, TABLE->TABLESIZE ); \
    unsigned indexStart = index; \
     \
    /* Only search through clusters, don't hop over empty entries */ \
    while(!HT_IS_EMPTY( TABLE->ARRAY, index )) \
    { \
      /* Break from loop if found matching entry */ \
      if(TABLE->ARRAY[index].data != HT_DELETED( TYPE )) \
      { \
        if(strcmp(TABLE->ARRAY[index].ID, Key) == 0) \
        { \
          if( DestructData##TYPE ) \
          { \
            DestructData##TYPE( TABLE->ARRAY[index].data ); \
          } \
          TABLE->ARRAY[index].data = HT_DELETED( TYPE ); \
          free( TABLE->ARRAY[index].ID ); \
          TABLE->ARRAY[index].ID = NULL; \
          TABLE->isTableFull = FALSE; \
          return RETURN_SUCCESS; \
        } \
      } \
       \
      ++index; \
       \
      /* wraparound to beginning of table */ \
      if(index == TABLE->TABLESIZE) \
      { \
        index = 0; \
      } \
       \
      /* If searched entire table */ \
      if(indexStart == index) \
      { \
        break; \
      } \
    } \
     \
    /* Unable to find matching key */ \
    return RETURN_FAILURE; \
  }

#define FIND_DATA( TYPE, TABLE, key ) \
  Find##TYPE( TABLE, key )

#define INSERT_DATA( TYPE, TABLE, data, key ) \
  Insert##TYPE( TABLE, data, key )

#define DELETE_DATA( TYPE, TABLE, key ) \
  Delete##TYPE( TABLE, key )

#define CREATE_TABLE( TYPE, TABLESIZE ) \
  Allocate##TYPE##_TABLE( TABLESIZE )

#define DESTROY_TABLE( TYPE, TABLE ) \
  Deallocate##TYPE##_TABLE( TABLE )

#define GET_TABLE_TYPE( TYPE ) \
  TYPE##_TABLE

#define GET_SLOT_TYPE( TYPE ) \
  SLOT_##TYPE
