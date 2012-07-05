////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/5/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef SHAPESH
#define SHAPESH

#include "Vector2D.h"

typedef struct _AE_CIRCLE
{
  VECTOR2D center_;
  float radius_;
} AE_CIRCLE;

typedef struct _AE_RECT
{
  VECTOR2D center_;
  int width_;
  int height_;
  int halfWidth_;
  int halfHeight_;
} AE_RECT;

#endif  SHAPESH