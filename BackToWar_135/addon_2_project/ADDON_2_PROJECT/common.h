#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <string.h>

typedef unsigned short word;


#define GP_USER
#define DIALOGS_USER
#define FASTDRAW_USER
#define FONTS_USER
#define GFILE_USER

#define CEXPORT __declspec(dllexport)
#define CIMPORT __declspec(dllimport)

#include "addon_project_130\fastdraw.h"
#pragma pack(1)
#include "addon_project_130\gp_draw.h"
#include "addon_project_130\dialogs.h"
#include "addon_project_130\fonts.h"
#include "addon_project_130\arc\gscarch.h"
#include "addon_project_130\resfile.h"
#include "addon_project_130\gfile.h"

extern CIMPORT int RealLx;
extern CIMPORT int RealLy;
extern CIMPORT int SCRSizeX;
extern CIMPORT int SCRSizeY;
extern CIMPORT int RSCRSizeX;
extern CIMPORT int RSCRSizeY;
extern CIMPORT int COPYSizeX;
extern CIMPORT int Pitch;

extern CIMPORT char BuildVersion[32];

extern CIMPORT int FPSTime;
extern CIMPORT int ScrollSpeed;
extern CIMPORT int WarSound;
extern CIMPORT int WorkSound;
extern CIMPORT int OrderSound;
extern CIMPORT int MidiSound;
extern CIMPORT void StopPlayCD();
extern CIMPORT int GetCDVolume();
extern CIMPORT void SetCDVolume(int Vol);
extern CIMPORT char RECFILE[128];
extern CIMPORT int ModeLX[32];
extern CIMPORT int ModeLY[32];
extern CIMPORT int NModes;
extern CIMPORT char PlName[64];
extern CIMPORT bool KeyPressed;
extern CIMPORT int NameChoose;
extern CIMPORT int ItemChoose;
extern CIMPORT char IPADDR[128];
extern CIMPORT int CurProtocol;
extern CIMPORT bool TOTALEXIT;
extern CIMPORT int LastKey;

CIMPORT void CBar(int x0,int y0,int Lx0,int Ly0,byte c);
CIMPORT bool MMItemChoose(SimpleDialog* SD);
CIMPORT int GETV(char* Name);
CIMPORT char* GETS(char* Name);
CIMPORT void LoadFog(int set);
CIMPORT bool MMChooseName(SimpleDialog* SD);
CIMPORT bool ProcessMessages();
CIMPORT void StdKeys();
CIMPORT void SlowLoadPalette(LPCSTR lpFileName);
CIMPORT void SlowUnLoadPalette(LPCSTR lpFileName);
CIMPORT void SavePlayerData();
CIMPORT void LoadPlayerData();
CIMPORT int CurPalette;
