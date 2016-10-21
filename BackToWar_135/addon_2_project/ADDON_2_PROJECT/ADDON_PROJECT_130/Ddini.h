/***********************************************************************
 *Direct Draw initialisation module                    
 *
 * This module creates the Direct Draw object with the primary surface
 * and a backbuffer and sets 800x600x8 display mode.
 *
 ***********************************************************************/
#ifndef __DDINI_H_
#define __DDINI_H_
//#include "afx.h"
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <stdlib.h>
#include <stdarg.h>
#include "resource.h"
#include "lines.h"
#include "protest.h"
#define free _ExFree
#define malloc _ExMalloc
void* _ExMalloc(int Size);
void _ExFree(void* Ptr);
inline void* _cdecl operator new(size_t size)
{
 return malloc(size);
};

inline void __cdecl operator delete(void *ptr)
{
 free(ptr);
};
#define CEXPORT __declspec(dllexport)
#define CIMPORT __declspec(dllimport)
//#define STARFORCE
#define MAKE_PTC
#define DLLEXPORT extern "C" __declspec(dllexport)

#ifndef STARFORCE
 #define DLL0(x) x()
 #define DLL1(x,y) x(y)
 #define DLL2(x,y,z) x(y,z)
 #define DLL3(x,y,z,t) x(y,z,t)
 #define SFLB_DLLEXPORT void
#else
 #define SFLB_DLLEXPORT extern "C" void __declspec(dllexport) __cdecl
 #define DLL0(x) x()
 #define DLL1(x,y) x(y)
 #define DLL2(x,y,z) x(y,z)
 #define DLL3(x,y,z,t) x(y,z,t)
#endif


//#ifndef __ddini_cpp_
extern LPDIRECTDRAW            lpDD;			   // DirectDraw object
extern LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
extern LPDIRECTDRAWSURFACE     lpDDSBack;      // DirectDraw back surface
extern BOOL                    bActive;        // is application active?
extern BOOL                    CurrentSurface; //=FALSE if backbuffer
											   // is active (Primary surface is visible)
											   //=TRUE if  primary surface is active
											   // (but backbuffer is visible)
extern BOOL                    DDError;        //=FALSE if Direct Draw works normally 
extern DDSURFACEDESC   ddsd;
extern HWND hwnd;
extern BOOL DDDebug;
/*  Create Direct Draw object
 * 
 * This procedure creadtes Direct Draw object with primary surface and 
 * one backbuffer and sets 800x600x8 display mode.
 * This procedure enables usage of all other procedure in thes module.
 */
bool CreateDDObjects(HWND hwnd);
/*     Closing all Direct Draw objects
 *
 * This procedure must be called before the program terminates,
 * otherwise Windows can occur some problems.
 */
void FreeDDObjects( void );
/*
 * Flipping Pages
 */
CEXPORT
void FlipPages(void);
/*
 * Getting Screen Pointer
 *
 * You will ge the pointer to the invisible area of the screen
 * i.e, if primary surface is visible, then you will obtain the
 * pointer to the backbuffer.
 * You must call UnlockSurface() to allow Windows draw on the screen
 */
void LockSurface(void);
/*
 *  Unlocking the surface 
 *
 *  You must unlock the Video memory for Windows to work properly
 */
void UnlockSurface(void);
/*
 * Getting then DC of the active (invisible) area of the screen
 */
HDC GetSDC(void);
//Sttting the palette
void LoadPalette(LPCSTR lpFileName);
void SetDebugMode();
void NoDebugMode();
//#endif
#endif //__DDINI_H_