////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/9/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include "OpenFile.h"
#include "Graphics.h"

BOOL SaveAEArtFile( const char *path, OPENFILENAMEA *ofn )
{
  memset( ofn, 0, sizeof(*ofn));
  ofn->lStructSize     = sizeof( OPENFILENAME );
  ofn->hwndOwner       = NULL;
  ofn->hInstance       = NULL;
  ofn->lpstrFilter     = (LPCSTR)"AsciiEngine Art Files\0*.AEArt\0\0";    
  (const char *)ofn->lpstrFile       = path;
  ofn->lpstrFile[0]    = '\0';
  ofn->nMaxFile        = MAX_PATH;
  ofn->lpstrTitle      = (LPCSTR)"Select A Location To Save To";
  ofn->Flags           = OFN_NONETWORKBUTTON |
                      OFN_PATHMUSTEXIST |
                      OFN_HIDEREADONLY;
  if (GetSaveFileNameA( ofn ))
    return( TRUE );
  return FALSE;
}

BOOL OpenAEArtFile( const char *path, OPENFILENAMEA *ofn )
{
  memset( ofn, 0, sizeof(*ofn));
  ofn->lStructSize     = sizeof( OPENFILENAME );
  ofn->hwndOwner       = NULL;
  ofn->hInstance       = NULL;
  ofn->lpstrFilter     = (LPCSTR)"AsciiEngine Art Files\0*.AEArt\0\0";    
  (const char *)ofn->lpstrFile       = path;
  ofn->lpstrFile[0]    = '\0';
  ofn->nMaxFile        = MAX_PATH;
  ofn->lpstrTitle      = (LPCSTR)"Select A File To Open";
  ofn->Flags           = OFN_NONETWORKBUTTON |
                      OFN_FILEMUSTEXIST |
                      OFN_PATHMUSTEXIST |
                      OFN_HIDEREADONLY;
  if (GetOpenFileNameA( ofn ))
    return( TRUE );
  return FALSE;
}

//
// LoadAllArtAssets
// Purpose: Loads all art assets of .AEArt format from the Assets folder.
//
RETURN_TYPE LoadAllArtAssets( const char *directory )
{
  // Use a few functions from MSDN to cycle through the files of a folder
  WIN32_FIND_DATAA fileData = { 0 };
  HANDLE handle;
  char *searchString = "*.AEArt";

  // Allocate space to concatenate the folder and the fileName together
  int size = strlen( directory ) + strlen( searchString ) + 2;
  char *entireSearchString = (char *)malloc( size );

  // Copy the folder and fileName into the pathName array
  strcpy_s( entireSearchString, size, directory );
  strcat_s( entireSearchString, size, searchString );

  handle = FindFirstFileA( entireSearchString, &fileData );

  do
  {
    // For each file found, load it
    LoadAEArtFile( directory, fileData.cFileName );
  }
  while(FindNextFileA( handle, &fileData ) != 0);

  return RETURN_SUCCESS;
}

//
// LoadAEArtFile
// Purpose: Loads a .AEArt file and places it into the table of image files
//
IMAGE *LoadAEArtFile( const char *folder, const char *fileName )
{
  FILE *fp;
  OPENFILENAMEA ofn = { 0 };
  IMAGE *image = NULL;

  // Allocate space to concatenate the folder and the fileName together
  int size = strlen( folder ) + strlen( fileName ) + 2;
  char *pathName = (char *)malloc( size );

  // Copy the folder and fileName into the pathName array
  strcpy_s( pathName, size, folder );
  strcat_s( pathName, size, fileName );

  fopen_s( &fp, pathName, "r" );

  if(fp) // read image contents in file
  {
    int x, y;
    CHAR *thisChar;
    COL *thisColor;
    AE_COORD bottomRight = { 0 };

    fscanf_s( fp, "%d", &bottomRight.x_ );
    fscanf_s( fp, "%d", &bottomRight.y_ );

    image = AllocateImage( fileName, bottomRight.x_, bottomRight.y_ );

    for(y = 0; y < bottomRight.y_; ++y)
    {
      for(x = 0; x < bottomRight.x_; ++x)
      {
        thisChar = CharAt( image, x, y );
        fscanf_s( fp, "%d", thisChar );
      }
    }

    for(y = 0; y < bottomRight.y_; ++y)
    {
      for(x = 0; x < bottomRight.x_; ++x)
      {
        thisColor = ColorAt( image, x, y );
        fscanf_s( fp, "%d", thisColor );
      }
    }
    fclose( fp );
  }
  return image;
}
