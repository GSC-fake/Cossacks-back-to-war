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
typedef void fnInitSXP();
typedef void fnRunSXP(int,char*,int x,int y,int x1,int y1);
typedef void fnProcessSXP(int,DialogsSystem*);
typedef void fnSXP_Operation(int);
typedef char* fnGetAccessKey(int);
typedef void fnSetAccessKey(int,char*);
typedef void tpSXP_SetVar(int Index,char* Name,char* value);
typedef char* tpSXP_GetVar(int Index,char* Name);
typedef void tpOpenRef(int Index,char* home);
typedef void tpResizeSXP(int Index,int x,int y,int x1,int y1);
typedef void tpStartDownloadInternetFile(char* Name,char* Server,char* DestName);
typedef void tpProcessDownloadInternetFiles();
typedef void tpSendRecBuffer(byte* Data,int size,bool Final);
extern bool KeyPressed;
extern int LastKey;


HMODULE H_Exp=NULL;
HMODULE H_ExpOld=NULL;
fnInitSXP* InitSXP=NULL;
fnRunSXP* RunSXP=NULL;
fnProcessSXP* ProcessSXP=NULL;
fnGetAccessKey* GetAccessKey=NULL;
fnSetAccessKey* SetAccessKey=NULL;
fnSXP_Operation* SXP_StepBack=NULL;
fnSXP_Operation* SXP_StepForw=NULL;
fnSXP_Operation* SXP_Refresh=NULL;
tpSXP_SetVar* SXP_SetVar=NULL;
tpSXP_GetVar* SXP_GetVar=NULL;
tpOpenRef* OpenRef=NULL;
tpResizeSXP* ResizeSXP=NULL;
tpStartDownloadInternetFile* StartDownloadInternetFile=NULL;
tpProcessDownloadInternetFiles* ProcessDownloadInternetFiles=NULL;
tpSendRecBuffer* SendRecBuffer=NULL;


void InitDipFunctions();
CEXPORT
void StartExplorer(){
	//attempt to use advanced version
	ResFile F=RReset("Internet\\Cash\\IntExplorerNew.dll");
	if(F!=INVALID_HANDLE_VALUE){
		int sz=RFileSize(F);
		void* buf=malloc(sz);
		RBlockRead(F,buf,sz);
		RClose(F);
		F=RRewrite("IntExplorer.dll");
		if(F!=INVALID_HANDLE_VALUE){
			RBlockWrite(F,buf,sz);
			RClose(F);
		};
		free(buf);
		DeleteFile("Internet\\Cash\\IntExplorerNew.dll");
	};
	H_Exp=LoadLibrary("IntExplorer.dll");
	if(H_Exp){
		InitSXP=(fnInitSXP*)GetProcAddress(H_Exp,"InitSXP");
		if(InitSXP)InitSXP();
		RunSXP=(fnRunSXP*)GetProcAddress(H_Exp,"RunSXP");
		ProcessSXP=(fnProcessSXP*)GetProcAddress(H_Exp,"ProcessSXP");
		GetAccessKey=(fnGetAccessKey*)GetProcAddress(H_Exp,"?GetAccessKey@@YAPADH@Z");
		SetAccessKey=(fnSetAccessKey*)GetProcAddress(H_Exp,"?SetAccessKey@@YAXHPAD@Z");
		SXP_StepBack=(fnSXP_Operation*)GetProcAddress(H_Exp,"SXP_StepBack");
		SXP_StepForw=(fnSXP_Operation*)GetProcAddress(H_Exp,"SXP_StepForw");
		SXP_Refresh=(fnSXP_Operation*)GetProcAddress(H_Exp,"SXP_Refresh");
		SXP_SetVar=(tpSXP_SetVar*)GetProcAddress(H_Exp,"SXP_SetVar");
		SXP_GetVar=(tpSXP_GetVar*)GetProcAddress(H_Exp,"SXP_GetVar");
		OpenRef=(tpOpenRef*)GetProcAddress(H_Exp,"OpenRef");
		ResizeSXP=(tpResizeSXP*)GetProcAddress(H_Exp,"ResizeSXP");
		StartDownloadInternetFile=(tpStartDownloadInternetFile*)GetProcAddress(H_Exp,"?StartDownloadInternetFile@@YAXPAD00@Z");
		ProcessDownloadInternetFiles=(tpProcessDownloadInternetFiles*)GetProcAddress(H_Exp,"?ProcessDownloadInternetFiles@@YAXXZ");
		SendRecBuffer=(tpSendRecBuffer*)GetProcAddress(H_Exp,"?SendRecBuffer@@YAXPAEH_N@Z");
	};
	InitDipFunctions();
};

CEXPORT
void FinExplorer(){
	if(H_Exp){
		FreeLibrary(H_Exp);
		H_Exp=NULL;
		InitSXP=NULL;
		RunSXP=NULL;
		ProcessSXP=NULL;
		if(H_ExpOld)FreeLibrary(H_ExpOld);
	};
};
CEXPORT
void ExplorerBack(int Index){
	if(SXP_StepBack)SXP_StepBack(Index);
};
CEXPORT
void ExplorerForw(int Index){
	if(SXP_StepBack)SXP_StepForw(Index);
};
CEXPORT
void ExplorerRefresh(int Index){
	if(SXP_Refresh)SXP_Refresh(Index);
};
CEXPORT
void RunExplorer(int Index,char* ref,int x,int y,int x1,int y1){
	if(RunSXP){
		RunSXP(Index,ref,x,y,x1,y1);
	};
};
CEXPORT
void ProcessExplorer(int Index){
	if(ProcessSXP){
		ProcessSXP(Index,NULL);
	};
};
CEXPORT
void ProcessExplorerDSS(int Index,DialogsSystem* DSS){
	if(ProcessSXP){
		ProcessSXP(Index,DSS);
	};
};
CEXPORT
void ExplorerSetVar(int Index,char* Name,char* value){
	if(SXP_SetVar)SXP_SetVar(Index,Name,value);
};
CEXPORT
char* ExplorerGetVar(int Index,char* Name){
	if(SXP_SetVar)return SXP_GetVar(Index,Name);
	else return NULL;
};
CEXPORT
void ExplorerOpenRef(int Index,char* ref){
	if(OpenRef)OpenRef(Index,ref);
};
CEXPORT
void ExplorerResize(int Index,int x,int y,int x1,int y1){
	if(ResizeSXP)ResizeSXP(Index,x,y,x1,y1);
};
bool ProcessNewInternetLogin();

void StartTest(){
	StartExplorer();
	//ProcessNewInternetLogin();
	//Process_GSC_ChatWindow(1,NULL);
	return;
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Back_shell.bmp");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	RunExplorer(0,"LF|LW_new|open&req.txt",35,152,35+758,152+315-2);
	int t0=GetTickCount();
	do{
		DSS.ProcessDialogs();
		ProcessExplorer(0);
		DSS.RefreshView();
		if(t0&&GetTickCount()-t0>4000){
			t0=0;
			OpenRef(0,"LW_tbl&RTYEWQ&3&uuu&ttt&0&ghqfghfd&jhgjhgjh&1&jhggjh&ghfhgfhgf");
		};
	}while(LastKey!=27);
};
//initialisation diplomasy

typedef void fnVoid();
typedef void fnVoidLPB(byte*);
typedef void fnVoidLPC(char*);
typedef void tpSaveAllDipData(byte** ptr,int* size);
typedef void tpPerformDipCommand(char* Data,int size);
typedef void tpLoadAllDipData(byte* ptr,int size);
typedef void tpStartDownloadInternetFile(char* Name,char* Server,char* DestName);
typedef void tpProcessDownloadInternetFiles();
typedef void tpSendRecBuffer(byte* Data,int size,bool Final);

fnVoid* ProcessDipRelations=NULL;
fnVoid* InitDipForThisMap=NULL;
fnVoid* ClearAllDipData=NULL;
fnVoidLPB* FreeSaveDipData=NULL;
tpSaveAllDipData* SaveAllDipData=NULL;
tpLoadAllDipData* LoadAllDipData=NULL;
tpPerformDipCommand* PerformDipCommand=NULL;

void InitDipFunctions(){
	HMODULE HDIP=GetModuleHandle("DipServer.dll");
	ProcessDipRelations=(fnVoid*)GetProcAddress(HDIP,"?ProcessDipRelations@@YAXXZ");
	InitDipForThisMap=(fnVoid*)GetProcAddress(HDIP,"?InitDipForThisMap@@YAXXZ");
	LoadAllDipData=(tpLoadAllDipData*)GetProcAddress(HDIP,"?LoadAllDipData@@YAXPAEH@Z");
	ClearAllDipData=(fnVoid*)GetProcAddress(HDIP,"?ClearAllDipData@@YAXXZ");
	FreeSaveDipData=(fnVoidLPB*)GetProcAddress(HDIP,"?FreeSaveDipData@@YAXPAE@Z");
	SaveAllDipData=(tpSaveAllDipData*)GetProcAddress(HDIP,"?SaveAllDipData@@YAXPAPAEPAH@Z");
	PerformDipCommand=(tpPerformDipCommand*)GetProcAddress(HDIP,"?PerformDipCommand@@YAXPADH@Z");
};
