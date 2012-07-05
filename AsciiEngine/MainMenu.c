////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// The various functions for a demonstration state called "MainMenu"
// The MainMenu state isn't actually a menu though...
// More information: http://cecilsunkure.blogspot.com/2012/02/game-program-design-game-state-manager.html

#include <stdio.h>
#include <stdlib.h>

#include "GameStateManager.h"
#include "GameStateList.h"
#include "GlobalDefines.h"
#include "Input.h"
#include "Graphics.h"
#include "Random.h"
#include "ConsoleFuncs.h"
#include "FrameRateController.h"

// Allows for management of GameObjects without including
// all the various game object headers to this file
#include "ObjectFactory.h"

int MainMenuLoad( void )
{
  // Allocate space for an image
  IMAGE *image = AllocateImage( "TestSun", 15, 15 );

  // Create arrays to temporarily hold the data for the image data
  CHAR charArray[15 * 15] = {
    255,255,255,255,255,255,255,177,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,177,255,255,255,177,255,255,255,177,255,255,255,
    255,255,255,255,177,255,255,255,255,255,177,255,255,255,255,
    255,255,255,255,255,255,177,177,177,255,255,255,255,255,255,
    255,255,255,255,255,177,178,219,178,177,255,255,255,255,255,
    255,255,255,255,177,178,219,219,219,178,177,255,255,255,255,
    177,255,177,255,177,219, 94,219, 94,219,177,255,177,255,177,
    255,255,255,255,177,178,219,126,219,178,177,255,255,255,255,
    255,255,255,255,255,177,178,219,178,177,255,255,255,255,255,
    255,255,255,255,255,255,177,177,177,255,255,255,255,255,255,
    255,255,255,255,177,255,255,255,255,255,177,255,255,255,255,
    255,255,255,177,255,255,255,177,255,255,255,177,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,177,255,255,255,255,255,255,255
  };
  COL colorArray[15 * 15] = {
    0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0,
    0,  0,  0,  0, 62,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 62, 62, 62,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 62, 62, 14, 62, 62,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 62, 62, 14, 14, 14, 62, 62,  0,  0,  0,  0,
   62,  0, 62,  0, 62, 14,224, 14,224, 14, 62,  0, 62,  0, 62,
    0,  0,  0,  0, 62, 62, 14,224, 14, 62, 62,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 62, 62, 14, 62, 62,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, 62, 62, 62,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 62,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,
    0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0, 62,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0,  0,  0,  0,  0
  };

  // Apply the image data to a specific image
  ImageSet( image, charArray, colorArray );

  AE_CreateObject( GO_REDSQUARE );
	return RETURN_SUCCESS;
}

int MainMenuInitialize( void )
{
  // Run the default initializer on all objects, any custom
  // initialization of an object will use the object's set
  // function, and should be done after this function call.
  AE_InitObjects( );
	return RETURN_SUCCESS;
}

int MainMenuUpdate( void )
{
  // You should use dt in this form whenever you require it
  float dt = GetDT( );

  // Run all objects' update functions.
  AE_UpdateObjects( );

  // Demonstration of how to draw an image to the DOUBLE_BUFFER
  // Note that the image will not be rendered to the screen unless RenderScreen
  // is called (and should only be called once per game loop within the
  // state's Draw function).
  if(IsKeyPressed( VK_ENTER ))
  {
    WriteImageToScreen( "TestSun", RandomInt( -15, BUFFERWIDTH ), RandomInt( -15, BUFFERHEIGHT ) );
  }
	return RETURN_SUCCESS;
}

int MainMenuDraw( )
{
  AE_DrawObjects( );
  // Renders the double buffer to the screen, only call this once per game loop!
  RenderScreen( );
	return RETURN_SUCCESS;
}

int MainMenuFree( void )
{
  DeallocateImage( "TestSun" );
	return RETURN_SUCCESS;
}

int MainMenuUnload( void )
{
	return RETURN_SUCCESS;
}