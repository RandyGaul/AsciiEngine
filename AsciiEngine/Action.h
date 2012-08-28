////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/16/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef ACTIONH
#define ACTIONH

#include "GlobalDefines.h"

typedef enum _ACTION_TYPE
{
  AT_BLOCKING,
  AT_NOT_BLOCKING,
  AT_DRAW,
  AT_DESTROY,
} AT;

typedef struct _ACTION
{
  AT type;
  AT isBlocking;
  void *PARAM;
  struct _ACTION *next;
  struct _ACTION *prev;
} ACTION;

#endif  ACTIONH