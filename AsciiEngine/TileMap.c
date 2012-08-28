////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/8/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "TileMap.h"
#include "Math2D.h"
#include "Graphics.h"

// Documentation for this file:
// http://cecilsunkure.blogspot.com/2012/04/binary-collision-maps-platformer.html

// Globals
TILE_MAP_SYSTEM_DATA TILE_MAP_SYSTEM = { 0 };

//
// MapBoundCheck
// Purpose: Checks to make sure a coordinate is within the boundaries of the
//          current map size.
//
BOOL MapBoundCheck( int x, int y )
{
  return (x < TILE_MAP_SYSTEM.MAP_WIDTH &&
          x > -1 &&
          y < TILE_MAP_SYSTEM.MAP_HEIGHT &&
          y > -1) ? TRUE : FALSE;
}

//
// DimensionClampX
// Returns a clamped version of a coordinate
//
int DimensionClampX( int x )
{
  if(x > 0)
    return (x > TILE_MAP_SYSTEM.MAP_WIDTH) ? TILE_MAP_SYSTEM.MAP_WIDTH : x;
  else
    return 0;
}

//
// DimensionClampY
// Returns a clamped version of a coordinate
//
int DimensionClampY( int y )
{
  if(y > 0)
    return (y > TILE_MAP_SYSTEM.MAP_HEIGHT) ? TILE_MAP_SYSTEM.MAP_HEIGHT : y;
  else
    return 0;
}

//
// CellAt
// Purpose: Returns a pointer to the cell at a location
//
CELL *CellAt( MAPDATA *map, int x, int y )
{
  if(MapBoundCheck( x, y ))
  {
    return (int *)(PtrAdd( map->data, (y * map->width + x) * sizeof( int ) ));
  }
  return NULL;
}

//
// HotSpotCollisionCheck
// Purpose: Small utility function for CheckHotspotCollision readability
//
BOOL HotSpotCollisionCheck( VECTOR2D hotspot )
{
  int x, y;
  AE_RECT TILE = { 0 };
  CELL *thisCell = NULL;
  TILE.width_ = 1.f;
  TILE.height_ = 1.f;

	for(y = 0; y < TILE_MAP_SYSTEM.MAP_HEIGHT; y++)
	{
		for(x = 0; x < TILE_MAP_SYSTEM.MAP_WIDTH; x++)
		{
      thisCell = CellAt( TILE_MAP_SYSTEM.TILE_MAP, x, y );

      if(*thisCell == COLLISION)
      {
        TILE.center_.x_ = (float)x;
        TILE.center_.y_ = (float)y;
        if(StaticPointToStaticRect( &hotspot, &TILE ))
        {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

//
// CheckHotspotCollision
// Purpose: Checks hotspots around a rectangle for collision within
//          a the current collision array.
//
COLLISION_FLAG CheckHotspotCollision( const AE_RECT rect )
{
  char buffer[100];
	COLLISION_FLAG flag = 0;
  VECTOR2D hotspot = { 0 };

	// Left up
  hotspot.x_ = rect.center_.x_ - rect.width_ / 2.f;
  hotspot.y_ = rect.center_.y_ - rect.width_ / 4.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_LEFT;
  }

	// Left down
	hotspot.x_ = rect.center_.x_ - rect.width_ / 2.f;
  hotspot.y_ = rect.center_.y_ + rect.height_ / 4.f;
  sprintf_s( buffer, 100, "hotspot left down: %f, %f", hotspot.x_, hotspot.y_ );
  WriteStringToScreen( buffer, 1, 40 );

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_LEFT;
  }

	// Right up
	hotspot.x_ = rect.center_.x_ + rect.width_ / 2.f;
  hotspot.y_ = rect.center_.y_ - rect.height_ / 4.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_RIGHT;
	}

	// Right down
	hotspot.x_ = rect.center_.x_ + rect.width_ / 2.f;
	hotspot.y_ = rect.center_.y_ + rect.height_ / 4.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_RIGHT;
	}

	// Up left
  hotspot.x_ = rect.center_.x_ - rect.width_ / 4.f;
  hotspot.y_ = rect.center_.y_ - rect.height_ / 2.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_TOP;
	}

	// Up Right
	hotspot.x_ = rect.center_.x_ + rect.width_ / 4.f;
	hotspot.y_ = rect.center_.y_ - rect.height_ / 2.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_TOP;
	}

	// Down left
	hotspot.x_ = rect.center_.x_ - rect.width_ / 4.f;
	hotspot.y_ = rect.center_.y_ + rect.height_ / 2.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_BOTTOM;
	}

	// Down Right
	hotspot.x_ = rect.center_.x_ + rect.width_ / 4.f;
	hotspot.y_ = rect.center_.y_ + rect.height_ / 2.f;

  if(HotSpotCollisionCheck( hotspot ))
  {
		flag |= COLLISION_BOTTOM;
	}

	return flag;
}

//
// ImportMAPDATA
// Purpose: Imports a map from a data file.
// Notes  : This function needs to be updated in order to construct
//          a proper binary array. For example, if you add in a new type
//          of tile, then this function needs to know if that tile is
//          supposed to have collision or not in order to construct
//          the binary array.
//
RETURN_TYPE ImportMAPDATA( const char *FileName )
{
	FILE *fp;
  int x, y;

  fopen_s( &fp, FileName, "rb" );
  
	if(fp)
	{
		// Set pointer to start of first number for width
		fseek( fp, 6, SEEK_SET );
		fscanf_s( fp, "%d", &TILE_MAP_SYSTEM.MAP_WIDTH );
		// Set pointer to start of second number for height
		fseek( fp, 8, SEEK_CUR );
		fscanf_s( fp, "%d", &TILE_MAP_SYSTEM.MAP_HEIGHT );

		// Allocate space for our map structure and the array
		TILE_MAP_SYSTEM.TILE_MAP = (MAPDATA *)malloc( sizeof( MAPDATA ) +
									              TILE_MAP_SYSTEM.MAP_WIDTH * sizeof( int ) * TILE_MAP_SYSTEM.MAP_HEIGHT );
		TILE_MAP_SYSTEM.COLLISION_MAP = (MAPDATA *)malloc( sizeof( MAPDATA ) +
												        TILE_MAP_SYSTEM.MAP_WIDTH * sizeof( int ) * TILE_MAP_SYSTEM.MAP_HEIGHT );

		// Set our data pointer to point to beginning of our array
		TILE_MAP_SYSTEM.TILE_MAP->data = (int *)PtrAdd( TILE_MAP_SYSTEM.TILE_MAP, sizeof( MAPDATA ) );
		TILE_MAP_SYSTEM.COLLISION_MAP->data = (int *)PtrAdd( TILE_MAP_SYSTEM.COLLISION_MAP, sizeof( MAPDATA ) );
    
		// Initialize width and height components
		TILE_MAP_SYSTEM.TILE_MAP->width = TILE_MAP_SYSTEM.MAP_WIDTH;
		TILE_MAP_SYSTEM.TILE_MAP->height = TILE_MAP_SYSTEM.MAP_HEIGHT;
		TILE_MAP_SYSTEM.COLLISION_MAP->width = TILE_MAP_SYSTEM.MAP_WIDTH;
		TILE_MAP_SYSTEM.COLLISION_MAP->height = TILE_MAP_SYSTEM.MAP_HEIGHT;

		// Initialize data arrays
		for(y = 0; y < TILE_MAP_SYSTEM.MAP_HEIGHT; ++y)
		{
			for(x = 0; x < TILE_MAP_SYSTEM.MAP_WIDTH; ++x)
			{
				int *dataCell, *thisCell;
				dataCell = CellAt( TILE_MAP_SYSTEM.TILE_MAP, x, y );
				fscanf_s( fp, "%d", dataCell );
				thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, x, y );

				// Truncate to binary in order to construct the binary array
        // from the data array read from the input file
				if(*dataCell == 1 || *dataCell == 2)
        {
          *thisCell = COLLISION;
        }
        else
        {
          *thisCell = NO_COLLISION;
        }
			}
		}
    
		fclose( fp );
    TILE_MAP_SYSTEM.ACTIVE = TRUE;
		return RETURN_SUCCESS;
	}
	else
	{
    // File does not exist
		return RETURN_FAILURE;
	}
}

//
// FreeMap
// Purpose: Frees the current map!
//
void FreeMap( void )
{
	free( TILE_MAP_SYSTEM.TILE_MAP );
	free( TILE_MAP_SYSTEM.COLLISION_MAP );
  TILE_MAP_SYSTEM.ACTIVE = FALSE;
}

//
// MapSystemInit
// Purpose: Initialize various aspects of the MapSystem for tile mapping
//
RETURN_TYPE MapSystemInit( const char *FileName )
{
  if(ImportMAPDATA( FileName ) == RETURN_SUCCESS)
  {
    return RETURN_SUCCESS;
  }
  // Likely could not find your file to load
  return RETURN_FAILURE;
}

//
//  SwapMap
//  Purpose: Swaps the current active map for another.
//
RETURN_TYPE SwapMap( const char *fileName )
{
  FreeMap( );
  if(ImportMAPDATA( fileName ) == RETURN_SUCCESS)
  {
    return RETURN_SUCCESS;
  }
  // Likely could not find your file to load
  return RETURN_FAILURE;
}

//
// DrawMap
// Purpose: Draws a map onto the DOUBLE_BUFFER
//
RETURN_TYPE DrawMap( void )
{
  int x, y;
  CELL *thisCell = NULL;

	for(y = 0; y < TILE_MAP_SYSTEM.MAP_HEIGHT; y++)
	{
		for(x = 0; x < TILE_MAP_SYSTEM.MAP_WIDTH; x++)
		{
      thisCell = CellAt( TILE_MAP_SYSTEM.TILE_MAP, x, y );

      if(thisCell)
      {
        if(*thisCell == 1)
        {
          WriteImageToScreen( "WhiteSquare.AEArt", x, y );
        }
        else if(*thisCell == 2)
        {
          WriteImageToScreen( "BlueSquare.AEArt",  x, y );
        }
      }
    }
  }
  return RETURN_SUCCESS;
}

RETURN_TYPE CreateTileEntitiesFromMap( void )
{
  int x, y;
  CELL *thisCell = NULL;

	for(y = 0; y < TILE_MAP_SYSTEM.MAP_HEIGHT; y++)
	{
		for(x = 0; x < TILE_MAP_SYSTEM.MAP_WIDTH; x++)
		{
      float xf = (float)x, yf = (float)y;
      thisCell = CellAt( TILE_MAP_SYSTEM.TILE_MAP, x, y );

      if(thisCell)
      {
        if(*thisCell == 1)
        {
          CreateEntity( "TILE", (int)&xf, (int)&yf );
        }
      }
    }
  }

  return RETURN_SUCCESS;
}
