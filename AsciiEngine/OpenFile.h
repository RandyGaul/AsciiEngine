////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef OPENFILEH
#define OPENFILEH

#include "GlobalDefines.h"
#include "Graphics.h"

BOOL OpenAEArtFile( const char *path, OPENFILENAMEA *ofn );
BOOL SaveAEArtFile( const char *path, OPENFILENAMEA *ofn );

//
// LoadAllArtAssets
// Purpose: Loads all art assets of .AEArt format from the Assets folder.
//
RETURN_TYPE LoadAllArtAssets( const char *directory );

//
// LoadAEArtFile
// Purpose: Loads a .AEArt file and places it into the table of image files
//
IMAGE *LoadAEArtFile( const char *folder, const char *fileName );

#endif  OPENFILEH