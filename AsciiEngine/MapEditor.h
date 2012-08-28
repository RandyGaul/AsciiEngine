////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/10/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "GlobalDefines.h"

#define VIEWPORT_SCROLL_SPEED 15.0f
#define VIEWPORT_OFFSET_X -7.5f
#define VIEWPORT_OFFSET_Y 6.f

#define VIEWPORT_HEIGHT 32.0f
#define VIEWPORT_WIDTH 57.0f

RETURN_TYPE MapEditorLoad( void );
RETURN_TYPE MapEditorInit( void );
RETURN_TYPE MapEditorUpdate( void );
RETURN_TYPE MapEditorDraw( void );
RETURN_TYPE MapEditorFree( void );
RETURN_TYPE MapEditorUnload( void );
