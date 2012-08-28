////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   8/7/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Serialize.h"

static FILE *fp = NULL;
static const char *FILENAME = NULL;

//
// SerializerCloseFile
// Purpose: Makes the serializer shut down the current file in use.
//
void SerializerCloseFile( void )
{
  fclose( fp );
  fp = NULL;
}

//
// SerializerSetFile
// Purpose: Sets the current file name for the serializer to use.
//
void SerializerSetFile( const char *fileName )
{
  if(fp)
  {
    SerializerCloseFile( );
  }

  FILENAME = fileName;
}

//
// SerializeString
// Purpose: Writes a string to file.
//
void SerializeString( const char *string )
{
  SERIALIZE_OPEN_FILE
  {
    fprintf_s( fp, "%s\n", string );
  }
}

//
// DeserializeString
// Purpose: Reads a string in from file.
//
int DeserializeString( char *string )
{
  DESERIALIZE_OPEN_FILE
  {
    return fscanf_s( fp, "%[^\n]", string, MAX_SERIALIZER_STRLEN - 1 );
  }
  return EOF;
}

//
// SerializeInt
// Purpose: Writes an int to file.
//
void SerializeInt( int val )
{
  SERIALIZE_OPEN_FILE
  {
    fprintf_s( fp, "%d\n", val );
  }
}

//
// DeserializeInt
// Purpose: Reads an int from file.
//
int DeserializeInt( int *val )
{
  DESERIALIZE_OPEN_FILE
  {
    int msg = fscanf_s( fp, "%d", val );
    fgetc( fp );
    return msg;
  }
  return EOF;
}

//
// SerializeFloat
// Purpose: Writes a float to file.
//
void SerializeFloat( float val )
{
  SERIALIZE_OPEN_FILE
  {
    fprintf_s( fp, "%f\n", val );
  }
}

//
// DeserializeFloat
// Purpose: Reads an int from file.
//
int DeserializeFloat( float *val )
{
  DESERIALIZE_OPEN_FILE
  {
    int msg = fscanf_s( fp, "%f", val );
    fgetc( fp );
    return msg;
  }
  return EOF;
}

//
// SerializeMapDimensions
// Purpose: Serializes the map's dimensions.
//
void SerializeMapDimensions( void )
{
  SERIALIZE_OPEN_FILE
  {
    SerializeInt( TILE_MAP_SYSTEM.MAP_WIDTH );
    SerializeInt( TILE_MAP_SYSTEM.MAP_HEIGHT );
  }
}

//
// DeserializeMapDimensions
// Purpose: Deserializes the map's dimensions.
//
void DeserializeMapDimensions( void )
{
  DESERIALIZE_OPEN_FILE
  {
    DeserializeInt( &TILE_MAP_SYSTEM.MAP_WIDTH );
    DeserializeInt( &TILE_MAP_SYSTEM.MAP_HEIGHT );
  }
}

//
// EntityToFile
// Purpose: Serializes a game entity to a file.
//
void EntityToFile( ENTITY *entity )
{
  SERIALIZE_OPEN_FILE
  {
    VECTOR2D pos = { 0 };
    int HP = 0;
    int i, inventoryNumElem = 0;
    ITEM_ID item;

    SerializeString( entity->CLASS_NAME );

    // Serialize position
    SendEntityMessage( entity, EM_GETPOS, (int)&pos.x_, (int)&pos.y_ );
    SerializeFloat( pos.x_ );
    SerializeFloat( pos.y_ );

    // Serialize HP
    SendEntityMessage( entity, EM_GETHP, (int)&HP, 0 );
    SerializeInt( HP );

    // Serialize inventory
    SendEntityMessage( entity, EM_GETINVSZ, (int)&inventoryNumElem, 0 );
    SerializeInt( inventoryNumElem );
    for(i = 0; i < inventoryNumElem; ++i)
    {
      SendEntityMessage( entity, EM_GETINV, (int)&item, i );
      SerializeInt( item );
    }
  }
}

//
// FileToEntities
// Purpose: Deserializes all game entities from a file.
//
ENTITY *FileToEntities( const char *fileName )
{
  ENTITY *entity = NULL;

  SerializerSetFile( fileName );
  
  DESERIALIZE_OPEN_FILE
  {
    DeserializeMapDimensions( );
    for(;;)
    {
      char CLASS_NAME[MAX_SERIALIZER_STRLEN] = { 0 };
      int hp = 0, inventoryNumElem = 0, i, item;
      VECTOR2D pos = { 0 };
      
      DeserializeString( CLASS_NAME );
      DeserializeFloat( &pos.x_ );
      DeserializeFloat( &pos.y_ );
      DeserializeInt( &hp );
      DeserializeInt( &inventoryNumElem );

      if(feof( fp ))
      {
        SerializerCloseFile( );
        return NULL;
      } 

      entity = CreateEntity( CLASS_NAME, 0, 0 );

      for(i = 0; i < inventoryNumElem; ++i)
      {
        DeserializeInt( &item );
        SendEntityMessage( entity, EM_SETINV, item, i );
      }

      SendEntityMessage( entity, EM_SETHP, hp, 0 );
      SendEntityMessage( entity, EM_SETPOS, (int)&pos.x_, (int)&pos.y_ );
    }
  }

  SerializerCloseFile( );

  return entity;
}
