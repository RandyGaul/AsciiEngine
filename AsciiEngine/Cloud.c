////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/19/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Cloud.h"
#include "EntityManager.h"
#include "Camera.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void CloudCOM_PROC( CLOUD *self, EM msg, int var1, int var2 )
{
  // GENERAL
  switch(msg)
  {
  case EM_CLSINIT:
    CloudInit( (const char *)var1 );
    break;
  case EM_CREATE:
    CloudCreate( self, (unsigned)var1 );
    break;
  case EM_DRAW:
    CloudDraw( self );
    break;
  case EM_UPDATE:
    CloudUpdate( self, (float *)var1 );
    break;

  // DATA ACCESS
  case EM_GETLOCUS:
    CloudGetLocus( self, (const char *)var1, (LOCUS *)var2 );
    break;
  case EM_CLDSETIM:
    CloudSetLocusImage( self, (const char *)var1, (IMAGE *)var2 );
    break;
  case EM_CLDSETAN:
    CloudSetLocusAnimation( self, (const char *)var1, (ANIMATION *)var2 );
    break;
  case EM_INSLOCUS:
    CloudInsertLocus( self, (LOCUS *)var1 );
    break;
  case EM_CLDFREAN:
    CloudDeallocateLocusAnimation( self, (const char *)var1 );
    break;
  case EM_CLDTGLLC:
    CloudLocusToggleActive( self, (const char *)var1 );
    break;
  case EM_CLDSETLC:
    CloudLocusSetActive( self, (const char *)var1, (BOOL *)var2 );
    break;
  case EM_CLDOFFLC:
    CloudLocusOff( self, (const char *)var1 );
    break;
  case EM_CLDONLC:
    CloudLocusOn( self, (const char *)var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void CloudCreate( CLOUD *self, int tableSize )
{
  self->loci = CREATE_TABLE( P_LOCUS, tableSize );
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void CloudInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ComponentDraw
// Purpose: Simply renders the animation.
//
void CloudDraw( CLOUD *self )
{
  unsigned i = 0, zOrder = 0;
  VECTOR2D pos = { 0 };

  // Get object's position and width/height -- defaults are zero in case don't exist
  SendEntityMessage( self->base.owner, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
  for(; zOrder < HIGHEST_ZORDER; ++zOrder)
  {
    for(; i < self->loci->TABLESIZE; ++i)
    {
      if(self->loci->ARRAY[i].data)
      {
        // Skip inactive loci or if zOrder doesn't match
        if(!self->loci->ARRAY[i].data->isActive || self->loci->ARRAY[i].data->zOrder != zOrder)
          continue;

        // Draw if contains an image
        if(self->loci->ARRAY[i].data->image)
        {
          VECTOR2D WH = { (float)self->loci->ARRAY[i].data->image->width, (float)self->loci->ARRAY[i].data->image->height };
          WriteImageToScreen( self->loci->ARRAY[i].data->image->ID,
            FloatToInt( pos.x_ - CAMOFFX - WH.x_ / 2.f + self->loci->ARRAY[i].data->coord.x_ + DimensionOffset( WH.x_ ) ),
            FloatToInt( pos.y_ - CAMOFFY - WH.y_ / 2.f + self->loci->ARRAY[i].data->coord.y_ + 1.f ) );
        }
        // Else draw an animation
        else
        {
          VECTOR2D WH = { 0 };
          int currentFrame = self->loci->ARRAY[i].data->animation->currentFrame;
          SendEntityMessage( self->base.owner, EM_GETWH, (int)&WH.x_, (int)&WH.y_ );
          WriteImageToScreen( self->loci->ARRAY[i].data->animation->frames[currentFrame]->ID,
            FloatToInt( pos.x_ - CAMOFFX - WH.x_ / 2.f + self->loci->ARRAY[i].data->coord.x_ + DimensionOffset( WH.x_ ) ),
            FloatToInt( pos.y_ - CAMOFFY - WH.y_ / 2.f + self->loci->ARRAY[i].data->coord.y_ + 1.f ) );
        }
      }
    }
  }
}

//
// CloudUpdate
// Purpose: Updates the cloud's animation's internal timers, allowing to flip through the frames.
//
void CloudUpdate( CLOUD *self, float *dt )
{
  unsigned i = 0;

  for(; i < self->loci->TABLESIZE; ++i)
  {
    if(self->loci->ARRAY[i].data)
    {
      // Skip inactive loci
      if(!self->loci->ARRAY[i].data->isActive)
        continue;

      // Update any found animations
      if(self->loci->ARRAY[i].data->animation)
      {
        UpdateAnimation( self->loci->ARRAY[i].data->animation, *dt );
      }
    }
  }
}

//
// CloudInsertLocus
// Purpose: Inserts a locus from LOCUS *var1 into the cloud.
//
void CloudInsertLocus( CLOUD *self, LOCUS *locus )
{
  INSERT_DATA( P_LOCUS, self->loci, locus, locus->ID );
}

//
// CloudGetLocus
// Purpose: Retrieves a pointer to a specific locus by const char *var1
//          stores pointer in LOCUS *var2
//
void CloudGetLocus( CLOUD *self, const char *name, LOCUS* locus )
{
  locus = FIND_DATA( P_LOCUS, self->loci, name );
}

//
// CloudSetLocusImage
// Purpose: Swaps the image * of locus const char *var1 with IMAGE *var2
//
void CloudSetLocusImage( CLOUD *self, const char *name, IMAGE *image )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );

  assert( locus->image );
  if(locus->image)
  {
    locus->image = image;
  }
}

//
// CloudSetLocusAnimation
// Purpose: Swaps the image * of locus const char *var1 with ANIMATION *var2
//
void CloudSetLocusAnimation( CLOUD *self, const char *name, ANIMATION *animation )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );

  assert( locus->animation );
  if(locus->animation)
  {
    locus->animation = animation;
  }
}

//
// CloudDeallocateLocusAnimation
// Purpose: Deallocates the animation of a specific locus at const char *var1
//
void CloudDeallocateLocusAnimation( CLOUD *self, const char *name )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );

  assert( locus->animation );
  if(locus->animation)
  {
    DeallocateAnimation( locus->animation );
  }
}

//
// CloudLocusToggleActive
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusToggleActive( CLOUD *self, const char *name )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );

  if(locus)
  {
    if(locus->isActive)
    {
      locus->isActive = FALSE;
    }
    else
    {
      locus->isActive = TRUE;
    }
  }
}

//
// CloudLocusSetActive
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusSetActive( CLOUD *self, const char *name, BOOL *activity )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );
  locus->isActive = *activity;
}

//
// CloudLocusOn
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusOn( CLOUD *self, const char *name )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );
  locus->isActive = TRUE;
}

//
// CloudLocusOff
// Purpose: Toggles activity of a locus const char *var1
//
void CloudLocusOff( CLOUD *self, const char *name )
{
  LOCUS *locus = FIND_DATA( P_LOCUS, self->loci, name );
  locus->isActive = FALSE;
}
