////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef GAMESTATEMANAGERH
#define GAMESTATEMANAGERH

#include "GameStateList.h"

typedef unsigned int stateIndicator;

extern stateIndicator currentState;
extern stateIndicator previousState;
extern stateIndicator nextState;

extern int (*Load)( void );
extern int (*Initialize)( void );
extern int (*Update)( void );
extern int (*Draw)( void );
extern int (*Free)( void );
extern int (*Unload)( void );

int GSM_Initialize( stateIndicator initVal );
int GSM_Update( void );

#endif // GAMESTATEMANAGERH