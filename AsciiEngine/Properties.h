////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

// This file contains various arbitrary categories for assigning
// properties to game entities as a bit-field

#define PLAYER                0x00000001
#define ENEMIES               0x00000002
#define DAMAGE_DEALER         0x00000004 // Will destroy self on-impact and send EM_DAMAGEHP
#define AXIS                  0x00000008 // TRUE is X, FALSE is Y
#define DRAWME                0x00000010 // TRUE draws FALSE does not
#define GRAVITYME             0x00000020 // TRUE then apply gravity, FALSE then not
#define DONT_COLLIDE_WITH_ME  0x00000040 // TRUE means others cannot collide with me
#define PICK_ME_UP_ITEM       0x00000080 // Enables items in item's properties to be picked up on contact
#define NO_PICKUP_ITEMS       0x00000100 // Disables ability to pickup items
