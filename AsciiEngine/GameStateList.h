////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#ifndef GAMESTATELISTH
#define GAMESTATELISTH

#include "GlobalDefines.h"
#include "TestLevel.h"
#include "TestLevel2.h"
#include "MapEditor.h"

enum GameState_
{
  Restart,
  Quit,
  TestLevel,
  TestLevel2,
  MapEditor,
} GAME_STATE;

#endif // GAMESTATELISTH