#if !defined(D_SHOW_PLAY_H__F7D21729_B3D2_11D4_86BC_0080AD1CEC29__INCLUDED_)
#define D_SHOW_PLAY_H__F7D21729_B3D2_11D4_86BC_0080AD1CEC29__INCLUDED_

#include <windows.h>
#include <mmsystem.h>
#include <streams.h>

#define APPLICATIONNAME "PlayFile"
#define CLASSNAME "PlayFile"

#define WM_GRAPHNOTIFY  WM_USER+13
#define HELPER_RELEASE(x) { if (x) x->Release(); x = NULL; }


struct TDShowPlay
	{
		IBaseFilter   *pif;
		IGraphBuilder *pigb;
		IMediaControl *pimc;
		IMediaEventEx *pimex;
		IVideoWindow  *pivw;
		HWND          hNotifyWnd;
		CHAR          szFileName[255];
	};

typedef TDShowPlay* PDShowPlay;

PDShowPlay	StartFile(LPCSTR lpszFileName, HWND hNotifyWnd);

BOOL		StopFile(PDShowPlay pDSP);

#endif // !defined(D_SHOW_PLAY_H__F7D21729_B3D2_11D4_86BC_0080AD1CEC29__INCLUDED_)