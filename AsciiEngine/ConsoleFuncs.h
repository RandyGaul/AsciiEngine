////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

// Documentation: http://cecilsunkure.blogspot.com/2011/12/windows-console-game-set-custom-color.html

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>

extern HANDLE OUTPUT_HANDLE; /* write (output) handle */
extern HANDLE INPUT_HANDLE; /* read (input handle */

#define WM_SETCONSOLEINFO (WM_USER+201) 
#pragma pack(push, 1) 
typedef struct _CONSOLE_INFO
{
  ULONG Length;
 COORD ScreenBufferSize;
 COORD WindowSize;
 ULONG WindowPosX;
 ULONG WindowPosY;
 COORD FontSize;
 ULONG FontFamily;
 ULONG FontWeight;
 WCHAR FaceName[32];
 ULONG CursorSize;
 ULONG FullScreen;
 ULONG QuickEdit;
 ULONG AutoPosition;
 ULONG InsertMode;
 USHORT ScreenColors;
 USHORT PopupColors;
 ULONG HistoryNoDup;
 ULONG HistoryBufferSize;
 ULONG NumberOfHistoryBuffers;
 COLORREF ColorTable[16];
 ULONG CodePage;
 HWND Hwnd;
 WCHAR ConsoleTitle[0x100];
 } CONSOLE_INFO;
#pragma pack(pop) 

typedef struct CONSOLE_FONT
{
  DWORD index;
  COORD dimension;
} CONSOLE_FONT;

#if(_WIN32_WINNT < 0x0600)
typedef struct _CONSOLE_FONT_INFOEX {
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT  FontFamily;
  UINT  FontWeight;
  WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
  ULONG      cbSize;
  COORD      dwSize;
  COORD      dwCursorPosition;
  WORD       wAttributes;
  SMALL_RECT srWindow;
  COORD      dwMaximumWindowSize;
  WORD       wPopupAttributes;
  BOOL       bFullscreenSupported;
  COLORREF   ColorTable[16];
} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;
#endif // _WIN32_WINNT < 0x0600

typedef BOOL (WINAPI *PGetCurrentConsoleFontEx)(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
typedef BOOL (WINAPI *PSetCurrentConsoleFontEx)(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
typedef BOOL (WINAPI *PGetConsoleScreenBufferInfoEx)(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);
typedef BOOL (WINAPI *PSetConsoleScreenBufferInfoEx)(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);


typedef BOOL (WINAPI *PSetConsoleFont)(HANDLE, DWORD);
typedef BOOL (WINAPI *PGetConsoleFontInfo)(HANDLE, BOOL, DWORD, CONSOLE_FONT*);
typedef int (WINAPI *PGetNumberOfConsoleFonts)();

BOOL SetConsoleInfo(HWND hwndConsole, CONSOLE_INFO *pci);
VOID WINAPI SetConsolePalette(COLORREF palette[], int fontX, int fontY, wchar_t *fontName);
static void GetConsoleSizeInfo(CONSOLE_INFO *pci, HANDLE hOutput);
int windowsVersionTest(void);
void initConsole(unsigned short *title, wchar_t *fontName, int fontx, int fonty);
void RenderScreen( void );
