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

extern RETURN_TYPE (*Load)( void );
extern RETURN_TYPE (*Initialize)( void );
extern RETURN_TYPE (*Update)( void );
extern RETURN_TYPE (*Draw)( void );
extern RETURN_TYPE (*Free)( void );
extern RETURN_TYPE (*Unload)( void );

int GSM_Initialize( stateIndicator initVal );
int GSM_Update( void );

#endif // GAMESTATEMANAGERH