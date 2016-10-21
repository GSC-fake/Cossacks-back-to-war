#include "ddini.h"
#include <mmsystem.h>
#include <digitalv.h>
#include <windef.h>
#include <string.h>
#include <io.h>
MCIDEVICEID wAVIDeviceID;
MCIDEVICEID wMIDDeviceID;


void PlayAVI(HWND hwnd,LPCSTR mfile,int Top);
void PlayMIDI (HWND hwnd,LPCSTR mfile);
void CloseAVI (HWND hwnd);
void CloseMIDI(HWND hwnd);

LPSTR GetCDROMWithFile(LPSTR FN);

void PlayAVI(HWND hwnd,LPCSTR mfile,int Top)
{
 MCI_OPEN_PARMS			 OpenParams;
 MCI_PLAY_PARMS			 PlayParams;
 MCI_ANIM_WINDOW_PARMS   WindowParams;
 MCIERROR				 ME;
 
 OpenParams.lpstrDeviceType="AVIVideo";
 OpenParams.lpstrElementName=mfile;
 OpenParams.dwCallback=UINT(hwnd);

 ME=mciSendCommand(wAVIDeviceID,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
	              (DWORD)(LPVOID)&OpenParams);
 char ccc[250];
 if(ME){
	 mciGetErrorString(ME,ccc,250);
 };
 wAVIDeviceID=OpenParams.wDeviceID;

 WindowParams.hWnd=hwnd;
 ME=mciSendCommand(wAVIDeviceID,MCI_WINDOW,
	               //MCI_ANIM_WINDOW_HWND ,
				   MCI_DGV_WINDOW_HWND ,
                   (DWORD)(LPMCI_ANIM_WINDOW_PARMS)&WindowParams);
 if(ME){
	 mciGetErrorString(ME,ccc,250);
 };
 MCI_DGV_PUT_PARMS WND;
 WND.dwCallback=(DWORD)hwnd;
 WND.rc.left=0;
 WND.rc.top=Top;
 WND.rc.right=640;
 WND.rc.bottom=480-2*Top;
 ME=mciSendCommand(wAVIDeviceID, MCI_PUT, 
   MCI_DGV_PUT_DESTINATION |MCI_DGV_RECT , (DWORD) &WND);
 if(ME){
	 mciGetErrorString(ME,ccc,250);
 };
 PlayParams.dwCallback=UINT(hwnd);
 
 ME=mciSendCommand(wAVIDeviceID,MCI_PLAY,MCI_NOTIFY,
	               (DWORD)(LPVOID)&PlayParams);
 if(ME){
	 mciGetErrorString(ME,ccc,250);
 };
}

void PlayMIDI(HWND hwnd,LPCSTR mfile)
{
 MCI_OPEN_PARMS		OpenParams;
 MCI_PLAY_PARMS		PlayParams;
 MCIERROR			ME;
 
 OpenParams.lpstrDeviceType="sequencer";
 OpenParams.lpstrElementName=mfile;
 OpenParams.dwCallback=UINT(hwnd);

 ME=mciSendCommand(wMIDDeviceID,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
	               (DWORD)(LPVOID)&OpenParams);

 wMIDDeviceID=OpenParams.wDeviceID;

 PlayParams.dwCallback=UINT(hwnd);
 
 ME=mciSendCommand(wMIDDeviceID,MCI_PLAY,MCI_NOTIFY,
	               (DWORD)(LPVOID)&PlayParams);
}

void CloseAVI(HWND hwnd)
{
  mciSendCommand(wAVIDeviceID,MCI_CLOSE,0,0);
  RedrawWindow(hwnd,NULL,NULL,RDW_INVALIDATE);
}

void CloseMIDI(HWND hwnd)
{
  mciSendCommand(wMIDDeviceID,MCI_CLOSE,0,0);
}
char lpBuffer[256];
LPSTR GetCDROMWithFile(LPSTR FN)
{
  //char* lpBuffer=new char[256];
  int n=-1;
  struct _finddata_t  FDATA;
  char FullName[256]="";
  long FH; 
    
  int Length=GetLogicalDriveStrings(256,lpBuffer);
  for(int x=0;x<=(Length/4)-1;x++)
	  if(GetDriveType(&lpBuffer[x*4])==DRIVE_CDROM)
	  {
       FullName[0]=0;
       strcat(FullName,&lpBuffer[x*4]);
	   strcat(FullName,FN);
       
	   FH=_findfirst((LPSTR)FullName,&FDATA);
	   if(FH!=-1)
	   {
		   _findclose(FH);
		   n=x;
	   };
	  };

  if(n!=-1)
	  return &lpBuffer[n*4];
  else
	  return "none";
}
