#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "multipl.h"
#include "fog.h"
#include "walls.h"
#include "Nature.h"
#include <time.h>
#include "Nucl.h"
#include "TopZones.h"
#include "Megapolis.h"
#include "Dialogs.h"
#include "fonts.h"
#include "dpchat.h"
#include "dplobby.h"
#include "GSound.h"
#include "3DGraph.h"
#include "3DMapEd.h"
#include "MapSprites.h"
#include <assert.h>
#include <math.h>
#include "NewMon.h"
#include "IconTool.h"
#include "GP_Draw.h"
#include "3DRandMap.h"
#include <crtdbg.h>
#include "ActiveScenary.h"
#include "DrawForm.h"
#include "Conststr.h"
#include <Process.h>
#include "MPlayer.h"
#include "Recorder.h"
#include "GSINC.H"
#include "TopoGraf.h"
#include "PeerClass.h";
#include "CEngine\goaceng.h";
#include "StrategyResearch.h"
#include "Safety.h"
#include "EinfoClass.h"
#include "mode.h"
#pragma pack(4)
#include "InetRaiting\stats\gstats.h"
#include "InetRaiting\stats\gpersist.h"
#include "InetRaiting\gp.h"
#pragma pack(1)
#include "IR.H"
#include "bmptool.h"

void StartExplorer();
void FinExplorer();
void RunExplorer(int Index,char* ref,int x,int y,int x1,int y1);
void ProcessExplorer(int Index);
extern int ItemChoose;

typedef char* fnGetAccessKey(int);
typedef void fnSetAccessKey(int,char*);
extern fnGetAccessKey* GetAccessKey;
extern fnSetAccessKey* SetAccessKey;

bool MCHOOSE(SimpleDialog* SD){
	ItemChoose=SD->UserParam;
	return true;
};
char ACCESS[16]="";
void SlowLoadPalette(LPCSTR lpFileName);
void ExplorerOpenRef(int Index,char* ref);
void ShowCentralMessage(char* Message,int GPIDX);
void DarkScreen();
#include "Dialogs\NewLogin.h"