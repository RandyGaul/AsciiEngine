////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "StringHash.h"

//
// This file contains macros for declaring and defining a typeless generic linked list.
// http://cecilsunkure.blogspot.com/2012/08/generic-programming-in-c.html
//

//
// DECLARE_LIST
// Purpose: Declares a linked list of a specific type on the heap.
//
#define DECLARE_LIST( TYPE )     \
  typedef struct _NODE_##TYPE    \
  {                              \
    TYPE data;                   \
    void (*DeleteData)( TYPE );  \
    int order;                   \
    struct _NODE_##TYPE *next;   \
    struct _NODE_##TYPE *prev;   \
  } NODE_##TYPE;                 \
\
  struct _LIST_##TYPE; \
\
  typedef struct _LIST_VTABLE_##TYPE                                                \
  {                                                                                 \
    void (*Destroy)  ( struct _LIST_##TYPE *self );                                 \
    NODE_##TYPE *(*CreateNode)( TYPE data, void (*DeleteData)( TYPE ), int order ); \
    RETURN_TYPE (*Insert)   ( struct _LIST_##TYPE *self, NODE_##TYPE *node );       \
    void (*Remove)   ( struct _LIST_##TYPE *self, NODE_##TYPE *node );              \
  } _LIST_VTABLE_##TYPE;                                                            \
\
  extern const _LIST_VTABLE_##TYPE LIST_VTABLE_##TYPE; \
\
  typedef struct _LIST_##TYPE           \
  {                                     \
    NODE_##TYPE *list;                  \
    const _LIST_VTABLE_##TYPE *vtable;  \
  } LIST_##TYPE;                        \
\
  LIST_##TYPE *LIST_CONSTRUCT_##TYPE( void ); \
  NODE_##TYPE *NODE_CREATE_##TYPE( TYPE data, void (*DeleteData)( TYPE data ), int order ); \
  RETURN_TYPE LIST_INSERT_##TYPE ( LIST_##TYPE *self, NODE_##TYPE *node ); \
  void LIST_REMOVE_##TYPE ( LIST_##TYPE *self, NODE_##TYPE *node ); \
  void LIST_DESTROY_##TYPE ( LIST_##TYPE *self ); \
  void LIST_CALLER_##TYPE ( LIST_##TYPE *self, RETURN_TYPE (*callback)( NODE_##TYPE *, void * ), void *param ); \
  TYPE LIST_PEEK_##TYPE ( LIST_##TYPE *self )

//
// DEFINE_LIST
// Purpose: Defines a linked list of a specific type on the heap.
//
#define DEFINE_LIST( TYPE )                       \
  const _LIST_VTABLE_##TYPE LIST_VTABLE_##TYPE =  \
  {                                               \
    LIST_DESTROY_##TYPE,                          \
    NODE_CREATE_##TYPE,                           \
    LIST_INSERT_##TYPE,                           \
    LIST_REMOVE_##TYPE                            \
  };                                              \
\
  LIST_##TYPE *LIST_CONSTRUCT_##TYPE( void )                                  \
  {                                                                           \
    LIST_##TYPE *linkedList = (LIST_##TYPE *)malloc( sizeof( LIST_##TYPE ) ); \
    linkedList->list = NULL;                                                  \
    linkedList->vtable = &LIST_VTABLE_##TYPE;                                 \
    return linkedList;                                                        \
  }                                                                           \
\
  NODE_##TYPE *NODE_CREATE_##TYPE( TYPE data, void (*DeleteData)( TYPE ), int order )  \
  {                                                                                    \
    NODE_##TYPE *newNode = (NODE_##TYPE *)malloc( sizeof( NODE_##TYPE ) );             \
    newNode->data = data;                                                              \
    newNode->DeleteData = DeleteData;                                                  \
    newNode->order = order;                                                            \
    newNode->next = NULL;                                                              \
    newNode->prev = NULL;                                                              \
    return newNode;                                                                    \
  }                                                                                    \
\
  RETURN_TYPE LIST_INSERT_##TYPE ( LIST_##TYPE *self, NODE_##TYPE *node )  \
  {                                                                        \
    NODE_##TYPE *scan = NULL;                                              \
    if(!self)                                                              \
      return RETURN_FAILURE;                                               \
                                                                           \
    scan = self->list;                                                     \
                                                                           \
    if(scan) /* if list is not empty */                                    \
    {                                                                      \
      while(scan->next)                                                    \
      {                                                                    \
        if(scan->order <= node->order)                                     \
          break;                                                           \
        scan = scan->next;                                                 \
      }                                                                    \
                                                                           \
      /* beginning of list */                                              \
      if(!scan->prev)                                                      \
      {                                                                    \
        if(scan->order <= node->order)                                     \
        {                                                                  \
          node->next = scan;                                               \
          scan->prev = node;                                               \
          self->list = node;                                               \
        }                                                                  \
        else                                                               \
        {                                                                  \
          scan->next = node;                                               \
          node->prev = scan;                                               \
        }                                                                  \
      }                                                                    \
      /* if not at end of list */                                          \
      else if(scan->next)                                                  \
      {                                                                    \
        node->next = scan;                                                 \
        node->prev = scan->prev;                                           \
        scan->prev->next = node;                                           \
        scan->prev = node;                                                 \
      }                                                                    \
      else                                                                 \
      {                                                                    \
        if(scan->prev) /* If more than one item in list */                 \
        {                                                                  \
          if(scan->order <= node->order)                                   \
          {                                                                \
            node->next = scan;                                             \
            node->prev = scan->prev;                                       \
            scan->prev->next = node;                                       \
            scan->prev = node;                                             \
          }                                                                \
          else                                                             \
          {                                                                \
            node->prev = scan;                                             \
            scan->next = node;                                             \
          }                                                                \
        }                                                                  \
        else /* One item in list */                                        \
        {                                                                  \
          /* Place before or after depending on zOrder */                  \
          if(scan->order <= node->order)                                   \
          {                                                                \
            scan->prev = node;                                             \
            node->next = scan;                                             \
            self->list = node;                                             \
          }                                                                \
          else                                                             \
          {                                                                \
            scan->next = node;                                             \
            node->prev = scan;                                             \
          }                                                                \
        }                                                                  \
      }                                                                    \
    }                                                                      \
    else /* if list is empty */                                            \
    {                                                                      \
      self->list = node;                                                   \
    }                                                                      \
                                                                           \
    return RETURN_SUCCESS;                                                 \
  }                                                                        \
\
  void LIST_REMOVE_##TYPE ( LIST_##TYPE *self, NODE_##TYPE *node )   \
  {                                               \
    if(node->prev)                                \
    {                                             \
      node->prev->next = node->next;              \
      if(node->next)                              \
      {                                           \
        node->next->prev = node->prev;            \
      }                                           \
    }                                             \
    else if(node->next)                           \
    {                                             \
      self->list = node->next;                    \
      node->next->prev = NULL;                    \
    }                                             \
    else                                          \
    {                                             \
      self->list = NULL;                          \
    }                                             \
                                                  \
    if(node->DeleteData)                          \
    {                                             \
      node->DeleteData( node->data );             \
    }                                             \
    free( node );                                 \
  }                                               \
\
  void LIST_DESTROY_##TYPE ( LIST_##TYPE *self )  \
  {                                               \
    NODE_##TYPE *temp = NULL;                     \
    NODE_##TYPE *scan = self->list;               \
                                                  \
    while(scan)                                   \
    {                                             \
      temp = scan->next;                          \
      self->vtable->Remove( self, scan );         \
      scan = temp;                                \
    }                                             \
                                                  \
    free( self );                                 \
  }                                               \
\
  void LIST_CALLER_##TYPE ( LIST_##TYPE *self, RETURN_TYPE (*callback)( NODE_##TYPE *, void * ), void *param )  \
  {                                                                                                             \
    NODE_##TYPE *scan = self->list, *temp = NULL;                                                               \
                                                                                                                \
    while(scan)                                                                                                 \
    {                                                                                                           \
      temp = scan->next;                                                                                        \
      /* Stop the callback process if return type is not 0 */                                                   \
      if(callback( scan, param ))                                                                               \
      {                                                                                                         \
        scan = temp;                                                                                            \
        return;                                                                                                 \
      }                                                                                                         \
      scan = temp;                                                                                              \
    }                                                                                                           \
  }                                                                                                             \
\
  TYPE LIST_PEEK_##TYPE ( LIST_##TYPE *self ) \
  {                                           \
    return self->list->data;                  \
  }

//
// LIST_CONSTRUCT
// Purpose: Constructs and returns a new list object of specified type.
//
#define LIST_CONSTRUCT( TYPE ) \
  LIST_CONSTRUCT_##TYPE( )

//
// NODE_CREATE
// Purpose: Constructs and returns a new node of a specified type.
//
#define NODE_CREATE( TYPE, data, DeleteData, order ) \
  NODE_CREATE_##TYPE( data, DeleteData, order )

//
// LIST_INSERT
// Purpose: Inserts a node of specified type in position determined by the order
//          data member.
// Notes: Will return RETURN_FAILURE if list pointer is NULL.
//
#define LIST_INSERT( TYPE, listSelf, node ) \
  LIST_INSERT_##TYPE( listSelf, node )

//
// LIST_REMOVE
// Purpose: Removes (deallocates) a node of a specified type from a list.
//
#define LIST_REMOVE( TYPE, list, node ) \
  LIST_REMOVE_##TYPE( list, node )

//
// LIST_DESTROY
// Purpose: Removes (deallocates) a list and all its nodes of a specified type.
//
#define LIST_DESTROY( TYPE, listSelf ) \
  LIST_DESTROY_##TYPE( listSelf )

//
// LIST_CALLER
// Purpose: Uses a callback on all nodes while supplying a specified param.
//
#define LIST_CALLER( TYPE, self, callback, param ) \
  LIST_CALLER_##TYPE( self, callback, param )

//
// LIST_PEEK
// Purpose: Returns the data of the first in the list.
//
#define LIST_PEEK( TYPE, self ) \
  LIST_PEEK_##TYPE( self )

//
// General data type handling. These functions must be used to handle list and node
// objects/pointers directly.
//
#define LIST_TYPE( TYPE ) \
  LIST_##TYPE
#define NODE_TYPE( TYPE ) \
  NODE_##TYPE
