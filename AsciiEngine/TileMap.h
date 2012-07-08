////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/8/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef TILEMAPH
#define TILEMAPH

#include "GlobalDefines.h"
#include "Shapes.h"

#define	COLLISION_LEFT		0x00000001	//0001
#define	COLLISION_RIGHT		0x00000002	//0010
#define	COLLISION_TOP		  0x00000004	//0100
#define	COLLISION_BOTTOM	0x00000008	//1000

typedef int COLLISION_FLAG;
typedef int CELL;

typedef enum
{
	NO_COLLISION,
	COLLISION
} COLLISION_TYPE;

typedef struct _MAPDATA
{
	int width;  // Width of the data array
	int height; // Height of the data array
	int *data;  // Data array
} MAPDATA;

typedef struct
{
  BOOL ACTIVE;            // Boolean for map system active/inactive
  int MAP_WIDTH;          // Width of the current map
  int MAP_HEIGHT;         // Height of the current map
  MAPDATA *TILE_MAP;      // Contains the current tile data array
  MAPDATA *COLLISION_MAP; // Contains the current collision data array
} TILE_MAP_SYSTEM_DATA;

extern MAPDATA *MapData;
extern MAPDATA *BinaryCollisionData;
extern int MAP_WIDTH;
extern int MAP_HEIGHT;

//
// MapBoundCheck
// Purpose: Checks to make sure a coordinate is within the boundaries of the
//          current map size.
//
BOOL MapBoundCheck( int x, int y );

//
//  SwapMap
//  Purpose: Swaps the current active map for another.
//
RETURN_TYPE SwapMap( const char *fileName );

//
// CellAt
// Purpose: Returns a pointer to the cell at a location
//
CELL *CellAt( MAPDATA *map, int x, int y );

//
// ImportMAPDATA
// Purpose: Imports a map from a data file
//
RETURN_TYPE ImportMAPDATA( const char *FileName );

//
// CheckHotspotCollision
// Purpose: Checks hotspots around a rectangle for collision within
//          a the current collision array.
//
COLLISION_FLAG CheckHotspotCollision( const AE_RECT rect );

//
// FreeMap
// Purpose: Frees the current map!
//
void FreeMap( void );

//
// DrawMap
// Purpose: Draws a map onto the DOUBLE_BUFFER
//
RETURN_TYPE DrawMap( void );

//
// MapSystemInit
// Purpose: Initialize various aspects of the MapSystem for tile mapping
//
RETURN_TYPE MapSystemInit( const char *FileName );

#endif  TILEMAPH