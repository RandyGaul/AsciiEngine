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
// CheckHotspotCollision
// Purpose: Checks hotspots around a rectangle for collision within
//          a the current collision array.
//
COLLISION_FLAG CheckHotspotCollision( const AE_RECT rect )
{
	COLLISION_FLAG flag = 0;
  VECTOR2D hotspot = { 0 };
  CELL *thisCell = NULL;

	// Left up
  hotspot.x_ = rect.center_.x_ - rect.halfWidth_ + EPSILON;
  hotspot.y_ = rect.center_.y_ - rect.width_ / 4.f + EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_LEFT;
	  }
  }

	// Left down
	hotspot.x_ = rect.center_.x_ - rect.halfWidth_ + EPSILON;
  hotspot.y_ = rect.center_.y_ + rect.height_ / 4.f - EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_LEFT;
	  }
  }

	// Right up
	hotspot.x_ = rect.center_.x_ + rect.halfWidth_ - EPSILON;
  hotspot.y_ = rect.center_.y_ - rect.height_ / 4.f + EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_RIGHT;
    }
	}

	// Right down
	hotspot.x_ = rect.center_.x_ + rect.halfWidth_ - EPSILON;
	hotspot.y_ = rect.center_.y_ + rect.height_ / 4.f - EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_RIGHT;
    }
	}

	// Up left
  hotspot.x_ = rect.center_.x_ - rect.width_ / 4.f + EPSILON;
  hotspot.y_ = rect.center_.y_ - rect.halfHeight_ + EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_TOP;
    }
	}

	// Up Right
	hotspot.x_ = rect.center_.x_ + rect.width_ / 4.f - EPSILON;
	hotspot.y_ = rect.center_.y_ - rect.halfHeight_ + EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_TOP;
    }
	}

	// Down left
	hotspot.x_ = rect.center_.x_ - rect.width_ / 4.f + EPSILON;
	hotspot.y_ = rect.center_.y_ + rect.halfHeight_ - EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_BOTTOM;
    }
	}

	// Down Right
	hotspot.x_ = rect.center_.x_ + rect.width_ / 4.f - EPSILON;
	hotspot.y_ = rect.center_.y_ + rect.halfHeight_ - EPSILON;
  thisCell = CellAt( TILE_MAP_SYSTEM.COLLISION_MAP, FloatToInt( hotspot.x_ ), FloatToInt( hotspot.y_ ) );

  if(thisCell)
  {
	  if(*thisCell == COLLISION)
	  {
		  flag |= COLLISION_BOTTOM;
    }
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
	FILE *fp = fopen( FileName, "rb" );
  int x, y;

	if(fp)
	{
		// Set pointer to start of first number for width
		fseek( fp, 6, SEEK_SET );
		fscanf( fp, "%d", &TILE_MAP_SYSTEM.MAP_WIDTH );
		// Set pointer to start of second number for height
		fseek( fp, 8, SEEK_CUR );
		fscanf( fp, "%d", &TILE_MAP_SYSTEM.MAP_HEIGHT );

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
				fscanf( fp, "%d", dataCell );
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
  CHAR charData = 219;
  COL colorDataWhite = 15;
  COL colorDataBlue = 3;

  ImageSet( AllocateImage( "WhiteTile", 1, 1 ), &charData, &colorDataWhite );
  ImageSet( AllocateImage( "BlueTile", 1, 1 ), &charData, &colorDataBlue );

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
          WriteImageToScreen( "WhiteTile", x, y );
        }
        else if(*thisCell == 2)
        {
          WriteImageToScreen( "BlueTile", x, y );
        }
      }
    }
  }
  return RETURN_SUCCESS;
}
