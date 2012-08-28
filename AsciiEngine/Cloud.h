////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/19/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include "Loci.h"
#include "GraphicsComponent.h"

//
// CLOUD class
// This class is derived from the GRAPHICS_COMPONENT base, and represents
// a two dimensional sprite image.
//
typedef struct _CLOUD_COMPONENT
{
  GRAPHICS_COMPONENT base;
  GET_TABLE_TYPE( P_LOCUS ) *loci;
} CLOUD;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void CloudCOM_PROC( CLOUD *self, EM msg, int var1, int var2 );

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void CloudCreate( CLOUD *self, int tableSize );

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void CloudInit( const char *className );

//
// ComponentDraw
// Purpose: Simply renders the animation.
//
void CloudDraw( CLOUD *self );

//
// AnimationUpdate
// Purpose: Updates the animation's internal timer, allowing to flip through the frames.
//
void CloudUpdate( CLOUD *self, float *dt );

//
// CloudInsertPoint
// Purpose: Inserts a point (LOCUS) into the cloud.
//
void CloudInsertLocus( CLOUD *self, LOCUS *locus );

//
// CloudGetLocus
// Purpose: Retrieves a pointer to a specific locus by const char *var1
//          stores pointer in LOCUS *var2
//
void CloudGetLocus( CLOUD *self, const char *name, LOCUS* locus );

//
// CloudSetLocusImage
// Purpose: Swaps the image * of locus const char *var1 with IMAGE *var2
//
void CloudSetLocusImage( CLOUD *self, const char *name, IMAGE *image );

//
// CloudSetLocusAnimation
// Purpose: Swaps the image * of locus const char *var1 with IMAGE *var2
//
void CloudSetLocusAnimation( CLOUD *self, const char *name, ANIMATION *animation );

//
// CloudDeallocateLocusAnimation
// Purpose: Deallocates the animation of a specific locus at const char *var1
//
void CloudDeallocateLocusAnimation( CLOUD *self, const char *name );

//
// CloudLocusToggleActive
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusToggleActive( CLOUD *self, const char *name );

//
// CloudLocusSetActive
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusSetActive( CLOUD *self, const char *name, BOOL *activity );

//
// CloudLocusOn
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusOn( CLOUD *self, const char *name );

//
// CloudLocusOff
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusOff( CLOUD *self, const char *name );
