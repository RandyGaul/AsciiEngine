////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/15/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file contains a single function for easy maintaince of
// the initialization of all entity creators

#pragma once

#include "GlobalDefines.h"

//
// RegisterEntityClasses
// Purpose: Register all entity class types by entering their creators
//          into the creator map, and initialize class resources/names.
//
RETURN_TYPE RegisterEntityClasses( void );

//
// RegisterEntityComponents
// Purpose: Register all component classes by initializes class
//          resources and names.
//
RETURN_TYPE RegisterEntityComponents( void );
