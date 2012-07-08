////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// This file mostly sets up the windows console, but also has some other
// various functionality.
// Documentation: http://cecilsunkure.blogspot.com/2011/12/windows-console-game-set-custom-color.html

#include "ConsoleFuncs.h"
#include "Graphics.h"

WCHAR CONSOLE_TITLE[MAX_CONSOLE_TITLE];

BOOL WINDOW_FOCUS = TRUE;     /* BOOL for storing window focus */
HANDLE OUTPUT_HANDLE;         /* write (output) handle */
HANDLE INPUT_HANDLE;          /* read (input handle */
HWND WINDOW_HANDLE;           /* Handle to window */
WNDPROC OLD_WNDPROC = { 0 };  /* Handle to the default wndproc */

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


/******************************************************************************
  initConsole

  Initializes various aspects of the console.
******************************************************************************/
void initConsole(unsigned short *title, wchar_t *fontName, int fontx, int fonty )
{
  // Used to center the window on the user's screen
  int x = GetSystemMetrics(SM_CXSCREEN) / 2;
  int y = GetSystemMetrics(SM_CYSCREEN) / 2;
  
    /* Setting the color palette to the default colors */
    /* Browse MSDN for COLORREF to learn more about these RGB values */
  COLORREF palette[16] = 
  {
    0x00000000, 0x001AA3ED, 0x002d5c2c, 0x007fb412,
    0x00000080, 0x005a4b61, 0x003e5f81, 0x00c0c0c0,
    0x00808080, 0x00f3a600, 0x0077c371, 0x00c8cc7a,
    0x000000ff, 0x00ff00ff, 0x003CFAFA, 0x00ffffff
  };
    /* Search MSDN for the RGB macro to easily generate COLORREF values */
    
  /* Window size coordinates, be sure to start index at zero! */
  SMALL_RECT windowSize = {0, 0, BUFFERWIDTH - 1, BUFFERHEIGHT - 1};

  /* A COORD struct for specificying the console's screen buffer dimensions */
  COORD bufferSize = {BUFFERWIDTH, BUFFERHEIGHT};
  
  CONSOLE_CURSOR_INFO cursorInfo = {1, 0};

  /* initialize handles */
  HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
  WINDOW_HANDLE = GetConsoleWindow( );

  /* initialize handles */
  OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
  INPUT_HANDLE = GetStdHandle(STD_INPUT_HANDLE);

  /* Set the console's title */
  SetConsoleTitle((LPCWSTR)title);
  
  /* Set cursor info */
  SetConsoleCursorInfo(wHnd, &cursorInfo);

  /* Set the console font settings and palette */
  SetConsolePalette(palette, fontx, fonty, fontName);
  
  /* Set the window size */
  SetConsoleWindowInfo(OUTPUT_HANDLE, TRUE, &windowSize);
  
  /* Set the screen's buffer size */
  SetConsoleScreenBufferSize(wHnd, bufferSize);

  /* Set the window size */
  SetConsoleWindowInfo(OUTPUT_HANDLE, TRUE, &windowSize);
  
  /* Set the window position */
  SetWindowPos(WINDOW_HANDLE, HWND_TOP, (x - ((BUFFERWIDTH / 2) * fontx)) - 5, (y - ((BUFFERHEIGHT / 2) * fonty)) - 5, 0, 0, SWP_NOSIZE);
}

/******************************************************************************
  windowsVersionTest

  Checks to see if have Vista/7 or earlier by attempting to retrieve function
  from kernel32.dll that is only available in Vista+ version of Windows.
******************************************************************************/
int windowsVersionTest(void)
{
    /* Retrieving pointers for Windows Vista/7 Functions */
  PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetCurrentConsoleFontEx");
    
    /* If exists then we have Vita/7 */
  if (pGetCurrentConsoleFontEx)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/******************************************************************************
  SetConsolePalette

  Sets the console palette and font size.
******************************************************************************/
VOID WINAPI SetConsolePalette(COLORREF palette[], int fontX, int fontY, wchar_t *fontName)
{ 
  int i;
  HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Retrieving pointers for Windows Vista/7 Functions */
  PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetCurrentConsoleFontEx");
  PSetCurrentConsoleFontEx pSetCurrentConsoleFontEx = (PSetCurrentConsoleFontEx)
    GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "SetCurrentConsoleFontEx");
  PGetConsoleScreenBufferInfoEx pGetConsoleScreenBufferInfoEx = (PGetConsoleScreenBufferInfoEx)
    GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetConsoleScreenBufferInfoEx");
  PSetConsoleScreenBufferInfoEx pSetConsoleScreenBufferInfoEx = (PSetConsoleScreenBufferInfoEx)
    GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "SetConsoleScreenBufferInfoEx");

    /* Check for pointers: if they exist, we have Vista/7 and we can use them */
  if (pGetCurrentConsoleFontEx && pSetCurrentConsoleFontEx &&
      pGetConsoleScreenBufferInfoEx && pSetConsoleScreenBufferInfoEx)
  {
    CONSOLE_SCREEN_BUFFER_INFOEX cbi; 
    CONSOLE_FONT_INFOEX cfi = {sizeof(CONSOLE_FONT_INFOEX)};

      /* Tell the font info how big it is, to avoid memory corruption */
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    pGetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

      /* Set the font type to name indicated by wide string literal */
      /* Set to 0 to keep current settings */
    lstrcpyW(cfi.FaceName, fontName);
    cfi.dwFontSize.X = fontX;  
    cfi.dwFontSize.Y = fontY;
    cfi.FontFamily = 0; /* Set to 0x30 for Terminal font */
    cfi.FontWeight = 0;

      /* Set the console font info */
    pSetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

      /* Get the size of the structure before filling the struct */
    cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    pGetConsoleScreenBufferInfoEx(hOutput, &cbi);

      /* Loop through the given palette, copying the data into the color table */
    for (i = 0 ; i < 16 ; ++i)
    {
      cbi.ColorTable[i] = palette[i];
    }
    
      /* Set the console screen buffer info */
    pSetConsoleScreenBufferInfoEx(hOutput, &cbi);
  }
  else  /* We don't have access to the vista functions */
  {
    int i;
    CONSOLE_INFO ci = { sizeof(ci) };
    HWND hwndConsole = GetConsoleWindow();

    GetConsoleSizeInfo(&ci, hOutput);

      /* Set to 0 to keep current settings */
    ci.FontSize.X = fontX;
    ci.FontSize.Y = fontY;
    ci.FontFamily = 0; /* Set to 0x30 for Terminal font */
    ci.FontWeight = 0;

    lstrcpyW(ci.FaceName, fontName); 
    ci.CursorSize = 100;
    ci.FullScreen = FALSE;
    ci.QuickEdit = FALSE;
    ci.AutoPosition = 0x10000;
    ci.InsertMode = TRUE;
    ci.ScreenColors = MAKEWORD(0x7, 0x0);
    ci.PopupColors = MAKEWORD(0x5, 0xf); 
    ci.HistoryNoDup = TRUE; 
    ci.HistoryBufferSize = 50; 
    ci.NumberOfHistoryBuffers = 4; 

    for(i = 0; i < 16; i++)
    {
      ci.ColorTable[i] = palette[i];
    }

    ci.CodePage = 0; 
    ci.Hwnd = hwndConsole;
    lstrcpyW(ci.ConsoleTitle, L""); 

    SetConsoleInfo(hwndConsole, &ci); 
  }
} 

/******************************************************************************
  GetConsoleSizeInfo (XP only)

  Fills up some info about the console font in the CONSOLE_INFO struct.
******************************************************************************/
static void GetConsoleSizeInfo(CONSOLE_INFO *pci, HANDLE hOutput)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(hOutput, &csbi);
  pci->ScreenBufferSize = csbi.dwSize;
  pci->WindowSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  pci->WindowSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  pci->WindowPosX = csbi.srWindow.Left;
  pci->WindowPosY = csbi.srWindow.Top;
}

/******************************************************************************
  SetConsoleInfo (XP only)

  Ends up sending a message to windows to reset the console info.
******************************************************************************/
BOOL SetConsoleInfo(HWND hwndConsole, CONSOLE_INFO *pci)
{
  DWORD dwConsoleOwnerPid;
  HANDLE hProcess;
  HANDLE hSection, hDupSection;
  PVOID ptrView = 0;
  HANDLE hThread;
  
  /* Open the process which "owns" the console */
  GetWindowThreadProcessId(hwndConsole, &dwConsoleOwnerPid);
  hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwConsoleOwnerPid);


  /* Create a SECTION object backed by page-file, then map a view of  */
  /* this section into the owner process so we can write the contents  */
  /* of the CONSOLE_INFO buffer into it  */
  hSection = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, pci->Length, 0);


  /* Copy our console structure into the section-object */
  ptrView = MapViewOfFile(hSection, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, pci->Length);
  memcpy(ptrView, pci, pci->Length); 
  UnmapViewOfFile(ptrView); 


  /* Map the memory into owner process  */
  DuplicateHandle(GetCurrentProcess(), hSection, hProcess, &hDupSection, 0, FALSE, DUPLICATE_SAME_ACCESS);

  /* Send console window the "update" message WM_SETCONSOLEINFO */
  SendMessage(hwndConsole, WM_SETCONSOLEINFO, (WPARAM)hDupSection, 0);

  /*clean up */
  hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)CloseHandle, hDupSection, 0, 0);
  CloseHandle(hThread);
  CloseHandle(hSection);
  CloseHandle(hProcess);
  return TRUE;
}

#include "Graphics.h"
#include "FrameRateController.h"

/* Wrapper function for writing to console */
void RenderScreen( void )
{ 
  /* Positions used to write to the screen */
  COORD charBufSize = {BUFFERWIDTH, BUFFERHEIGHT};
  COORD characterPos = {0,0};
  SMALL_RECT writeArea = {0,0,BUFFERWIDTH - 1,BUFFERHEIGHT - 1};

#ifdef DISPLAY_FPS
  char buffer[100];
  sprintf( buffer, "FPS: %d", (int)(1000.f / (float)(GetCurrentGameTime( ) - GetTimeAtFrameStart( ))) );
  WriteStringToScreen( buffer, BUFFERWIDTH - 8, 0 );
#endif // DISPLAY_FPS
  
  // This function renders to the console's screen buffer. This function is slow! Only
  // call this once per game loop at most.
  WriteConsoleOutputA( OUTPUT_HANDLE, DOUBLE_BUFFER, charBufSize, characterPos, &writeArea );
}
