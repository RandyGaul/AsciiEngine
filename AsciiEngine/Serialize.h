////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/7/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include "Entity.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "ItemList.h"
#include "Component.h"
#include "SmallInventory.h"
#include "TileMap.h"

#define SERIALIZE_OPEN_FILE if(!fp) \
    fopen_s( &fp, FILENAME, "w" ); \
  if(fp)

#define DESERIALIZE_OPEN_FILE if(!fp) \
    fopen_s( &fp, FILENAME, "r" ); \
  if(fp)

#define MAX_SERIALIZER_STRLEN 100

//
// SerializerCloseFile
// Purpose: Makes the serializer shut down the current file in use.
//
void SerializerCloseFile( void );

//
// SerializerSetFile
// Purpose: Sets the current file name for the serializer to use.
//
void SerializerSetFile( const char *fileName );

//
// SerializeString
// Purpose: Writes a string to file.
//
void SerializeString( const char *string );

//
// DeserializeString
// Purpose: Reads a string in from file.
//
int DeserializeString( char *string );

//
// SerializeInt
// Purpose: Writes an int to file.
//
void SerializeInt( int val );

//
// DeserializeInt
// Purpose: Reads an int from file.
//
int DeserializeInt( int *val );

//
// SerializeFloat
// Purpose: Writes a float to file.
//
void SerializeFloat( float val );

//
// DeserializeFloat
// Purpose: Reads an int from file.
//
int DeserializeFloat( float *val );

//
// SerializeMapDimensions
// Purpose: Serializes the map's dimensions.
//
void SerializeMapDimensions( void );

//
// DeserializeMapDimensions
// Purpose: Deserializes the map's dimensions.
//
void DeserializeMapDimensions( void );

//
// EntityToFile
// Purpose: Serializes a game entity to a file. Overwrites existing files.
//
void EntityToFile( ENTITY *entity );

//
// FileToEntities
// Purpose: Deserializes all game entities from a file.
//
ENTITY *FileToEntities( const char *fileName );
