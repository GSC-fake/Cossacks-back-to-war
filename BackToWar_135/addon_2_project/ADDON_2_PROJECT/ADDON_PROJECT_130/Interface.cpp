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
extern bool RUNMAPEDITOR;
extern bool RUNUSERMISSION;
extern char USERMISSPATH[128];
bool UseGSC_Login=0;
CEXPORT bool CheckGSC_Login(){
	return UseGSC_Login;
};
RoomInfo GlobalRIF;
int GetGSC_Profile(){
	return GlobalRIF.Profile;
};
//#define FRANCEVERSION
byte RedColor2=0xBB;
extern int CurrentAnswer;
bool CommEnterName();
//#define SINGLETESTNETWORK
bool NotifyFirewallState();
//#define TESTVERSION
void UnPress();
//#define TUTORIAL_DEMOVERSION
int CurrentNation=-1;
extern int PitchTicks;
extern int MaxPingTime;
void StartPing(DWORD DPID,int ID);
void EndPing(int ID);
bool CheckLogin();
char* GetLString(DWORD DPID);
#define MinPing0 50
void ShowLoading();
int CurProtocol=0;
extern char CHATSTRING[256];
extern DWORD CHATDPID;
void SendChat(char* str,bool);
extern int ModeLX[32];
extern int ModeLY[32];
extern int NModes;
extern int RM_LandType;
extern int RM_Resstart;
extern int RM_Restot;
void CenterScreen();
bool Camp_EnterName();
bool ProcessSingleCampagin(int n);
void CreateNationalMaskForMap(char* Name);
extern bool realLpressed;
void CreateMiniMap();
SFLB_DLLEXPORT SFLB_CreateGamesList(ListBox* LB);
char* GetTextByID(char* ID);
void CreateRandomMap(char* Name);
void RandomMapDialog(char* Result);
void RandomMapDialog1(char* Result,int N,char* Nats);
bool IgnoreSlow=false;
void PrepareGameMedia(byte myid,bool);
extern int exRealLx;
extern int exRealLy;
bool CHKV(char* Name);
bool WaitingHostGame(int);
void NewMap(int szX,int szY);
bool WaitingJoinGame(int);
void SlowLoadPalette(LPCSTR lpFileName);
void SlowUnLoadPalette(LPCSTR lpFileName);
void SetDarkPalette();
void CopyToScreen(int x,int y,int Lx,int Ly);
void ChooseInterior(int Type);
void Save3DMap(char* Map);
void Load3DMap(char* Map);
void EditMiniMap();
extern short WheelDelta;
SFLB_DLLEXPORT LoadMEDButtons();
int time1,time2,time3,time4,time5;
extern int time8;
SFLB_DLLEXPORT processMLoadGame();
extern char GameName[128];
bool ContinueGame;
extern word rpos;
char CurrentMap[64];
void CBar(int x,int y,int Lx,int Ly,byte c);
void PrepareEditMedia(byte myid);
extern bool EditMapMode;
extern int RES[8][8];
extern byte mapPos[16];
void PreLoadExtendedMap(char* s);
void PostLoadExtendedMap(char* s);
void InitGame();
int nsmaplx;
int nsmaply;
int GameMode;
extern int LastKey;
extern bool KeyPressed;
void MFix();
//SQPicture MainMenuGround;
int WarSound;
int WorkSound;
int OrderSound;
int MidiSound;
/*
SQPicture w164x28d;
SQPicture r164x28e;
SQPicture r164x28p;
SQPicture w224x28d;
SQPicture r224x28e;

SQPicture sb_up_e;
SQPicture sb_up_p;
SQPicture sb_up_d;

SQPicture sb_dn_e;
SQPicture sb_dn_p;
SQPicture sb_dn_d;

SQPicture sb_lf_e;
SQPicture sb_lf_p;
SQPicture sb_lf_d;

SQPicture sb_ri_e;
SQPicture sb_ri_p;
SQPicture sb_ri_d;

SQPicture sb_vbar;
SQPicture sb_vbare;
SQPicture sb_hbar;
SQPicture sb_hbare;

SQPicture sb_btn;

SQPicture chk1_on;
SQPicture chk1_off;
SQPicture chk2_on;
SQPicture chk2_off;
*/
//SQPicture w160x160;
//SQPicture w160x256;
//SQPicture y288x256;
//SQPicture y288x128;
//SQPicture w288x256;
//SQPicture w288x128;

SQPicture LoPanel;
RLCTable TPassive;
RLCTable TActive;
RLCTable TDisable;
RLCFont FPassive;
RLCFont FActive;
RLCFont FDisable;
extern bool CheapMode;
int PanelLx;
int PanelLy;
bool MultiplayerStart;
bool GameNeedToDraw;
extern bool ChoosePosition;
extern word NPlayers;
void CloseMPL();
void IBEnumeratePlayers(InputBox** IB);
void LBEnumerateSessions(ListBox* LB,int);
void AnalyseMessages();
bool CreateNamedSession(char* Name,DWORD User2,int Max);
bool InGame;
bool JoinNameToSession(int ns,char* Name);
void FreeDDObjects( void );
bool StartIGame(bool);
extern bool GameInProgress;
byte MyRace;
extern LPDIRECTPLAY3A		lpDirectPlay3A;
extern word PlayerMenuMode;
extern LPVOID lplpConnectionBuffer[16];
extern bool SHOWSLIDE;
void PlayVideo();
void ProcessNetCash();
void ProcessReceive();
int NPROCM=0;
int TPROCM=0;
int LastCTRLPressTime=0;
void ProcessLogin();
int PrevProgStage=0;
char* PROGSTR=NULL;
extern int CurPalette;
extern int RealLx;
extern int RealLy;
void ShowCharUNICODE(int x,int y,byte* strptr,lpRLCFont lpr);
void ShowProgStr(char* ss,int prog){
	if(CurPalette){
		LocalGP LOAD("Interface\\_Loading");
		GPS.ShowGP((RealLx-GPS.GetGPWidth(LOAD.GPID,0))/2,(RealLy-GPS.GetGPHeight(LOAD.GPID,0))/2,LOAD.GPID,0,0);
	}else{
		DrawStdBar((RealLx-330)/2+20,(RealLy-70)/2+18,(RealLx-330)/2+318,(RealLy-70)/2+55);
	};
	int L=strlen(ss);
	L=(L*prog)/100;
	int x0=(RealLx-GetRLCStrWidth(ss,&YellowFont))/2+1+5;
	int y0=(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2+1;
	int spos=0;
	do{
		if(spos<=L)ShowCharUNICODE(x0,y0,(byte*)(ss+spos),&WhiteFont);
		else ShowCharUNICODE(x0,y0,(byte*)(ss+spos),&YellowFont);
		int LL;
		x0+=GetRLCWidthUNICODE(YellowFont.RLC,(byte*)(ss+spos),&LL);
		spos+=LL;
	}while(ss[spos]);
	CopyToScreen(0,0,RealLx,RSCRSizeY);
};
void ProcessNewInternet();
int PrevT=0;
int COUNTER1=0;
int LastBActiveTime=0;
void IAmLeft();
extern byte SpecCmd;
void ShowOptMessage(char* ID,int v){
	char* str=GetTextByID(ID);
	if(str[0]!='#'){
		char HHH[512];
		sprintf(HHH,str,v);
		AssignHint1(HHH,200,32);
	};
};
byte INSIDE3=0;
bool NeedToPerformGSC_Report=0;
bool NeedToReportInGameStats=0;
int PrevReportTime=0;
int LastTimeReport_tmtmt=0;
extern int tmtmt;
extern City CITY[8];
void EndGSC_Reporting(){
	NeedToReportInGameStats=0;
	NeedToPerformGSC_Report=0;
	LeaveGSCRoom();
};
void ProcessExplorer(int Index);
bool PDIF_Inside=0;
extern int TIME1;
int PrevProcTime=0;
extern City CITY[8];
extern DWORD MyDPID;
//--------------------inserted from DIPLOMACY.H---------------//
typedef void tpStartDownloadInternetFile(char* Name,char* Server,char* DestName);
typedef void tpProcessDownloadInternetFiles();
typedef void tpSendRecBuffer(byte* Data,int size,bool Final);

extern tpStartDownloadInternetFile* StartDownloadInternetFile;
extern tpProcessDownloadInternetFiles* ProcessDownloadInternetFiles;
extern tpSendRecBuffer* SendRecBuffer;
//-----------------------------------------------------------//
CEXPORT
bool ProcessMessages(){
	if(PDIF_Inside)return false;
	int TT=GetTickCount();
	if(!PrevProcTime)PrevProcTime=TT;
	if(TT-PrevProcTime>3000){
		PDIF_Inside=1;
		if(ProcessDownloadInternetFiles)ProcessDownloadInternetFiles();
		ProcessExplorer(16);
		PDIF_Inside=0;
		PrevProcTime=TT;
	};
	if(NeedToPerformGSC_Report){
		int T=GetTickCount();
		if(!PrevReportTime)PrevReportTime=T;
		if(T-PrevReportTime>120000){
			int NZeros=0;
			int PROFS[8];
			for(int i=0;i<NPlayers;i++){
				if(!PINFO[i].ProfileID)NZeros++;
				PROFS[i]=PINFO[i].ProfileID;
			};
			if(!NZeros){
				ReportAliveState(NPlayers,PROFS);
				PrevReportTime=T;
			};
		};
	};
	if(NeedToReportInGameStats&&UseGSC_Login){
		if(tmtmt-LastTimeReport_tmtmt>=256){
			int NMN[8]={0,0,0,0,0,0,0};
			for(int i=0;i<MAXOBJECT;i++){
				OneObject* OB=Group[i];
				if(OB&&(OB->Hidden||!OB->Sdoxlo)&&(!OB->NewBuilding)){
					NMN[OB->NNUM]++;
				};
			};
			OnePlayerReport OPR[8];
			for(i=0;i<NPlayers;i++)if(PINFO[i].PlayerID==MyDPID){
				int NI=PINFO[i].ColorID;
				int NP=0;
				int NW=0;
				int NN=NATIONS[NI].NMon;
				for(int j=0;j<NN;j++){
					NewMonster* NM=NATIONS[NI].Mon[j]->newMons;
					if(NM->Peasant)NP+=NATIONS[NI].NProduced[j];
					else if(!NM->Building)NW+=NATIONS[NI].NProduced[j];
				};
				
				OPR[0].NBornP=NP;
				OPR[0].NBornUnits=NW;
				OPR[0].Population=NMN[PINFO[i].ColorID];
				OPR[0].Profile=PINFO[i].ProfileID;
				for(int p=0;p<6;p++)OPR[i].ReachRes[p]=NATIONS[NI].ResTotal[p];
				OPR[0].Score=CITY[NI].Account/100;
				OPR[0].State=NATIONS[NI].VictState;
				for(int q=0;q<6;q++)OPR[0].ReachRes[q]=NATIONS[NI].ResTotal[q];
			};
			ReportGSCGame(tmtmt,NPlayers,OPR);
			LastTimeReport_tmtmt=tmtmt;
		};
	};
	try{
		INSIDE3=1;
		int T1=GetTickCount();
		if((!PrevT)||T1-PrevT>10){
			try{
				int TT0=T1;
				INSIDE3=4;
				ProcessNewInternet();
				INSIDE3=5;
			}
			catch(...){};
			int TT0=GetTickCount()-T1;
			if(TT0>COUNTER)COUNTER=TT0;
			try{
				INSIDE3=6;
				ProcessLogin();
				INSIDE3=7;
			}catch(...){};
			try{
				TPEN.Process();
				INSIDE3=8;
			}catch(...){};
			//NPROCM++;
			//int T0=GetTickCount();
			if(GetKeyState(VK_CONTROL)&0x8000){
				LastCTRLPressTime=GetTickCount();
			};
			INSIDE3=9;
			TT0=GetTickCount();
			try{
				ProcessReceive();
			}catch(...){};
			INSIDE3=10;
			TT0=GetTickCount()-TT0;
			if(TT0>COUNTER1)COUNTER1=TT0;
			try{
				ProcessNetCash();
			}catch(...){};
			INSIDE3=11;
			PrevT=T1;
			if(bActive){
				LastBActiveTime=T1;
			}else{
				if(GameInProgress&&NPlayers>1&&T1-LastBActiveTime>10000){
					if(NATIONS[MyNation].VictState!=2){
						IAmLeft();
						SpecCmd=199;
						ShowOptMessage("#ALTTABDEFEAT",0);
					};
				};
			};
			INSIDE3=12;
		};
		MSG         msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT)
			{	
				//FreeDDObjects();
				//PostQuitMessage(msg.wParam);
				//TPROCM+=GetTickCount()-T0;
				INSIDE3=3;
				return true;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//TPROCM+=GetTickCount()-T0;
		INSIDE3=13;
		if(GPROG.NWeights){
			if((!PrevProgStage)||GetTickCount()-PrevProgStage>300){
				PrevProgStage=GetTickCount();
				if(!PROGSTR)PROGSTR=GetTextByID("PROGSTR%s");
				char ccx[128];
				char tmp[32];
				DWORD CID=GPROG.StageID[GPROG.CurStage];
				tmp[0]=CID>>24;
				tmp[1]=(CID>>16)&255;
				tmp[2]=(CID>>8)&255;
				tmp[3]=(CID)&255;
				tmp[4]=' ';
				tmp[5]=0;
				int cpr=GPROG.GetCurProgress();
				sprintf(tmp+5,"%d%%",cpr);
				sprintf(ccx,PROGSTR,tmp);
				ShowProgStr(ccx,/*PROGSTR,*/cpr);
			};
		};
		INSIDE3=2;
	}catch(...){};
	return false;
};
extern bool EnterChatMode;
void ProcessChatKeys();
void ProcessVotingKeys();
bool ProcessMessagesEx(){
	if(GetKeyState(VK_CONTROL)&0x8000){
		LastCTRLPressTime=GetTickCount();
	};
	ProcessVotingKeys();
	if(EnterChatMode){
		ProcessChatKeys();
	};
	MSG         msg;
	//ProcessNetCash();
	bool MSR=0;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		if (msg.message == WM_QUIT)
		{
			//FreeDDObjects();
			//PostQuitMessage(msg.wParam);
			return true;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		MSR=1;
	}
	return MSR;
};
void normstr(char* str);
char PlName[64];
void ProcessHelp();
void ProcessCampagins(int Options);
SFLB_DLLEXPORT SFLB_ReadFirstPlayerName(char* ccc);
#ifdef MAKE_PTC
SFLB_DLLEXPORT SFLB_LoadMEDButtons();
SFLB_DLLEXPORT SFLB_InitDialogs(){
	DLL1(SFLB_ReadFirstPlayerName,PlName);
	unsigned long dws=20;
	if(!PlName[0]){
		GetComputerName(PlName,&dws);
		normstr(PlName);
	};
    FPassive=YellowFont;
    FActive=WhiteFont;
    FDisable=YellowFont;
	/*LoadRLC("fpassive.rlc",&TPassive);
	LoadRLC("factive.rlc",&TActive);
	LoadRLC("fdisable.rlc",&TDisable);
	RegisterRLCFont(&FPassive,TPassive,0);
	RegisterRLCFont(&FActive,TActive,0);
	RegisterRLCFont(&FDisable,TDisable,0);*/
	//MainMenuGround.LoadPicture("014.bpx");
	/*
	w164x28d.LoadPicture("w164x28d.bpx");
	r164x28e.LoadPicture("r164x28e.bpx");
	r164x28p.LoadPicture("r164x28p.bpx");
	w224x28d.LoadPicture("w224x28d.bpx");
	r224x28e.LoadPicture("r224x28e.bpx");
	

	sb_up_e.LoadPicture("sb_up_e.bpx");
	sb_up_p.LoadPicture("sb_up_p.bpx");
	sb_up_d.LoadPicture("sb_up_d.bpx");

	sb_dn_e.LoadPicture("sb_dn_e.bpx");
	sb_dn_p.LoadPicture("sb_dn_p.bpx");
	sb_dn_d.LoadPicture("sb_dn_d.bpx");

	sb_lf_e.LoadPicture("sb_lf_e.bpx");
	sb_lf_p.LoadPicture("sb_lf_p.bpx");
	sb_lf_d.LoadPicture("sb_lf_d.bpx");

	sb_ri_e.LoadPicture("sb_ri_e.bpx");
	sb_ri_p.LoadPicture("sb_ri_p.bpx");
	sb_ri_d.LoadPicture("sb_ri_d.bpx");

	sb_vbar.LoadPicture("sb_vbar.bpx");
	sb_vbare.LoadPicture("sb_vbare.bpx");
	sb_hbar.LoadPicture("sb_hbar.bpx");
	sb_hbare.LoadPicture("sb_hbare.bpx");

	sb_btn.LoadPicture("sb_btn.bpx");

	chk1_on.LoadPicture("chk1_on.bpx");
	chk1_off.LoadPicture("chk1_off.bpx");
	chk2_on.LoadPicture("chk2_on.bpx");
	chk2_off.LoadPicture("chk2_off.bpx");
	*/

	//w160x160.LoadPicture("w160x160.bpx");
	//w160x256.LoadPicture("w160x256.bpx");

	//y288x256.LoadPicture("y288x256.bpx");
	//y288x128.LoadPicture("y288x128.bpx");
	//w288x256.LoadPicture("w288x256.bpx");
	//w288x128.LoadPicture("w288x128.bpx");
	DLL0(SFLB_LoadMEDButtons);
};
#endif
CEXPORT
int ItemChoose;
CEXPORT
bool MMItemChoose(SimpleDialog* SD){
	ItemChoose=SD->UserParam;
	Lpressed=false;
	return true;
};
bool CHANGESORT(SimpleDialog* SD){
	if(TPEN.SORTTYPE==SD->UserParam)TPEN.SORTTYPE=-TPEN.SORTTYPE;
	else TPEN.SORTTYPE=SD->UserParam;
	Lpressed=0;
	return true;
};
CEXPORT
void StdKeys(){
	if(KeyPressed&&(LastKey==27||LastKey==13)){
		if(LastKey==13)ItemChoose=mcmOk;
		if(LastKey==27)ItemChoose=mcmCancel;
		KeyPressed=0;
		LastKey=0;
	};
};
extern bool LB_SORT_ITEM;
void InstallMap(ListBox* LB,char* Name){
	LB_SORT_ITEM=1;
	LB->AddItem(Name,0);
	LB_SORT_ITEM=0;
};
void CreateMapsList(ListBox* LB){
	TGSCFindInfo* FD=GSFILES.gFindFirst("*.m3d");
	if(FD){
		InstallMap(LB,FD->m_FileName);
		while(GSFILES.gFindNext(FD))InstallMap(LB,FD->m_FileName);
	};
};
void InstallNewMap(ListBox* LB,WIN32_FIND_DATA* FD){
	LB->AddItem(FD->cFileName,0);
};
void CreateNewMapsList(ListBox* LB){
	TGSCFindInfo* FD=GSFILES.gFindFirst("*.m3d");
	if(FD){
		InstallMap(LB,FD->m_FileName);
		while(GSFILES.gFindNext(FD))InstallMap(LB,FD->m_FileName);
	};
};
//----------------Graphics menu----------------//
bool InitScreen();
int OldSizeX;
int OldSizeY;
int mul3(int);
extern LPDIRECTDRAW            lpDD;
int GetRealTime();
bool CheckMode(){
	return true;
	SQPicture Pan("pan17.bpx");
	RLCFont gf24w(GETS("@SMFONT1"));
	RLCFont gf24y(GETS("@SMFONT0"));
	int mmlx=Pan.GetLx();
	int mmly=Pan.GetLy();
	ContinueGame=false;
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&Pan,&Pan,&Pan);
	//TextButton* Mess=GMM.addTextButton(PIC1,288>>1,30,"Íîðìàëüíî ?",&FActive,&FPassive,&FDisable,1);
	TextButton* OkBtn=GMM.addTextButton(PIC1,GETV("VMQOKX"),GETV("VMQOKY"),GETS("@VMQOKSTR"),&gf24w,&gf24y,&gf24y,1);
	TextButton* CancelBtn=GMM.addTextButton(PIC1,GETV("VMQNOX"),GETV("VMQNOY"),GETS("@VMQNOSTR"),&gf24w,&gf24y,&gf24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	int time=GetRealTime();
	ItemChoose=-1;
	do{
		ProcessMessages();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1&&GetRealTime()-time<8000);
	if(ItemChoose==mcmOk)return true;
	else return false;

};
void GSSetup800();
void DrawAllScreen();
extern int COPYSizeX;
extern int RealLx;
extern int RealLy;
void SERROR(){
	PlayEffect(0,0,0);
	int time=GetRealTime();
	do{}while(GetRealTime()-time<1000);
};
void SERROR1(){
	PlayEffect(1,0,0);
	int time=GetRealTime();
	do{}while(GetRealTime()-time<1000);
};
void SERROR2(){
	PlayEffect(2,0,0);
	int time=GetRealTime();
	do{}while(GetRealTime()-time<1000);
};
extern int SCRSZY;
void ClearScreen(){
	if(RealScreenPtr)memset(RealScreenPtr,0,RSCRSizeX*SCRSZY);
};
extern byte fog[8192+1024];
#ifdef MAKE_PTC
CEXPORT
void DarkScreen(){
	byte* sptr=(byte*)ScreenPtr;
	int sz=ScrWidth*RealLy;
	for(int i=0;i<sz;i++)sptr[i]=fog[4096+1024+sptr[i]];
	int ofs=0;
	int ry=RealLy>>1;
	for(int iy=0;iy<ry;iy++){
		ofs=ScrWidth*iy*2;
		for(int ix=0;ix<RealLx;ix+=2){
			sptr[ofs]=0;
			ofs+=2;
		};
		ofs=ScrWidth*(iy*2+1)+1;
		for(ix=0;ix<RealLx;ix+=2){
			sptr[ofs]=0;
			ofs+=2;
		};
	};
};
#endif
extern int CurPalette;
#ifdef MAKE_PTC
void ShowLoading(){
	DarkScreen();
	if(CurPalette){
		LocalGP LOAD("Interface\\_Loading");
		GPS.ShowGP((RealLx-GPS.GetGPWidth(LOAD.GPID,0))/2,(RealLy-GPS.GetGPHeight(LOAD.GPID,0))/2,LOAD.GPID,0,0);
	}else{
		DrawStdBar((RealLx-330)/2+20,(RealLy-70)/2+18,(RealLx-330)/2+318,(RealLy-70)/2+55);
	};
	char* ss=GetTextByID("LOADING");
	ShowString((RealLx-GetRLCStrWidth(ss,&YellowFont))/2+1+5,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2+1,ss,&BlackFont);
	ShowString((RealLx-GetRLCStrWidth(ss,&YellowFont))/2+5,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2,ss,&YellowFont);
	CopyToScreen(0,0,RealLx,RSCRSizeY);
};
#endif
void SetGameDisplayModeAnyway(int SizeX,int SizeY){
	ClearScreen();
	RealLx=SizeX;
	RealLy=SizeY;
	//FreeDDObjects();
	InitScreen();
	GSSetup800();
	SetCursorPos(512,300);
	SetMPtr(512,300,0);
	//DrawAllScreen();
};
bool SetGameDisplayMode(int SizeX,int SizeY){
	ClearScreen();
	RealLx=SizeX;
	RealLy=SizeY;
	exRealLx=RealLx;
	exRealLy=RealLy;
	//FreeDDObjects();
	InitScreen();
	GSSetup800();
	DrawAllScreen();
	SetCursorPos(512,300);
	SetMPtr(512,300,0);
	if(CheckMode())return true;
	else{
		RealLx=OldSizeX;
		RealLy=OldSizeY;
		//FreeDDObjects();
		InitScreen();
		GSSetup800();
		DrawAllScreen();
		return false;
	};
	return false;
};
extern int ScrollSpeed;
int FPSTime;

//-----------------Speed menu------------------//
void ProcessSpeed(int x,int y){
	
};
//----------------SOUND----------------

void ProcessSound(int x,int y){
	
};
//-----------------Options menu----------------//
void ProcessOptions(int x,int y){
	
};
//-----------------SINGLE PLAYER---------------//
void UnLoading();
static byte Ntn[8];
bool NatChoose(SimpleDialog* SD){
	BpxTextButton* TB=(BpxTextButton*)SD;
	char* qq=TB->Message;
	if(qq[0]=='Î')strcpy(TB->Message,"ËÞÄÈ");
	else strcpy(TB->Message,"ÎÐÊÈ");
	SD->NeedToDraw=true;
	Lpressed=true;
	return true;
};	
int coorX[8];
int coorY[8];
void setCoor(){
	for(int i=0;i<8;i++){
		coorX[i]=-1;
		coorY[i]=-1;
	};
};
void LoadAIFromDLL(byte Nat,char* Name);
void LoadNation(char* fn,byte msk,byte NIndex,byte);
extern City CITY[8];
void ProcessMissions(){
	
};
void OldprocessSinglePlayer(){
	
};
//-----------------WAITING FOR OPPONENTS(HOST)-------------------//
bool processHostConnection(){
	return 0;
};
//-----------------WAITING FOR OPPONENTS(JOIN)-------------------//
bool processJoinConnection(){
	return 0;
};
//--------------------JOIN  TO SESSION---------------------//
bool processJoinGame(){
	return false;
};
extern char ROOMNAMETOCONNECT[128];
bool JOINTOINETGAME(char* SNAME){

	return false;
};
bool ProcessOneBattle(int BtlID);
bool MPL_JoinGame(int ID){
	LocalGP BTNS("Interface\\Game_Select");
	LocalGP FONT1("romw");
	LocalGP FONT2("romw1");
	RLCFont FontA(FONT2.GPID);
	RLCFont FontP(FONT1.GPID);
	LoadFog(2);
	SQPicture Back("Interface\\Game_Select_Background.bmp");
	DialogsSystem MENU(0,0);
	MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,0))>>1)-85;
	//int dy=(RealLy-GPS.GetGPHeight(BTNS.GPID,0))>>1;
	//MENU.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	GP_Button* Join=MENU.addGP_Button(NULL,93,594,BTNS.GPID,0,1);
	Join->OnUserClick=&MMItemChoose;
	Join->UserParam=mcmJoin;
	GP_Button* Refresh=MENU.addGP_Button(NULL,238,594,BTNS.GPID,2,3);
	Refresh->OnUserClick=&MMItemChoose;
	Refresh->UserParam=mcmRefresh;
	GP_Button* Cancel=MENU.addGP_Button(NULL,384,594,BTNS.GPID,4,5);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;
	ListBox* LB=MENU.addGP_ListBox(NULL,92,172,15,BTNS.GPID,6,26,&WhiteFont,&YellowFont,NULL);
	LBEnumerateSessions(LB,ID);
	LB->CurItem=-1;
	LB->M_Over=9;
	if(LB->NItems)LB->CurItem=0;
StartJoin:;
	int pp=1;
	do{
		ItemChoose=-1;
		do{
			ProcessMessages();
			//OkBtn->NeedToDraw=true;
			if(LB->CurItem==-1)Join->Enabled=false;
			else Join->Enabled=true;
			MENU.MarkToDraw();
			MENU.ProcessDialogs();
			for(int i=0;i<LB->NItems;i++){
				char nps[16];
				int ppr=(LB->GetItem(i)->Param1)&65535;
				sprintf(nps,"%d/%d",ppr&255,ppr>>8);
				if(LB->CurItem==i)ShowString(LB->x+364,LB->y+6+i*26,nps,&WhiteFont);
				else ShowString(LB->x+364,LB->y+6+i*26,nps,&YellowFont);
			};
			MENU.RefreshView();
			if(ItemChoose==mcmRefresh){
				LBEnumerateSessions(LB,ID);
				ItemChoose=-1;
				if(!LB->NItems)LB->CurItem=-1;
			};
			if(pp){
				SlowLoadPalette("2\\agew_1.pal");
				pp=0;
			};
		}while(ItemChoose==-1);
		if(ItemChoose==mcmJoin&&LB->CurItem!=-1){
			int BID=LB->GetItem(LB->CurItem)->Param1>>16;
			if(BID){
				SlowUnLoadPalette("2\\agew_1.pal");
				if(!ProcessOneBattle(BID-1)){
					SlowUnLoadPalette("2\\agew_1.pal");
					goto StartJoin;
				};
			};
			if(JoinNameToSession(LB->CurItem,PlName)){
				if(WaitingJoinGame(LB->GetItem(LB->CurItem)->Param1>>16)){
					return true;
				}else ItemChoose=mcmCancel;
			};
		};
	}while(ItemChoose!=mcmCancel);
	SlowUnLoadPalette("2\\agew_1.pal");
	return false;
};
//--------------------HOST THE SESSION---------------------//
bool processHostGame(){
	return false;
};
bool MPL_EnterName();
extern char IPADDR[128];
int MPL_ChooseConnection();
void WaitWithMessage(char* Message);
void NoWaitWithMessage(char* Message);
#ifdef MAKE_PTC
int ProcessInternetConnection(bool Active);
bool FindSessionAndJoin(char* Name,char* Nick,bool Style);
bool CreateSession(char* SessName,char* Name,DWORD User2,bool Style,int MaxPlayers);
extern int GMTYPE;
int IEMMOD=0;
bool DoNewInet=0;
bool InternetGameLogin();
extern int GMMAXPL;
extern bool TOTALEXIT;
bool ProcessNewInternetLogin();
extern char** NatsIDS;
bool processMultiplayer(){
	byte AddrBuf[128];
	memset(AddrBuf,0,128);
	int crs=0;
RetryConn:;
	if(IEMMOD)goto REC3;//REINCONN;
	crs=MPL_ChooseConnection();
	if(TOTALEXIT)return 0;
	if(crs==mcmCancel)return 0;
	
	if(CurProtocol==3){
REC3:
		if(!InternetGameLogin())return false;
REINCONN:;
		int r=ProcessInternetConnection(1);
		if(!r)return 0;
		if(r==2)crs=10;//Join
		if(r==1)crs=11;//Host DM
		if(r==3)crs=13;//Host BT
	}else{
		if(!CommEnterName())return 0;
	};
	DoNewInet=0;
	if(CurProtocol>2)DoNewInet=1;
	if(!DoNewInet){
		if(!lpDirectPlay3A){
			CreateMultiplaterInterface();
			if(!lpDirectPlay3A)return 0;
		};
		LPDIRECTPLAYLOBBYA	lpDPlayLobbyA = NULL;
		LPDIRECTPLAYLOBBY2A	lpDPlayLobby2A = NULL;
		if FAILED(DirectPlayLobbyCreate(NULL, &lpDPlayLobbyA, NULL, NULL, 0)) return 0;
			// get ANSI DirectPlayLobby2 interface
		HRESULT hr = lpDPlayLobbyA->QueryInterface(IID_IDirectPlayLobby2A, (LPVOID *) &lpDPlayLobby2A);
		if FAILED(hr)return 0;
				// don't need DirectPlayLobby interface anymore
		lpDPlayLobbyA->Release();
		lpDPlayLobbyA = NULL;
		DPCOMPOUNDADDRESSELEMENT	addressElements[3];
			DWORD sz=128;
		char* cc="";
		switch(CurProtocol){
		case 0://IPX
			addressElements[0].guidDataType = DPAID_ServiceProvider;
			addressElements[0].dwDataSize = sizeof(GUID);
			addressElements[0].lpData = (LPVOID) &DPSPGUID_IPX;
			lpDPlayLobby2A->CreateCompoundAddress(addressElements,1,AddrBuf,&sz);
			/*
			memcpy(AddrBuf,&DPAID_TotalSize,16);
			AddrBuf[16]=56;
			memcpy(AddrBuf+20,&DPAID_ServiceProvider,16);
			AddrBuf[36]=16;
			memcpy(AddrBuf+40,&DPSPGUID_IPX,16);
			*/
			break;
		case 1://TCP/IP
			IPADDR[0]=0;
		case 3:
		case 2:
			addressElements[0].guidDataType = DPAID_ServiceProvider;
			addressElements[0].dwDataSize = sizeof(GUID);
			addressElements[0].lpData = (LPVOID) &DPSPGUID_TCPIP;
			addressElements[1].guidDataType = DPAID_INet;
			addressElements[1].dwDataSize = strlen(IPADDR)+1;
			addressElements[1].lpData = (LPVOID) IPADDR;
			lpDPlayLobby2A->CreateCompoundAddress(addressElements,2,AddrBuf,&sz);
			/*
			memcpy(AddrBuf,&DPAID_ServiceProvider,16);
			AddrBuf[16]=16;
			memcpy(AddrBuf+20,&DPSPGUID_TCPIP,16);
			memcpy(AddrBuf+36,&DPAID_INet,16);
			AddrBuf[40]=1;
			AddrBuf[41]=0;
			*/
			break;
		};
		lpDPlayLobby2A->Release();
		CloseMPL();
		CreateMultiplaterInterface();
		HRESULT HR=lpDirectPlay3A->InitializeConnection(AddrBuf,0);
		if(FAILED(HR))goto RetryConn;
	}else{
		CloseMPL();
		CreateMultiplaterInterface();
	};
	switch(crs){
	case mcmHost:
		if(CreateNamedSession(PlName,0,GMMAXPL))WaitingHostGame(0);
		break;
	case mcmJoin:
		MPL_JoinGame(0);
		break;
	case 11://Inet Host(Deathmatch)
		PlayerMenuMode=1;
		if(UseGSC_Login){
			if(CreateSession(GlobalRIF.Name,GlobalRIF.Nick,0,DoNewInet,GlobalRIF.MaxPlayers)){
				NeedToPerformGSC_Report=1;
				WaitingHostGame(0);
				NeedToPerformGSC_Report=0;
				if(PlayerMenuMode==1){
					//need to leave the room there
					LeaveGSCRoom();
					goto REINCONN;
				}else{
					char* PLAYERS[8];
					int Profiles[8];
					char NAT[8][32];
					char* Nations[8];
					int Teams[8];
					int Colors[8];
					for(int i=0;i<NPlayers;i++){
						PLAYERS[i]=PINFO[i].name;
						sprintf(NAT[i],"%d",PINFO[i].NationID);
						Nations[i]=NAT[i];
						Profiles[i]=PINFO[i].ProfileID;
						Teams[i]=PINFO[i].GroupID;
						Colors[i]=PINFO[i].ColorID;
					};
					StartGSCGame("",PINFO[0].MapName,NPlayers,Profiles,Nations,Teams,Colors);
					NeedToReportInGameStats=1;
					LastTimeReport_tmtmt=0;
				};
			}else{ 
				LeaveGSCRoom();
				goto REINCONN;
			};
		}else{
			if(TPEN.MyRoom&&CreateSession(TPEN.MyRoom->Name,PlName,0,DoNewInet,GMMAXPL)){
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				if(TPEN.MyRoom)WaitingHostGame(0);
				else{
					WaitWithMessage(GetTextByID("ICUNCR"));
					CloseMPL();
				};

			}else{
				WaitWithMessage(GetTextByID("ICUNCR"));
				goto REINCONN;
			};
			if(PlayerMenuMode==1){
				NoWaitWithMessage(GetTextByID("ICDISG"));
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				if(TPEN.MyRoom)TPEN.LeaveMyRoom();
				goto REINCONN;
			}else{
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				//if(TPEN.Connected&&TPEN.MyRoom){
					//TPEN.MyRoom->RStart=1;
					//peerStateChanged(TPEN.Peer);
				//};
				if(TPEN.MyRoom&&TPEN.MyRoom->RoomConnected){
					//char GCHAT[512]="";
					//sprintf(GCHAT,"[~ADMI@START~]%s",TPEN.MyRoom->Name);
					//TPEN.CreateMyRoomInfoString(GCHAT);
					//if(TPEN.HostMessage[0])TPEN.SendGlobalChat(TPEN.HostMessage);
				};
				//TPEN.Disconnect();
				TPEN.StartGame(true);
			};
		};
		break;
	case 13:
		PlayerMenuMode=1;
		if(TPEN.MyRoom&&CreateSession(TPEN.MyRoom->Name,PlName,1,DoNewInet,2)){
			do{
				ProcessMessages();
			}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
			if(TPEN.MyRoom)WaitingHostGame(1);
			else{
				WaitWithMessage(GetTextByID("ICUNCR"));
				CloseMPL();
			};
		}else{
			WaitWithMessage(GetTextByID("ICUNCR"));
			do{
				ProcessMessages();
			}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
			if(TPEN.MyRoom)TPEN.LeaveMyRoom();
			goto REINCONN;
		};
		if(PlayerMenuMode==1){
			NoWaitWithMessage(GetTextByID("ICDISG"));
			do{
				ProcessMessages();
			}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
			if(TPEN.MyRoom)TPEN.LeaveMyRoom();
			goto REINCONN;
		}else{
			do{
				ProcessMessages();
			}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
			//TPEN.Disconnect();
			TPEN.StartGame(false);
			//if(TPEN.Connected&&TPEN.MyRoom){
				//TPEN.MyRoom->RStart=1;
				//peerStateChanged(TPEN.Peer);
			//};
		};
		break;
	case 10://Inet Join(Deathmatch)
		if(UseGSC_Login){
			PlayerMenuMode=1;
			strcpy(IPADDR,GlobalRIF.RoomIP);
			if(!FindSessionAndJoin(ROOMNAMETOCONNECT,GlobalRIF.Nick,DoNewInet)){
				LeaveGSCRoom();
				WaitWithMessage(GetTextByID("ICUNJ"));
			}else{
				WaitingJoinGame(GMTYPE);
			};
			if(PlayerMenuMode==1){
				LeaveGSCRoom();
				goto REINCONN;
			}else{
				char* PLAYERS[8];
				int Profiles[8];
				char NAT[8][32];
				char* Nations[8];
				int Teams[8];
				int Colors[8];
				for(int i=0;i<NPlayers;i++){
					PLAYERS[i]=PINFO[i].name;
					sprintf(NAT[i],"%d",PINFO[i].NationID);
					Nations[i]=NAT[i];
					Profiles[i]=PINFO[i].ProfileID;
					Teams[i]=PINFO[i].GroupID;
					Colors[i]=PINFO[i].ColorID;
				};
				StartGSCGame("",PINFO[0].MapName,NPlayers,Profiles,Nations,Teams,Colors);
				NeedToReportInGameStats=1;
				LastTimeReport_tmtmt=0;
			};
		}else{
			PlayerMenuMode=1;
			if(!FindSessionAndJoin(ROOMNAMETOCONNECT,TPEN.MyNick,DoNewInet)){
				WaitWithMessage(GetTextByID("ICUNJ"));
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				if(TPEN.MyRoom)TPEN.LeaveMyRoom();
				goto REINCONN;
			}else{
				/*
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				*/
				WaitingJoinGame(GMTYPE);
				/*
				if(TPEN.MyRoom)WaitingJoinGame(GMTYPE);
				else{
					WaitWithMessage(GetTextByID("ICUNJ"));
					CloseMPL();
				};
				*/
			};	
			if(PlayerMenuMode==1){
				NoWaitWithMessage(GetTextByID("ICDISG"));
				do{
					ProcessMessages();
				}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
				if(TPEN.MyRoom)TPEN.LeaveMyRoom();
				goto REINCONN;
			}else TPEN.StartGame(false);
				//TPEN.Disconnect();
		};
		break;
	};
	return 1;
};
#endif
bool ProcessOneBattle(int BtlID);
int ProcessWars();
void processBattleMultiplayer(){
TryConnection:;
	byte AddrBuf[128];
	memset(AddrBuf,0,128);
	int crs;
	crs=MPL_ChooseConnection();
	if(TOTALEXIT)return;
	if(crs==mcmCancel)return;
	if(CurProtocol==3){
		IEMMOD=1;
		processMultiplayer();
		if(TOTALEXIT)return;
		IEMMOD=0;
		return;
	};
	if(!CommEnterName())return;
	int BTLID=1;
	if(crs==mcmHost){
		BTLID=ProcessWars();
	};
	if(BTLID==-1)goto TryConnection;
	if(!lpDirectPlay3A){
		CreateMultiplaterInterface();
		if(!lpDirectPlay3A)return;

		LPDIRECTPLAYLOBBYA	lpDPlayLobbyA = NULL;
		LPDIRECTPLAYLOBBY2A	lpDPlayLobby2A = NULL;
		if FAILED(DirectPlayLobbyCreate(NULL, &lpDPlayLobbyA, NULL, NULL, 0)) return;
		// get ANSI DirectPlayLobby2 interface
		HRESULT hr = lpDPlayLobbyA->QueryInterface(IID_IDirectPlayLobby2A, (LPVOID *) &lpDPlayLobby2A);
		if FAILED(hr)return;

		// don't need DirectPlayLobby interface anymore
		lpDPlayLobbyA->Release();
		lpDPlayLobbyA = NULL;
		DPCOMPOUNDADDRESSELEMENT	addressElements[3];
		DWORD sz=128;
		char* cc="";
		switch(CurProtocol){
		case 0://IPX
			addressElements[0].guidDataType = DPAID_ServiceProvider;
			addressElements[0].dwDataSize = sizeof(GUID);
			addressElements[0].lpData = (LPVOID) &DPSPGUID_IPX;
			lpDPlayLobby2A->CreateCompoundAddress(addressElements,1,AddrBuf,&sz);
			break;
		case 1://TCP/IP
		case 2:
			addressElements[0].guidDataType = DPAID_ServiceProvider;
			addressElements[0].dwDataSize = sizeof(GUID);
			addressElements[0].lpData = (LPVOID) &DPSPGUID_TCPIP;
			addressElements[1].guidDataType = DPAID_INet;
			addressElements[1].dwDataSize = strlen(IPADDR)+1;
			addressElements[1].lpData = (LPVOID) IPADDR;
			lpDPlayLobby2A->CreateCompoundAddress(addressElements,2,AddrBuf,&sz);
			break;

		};
		lpDPlayLobby2A->Release();
		if FAILED(lpDirectPlay3A->InitializeConnection(AddrBuf
			/*lplpConnectionBuffer[CurProtocol]*/,0)) return;
	};
	switch(crs){
	case mcmHost:
		if(CreateNamedSession(PlName,BTLID+1,2))WaitingHostGame(BTLID+1);
		break;
	case mcmJoin:
		MPL_JoinGame(BTLID+1);
		break;
	};
};
//--------------------MULTIPLAYER GAME---------------------//
extern char SaveFileName[128];
void OldprocessMultiplayer(){
	
};
//---------------------Map options-------------------------//
//int MO_LandType=0;
//int MO_StartRes=0;
//int MO_ResOnMap=0;
char MapScenaryDLL[200]="";
void ProcessMapOptions(){
	LocalGP FONT("vinBig");
	RLCFont fntb(FONT.GPID);
	fntb.SetBlackColor();
	RLCFont fntr(FONT.GPID);
	fntr.SetRedColor();
	int x0=(RealLx-64*7)>>1;
	int y0=(RealLy-64*2)>>1;
	DialogsSystem GMM(x0,y0);
	char DLLSC[200];
	strcpy(DLLSC,MapScenaryDLL);
	GMM.addTextButton(NULL,32*7,-20,GetTextByID("SCDLL"),&BigYellowFont,&BigYellowFont,&BigYellowFont,1);
	TextButton* Ok=GMM.addTextButton(NULL,32*7-100,80,"Ok",&fntr,&fntb,&fntb,1);
	Ok->UserParam=mcmOk;
	Ok->OnUserClick=&MMItemChoose;
	TextButton* Cancel=GMM.addTextButton(NULL,32*7+100,80,"Cancel",&fntr,&fntb,&fntb,1);
	Cancel->UserParam=mcmCancel;
	Cancel->OnUserClick=&MMItemChoose;
	int ibx=21;
	int iby=44;
	int iblx=400;
	int ibly=20;
	InputBox* EB=GMM.addInputBox(NULL,ibx,iby,DLLSC,100,iblx,ibly,&BlackFont,&RedFont);
	EB->Active=1;
	ItemChoose=-1;
	do{
		DrawPaperPanel(x0,y0,x0+64*7,y0+64*2);
		Xbar(x0+ibx,y0+iby,iblx+10,ibly+4,0x3C);
		GMM.MarkToDraw();
		ProcessMessages();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		strcpy(MapScenaryDLL,DLLSC);
	};
};
char DEFPLNAMES[8][64];
//--------------------RESOURCE EDITOR----------------------//
void MemScreenPart(int x,int y,int lx,int ly,byte* Ptr);
extern int CBB_GPFILE;
int ProcessResEdit(){
	LocalGP BTNS("Interface\\AI_Res");
	DialogsSystem DSS((RealLx-532)>>1,(RealLy-540)>>1);
	byte* Back=(byte*)malloc(532*544);
	MemScreenPart((RealLx-532)>>1,(RealLy-540)>>1,532,540,Back);
	DSS.addBPXView(NULL,0,0,532,540,1,1,1,Back,NULL);
	DSS.addGPPicture(NULL,0,0,BTNS.GPID,0);
	DSS.addGPPicture(NULL,0,0,BTNS.GPID,1);
	ComboBox* PLAYER=DSS.addGP_ComboBoxDLX(NULL,100,52,139,CBB_GPFILE,0,9,9,&WhiteFont,&YellowFont,NULL);
	char* cc=GetTextByID(GetTextByID("$PLAYER%D"));
	for(int i=0;i<8;i++){
		char ccx[128];
		sprintf(ccx,cc,i+1);
		PLAYER->AddLine(ccx);
	};
	PLAYER->CurLine=MyNation;
	PLAYER->AddLine(GetTextByID("$PLAYERALL"));
	char ResST[22][16];
	char PLNAMES[9][64];
	for(i=0;i<8;i++)strcpy(PLNAMES[i],DEFPLNAMES[i]);
	PLNAMES[8][0]=0;
	byte RESRID[8];
	int RESLOC[8];
	int NRes=0;
	for(i=0;i<8;i++){
		if(RDS[i].Enabled){
			itoa(RES[MyNation][i],ResST[i],10);
			RESLOC[i]=RES[MyNation][NRes];
			RESRID[NRes]=i;
			NRes++;
		};
	};
	for(i=0;i<NRes;i++){
		DSS.addInputBox(NULL,112+3,93+26*i,ResST[i],12,130,24,&YellowFont,&WhiteFont);
	};
	InputBox* IBN=DSS.addInputBox(NULL,320+3,51+1,PLNAMES[MyNation],32,160,24,&YellowFont,&WhiteFont);
	char DLLPT[200];
	strcpy(DLLPT,MapScenaryDLL);
	DSS.addInputBox(NULL,161+3,264,DLLPT,190,320,24,&YellowFont,&WhiteFont);
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
	ComboBox* CBSTYLE=DSS.addGP_ComboBoxDLX(NULL,263,119,491-263,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	for(int p=0;p<RMP.NSTY;p++){
		CBSTYLE->AddLine(RMP.STY[p].Name);
	};
	CBSTYLE->CurLine=RM_LandType;
	ComboBox* CBRESST=DSS.addGP_ComboBoxDLX(NULL,263,171,491-263,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	for(p=0;p<RMP.NRES;p++){
		CBRESST->AddLine(RMP.RES[p].Name);
	};
	CBRESST->CurLine=RM_Resstart;
	ComboBox* CBRESTOT=DSS.addGP_ComboBoxDLX(NULL,263,223,491-263,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	for(p=0;p<RMP.NMINES;p++){
		CBRESTOT->AddLine(RMP.MINES[p].Name);
	};
	CBRESTOT->CurLine=RM_Restot;
	ItemChoose=-1;
	GP_Button* OkBtn=DSS.addGP_Button(NULL,79,319,BTNS.GPID,5,4);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	GP_Button* CancelBtn=DSS.addGP_Button(NULL,300,319,BTNS.GPID,3,2);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	int prevNat=MyNation;
	do{
		if(PLAYER->CurLine!=prevNat){
			prevNat=PLAYER->CurLine;
			if(prevNat<8){
				for(i=0;i<NRes;i++){
					RESLOC[RESRID[i]]=RES[prevNat][RESRID[i]];
					sprintf(ResST[i],"%d",RESLOC[RESRID[i]]);
				};
			};
			IBN->Str=PLNAMES[prevNat];
		};
		for(i=0;i<NRes;i++){
			RESLOC[RESRID[i]]=atoi(ResST[i]);
		};
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		if(PLAYER->CurLine==8){
			for(i=0;i<8;i++){
				RES[i][0]=RESLOC[0];
				RES[i][1]=RESLOC[3];
				RES[i][2]=RESLOC[2];
				RES[i][3]=RESLOC[1];
				RES[i][4]=RESLOC[4];
				RES[i][5]=RESLOC[5];
			};
		}else{
			RES[prevNat][0]=RESLOC[0];
			RES[prevNat][1]=RESLOC[3];
			RES[prevNat][2]=RESLOC[2];
			RES[prevNat][3]=RESLOC[1];
			RES[prevNat][4]=RESLOC[4];
			RES[prevNat][5]=RESLOC[5];
		};
		if(ItemChoose==mcmOk){
			RM_LandType=CBSTYLE->CurLine;
			RM_Resstart=CBRESST->CurLine;
			RM_Restot=CBRESTOT->CurLine;
		};
		strcpy(MapScenaryDLL,DLLPT);
	};
	free(Back);
	return ItemChoose;
};
//---------------------------------------------------------//
int TM_Angle0=0;
int TM_Angle1=89;
int TM_Tan0;
int TM_Tan1;
int TM_Height0=0;
int TM_Height1=1024;
bool TexMapMod=false;


//---------------------------------------------------------//
void ProcessFranceMission();
bool SingleOptions();
bool SelectSingleMission();
int MM_ProcessSinglePlayer(){
	UseGSC_Login=0;
	DLL0(SFLB_LoadPlayerData);//();
	LoadFog(2);
	//SlowUnLoadPalette("2\\agew_1.pal");
	LocalGP BTNS("Interface\\Single_Player");
	SQPicture MnPanel("Interface\\Background_Single_Player.bmp");
	DialogsSystem MMenu(0,0);
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	int Dy=27;
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	GP_Button* Compagin=MMenu.addGP_Button(NULL,76,140+35+Dy,BTNS.GPID,0,1);
	Compagin->UserParam=1;
	Compagin->OnUserClick=&MMItemChoose;
	Compagin->Hint=GetTextByID("SCOMPAGIN");
	Compagin->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#ifdef INETTESTVERSION
	Compagin->UserParam=-1;
#endif
	GP_Button* Mission=MMenu.addGP_Button(NULL,76,140+82+35+Dy,BTNS.GPID,2,3);
	Mission->UserParam=2;
	Mission->OnUserClick=&MMItemChoose;
	Mission->Hint=GetTextByID("SMISSION");
	Mission->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#ifdef INETTESTVERSION
	Mission->UserParam=-1;
#endif
	GP_Button* Random=MMenu.addGP_Button(NULL,76,140+35+82*2+Dy,BTNS.GPID,4,5);
	Random->UserParam=3;
	Random->OnUserClick=&MMItemChoose;
	Random->Hint=GetTextByID("SRANDOM");
	Random->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	/*
	GP_Button* Historical=MMenu.addGP_Button(NULL,76,140+82*3+Dy,BTNS.GPID,6,7);
	Historical->UserParam=-1;//4;
	Historical->OnUserClick=&MMItemChoose;
	Historical->Hint=GetTextByID("SHISTORICAL");
	Historical->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	*/
	GP_Button* Back=MMenu.addGP_Button(NULL,76,140+35+82*3+Dy,BTNS.GPID,6,7);
	Back->UserParam=5;
	Back->OnUserClick=&MMItemChoose;
	Back->Hint=GetTextByID("SBACK");
	Back->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	ItemChoose=-1;
	int pp=1;
	KeyPressed=false;
	LastKey=0;
	do{
		ProcessMessages();
		if(KeyPressed&&LastKey==27){
			ItemChoose=5;
			KeyPressed=0;
		};
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
		if((ItemChoose==1||ItemChoose==2)&&!CAMPAGINS.NCamp)ItemChoose=-1;
#ifdef TUTORIAL_DEMOVERSION
	if(ItemChoose==2)ItemChoose=-1;
#endif 
	}while(ItemChoose==-1);
	if(ItemChoose==3){
		SlowUnLoadPalette("2\\agew_1.pal");
		SingleOptions();
	};
	if(ItemChoose==1){
		SlowUnLoadPalette("2\\agew_1.pal");
		ProcessCampagins(-1);
	};
#ifndef TUTORIAL_DEMOVERSION
	if(ItemChoose==2){
		SlowUnLoadPalette("2\\agew_1.pal");
		SelectSingleMission();
	};
#endif
	if(ItemChoose==5){
		SlowUnLoadPalette("2\\agew_1.pal");
	};
	return ItemChoose;
};
int NameChoose=-1;
bool MMChooseName(SimpleDialog* SD){
	NameChoose=SD->UserParam;
	Lpressed=false;
	return false;
};
void __stdcall CDGINIT_INIT2();
void __stdcall CDGINIT_INIT1();
#ifdef MAKE_PTC
SFLB_DLLEXPORT SFLB_ReadFirstPlayerName(char* ccc){
	CDGINIT_INIT1();
	CDGINIT_INIT2();
	GFILE* F=Gopen("players.txt","r");
	int N=0;
	ccc[0]=0;
	if(F){
		ccc[0]=0;
		int cc=0;
		int nn=0;
		while(!(cc==0x0A||cc==EOF)){
			cc=Ggetch(F);
			if(!(cc==0x0A||cc==EOF)){
				ccc[nn]=cc;
				nn++;
			}else{
				//Ggetch(f);
			};
		};
		ccc[nn]=0;
		Gclose(F);
	};
};
#endif
bool ENRETVAL=0;
#ifdef MAKE_PTC
void EnterName(char* BackGround){
	//SlowUnLoadPalette("1\\agew_1.pal");
	ENRETVAL=0;
	LoadFog(2);
	LocalGP BTNS("Interface\\Player_Name");
	LocalGP FONT1("romw1");
	LocalGP FONT2("romw");
	RLCFont Font1(FONT1.GPID);
	RLCFont Font2(FONT2.GPID);
	SQPicture Back("Interface\\Background_Player_Name.bmp");
	DialogsSystem MENU(0,0);
	MENU.UserClickSound=-1;
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,0))>>1)-85-125;
	//int dy=(RealLx-GPS.GetGPWidth(BTNS.GPID,0))>>1;
	MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
	//MENU.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	InputBox* IB=MENU.addInputBox(NULL,183-8,561-15,PlName,16,250,40,&WhiteFont,&YellowFont,0);
	IB->Active=true;
	GP_TextButton* TBS[14];
	GPPicture* GPP[14];
	int XL0=104-12;
	int YL0=190-23+4;
	for(int i=0;i<12;i++)TBS[i]=NULL;
	GFILE* F=Gopen("players.txt","r");
	int N=0;
	KeyPressed=0;
	if(F){
		char ccc[128];
		do{
			ccc[0]=0;
			int cc=0;
			int nn=0;
			while(!(cc==0x0A||cc==EOF)){
				cc=Ggetch(F);
				if(!(cc==0x0A||cc==EOF)){
					ccc[nn]=cc;
					nn++;
				}else{
					//Ggetch(f);
				};
			};
			ccc[nn]=0;
			if(ccc[0]){
				if(N<14){
					GPP[N]=MENU.addGPPicture(NULL,XL0,YL0,BTNS.GPID,7+(N%3));
					GPP[N]->Visible=0;
					TBS[N]=MENU.addGP_TextButton(NULL,XL0,YL0,ccc,BTNS.GPID,4+(N%3),&WhiteFont,&YellowFont);
					TBS[N]->FontDy++;
					TBS[N]->OnUserClick=&MMChooseName;
					TBS[N]->UserParam=N;
					TBS[N]->y1-=2;
					//TBS[N]->FontDy++;
					YL0+=26;
					N++;
				};
			};
		}while(ccc[0]&&N<12);
		Gclose(F);
	};
	int LastName=-1;
	if(N){
		strcpy(PlName,TBS[0]->Message);
		LastName=0;
	};
	GP_Button* Accept=MENU.addGP_Button(NULL,113,594,BTNS.GPID,0,1);
	Accept->OnUserClick=&MMItemChoose;
	Accept->UserParam=mcmOk;
	GP_Button* Cancel=MENU.addGP_Button(NULL,333,594,BTNS.GPID,2,3);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;
	ItemChoose=-1;
	NameChoose=-1;
	int pp=1;
	KeyPressed=0;
	do{
		ProcessMessages();
		StdKeys();
		MENU.ProcessDialogs();
		MENU.RefreshView();
		if(NameChoose!=-1){
			strcpy(PlName,TBS[NameChoose]->Message);
			LastName=NameChoose;
			NameChoose=-1;
		};
		Accept->Enabled=strlen(PlName)!=0;
		if(!Accept->Enabled&&ItemChoose==mcmOk)ItemChoose=-1;
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
		for(int i=0;i<N;i++)GPP[i]->Visible=i==LastName;
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		bool orig=true;
		for(int i=0;i<N;i++)if(!strcmp(PlName,TBS[i]->Message))orig=false;
		GFILE* F=Gopen("players.txt","w");
		if(F){
			int NN=0;
			Gprintf(F,"%s\n",PlName);
			NN++;
			for(i=0;i<N;i++){
				if(NN<12&&strcmp(PlName,TBS[i]->Message)){
					Gprintf(F,"%s\n",TBS[i]->Message);
					NN++;
				};
			};
			Gclose(F);
		};
		DLL0(SFLB_LoadPlayerData);//();
		SavePlayerData();
		SlowUnLoadPalette("2\\agew_1.pal");
		ENRETVAL=1;
		return;
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	return;
};
#endif
bool MPL_EnterName(){
	EnterName("Interface\\Multi_opt\\Background_Multi_Options.bmp");
	return ENRETVAL;
};
bool Camp_EnterName(){
	EnterName("Interface\\Campagins\\Background_Campagin.bmp");
	return ENRETVAL;
};
bool CommEnterName(){
	EnterName("Interface\\MainMenu\\Background_main_opt.bmp");
	return ENRETVAL;
};
char IPADDR[128]="";
bool TOTALEXIT=0;
int MPL_ChooseConnection(){
	LocalGP BTNS("Interface\\Type_connection");
	SQPicture Back("Interface\\Background_Type_Connection.bmp");
//#ifndef FRANCEVERSION
//	SQPicture IBACK("Interface\\Background_Type_Connection_Crop.bmp");
//#endif
	LoadFog(2);
	DialogsSystem MENU(0,0);
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,0))>>1)-85;
	//int dy=(RealLx-GPS.GetGPWidth(BTNS.GPID,0))>>1;
	MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
//#ifndef FRANCEVERSION
//	MENU.addPicture(NULL,72,222,&IBACK,&IBACK,&IBACK);
//#endif
	//char* IPTXT=GetTextByID("IP:");
	//int L=GetRLCStrWidth(IPTXT,&YellowFont);
	//MENU.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	int dy1=0;
	int dy2=0;
	int dy3=0;
#ifdef FRANCEVERSION
	dy1=-2;
	dy2=24;
	dy3=-3;
#endif
	dy1-=13;
	dy2-=13;
	dy3-=13;
	GP_Button* IPX=MENU.addGP_Button(NULL,100-3,314-13-26+dy1,BTNS.GPID,0,2);
	IPX->UserParam=0;
	IPX->OnUserClick=&MMChooseName;
	GP_Button* TCP=MENU.addGP_Button(NULL,100-3,340-13-26+dy1,BTNS.GPID,3,5);
	TCP->UserParam=1;
	TCP->OnUserClick=&MMChooseName;
	GP_Button* TCPDIRECT=MENU.addGP_Button(NULL,100-3,340-13+dy1,BTNS.GPID,12,14);
	TCPDIRECT->UserParam=2;
	TCPDIRECT->OnUserClick=&MMChooseName;
#ifdef FRANCEVERSION
	GP_Button* GOA=MENU.addGP_Button(NULL,97,340-13+dy2,BTNS.GPID,15,17);
	GOA->UserParam=100;
	GOA->OnUserClick=&MMChooseName;

	GP_Button* INET=MENU.addGP_Button(NULL,100-3,340+13+dy2,BTNS.GPID,23,25);
	INET->UserParam=4;
	INET->OnUserClick=&MMChooseName;

	GP_Button* INET2=MENU.addGP_Button(NULL,100-3,340+13+dy2+26,BTNS.GPID,20,22);
	INET2->UserParam=3;
	INET2->OnUserClick=&MMChooseName;
#else
	GP_Button* INET=MENU.addGP_Button(NULL,100-3,340+13+dy2,BTNS.GPID,15,17);
	INET->UserParam=4;
	INET->OnUserClick=&MMChooseName;

	GP_Button* INET2=MENU.addGP_Button(NULL,100-3,340+13+dy2+26,BTNS.GPID,20,22);
	INET2->UserParam=3;
	INET2->OnUserClick=&MMChooseName;
#endif
	GP_Button* Create=MENU.addGP_Button(NULL,93,396+13+52+dy2+dy3+26+13,BTNS.GPID,6,7);
	Create->UserParam=mcmHost;
	Create->OnUserClick=&MMItemChoose;
	GP_Button* Join=MENU.addGP_Button(NULL,238,396+13+52+dy2+dy3+26+13,BTNS.GPID,8,9);
	Join->UserParam=mcmJoin;
	Join->OnUserClick=&MMItemChoose;
	GP_Button* Cancel=MENU.addGP_Button(NULL,383,396+13+52+dy2+dy3+26+13,BTNS.GPID,10,11);
	Cancel->UserParam=mcmCancel;
	Cancel->OnUserClick=&MMItemChoose;
	GPPicture* IP1=MENU.addGPPicture(NULL,25+72,180+222+dy2+dy3+26+13,BTNS.GPID,19);
	IP1->Visible=0;
	GPPicture* IP2=MENU.addGPPicture(NULL,230+72,180+222+dy2+dy3+26+13,BTNS.GPID,18);
	IP2->Visible=0;
	InputBox* IBIP=MENU.addInputBox(NULL,228+72,180+222+dy2+dy3+26+13,IPADDR,64,260,20,&YellowFont,&WhiteFont);
	ItemChoose=-1;
	NameChoose=0;
	int pp=1;
	CurProtocol=1;
	do{
		ProcessMessages();
		MENU.ProcessDialogs();
		MENU.RefreshView();
		IBIP->Visible=0;
		IBIP->Enabled=0;
		IP1->Visible=0;
		IP2->Visible=0;
#ifdef FRANCEVERSION
		if(NameChoose==0){
			IPX->PassiveFrame=1;
			CurProtocol=0;
		}else{
			IPX->PassiveFrame=2;
		};
		if(NameChoose==1){
			TCP->PassiveFrame=4;
			CurProtocol=1;
		}else{
			TCP->PassiveFrame=5;
		};
		if(NameChoose==2){
			TCPDIRECT->PassiveFrame=13;
			CurProtocol=2;
			IP1->Visible=1;
			IP2->Visible=1;
			IBIP->Visible=1;
			IBIP->Enabled=1;
		}else{
			TCPDIRECT->PassiveFrame=14;
		};
		if(NameChoose==3){
			INET2->PassiveFrame=21;
			CurProtocol=3;
		}else{
			INET2->PassiveFrame=22;
		};
		if(NameChoose==4){
			INET->PassiveFrame=24;
			CurProtocol=4;
		}else{
			INET->PassiveFrame=25;
		};
		if(NameChoose==100){
			GOA->PassiveFrame=16;
			CurProtocol=100;
		}else{
			GOA->PassiveFrame=17;
		};
#else
		if(NameChoose==0){
			IPX->PassiveFrame=1;
			CurProtocol=0;
		}else{
			IPX->PassiveFrame=2;
		};
		if(NameChoose==1){
			TCP->PassiveFrame=4;
			CurProtocol=1;
		}else{
			TCP->PassiveFrame=5;
		};
		if(NameChoose==2){
			TCPDIRECT->PassiveFrame=13;
			CurProtocol=2;
			IP1->Visible=1;
			IP2->Visible=1;
			IBIP->Visible=1;
			IBIP->Enabled=1;
		}else{
			TCPDIRECT->PassiveFrame=14;
		};
		if(NameChoose==3){
			INET2->PassiveFrame=21;
			CurProtocol=3;
		}else{
			INET2->PassiveFrame=22;
		};
		if(NameChoose==4){
			INET->PassiveFrame=16;
			CurProtocol=4;
		}else{
			INET->PassiveFrame=17;
		};
#endif
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
	}while(ItemChoose==-1);
	if(CurProtocol==100&&ItemChoose!=mcmCancel){
		TOTALEXIT=1;
		CurProtocol=0;
		ItemChoose=mcmCancel;
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	UseGSC_Login=0;
	if(CurProtocol==4){
		CurProtocol=3;
		UseGSC_Login=1;
	};
	return ItemChoose;
};

extern DPID MyDPID;
bool PIEnumeratePlayers(PlayerInfo* PIN,bool DoMsg);
CEXPORT bool EnumPlr(){
	return PIEnumeratePlayers(PINFO,false);
};
PlayerInfo PINFO[8];
char Names[32][8];
int tmm1,tmm2,tmm3;
extern int COUN;
extern char** NatNames;
extern char** NatScripts;
extern int NNations;
char* Unknm="?";
char* GetPName(int i){
	for(int j=0;j<8;j++)if(PINFO[j].ColorID==i)return PINFO[j].name;
	return Unknm;
};
bool ColorMouseOver(SimpleDialog* SD){
	if(!SD->Enabled)return false; 
	GPPicture* CB=(GPPicture*)SD;
	if(Lpressed){
		CB->Nation++;
		if(CB->Nation>6)CB->Nation=0;
		Lpressed=false;
	};
	if(Rpressed){
		CB->Nation--;
		if(CB->Nation<0)CB->Nation=6;
		Rpressed=false;
	};
	return true;
};
bool ChangeAlias(SimpleDialog* SD){
	if((!SD->Enabled)||(!SD->Visible))return false;
	GPPicture* GPP=(GPPicture*)SD;
	if(Lpressed){
		if(GPP->Nation<7)GPP->Nation++;
		else GPP->Nation=0;
		Lpressed=0;
	};
	if(Rpressed){
		if(GPP->Nation>0)GPP->Nation--;
		else GPP->Nation=7;
		Rpressed=0;

	};
	return true;
};
extern int tmtmt;
bool GetPreview(char* Name,byte* Data);
void Decode(byte* data,byte* xlt,int Size){
	for(int i=0;i<Size;i++)data[i]=xlt[data[i]];
};
char* UNKN="?UNKNOWN?";
char* GetPlNameByID(DWORD ID){
	for(int i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID==ID){
			return PINFO[i].name;
		};
	};
	return UNKN;
};
void ControlLingvo(char* str){
	char* c1=strstr(str,"fuck");
	if(c1){
		c1[0]='?';
		c1[1]='?';
		c1[2]='?';
		c1[3]='?';
	};
	c1=strstr(str,"FUCK");
	if(c1){
		c1[0]='?';
		c1[1]='?';
		c1[2]='?';
		c1[3]='?';
	};
};
void StopConnectionToSession(LPDIRECTPLAY3A lpDirectPlay3A);
extern int GLOBALTIME;
extern int PGLOBALTIME;
extern int CurrentStartTime[8];
extern int NextStartTime[8];
CEXPORT void SendPings();
bool CheckPingsReady();

void ClearCTime(){
	memset(CurrentStartTime,0xFF,8*4);
	memset(NextStartTime,0xFF,8*4);
};
void ShowCentralMessage(char* Message,int GPIDX){
	int L=GetRLCStrWidth(Message,&WhiteFont);
	int DX=0;
	DrawStdBar2((RealLx-L-64)/2-DX,(RealLy-70)/2+18,(RealLx+L+64)/2-DX,(RealLy-70)/2+55,GPIDX);
	ShowString((RealLx-L)/2+1-DX,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2+1,Message,&BlackFont);
	ShowString((RealLx-L)/2-DX,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2,Message,&YellowFont);
};
CEXPORT void ShowClanString(int x,int y,char* s,byte State,RLCFont* Fn,RLCFont* Fn1,int DY);
void xLine(int x,int y,int x1,int y1,byte c);
int SearchPlayer(char* Nick){
	for(int i=0;i<TPEN.NPlayers;i++){
		if(!strcmp(Nick,TPEN.Players[i].Name))return i;
	};
	for(i=0;i<TPEN.ABPL.NPlayers;i++){
		if(!strcmp(Nick,TPEN.ABPL.Names[i]))return i+TPEN.NPlayers;
	};
	return -1;
};
void Draw_PLIST(int x,int y,int Lx,int Ly,int Index,byte Active,int param){
	if(Index<TPEN.NPlayers){
		int GPF=param;
		RLCFont* FONT=Active==2?&WhiteFont:&YellowFont;
		RLCFont* FONT1=NULL;
		char cc3[256];
		strcpy(cc3,TPEN.Players[Index].Name);
		//char* cc=strstr(cc3,"[inside]");
		//if(cc)cc[0]=0;
		bool Really=1;
		int DYF=0;
		if(TPEN.Players[Index].ProfState==15&&TPEN.Players[Index].ProfileID){
			//strcat(cc3,"(R)");
			FONT=Active==2?&SpecialWhiteFont:&SpecialYellowFont;
			FONT1=&SpecialRedFont;
			DYF=-5;
			Really=1;
		};
		if(TPEN.Players[Index].ProfState==1||
			(TPEN.Players[Index].ProfState==3&&TPEN.Players[Index].ProfileID)){
			strcat(cc3,"(?)");
		};
		if(Really)ShowClanString(x+45-6,y+3,cc3,Active,FONT,FONT1,DYF);
		else{
			if(FONT1)ShowString(x+45-6+1,y+3+DYF+1,cc3,FONT1);
			ShowString(x+45-6,y+3+DYF,cc3,FONT);
		};
		int png=TPEN.Players[Index].Ping;
		int spp=0;
		if(png<0)spp=16;
		else if(png<300)spp=12;
		else if(png<500)spp=13;
		else if(png<900)spp=14;
		else spp=15;
		if(spp!=16)GPS.ShowGP(x,y,GPF,spp,0);
		if(TPEN.Players[Index].Muted){
			xLine(x+45-7,y+12,x+45+GetRLCStrWidth(cc3,&YellowFont),y+12,RedColor2);
			xLine(x+45-7,y+13,x+45+GetRLCStrWidth(cc3,&YellowFont),y+13,RedColor2);
		};

	}else{
		Index-=TPEN.NPlayers;
		//if(Index<TPEN.NRoomPlayers){
		if(Index<TPEN.ABPL.NPlayers){
			RLCFont* FONT=&RedFont;
			int GPF=param;
			ShowString(x+45,y+3,TPEN.ABPL.Names[Index],FONT);
			GPS.ShowGP(x,y,GPF,17,0);
		};
	};
};
char* BATTLTXT=NULL;
char* DEATHTXT=NULL;
void LimitString(char* str,lpRLCFont FONT,int L){
	int L0;
	do{
		L0=GetRLCStrWidth(str,FONT);
		if(L0>L){
			int LL=strlen(str);
			str[LL-4]='.';
			str[LL-3]='.';
			str[LL-2]='.';
			str[LL-1]=0;
		};
	}while(L0>L);
};
extern word dwVersion;
void CreateRoomsHintString(int Idx,char* hint,bool Active){
	hint[0]=0;
	if(Idx<TPEN.NFRooms){
		int Index=TPEN.FiltRef[Idx];
		if(Index<1000000){
			if(Index>=TPEN.NRooms)return;
			GServer G=TPEN.Room[Index].G;
			strcpy(hint,TPEN.Room[Index].Name);
			char* cc=ServerGetStringValue(G,"mapname","");
			cc=strstr(cc,"|");
			if(cc){
				strcat(hint,", ");
				strcat(hint,cc+1);
				strcat(hint,"\\");
			}else strcat(hint,"\\");
			cc=ServerGetStringValue(G,"gamemode","x");
			if(!strcmp(cc,"closedplaying")){
				strcat(hint,GetTextByID("GAMINPR"));
			}else{
				if(strcmp(cc,"wait")){
					strcat(hint,GetTextByID("GAMINAR"));
				}else{
					if(Active){
						cc=ServerGetStringValue(G,"gamever","0");
						char test[16];
						sprintf(test,"%d.%d%d",dwVersion/100,(dwVersion/10)%10,dwVersion%10);
						if(strcmp(cc,test)){
							sprintf(hint+strlen(hint),GetTextByID("IINVVER"),test);
						}else{
							int max=ServerGetIntValue(G,"maxplayers",0);
							int np=ServerGetIntValue(G,"numplayers",0);
							if(np>=max){
								strcat(hint,GetTextByID("ROMFULL"));
							}else{
								cc=ServerGetStringValue(G,"password","0");
								if(cc[0]=='1'){
									strcat(hint,GetTextByID("RMPASSW"));
								}else{
									int L=GetCEW(G,1);
									if(L==3)strcat(hint,GetTextByID("CANJOIN3")); else 
									if(L==2)strcat(hint,GetTextByID("CANJOIN2")); else 
									if(L==1)strcat(hint,GetTextByID("CANJOIN1")); else 
									strcat(hint,GetTextByID("CANJOIN0"));
								};
							};
						};
					};
				};
			};
		};
	}else hint[0]=0;
};
void CreatePlayerHintString(int Index,char* hint){ 
	if(Index<TPEN.NPlayers){
		if(TPEN.Players[Index].Ping==-1){
			sprintf(hint,GetTextByID("DBLCLICKU"),
				TPEN.Players[Index].Name);
		}else{
			sprintf(hint,GetTextByID("DBLCLICK"),
				TPEN.Players[Index].Name,TPEN.Players[Index].Ping);
		};
	}else{
		Index-=TPEN.NPlayers;
		if(Index<TPEN.ABPL.NPlayers){
			sprintf(hint,GetTextByID("PLINGAME"),TPEN.ABPL.Names[Index]);
		};
	};
};
void Draw_RLIST(int x,int y,int Lx,int Ly,int Idx,byte Active,int param){
	if(Idx<TPEN.NFRooms){
		int Index=TPEN.FiltRef[Idx];
		if(Index<1000000){
			int Sign=0;
			if(Index>=TPEN.NRooms)return;
			int GPF=param;
			RLCFont* FONT=Active==2?&WhiteFont:&YellowFont;
			GServer GG=TPEN.Room[Index].G;
			char ccc3[256];
			char* ccx1=ServerGetStringValue(GG,"password","0");
			strcpy(ccc3,TPEN.Room[Index].Name);
			char* ccv1=ServerGetStringValue(GG,"mapname","0");
			ccv1=strstr(ccv1,"|");
			if(ccv1){
				strcat(ccc3,", ");
				strcat(ccc3,ccv1+1);
			}
			if(ccx1[0]=='1')Sign=1;//strcat(ccc3," [PASSWORD]");
			LimitString(ccc3,FONT,310);
			ShowString(x+45,y+3,ccc3,FONT);
			int png=ServerGetPing(GG);
			char cc[32];
			if(png!=9999){
				sprintf(cc,"%d",png);
				ShowString(486-GetRLCStrWidth(cc,FONT)/2,y+3,cc,FONT);
			};
			char* ccx=ServerGetStringValue(GG,"gamever","?");
			if(ccx){
				ShowString(552-GetRLCStrWidth(ccx,FONT)/2,y+3,ccx,FONT);
			};
			int max=ServerGetIntValue(GG,"maxplayers",0);
			int np=ServerGetIntValue(GG,"numplayers",0);
			sprintf(cc,"%d/%d",np,max);
			ShowString(422-GetRLCStrWidth(cc,FONT)/2,y+3,cc,FONT);
			if(!BATTLTXT){
				BATTLTXT=GetTextByID("BATTLTXT");
				DEATHTXT=GetTextByID("DEATHTXT");
			};
			int TYPE=GetCEW(GG,0);
			if(TYPE){
				ShowString(593,y+3,BATTLTXT,FONT);
			}else{
				ShowString(593,y+3,DEATHTXT,FONT);
			};
			ccx=ServerGetStringValue(GG,"gamemode","x");
			if(!strcmp(ccx,"closedplaying")){
				GPS.ShowGP(x,y,GPF,17,0);
			}else
			if(strcmp(ccx,"wait")){
				GPS.ShowGP(x,y,GPF,60,0);//spy icon
			}else if(Sign){
				GPS.ShowGP(x,y,GPF,61,0);//lock
			};
			int Lev=GetCEW(GG,1);
			if(Lev&&Lev<4)GPS.ShowGP(731,y+2,GPF,61+Lev,0);
			/*
			int png=TPEN.Players[Index].Ping;
			int spp=0;
			if(png<0)spp=16;
			else if(png<300)spp=12;
			else if(png<500)spp=13;
			else if(png<900)spp=14;
			else spp=15;
			GPS.ShowGP(x,y,GPF,spp,0);
			*/
		}else{
			Index-=1000000;
			if(Index<TPEN.NRInGame){
				RoomInGame* RIG=TPEN.RInGame+Index;
				int GPF=param;
				RLCFont* FONT=&RedFont;
				ShowString(x+45,y+3,RIG->Name,FONT);
				char cc[32];
				sprintf(cc,"%d",RIG->NPlayers);
				ShowString(422-GetRLCStrWidth(cc,FONT)/2,y+3,cc,FONT);
				GPS.ShowGP(x,y,GPF,17,0);
				if(!BATTLTXT){
					BATTLTXT=GetTextByID("BATTLTXT");
					DEATHTXT=GetTextByID("DEATHTXT");
				};
				if(RIG->Type){
					ShowString(593,y+3,BATTLTXT,FONT);
				}else{
					ShowString(593,y+3,DEATHTXT,FONT);
				};
			};
		};
	};
};
char SessionName[128]="";
char SessPassword[64]="";
int GMMOD=0;
int GMLEV=0;
int GMMAXPL=7;
void DRAWBOX(int x,int y,int Lx,int Ly,int Idx,byte Active,int param){
	DrawStdBar2(x,y,x+Lx-1,y+Ly-1,param);
}
bool EnterPassword(){
	LocalGP BARS("Interface\\bor2");
	DarkScreen();
	DialogsSystem DSS(0,0);
	SessPassword[0]=0;
	CustomBox* CBOX=DSS.addCustomBox(RealLx/2-170,RealLy/2-44,340,80,&DRAWBOX);
	CBOX->param=BARS.GPID;
	InputBox* IB=DSS.addInputBox(NULL,RealLx/2-143,RealLy/2-2,SessPassword,40,160,20,&WhiteFont,&YellowFont);
	IB->Active=1;
	char* cc=GetTextByID("ENTERPASSWORD");
	DSS.addTextButton(NULL,RealLx/2,RealLy/2-40,cc,&BigYellowFont,&BigYellowFont,&BigYellowFont,1);
	ColoredBar* CB=DSS.addColoredBar(RealLx/2-150,RealLy/2-4,300,24,0xAD);
	CB->Style=1;
	ItemChoose=-1;
	LastKey=0;
	KeyPressed=0;
	do{
		ProcessMessages();
		StdKeys();
		DSS.MarkToDraw();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	return ItemChoose==mcmOk;
};
void EnterPersonalMessage(char* Nick){
	char nick[128];
	strcpy(nick,Nick);
	LocalGP BARS("Interface\\bor2");
	DarkScreen();
	DialogsSystem DSS(0,0);
	int DL=60;
	int Y0=RealLy/2-44+10+70+3;
	int X0=RealLx/2-70-DL-80;
	DSS.addGPPicture(NULL,X0,Y0,BARS.GPID,14);
	GPS.ShowGP(X0,Y0,BARS.GPID,17,0);
	GP_TextButton* OK=DSS.addGP_TextButton(NULL,X0+9,Y0+20,GetTextByID("@OK"),BARS.GPID,15,&WhiteFont,&YellowFont);
	OK->OnUserClick=&MMItemChoose;
	OK->UserParam=mcmOk;

	X0=RealLx/2+70+DL-80;
	DSS.addGPPicture(NULL,X0,Y0,BARS.GPID,14);
	GPS.ShowGP(X0,Y0,BARS.GPID,17,0);
	GP_TextButton* CANCEL=DSS.addGP_TextButton(NULL,X0+9,Y0+20,GetTextByID("@CANCEL"),BARS.GPID,15,&WhiteFont,&YellowFont);
	CANCEL->OnUserClick=&MMItemChoose;
	CANCEL->UserParam=mcmCancel;

	char MESSAGE[256]="";
	
	CustomBox* CBOX=DSS.addCustomBox(RealLx/2-170-DL,RealLy/2-44+10,340+DL*2,80-10,&DRAWBOX);
	CBOX->param=BARS.GPID;
	InputBox* IB=DSS.addInputBox(NULL,RealLx/2-143-10-DL,RealLy/2-2,MESSAGE,120,290+DL*2,20,&WhiteFont,&YellowFont);
	IB->Active=1;
	char cc2[128];
	sprintf(cc2,GetTextByID("ENTERMESS"),nick);
	DSS.addTextButton(NULL,RealLx/2,RealLy/2-40+10,cc2,&YellowFont,&YellowFont,&YellowFont,1);
	ColoredBar* CB=DSS.addColoredBar(RealLx/2-150-DL,RealLy/2-4+1,300+DL*2,24-1,135);//107
	CB->Style=1;
	

	ItemChoose=-1;
	LastKey=0;
	KeyPressed=0;
	do{
		ProcessMessages();
		StdKeys();
		DSS.MarkToDraw();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1&&!GameInProgress);
	if(ItemChoose==mcmOk){
		if(TPEN.Peer&&TPEN.Connected){
			if(MESSAGE[0]){
				peerMessagePlayer(TPEN.Peer,nick,MESSAGE);
				char ccc[128];
				sprintf(ccc,"%s-->%s",TPEN.MyNick,nick);
				TPEN.GlobalChat.Add(ccc,MESSAGE);
			};

		};
	};
	ItemChoose=-1;
};
extern bool ProfIsInit;
bool CreateSessionDialog(){
	if(SessionName[0]==127)strcpy(SessionName,SessionName+5);
	LocalGP BTNS("Interface\\CreateIGame");
	DialogsSystem DSS(((1024-452)>>1)-80,(768-237-26)>>1);
	GPS.ShowGP(DSS.BaseX,DSS.BaseY,BTNS.GPID,1,1);
	DSS.addGPPicture(NULL,0,0,BTNS.GPID,0);
	GP_Button* OKBTN=DSS.addGP_Button(NULL,67,192+26,BTNS.GPID,4,5);
	OKBTN->UserParam=mcmOk;
	OKBTN->OnUserClick=&MMItemChoose;
	GP_Button* CANCELBTN=DSS.addGP_Button(NULL,256,192+26,BTNS.GPID,2,3);
	CANCELBTN->UserParam=mcmCancel;
	CANCELBTN->OnUserClick=&MMItemChoose;
	InputBox* SESSN=DSS.addInputBox(NULL,191,58,SessionName,120,230,20,&YellowFont,&WhiteFont);
	SESSN->Active=1;
	InputBox* SESSPS=DSS.addInputBox(NULL,191,136+26+3,SessPassword,63,230,20,&YellowFont,&WhiteFont);
	GPPicture* GPNP=DSS.addGPPicture(NULL,195+(236-195)*(GMMAXPL-2),111+26,BTNS.GPID,15);
	GP_TextButton* NPL[6];
	for(int i=0;i<6;i++){
		char cc1[3]="2";
		cc1[0]='2'+i;
		NPL[i]=DSS.addGP_TextButton(NULL,195+(236-195)*i,111+26,cc1,BTNS.GPID,14,&WhiteFont,&YellowFont);
		NPL[i]->OnUserClick=&MMItemChoose;
		NPL[i]->UserParam=i;
	};
	ComboBox* LEV=DSS.addGP_ComboBox(NULL,195,85,BTNS.GPID,6,9,0,&WhiteFont,&YellowFont,NULL);
	LEV->AddLine(GetTextByID("LEV_0M"));
	LEV->AddLine(GetTextByID("LEV_1M"));
	LEV->AddLine(GetTextByID("LEV_2M"));
	LEV->AddLine(GetTextByID("LEV_3M"));
	LEV->CurLine=GMLEV;

	ComboBox* GCB=DSS.addGP_ComboBox(NULL,195,85+26,BTNS.GPID,6,9,0,&WhiteFont,&YellowFont,NULL);
	GCB->AddLine(GetTextByID("Deathmatch"));
	GCB->AddLine(GetTextByID("Battle"));
	if(ProfIsInit){
		GCB->AddLine(GetTextByID("Rated_Deathmatch"));
		GCB->CurLine=2;
	}else{
		GCB->CurLine=0;
	};
	ItemChoose=-1;
	do{
		ProcessMessages();
		StdKeys();
		DSS.ProcessDialogs();
		DSS.RefreshView();
		GPNP->x=DSS.BaseX+195+(236-195)*(GMMAXPL-2);
		if(GCB->CurLine==1){
			for(int i=0;i<6;i++){
				NPL[i]->Visible=0;
				NPL[i]->Enabled=0;
			};
			GPNP->Visible=0;
		}else{
			for(int i=0;i<6;i++){
				NPL[i]->Visible=1;
				NPL[i]->Enabled=1;
				/*
				if(i==GMMAXPL-2){
					NPL[i]->ActiveFont=&BigWhiteFont;
					NPL[i]->PassiveFont=&BigYellowFont;
					NPL[i]->FontDy=-4;
				}else{
					NPL[i]->ActiveFont=&WhiteFont;
					NPL[i]->PassiveFont=&YellowFont;
					NPL[i]->FontDy=0;
				};
				*/
			};
			GPNP->Visible=1;
		};
		if(ItemChoose>=0&&ItemChoose<7){
			GMMAXPL=ItemChoose+2;
			ItemChoose=-1;
		};
		for(int i=0;i<6;i++){
			NPL[i]->Sprite=14+(i==(GMMAXPL-2));
		};
		OKBTN->Enabled=SessionName[0]!=0;
	}while(ItemChoose==-1);
	if(GMMOD=GCB->CurLine==2){
		char ccc[256];
		strcpy(ccc,"0017");
		strcat(ccc,SessionName);
		strcpy(SessionName,ccc);
	};
	GMMOD=GCB->CurLine&1;
	GMLEV=LEV->CurLine;
	return ItemChoose==mcmOk;
};
void NoWaitWithMessage(char* Message){
	LocalGP BOR2("Interface\\bor2");
	DarkScreen();
	ShowCentralMessage(Message,BOR2.GPID);
	FlipPages();
};
void WaitWithMessage(char* Message){
	LocalGP BOR2("Interface\\bor2");
	DarkScreen();
	ShowCentralMessage(Message,BOR2.GPID);
	FlipPages();
	int T=GetTickCount();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(GetTickCount()-T<3000&&!KeyPressed);
	KeyPressed=0;
};
char ROOMNAMETOCONNECT[128];
extern char LobbyVersion[32];
bool CheckJoin(GServer G){
	char* ccx=ServerGetStringValue(G,"gamemode","x");
	char* ccv=ServerGetStringValue(G,"gamever","x");
	char cc3[32];
	//sprintf(cc3,"%d.%d%d",dwVersion/100,(dwVersion/10)%10,dwVersion%10);
	return strcmp(ccx,"wait")==0&&!strcmp(ccv,LobbyVersion);
};
extern word dwVersion;


int NCHATS=0;
int MAXCHATS=0;
char** ChatMess=NULL;
char** ChatSender=NULL;
int NPERSCHATS=0;
int MAXPERSCHATS=0;
char** PersChatMess=NULL;
char** PersChatSender=NULL;
void AddPrimitiveChat(char* Nick,char* str,
				  char** &ChatMess,char** &ChatSender,
				  int &NCHATS,int &MAXCHATS){
	if(NCHATS>=MAXCHATS){
		MAXCHATS+=32;
		ChatMess=(char**)realloc(ChatMess,4*MAXCHATS);
		ChatSender=(char**)realloc(ChatSender,4*MAXCHATS);
	};
	if(NCHATS>512){
		free(ChatMess[0]);
		free(ChatSender[0]);
		memcpy(ChatMess,ChatMess+1,NCHATS*4);
		memcpy(ChatSender,ChatSender+1,NCHATS*4);
		NCHATS--;
	};
	ChatMess[NCHATS]=new char[strlen(str)+1];
	strcpy(ChatMess[NCHATS],str);
	ChatSender[NCHATS]=new char[strlen(Nick)+1];
	strcpy(ChatSender[NCHATS],Nick);
	NCHATS++;
};
void AddChatString(char* Nick,char* str,int MaxLx,lpRLCFont FONT,
				  char** &ChatMess,char** &ChatSender,
				  int &NCHATS,int &MAXCHATS){
	bool FLine=1;
	char ACCAMULATOR[256];
	int pp=0;
	int sp=0;
	int LL=strlen(str);
	sprintf(ACCAMULATOR,"%s: ",Nick);
	int LName=GetRLCStrWidth(ACCAMULATOR,FONT);
	if(LName==32)LName++;
	ACCAMULATOR[0]=0;
	do{
		int Lx=GetRLCStrWidth(ACCAMULATOR,FONT)+LName;
		int Lx1=strlen(ACCAMULATOR);
		ACCAMULATOR[Lx1]=str[sp];
		ACCAMULATOR[Lx1+1]=0;
		sp++;
		if(Lx>MaxLx){
			if(LName!=32){
				AddPrimitiveChat(Nick,ACCAMULATOR,ChatMess,ChatSender,NCHATS,MAXCHATS);
				LName=32;
				ACCAMULATOR[0]=0;
			}else{
				AddPrimitiveChat("",ACCAMULATOR,ChatMess,ChatSender,NCHATS,MAXCHATS);
				ACCAMULATOR[0]=0;
			};
		};
	}while(sp<LL);
	if(ACCAMULATOR[0]){
		if(LName!=32){
			AddPrimitiveChat(Nick,ACCAMULATOR,ChatMess,ChatSender,NCHATS,MAXCHATS);
			LName=32;
			ACCAMULATOR[0]=0;
		}else{
			AddPrimitiveChat("",ACCAMULATOR,ChatMess,ChatSender,NCHATS,MAXCHATS);
			ACCAMULATOR[0]=0;
		};
	};
};
bool SENDPRIVMESS(SimpleDialog* SD){
	ComplexBox* CB=(ComplexBox*)SD;
	if(CB->CurrentItem>=0){
		if(CB->CurrentItem<TPEN.NPlayers){
			EnterPersonalMessage(TPEN.Players[CB->CurrentItem].Name);
		}else{
			if(CB->CurrentItem-TPEN.NPlayers<TPEN.ABPL.NPlayers){
				EnterPersonalMessage(TPEN.ABPL.Names[CB->CurrentItem-TPEN.NPlayers]);
			};
		};
	};
	KeyPressed=0;
	LastKey=0;
	return true;
};
bool DisableCreate=0;
extern bool UnderFirewall;

extern char LobbyVersion[32];
void CheckProfileInit();
int GetGerbByScore(int Score){
	if(Score<5*6)return Score/5;
	Score-=5*6;
	if(Score<10*7)return 6+Score/10;
	Score-=10*7;
	if(Score<20*4)return 13+Score/20;
	Score-=20*4;
	if(Score<30*2)return 17+Score/30;
	Score-=30*2;
	if(Score<50*3)return 19+Score/50;
	Score-=50*3;
	if(Score<100*3)return 22+Score/100;
	Score-=100*3;
	if(Score<150*5)return 25+Score/150;
	Score-=150*5;
	int rr=30+Score/200;
	if(rr>41)rr=41;
	return rr;
};
int GetRankByScore(int Score){
	int rr=GetGerbByScore(Score);
	if(rr<5 )return 0;
	if(rr<12)return 1;
	if(rr<16)return 2;
	if(rr<18)return 3;
	if(rr<21)return 4;
	if(rr<24)return 5;
	if(rr<29)return 6;
	if(rr<34)return 7;
	return 8;
};
extern char** NatNames;
void GPI_callback3(GPConnection* gp,void* arg,void* par){
	GPGetInfoResponseArg* GIRA=(GPGetInfoResponseArg*)arg;
	GPGetInfoResponseArg* GPI=(GPGetInfoResponseArg*)par;
	*GPI=*GIRA;
};
extern GPConnection* LOGIN_gp;
void GETCOUNTRY(char* code,char* res);
void DRAW_TOP100(int x,int y,int Lx,int Ly,int Index,byte Active,int param){
	if(Index>=0&&Index<100){
		int fdy=3;
		RLCFont* FNT=&YellowFont;
		if(Active==2){
			FNT=&WhiteFont;
		};
		if(T100.CLIENT[Index].PLINF
			&&T100.CLIENT[Index].PLINF->nick[0]){
			ShowString(x+40,y+fdy,T100.CLIENT[Index].PLINF->nick,FNT);
			char ccc[64];
			if(T100.CLIENT[Index].Score){
				sprintf(ccc,"%d",T100.CLIENT[Index].Score-1);
			}else{
				strcpy(ccc,"???");
			};
			ShowString(x+698-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
			sprintf(ccc,"%d",Index+1);
			ShowString(x+15-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
			strcpy(ccc,T100.CLIENT[Index].PLINF->homepage);
			ShowString(x+261-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
			SYSTEMTIME BIRTH;
			SYSTEMTIME CURTIME;
			FILETIME FT_BIRTH;
			FILETIME FT_CURTIME;
			GetSystemTime(&CURTIME);
			memset(&BIRTH,0,sizeof BIRTH);
			BIRTH.wYear=T100.CLIENT[Index].PLINF->birthyear;
			BIRTH.wMonth=T100.CLIENT[Index].PLINF->birthmonth;
			BIRTH.wDay=T100.CLIENT[Index].PLINF->birthday;
			SystemTimeToFileTime(&BIRTH,&FT_BIRTH);
			SystemTimeToFileTime(&CURTIME,&FT_CURTIME);
			LARGE_INTEGER L_BIRTH;
			LARGE_INTEGER L_CURTIME;
			memcpy(&L_BIRTH,&FT_BIRTH,8);
			memcpy(&L_CURTIME,&FT_CURTIME,8);
			L_CURTIME.QuadPart-=L_BIRTH.QuadPart;
			memcpy(&FT_CURTIME,&L_CURTIME,8);
			FileTimeToSystemTime(&FT_CURTIME,&CURTIME);
			sprintf(ccc,"%d",CURTIME.wYear-1601);
			ShowString(x+378-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);

			int NT=T100.CLIENT[Index].NBattl;
			int NV=T100.CLIENT[Index].NVict;
			int NI=T100.CLIENT[Index].NIncomp;

			sprintf(ccc,"%d",NT+NI);
			ShowString(x+459-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
			sprintf(ccc,"%d",NV);
			ShowString(x+539-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
			if(NT)sprintf(ccc,"%d(%d%%)",NI,NI*100/(NT+NI));
			else sprintf(ccc,"%d",NI);
			ShowString(x+618-GetRLCStrWidth(ccc,FNT)/2,y+fdy,ccc,FNT);
		};
	};
};
typedef byte GR_ARR[8][32]; 
int DrawGraph(Canvas* CAN,int y0,int Npt,GR_ARR Data,byte* Col,int N,word* Max,char* Text){
	byte COL=0x7C;
	byte COL1=0x88;
	int L1=16;
	int L2=102;
	int L3=L2-2;
	int Lx=391;
	CAN->AddRect(0,y0,Lx+2,L1,COL);
	CAN->AddText(10,y0+2,Text,&SmallWhiteFont);
	y0+=L1;

	CAN->AddRect(0,y0,Lx+2,L2,COL);
	CAN->AddBar(1,y0+1,Lx,L2-2,COL1);
	int MaxV=1;
	for(int i=0;i<N;i++)if(Max[i]>MaxV)MaxV=Max[i];
	int divisor=100*MaxV;
	for(i=0;i<N;i++){
		byte C=0xD0+Col[i]*4;
		byte* data=&Data[i][0];
		int Maxi=Max[i];
		for(int j=1;j<Npt;j++){
			int x0=1+((j-1)*Lx)/Npt;
			int x1=1+(j*Lx)/Npt;
			CAN->AddLine(1+((j-1)*Lx)/Npt,
						 y0+1+L3-(int(data[j-1])*Maxi*(L3-2))/divisor,
				         1+(j*Lx)/Npt,
						 y0+1+L3-(int(data[j])*Maxi*(L3-2))/divisor,C);
		};
	};
	char cc[32];
	sprintf(cc,"%d",MaxV);
	CAN->AddText(10,y0+2,cc,&SmallWhiteFont);
	return L2+L1;
};
int  RESPOND=0;
//1-ok
//2-password
//3-invalid version
//4-room is full
//5-not created
//6-room is in the game
DWORD  PASSHASH=0;
word JP_ver=0;
DWORD CalcPassHash(char* pass){
	int L=strlen(pass);
	DWORD S=0;
	for(int i=0;i<L;i++)S+=pass[i];
	for(i=0;i<L-1;i++)S+=pass[i]*pass[i+1];
	for(i=0;i<L-2;i++)S+=pass[i]*pass[i+1]*pass[i+2];
	for(i=0;i<L-3;i++)S+=pass[i]*pass[i+1]*pass[i+2]*pass[i+3];
	for(i=0;i<L-4;i++)S+=pass[i]*pass[i+1]*pass[i+2]*pass[i+3]*pass[i+4];
	for(i=0;i<L-5;i++)S+=pass[i]*pass[i+1]*pass[i+2]*pass[i+3]*pass[i+4]*pass[i+5];
	return S;
};
bool GetPLIP(char* Nick,char* IP);
extern char RESPNICK[128];
bool TryToJoinToPlayer(char* name){
	char Name[128];
	strcpy(Name,name);
	LocalGP BOR2("Interface\\bor2");
	char ccc[128];
	RESPOND=0;
	PASSHASH=0;
	JP_ver=0;
	peerMessagePlayer(TPEN.Peer,Name,"@@@I_WANT_TO_JOIN");
	int T0=GetTickCount();
	DarkScreen();
	ShowCentralMessage(GetTextByID("ICJOIN"),BOR2.GPID);
	FlipPages();
	int TT=GetTickCount();
	do{
		if(GetTickCount()-TT>3000){
			peerMessagePlayer(TPEN.Peer,Name,"@@@I_WANT_TO_JOIN");
			TT=GetTickCount();
		};
		ProcessMessages();
		if(RESPOND&&_stricmp(RESPNICK,Name))RESPOND=0;
	}while(GetTickCount()-T0<20000&&RESPOND==0);
	char* ERR=NULL;
	switch(RESPOND){
	case 0:
		ERR=GetTextByID("JNPG_E3");
		break;
	case 2:
		if(EnterPassword()){
			DWORD V=CalcPassHash(SessPassword);
			int T0=GetTickCount();
			do{
				ProcessMessages();
			}while(GetTickCount()-T0<1000);
			if(V!=PASSHASH){
				ERR=GetTextByID("JNPG_E6");
				return false;
			};
		}else return false;
		break;
	case 3:
		ERR=GetTextByID("JNPG_E2");
		break;
	case 4:
		ERR=GetTextByID("JNPG_E4");
		break;
	case 5:
		ERR=GetTextByID("JNPG_E1");
		break;
	case 6:
		ERR=GetTextByID("JNPG_E5");
		break;
	};
	if(ERR){
		DarkScreen();
		ShowCentralMessage(ERR,BOR2.GPID);
		FlipPages();
		int T0=GetTickCount();
		KeyPressed=0;
		do{
			ProcessMessages();
		}while(GetTickCount()-T0<10000&&!KeyPressed);
		return false;
	};
	return true;
};
void RunHTTPC(){
	STARTUPINFO			StartUpInfo;
	PROCESS_INFORMATION		ProcessInformation;
	memset(&StartUpInfo,0x00,sizeof(STARTUPINFO));
	StartUpInfo.cb=sizeof(STARTUPINFO);	
	StartUpInfo.wShowWindow=SW_SHOWMINNOACTIVE;
	StartUpInfo.dwFlags=STARTF_USESHOWWINDOW;

	CreateProcess(	"httpc.exe",
				NULL,
				NULL,
				NULL,
				FALSE,
				0x00,
				NULL,
				NULL,
				&StartUpInfo,
				&ProcessInformation);
};
bool GetPLIP(char* Nick,char* IP);
bool T100_cmd_done=0;
void DecodeGS_Password(char* pass,char* result);
bool CheckPlayerToExit();
extern bool RejectThisPlayer;
void SendPlayerRequest();
bool INSIDE1=0;
CIMPORT
void SendPrivateMessage(char* Nick,char* MESSAGE);
bool CheckForPersonalChat(char* STR){
	if(STR[0]=='-'&&STR[1]=='-'&&STR[2]=='>'){
		char* SS=strchr(STR,':');
		if(SS){
			int L=SS-STR-3;
			if(L>0){
				char SS3[256];
				memcpy(SS3,STR+3,L);
				SS3[L]=0;
				if(UseGSC_Login){
					SendPrivateMessage(SS3,SS+1);
				}else
				if(TPEN.Peer&&TPEN.Connected){
					peerMessagePlayer(TPEN.Peer,SS3,SS+1);
					char ccc[128];
					sprintf(ccc,"%s-->%s",TPEN.MyNick,SS3);
					TPEN.GlobalChat.Add(ccc,SS+1);
					return true;
				};
			};
		};
	};
	return false;
};
extern char LASTCLICKCHATNAME[128];
bool CheckPersonality(char* MESSAGE){
	if(LASTCLICKCHATNAME[0]){
		char CC4[512];
		CC4[0]=0;
		if(MESSAGE[0]=='-'&&MESSAGE[1]=='-'&&MESSAGE[2]=='>'){
			char* SS=strchr(MESSAGE,':');
			if(SS){
				strcpy(CC4,SS+1);
			}else strcpy(CC4,MESSAGE);
		}else{
			strcpy(CC4,MESSAGE);
		};
		sprintf(MESSAGE,"-->%s:%s",LASTCLICKCHATNAME,CC4);
		LASTCLICKCHATNAME[0]=0;
		return true;
	};
	return false;
};
bool HaveNewGeneral=0;
bool HaveNewPers=0;
bool ReadWinString(GFILE* F,char* STR,int Max);

void SaveGlobalChat(){
	FILE* F=fopen("Internet\\common_chat.txt","a");
	if(F){
		if(NCHATS){
			SYSTEMTIME ST;
			GetSystemTime(&ST);
			fprintf(F,"[UPDATED %d.%d.%d %d:%d]\n",ST.wDay,ST.wMonth,ST.wYear,ST.wHour,ST.wMinute);
		};
		for(int i=0;i<NCHATS;i++)fprintf(F,"%s:%s\n",ChatSender[i],ChatMess[i]);
		fclose(F);
	};
};
void LoadGeneralChat(){
	return;
	GFILE* F=Gopen("Internet\\common_chat.txt","r");
	if(F){
		char SS[512];
		bool WELL=0;
		do{
			SS[0]=0;
			ReadWinString(F,SS,511);
			WELL=SS[0]!=0;
			char* si=strchr(SS,':');
			if(si&&si-SS<30){
				si[0]=0;
				AddChatString(SS,si+1,430,&YellowFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
			};
		}while(WELL);
		SYSTEMTIME ST;
		GetSystemTime(&ST);
		char CCC[256];
		sprintf(CCC,"< %d.%d.%d %d:%d >",ST.wDay,ST.wMonth,ST.wYear,ST.wHour,ST.wMinute);
		AddChatString("",CCC,430,&YellowFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
		Gclose(F);
	};
};
void SavePersChat(){
	FILE* F=fopen("Internet\\personal_chat.txt","a");
	if(F){
		if(NPERSCHATS){
			SYSTEMTIME ST;
			GetSystemTime(&ST);
			fprintf(F,"[UPDATED %d.%d.%d %d:%d]\n",ST.wDay,ST.wMonth,ST.wYear,ST.wHour,ST.wMinute);
		};
		for(int i=0;i<NPERSCHATS;i++)fprintf(F,"%s:%s\n",PersChatSender[i],PersChatMess[i]);
		fclose(F);
	};
};
void LoadPersonalChat(){
	return;
	GFILE* F=Gopen("Internet\\personal_chat.txt","r");
	if(F){
		char SS[512];
		bool WELL=0;
		do{
			SS[0]=0;
			ReadWinString(F,SS,511);
			WELL=SS[0]!=0;
			char* si=strchr(SS,':');
			if(si&&si-SS<30){
				si[0]=0;
				AddChatString(SS,si+1,430,&YellowFont,PersChatMess,PersChatSender,NPERSCHATS,MAXPERSCHATS);
			};
		}while(WELL);
		SYSTEMTIME ST;
		GetSystemTime(&ST);
		char CCC[256];
		sprintf(CCC,"< %d.%d.%d %d:%d >",ST.wDay,ST.wMonth,ST.wYear,ST.wHour,ST.wMinute);
		AddChatString("",CCC,430,&YellowFont,PersChatMess,PersChatSender,NPERSCHATS,MAXPERSCHATS);
		Gclose(F);
	};

};
int ProcessInternetConnection(bool Active){
	if(UseGSC_Login){
		int r=Process_GSC_ChatWindow(Active,&GlobalRIF);
		return r;
	};
	INSIDE1=1;
	if(Active){
		ItemChoose=-1;
		GameInProgress=0;
		PlayerMenuMode=1;
		/*
		for(int i=0;i<NCHATS;i++){
			free(ChatMess[i]);
			free(ChatSender[i]);
		};
		if(MAXCHATS){
			free(ChatMess);
			free(ChatSender);
		};
		NCHATS=0;
		MAXCHATS=0;
		ChatMess=NULL;
		ChatSender=NULL;
		*/
	};
	ClearScreen();
	LoadFog(2);
	LoadPalette("2\\agew_1.pal");
	LocalGP BTNS("Interface\\igame");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP DIS("Interface\\an_start_disable");
	LocalGP SCROL("Interface\\_Slider");	
	LocalGP BOR2("Interface\\bor2");
	LocalGP IBTN("Interface\\IButtons");
	LocalGP GERB("Interface\\gerb_low2");
	LocalGP TOPGP("Interface\\top100");
	LocalGP SYM3("Interface\\isymb3");
	LocalGP CHFILTER("Interface\\Chat_Filter");


	SQPicture Back("Interface\\Backgroung_Internet_Game.bmp");
	SQPicture IPLInfoBack("Interface\\Background_Player_Info.bmp");
	SQPicture ITOPBACK("Interface\\Background_Top100.bmp");
	Back.Draw(0,0);
	DarkScreen();
	ShowCentralMessage(GetTextByID("ICCONN"),BOR2.GPID);
	FlipPages();
	//CheckProfileInit();
	if(!TPEN.Connected){
		Back.Draw(0,0);
		DarkScreen();
		ShowCentralMessage(GetTextByID("ICCONN"),BOR2.GPID);
		FlipPages();
		TPEN.Connect(PlName);
		bool NeedDraw=1;
		do{
			ProcessMessages();
			if(bActive){
				if(NeedDraw)FlipPages();
				NeedDraw=0;
			}else NeedDraw=1;
			if(GetTickCount()-TPEN.ConnStartTime>60000){
				TPEN.ErrorType=1;
			};
		}while(!(TPEN.Connected||TPEN.ErrorType));
		if(TPEN.ErrorType){
			Back.Draw(0,0);
			DarkScreen();
			ShowCentralMessage(GetTextByID("ICUNCON"),BOR2.GPID);
			FlipPages();
			bool NeedDraw=1;
			KeyPressed=0;
			int t0=GetTickCount();
			do{
				ProcessMessages();
				if(bActive){
					if(NeedDraw)FlipPages();
					NeedDraw=0;
				}else NeedDraw=1;
			}while((GetTickCount()-t0<20000)&&!KeyPressed);
			KeyPressed=0;
			peerShutdown(TPEN.Peer);
			TPEN.Peer=NULL;
			INSIDE1=0;
			return false;
		};
		TPEN.MyIP[0]=0;
		GetPLIP(TPEN.MyNick,TPEN.MyIP);
	};
	if(TPEN.MyRoom&&Active)TPEN.LeaveMyRoom();
	DialogsSystem DSS(0,0);

	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	DSS.HintFont=&hfnt;
	DSS.HintY=701;
	DSS.HintX=18;

	DSS.addPicture(NULL,0,0,&Back,&Back,&Back);
	int PLIX=32;
	int PLIY=123;

	Picture* IPINF=DSS.addPicture(NULL,PLIX,PLIY,&IPLInfoBack,&IPLInfoBack,&IPLInfoBack);
	IPINF->Visible=0;
	int GRBX=158-177;
	int GRBY=123-133+8;
	//GPPicture* GERBACK=DSS.addGPPicture(NULL,PLIX+GRBX,PLIY+GRBY,GERB.GPID,0);
	//GERBACK->Visible=0;
	GPPicture* GERBVAL=DSS.addGPPicture(NULL,PLIX+GRBX,PLIY+GRBY,GERB.GPID,1);
	GERBVAL->Visible=0;
	//ListBox* PILB=DSS.addListBox(NULL,PLIX+327,PLIY+36,8,300,26,&YellowFont,&YellowFont,NULL);
	//PILB->Visible=0;
	Canvas* PILB=DSS.AddCanvas(PLIX+337,PLIY+36,394,215);
	PILB->BottomY=0;

	VScrollBar* PIVS=DSS.addNewGP_VScrollBar(NULL,PLIX+745,PLIY+28,226,1,0,SCROL.GPID,0);
	PIVS->Visible=0;
	PILB->VS=PIVS;
	PIVS->ScrDy=100;
	PIVS->OnesDy=32;
	//top100
	Picture* TOPBACK=DSS.addPicture(NULL,PLIX,PLIY,&ITOPBACK,&ITOPBACK,&ITOPBACK);
	TOPBACK->Visible=0;
	TOPBACK->Enabled=0;
	ComplexBox* TOPBOX=DSS.addComplexBox(PLIX+4,PLIY+36,8,26,&DRAW_TOP100,TOPGP.GPID,0);
	TOPBOX->Visible=0;
	TOPBOX->Enabled=0;
	TOPBOX->N=100;
	TOPBOX->OnUserClick=&MMItemChoose;
	TOPBOX->Hint=GetTextByID("INHIN2");
	TOPBOX->UserParam=43;

	GPPicture* CHATFBACK=DSS.addGPPicture(NULL,481,607,CHFILTER.GPID,0);
	CHATFBACK->OnUserClick=&MMItemChoose;
	CHATFBACK->UserParam=103;

	GPPicture* GLOBCHAT=DSS.addGPPicture(NULL,483,615,CHFILTER.GPID,1);
	GPPicture* PERSCHAT=DSS.addGPPicture(NULL,483,615,CHFILTER.GPID,2);

	
	VScrollBar* TOPVS=DSS.addNewGP_VScrollBar(NULL,PLIX+745,PLIY+28,226,1,0,SCROL.GPID,0);
	TOPVS->Visible=0;
	TOPBOX->VS=TOPVS;
	TOPVS->Visible=0;
	TOPVS->Enabled=0;
	TOPVS->ScrDy=70;
	TOPVS->OnesDy=10;

	byte BCL=79;
	ColoredBar* TOPBTN=DSS.addViewPort2(632-10,613,25,19,BCL);
	TOPBTN->OnUserClick=&MMItemChoose;
	TOPBTN->Hint=GetTextByID("INHIN1");
	TOPBTN->UserParam=10;
	ColoredBar* PLIBTN=DSS.addViewPort2(658-10,613,26,19,BCL);
	PLIBTN->OnUserClick=&MMItemChoose;
	PLIBTN->Hint=GetTextByID("INHIN2");
	PLIBTN->UserParam=11;
	ColoredBar* LETBTN=DSS.addViewPort2(686-10,613,27,19,BCL);
	LETBTN->OnUserClick=&MMItemChoose;
	LETBTN->Hint=GetTextByID("INHIN4");
	LETBTN->UserParam=31;
	ColoredBar* SRVBTN=DSS.addViewPort2(607-10,613,25,19,BCL);
	SRVBTN->OnUserClick=&MMItemChoose;
	SRVBTN->Hint=GetTextByID("INHIN3");
	SRVBTN->UserParam=13;
	GPPicture* KICKPIC=DSS.addGPPicture(NULL,714-10+2,613,SYM3.GPID,0);
	ColoredBar* KICKBTN=DSS.addViewPort2(714-10,613,25,19,BCL);
	KICKBTN->OnUserClick=&MMItemChoose;
	char* MUTE=GetTextByID("INHIN5");
	char* NOMUTE=GetTextByID("INHIN6");
	KICKBTN->Hint=MUTE;
	KICKBTN->UserParam=14;
	if(Active){
		ColoredBar* JOINPL=DSS.addViewPort2(715-10+25,613,23,19,BCL);
		JOINPL->OnUserClick=&MMItemChoose;
		JOINPL->Hint=GetTextByID("JOINPLGM");
		JOINPL->UserParam=15;
	}else{
		DSS.addGPPicture(NULL,715-10+25,613,SYM3.GPID,1);
	};
	CHATSTRING[0]=0;
	ChatViewer* CHVIEW=DSS.addChatViewer(NULL,42,418+5,7,26,462,&ChatMess,&ChatSender,&NCHATS);
	ChatViewer* PERSCHVIEW=DSS.addChatViewer(NULL,42,418+5,7,26,462,&PersChatMess,&PersChatSender,&NPERSCHATS);
	char CHATMESSAGE[256]="";
	InputBox* CHATBOX=DSS.addInputBox(NULL,122,612,CHATMESSAGE,200,392-36,20,&YellowFont,&WhiteFont);
	CHATBOX->Active=1;
	VScrollBar* CHSCR=DSS.addNewGP_VScrollBar(NULL,505,411,197,1,0,SCROL.GPID,0);
	CHSCR->Visible=0;
	
	KeyPressed=0;
	VScrollBar* RMVS=DSS.addNewGP_VScrollBar(NULL,778,152,193,1,0,SCROL.GPID,0);
	RMVS->ScrDy=6*10;
	RMVS->OnesDy=10;
	ComplexBox* RMLIST=DSS.addComplexBox(37,155+5,7,26,&Draw_RLIST,BTNS.GPID,0);
	RMLIST->param=BTNS.GPID;
	RMLIST->VS=RMVS;

	VScrollBar* PLVS=DSS.addNewGP_VScrollBar(NULL,778,438,197-26,1,0,SCROL.GPID,0);
	PLVS->ScrDy=6*10;
	PLVS->OnesDy=10;
	ComplexBox* PLLIST=DSS.addComplexBox(559,447,6,26,&Draw_PLIST,BTNS.GPID,6);
	PLLIST->param=BTNS.GPID;
	PLLIST->VS=PLVS;
	//PLLIST->OnUserClick=&MMItemChoose;
	//PLLIST->UserParam=31;
	int NL=3;
	if(!Active)NL--;
	int LONE=32;
	int LLX=60;
	int LY1=LONE*NL;
	int xc=916;
	int yc=380;
	//CustomBox* BARX=DSS.addCustomBox(xc-LLX,yc-LY1/2-20,LLX*2,LY1+40,&DRAWBOX);
	//BARX->param=BOR2.GPID;
	GP_Button* CREATE=NULL;
	GP_Button* JOIN=NULL;
	GP_Button* REFRESH=NULL;
	if(!Active){
		CREATE=DSS.addGP_Button(NULL,862,668,IBTN.GPID,7,6);
		CREATE->UserParam=78;
		CREATE->OnUserClick=&MMItemChoose;
		CREATE->Hint=GetTextByID("IG_BACK");
		REFRESH=DSS.addGP_Button(NULL,862,668-100,IBTN.GPID,11,10);
		REFRESH->UserParam=77;
		REFRESH->OnUserClick=&MMItemChoose;
		REFRESH->Hint=GetTextByID("IG_REFRESH");
	}else{
		DSS.addGPPicture(NULL,862,668-100,IBTN.GPID,3);
		JOIN=DSS.addGP_Button(NULL,862,668-100,IBTN.GPID,5,4);
		JOIN->UserParam=mcmJoin;
		JOIN->OnUserClick=&MMItemChoose;
		JOIN->Hint=GetTextByID("IG_JOIN");

		DSS.addGPPicture(NULL,862,668-200,IBTN.GPID,0);
		CREATE=DSS.addGP_Button(NULL,862,668-200,IBTN.GPID,2,1);
		CREATE->UserParam=mcmOk;
		CREATE->OnUserClick=&MMItemChoose;
		CREATE->Hint=GetTextByID("IG_CREATE");

		REFRESH=DSS.addGP_Button(NULL,862,668-300,IBTN.GPID,11,10);
		REFRESH->UserParam=77;
		REFRESH->OnUserClick=&MMItemChoose;
		REFRESH->Hint=GetTextByID("IG_REFRESH");
	};
	//VideoButton* OkBtn=DSS.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	//OkBtn->Hint=GetTextByID("MOSTART");
	//OkBtn->UserParam=mcmOk;
	//OkBtn->OnUserClick=&MMItemChoose;
	if(Active){
		VideoButton* CancelBtn=DSS.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
		CancelBtn->UserParam=mcmCancel;
		CancelBtn->OnUserClick=&MMItemChoose;
		CancelBtn->Hint=GetTextByID("IG_CANCEL");
	};
	
	//FILTERS
	char* ALLTX=GetTextByID("ALL");
	ComboBox* PLAYERS=DSS.addGP_ComboBox(NULL,398,352,BTNS.GPID,18,9,0,&WhiteFont,&YellowFont,NULL);
	PLAYERS->Hint=GetTextByID("FIL_PLAYERS");
	PLAYERS->FontDx-=4;
	PLAYERS->AddLine(ALLTX);
	PLAYERS->AddLine("1");
	PLAYERS->AddLine("2");
	PLAYERS->AddLine("3");
	PLAYERS->AddLine("4");
	PLAYERS->AddLine("5");
	PLAYERS->AddLine("6");
	PLAYERS->AddLine(">1");
	PLAYERS->AddLine(">2");
	PLAYERS->AddLine(">3");
	PLAYERS->AddLine(">4");
	PLAYERS->AddLine(">5");
	PLAYERS->AddLine(">6");
	ComboBox* PING=DSS.addGP_ComboBox(NULL,456,352,BTNS.GPID,26,9,0,&WhiteFont,&YellowFont,NULL);
	PING->Hint=GetTextByID("FIL_PING");
	PING->FontDx-=4;
	PING->AddLine(ALLTX);
	PING->AddLine("<100");
	PING->AddLine("<200");
	PING->AddLine("<300");
	PING->AddLine("<400");
	PING->AddLine("<500");
	PING->AddLine("<600");
	PING->AddLine("<700");
	PING->AddLine("<800");
	ComboBox* VERSION=DSS.addGP_ComboBox(NULL,524,352,BTNS.GPID,26,9,0,&WhiteFont,&YellowFont,NULL);
	VERSION->Hint=GetTextByID("FIL_VERS");
	char cc[32];
	sprintf(cc,"%s",LobbyVersion);
	VERSION->AddLine(ALLTX);
	VERSION->AddLine(cc);
	VERSION->FontDx-=4;
	ComboBox* TYPE=DSS.addGP_ComboBox(NULL,590,352,BTNS.GPID,34,9,0,&WhiteFont,&YellowFont,NULL);
	TYPE->Hint=GetTextByID("FIL_TYPE");
	TYPE->AddLine(ALLTX);
	TYPE->AddLine(GetTextByID("DEATHTXT"));
	TYPE->AddLine(GetTextByID("BATTLTXT"));
	ComboBox* LEVEL=DSS.addGP_ComboBox(NULL,723,352,BTNS.GPID,18,9,0,&WhiteFont,&YellowFont,NULL);
	LEVEL->Hint=GetTextByID("FIL_LEVEL");
	LEVEL->FontDx-=4;
	LEVEL->OneDx-=4;
	LEVEL->AddLine(ALLTX);
	LEVEL->AddLine(GetTextByID("LEV_1"));
	LEVEL->AddLine(GetTextByID("LEV_2"));
	LEVEL->AddLine(GetTextByID("LEV_3"));
	
	char MASK[64]="";
	GP_Button* CBI[6];
	InputBox* MSIB=DSS.addInputBox(NULL,73,351,MASK,60,300,20,&YellowFont,&WhiteFont);
	MSIB->Hint=GetTextByID("FIL_NAME");
	int ccc=152;
	SimpleDialog* SORT_Name=DSS.addViewPort(70,129,321,19);
	SORT_Name->Hint=GetTextByID("SRT_ROOM");
	SORT_Name->UserParam=1;
	SORT_Name->OnUserClick=&CHANGESORT;
	CBI[0]=DSS.addGP_Button(NULL,69+3,128,BTNS.GPID,51,50);
	SimpleDialog* SORT_Players=DSS.addViewPort(395,128,55,19);
	SORT_Players->Hint=GetTextByID("SRT_PLAYERS");
	SORT_Players->UserParam=2;
	SORT_Players->OnUserClick=&CHANGESORT;
	CBI[1]=DSS.addGP_Button(NULL,395+3,128,BTNS.GPID,55,54);
	SimpleDialog* SORT_Ping=DSS.addViewPort(454,129,63,19);
	SORT_Ping->Hint=GetTextByID("SRT_PING");
	SORT_Ping->UserParam=3;
	SORT_Ping->OnUserClick=&CHANGESORT;
	CBI[2]=DSS.addGP_Button(NULL,453+3,128,BTNS.GPID,53,52);
	SimpleDialog* SORT_Vers=DSS.addViewPort(522,129,62,19);
	SORT_Vers->Hint=GetTextByID("SRT_VERS");
	SORT_Vers->UserParam=4;
	SORT_Vers->OnUserClick=&CHANGESORT;
	CBI[3]=DSS.addGP_Button(NULL,521+3,128,BTNS.GPID,59,58);
	SimpleDialog* SORT_Type=DSS.addViewPort(588,129,200-61,19);
	SORT_Type->Hint=GetTextByID("SRT_TYPE");
	SORT_Type->UserParam=5;
	SORT_Type->OnUserClick=&CHANGESORT;
	CBI[4]=DSS.addGP_Button(NULL,587+3,128,BTNS.GPID,57,56);
	SimpleDialog* SORT_Level=DSS.addViewPort(722,129,55,19);
	SORT_Level->Hint=GetTextByID("SRT_LEVEL");
	SORT_Level->UserParam=6;
	SORT_Level->OnUserClick=&CHANGESORT;
	CBI[5]=DSS.addGP_Button(NULL,723,128,BTNS.GPID,66,65);
	int LOSPR[6]={50,54,52,58,56,65};
	//-------//
	int NCLINES=0;
	char* PNAME="";
	int i;
	ItemChoose=-1;
	TPEN.FILTER.CRC+=10;
	bool FIRST=1;
	char ROOMLISTHINT[512]="";
	char PLLISTHINT[512]="";
	RMLIST->Hint=ROOMLISTHINT;
	PLLIST->Hint=PLLISTHINT;
	TextButton* TBNP=DSS.addTextButton(NULL,785,417,"                        ",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,0);
	TextButton* TBNG=DSS.addTextButton(NULL,386,132,"                        ",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,0);
	char* tx_NPL=GetTextByID("NPLAYMSS");
	char* tx_NRM=GetTextByID("NROOMMSS");
	int PLINFMOD=0;
	InternetStatsChunks ISC;
	ISC.Clear();
	GPGetInfoResponseArg GPI;
	if(Active){
		RunHTTPC();
	};
	char CURRNICK[128];
	CURRNICK[0]=0;
	int CurLBP=PLAYERS->CurLine;
	bool DOPASS=0;
	if(Active&&CheckLogin()){
		SendPlayerRequest();
	};
	char* ONLY=GetTextByID("ONLYOU");
	bool PREVCHATMODE=0;
	bool CURCHMODE=1;
	int LastEnterPress=GetTickCount()-20000;
	char PREVMESSAGE[512]="";
	do{
		if(!CURCHMODE){
			PERSCHVIEW->Visible=1;
			PERSCHVIEW->Enabled=1;
			CHVIEW->Visible=0;
			CHVIEW->Enabled=0;
			if(PREVCHATMODE){
				if(*PERSCHVIEW->NChats>PERSCHVIEW->ScrNy){
					CHSCR->SPos=*PERSCHVIEW->NChats-PERSCHVIEW->ScrNy;
					CHSCR->SMaxPos=CHSCR->SPos;
				};
			};
			PREVCHATMODE=0;
			if(HaveNewGeneral){
				GLOBCHAT->Visible=(GetTickCount()/800)&1;
				PERSCHAT->Visible=0;
			}else{
				GLOBCHAT->Visible=1;
				PERSCHAT->Visible=0;
			};
			HaveNewPers=0;
		}else{
			PERSCHVIEW->Visible=0;
			PERSCHVIEW->Enabled=0;
			CHVIEW->Visible=1;
			CHVIEW->Enabled=1;
			if(!PREVCHATMODE){
				if(*CHVIEW->NChats>CHVIEW->ScrNy){
					CHSCR->SPos=*CHVIEW->NChats-CHVIEW->ScrNy;
					CHSCR->SMaxPos=CHSCR->SPos;
				};
			};
			PREVCHATMODE=1;
			if(HaveNewPers){
				GLOBCHAT->Visible=0;
				PERSCHAT->Visible=(GetTickCount()/800)&1;
			}else{
				GLOBCHAT->Visible=0;
				PERSCHAT->Visible=1;
			};
			HaveNewGeneral=0;
		};
		if(LASTCLICKCHATNAME[0]){
			for(int i=0;i<TPEN.NPlayers;i++)if(!strcmp(TPEN.Players[i].Name,LASTCLICKCHATNAME)){
				PLLIST->CurrentItem=i;
				PLLIST->FirstVisItem=i;
				PLVS->SPos=i*10;
				if(PLVS->SPos>PLVS->SMaxPos)PLVS->SPos=PLVS->SMaxPos;
				PLLIST->CurrentItem=PLVS->SPos/10;
				PLLIST->FirstVisItem=PLVS->SPos/10;
			};
		};
		if(CheckPersonality(CHATMESSAGE)){
			CHATBOX->CursPos=strlen(CHATMESSAGE);
		};
		if(CURRNICK[0]&&CurLBP==PLLIST->CurrentItem&&CurLBP!=-1){
			int cp=SearchPlayer(CURRNICK);
			if(cp!=-1)PLLIST->CurrentItem=cp;
		};
		if(PLLIST->CurrentItem>=0){
			int v=PLLIST->CurrentItem;
			if(v<TPEN.NPlayers){
				strcpy(CURRNICK,TPEN.Players[v].Name);
				CurLBP=v;
			}else{
				v-=TPEN.NPlayers;	
				if(v<TPEN.ABPL.NPlayers){
					strcpy(CURRNICK,TPEN.ABPL.Names[v]);
					CurLBP=v+TPEN.NPlayers;
				};
			};
		};
		
		if(PLLIST->CurrentItem>=0){
			if(PLLIST->CurrentItem<TPEN.NPlayers){
				if(TPEN.Players[PLLIST->CurrentItem].Muted){
					KICKBTN->Hint=NOMUTE;
					KICKPIC->Visible=0;
				}else{
					KICKBTN->Hint=MUTE;
					KICKPIC->Visible=1;
				};
			}else KICKBTN->Hint=MUTE;
		}else KICKBTN->Hint=MUTE;
		if(PLINFMOD==1||PLINFMOD==2){
			for(int p=0;p<6;p++){
				CBI[p]->Enabled=0;
				CBI[p]->Visible=0;
			};
			PLAYERS->Visible=0;
			PING->Visible=0;
			VERSION->Visible=0;
			TYPE->Visible=0;
			LEVEL->Visible=0;

			SORT_Name->Visible=0;
			SORT_Players->Visible=0;
			SORT_Ping->Visible=0;
			SORT_Vers->Visible=0;
			SORT_Type->Visible=0;
			SORT_Level->Visible=0;
			MSIB->Enabled=0;
			MSIB->Visible=0;

			RMLIST->Visible=0;
			RMLIST->Enabled=0;
			RMVS->Visible=0;
			RMVS->Enabled=0;

			IPINF->Visible=1;
			IPINF->Enabled=1;
			//GERBACK->Visible=1;
			//GERBACK->Enabled=1;
			GERBVAL->Visible=1;
			GERBVAL->Enabled=1;
			PILB->Visible=1;
			PILB->Enabled=1;

			TOPBACK->Visible=0;
			TOPBOX->Visible=0;
			TOPVS->Visible=0;
			TOPBACK->Enabled=0;
			TOPBOX->Enabled=0;
			TOPVS->Enabled=0;
			//PIVS->Visible=PILB->NItems>PILB->ny;
			TBNG->Visible=0;
			if(PLINFMOD==1){
				if(GPI.result!=GP_NO_ERROR){
					PLINFMOD=2;
					int y0=PILB->BottomY;
					PILB->AddText(16,y0,GetTextByID("PIF_UNACC"),&RedFont);
					PILB->BottomY+=18;
				};
				if(GPI.nick[0]&&GPI.result==GP_NO_ERROR){
					PLINFMOD=2;
					byte cc=0x7C;
					int y0=PILB->BottomY;
					int tdy=5;
					int msx1=120;
					char ccc[256];
					char ccc1[256];

					PILB->AddRect(0,y0,393,27,cc);
					PILB->AddLine(msx1,y0,msx1,y0+26,cc);
					PILB->AddText(16,y0+tdy,GetTextByID("PIF_ST0"),&YellowFont);
					GETCOUNTRY(GPI.countrycode,ccc);
					PILB->AddText(msx1+16,y0+tdy,ccc,&YellowFont);	
					y0+=26;

					PILB->AddRect(0,y0,393,27,cc);
					PILB->AddLine(msx1,y0,msx1,y0+26,cc);
					PILB->AddText(16,y0+tdy,GetTextByID("PIF_ST1"),&YellowFont);
					sprintf(ccc,"%d.%d.%d",GPI.birthday,GPI.birthmonth,GPI.birthyear);
					PILB->AddText(msx1+16,y0+tdy,ccc,&YellowFont);	
					y0+=26;

					PILB->AddRect(0,y0,393,27,cc);
					PILB->AddLine(msx1,y0,msx1,y0+26,cc);
					PILB->AddText(16,y0+tdy,GetTextByID("PIF_ST2"),&YellowFont);
					switch(GPI.sex){
					case GP_MALE:
						PILB->AddText(msx1+16,y0+tdy,GetTextByID("GEN_M"),&YellowFont);	
						break;
					case GP_FEMALE:
						PILB->AddText(msx1+16,y0+tdy,GetTextByID("GEN_F"),&YellowFont);	
						break;
					default:
						PILB->AddText(msx1+16,y0+tdy,GetTextByID("GEN_U"),&YellowFont);	
						break;
					};
					y0+=26;

					PILB->AddRect(0,y0,393,27,cc);
					PILB->AddLine(msx1,y0,msx1,y0+26,cc);
					PILB->AddText(16,y0+tdy,GetTextByID("PIF_ST3"),&YellowFont);
					PILB->AddText(msx1+16,y0+tdy,GPI.email,&YellowFont);	
					y0+=26;

					if(GPI.icquin){
						PILB->AddRect(0,y0,393,27,cc);
						PILB->AddLine(msx1,y0,msx1,y0+26,cc);
						PILB->AddText(16,y0+tdy,GetTextByID("ICQ#"),&YellowFont);
						sprintf(ccc,"%d",GPI.icquin);
						PILB->AddText(msx1+16,y0+tdy,ccc,&YellowFont);	
						y0+=26;
					};

					if(GPI.homepage[0]){
						PILB->AddRect(0,y0,393,27,cc);
						PILB->AddLine(msx1,y0,msx1,y0+26,cc);
						PILB->AddText(16,y0+tdy,GetTextByID("PIF_ST5"),&YellowFont);
						PILB->AddText(msx1+16,y0+tdy,GPI.homepage,&YellowFont);	
						y0+=26;
					};
					//y0+=16;
					PILB->BottomY=y0;
					if(DOPASS)ISC.StartDownload(GPI.profile,1);
					else ISC.StartDownload(GPI.profile,0);
				};
			};
			if(ISC.CDOWN.Started&&(ISC.CDOWN.Finished||ISC.Error)){
				if(ISC.CDOWN.CurPage==1&&!ISC.CDOWN.Error){
					char res[128],rrr[128];
					DecodeGS_Password(res,(char*)ISC.Chunks[0]->Data);
					sprintf(rrr,"password: %s",res);
					PILB->AddText(0,PILB->BottomY,rrr,&YellowFont);
					PILB->BottomY+=24;
					ISC.Clear();
					ISC.StartDownload(GPI.profile,0);
				};
				if(ISC.CDOWN.CurPage==0&&!ISC.CDOWN.Error){
					int NREC=0;
					int CURSCORE=0;
					int NINCOMP=0;
					for(int i=0;i<ISC.N;i++){
						if(ISC.Chunks[i]->Index==0||ISC.Chunks[i]->Index==27){
							int ProfileID=ISC.CDOWN.CurProfile;
							int w1=*((DWORD*)ISC.Chunks[i]->Data);
							int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
							int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
							
							int sco1=w1^DWORD(ProfileID);
							int sco2=w2^0xFB47E6C3;
							if(sco1==sco2){
								NREC=w3;
								CURSCORE=sco1;
							};
						};
						if(ISC.Chunks[i]->Index==28){
							int ProfileID=ISC.CDOWN.CurProfile;
							int w1=*((DWORD*)ISC.Chunks[i]->Data);
							int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
							int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
							int w5=*((DWORD*)(ISC.Chunks[i]->Data+16));
							int w6=*((DWORD*)(ISC.Chunks[i]->Data+20));
							int sco1=w1^DWORD(ProfileID);
							int sco2=w2^0xFB47E6C3;
							int incomp1=(w5+DWORD(ProfileID))^(0x6523A4+DWORD(ProfileID));
							int incomp2=(w6+DWORD(ProfileID))^(0x1234E6-DWORD(ProfileID));

							if(sco1==sco2&&incomp1==incomp2){
								NREC=w3;
								CURSCORE=sco1;
								NINCOMP=incomp1;
							};
						};
					};
					ISC.Clear();
					ISC.CDOWN.Started=0;
					if(NREC){
						ISC.StartDownload(ISC.CDOWN.CurProfile,2+NREC);
					};
					char ccc[128];
					char cc2[36];
					sprintf(cc2,"RS_RANK_%d",GetRankByScore(CURSCORE));
					sprintf(ccc,GetTextByID("SCORANK"),CURSCORE,GetTextByID(cc2));
					PILB->AddText(0,PILB->BottomY,ccc,&YellowFont);
					PILB->BottomY+=24;
					if(NREC){
						sprintf(ccc,GetTextByID("TX_INCOMP"),NINCOMP,NREC+NINCOMP,(NINCOMP*100)/(NREC+NINCOMP));
						PILB->AddText(0,PILB->BottomY,ccc,&YellowFont);
						PILB->BottomY+=24;
					};
					GERBVAL->SpriteID=GetGerbByScore(CURSCORE)+1;
					GERBVAL->Visible=1;
				}else if(ISC.CDOWN.CurPage>1){
					if(!ISC.CDOWN.Error){
						int TextDy=5;
						int XB0=0;
						int XB1=18;
						int XB2=XB1+18;
						int XB3=XB2+123;
						int XB4=XB3+64;
						int XB5=XB4+90;
						int XB6=XB5+80;
						byte COL=0x7C;
						for(int j=ISC.N-1;j>=0;j--){
							char ccc[128];
							char MapName[128];
							char GameName[128];
							if(ISC.Chunks[j]->Index==81){
								byte* data=ISC.Chunks[j]->Data;
								int pos=0;
								DWORD Date=*((DWORD*)data);
								int Min=Date%60;
								Date/=60;
								int Hour=Date%24;
								Date/=24;
								int Day=(Date%31)+1;
								Date/=31;
								int Month=(Date%12)+1;
								Date/=12;
								int Year=2000+Date;
								int Npl=data[4];
								word PTime=*((word*)(data+5));
								int DScore=data[8];
								int LMap=data[9];
								memcpy(MapName,data+10,LMap);
								MapName[LMap]=0;
								int LGame=data[10+LMap];
								memcpy(GameName,data+11+LMap,LGame);
								GameName[LGame]=0;		
								int Y0=PILB->BottomY;		

								RLCFont* FNT=&YellowFont;
								PILB->AddRect(XB0,Y0,393,27,COL);
								PILB->AddRect(XB0+1,Y0+1,393-2,27-2,COL);
								int xx3=120;
								PILB->AddLine(xx3,Y0,xx3,Y0+26,COL);
								sprintf(ccc,"%d.%d.%d %d:%d%d",Day,Month,Year,Hour,Min/10,Min%10);
								PILB->AddCText((xx3+XB0)>>1,Y0+TextDy,ccc,FNT);
								sprintf(ccc,"%s (%d min)",GameName,PTime);
								PILB->AddText(xx3+16,Y0+TextDy,ccc,FNT);
								Y0+=26;
								/*
								sprintf(ccc,"Map: %s",MapName);
								PILB->AddRect(XB0,Y0,393,27,COL);
								PILB->AddText(0,Y0,ccc,&YellowFont);
								Y0+=26;
								*/

								pos=11+LMap+LGame;
								//PILB->AddItem("Players:",0);
								int TeamID=0;
								byte pmask=0;	

								byte Popul[8][32];
								byte SCORE[8][32];
								word MaxPopul[8];
								word MaxScore[8];
								byte ColorN[8];

								for(int i=0;i<Npl;i++){

									PILB->AddRect(XB0,Y0,393,27,COL);
									PILB->AddLine(XB1,Y0,XB1,Y0+26,COL);
									PILB->AddLine(XB2,Y0,XB2,Y0+26,COL);
									PILB->AddLine(XB3,Y0,XB3,Y0+26,COL);
									PILB->AddLine(XB4,Y0,XB4,Y0+26,COL);
									PILB->AddLine(XB5,Y0,XB5,Y0+26,COL);

									int LNick=data[pos+6+7];
									memcpy(MapName,data+pos+7+7,LNick);
									MapName[LNick]=0;
									DWORD Score=*((DWORD*)(data+pos+2));
									byte Mask=data[pos+6];
									if(!(Mask&pmask)){
										pmask=Mask;
										TeamID++;
									};
									byte Color=data[pos+7];
									ColorN[i]=Color;
									byte NationID=data[pos+8];
									//sprintf(ccc,"%s (%.2f), ",MapName,float(Score)/100);
									sprintf(ccc,"%d",TeamID);
									int xc=(XB1+XB2)>>1;
									PILB->AddBar(xc-4,Y0+13-4,8,8,0xD0+Color*4);
									PILB->AddCText((XB0+XB1)>>1,Y0+TextDy,ccc,FNT);
									PILB->AddText(XB2+5,Y0+TextDy,MapName,FNT);
									sprintf(ccc,"%.2f",float(Score)/100);
									PILB->AddCText((XB3+XB4)>>1,Y0+TextDy,ccc,FNT);
									if(NationID<NNations)PILB->AddCText((XB4+XB5)>>1,Y0+TextDy,NatNames[NationID],FNT);
									ccc[0]=0;
									switch(data[pos+1]){
									case 1://defeat
										strcat(ccc,"Defeat.");
										break;
									case 0://victory
										strcat(ccc,"Victory!");
										break;
									case 3://disconnectted
										strcat(ccc,"???");
										break;
									default:
										strcat(ccc,"?unknown?");
										break;
									};
									pos+=7+7+LNick;
									PILB->AddCText((XB5+XB6)>>1,Y0+TextDy,ccc,FNT);
									Y0+=26;
									MaxScore[i]=*((DWORD*)(data+pos));
									MaxPopul[i]=*((DWORD*)(data+pos+2));
									pos+=4;
									memcpy(SCORE[i],data+pos,32);
									pos+=32;
									memcpy(Popul[i],data+pos,32);
									pos+=32;
								};

								word CSCOR=*((word*)(data+pos));
								char dscor=data[pos+2];
								pos+3;
								
								Y0+=DrawGraph(PILB,Y0,32,SCORE,ColorN,Npl,MaxScore,GetTextByID("HDR_SCORE:"));
								Y0+=DrawGraph(PILB,Y0,32,Popul,ColorN,Npl,MaxPopul,GetTextByID("HDR_POPUL:"));
								sprintf(ccc,GetTextByID("HDR_DSCORE"),CSCOR,dscor);
								PILB->AddText(0,Y0,ccc,FNT);
								Y0+=26;
								Y0+=16;
								PILB->BottomY=Y0;
							};
						};
					};
					ISC.Clear();
					if(ISC.CDOWN.CurPage>2){
						ISC.StartDownload(ISC.CDOWN.CurProfile,ISC.CDOWN.CurPage-1);
					};
				};
			};
			if(ISC.Error)PLINFMOD=0;
			if(!GERBVAL->SpriteID)GERBVAL->Visible=0;
		}else if(PLINFMOD==3){
			TOPBACK->Visible=1;
			TOPBOX->Visible=1;
			TOPBACK->Enabled=1;
			TOPBOX->Enabled=1;
			MSIB->Enabled=0;
			MSIB->Visible=0;
			RMLIST->Visible=0;
			RMLIST->Enabled=0;

			IPINF->Visible=0;
			IPINF->Enabled=0;
			GERBVAL->Visible=0;
			GERBVAL->Enabled=0;
			PILB->Visible=0;
			PILB->Enabled=0;
			PIVS->Visible=0;
			RMVS->Visible=0;
			RMVS->Enabled=0;
			for(int p=0;p<6;p++){
				CBI[p]->Enabled=0;
				CBI[p]->Visible=0;
			};
			PLAYERS->Visible=0;
			PING->Visible=0;
			VERSION->Visible=0;
			TYPE->Visible=0;
			LEVEL->Visible=0;
			TBNG->Visible=0;

			SORT_Name->Visible=0;
			SORT_Players->Visible=0;
			SORT_Ping->Visible=0;
			SORT_Vers->Visible=0;
			SORT_Type->Visible=0;
			SORT_Level->Visible=0;

			TOPBACK->Visible=1;
			TOPBACK->Enabled=1;
			TOPBOX->Visible=1;
			TOPBOX->Enabled=1;
		}else{
			RMLIST->Visible=1;
			RMLIST->Enabled=1;

			MSIB->Enabled=1;
			MSIB->Visible=1;

			IPINF->Visible=0;
			IPINF->Enabled=0;
			//GERBACK->Visible=0;
			//GERBACK->Enabled=0;
			GERBVAL->Visible=0;
			GERBVAL->Enabled=0;
			PILB->Visible=0;
			PILB->Enabled=0;
			PIVS->Visible=0;
			for(int p=0;p<6;p++){
				CBI[p]->Enabled=1;
				CBI[p]->Visible=1;
			};
			PLAYERS->Visible=1;
			PING->Visible=1;
			VERSION->Visible=1;
			TYPE->Visible=1;
			LEVEL->Visible=1;
			TBNG->Visible=1;

			SORT_Name->Visible=1;
			SORT_Players->Visible=1;
			SORT_Ping->Visible=1;
			SORT_Vers->Visible=1;
			SORT_Type->Visible=1;
			SORT_Level->Visible=1;

			TOPBACK->Visible=0;
			TOPBOX->Visible=0;
			TOPVS->Visible=0;
			TOPBACK->Enabled=0;
			TOPBOX->Enabled=0;
			TOPVS->Enabled=0;
		};
		if(UnderFirewall){
			DisableCreate=NotifyFirewallState();
			UnderFirewall=0;
		};
		sprintf(TBNP->Message,tx_NPL,TPEN.NPlayers+TPEN.ABPL.NPlayers);
		sprintf(TBNG->Message,tx_NRM,RMLIST->N);
		TBNP->x=785-GetRLCStrWidth(TBNP->Message,&YellowFont);
		TBNG->x=386-GetRLCStrWidth(TBNG->Message,&YellowFont);
		if(!Active){
			PIEnumeratePlayers(PINFO,false);
			SendPings();
			if(NPlayers>7)NPlayers=7;
		};
		for(i=0;i<6;i++){
			if(abs(TPEN.SORTTYPE)==i+1){
				CBI[i]->PassiveFrame=LOSPR[i];
			}else{
				CBI[i]->PassiveFrame=1000;
			}
			//CBI[i]->Visible=abs(TPEN.SORTTYPE)==i+1;
			//CBI[i]->Enabled=abs(TPEN.SORTTYPE)==i+1;
			//CBI[i]->Style=1;
		};
		if(RMLIST->M_OvrItem>=0){
			CreateRoomsHintString(RMLIST->M_OvrItem,ROOMLISTHINT,Active);
		};
		if(PLLIST->M_OvrItem>=0){
			CreatePlayerHintString(PLLIST->M_OvrItem,PLLISTHINT);
		};
		TPEN.FILTER.CHK_Ver=VERSION->CurLine!=0;
		TPEN.FILTER.CHK_Ping=PING->CurLine!=0;
		TPEN.FILTER.MinPing=PING->CurLine*100;
		TPEN.FILTER.CHK_Type=TYPE->CurLine;
		TPEN.FILTER.CHK_Level=LEVEL->CurLine;
		strcpy(TPEN.FILTER.MASKSTR,MASK);
		if(PLAYERS->CurLine){
			if(PLAYERS->CurLine<7){
				TPEN.FILTER.CHK_Players=1;
				TPEN.FILTER.CHK_MinPlayers=0;
				TPEN.FILTER.NPlayers=PLAYERS->CurLine;
			}else{ 
				TPEN.FILTER.CHK_Players=0;
				TPEN.FILTER.CHK_MinPlayers=1;
				TPEN.FILTER.NPlayers=PLAYERS->CurLine-6;
			};
		}else{
			TPEN.FILTER.CHK_Players=0;
			TPEN.FILTER.CHK_MinPlayers=0;
		};
		TPEN.ProcessRoomsInGame();
		PLLIST->N=TPEN.NPlayers+TPEN.ABPL.NPlayers;//TPEN.NRoomPlayers;
		GServer CSRV=NULL;
		if(RMLIST->CurrentItem!=-1&&RMLIST->CurrentItem<TPEN.NFRooms&&TPEN.FiltRef[RMLIST->CurrentItem]<1000000){
			CSRV=TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G;
		};
		TPEN.ProcessFilter();
		RMLIST->CurrentItem=-1;
		for(i=0;i<TPEN.NFRooms;i++)if(TPEN.FiltRef[i]<1000000)if(TPEN.Room[TPEN.FiltRef[i]].G==CSRV)
			RMLIST->CurrentItem=i;
		if(PLLIST->CurrentItem>=PLLIST->N)PLLIST->CurrentItem=PLLIST->N-1;
		RMLIST->N=TPEN.NFRooms;//+TPEN.NRInGame;
		if(RMLIST->FirstVisItem+RMLIST->NOnScr>=RMLIST->N)
			RMLIST->FirstVisItem=RMLIST->N-RMLIST->NOnScr;
		if(RMLIST->FirstVisItem<0)RMLIST->FirstVisItem=0;
		if(RMLIST->CurrentItem>=RMLIST->N)RMLIST->CurrentItem=RMLIST->N-1;
		int NCL=7;
		bool AddChat=FIRST;
		bool AddPersChat=0;
		FIRST=0;
		if(TPEN.GlobalChat.NCStr){
			for(int j=0;j<TPEN.GlobalChat.NCStr;j++){
				AddChatString(
					TPEN.GlobalChat.CStr[j].PlName,
					TPEN.GlobalChat.CStr[j].Message,430,
					&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
				AddChat=1;
				char CCX[128];
				sprintf(CCX,"%s-->",TPEN.MyNick);
				if(strstr(TPEN.GlobalChat.CStr[j].PlName,ONLY)){
					AddChatString(
						TPEN.GlobalChat.CStr[j].PlName,
						TPEN.GlobalChat.CStr[j].Message,430,
						&WhiteFont,PersChatMess,PersChatSender,NPERSCHATS,MAXPERSCHATS);
					AddPersChat=1;
					HaveNewPers=1;
				}else{
					if(strstr(TPEN.GlobalChat.CStr[j].PlName,CCX)){
						AddChatString(
							TPEN.GlobalChat.CStr[j].PlName,
							TPEN.GlobalChat.CStr[j].Message,430,
							&WhiteFont,PersChatMess,PersChatSender,NPERSCHATS,MAXPERSCHATS);
						AddPersChat=1;
					}else HaveNewGeneral=1;
				};
			};
			TPEN.GlobalChat.Clear();
		};
		PNAME="";
		if(CHVIEW->Visible){
			if(NCHATS>NCL){
				int pp=CHSCR->SMaxPos;
				CHSCR->SMaxPos=NCHATS-NCL;
				if(AddChat&&pp==CHSCR->SPos||!CHSCR->SPos)CHSCR->SPos=CHSCR->SMaxPos;
				CHSCR->Visible=1;
				CHVIEW->ChatDY=CHSCR->SPos;
			}else{
				CHSCR->Visible=0;
				CHSCR->SPos=0;
				CHVIEW->ChatDY=0;
			};
		}else{
			if(NPERSCHATS>NCL){
				int pp=CHSCR->SMaxPos;
				CHSCR->SMaxPos=NPERSCHATS-NCL;
				if(AddPersChat&&pp==CHSCR->SPos||!CHSCR->SPos)CHSCR->SPos=CHSCR->SMaxPos;
				CHSCR->Visible=1;
				PERSCHVIEW->ChatDY=CHSCR->SPos;
			}else{
				CHSCR->Visible=0;
				CHSCR->SPos=0;
				PERSCHVIEW->ChatDY=0;
			};
		};
		ProcessMessages();
		ISC.ProcessDownload();
		T100.Process();
		if(!TPEN.Connected){
			DarkScreen();
			ShowCentralMessage(GetTextByID("ICCONN"),BOR2.GPID);
			FlipPages();
			TPEN.Connect(PlName);
			bool NeedDraw=1;
			do{
				ProcessMessages();
				if(bActive){
					if(NeedDraw)FlipPages();
					NeedDraw=0;
				}else NeedDraw=1;
				if(GetTickCount()-TPEN.ConnStartTime>60000){
					TPEN.ErrorType=1;
				};
			}while(!(TPEN.Connected||TPEN.ErrorType));
			if(TPEN.ErrorType){
				Back.Draw(0,0);
				DarkScreen();
				ShowCentralMessage(GetTextByID("ICUNCON"),BOR2.GPID);
				FlipPages();
				bool NeedDraw=1;
				KeyPressed=0;
				int t0=GetTickCount();
				do{
					ProcessMessages();
					if(bActive){
						if(NeedDraw)FlipPages();
						NeedDraw=0;
					}else NeedDraw=1;
				}while((GetTickCount()-t0<20000)&&!KeyPressed);
				KeyPressed=0;
				peerShutdown(TPEN.Peer);
				TPEN.Peer=NULL;
				INSIDE1=0;
				return false;
			};
			TPEN.MyIP[0]=0;
			GetPLIP(TPEN.MyNick,TPEN.MyIP);
		};
		if(KeyPressed&&LastKey==13&&GetTickCount()-LastEnterPress>4000){
			KeyPressed=0;
			if(CHATMESSAGE[0]){
				LastEnterPress=GetTickCount();
				if(strcmp(PREVMESSAGE,CHATMESSAGE)){
					strcpy(PREVMESSAGE,CHATMESSAGE);
					if(!CheckForPersonalChat(CHATMESSAGE))TPEN.SendGlobalChat(CHATMESSAGE);
					if(CHATMESSAGE[0]=='-'&&CHATMESSAGE[1]=='-'&&CHATMESSAGE[2]=='>'){
						char* ss=strstr(CHATMESSAGE,":");
						if(ss)ss[1]=0;
						else CHATMESSAGE[0]=0;
					}else{
						CHATMESSAGE[0]=0;
					};
				};
			};
		};
		if(GameInProgress){
			INSIDE1=0;
			return 0;
		};
		DSS.MarkToDraw();
		DSS.ProcessDialogs();
		DSS.RefreshView();
		
		if(RMLIST->CurrentItem>=0&&TPEN.FiltRef&&(!DisableCreate)
			&&TPEN.FiltRef[RMLIST->CurrentItem]<1000000
			&&TPEN.FiltRef[RMLIST->CurrentItem]<TPEN.NRooms
			&&RMLIST->CurrentItem<TPEN.NFRooms
			&&CheckJoin(TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G)){
			if(JOIN){
				JOIN->Visible=1;
				JOIN->Enabled=1;
			};
		}else{
			if(JOIN){
				JOIN->Visible=0;
				JOIN->Enabled=0;
			};
		};
		if(CREATE){
			CREATE->Visible=!DisableCreate;
			CREATE->Enabled=!DisableCreate;
		}
		if(ItemChoose==mcmJoin){
			if(RMLIST->CurrentItem>=0&&TPEN.FiltRef[RMLIST->CurrentItem]<1000000&&RMLIST->CurrentItem<TPEN.NFRooms
					&&CheckJoin(TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G)){
				char* gg=ServerGetStringValue(TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G,"password","0");
				bool okk=0;
				if(gg[0]=='1'){
					okk=EnterPassword();
					KeyPressed=0;
				}else{
					SessPassword[0]=0;
					okk=1;
				};
				if(okk){
					DarkScreen();
					ShowCentralMessage(GetTextByID("ICJOIN"),BOR2.GPID);
					FlipPages();
					strcpy(TPEN.HostMessage,TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].Name);
					strcpy(ROOMNAMETOCONNECT,TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].Name);
					TPEN.JoinRoom(TPEN.Room+TPEN.FiltRef[RMLIST->CurrentItem],SessPassword);
					if(!TPEN.MyRoom){
						//Unable to connect.
						ItemChoose=-1;
					}else{
						if(gg[0]=='1'){
							do{
								ProcessMessages();
							}while(TPEN.MyRoom&&!TPEN.MyRoom->RoomConnected);
							if(TPEN.MyRoom&&TPEN.MyRoom->RoomConnected){
								strcpy(IPADDR,ServerGetAddress(TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G));
								INSIDE1=0;
								return 2;
							}else{
								WaitWithMessage(GetTextByID("ICUNJ"));
								IPADDR[0]=0;
							};
						}else{
							strcpy(IPADDR,ServerGetAddress(TPEN.Room[TPEN.FiltRef[RMLIST->CurrentItem]].G));
							INSIDE1=0;
							return 2;
						};
					};
				};
			};
			ItemChoose=-1;
		}else
		if(ItemChoose==mcmOk){
			if(CreateSessionDialog()){
				DarkScreen();
				ShowCentralMessage(GetTextByID("ICCREATE"),BOR2.GPID);
				FlipPages();
				if(GMMOD&1)TPEN.CreateStagingRoom(SessionName,SessPassword,2,GMMOD,GMLEV);
				else TPEN.CreateStagingRoom(SessionName,SessPassword,GMMAXPL,GMMOD,GMLEV);
				INSIDE1=0;
				return 1+GMMOD*2;
			}else{
				ItemChoose=-1;
			};
		}else if(ItemChoose==77){
			ItemChoose=-1;
			TPEN.RefreshSessions();
		}else if(ItemChoose==31){
			ItemChoose=-1;
			//if(PLLIST->CurrentItem>=0&&PLLIST->CurrentItem<TPEN.NPlayers){
			//	EnterPersonalMessage(TPEN.Players[PLLIST->CurrentItem].Name);
			//};
			if(PLLIST->CurrentItem>=0){
				if(PLLIST->CurrentItem<TPEN.NPlayers){
					EnterPersonalMessage(TPEN.Players[PLLIST->CurrentItem].Name);
				}else{
					if(PLLIST->CurrentItem-TPEN.NPlayers<TPEN.ABPL.NPlayers){
						EnterPersonalMessage(TPEN.ABPL.Names[PLLIST->CurrentItem-TPEN.NPlayers]);
					};
				};
			};
			KeyPressed=0;
			LastKey=0;
		}else if(ItemChoose==10){//top100
			if(CheckLogin()){
				//if(!T100_cmd_done){
					T100.Clear();
					T100.Download();
					T100.Started=1;
				//	T100_cmd_done=1;
				//};
				TOPVS->SPos=0;
				PLINFMOD=3;
			};
			ItemChoose=-1;
		}else if(ItemChoose==11){//player info
			if(PLLIST->CurrentItem>=0&&CheckLogin()){
				if(PLLIST->CurrentItem<TPEN.NPlayers){
					PILB->L=0;
					PILB->BottomY=0;
					if(TPEN.Players[PLLIST->CurrentItem].ProfileID){
						//ISC.StartDownload(TPEN.Players[PLLIST->CurrentItem].ProfileID,0);
						ISC.CDOWN.Started=0;
						ISC.Error=0;
						ISC.Clear();
						PLINFMOD=1;
						char* Name=TPEN.Players[PLLIST->CurrentItem].Name;
						PILB->AddText(2,PILB->BottomY+2,Name,&BigRedFont);
						PILB->AddText(0,PILB->BottomY,Name,&BigYellowFont);
						PILB->BottomY+=32;
						memset(&GPI,0,sizeof GPI);
						GPResult Res=gpGetInfo(LOGIN_gp,TPEN.Players[PLLIST->CurrentItem].ProfileID,GP_DONT_CHECK_CACHE,GP_NON_BLOCKING,&GPI_callback3,&GPI);
						PIVS->SPos=0;
					};
				};
			};
			ItemChoose=-1;
			GERBVAL->SpriteID=0;
		}else if(ItemChoose==43){//t100 click
			int Index=TOPBOX->CurrentItem;
			if(Index<100&&T100.CLIENT[Index].PLINF){
				int prof=T100.CLIENT[Index].PLINF->profile;
				if(prof){
					PILB->L=0;
					PILB->BottomY=0;
					ISC.CDOWN.Started=0;
					ISC.Error=0;
					ISC.Clear();
					PLINFMOD=1;
					char* Name=T100.CLIENT[Index].PLINF->nick;
					PILB->AddText(2,PILB->BottomY+2,Name,&BigRedFont);
					PILB->AddText(0,PILB->BottomY,Name,&BigYellowFont);
					PILB->BottomY+=32;
					memset(&GPI,0,sizeof GPI);
					GPResult Res=gpGetInfo(LOGIN_gp,prof,GP_DONT_CHECK_CACHE,GP_NON_BLOCKING,&GPI_callback3,&GPI);
					PIVS->SPos=0;
				};
				GERBVAL->SpriteID=0;
			};
			ItemChoose=-1;
		}else if(ItemChoose==13){//servers list
			PLINFMOD=0;
			ItemChoose=-1;
		}else if(ItemChoose==14){
			if(PLLIST->CurrentItem>=0){
				if(PLLIST->CurrentItem<TPEN.NPlayers){
					TPEN.Players[PLLIST->CurrentItem].Muted=!TPEN.Players[PLLIST->CurrentItem].Muted;
				};
			};
			ItemChoose=-1;
		}else if(ItemChoose==15){
			if(PLLIST->CurrentItem<TPEN.NPlayers){
				if(TryToJoinToPlayer(TPEN.Players[PLLIST->CurrentItem].Name)){
					INSIDE1=0;
					return 2;
				}else ItemChoose=-1;
			};

		};
		if(RejectThisPlayer||CheckPlayerToExit())ItemChoose=mcmCancel;
		if(ItemChoose==103){
			CURCHMODE=!CURCHMODE;
			ItemChoose=-1;
		};
	}while(ItemChoose==-1&&!GameInProgress);
	if(Active&&TPEN.Connected){
		TPEN.Disconnect();
	};
	INSIDE1=0;
	return 0;
};
CEXPORT void SendPings();
bool CheckPingsReady();
int GetAveragePing();
extern int CurStatus;
void ReceiveAll();
void CreateDiffStr(char* str);
extern int NPings;
int GetMaxRealPing();
extern int CurrentMaxPing[8];
int PPTIME=0;
bool SendToAllPlayers(DWORD Size,LPVOID lpData);
int GetMapSUMM(char* Name);
int GetReadyPercent();
bool CheckExistConn();
void PrintBadConn(char* str);
char* _engNOCONN="No direct connection established with:";
byte MPL_NatRefTBL[8]={0,1,2,3,4,5,6,7};
void SetStdTBL(){
	for(int i=0;i<8;i++)MPL_NatRefTBL[i]=i;
};
int GetLogRank();
void SETPLAYERDATA(DWORD ID,void* Data,int size,bool);
void SETPLAYERNAME(DPNAME* lpdpName,bool);
extern DPID ServerDPID;
void ClearLPACK();
bool GetPreviewName(char* Name,char* ccc);
void DeepDeletePeer(DWORD ID);
int GetMyProfile();
bool INSIDE2=0;
bool RunEnciclopia(SimpleDialog* SD);
CIMPORT
void ChatProcess();
bool MPL_WaitingGame(bool Host,bool SINGLE){
	if(SINGLE){
		UseGSC_Login=0;
	};
	INSIDE2=1;
	ClearLPACK();
	ServerDPID=0;
	int r0=GetTickCount();
	PPTIME=r0;
	memset(CurrentMaxPing,0xFF,4*8);
	ReceiveAll();
	CurStatus=0;
	PitchTicks=8;
	MaxPingTime=0;
	ClearCTime();
	int NCHATS=0;
	CHATSTRING[0]=0;
	int MAXCHATS=0;
	char** ChatMess=NULL;
	char** ChatSender=NULL;
	PlayerInfo MYPINF;
	memset(&MYPINF,0,sizeof MYPINF);
	INSIDE2=100;
	byte* Preview=new byte[(292*190)+4];
	char Currand[200];
	((word*)Preview)[0]=292;
	((word*)Preview)[1]=190;
	bool PrPresent=false;
	char LastPrName[200]="";
	byte XLAT[256];
	ResFile fx=RReset("2\\0to1.xlt");
	RBlockRead(fx,XLAT,256);
	RClose(fx);

	LoadFog(2);
	LocalGP BTNS("Interface\\Multi_opt");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP DIS("Interface\\an_start_disable");
	LocalGP SCROL("Interface\\_Slider");	
	LocalGP MASKA("Interface\\preview_mask");
	LocalGP NewFlag("Interface\\NewFlag");
	LocalGP INCHAT("Interface\\IButtons");
	LocalGP CCOM("Interface\\CompCombo");
	LocalGP SINGL("Interface\\Random_map");
	LocalGP LONGBOX("Interface\\LongBox");
	LocalGP ISYM3("Interface\\isymb3");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");

	SQPicture Back;
	if(SINGLE){
		Back.LoadPicture("Interface\\Random_Map_Background.bmp");
	}else{
		Back.LoadPicture("Interface\\Multiplayer_Create_Background.bmp");
	};
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"2\\orange.grd");
	RLCFont FontW(FONT.GPID);
	FontW.SetColorTable(4);
	LoadOptionalTable(4,"2\\white.grd");
	INSIDE2=101;
	DialogsSystem MENU(0,0);
	MENU.OkSound=GetSound("START");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MENU.HintFont=&hfnt;
	MENU.HintY=701;
	MENU.HintX=18;
	Picture* GPPB=MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
	TextButton* SHOWREC=MENU.addTextButton(NULL,1010,4,"0018",&YellowFont,&YellowFont,&YellowFont,0);
	GPPicture*  NameBack[8];
	GPPicture*  NationBack[8];
	GPPicture*  ColorBack[8];
	GPPicture*  Flags[8];
	GPPicture*  CD_Back[8];
	GPPicture*  CD_Present[8];
	GPPicture*  ReadyBack[8];
	GPPicture*  AliasBack[8];
	ComboBox*   COMPS[8];
	ComboBox*   KICK[8];
	GPPicture*  BCOMP[8];

	ComboBox*   ADD_OPT;
	ComboBox*   ADD_OPT_VAL;
	bool COMPPREV[8];
	memset(COMPPREV,0,sizeof COMPPREV);

	TextButton* AliasID[8];
	InputBox*   MNAME  [8];
	ComboBox*   MNATION[8];
	TextButton* ReadyFlow[8];
	//char        VersID[8][8];
	TextButton* VersTextShadow[8];
	TextButton* VersText[8];
	//ColoredBar* MCOLOR [8];
	GPPicture*  MREADY[8];
	byte COMCOLOR[8];
	byte COMNATION[8];
	byte COMALLY[8];
	int NComp=0;
	memset(COMCOLOR,0,sizeof COMCOLOR);
	memset(COMNATION,0,sizeof COMNATION);
	memset(COMALLY,0,sizeof COMALLY);
	int HostID=-1;
	char* ADDCOM="Add a Computer";
	//MENU.addInputBox(NULL,0,0,CurrentMap,64,400,25,&FontW,&FontW);
	ChatViewer* CHVIEW=NULL;
	if(!SINGLE)CHVIEW=MENU.addChatViewer(NULL,47,502,4,26,380,&ChatMess,&ChatSender,&NCHATS);
	char CHATMESSAGE[256]="";
	InputBox* CHATBOX=NULL;
	if(!SINGLE){
		CHATBOX=MENU.addInputBox(NULL,126-8,612,CHATMESSAGE,250,320,22,&YellowFont,&WhiteFont);
		CHATBOX->Active=1;
	};
	INSIDE2=102;
	VScrollBar* CHSCR=MENU.addNewGP_VScrollBar(NULL,443,483,125,1,0,SCROL.GPID,0);
	CHSCR->Visible=0;
	BPXView* PREV=MENU.addBPXView(NULL,496,441,292,190,1,1,1,Preview+4,NULL);
	PREV->Visible=false;
	GPPicture* PMASK=MENU.addGPPicture(NULL,496,441,MASKA.GPID,0);
	if(SINGLE){
		VideoButton* ENC=MENU.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
		ENC->UserParam=0;
		ENC->OnUserClick=&RunEnciclopia;
	};
	char* rtxt=GetTextByID("???");
	int RNATID=GlobalAI.NAi;
	for(int i=0;i<8;i++){
		if(SINGLE){
			COMPS[i]=MENU.addGP_ComboBox(NULL,38,161+i*26,SINGL.GPID,24+8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
			KICK[i]=NULL;
		}else{
			COMPS[i]=MENU.addGP_ComboBox(NULL,38,161+i*26,CCOM.GPID,8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
			if(Host){
				KICK[i]=MENU.addGP_ComboBox(NULL,38,161+i*26,CCOM.GPID,8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
				KICK[i]->AddLine("                                                   ");
				KICK[i]->AddLine(GetTextByID("KICK"));
				KICK[i]->Visible=0;
			}else KICK[i]=NULL;
		};
		if(SINGLE)BCOMP[i]=MENU.addGPPicture(NULL,38,161+i*26,SINGL.GPID,90+(i%3));
		else BCOMP[i]=MENU.addGPPicture(NULL,38,161+i*26,CCOM.GPID,24+(i%3));
		BCOMP[i]->Visible=0;
		COMPS[i]->AddLine(GetTextByID("None"));
		COMPS[i]->AddLine(GetTextByID("@RMID_EASY"));
		COMPS[i]->AddLine(GetTextByID("@RMID_NORMAL"));
		COMPS[i]->AddLine(GetTextByID("@RMID_HARD"));
		COMPS[i]->AddLine(GetTextByID("@RMID_VERYHARD"));

		COMPS[i]->Visible=0;
		COMPS[i]->Enabled=0;
		if(!SINGLE){
			NameBack[i]=MENU.addGPPicture(NULL,38,161+i*26,BTNS.GPID,9+(i%3));
			NameBack[i]->Visible=0;
		};
		INSIDE2=103;
		MNAME[i]=MENU.addInputBox(NULL,32+9,160+i*26,PINFO[i].name,20,120,20,&WhiteFont,&YellowFont);
		MNAME[i]->Visible=0;
		if(!SINGLE){
			NationBack[i]=MENU.addGPPicture(NULL,173,161+i*26,BTNS.GPID,i%3);
			NationBack[i]->Visible=0;
		};
		
		if(!SINGLE){
			CD_Back[i]=MENU.addGPPicture(NULL,376,161+i*26,BTNS.GPID,3+(i%3));
			CD_Back[i]->Visible=0;
			CD_Present[i]=MENU.addGPPicture(NULL,365+13,162+i*26,BTNS.GPID,25);
			CD_Present[i]->Visible=0;
			VersTextShadow[i]=MENU.addTextButton(NULL,376+12,161+6+i*26,"        ",&SmallBlackFont,&SmallBlackFont,&SmallBlackFont,1);
			VersTextShadow[i]->Visible=0;
			VersText[i]=MENU.addTextButton(NULL,376+12-1,161+6-2+i*26,"        ",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,1);
			VersText[i]->Visible=0;
			ReadyBack[i]=MENU.addGPPicture(NULL,408,161+i*26,BTNS.GPID,15+(i%3));
			ReadyBack[i]->Visible=0;
			ReadyFlow[i]=MENU.addTextButton(NULL,332+100-3,164+i*26,"100%",&YellowFont,&YellowFont,&YellowFont,1);
			ReadyFlow[i]->Visible=0;
			ReadyFlow[i]->Enabled=0;
			MREADY[i]=MENU.addGPPicture(NULL,413+5,162+i*26,BTNS.GPID,26);
			MREADY[i]->Visible=0;

			AliasBack[i]=MENU.addGPPicture(NULL,332,161+i*26,BTNS.GPID,96+(i%3));
			AliasID[i]=MENU.addTextButton(NULL,332+18,165+i*26,"X",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,1);
			AliasBack[i]->OnMouseOver=&ChangeAlias;
			AliasBack[i]->Visible=0;
			AliasBack[i]->Nation=0;
			AliasID[i]->Visible=0;
			ColorBack[i]=MENU.addGPPicture(NULL,285,161+i*26,BTNS.GPID,6+(i%3));
			ColorBack[i]->Visible=0;
			ColorBack[i]->OnMouseOver=&ColorMouseOver;
			ColorBack[i]->Hint=GetTextByID("MMCHANGECOLOR");
			Flags[i]=MENU.addGPPicture(NULL,295-5+19-14,161-11+12+i*26,NewFlag.GPID,(i*17)%45);
			Flags[i]->Visible=0;
			ColorBack[i]->Child=Flags[i];
		}else{
			AliasBack[i]=MENU.addGPPicture(NULL,359,161+i*26,SINGL.GPID,93+(i%3));
			AliasID[i]=MENU.addTextButton(NULL,358+21,165+i*26,"X",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,1);
			AliasBack[i]->OnMouseOver=&ChangeAlias;
			AliasBack[i]->Visible=0;
			AliasBack[i]->Nation=0;
			AliasID[i]->Visible=0;
			ColorBack[i]=MENU.addGPPicture(NULL,409,161+i*26,SINGL.GPID,93+(i%3));
			ColorBack[i]->Visible=0;
			ColorBack[i]->OnMouseOver=&ColorMouseOver;
			ColorBack[i]->Hint=GetTextByID("MMCHANGECOLOR");
			Flags[i]=MENU.addGPPicture(NULL,418-5+19-14,161-11+12+i*26,NewFlag.GPID,(i*17)%45);
			Flags[i]->Visible=0;
			ColorBack[i]->Child=Flags[i];
		};

		MNAME[i]->Hint=GetTextByID("MOCHANGENAME");
		MNAME[i]->Visible=false;
		MNAME[i]->Enabled=false;
		if(SINGLE)MNATION[i]=MENU.addGP_ComboBox(NULL,203,161+i*26,SINGL.GPID,8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
		else MNATION[i]=MENU.addGP_ComboBox(NULL,173,161+i*26,BTNS.GPID,28+8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
		//VScrollBar* VS3;
		//MNATION[i]->AssignScroll(&MENU,&VS3,SCROL.GPID,0,6);
		MNATION[i]->Hint=GetTextByID("MMCHANGENAT");
		
#ifdef TUTORIAL_DEMOVERSION
		int NG=1;
#else
		int NG=GlobalAI.NAi;
#endif
		for(int j=0;j<NG;j++){
			MNATION[i]->AddLine(GlobalAI.Ai[j].Message);
		};
#ifndef TUTORIAL_DEMOVERSION
		MNATION[i]->AddLine(rtxt);
#endif
		MNATION[i]->FontDx-=2;

		//MNATION[i]->OneDx-=2;
		//MCOLOR[i]=MENU.addColoredBar(32+318,160+i*25,32,20,0xF7);
		//MCOLOR[i]->Hint=GetTextByID("MMCHANGECOLOR");
		//MCOLOR[i]->OnMouseOver=&ColorMouseOver;
	};
	int cc1=0;
	byte mss1=1;
	byte MSS1=0;
	bool GMREADY=true;
	INSIDE2=104;
	//---------------Page 1--------------
	VScrollBar* VSB=MENU.addNewGP_VScrollBar(NULL,778,152,221,1,0,SCROL.GPID,0);
	ListBox* LBMaps=MENU.addGP_ListBox(NULL,494,161,8,BTNS.GPID,18,26,&WhiteFont,&YellowFont,VSB);
	//---------------Page 2--------------
	int y=161;
	int y0=y;
	int x=506;
	int x0=x+128+20;
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
	ComboBox* CMGRP1[8];
	GPPicture* RMS=MENU.addGPPicture(NULL,495,149,BTNS.GPID,21);
	CMGRP1[0]=MENU.addGP_ComboBox(NULL,633,161,BTNS.GPID,60,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[0]->CurLine=RMP.STY_DEF;
	int RSTYID=RMP.NSTY;
	for(int p=0;p<RMP.NSTY;p++){
		CMGRP1[0]->AddLine(RMP.STY[p].Name);
	};
	CMGRP1[0]->AddLine(rtxt);
	CMGRP1[0]->Hint=GetTextByID("SOMAPSTYLE");
	y+=25;
	int RRELID=RMP.NRelief;
	CMGRP1[1]=MENU.addGP_ComboBox(NULL,633,161+26,BTNS.GPID,68,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[1]->CurLine=RMP.Relief_DEF;
	for(p=0;p<RMP.NRelief;p++){
		CMGRP1[1]->AddLine(RMP.Relief[p]);
	};
	CMGRP1[1]->AddLine(rtxt);
	CMGRP1[1]->Hint=GetTextByID("SOMOUNT");
	y+=25;
	int RRESID=RMP.NRES;
	CMGRP1[2]=MENU.addGP_ComboBox(NULL,633,161+26*2,BTNS.GPID,76,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[2]->CurLine=RMP.RES_DEF;
	for(p=0;p<RMP.NRES;p++){
		CMGRP1[2]->AddLine(RMP.RES[p].Name);
	};
	CMGRP1[2]->AddLine(rtxt);
	CMGRP1[2]->Hint=GetTextByID("SORESTOT");
	y+=25;
	CMGRP1[3]=MENU.addGP_ComboBox(NULL,633,161+26*3,BTNS.GPID,60,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[3]->CurLine=RMP.MINES_DEF;
	int RMINEID=RMP.NMINES;
	for(p=0;p<RMP.NMINES;p++){
		CMGRP1[3]->AddLine(RMP.MINES[p].Name);
	};
	CMGRP1[3]->AddLine(rtxt);
	CMGRP1[3]->Hint=GetTextByID("SORESONMAP");

	CMGRP1[4]=MENU.addGP_ComboBox(NULL,633,161+26*4,BTNS.GPID,60,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[4]->AddLine(GetTextByID("MS_NORMAL"));
	CMGRP1[4]->AddLine(GetTextByID("MS_LARGE"));
	CMGRP1[4]->AddLine(GetTextByID("MS_HUGE"));
	CMGRP1[4]->CurLine=0;

	ADD_OPT=MENU.addGP_ComboBoxDLX(NULL,633-65-64,161+26*6,100+100+64,LONGBOX.GPID,0,0,0,&WhiteFont,&YellowFont,NULL);
	ADD_OPT->AddLine(GetTextByID("GMTP_TP1"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP2"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP3"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP4"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP5"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP6"));
	ADD_OPT->AddLine(GetTextByID("GMTP_TP7"));

	ADD_OPT_VAL=MENU.addGP_ComboBoxDLX(NULL,633-65-64+26,161+26*7,100+100+64-26,LONGBOX.GPID,0,0,0,&WhiteFont,&YellowFont,NULL);
	GPPicture* AOPPIC=MENU.addGPPicture(NULL,633-65-64,161+26*7,ISYM3.GPID,2);
	TextButton* AOPTB=MENU.addTextButton(NULL,633-65-64+2,161+26*5+3,GetTextByID("ADDMPOPT"),&WhiteFont,&WhiteFont,&WhiteFont,0);
	int PrevCOMBO=-1;

	GPPicture* Exam=MENU.addGPPicture(NULL,495,413,BTNS.GPID,95);
	//---------------Page 3--------------
	VScrollBar* VSS=MENU.addNewGP_VScrollBar(NULL,778,152,221,1,0,SCROL.GPID,0);
	ListBox* LBSav=MENU.addGP_ListBox(NULL,494,161,8,BTNS.GPID,18,26,&WhiteFont,&YellowFont,VSS);
	//-----------------------------------
	GP_PageControl* GPP=MENU.addPageControl(NULL,495,128,BTNS.GPID,22);
	GPP->Hint=GetTextByID("MOPAGES");

	GPP->AddPage(495,128,495+88,128+22,22);
	GPP->AddPage(495+88,128,495+197,128+22,23);
	GPP->AddPage(495+197,128,495+292,128+22,24);
	GPP->CurPage=1;
	ComboBox* VICT=MENU.addGP_ComboBox(NULL,173,418,BTNS.GPID,52,9,0,&WhiteFont,&YellowFont,NULL);
	INSIDE2=105;
	for(i=0;i<=9;i++){
		char ccx[32];
		sprintf(ccx,"VICOND%d",i);
		char* cc2=GetTextByID(ccx);
		if(cc2!=ccx){
			VICT->AddLine(cc2);
		}else goto ffe1;
	};
	VICT->CurLine=0;
	VICT->Visible=0;
	VICT->Enabled=0;
	INSIDE2=106;
ffe1:;
	ComboBox* TIME=MENU.addGP_ComboBox(NULL,358,418,BTNS.GPID,84,9,0,&WhiteFont,&YellowFont,NULL);
	for(i=0;i<=9;i++){
		char ccx[32];
		sprintf(ccx,"TIME%d",i);
		char* cc2=GetTextByID(ccx);
		if(cc2!=ccx){
			TIME->AddLine(cc2);
		}else goto ffe2;
	};
ffe2:;
	if(!Host){
		for(int j=0;j<5;j++)CMGRP1[j]->Enabled=false;
		GPP->Enabled=false;
	};
	GPPicture* DISBL=MENU.addGPPicture(NULL,862,568,DIS.GPID,0);
	VideoButton* OkBtn;
	if(Host){
		OkBtn=MENU.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
		if(SINGLE)OkBtn->Hint=GetTextByID("SOSTART");
		else OkBtn->Hint=GetTextByID("MOSTART");
	}else{
		OkBtn=MENU.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
		OkBtn->Hint=GetTextByID("MOREADY");
	};
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	VideoButton* CancelBtn=MENU.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	if(SINGLE)CancelBtn->Hint=GetTextByID("SOCANCEL");
	else CancelBtn->Hint=GetTextByID("MOCANCEL");
	if(TPEN.Connected||UseGSC_Login){
		GP_Button* ENC=MENU.addGP_Button(NULL,862,468,INCHAT.GPID,9,8);
		ENC->UserParam=99;
		ENC->OnUserClick=&MMItemChoose;
		ENC->Hint=GetTextByID("BACKINCHAT");
	};
	ItemChoose=-1;
	memset(PINFO,0,sizeof PINFO);
	INSIDE2=107;
	for(i=0;i<8;i++)PINFO[i].Version=dwVersion;
	if(SINGLE){
		NPlayers=1;
		memset(&PINFO[0],0,sizeof PINFO[0]);
		PINFO[0].PlayerID=0x12345678;
		MyDPID=0x12345678;
		PINFO[0].ColorID=0;
		strcpy(PINFO[0].name,PlName);

	}else PIEnumeratePlayers(PINFO,false);
	if(NPlayers>7)NPlayers=7;
	
	byte CUSED=0;
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID!=MyDPID){
			CUSED|=(1<<PINFO[i].ColorID);
		};
	};
	cc1=0;
	mss1=1;
	while(CUSED&mss1){
		cc1++;
		mss1<<=1;
	};
	GameInProgress=0;
	if(!SINGLE)PIEnumeratePlayers(PINFO,false);
	if(NPlayers>7)NPlayers=7;
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID==MyDPID){
			PINFO[i].ColorID=cc1;
			ColorBack[i]->Nation=cc1;
			if(Host)PINFO[i].Ready=1;else PINFO[i].Ready=0;
			PINFO[i].Host=Host;
			PINFO[i].CD=1;
			PINFO[i].Version=dwVersion;
			PINFO[i].Rank=GetLogRank();
			PINFO[i].ProfileID=GetMyProfile();
		}else{
			memset(PINFO+i,0,sizeof PlayerInfo);
		};
	};
	if(Host){
		DLL1(SFLB_CreateGamesList,LBSav);
		CreateMapsList(LBMaps);
	};
	INSIDE2=108;
	PlayerMenuMode=1;
	GameInProgress=0;
	tmtmt=0;
	REALTIME=0;
	GLOBALTIME=0;
	PGLOBALTIME=0;
	int pp=1;
	GFILE* f=Gopen("multi.opt","r");
	if(f){
		int v=0;
		Gscanf(f,"%d",&v);
		if(v==1234){	
			for(int i=0;i<5;i++){
				v=0;
				Gscanf(f,"%d",&v);
				CMGRP1[i]->CurLine=v;
			};
			v=0;
			Gscanf(f,"%d",&v);
			VICT->CurLine=v;
			Gscanf(f,"%d",&v);
			TIME->CurLine=v;
		};
		Gclose(f);

	};
	KeyPressed=0;
	PSUMM.ClearPingInfo();
	PBACK.Clear();
	ReceiveAll();
	bool P1E;
	bool P2E;
	bool P3E;
	int DYL;
	//int p;
	char* PNAME="";
	int NCLINES=0;
	char oldname[64]="";
	bool MyOldVers=0;
	bool PresOldVers=0;
	int PREVSD=GetTickCount()-3000;
	word MaxVers=0;
	int CURSUMM=0;
	int NOMREADY=-1;
	char* OLDV=GetTextByID("OLDVER");
	char* NOCONN=GetTextByID("$NOCONN");
	if(NOCONN[0]=='$')NOCONN=_engNOCONN;
	int FInTime=GetTickCount();
	char* COMPTXT="Computer";
	char* DIFSAV=GetTextByID("DIFSAV");
	//char* DIFMAP=GetTextByID("DIFMAP");
	bool PrevPress=0;
	//TPEN.HostMessage[0]=0;
	if(SINGLE){
		VICT->CurLine=0;
		VICT->Visible=0;
	};
	int CUROPTVAL[8]={0,0,0,0,0,0,0,0};
	GFILE* F=Gopen("MuliExOpt.dat","r");
	if(F){
		Gscanf(F,"%d%d%d%d%d%d%d",CUROPTVAL,CUROPTVAL+1,CUROPTVAL+2,CUROPTVAL+3,CUROPTVAL+4,CUROPTVAL+5,CUROPTVAL+6,CUROPTVAL+7);
		Gclose(F);
	};
	int MAXOPTVAL[8]={10,3,3,10,3,4,7,9};
	int NOPTV=7;
	int PREVCUROPT=-1;
	int PREVCNAME=GetTickCount();
	/*
	if(Single){
		CUROPTVAL[0]=0;
		CUROPTVAL[4]=0;
		MAXOPTVAL[0]=0;
		MAXOPTVAL[4]=0;
	};
	*/
	INSIDE2=109;
	LARGE_INTEGER V1;
	QueryPerformanceCounter(&V1);
	LARGE_INTEGER V2;
	QueryPerformanceFrequency(&V2);
	DWORD GMGUID=V1.LowPart+V2.LowPart;
	if(SINGLE){
		FILE* F1=fopen("comp.opt","r");
		if(F1){
			for(int i=0;i<6;i++){
				int h=0;
				int z=fscanf(F1,"%d",&h);
				if(z==1){
					if(h>4)h=4;
					if(h<0)h=0;
					COMPS[i+1]->CurLine=h;
				};
			};
			fclose(F1);
		}else{
			COMPS[1]->CurLine=1;
		};
	};
	char* ONLY=GetTextByID("ONLYOU");
	int NCS0=0;
	do{
		if(UseGSC_Login){
			ChatProcess();
			if(CheckPersonality(CHATMESSAGE)){
				CHATBOX->CursPos=strlen(CHATMESSAGE);
			};
		};
		INSIDE2=78;
		if(Host)ServerDPID=MyDPID;

		if(SINGLE){
			ADD_OPT->Visible=1;
			ADD_OPT->Enabled=1;
			ADD_OPT_VAL->Visible=1;
			AOPPIC->Visible=1;
			AOPTB->Visible=1;
			ADD_OPT_VAL->Enabled=1;
#ifdef INETTESTVERSION
			for(int t=0;t<8;t++)CUROPTVAL[t]=0;
			ADD_OPT_VAL->CurLine=0;
			CMGRP1[0]->CurLine=0;
			CMGRP1[4]->CurLine=0;
			GPP->CurPage=1;
#endif
		}else{
			ADD_OPT->Visible=1;
			ADD_OPT->Enabled=1;
			ADD_OPT_VAL->Visible=Host;
			AOPPIC->Visible=Host;
			AOPTB->Visible=Host;
			ADD_OPT_VAL->Enabled=Host;
		};
		if(PrevCOMBO!=ADD_OPT->CurLine||CUROPTVAL[ADD_OPT->CurLine]!=ADD_OPT_VAL->CurLine||!Host){
			//PrevCOMBO=ADD_OPT->CurLine;
			int aocl=ADD_OPT->CurLine;
			int aovcl=ADD_OPT_VAL->CurLine;
			if(PrevCOMBO==aocl&&Host){
				CUROPTVAL[aocl]=aovcl;
			};
			ADD_OPT->Clear();
			for(int i=0;i<NOPTV;i++){
				char ccc[100];
				sprintf(ccc,"GMTP_TP%d",i+1);
				char cc1[128];
				char cc2[256];
				sprintf(cc1,"@GMTP_TP%d_0%d",i+1,CUROPTVAL[i]);
				sprintf(cc2,"%s: %s",GetTextByID(ccc),GetTextByID(cc1));
				LimitString(cc2,&YellowFont,230);
				ADD_OPT->AddLine(cc2);
			};
			ADD_OPT->CurLine=aocl;
			int n=MAXOPTVAL[aocl];
			ADD_OPT_VAL->Clear();
			for(i=0;i<10;i++){
				char ccc[128];
				sprintf(ccc,"@GMTP_TP%d_0%d",aocl+1,i);
				char* text=GetTextByID(ccc);
				if(text[0]!='@')ADD_OPT_VAL->AddLine(text);
			};
			if(PrevCOMBO==aocl){
				ADD_OPT_VAL->CurLine=aovcl;
			}else{ 
				ADD_OPT_VAL->CurLine=CUROPTVAL[aocl];
			};
			PrevCOMBO=aocl;
		};
		INSIDE2=79;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID==MyDPID){
				if(Host)PINFO[i].Ready=1;
				PINFO[i].Host=Host;
				PINFO[i].CD=1;
				PINFO[i].Version=dwVersion;
				PINFO[i].Rank=GetLogRank();
				PINFO[i].ProfileID=GetMyProfile();
				if(Host)PINFO[i].Game_GUID=GMGUID;
			};
		};
		int CLY=19;
		int NCL=4;
		bool AddChat=0;
		ProcessMessages();
		if(GameInProgress)goto FinCLC;
		INSIDE2=80;
		if(!SINGLE){
			if(KeyPressed&&LastKey==13){
				if(CHATBOX->Active&&CHATMESSAGE[0]){
					ControlLingvo(CHATMESSAGE);
					if(UseGSC_Login&&strstr(CHATMESSAGE,"-->")){
						CheckForPersonalChat(CHATMESSAGE);
					}else SendChat(CHATMESSAGE,0);
					AddChatString(
						GetPlNameByID(MyDPID),
						CHATMESSAGE,375,
							&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
					AddChat=1;
					CHATMESSAGE[0]=0;
				};
				KeyPressed=0;
				LastKey=0;
			}else
			if(TPEN.GlobalChat.NCStr>NCS0){
				for(int j=NCS0;j<TPEN.GlobalChat.NCStr;j++){
					if(strstr(TPEN.GlobalChat.CStr[j].PlName,ONLY)){
						AddChatString(
							TPEN.GlobalChat.CStr[j].PlName,
							TPEN.GlobalChat.CStr[j].Message,375,
								&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
						AddChat=1;
					};
				};
				NCS0=TPEN.GlobalChat.NCStr;
			};
			if(CHATSTRING[0]){
				if(CHATSTRING[0]=='@'&&CHATSTRING[1]=='@'&&CHATSTRING[2]=='@'&&CHATSTRING[3]==127){
					DWORD ID;
					char ccx[64];
					int z=sscanf(CHATSTRING,"%s%d",ccx,&ID);
					if(z==2&&ID==MyDPID){ItemChoose=mcmCancel;
						CHATSTRING[0]=0;
						WaitWithMessage(GetTextByID("YOUWKICK"));
					};
				}else{
					AddChatString(
							GetPlNameByID(CHATDPID),
							CHATSTRING,375,
							&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
					CHATSTRING[0]=0;
					AddChat=1;
				};
			};
				
			SendPings();
			if(NCHATS>NCL){
				CHSCR->SMaxPos=NCHATS-NCL;
				if(AddChat)CHSCR->SPos=CHSCR->SMaxPos;
				CHSCR->Visible=1;
				CHVIEW->ChatDY=CHSCR->SPos;
			}else{
				CHSCR->Visible=0;
				CHSCR->SPos=0;
				CHVIEW->ChatDY=0;
			};
		};
		INSIDE2=81;
		DYL=CHSCR->SPos;	
		P1E=GPP->CurPage==0;
		P2E=GPP->CurPage==1;
		P3E=GPP->CurPage==2;
		Exam->Visible=P2E;
		VSB->Visible=P1E;
		LBMaps->Visible=P1E;
		for(p=0;p<5;p++){
			CMGRP1[p]->Visible=P2E;
			CMGRP1[p]->Enabled=P2E&&Host;
		};
		VSS->Visible=P3E;
		LBSav->Visible=P3E;
		RMS->Visible=P2E;

		ADD_OPT->Visible=P2E;
		ADD_OPT->Enabled=P2E;
		ADD_OPT_VAL->Visible=P2E&&Host;
		ADD_OPT_VAL->Enabled=P2E&&Host;
		AOPPIC->Visible=P2E&&Host;
		AOPTB->Visible=P2E&&Host;
		
		//tmm1=GetRealTime();
		StdKeys();
		INSIDE2=81;
		if(ItemChoose==mcmOk&&!OkBtn->Enabled)ItemChoose=-1;
		//tmm1=GetRealTime()-tmm1;
		//tmm2=GetRealTime();
		AnalyseMessages();
		if(GameInProgress)goto FinCLC;
		//tmm2=GetRealTime()-tmm2;
		if(MyOldVers)GPPB->Hint=OLDV;
		else GPPB->Hint=NULL;
		MENU.MarkToDraw();
		MENU.ProcessDialogs();
		if(GameInProgress)goto FinCLC;
		//tmm3=GetRealTime();
		char ccc[128];
		for(p=NPlayers;p<8;p++)CurrentMaxPing[p]=-1;
		INSIDE2=12;
		INSIDE2=110;
		if(PSUMM.NPL&&PSUMM.PSET[0].NPings){
			int png=GetMaxRealPing();
			
			//png=GetAveragePing();
			//MaxPingTime=png;
			if(GetRealTime()-PPTIME>1000){
				DWORD lpp[3];
				lpp[0]='PNTF';
				lpp[1]=png;
				lpp[2]=lpp[0]+lpp[1];
				SendToAllPlayers(12,lpp);
				PPTIME=GetRealTime();
				for(p=0;p<NPlayers;p++)if(PINFO[p].PlayerID==MyDPID)CurrentMaxPing[p]=png;
			};
			for(p=0;p<NPlayers;p++)if(CurrentMaxPing[p]>png)png=CurrentMaxPing[p];
			MaxPingTime=png;
			if(png<MinPing0)MaxPingTime=0;
			if(png>=MinPing0&&png<300)MaxPingTime=300;
			if(MaxPingTime)MaxPingTime+=500;
			char cc2[300];
			CreateDiffStr(cc2);
			sprintf(ccc,"max ping: %d  (%s)",png,cc2);
			//ShowString(10,768-24,ccc,&SmallYellowFont);
			strcpy(MENU.DefaultHint,ccc);
		}else{
			CreateDiffStr(MENU.DefaultHint);
		};
		/*
		if(NPings){
			char cc2[200];
			sprintf(ccc,"Npings: %d",NPings);
			ShowString(10,768-48,ccc,&SmallYellowFont);

		};
		*/
		INSIDE2=89;
		SHOWREC->Visible=RecordMode;
		MENU.RefreshView();
		if(GameInProgress)goto FinCLC;
		for(i=NPlayers;i<NPlayers+NComp;i++){
			COMALLY[i-NPlayers]=AliasBack[i]->Nation;
			COMNATION[i-NPlayers]=MNATION[i]->CurLine;
		};
		//tmm3=GetRealTime()-tmm3;
		//sprintf(STRI,"%d %d %d %d",COUN,tmm1,tmm2,tmm3);
		if(VICT->CurLine){
			TIME->Visible=1;
			TIME->Enabled=1;
		}else{
			TIME->Visible=0;
			TIME->Enabled=0;
		};
		TIME->Enabled=TIME->Visible;
		NOMREADY=-1;
		if(!SINGLE)for(i=0;i<8;i++)ReadyFlow[i]->Visible=0;
		INSIDE2=10;
		if(Host){
			int HostID=-1;
			byte CMask=0;
			for(int i=0;i<NPlayers;i++){
				if(PINFO[i].Host)HostID=i;
			};
			VICT->Enabled=!SINGLE;
			TIME->Enabled=TIME->Visible;
			for(int q=0;q<NPlayers;q++){
				CMask|=1<<PINFO[q].ColorID;
			};
			int NN=0;
			for(q=NPlayers;q<7;q++)if(PINFO[HostID].COMPINFO[q]){
				word W=PINFO[HostID].COMPINFO[q];
				int Color=W&15;
				CMask|=1<<Color;
			};
			for(q=0;q<8;q++)if(CMask&(1<<q))NN++;
			/*
			if(NN>4){
				CMGRP1[0]->Enabled=0;
				CMGRP1[0]->CurLine=0;
			};
			*/
			if(HostID!=-1){
				int PPP;
				if(!SINGLE){
					if((PPP=GetReadyPercent())<100){
						sprintf(ReadyFlow[HostID]->Message,"%d%%",PPP);
						ReadyFlow[HostID]->Visible=1;
						MREADY[HostID]->Visible=0;
						MREADY[HostID]->Enabled=0;
						NOMREADY=HostID;
					}else{
						ReadyFlow[HostID]->Visible=0;
						MREADY[HostID]->Visible=1;
						MREADY[HostID]->Enabled=1;
						NOMREADY=-1;;
					};
				};
				PINFO[HostID].MapName[0]=0;
				if(GPP->CurPage==0){
					if(LBMaps->CurItem>=0&&LBMaps->NItems){
						strcpy(PINFO[HostID].MapName,LBMaps->GetItem(LBMaps->CurItem)->Message);
					};
					strcpy(CurrentMap,PINFO[HostID].MapName);
				}else
				if(GPP->CurPage==1){
					PINFO[HostID].MapStyle=CMGRP1[0]->CurLine;
					PINFO[HostID].HillType=CMGRP1[1]->CurLine;
					PINFO[HostID].StartRes=CMGRP1[2]->CurLine;
					PINFO[HostID].ResOnMap=CMGRP1[3]->CurLine;
					PINFO[HostID].VictCond=VICT->CurLine;
					PINFO[HostID].GameTime=TIME->CurLine;
					for(int i=0;i<7;i++)
						PINFO[HostID].UserParam[i]=CUROPTVAL[i];
					char Nats[9];
					char Nats1[9];
					strcpy(Nats,"00000000");
					strcpy(Nats1,"00000000");
					char* NTCHAR="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
					int NP=0;
					for(int q=0;q<NPlayers;q++){
						Nats[7-PINFO[q].ColorID]=NTCHAR[MNATION[q]->CurLine+1];
						//Nats1[7-PINFO[q].ColorID]='1';
					};
					for(q=NPlayers;q<7;q++)if(PINFO[HostID].COMPINFO[q]){
						word W=PINFO[HostID].COMPINFO[q];
						int Nat=W>>11;
						int Color=W&15;
						int Diff=(W>>8)&7;
						int Team=(W>>4)&15;
						Nats[7-Color]=NTCHAR[Nat+1];
					};
					for(int u=0;u<8;u++)if(Nats[u]!='0')NP++;
					char ccc[128];
					int r=r0&65535;
					//sscanf(ccc,"%d",&r);
					int s=CMGRP1[0]->CurLine+((NP-2)<<4)+(CMGRP1[1]->CurLine<<8)
						+(CMGRP1[2]->CurLine<<12)+(CMGRP1[3]->CurLine<<16);
					//sprintf(CurrentMap,"RND %X %X %s.m3d",r,s,Nats);
					int op=CUROPTVAL[0]+CUROPTVAL[1]*10+CUROPTVAL[2]*100+
						CUROPTVAL[3]*1000+CUROPTVAL[4]*10000+CUROPTVAL[5]*100000+CUROPTVAL[6]*1000000;
					sprintf(PINFO[HostID].MapName,"RN%d %X %X %s %d.m3d",CMGRP1[4]->CurLine,r,s,Nats,op);
					int sty=CMGRP1[0]->CurLine==RSTYID?rand()%RSTYID:CMGRP1[0]->CurLine;
					int rel=CMGRP1[1]->CurLine==RRELID?rand()%RRELID:CMGRP1[1]->CurLine;
					int res=CMGRP1[2]->CurLine==RRESID?rand()%RRESID:CMGRP1[2]->CurLine;
					int min=CMGRP1[3]->CurLine==RMINEID?rand()%RMINEID:CMGRP1[3]->CurLine;
					strcpy(Nats,"00000000");
					for(q=0;q<NPlayers;q++){
						Nats[7-PINFO[q].ColorID]=MNATION[q]->CurLine==RNATID?
							NTCHAR[1+(rand()%RNATID)]:NTCHAR[MNATION[q]->CurLine+1];
					};
					for(q=NPlayers;q<7;q++)if(PINFO[HostID].COMPINFO[q]){
						word W=PINFO[HostID].COMPINFO[q];
						int Nat=W>>11;
						int Color=W&15;
						int Diff=(W>>8)&7;
						int Team=(W>>4)&15;
						Nats[7-Color]=MNATION[q]->CurLine==RNATID?
							NTCHAR[1+(rand()%RNATID)]:NTCHAR[MNATION[q]->CurLine+1];
						//NP++;
					};
					if(NP<2)NP=2;
					s=sty+((NP-2)<<4)+(rel<<8)
						+(res<<12)+(min<<16);
					sprintf(CurrentMap,"RN%d %X %X %s %d.m3d",CMGRP1[4]->CurLine,r,s,Nats,op);
				}else{
					if(LBSav->CurItem>=0&&LBSav->NItems){
						strcpy(PINFO[HostID].MapName,LBSav->GetItem(LBSav->CurItem)->Message);
					};
					strcpy(CurrentMap,PINFO[HostID].MapName);
				};
			};
		}else{
			VICT->Enabled=0;
			TIME->Enabled=0;
			for(int i=0;i<NPlayers;i++){
				if(PINFO[i].Host){
					VICT->CurLine=PINFO[i].VictCond;
					TIME->CurLine=PINFO[i].GameTime;
					PINFO[0].VictCond=PINFO[i].VictCond;
					PINFO[0].GameTime=PINFO[i].GameTime;
					char* MPN=PINFO[i].MapName;
					if(MPN[0]=='R'&&MPN[1]=='N'&&MPN[3]==' '){
						int sz=MPN[2]-'0';
						if(sz>2)sz=2;
						if(sz<0)sz=0;
						CMGRP1[4]->CurLine=sz;
					};
				};
				if(!SINGLE)ReadyFlow[i]->Visible=0;
			};
			for(i=0;i<4;i++)CMGRP1[i]->Enabled=0;
			VICT->Enabled=0;
			TIME->Enabled=0;
			NOMREADY=-1;
		};
		if(GPP->CurPage==0){
			if(strcmp(CurrentMap,LastPrName)){
				strcpy(LastPrName,CurrentMap);
				if(GetPreview(CurrentMap,Preview+4)){
					PREV->Visible=1;
					Decode(Preview+4,XLAT,292*190);
				}else{
					PREV->Visible=false;
				};
			};
		}else
		if(GPP->CurPage==1){
			char Nats[9];
			char Nats1[9];
			strcpy(Nats,"00000000");
			strcpy(Nats1,"00000000");
			char* NTCHAR="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			for(int q=0;q<NPlayers;q++){
				Nats[7-PINFO[q].ColorID]=NTCHAR[MNATION[q]->CurLine+1];
				//Nats1[7-PINFO[q].ColorID]='1';
			};
			for(q=NPlayers;q<7;q++)if(PINFO[HostID].COMPINFO[q]){
				word W=PINFO[HostID].COMPINFO[q];
				int Nat=W>>11;
				int Color=W&15;
				int Diff=(W>>8)&7;
				int Team=(W>>4)&15;
				Nats[7-Color]=NTCHAR[Nat+1];
			};
			char ccc[128];
			int r=(r0)&65535;
			//sprintf(ccc,"%d",&r);
			//int NP=NPlayers;
			//for(q=NPlayers;q<7;q++)if(PINFO[HostID].COMPINFO[q]){
			//	NP++;
			//};
			int NP=0;
			for(int u=0;u<8;u++)if(Nats[u]!='0')NP++;
			if(NP<2)NP=2;
			for(int j=0;j<NP;j++)Nats1[7-j]='1';
			sprintf(Currand,"Preview\\%d%d%d%d",CMGRP1[1]->CurLine==5,CMGRP1[0]->CurLine,NP,CUROPTVAL[3]!=0);
			if(strcmp(Currand,LastPrName)){
				strcpy(LastPrName,Currand);
				if(GetPreview(Currand,Preview+4)){
					PREV->Visible=1;
					Decode(Preview+4,XLAT,292*190);
				}else{
					PREV->Visible=false;
				};
			};
		}else{
			PREV->Visible=0;
			if(strcmp(CurrentMap,LastPrName)){
				strcpy(LastPrName,CurrentMap);
				int S=GetMapSUMM(CurrentMap);
				for(int v=0;v<NPlayers;v++)if(PINFO[v].PlayerID==MyDPID)PINFO[v].CHKSUMM=S;
			};
		};
		MaxVers=0;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].Version>MaxVers)MaxVers=PINFO[i].Version;
		};
		INSIDE2=9;
		for(i=0;i<8;i++){
			if(i<NPlayers){
				if(PINFO[i].PlayerID==MyDPID){
					PINFO[i].NationID=MNATION[i]->CurLine;
					PINFO[i].ColorID=ColorBack[i]->Nation;
					PINFO[i].GroupID=AliasBack[i]->Nation;
					if(Host)PINFO[i].Page=GPP->CurPage;
					bool ch=memcmp(&MYPINF,PINFO+i,sizeof MYPINF)!=0;
					if(ch||GetTickCount()-PREVSD>5000){//3000
						if(!SINGLE){
							SETPLAYERDATA(MyDPID,(void*)&PINFO[i].NationID,sizeof(PlayerInfo)-36,ch);
						};
						memcpy(&MYPINF,PINFO+i,sizeof MYPINF);
						PREVSD=GetTickCount();
					};
					if(ch&&Host&&!SINGLE)PSUMM.ClearPingInfo();
					DPNAME dpName;
					ZeroMemory(&dpName, sizeof(DPNAME));
					dpName.dwSize = sizeof(DPNAME);
					dpName.lpszShortNameA = MNAME[i]->Str;
					dpName.lpszLongNameA = NULL;
					if(strcmp(dpName.lpszShortNameA,oldname)||GetTickCount()-PREVCNAME>3000){
						if(!SINGLE)SETPLAYERNAME(&dpName,strcmp(dpName.lpszShortNameA,oldname));
						strcpy(oldname,dpName.lpszShortNameA);
						PREVCNAME=GetTickCount();
					};
					MNATION[i]->Enabled=P2E;
					MNATION[i]->Visible=P2E;
					AliasBack[i]->Visible=1;
					AliasBack[i]->Enabled=1;
					AliasID[i]->Visible=1;
					AliasID[i]->Enabled=1;
					CurrentNation=MNATION[i]->CurLine;
					//MGRP[i]->Enabled=true;
					if(!SINGLE)NameBack[i]->Visible=1;
					MNAME[i]->Visible=1;
					MNAME[i]->Enabled=0;//1;
					if(strstr(TPEN.HostMessage,"0017")&&!SINGLE){
						MNAME[i]->Enabled=0;
					};
					if(KICK[i]){
						KICK[i]->Visible=0;
						KICK[i]->Enabled=0;
					};
					if(!SINGLE){
						NationBack[i]->Visible=0;
						NationBack[i]->Enabled=0;
						CD_Back[i]->Visible=1;
					};
					ColorBack[i]->Visible=1;
					ColorBack[i]->Enabled=1;
					if(!SINGLE)ReadyBack[i]->Visible=1;
					MyOldVers=PINFO[i].Version!=MaxVers;
				}else{
					if(!SINGLE){
						NationBack[i]->Visible=1;
						NationBack[i]->Enabled=1;
						CD_Back[i]->Visible=0;
					};
					AliasBack[i]->Visible=0;
					AliasBack[i]->Enabled=0;
					if(KICK[i]){
						KICK[i]->Visible=1;
						KICK[i]->Enabled=1;
						strcpy(KICK[i]->Lines[0],MNAME[i]->Str);
						while(GetRLCStrWidth(KICK[i]->Lines[0],&YellowFont)>99){
							KICK[i]->Lines[0][strlen(KICK[i]->Lines[0])-1]=0;
						};
						if(KICK[i]->CurLine==1){
							char cc[32];
							sprintf(cc,"@@@0002KICK %d",PINFO[i].PlayerID);
							SendChat(cc,0);
							KICK[i]->CurLine=0;
							if(DoNewInet){
								//assert(PINFO[i].PlayerID!=1);
								DeepDeletePeer(PINFO[i].PlayerID);
							};
						};
						MNAME[i]->Visible=0;//!!!!!!!!
						MNAME[i]->Enabled=0;
						MNAME[i]->Active=0;
					}else{
						MNAME[i]->Visible=1;//!!!!!!!!
						MNAME[i]->Enabled=0;
						MNAME[i]->Active=0;
					};
					if(!SINGLE)NameBack[i]->Visible=0;
					MNATION[i]->Enabled=0;
					ColorBack[i]->Visible=0;
					ColorBack[i]->Enabled=0;
					if(!SINGLE)ReadyBack[i]->Visible=0;
					//MGRP[i]->Enabled=false;
				};
				if(!SINGLE){
					if(MNAME[i]->Active)NameBack[i]->SpriteID=12+(i%3);
					else NameBack[i]->SpriteID=9+(i%3);
				};
				Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
				Flags[i]->Nation=ColorBack[i]->Nation;
				if(AliasBack[i]->Nation){
					AliasID[i]->Message[0]='0'+AliasBack[i]->Nation;
				}else{
					AliasID[i]->Message[0]='X';
				};
				MNATION[i]->Visible=true;
				//MCOLOR[i]->Visible=true;
				if(!SINGLE){
					MREADY[i]->SpriteID=26+(PINFO[i].Ready!=0);
					if(i!=NOMREADY){
						MREADY[i]->Visible=true;
						MREADY[i]->Enabled=true;
					};
				};
				Flags[i]->Visible=1;
				if(!SINGLE)CD_Present[i]->Visible=1;
				//MREADY[i]->Visible=1;
				MNATION[i]->Visible=1;
				AliasID[i]->Visible=1;
				AliasID[i]->Enabled=1;
				int v=PINFO[i].Version;
				if(!SINGLE){
					char VERS[128];
					if(v>255){
						sprintf(VERS,"M%d",v>>8);
					}else{
						sprintf(VERS,"%d.%d%d",v/100,(v/10)%10,v%10);
					};
					strcpy(VersText[i]->Message,VERS);
					strcpy(VersTextShadow[i]->Message,VERS);
				
					if(v!=MaxVers&&(GetTickCount()/300)&1){
						VersText[i]->ActiveFont=&SmallRedFont;
						VersText[i]->PassiveFont=&SmallRedFont;
					}else{
						VersText[i]->ActiveFont=&SmallYellowFont;
						VersText[i]->PassiveFont=&SmallYellowFont;
					};
					VersText[i]->Visible=1;
					VersTextShadow[i]->Visible=1;
				};
				PresOldVers=v!=MaxVers;
				//ReadyBack[i]->Visible=0;
				//MGRP[i]->Visible=true;
			}else{
				if(i<NComp+NPlayers){
					if(!SINGLE){
						NameBack[i]->Visible=0;
						NationBack[i]->Visible=1;
						CD_Back[i]->Visible=1;
						CD_Present[i]->Visible=1;
						ReadyBack[i]->Visible=1;
						VersText[i]->Visible=0;
						VersTextShadow[i]->Visible=0;
						MREADY[i]->Visible=0;
					};
					ColorBack[i]->Visible=1;
					Flags[i]->Visible=1;
					
					MNAME[i]->Visible=1;
					MNAME[i]->Enabled=0;
					if(KICK[i]){
						KICK[i]->Visible=1;
						KICK[i]->Enabled=1;
					};
					MNAME[i]->Str=COMPTXT;
					MNAME[i]->Active=0;
					MNATION[i]->Visible=1;
					MNATION[i]->Enabled=1;
					int pp=i-NPlayers;
					MNATION[i]->CurLine=COMNATION[pp];
					AliasBack[i]->Visible=1;
					AliasBack[i]->Enabled=1;
					AliasID[i]->Visible=1;
					AliasID[i]->Enabled=1;
					if(COMALLY[pp])AliasID[i]->Message[0]='0'+COMALLY[pp];
					else AliasID[i]->Message[0]='X';
					//MGRP[i]->Visible=false;
					Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
					Flags[i]->Nation=ColorBack[i]->Nation;
				}else{
					if(!SINGLE){
						NameBack[i]->Visible=0;
						NationBack[i]->Visible=0;
						CD_Back[i]->Visible=0;
						CD_Present[i]->Visible=0;
						ReadyBack[i]->Visible=0;
						VersText[i]->Visible=0;
						VersTextShadow[i]->Visible=0;
						MREADY[i]->Visible=0;
					};
					ColorBack[i]->Visible=0;
					Flags[i]->Visible=0;
					
					MNAME[i]->Visible=0;
					MNAME[i]->Enabled=0;
					if(KICK[i]){
						KICK[i]->Visible=0;
						KICK[i]->Enabled=0;
					};
					MNAME[i]->Active=0;
					MNATION[i]->Visible=0;
					MNATION[i]->Enabled=0;
					AliasBack[i]->Visible=0;
					AliasBack[i]->Enabled=0;
					AliasID[i]->Visible=0;
					AliasID[i]->Enabled=0;
					//MGRP[i]->Visible=false;
					
				};
			};
		};
		INSIDE2=8;
		PrevPress=realLpressed;
		if(Host){
			//if(KeyPressed){
			//	if(LastKey==107&&NComp+NPlayers<7)NComp++;
			//	if(LastKey==109&&NComp)NComp--;
			//};
		};
		if(!SINGLE){
			if(!PIEnumeratePlayers(PINFO,true)){
				ItemChoose=mcmCancel;
			};
		};
		if(NPlayers>7)NPlayers=7;
		if(!Host){
			int HostID=-1;
			int MyID=-1;
			for(int i=0;i<NPlayers;i++){
				if(PINFO[i].Host)HostID=i;
				if(PINFO[i].PlayerID==MyDPID)MyID=i;
			};
			if(HostID!=-1&&MyID!=-1){
				switch(PINFO[HostID].Page){
				case 1:
					GPP->CurPage=1;
					CMGRP1[0]->CurLine=PINFO[HostID].MapStyle;
					CMGRP1[1]->CurLine=PINFO[HostID].HillType;
					CMGRP1[2]->CurLine=PINFO[HostID].StartRes;
					CMGRP1[3]->CurLine=PINFO[HostID].ResOnMap;
					for(i=0;i<7;i++){
						int v=PINFO[HostID].UserParam[i];
						if(v!=CUROPTVAL[i]){
							CUROPTVAL[i]=v;
							PREVCUROPT=-1;
						};
					};
					break;
				case 2:
					GPP->CurPage=2;
					LBSav->ClearItems();
					LBSav->AddItem(PINFO[HostID].MapName,0);
					break;
				case 0:
					GPP->CurPage=0;
					LBMaps->ClearItems();
					LBMaps->AddItem(PINFO[HostID].MapName,0);
					break;
				};
				strcpy(PINFO[MyID].MapName,PINFO[HostID].MapName);
				PINFO[MyID].MapStyle=PINFO[HostID].MapStyle;
				PINFO[MyID].HillType=PINFO[HostID].HillType;
				PINFO[MyID].StartRes=PINFO[HostID].StartRes;
				PINFO[MyID].ResOnMap=PINFO[HostID].ResOnMap;
				PINFO[MyID].Game_GUID=PINFO[HostID].Game_GUID;
				strcpy(CurrentMap,PINFO[HostID].MapName);
			};
		};
		for(i=0;i<8;i++){
			if(i<NPlayers){
				MNATION[i]->CurLine=PINFO[i].NationID;
				ColorBack[i]->Nation=PINFO[i].ColorID;
				AliasBack[i]->Nation=PINFO[i].GroupID;
			};
		};
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID==MyDPID&&ItemChoose==mcmOk&&!Host){
				PINFO[i].Ready=1;
			};
		};
		HostID=-1;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].Host)HostID=i;
		};
		INSIDE2=7;
		if(HostID!=-1){
			if(Host){
				for(i=0;i<7;i++){
					COMPS[i]->Visible=(i>=NPlayers);
					COMPS[i]->Enabled=COMPS[i]->Visible;
					BCOMP[i]->Visible=0;
					if(COMPS[i]->Visible&&COMPS[i]->CurLine){
						if(!COMPPREV[i]){
							byte msk=0;
							for(int j=0;j<NPlayers;j++)msk|=1<<ColorBack[j]->Nation;
							for(j=NPlayers;j<7;j++){
								if(COMPS[j]->Visible&&COMPS[j]->CurLine){
									msk|=1<<ColorBack[j]->Nation;
								};
							};
							int defc=-1;
							for(j=0;j<7&&defc==-1;j++){
								if(!(msk&(1<<j)))defc=j;
							};
							if(defc==-1)defc=0;
							ColorBack[i]->Nation=defc;
							AliasBack[i]->Nation=7;
						};

						if(!SINGLE){
							NameBack[i]->Visible=0;
							NationBack[i]->Visible=1;
							CD_Back[i]->Visible=0;
							CD_Present[i]->Visible=0;
							ReadyBack[i]->Visible=0;
							MREADY[i]->Visible=0;
							VersText[i]->Visible=0;
							VersTextShadow[i]->Visible=0;
						};
						ColorBack[i]->Visible=1;
						Flags[i]->Visible=1;
						MNAME[i]->Visible=0;
						MNAME[i]->Enabled=0;
						if(KICK[i]){
							KICK[i]->Visible=0;
							KICK[i]->Enabled=0;
						};
						MNAME[i]->Active=0;
						MNATION[i]->Visible=1;
						MNATION[i]->Enabled=1;
						int pp=i-NPlayers;
						AliasBack[i]->Visible=1;
						AliasBack[i]->Enabled=1;
						AliasID[i]->Visible=1;
						AliasID[i]->Enabled=1;
						if(AliasBack[i]->Nation){
							AliasID[i]->Message[0]='0'+AliasBack[i]->Nation;
						}else{
								AliasID[i]->Message[0]='X';
						};
						//MGRP[i]->Visible=false;
						Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
						Flags[i]->Nation=ColorBack[i]->Nation;
						word W=int(Flags[i]->Nation)+
							(int(AliasBack[i]->Nation)<<4)+
							(int(COMPS[i]->CurLine)<<8)+(int(MNATION[i]->CurLine)<<11);
						PINFO[HostID].COMPINFO[i]=W;
					}else PINFO[HostID].COMPINFO[i]=0;
					COMPPREV[i]=COMPS[i]->Visible&&COMPS[i]->CurLine;
				};
			}else{
				for(i=0;i<7;i++){
					if(i>=NPlayers){
						word W=PINFO[HostID].COMPINFO[i];
						if(W){
							COMPS[i]->Visible=1;
							COMPS[i]->CurLine=(W>>8)&7;
							
							if(!SINGLE){
								NameBack[i]->Visible=0;
								NationBack[i]->Visible=1;
								CD_Back[i]->Visible=0;
								CD_Present[i]->Visible=0;
								ReadyBack[i]->Visible=0;
								MREADY[i]->Visible=0;
								VersText[i]->Visible=0;
								VersTextShadow[i]->Visible=0;
							};
							ColorBack[i]->Visible=1;
							Flags[i]->Visible=1;
							MNAME[i]->Visible=0;
							MNAME[i]->Enabled=0;
							if(KICK[i]){
								KICK[i]->Visible=0;
								KICK[i]->Enabled=0;
							};
							MNAME[i]->Active=0;
							MNATION[i]->Visible=1;
							MNATION[i]->Enabled=1;
							MNATION[i]->CurLine=W>>11;
							int pp=i-NPlayers;
							AliasBack[i]->Visible=1;
							AliasBack[i]->Enabled=1;
							AliasID[i]->Visible=1;
							AliasID[i]->Enabled=1;
							AliasBack[i]->Nation=(W&255)>>4;
							if(AliasBack[i]->Nation){
								AliasID[i]->Message[0]='0'+AliasBack[i]->Nation;
							}else{
								AliasID[i]->Message[0]='X';
							};
							//MGRP[i]->Visible=false;
							Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
							ColorBack[i]->Nation=W&15;
							Flags[i]->Nation=ColorBack[i]->Nation;
							BCOMP[i]->Visible=0;//1;
						}else{
							COMPS[i]->Visible=0;
							BCOMP[i]->Visible=0;
						};
						COMPS[i]->Enabled=0;
					}else{
						COMPS[i]->Visible=0;
						COMPS[i]->Enabled=0;
						BCOMP[i]->Visible=0;
					};
				};
			};
		};
		INSIDE2=6;
		GMREADY=true;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID!=MyDPID&&!PINFO[i].Ready)GMREADY=false;
		};
		MSS1=0;
		/*
		for(i=0;i<NPlayers;i++){
			byte MSS2=1<<PINFO[i].ColorID;
			if(MSS1&MSS2)GMREADY=false;
			MSS1|=MSS2;
			if(!PINFO[i].Ready)GMREADY=false;
		};
		*/
		for(i=0;i<7;i++){
			if(COMPS[i]->Visible&&COMPS[i]->CurLine){
				byte MSS2=1<<ColorBack[i]->Nation;
				if(MSS1&MSS2&&Host)GMREADY=false;
				MSS1|=MSS2;
			};
		};
		INSIDE2=5;
		if(Host){
//#ifndef SINGLETESTNETWORK
			if(!SINGLE){
				if(NPlayers<2)GMREADY=false;
				if(!CheckPingsReady())GMREADY=false;
				byte bs=0;
				for(int i=0;i<NPlayers;i++)bs|=1<<AliasBack[i]->Nation;
				if(!(bs&1)){
					bs|=1;
					if(bs==2||bs==4||bs==8||bs==16||bs==32||bs==64||bs==128)GMREADY=false;
				};
				for(i=0;i<NPlayers;i++)if(CurrentMaxPing[i]==-1)GMREADY=0;
				if(PresOldVers)GMREADY=0;
			};

			//teams calculating
			int ntm=0;
			byte ams=0;
			int cur_tm[8];
			memset(cur_tm,0xFF,sizeof cur_tm);
			for(int i=0;i<8;i++)if(AliasID[i]->Visible){
				int tm=AliasBack[i]->Nation;
				int cl=ColorBack[i]->Nation;
				if(cur_tm[cl]!=-1){
					if(tm!=cur_tm[cl]||!cur_tm[cl]){
						GMREADY=0;
					};
				}else cur_tm[cl]=tm;
				int alb=AliasBack[i]->Nation;
				if(!alb)ntm++;
				else{
					if(!(ams&(1<<alb))){
						ntm++;
						ams|=1<<alb;
					};
				};
			};
			if(ntm<2)GMREADY=0;
//#endif
			//MENU.DefaultHint[0]=0;
			if(GPP->CurPage==2){
				int MINS=0;
				for(int i=0;i<NPlayers;i++)
					if(PINFO[i].PlayerID==MyDPID)MINS=PINFO[i].CHKSUMM;
				/*
				for(i=0;i<NPlayers;i++)if(PINFO[i].CHKSUMM!=MINS){
					GMREADY=0;
					strcpy(MENU.DefaultHint,DIFSAV);
				};
				*/
			};
			OkBtn->Enabled=GMREADY;
			OkBtn->Visible=GMREADY;
			if(TPEN.MyRoom&&TPEN.MyRoom->RoomConnected){
				TPEN.CreateMyRoomInfoString(TPEN.HostMessage);
			};
		}else{
			OkBtn->Enabled=!MyOldVers;
			OkBtn->Visible=!MyOldVers;
			if(!CheckExistConn()){
				if(!(GetKeyState(VK_CONTROL)&0x8000)){
					OkBtn->Enabled=0;
					OkBtn->Visible=0;
				};
				if(GetTickCount()-FInTime>2000){
					strcpy(MENU.DefaultHint,NOCONN);
					PrintBadConn(MENU.DefaultHint+strlen(MENU.DefaultHint));
				};
			};
			if(P1E){
				OkBtn->Enabled=PREV->Visible;
				OkBtn->Visible=PREV->Visible;
				if(!PREV->Visible){
					if((GetTickCount()/200)&1){
						LBMaps->AFont=&WhiteFont;
						LBMaps->PFont=&YellowFont;
					}else{
						LBMaps->AFont=&RedFont;
						LBMaps->PFont=&RedFont;
					};
				}else{
					LBMaps->AFont=&WhiteFont;
					LBMaps->PFont=&YellowFont;
				};
			};
		};
		INSIDE2=4;
		//checking readyness
		if(ItemChoose==mcmOk&&!Host)ItemChoose=-1;
		INSIDE2=3;
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
			ReceiveAll();
			//PSUMM.ClearPingInfo();
		};
		if(ItemChoose==99){
			INSIDE2=2;
			ProcessInternetConnection(0);
			NCS0=0;
			INSIDE2=33;
			ItemChoose=-1;
			if(PlayerMenuMode!=1)ItemChoose=mcmSingle;
		};
FinCLC:;
	   if(RejectThisPlayer||CheckPlayerToExit())ItemChoose=mcmCancel;
	   INSIDE2=77;
	}while(ItemChoose==-1&&PlayerMenuMode==1);
	
	if(Host){
		GFILE* F=Gopen("MuliExOpt.dat","wt");
		int r=GetLastError();
		if(F){
			Gprintf(F,"%d %d %d %d %d %d %d",CUROPTVAL[0],CUROPTVAL[1],CUROPTVAL[2],CUROPTVAL[3],CUROPTVAL[4],CUROPTVAL[5],CUROPTVAL[6],CUROPTVAL[7]);
			Gclose(F);
		};
	};
	if(SINGLE){
		FILE* Fx=fopen("comp.opt","wt");
		if(Fx){
			for(int i=0;i<6;i++){
				fprintf(Fx,"%d ",COMPS[i+1]->CurLine);
			};
			fclose(Fx);
		};
	};
	if(Host&&PlayerMenuMode!=-1){
		for(int i=0;i<8;i++)MPL_NatRefTBL[i]=0xFF;
		int NN[8]={0,0,0,0,0,0,0,0};
		for(i=NPlayers;i<7;i++)if(PINFO[HostID].COMPINFO[i]){
			word W=PINFO[HostID].COMPINFO[i];
			int Nat=W>>11;
			int Color=W&15;
			MPL_NatRefTBL[Color]=Color;
			NN[Color]=1;
		};
		for(i=0;i<NPlayers;i++){
			int c=PINFO[i].ColorID;
			if(MPL_NatRefTBL[c]==0xFF){
				MPL_NatRefTBL[c]=c;
			};
		};
		for(i=0;i<NPlayers;i++){
			int c=PINFO[i].ColorID;
			if(NN[c]){
				for(int j=0;j<8;j++)if(MPL_NatRefTBL[j]==0xFF){
					MPL_NatRefTBL[j]=c;
					PINFO[i].ColorID=j;
					j=8;
				};
			}else{
				NN[c]=1;
			}
		};
		for(i=0;i<8;i++)if(MPL_NatRefTBL[i]==0xFF)MPL_NatRefTBL[i]=i;
		if(SINGLE){
			memcpy(NatRefTBL,MPL_NatRefTBL,8);
		};
	};
	if(NCHATS){
		for(int i=0;i<NCHATS;i++){
			free(ChatMess[i]);
			free(ChatSender[i]);
		};
		free(ChatMess);
		free(ChatSender);
	};
	if(PINFO[0].VictCond){
		int t=60;
		char cc3[32];
		sprintf(cc3,"-TIME%d",PINFO[0].GameTime);
		sscanf(GetTextByID(cc3),"%d",&t);
		PINFO[0].GameTime=t*60;
	};
	if(Host){
		f=Gopen("multi.opt","w");
		if(f){
			Gprintf(f,"1234 %d %d %d %d %d %d %d",CMGRP1[0]->CurLine,CMGRP1[1]->CurLine,CMGRP1[2]->CurLine,CMGRP1[3]->CurLine,CMGRP1[4]->CurLine,VICT->CurLine,TIME->CurLine);
			Gclose(f);
		};
	};
	free(Preview);
	if(ItemChoose==mcmCancel){
		CloseMPL();
	};
	INSIDE2=0;
	return (ItemChoose==mcmOk)||PlayerMenuMode!=1;
};
int SetCurrentBattle(int BattleID,
					  SQPicture* Prev,
					  ComboBox** MNATION,
					  TextViewer* BTTXT){
	if(BattleID<0)return 0;
	if(BattleID>=WARS.NBattles)return WARS.NBattles-1;
	Prev->LoadPicture(WARS.Battles[BattleID].MiniMap);
	for(int i=0;i<2;i++){
		int cl=MNATION[i]->CurLine;
		MNATION[i]->Clear();
		MNATION[i]->AddLine(WARS.Battles[BattleID].RedUnits);
		MNATION[i]->AddLine(WARS.Battles[BattleID].BlueUnits);
		MNATION[i]->CurLine=cl;
	};
	ResFile FF1=RReset(WARS.Battles[BattleID].Brief);
	if(FF1!=INVALID_HANDLE_VALUE){
		ResFile FF2=RRewrite("miss.txt");
		if(FF2!=INVALID_HANDLE_VALUE){
			RBlockWrite(FF2,WARS.Battles[BattleID].BigHeader,strlen(WARS.Battles[BattleID].BigHeader));
			char c=0x0D;
			RBlockWrite(FF2,&c,1);
			c=0x0A;
			RBlockWrite(FF2,&c,1);
			c=0x0D;
			RBlockWrite(FF2,&c,1);
			c=0x0A;
			RBlockWrite(FF2,&c,1);
			byte* Data=new byte[RFileSize(FF1)];
			RBlockRead(FF1,Data,RFileSize(FF1));
			RBlockWrite(FF2,Data,RFileSize(FF1));
			RClose(FF2);
		};
		RClose(FF1);
	};
	BTTXT->LoadFile("miss.txt");
	return BattleID;
};
CEXPORT
void AddToGChat(char* Nick,char* Message){
	TPEN.GlobalChat.Add(Nick,Message);
};
CEXPORT
void ClearGChat(){
	TPEN.GlobalChat.Clear();
};
bool MPL_WaitingBattleGame(bool Host,int BattleID){
	ClearLPACK();
	ReceiveAll();
	CurStatus=0;
	PitchTicks=8;
	MaxPingTime=0;
	ClearCTime();
	int NCHATS=0;
	CHATSTRING[0]=0;
	int MAXCHATS=0;
	char** ChatMess=NULL;
	char** ChatSender=NULL;
	LoadFog(2);
	LocalGP BTNS("Interface\\Multi_opt");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP DIS("Interface\\an_start_disable");
	LocalGP SCROL("Interface\\_Slider");	
	LocalGP MASKA("Interface\\History_mask1");
	LocalGP NewFlag("Interface\\NewFlag");
	LocalGP INCHAT("Interface\\IButtons");
	PSUMM.ClearPingInfo();
	PlayerInfo MYPINF;
	memset(&MYPINF,0,sizeof MYPINF);

	SQPicture Back("Interface\\Background_Historical_Create.bmp");
	SQPicture Prev(WARS.Battles[BattleID].MiniMap);
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"2\\orange.grd");
	RLCFont FontW(FONT.GPID);
	FontW.SetColorTable(4);
	LoadOptionalTable(4,"2\\white.grd");

	DialogsSystem MENU(0,0);
	MENU.OkSound=GetSound("START");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MENU.HintFont=&hfnt;
	MENU.HintY=701;
	MENU.HintX=18;
	Picture* GPPB=MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
	GPPicture*  NameBack[2];
	GPPicture*  NationBack[2];
	GPPicture*  ColorBack[2];
	GPPicture*  Flags[2];
	GPPicture*  CD_Back[2];
	GPPicture*  CD_Present[2];
	GPPicture*  ReadyBack[2];
	InputBox*   MNAME  [2];
	ComboBox*   MNATION[2];
	TextButton* ReadyFlow[2];
	//ColoredBar* MCOLOR [8];
	TextButton* VersTextShadow[8];
	TextButton* VersText[8];
	GPPicture*  MREADY[2];
	//MENU.addInputBox(NULL,0,0,CurrentMap,64,400,25,&FontW,&FontW);
	ChatViewer* CHVIEW=MENU.addChatViewer(NULL,506,424,7,26,250,&ChatMess,&ChatSender,&NCHATS);
	char CHATMESSAGE[256]="";
	InputBox* CHATBOX=MENU.addInputBox(NULL,588-14,612,CHATMESSAGE,250,190,22,&YellowFont,&WhiteFont);
	CHATBOX->Active=1;
	VScrollBar* CHSCR=MENU.addNewGP_VScrollBar(NULL,778,409,198,1,0,SCROL.GPID,0);
	CHSCR->Visible=0;
	Picture* PREV=MENU.addPicture(NULL,496,156,&Prev,&Prev,&Prev);
	GPPicture* PMASK=MENU.addGPPicture(NULL,496,156,MASKA.GPID,0);
	VScrollBar* TXSB=MENU.addNewGP_VScrollBar(NULL,443,283,351,1,0,SCROL.GPID,0);
	
	ResFile FF1=RReset(WARS.Battles[BattleID].Brief);
	if(FF1!=INVALID_HANDLE_VALUE){
		ResFile FF2=RRewrite("miss.txt");
		if(FF2!=INVALID_HANDLE_VALUE){
			RBlockWrite(FF2,WARS.Battles[BattleID].BigHeader,strlen(WARS.Battles[BattleID].BigHeader));
			char cx=0x0D;
			RBlockWrite(FF2,&cx,1);
			cx=0x0A;
			RBlockWrite(FF2,&cx,1);
			cx=0x0D;
			RBlockWrite(FF2,&cx,1);
			cx=0x0A;
			RBlockWrite(FF2,&cx,1);
			byte* Data=new byte[RFileSize(FF1)];
			RBlockRead(FF1,Data,RFileSize(FF1));
			RBlockWrite(FF2,Data,RFileSize(FF1));
			RClose(FF2);
		};
		RClose(FF1);
	};

	TextViewer* BTTXT=MENU.addTextViewer(NULL,47,294,385,330,"miss.txt",&YellowFont);
	BTTXT->SymSize=20;
	BTTXT->PageSize=(BTTXT->y1-BTTXT->y)/BTTXT->SymSize;

	BTTXT->AssignScroll(TXSB);
	for(int i=0;i<2;i++){
		NameBack[i]=MENU.addGPPicture(NULL,38+5,161+i*26,BTNS.GPID,9+(i%3));
		NameBack[i]->Visible=0;
		MNAME[i]=MENU.addInputBox(NULL,32+5+5,160+i*26,PINFO[i].name,20,128,20,&WhiteFont,&YellowFont);
		MNAME[i]->Visible=0;
		NationBack[i]=MENU.addGPPicture(NULL,183,161+i*26,BTNS.GPID,i%3);
		NationBack[i]->Visible=0;
		ColorBack[i]=MENU.addGPPicture(NULL,295+8,161+i*26,BTNS.GPID,6+(i%3));
		ColorBack[i]->Visible=0;
		Flags[i]=MENU.addGPPicture(NULL,295-5+19+1,161-11+12+i*26,NewFlag.GPID,(i*17)%45);
		Flags[i]->Visible=0;
		CD_Back[i]=MENU.addGPPicture(NULL,358+5,161+i*26,BTNS.GPID,3+(i%3));
		CD_Back[i]->Visible=0;
		CD_Present[i]=MENU.addGPPicture(NULL,365,162+i*26,BTNS.GPID,25);
		CD_Present[i]->Visible=0;
		VersTextShadow[i]=MENU.addTextButton(NULL,376+12-12,161+6+i*26,"        ",&SmallBlackFont,&SmallBlackFont,&SmallBlackFont,1);
		VersTextShadow[i]->Visible=0;
		VersText[i]=MENU.addTextButton(NULL,376+12-12-1,161+6-2+i*26,"        ",&SmallYellowFont,&SmallYellowFont,&SmallYellowFont,1);
		VersText[i]->Visible=0;
		ReadyBack[i]=MENU.addGPPicture(NULL,399+4,161+i*26,BTNS.GPID,15+(i%3));
		ReadyBack[i]->Visible=0;

		MNAME[i]->Hint=GetTextByID("MOCHANGENAME");
		MNAME[i]->Visible=false;
		MNAME[i]->Enabled=false;
		MNATION[i]=MENU.addGP_ComboBox(NULL,183,161+i*26,BTNS.GPID,28+8*(i%3),8,0,&WhiteFont,&YellowFont,NULL);
		MNATION[i]->Hint=GetTextByID("MMCHANGENAT");
		MREADY[i]=MENU.addGPPicture(NULL,413,162+i*26,BTNS.GPID,26);
		MREADY[i]->Visible=0;
		MNATION[i]->AddLine(WARS.Battles[BattleID].RedUnits);
		MNATION[i]->AddLine(WARS.Battles[BattleID].BlueUnits);
		MNATION[i]->CurLine=i;
		MNATION[i]->Enabled=Host;

		MNATION[i]->FontDx-=2;
		//MNATION[i]->OneDx-=2;
		//MCOLOR[i]=MENU.addColoredBar(32+318,160+i*25,32,20,0xF7);
		//MCOLOR[i]->Hint=GetTextByID("MMCHANGECOLOR");
		//MCOLOR[i]->OnMouseOver=&ColorMouseOver;
		ReadyFlow[i]=MENU.addTextButton(NULL,332+100-8,164+i*26,"100%",&YellowFont,&YellowFont,&YellowFont,1);
		ReadyFlow[i]->Visible=0;
		ReadyFlow[i]->Enabled=0;
	};
	
	GPPicture* DISBL=MENU.addGPPicture(NULL,862,568,DIS.GPID,0);
	VideoButton* OkBtn;
	if(Host){
		OkBtn=MENU.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
		OkBtn->Hint=GetTextByID("MOSTART");
	}else{
		OkBtn=MENU.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
		OkBtn->Hint=GetTextByID("MOREADY");
	};
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	VideoButton* CancelBtn=MENU.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->Hint=GetTextByID("MOCANCEL");
	if(TPEN.Connected&&TPEN.MyRoom){
		GP_Button* ENC=MENU.addGP_Button(NULL,862,468,INCHAT.GPID,9,8);
		ENC->UserParam=99;
		ENC->OnUserClick=&MMItemChoose;
		ENC->Hint=GetTextByID("BACKINCHAT");
	};

	ItemChoose=-1;
	memset(PINFO,0,sizeof PINFO);
	GameInProgress=0;
	PIEnumeratePlayers(PINFO,0);
	if(NPlayers>2)NPlayers=2;
	byte CUSED=0;
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID!=MyDPID){
			CUSED|=(1<<PINFO[i].ColorID);
		};
	};
	int cc1=0;
	byte mss1=1;
	while(CUSED&mss1){
		cc1++;
		mss1<<=1;
	};
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID==MyDPID){
			PINFO[i].ColorID=cc1;
			ColorBack[i]->Nation=cc1;
			if(Host)PINFO[i].Ready=1;else PINFO[i].Ready=0;
			PINFO[i].Host=Host;
			PINFO[i].CD=1;
			PINFO[i].Version=dwVersion;
		}else{
			memset(PINFO+i,0,sizeof PlayerInfo);
		};
	};
	PIEnumeratePlayers(PINFO,0);
	if(NPlayers>2)NPlayers=2;
	PlayerMenuMode=1;
	GameInProgress=0;
	tmtmt=0;
	REALTIME=0;
	GLOBALTIME=0;
	PGLOBALTIME=0;
	int pp=1;
	KeyPressed=0;
	PBACK.Clear();
	PSUMM.ClearPingInfo();
	ReceiveAll();
	byte MSS1=0;
	bool GMREADY=true;
	int HostID=-1;
	int NCLINES=0;
	char* PNAME="";
	int DYL;
	char oldname[64]="";
	bool MyOldVers=0;
	bool PresOldVers=0;
	int PREVSD=GetTickCount();
	int NOMREADY=-1;
	word MaxVers=0;
	char* OLDV=GetTextByID("OLDVER");
	for(i=0;i<2;i++)PINFO[i].MapStyle=BattleID;
	if(Host)strcpy(MENU.DefaultHint,GetTextByID("DEVHISUS"));
	int NCS0=0;
	char* ONLY=GetTextByID("ONLYOU");
	do{
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID==MyDPID){
				if(Host)PINFO[i].Ready=1;
				PINFO[i].Host=Host;
				PINFO[i].CD=1;
				PINFO[i].Version=dwVersion;
			};
		};
		int CLY=19;
		int NCL=7;
		bool AddChat=0;
		HostID=-1;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].Host)HostID=i;
		};
		ProcessMessages();
		if(KeyPressed&&Host){
			if(LastKey==109){
				BattleID=SetCurrentBattle(BattleID-1,&Prev,MNATION,BTTXT);
				KeyPressed=0;
				PINFO[HostID].MapStyle=BattleID;
			};
			if(LastKey==107){
				BattleID=SetCurrentBattle(BattleID+1,&Prev,MNATION,BTTXT);
				KeyPressed=0;
				PINFO[HostID].MapStyle=BattleID;
			};
		};
		if(GameInProgress)goto FinCLC;
		if(KeyPressed&&LastKey==13){
			if(CHATBOX->Active&&CHATMESSAGE[0]){
				ControlLingvo(CHATMESSAGE);
				SendChat(CHATMESSAGE,0);
				AddChatString(
					GetPlNameByID(MyDPID),
					CHATMESSAGE,250,
					&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
				AddChat=1;
				CHATMESSAGE[0]=0;
			}else
			if(TPEN.GlobalChat.NCStr>NCS0){
				for(int j=NCS0;j<TPEN.GlobalChat.NCStr;j++){
					if(strstr(TPEN.GlobalChat.CStr[j].PlName,ONLY)){
						AddChatString(
							TPEN.GlobalChat.CStr[j].PlName,
							TPEN.GlobalChat.CStr[j].Message,375,
								&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
						AddChat=1;
					};
				};
				NCS0=TPEN.GlobalChat.NCStr;
			};
			KeyPressed=0;
			LastKey=0;
		};
		if(CHATSTRING[0]){
			AddChatString(
					GetPlNameByID(CHATDPID),
					CHATSTRING,250,
					&WhiteFont,ChatMess,ChatSender,NCHATS,MAXCHATS);
			CHATSTRING[0]=0;
			AddChat=1;
		};
		NCLINES=0;
		PNAME="";
		if(NCHATS>NCL){
			CHSCR->SMaxPos=NCHATS-NCL;
			if(AddChat)CHSCR->SPos=CHSCR->SMaxPos;
			CHSCR->Visible=1;
			CHVIEW->ChatDY=CHSCR->SPos;
		}else{
			CHSCR->Visible=0;
			CHSCR->SPos=0;
			CHVIEW->ChatDY=0;
		};
		DYL=CHSCR->SPos;
		
		SendPings();
		StdKeys();
		if(ItemChoose==mcmOk&&!OkBtn->Enabled)ItemChoose=-1;
		AnalyseMessages();
		if(GameInProgress)goto FinCLC;
		if(MyOldVers)GPPB->Hint=OLDV;
		MENU.MarkToDraw();
		MENU.ProcessDialogs();
		if(GameInProgress)goto FinCLC;
		char ccc[128];
		if(PSUMM.NPL&&PSUMM.PSET[0].NPings){
			int png=GetMaxRealPing();
			
			//png=GetAveragePing();
			//MaxPingTime=png;
			if(GetRealTime()-PPTIME>1000){
				DWORD lpp[3];
				lpp[0]='PNTF';
				lpp[1]=png;
				lpp[2]=lpp[0]+lpp[1];
				SendToAllPlayers(12,lpp);
				PPTIME=GetRealTime();
				for(int p=0;p<NPlayers;p++)if(PINFO[p].PlayerID==MyDPID)CurrentMaxPing[p]=png;
			};
			for(int p=0;p<NPlayers;p++)if(CurrentMaxPing[p]>png)png=CurrentMaxPing[p];
			MaxPingTime=png;
			if(png<MinPing0)MaxPingTime=0;//FIXIT!!!!!!!!!!!
			if(png>=MinPing0&&png<300)MaxPingTime=300;
			if(MaxPingTime)MaxPingTime+=500;
			char cc2[300];
			CreateDiffStr(cc2);
			sprintf(ccc,"max ping: %d  (%s)",png,cc2);
			ShowString(10,768-24,ccc,&SmallYellowFont);
		};
		
		MENU.RefreshView();
		if(GameInProgress)goto FinCLC;
		
		ReadyFlow[0]->Visible=0;
		ReadyFlow[1]->Visible=0;
		if(Host){
			if(HostID!=-1){
				PINFO[HostID].MapName[0]=0;
				strcpy(PINFO[HostID].MapName,WARS.Battles[BattleID].Map);
				strcpy(CurrentMap,PINFO[HostID].MapName);
				MNATION[HostID]->Enabled=1;
				MNATION[1-HostID]->Enabled=0;
				int PPP;
				if((PPP=GetReadyPercent())<100){
					sprintf(ReadyFlow[HostID]->Message,"%d%%",PPP);
					ReadyFlow[HostID]->Visible=1;
					MREADY[HostID]->Visible=0;
					MREADY[HostID]->Enabled=0;
					NOMREADY=HostID;
				}else{
					ReadyFlow[HostID]->Visible=0;
					MREADY[HostID]->Visible=1;
					MREADY[HostID]->Enabled=1;
					NOMREADY=-1;;
				};
			};
		}else{
			MNATION[0]->Enabled=0;
			MNATION[1]->Enabled=0;
			ReadyFlow[0]->Visible=0;
			ReadyFlow[1]->Visible=0;

		};
		if(HostID!=-1){
			MNATION[1-HostID]->CurLine=1-MNATION[HostID]->CurLine;
			for(int i=0;i<2;i++){
				ColorBack[i]->Nation=MNATION[i]->CurLine;
				Flags[i]->Nation=MNATION[i]->CurLine;
			};
		};
		MaxVers=0;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].Version>MaxVers)MaxVers=PINFO[i].Version;
		};
		for(i=0;i<2;i++){
			if(i<NPlayers){
				if(PINFO[i].PlayerID==MyDPID){
					PINFO[i].NationID=MNATION[i]->CurLine;
					PINFO[i].ColorID=ColorBack[i]->Nation;
					bool ch=memcmp(&MYPINF,PINFO+i,sizeof MYPINF);
					if(ch||GetTickCount()-PREVSD>3000){//3000
						SETPLAYERDATA(MyDPID,(void*)&PINFO[i].NationID,sizeof(PlayerInfo)-36,ch);
						memcpy(&MYPINF,PINFO+i,sizeof MYPINF);
						PREVSD=GetTickCount();
					};
					if(ch&&Host)PSUMM.ClearPingInfo();
					DPNAME dpName;
					ZeroMemory(&dpName, sizeof(DPNAME));
					dpName.dwSize = sizeof(DPNAME);
					dpName.lpszShortNameA = MNAME[i]->Str;
					dpName.lpszLongNameA = NULL;
					if(strcmp(dpName.lpszShortNameA,oldname)){
						SETPLAYERNAME(&dpName,strcmp(dpName.lpszShortNameA,oldname)!=0);
						strcpy(oldname,dpName.lpszShortNameA);
					};
					//MNATION[i]->Enabled=true;
					//MGRP[i]->Enabled=true;
						NameBack[i]->Visible=1;
					MNAME[i]->Visible=1;
					MNAME[i]->Enabled=0;//1;
					NationBack[i]->Visible=1;
					NationBack[i]->Enabled=1;
					CD_Back[i]->Visible=1;
					//MNATION[i]->Enabled=1;
					ColorBack[i]->Visible=1;
					ColorBack[i]->Enabled=1;
					ReadyBack[i]->Visible=1;
					MyOldVers=PINFO[i].Version!=MaxVers;
				}else{
					NationBack[i]->Visible=1;
					NationBack[i]->Enabled=1;
					MNAME[i]->Visible=1;
					MNAME[i]->Enabled=0;
					MNAME[i]->Active=0;
					NameBack[i]->Visible=0;
					//MNATION[i]->Enabled=0;
					CD_Back[i]->Visible=0;
					ColorBack[i]->Visible=0;
					ColorBack[i]->Enabled=0;
					ReadyBack[i]->Visible=0;
					//MGRP[i]->Enabled=false;
				};
				if(MNAME[i]->Active)NameBack[i]->SpriteID=12+(i%3);
				else NameBack[i]->SpriteID=9+(i%3);
				Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
				Flags[i]->Nation=ColorBack[i]->Nation;
				MNATION[i]->Visible=true;
				//MCOLOR[i]->Visible=true;
				MREADY[i]->SpriteID=26+(PINFO[i].Ready!=0);
				if(i!=NOMREADY){
					MREADY[i]->Visible=true;
					MREADY[i]->Enabled=true;
				};
				Flags[i]->Visible=1;
				CD_Present[i]->Visible=1;
				//MREADY[i]->Visible=1;
				MNATION[i]->Visible=1;
				//ReadyBack[i]->Visible=0;
				//MGRP[i]->Visible=true;
				int v=PINFO[i].Version;
				char VERS[128];
				if(v>255){
					sprintf(VERS,"M%d",v>>8);
				}else{
					sprintf(VERS,"%d.%d%d",v/100,(v/10)%10,v%10);
				};
				strcpy(VersText[i]->Message,VERS);
				strcpy(VersTextShadow[i]->Message,VERS);
				if(v!=MaxVers&&(GetTickCount()/300)&1){
					VersText[i]->ActiveFont=&SmallRedFont;
					VersText[i]->PassiveFont=&SmallRedFont;
				}else{
					VersText[i]->ActiveFont=&SmallYellowFont;
					VersText[i]->PassiveFont=&SmallYellowFont;
				};
				VersText[i]->Visible=1;
				VersTextShadow[i]->Visible=1;
				PresOldVers=v!=MaxVers;
			}else{
				NameBack[i]->Visible=0;
				NationBack[i]->Visible=0;
				ColorBack[i]->Visible=0;
				Flags[i]->Visible=0;
				CD_Back[i]->Visible=0;
				CD_Present[i]->Visible=0;
				ReadyBack[i]->Visible=0;
				MNAME[i]->Visible=0;
				MNAME[i]->Enabled=0;
				MNAME[i]->Active=0;
				MREADY[i]->Visible=0;
				MNATION[i]->Visible=0;
				//MGRP[i]->Visible=false;
				VersText[i]->Visible=0;
				VersTextShadow[i]->Visible=0;
			};
		};
		if(!PIEnumeratePlayers(PINFO,1)){
			ItemChoose=mcmCancel;
		};
		if(NPlayers>2)NPlayers=2;
		if(!Host){
			int HostID=-1;
			int MyID=-1;
			for(int i=0;i<NPlayers;i++){
				if(PINFO[i].Host)HostID=i;
				if(PINFO[i].PlayerID==MyDPID)MyID=i;
			};
			if(HostID!=-1&&MyID!=-1){
				if(PINFO[MyID].MapStyle!=PINFO[HostID].MapStyle){
					PINFO[MyID].MapStyle=PINFO[HostID].MapStyle;
					BattleID=SetCurrentBattle(PINFO[MyID].MapStyle,&Prev,MNATION,BTTXT);
					MYPINF.MapStyle=PINFO[MyID].MapStyle;
				};
				strcpy(PINFO[MyID].MapName,PINFO[HostID].MapName);
				//PINFO[MyID].MapStyle=0;
				PINFO[MyID].HillType=0;
				PINFO[MyID].StartRes=0;
				PINFO[MyID].ResOnMap=0;
				strcpy(CurrentMap,PINFO[HostID].MapName);
			};
		};
		for(i=0;i<NPlayers;i++){
			MNATION[i]->CurLine=PINFO[i].NationID;
			ColorBack[i]->Nation=PINFO[i].ColorID;
			if(PINFO[i].PlayerID==MyDPID&&ItemChoose==mcmOk&&!Host){
				PINFO[i].Ready=1;
			};
		};
		GMREADY=true;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID!=MyDPID&&!PINFO[i].Ready)GMREADY=false;
		};
		MSS1=0;
		for(i=0;i<NPlayers;i++){
			byte MSS2=1<<PINFO[i].ColorID;
			if(MSS1&MSS2)GMREADY=false;
			MSS1|=MSS2;
			if(!PINFO[i].Ready)GMREADY=false;
		};
		if(Host){
			if(NPlayers<2)GMREADY=false;
			if(!CheckPingsReady())GMREADY=false;
			if(PresOldVers)GMREADY=0;
			OkBtn->Enabled=GMREADY;
			OkBtn->Visible=GMREADY;
			if(TPEN.MyRoom&&TPEN.MyRoom->RoomConnected){
				TPEN.CreateMyRoomInfoString(TPEN.HostMessage);
			};
		}else{
			OkBtn->Enabled=!MyOldVers;
			OkBtn->Visible=!MyOldVers;
		};
		//checking readyness
		if(ItemChoose==mcmOk&&!Host)ItemChoose=-1;
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
			ReceiveAll();
			//PSUMM.ClearPingInfo();
		};
		if(ItemChoose==99){
			ProcessInternetConnection(0);
			ItemChoose=-1;
			if(PlayerMenuMode!=1)ItemChoose=mcmSingle;
		};
FinCLC:;
	}while(ItemChoose==-1&&PlayerMenuMode==1);
	PINFO[0].GameTime=0;
	PINFO[0].VictCond=0;
	if(NCHATS){
		for(int i=0;i<NCHATS;i++){
			free(ChatMess[i]);
			free(ChatSender[i]);
		};
		free(ChatMess);
		free(ChatSender);
	};
	return (ItemChoose==mcmOk)||PlayerMenuMode!=1;//ItemChoose==mcmOk;
};
void CreateNationalMaskForRandomMap(char*);
void CreateMaskForSaveFile(char*);
void CreateNationalMaskForMap(char*);
int DetermineNationAI(byte Nat){
	for(int i=0;i<MAXOBJECT;i++){
		OneObject* OB=Group[i];
		if(OB&&OB->NNUM==Nat&&OB->newMons->Peasant&&!OB->Sdoxlo){
			char* name=OB->Ref.General->MonsterID;
			for(int j=0;j<GlobalAI.NAi;j++){
				if(!strcmp(GlobalAI.Ai[j].Peasant_ID,name))return j;
			};
		};
	};
	return -1;
};
bool GetPreview(char* Name,byte* Data);
bool RunEnciclopia(SimpleDialog* SD){
	WinExec("HView.exe",SW_NORMAL);
	/*
	char cc[256];
	GetWindowsDirectory(cc,256);
	char cc1[300];
	sprintf(cc1,"%s\\command\\start.exe",cc);
	GFILE* f=Gopen("Info\\index.htm","r");
	if(f){
		Gclose(f);
		char cc2[300];
		sprintf(cc2,"%s /max Info\\index.htm",cc1);
		WinExec(cc2,SW_MINIMIZE);
		return 0;
	};
	for(int i='d';i<='z';i++){
		char cd[2]="a";
		char cc3[300];
		cd[0]=i;
		sprintf(cc3,"%s:\\GSC_Info\\index.htm",cd);
		GFILE* f=Gopen(cc3,"r");
		if(f){
			Gclose(f);
			char cc2[300];
			sprintf(cc2,"%s /max %s",cc1,cc3);
			WinExec(cc2,SW_MINIMIZE);
			return 0;
		};

	};
	*/
	return 0;
};
extern int RunMethod;
bool SingleOptions(){
	if(MPL_WaitingGame(1,1)){
		StartIGame(1);
		return true;
	}else return false;

	MaxPingTime=0;
	byte* Preview=new byte[(292*190)+4];
	char Currand[200];
	((word*)Preview)[0]=292;
	((word*)Preview)[1]=190;
	bool PrPresent=false;
	char LastPrName[200]="";
	byte XLAT[256];
	ResFile fx=RReset("2\\0to1.xlt");
	RBlockRead(fx,XLAT,256);
	RClose(fx);

	//SlowUnLoadPalette("1\\agew_1.pal");
	int MaxPlay=7;
	LocalGP BTNS("Interface\\Random_map");
	LocalGP MASKA("Interface\\preview_mask");
	LocalGP SCROL("Interface\\_Slider");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP DIS("Interface\\an_start_disable");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP NewFlag("Interface\\NewFlag");

	SQPicture Back("Interface\\Random_Map_Background.bmp");
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"1\\orange.grd");
	RLCFont FontW(FONT.GPID);
	FontW.SetColorTable(4);
	LoadOptionalTable(4,"1\\white.grd");

	DialogsSystem MENU(0,0);
	MENU.OkSound=GetSound("START");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MENU.HintFont=&hfnt;
	MENU.HintY=701;
	MENU.HintX=18;
	MENU.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MENU.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");
	BPXView* PREV=MENU.addBPXView(NULL,496,441,292,190,1,1,1,Preview+4,NULL);
	PREV->Visible=false;
	GPPicture* MSK=MENU.addGPPicture(NULL,496,441,MASKA.GPID,0);
	InputBox* MNAME  [8];
	ComboBox*   MNATION[8];
	ComboBox*   COMP[8];
	GPPicture* Flags[8];
	GPPicture* BACK[8];
	char* NoPlayer=GetTextByID("None");
	char* CompName=GetTextByID("Computer");
	MNAME[0]=MENU.addInputBox(NULL,38+6,161,PINFO[0].name,20,128,20,&WhiteFont,&YellowFont);
	MNAME[0]->Hint=GetTextByID("SOCHANGENAME");
	for(int i=0;i<MaxPlay;i++){
		BACK[i]=MENU.addGPPicture(NULL,223,161+26*i,BTNS.GPID,90+(i%3));
		Flags[i]=MENU.addGPPicture(NULL,413-20+18,162-10+11+i*26,NewFlag.GPID,(i*17)%45);
		if(i>1)Flags[i]->Visible=0;
		Flags[i]->Nation=i;
		if(i){
			COMP[i]=MENU.addGP_ComboBox(NULL,38,187-26+i*26,BTNS.GPID,24+(i%3)*8,9,0,&WhiteFont,&YellowFont,NULL);
			COMP[i]->AddLine(NoPlayer);
			COMP[i]->AddLine(CompName);
			COMP[i]->CurLine=i<2;
			COMP[i]->Hint=GetTextByID("SOCHANGECOMP");
		};
		MNATION[i]=MENU.addGP_ComboBox(NULL,223,161+26*i,BTNS.GPID,(i%3)*8,8,0,&WhiteFont,&YellowFont,NULL);
		if(i)MNATION[i]->Hint=GetTextByID("MMCHANGENAT2");
		else MNATION[i]->Hint=GetTextByID("MMCHANGENAT1");
#ifdef TUTORIAL_DEMOVERSION
		int NG=1;
#else
		int NG=GlobalAI.NAi;
		if(i)NG=GlobalAI.NComp;
#endif
		for(int j=0;j<NG;j++){
			MNATION[i]->AddLine(GlobalAI.Ai[j].Message);
		};
	};
	for(i=0;i<MaxPlay;i++){
		switch(i){
		case 0:
			strcpy(PINFO[i].name,PlName);
			break;
		case 1:
			strcpy(PINFO[i].name,CompName);
			break;
		default:
			strcpy(PINFO[i].name,NoPlayer);
		};
		PINFO[i].ColorID=i;
	};
	//MENU.addInputBox(NULL,0,0,CurrentMap,64,400,25,&FontW,&FontW);

	/*
	char NAMY[16];
	for(i=0;i<MaxPlay;i++){
		MNAME[i]=MENU.addInputBox(NULL,32,160+i*25,PINFO[i].name,20,128,20,&FontY,&FontW);
		//MNAME[i]->Enabled=false;
		MNATION[i]=MENU.addComboBox(NULL,32+180,160+i*25,160,20,20,0,255,&FontW,&FontY,NULL);
		MNATION[i]->Hint=GetTextByID("MMCHANGENAT");
		int NG=GlobalAI.NAi;
		if(i)NG=GlobalAI.NComp;
		for(int j=0;j<NG;j++){
			MNATION[i]->AddLine(GlobalAI.Ai[j].Message);
		};
		MNATION[i]->FontDx=4;
		MNATION[i]->FontDy=2;
		MCOLOR[i]=MENU.addColoredBar(32+318+30+15+6,160+i*25,32,20,0xF7+i);
		if(i>0){
			MNATION[i]->Visible=false;
			MNATION[i]->Enabled=false;
			MCOLOR[i]->Visible=false;
			MCOLOR[i]->Enabled=false;
			MNAME[i]->OnUserClick=&MMChooseName;
			MNAME[i]->UserParam=i;
			MNAME[i]->Hint=GetTextByID("SOCHANGECOMP");
		}else{
			MNAME[i]->Hint=GetTextByID("SOCHANGENAME");
		};
	};
	*/
	//---------------Page 1--------------
	GPPicture* DMP=MENU.addGPPicture(NULL,495,149,BTNS.GPID,58);
	VScrollBar* VSB=MENU.addNewGP_VScrollBar(NULL,778,152,221,1,0,SCROL.GPID,0);
	ListBox* LBMaps=MENU.addGP_ListBox(NULL,494,160,8,BTNS.GPID,59,26,&WhiteFont,&YellowFont,VSB);
	LBMaps->FontDx-=8;
	LBMaps->FontDy-=2;
	LBMaps->M_Over=62;
	//---------------Page 2--------------
	int y=161;
	int y0=y;
	int x=506;
	int x0=x+128+20;
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
	ComboBox* CMGRP1[6];
	//GPPicture* RMS=MENU.addGPPicture(NULL,495,149,BTNS.GPID,21);
	CMGRP1[0]=MENU.addGP_ComboBox(NULL,633,161,BTNS.GPID,65,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[0]->CurLine=RMP.STY_DEF;
	for(int p=0;p<RMP.NSTY;p++){
		CMGRP1[0]->AddLine(RMP.STY[p].Name);
	};
	CMGRP1[0]->Hint=GetTextByID("SOMAPSTYLE");
	y+=25;
	CMGRP1[1]=MENU.addGP_ComboBox(NULL,633,161+26,BTNS.GPID,73,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[1]->CurLine=RMP.Relief_DEF;
	for(p=0;p<RMP.NRelief;p++){
		CMGRP1[1]->AddLine(RMP.Relief[p]);
	};
	CMGRP1[1]->Hint=GetTextByID("SOMOUNT");
	y+=25;
	CMGRP1[2]=MENU.addGP_ComboBox(NULL,633,161+26*2,BTNS.GPID,81,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[2]->CurLine=RMP.RES_DEF;
	for(p=0;p<RMP.NRES;p++){
		CMGRP1[2]->AddLine(RMP.RES[p].Name);
	};
	CMGRP1[2]->Hint=GetTextByID("SORESTOT");
	y+=25;
	CMGRP1[3]=MENU.addGP_ComboBox(NULL,633,161+26*3,BTNS.GPID,65,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[3]->CurLine=RMP.MINES_DEF;
	for(p=0;p<RMP.NMINES;p++){
		CMGRP1[3]->AddLine(RMP.MINES[p].Name);
	};
	CMGRP1[3]->Hint=GetTextByID("SORESONMAP");
	
	CMGRP1[4]=MENU.addGP_ComboBox(NULL,173,446,BTNS.GPID,48,8,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[4]->CurLine=1;
	CMGRP1[4]->AddLine(GetTextByID("@RMID_EASY"));
	CMGRP1[4]->AddLine(GetTextByID("@RMID_NORMAL"));
	CMGRP1[4]->AddLine(GetTextByID("@RMID_HARD"));
	CMGRP1[4]->AddLine(GetTextByID("@RMID_VERYHARD"));
	CMGRP1[4]->Hint=GetTextByID("DIFFICULTY");
	GPPicture* Exam=MENU.addGPPicture(NULL,495,413,BTNS.GPID,89);

	CMGRP1[5]=MENU.addGP_ComboBox(NULL,633,161+26*4,BTNS.GPID,60,9,0,&WhiteFont,&YellowFont,NULL);
	CMGRP1[5]->CurLine=0;
	CMGRP1[5]->AddLine(GetTextByID("MS_NORMAL"));
	CMGRP1[5]->AddLine(GetTextByID("MS_LARGE"));
	CMGRP1[5]->AddLine(GetTextByID("MS_HUGE"));

	//-----------------------------------
	GP_PageControl* GPP=MENU.addPageControl(NULL,495,128,BTNS.GPID,56);
	GPP->AddPage(495,128,495+146,128+22,56);
	GPP->AddPage(495+146,128,495+292,128+22,57);
	GPP->CurPage=1;
	GPP->Hint=GetTextByID("SOPAGES");
	GPPicture* DISBL=MENU.addGPPicture(NULL,862,568,DIS.GPID,0);
	VideoButton* OkBtn;
	OkBtn=MENU.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->Hint=GetTextByID("SOSTART");
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	//GPPicture* DISBL=MENU.addGPPicture(NULL,862,568,DIS.GPID,0);
	VideoButton* CancelBtn=MENU.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->Hint=GetTextByID("SOCANCEL");
	CreateMapsList(LBMaps);
	NameChoose=-1;
	ItemChoose=-1;
	int pp=1;
	GFILE* f=Gopen("Single.opt","r");
	if(f){
		int v;
		for(int i=0;i<5;i++){
			v=0;
			Gscanf(f,"%d",&v);
			CMGRP1[i]->CurLine=v;
		};
		Gclose(f);
	};
	LoadFog(2);
	KeyPressed=0;
	do{
		CurrentNation=MNATION[0]->CurLine;
		for(i=0;i<MaxPlay;i++)Flags[i]->SpriteID=(i*229+GetRealTime()/30)%45;
		bool P1E=GPP->CurPage==0;
		bool P2E=GPP->CurPage==1;
		VSB->Visible=P1E;
		LBMaps->Visible=P1E;
		DMP->Visible=P2E;
		for(int p=0;p<6;p++){
			CMGRP1[p]->Visible=P2E;
			CMGRP1[p]->Enabled=P2E;
		};
		Exam->Visible=P2E;
		PREV->Active=0;
		ProcessMessages();
		StdKeys();
		PREV->Active=0;
		CurrentMap[0]=0;
		if(GPP->CurPage==0){
			if(LBMaps->CurItem>=0&&LBMaps->NItems){
				strcpy(CurrentMap,LBMaps->GetItem(LBMaps->CurItem)->Message);
			};
			if(strcmp(CurrentMap,LastPrName)){
				strcpy(LastPrName,CurrentMap);
				if(GetPreview(CurrentMap,Preview+4)){
					PREV->Visible=1;
					Decode(Preview+4,XLAT,292*190);
				}else{
					PREV->Visible=false;
				};
			};
		}else
		if(GPP->CurPage==1){
			char Nats[9];
			char Nats1[9];
			strcpy(Nats,"00000000");
			strcpy(Nats1,"00000000");
			char* NTCHAR="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			int ss=0;
			for(int q=0;q<MaxPlay;q++){
				if(strcmp(PINFO[q].name,NoPlayer)){
					Nats[7-PINFO[q].ColorID]=NTCHAR[MNATION[q]->CurLine+1];
					Nats1[7-ss]='1';
					ss++;
				};
			};
			if(ss>4){
				CMGRP1[0]->Enabled=0;
				CMGRP1[0]->CurLine=0;
			};
			char ccc[128];
			int r=GetRealTime()&65535;
			sscanf(ccc,"%d",&r);
			int NP=-1;
			for(int j=1;j<MaxPlay;j++){
				if(strcmp(PINFO[j].name,NoPlayer))NP++;
			};
			int s=CMGRP1[0]->CurLine+((NP)<<4)+(CMGRP1[1]->CurLine<<8)
				+(CMGRP1[2]->CurLine<<12)+(CMGRP1[3]->CurLine<<16);
			sprintf(CurrentMap,"RND %X %X %s.m3d",r,s,Nats);
			sprintf(Currand,"Preview\\%d%d %s",CMGRP1[1]->CurLine,CMGRP1[0]->CurLine,Nats1);
			if(strcmp(Currand,LastPrName)){
				strcpy(LastPrName,Currand);
				if(GetPreview(Currand,Preview+4)){
					PREV->Visible=1;
					Decode(Preview+4,XLAT,292*190);
				}else{
					PREV->Visible=false;
				};
			};
		};
		MENU.MarkToDraw();
		MENU.ProcessDialogs();
		MENU.RefreshView();
		
		/*
		if(NameChoose!=-1){
			if(!strcmp(MNAME[NameChoose]->Str,NoPlayer)){
				strcpy(PINFO[NameChoose].name,CompName);
			}else{
				strcpy(PINFO[NameChoose].name,NoPlayer);
			};
			NameChoose=-1;
		};
		*/
		for(i=1;i<MaxPlay;i++){
			if(COMP[i]->CurLine==0){
				MNATION[i]->Visible=false;
				MNATION[i]->Enabled=false;
				Flags[i]->Visible=false;
				strcpy(PINFO[i].name,NoPlayer);
			}else{
				MNATION[i]->Visible=P2E;
				MNATION[i]->Enabled=P2E;
				Flags[i]->Visible=true;
				strcpy(PINFO[i].name,CompName);
			};
		};
		bool GMREADY=true;
		int nn=0;
		for(i=1;i<MaxPlay;i++){
			if(COMP[i]->CurLine)nn++;
		};
		if(!nn)GMREADY=false;
		OkBtn->Enabled=GMREADY;
		OkBtn->Visible=GMREADY;
		//if(ItemChoose==mcmOk)ItemChoose=-1;
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		RunMethod=0x23000000+RM_Resstart+(RM_Restot<<4)+(CMGRP1[4]->CurLine<<8)
			+(RMP.STY[RM_LandType].AI_Style<<12);
		ShowLoading();
		bool RunAI=true;
		if(strstr(CurrentMap,"RND ")){
			CreateNationalMaskForRandomMap(CurrentMap);
		}else if(strstr(CurrentMap,".sav")||strstr(CurrentMap,".SAV"))CreateMaskForSaveFile(CurrentMap);
		else CreateNationalMaskForMap(CurrentMap);
		CurrentCampagin=-1;
		CurrentMission=-1;
		PrepareGameMedia(0,0);
		if(MapScenaryDLL[0])RunAI=0;
		InitGame();
		ItemChoose=mcmSingle;
		//InitExplosions();
		//PrepareToGame();
		for(int k=1;k<MaxPlay;k++){
			int nidx=DetermineNationAI(k);
			if(nidx!=-1&&COMP[k]->CurLine){//strcmp(PINFO[k].name,NoPlayer)){
				char ccx[64];
				Nation* NT=NATIONS+k;
				int MaxA=-1;
				char* NtID=GlobalAI.Ai[nidx/*MNATION[k]->CurLine*/].NationID;
				int Land=CMGRP1[0]->CurLine;
				for(int w=0;w<10;w++){
					sprintf(ccx,"%s.%d",NtID,w);
					char* AIN=GetTextByID(ccx);
					if(AIN!=ccx)MaxA=w;
				};
				if(MaxA==-1){
					sprintf(ccx,"Undefined AI identifier (see miss_AI.txt) : %s.%d",NtID,0);
					ErrM(ccx);
				};
				if(RunAI){
					sprintf(ccx,"%s.%d",NtID,((MaxA+1)*int(rando()))>>15);
					LoadAIFromDLL(k,GetTextByID(ccx));
				};
				strcpy(NT->CITY->AIID,ccx);
				NT->CITY->MAX_WORKERS=NT->DEFAULT_MAX_WORKERS;
				NT->CITY->StartRes=RM_Resstart;//CMGRP1[2]->CurLine;
				NT->CITY->ResOnMap=RM_Restot;//CMGRP1[3]->CurLine;
				NT->CITY->Difficulty=CMGRP1[4]->CurLine;
				NT->CITY->LandType=RMP.STY[RM_LandType].AI_Style;//RMP.STY[CMGRP1[0]->CurLine].AI_Style;
				if(RunAI){
					NT->AI_Enabled=true;
					NT->NMask=0x7E;
					for(int i=0;i<MAXOBJECT;i++){
						OneObject* OB=Group[i];
						if(OB&&OB->NNUM==k&&OB->BrigadeID==0xFFFF){
							NT->CITY->RegisterNewUnit(OB);
							OB->NMask=0x7E;
						};
					};
				};
			};
		};
	}else SlowUnLoadPalette("2\\agew_1.pal");
	PINFO[0].GameTime=0;
	PINFO[0].VictCond=0;
	f=Gopen("Single.opt","w");
	if(f){
		Gprintf(f,"%d %d %d %d %d",CMGRP1[0]->CurLine,CMGRP1[1]->CurLine,CMGRP1[2]->CurLine,CMGRP1[3]->CurLine,CMGRP1[4]->CurLine);
		Gclose(f);
	};
	free(Preview);
	return true;
};
int ProcessWars();
void processBattleMultiplayer();
CIMPORT void GoHomeAnyway();
#ifdef MAKE_PTC
int MM_ProcessMultiPlayer(){
	GoHomeAnyway();
	//SlowUnLoadPalette("2\\agew_1.pal");
	LocalGP BTNS("Interface\\Multi_Player");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	SQPicture MnPanel("Interface\\Background_Multi_Player.bmp");
	DialogsSystem MMenu(0,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	int Dy=110;
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	GP_Button* DeathM=MMenu.addGP_Button(NULL,76,140+Dy,BTNS.GPID,0,1);
	DeathM->UserParam=1;
	DeathM->OnUserClick=&MMItemChoose;
	DeathM->Hint=GetTextByID("MDEATHM");
	DeathM->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	GP_Button* HistBatt=MMenu.addGP_Button(NULL,76,140+82+Dy,BTNS.GPID,2,3);
	HistBatt->UserParam=2;
	HistBatt->OnUserClick=&MMItemChoose;
	HistBatt->Hint=GetTextByID("MHISTBATT");
	HistBatt->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	GP_Button* Back=MMenu.addGP_Button(NULL,76,140+82*2+Dy,BTNS.GPID,4,5);
	Back->UserParam=5;
	Back->OnUserClick=&MMItemChoose;
	Back->Hint=GetTextByID("MBACK");
	Back->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	ItemChoose=-1;
	UnPress();
	Lpressed=0;
	LastKey=0;
	KeyPressed=0;
	int pp=1;
	do{
		ProcessMessages();
		if(KeyPressed&&LastKey==27){
			ItemChoose=5;
			KeyPressed=0;
		};
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
#ifdef TUTORIAL_DEMOVERSION
		if(ItemChoose==2)ItemChoose=-1;
#else
		if(ItemChoose==2&&!WARS.NWars)ItemChoose=-1;
#endif
	}while(ItemChoose==-1);
	SlowUnLoadPalette("2\\agew_1.pal");
	if(ItemChoose==1){
		processMultiplayer();
		if(TOTALEXIT)return mcmCancel;
	};
	if(ItemChoose==2){
		if(WARS.NWars)processBattleMultiplayer();
		//ProcessWars();
	};
	return ItemChoose;
};
#endif
/*
Accept      - 153x239
Cancel      - 304x239
Low_Speed   - 224x120
High_Speed  - 397x120
Low_Scrol   - 224x151
High_Scrol  - 397x151
Low_Music   - 224x182
High_Music  - 397x182
Low_Sound   - 224x214
High_Sound  - 397x214

Ñëàéäåð:
Low - ëåâàÿ âåðõíÿÿ òî÷êà ìèíèìàëüíîãî çíà÷åíèÿ,
High - ëåâàÿ âåðõíÿÿ òî÷êà ìàêñèìàëüíî çíà÷åíèÿ.

Low_Speed   - 233x120
High_Speed  - 383x120
Low_Scrol   - 233x151
High_Scrol  - 383x151
Low_Music   - 233x182
High_Music  - 383x182
Low_Sound   - 233x214
High_Sound  - 383x214
*/
extern int exRealLx;
extern int exRealLy;
extern int exFMode;
int GetCDVolume();
void SetCDVolume(int);
int PlayMode=2;
void StopPlayCD();
void PlayRandomTrack();
extern byte TracksMask[16];
char RECFILE[128]="";
bool ProcessMenuOptions(){
	//SlowUnLoadPalette("1\\agew_1.pal");
	LocalGP BTNS("Interface\\Options");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	LoadPointer("cur_mn.rlc");
	SQPicture MnPanel("Interface\\Background_options.bmp");
	DialogsSystem MMenu(0,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,1))>>1)-85-125;
	//int dy=(RealLy-GPS.GetGPHeight(BTNS.GPID,1))>>1;
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,1);

	GP_Button* OkBtn=MMenu.addGP_Button(NULL,113,534+10+13,BTNS.GPID,8,9);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;

	GP_Button* ExitBtn=MMenu.addGP_Button(NULL,333,534+10+13,BTNS.GPID,10,11);
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;

	if(FPSTime>100)FPSTime=100;
	if(FPSTime<0)FPSTime=0;
	//game speed (#3)
	if(ScrollSpeed<2)ScrollSpeed=2;
	int X0=244-2;
	int LX=484-244+20;
	int DY=10;
	GPPicture* P1=MMenu.addGPPicture(NULL,240,317+10-13,BTNS.GPID,13);
	GPPicture* P2=MMenu.addGPPicture(NULL,240,343+10-13,BTNS.GPID,14);
	GPPicture* P3=MMenu.addGPPicture(NULL,240,447+10-13,BTNS.GPID,15);
	GPPicture* P4=MMenu.addGPPicture(NULL,240,473+10-13,BTNS.GPID,16);
	P1->Visible=0;
	P2->Visible=0;
	P3->Visible=0;
	P4->Visible=0;
	VScrollBar* HB=MMenu.addGP_ScrollBarL(NULL,X0,476+DY+10-13,100,100-FPSTime,BTNS.GPID,12,LX,12,0,0);
	//scroll speed (#4)
	VScrollBar* SSP=MMenu.addGP_ScrollBarL(NULL,X0,450+DY+10-13,8,ScrollSpeed-2,BTNS.GPID,12,LX,12,0,0);
	//sound volume (#1)
	VScrollBar* SVL=MMenu.addGP_ScrollBarL(NULL,X0,346+DY+10-13,100,WarSound,BTNS.GPID,12,LX,12,0,0);
	//music volume (#2)
	MidiSound=GetCDVolume();
	VScrollBar* MVL=MMenu.addGP_ScrollBarL(NULL,X0,320+DY+10-13,100,MidiSound,BTNS.GPID,12,LX,12,0,0);
	ComboBox* VMode=MMenu.addGP_ComboBox(NULL,240,240-16-13,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VMode->CurLine=100;
	GP_Button* REC=MMenu.addGP_Button(NULL,240,496,BTNS.GPID,20,19);
	REC->OnUserClick=&MMItemChoose;
	REC->UserParam=77;
	bool RECSTATE=RecordMode;
	GP_Button* EDITPAN=MMenu.addGP_Button(NULL,270,496,BTNS.GPID,24,23);
	InputBox* IBREC=MMenu.addInputBox(NULL,275,496,RECFILE,120,240,26,&YellowFont,&WhiteFont);
	for(int i=0;i<NModes;i++){
		char cc[30];
		sprintf(cc,"%dx%d",ModeLX[i],ModeLY[i]);
		VMode->AddLine(cc);
		if(exRealLx==ModeLX[i]&&exRealLy==ModeLY[i])VMode->CurLine=i;
	};
	if(VMode->CurLine==100)VMode->CurLine=0;
	ComboBox* FMode=MMenu.addGP_ComboBox(NULL,240,421+10-13,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	FMode->AddLine(SLOWMOD);
	FMode->AddLine(FASTMOD);
	FMode->CurLine=exFMode;

	ComboBox* MUS=MMenu.addGP_ComboBox(NULL,240,240-16+80-3-13,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	MUS->AddLine(GetTextByID("NOCD"));
	MUS->AddLine(GetTextByID("NATMUS"));
	MUS->AddLine(GetTextByID("RNDMUS"));
	MUS->CurLine=PlayMode;

	ItemChoose=-1;
	int pp=1;
	KeyPressed=0;
	int PrevPlayMode=MUS->CurLine!=0;
	int ppp=PlayMode;
	do{
		if(RECSTATE){
			EDITPAN->Enabled=1;
			IBREC->Enabled=1;
			REC->ActiveFrame=22;
			REC->PassiveFrame=21;
			IBREC->Active=1;
		}else{
			EDITPAN->Enabled=0;
			IBREC->Enabled=0;
			REC->ActiveFrame=20;
			REC->PassiveFrame=19;
			IBREC->Active=0;
		};
		P1->Visible=P1->MouseOver;
		P2->Visible=P2->MouseOver;
		P3->Visible=P3->MouseOver;
		P4->Visible=P4->MouseOver;
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(ItemChoose==77){
			RECSTATE=!RECSTATE;
			ItemChoose=-1;
		};
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
		SetCDVolume(MVL->SPos);
		if(PrevPlayMode!=(MUS->CurLine!=0)){
			PlayMode=MUS->CurLine;
			if(MUS->CurLine)PlayRandomTrack();
			else StopPlayCD();
			PrevPlayMode=MUS->CurLine!=0;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		FPSTime=100-HB->SPos;
		ScrollSpeed=SSP->SPos+2;
		exRealLx=ModeLX[VMode->CurLine];
		exRealLy=ModeLY[VMode->CurLine];
		WarSound=SVL->SPos;
		MidiSound=MVL->SPos;
		PlayMode=MUS->CurLine;
		exFMode=FMode->CurLine;
		RecordMode=RECSTATE;
	}else{
		PlayMode=ppp;
		if((PlayMode!=0)!=PrevPlayMode){
			if(PlayMode)PlayRandomTrack();
			else StopPlayCD();
		};
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	return false;
};
bool ProcessGameOptions(){
	LocalGP BTNS("Interface\\Options_for_Game");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	LoadPointer("cur_mn.rlc");
	//SQPicture MnPanel("Interface\\Background_options.bmp");
	int dx=-63+6+((RealLx-484)>>1);
	int dy=-166+((RealLy-425)>>1);
	DialogsSystem MMenu(dx,dy);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,1))>>1)-85-125;
	//int dy=(RealLy-GPS.GetGPHeight(BTNS.GPID,1))>>1;
	GPPicture* PIC=MMenu.addGPPicture(NULL,63,166,BTNS.GPID,14);
	GPS.ShowGP(dx+63,dy+166,BTNS.GPID,13,0);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,1);

	GP_Button* OkBtn=MMenu.addGP_Button(NULL,113,534+11,BTNS.GPID,8,9);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;

	GP_Button* ExitBtn=MMenu.addGP_Button(NULL,333,534+11,BTNS.GPID,10,11);
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;

	if(FPSTime>100)FPSTime=100;
	if(FPSTime<0)FPSTime=0;
	//game speed (#3)
	if(ScrollSpeed<2)ScrollSpeed=2;
	int X0=244-2;
	int LX=484-244+20;
	int DY=10;
	GPPicture* P1=MMenu.addGPPicture(NULL,240,317+11,BTNS.GPID,15);
	GPPicture* P2=MMenu.addGPPicture(NULL,240,343+11,BTNS.GPID,16);
	GPPicture* P3=MMenu.addGPPicture(NULL,240,447+11,BTNS.GPID,17);
	GPPicture* P4=MMenu.addGPPicture(NULL,240,473+11,BTNS.GPID,18);
	P1->Visible=0;
	P2->Visible=0;
	P3->Visible=0;
	P4->Visible=0;
	VScrollBar* HB=MMenu.addGP_ScrollBarL(NULL,X0,476+DY+11,100,100-FPSTime,BTNS.GPID,12,LX,12,0,0);
	//scroll speed (#4)
	VScrollBar* SSP=MMenu.addGP_ScrollBarL(NULL,X0,450+DY+11,8,ScrollSpeed-2,BTNS.GPID,12,LX,12,0,0);
	//sound volume (#1)
	MidiSound=GetCDVolume();
	VScrollBar* SVL=MMenu.addGP_ScrollBarL(NULL,X0,346+DY+11,100,WarSound,BTNS.GPID,12,LX,12,0,0);
	//music volume (#2)
	VScrollBar* MVL=MMenu.addGP_ScrollBarL(NULL,X0,320+DY+11,100,MidiSound,BTNS.GPID,12,LX,12,0,0);
	ComboBox* VMode=MMenu.addGP_ComboBox(NULL,240,240-15,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VMode->CurLine=100;
	for(int i=0;i<NModes;i++){
		char cc[30];
		sprintf(cc,"%dx%d",ModeLX[i],ModeLY[i]);
		VMode->AddLine(cc);
		if(RealLx==ModeLX[i]&&RealLy==ModeLY[i])VMode->CurLine=i;
	};
	if(VMode->CurLine==100)VMode->CurLine=0;
	ComboBox* FMode=MMenu.addGP_ComboBox(NULL,240,421+11,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	FMode->AddLine(SLOWMOD);
	FMode->AddLine(FASTMOD);
	FMode->CurLine=exFMode;

	ComboBox* MUS=MMenu.addGP_ComboBox(NULL,240,240-15+80-3,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	MUS->AddLine(GetTextByID("NOCD"));
	MUS->AddLine(GetTextByID("NATMUS"));
	MUS->AddLine(GetTextByID("RNDMUS"));
	MUS->CurLine=PlayMode;

	ItemChoose=-1;
	//SVL->SPos=WarSound;
	//MVL->SPos=MidiSound;
	//int pp=1;
	int PrevPlayMode=MUS->CurLine!=0;
	KeyPressed=0;
	int ppp=PlayMode;
	int StartTime=GetTickCount();
	do{
		if(GetTickCount()-StartTime>10000&&NPlayers>1){
			ItemChoose=mcmCancel;
			ShowOptMessage("#LOOKOPT",0);
			//SpecCmd=199;
			//IAmLeft();
		};
		P1->Visible=P1->MouseOver;
		P2->Visible=P2->MouseOver;
		P3->Visible=P3->MouseOver;
		P4->Visible=P4->MouseOver;
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		SetCDVolume(MVL->SPos);
		if(PrevPlayMode!=(MUS->CurLine!=0)){
			PlayMode=MUS->CurLine;
			if(MUS->CurLine)PlayRandomTrack();
			else StopPlayCD();
			PrevPlayMode=MUS->CurLine!=0;
		};
		//if(pp){
		//	SlowLoadPalette("2\\agew_1.pal");
		//	pp=0;
		//};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		FPSTime=100-HB->SPos;
		ScrollSpeed=SSP->SPos+2;
		exFMode=FMode->CurLine;
		if(RealLx!=ModeLX[VMode->CurLine]||RealLy!=ModeLY[VMode->CurLine])SetGameDisplayMode(ModeLX[VMode->CurLine],ModeLY[VMode->CurLine]);
		WarSound=SVL->SPos;
		MidiSound=MVL->SPos;
		PlayMode=MUS->CurLine;
	}else{
		PlayMode=ppp;
		if((PlayMode!=0)!=PrevPlayMode){
			if(PlayMode)PlayRandomTrack();
			else StopPlayCD();
		};
	};
	return false;
};
bool CreateMultiplaterInterface();
void ProcessMissions();
void PlayVideo();
extern char BuildVersion[32];
void SlideShow();
void ShowPreview();
extern byte PlayGameMode;
extern bool RetryVideo;
int GetRndVid(int N);
void CloseLogin();
void processMLoadGame();
bool InMainMenuLoop=0;
extern bool RejectThisPlayer;
//#define DONOTHING
int processMainMenu(){
	
	int StTime=GetTickCount();
	CloseMPL();
	SetDarkPalette();
	InGame=false;
	GameMode=1;
	SetRLCWindow(0,0,RealLx,RSCRSizeY,SCRSizeX);
	NPlayers=1;
	MultiplayerStart=false;
	ItemChoose=-1;
	CBar(0,0,RealLx,RSCRSizeY,0);
	
	//--------------------------------------------------------------------
	//Loading resources.
	
	LocalGP BTNS("Interface\\Main_Menu");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	LoadPointer("cur_mn.rlc");
	SQPicture MnPanel("Interface\\Background_Main_Menu.bmp");
	DialogsSystem MMenu(0,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	GP_Button* Single=MMenu.addGP_Button(NULL,76,140,BTNS.GPID,0,1);
#ifndef DONOTHING
	Single->UserParam=mcmSingle;
	Single->OnUserClick=&MMItemChoose;
	Single->Hint=GetTextByID("MMSINGLE");
	Single->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#endif
	GP_Button* Multi=MMenu.addGP_Button(NULL,76,140+82,BTNS.GPID,2,3);
#ifndef DONOTHING
	Multi->UserParam=mcmMulti;
	Multi->OnUserClick=&MMItemChoose;
	Multi->Hint=GetTextByID("MMMULTI");
	Multi->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#endif
	GP_Button* Load=MMenu.addGP_Button(NULL,76,140+82*2,BTNS.GPID,4,5);
#ifndef DONOTHING
	Load->UserParam=mcmLoad;
	Load->OnUserClick=&MMItemChoose;
	Load->Hint=GetTextByID("MMLOAD");
	Load->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#endif
//#ifdef INETTESTVERSION
//	Load->UserParam=-1;
//#endif
	GP_Button* Options=MMenu.addGP_Button(NULL,76,140+82*3,BTNS.GPID,6,7);
#ifndef DONOTHING
	Options->UserParam=mcmEdit;
	Options->OnUserClick=&MMItemChoose;
	Options->Hint=GetTextByID("MMOPTIONS");
	Options->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#endif
	GP_Button* Video=MMenu.addGP_Button(NULL,76,140+82*4,BTNS.GPID,8,9);
	Video->UserParam=mcmVideo;
//#ifdef INETTESTVERSION
//	Video->UserParam=-1;
//#endif
#ifndef DONOTHING
	Video->OnUserClick=&MMItemChoose;
	Video->Hint=GetTextByID("MMVIDEO");
	Video->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
#endif
	GP_Button* Exit=MMenu.addGP_Button(NULL,76,140+82*5,BTNS.GPID,10,11);
	Exit->UserParam=mcmExit;
	Exit->OnUserClick=&MMItemChoose;
	Exit->Hint=GetTextByID("MMEXIT");
	Exit->AssignSound(GETS("@MOUSESOUND"),MOUSE_SOUND);
	MMenu.addTextButton(NULL,1024-GetRLCStrWidth(BuildVersion,&SmallYellowFont1),748,BuildVersion,&SmallYellowFont1,&SmallYellowFont1,&SmallYellowFont1,0);
	int nn=0;
loop1:
	if(CurrentCampagin!=-1&&CurrentMission!=-1){
		ProcessCampagins(CurrentCampagin);
		nn=1;
		if(ItemChoose==mcmSingle)return ItemChoose;
		//SlowUnLoadPalette("1\\agew_1.pal");
	};
	if(nn){
		//SlowUnLoadPalette("1\\agew_1.pal");
		nn=0;
	};
	ItemChoose=-1;
	LoadFog(2);
	StTime=GetTickCount();
	CloseLogin();
	LastKey=0;
	KeyPressed=0;
	RejectThisPlayer=0;
	do{
		if(ADDSH==1&&bActive&&(GetTickCount()-StTime>30000||RetryVideo)&&!(RUNMAPEDITOR||RUNUSERMISSION)){
			GFILE* f=Gopen("Demo\\demo.run","r");
			if(f){
				int N;
				int z=Gscanf(f,"%d",&N);
				if(z==1){
					int M=GetRndVid(N);
					char NAME[64];
					for(int i=0;i<M;i++)Gscanf(f,"%s",NAME);
					Gscanf(f,"%s",NAME);
					RGAME.ReadStream(NAME);
					if(RGAME.Size){
						PlayGameMode=1;
						RecordMode=0;
						ItemChoose=43;
						RetryVideo=1;
						KeyPressed=0;
					};
				};
				Gclose(f);
				StTime=GetTickCount();
			};
		};
		InMainMenuLoop=1;
		ProcessMessages();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		InMainMenuLoop=0;
		if(!nn){
			SlowLoadPalette("2\\agew_1.pal");
			LoadFog(2);
		};
		nn++;
		//if(ItemChoose==mcmVideo&&!(GetKeyState(VK_CONTROL)&0x8000))ItemChoose=-1;
		if(RUNMAPEDITOR){
			ItemChoose=mcmVideo;
		};
		if(RUNUSERMISSION){
			ItemChoose=111;
		};
		if(TOTALEXIT)ItemChoose=mcmExit;
	}while(ItemChoose==-1);
	if(ItemChoose==mcmSingle){
		SlowUnLoadPalette("2\\agew_1.pal");
		if(CommEnterName()){
			int res=MM_ProcessSinglePlayer();
			if(res==5)goto loop1;
		};
	};
#ifdef MAKE_PTC
	if(ItemChoose==mcmMulti){
		SlowUnLoadPalette("2\\agew_1.pal");
		int res=MM_ProcessMultiPlayer();
		if(res==5)goto loop1;
	};
#endif
	if(ItemChoose==mcmVideo){
		ShowLoading();
		LOADNATMASK=0xFFFFFFFF;
		PrepareEditMedia(0);
		ItemChoose=mcmSingle;
	};
	if(ItemChoose==mcmEdit){
		SlowUnLoadPalette("2\\agew_1.pal");
		ProcessMenuOptions();
		goto loop1;
	};
	if(ItemChoose==mcmLoad){
		SlowUnLoadPalette("2\\agew_1.pal");
		processMLoadGame();
	};
	if(ItemChoose==mcmExit){
		SlowUnLoadPalette("2\\agew_1.pal");
		SlideShow();
	};
	if(ItemChoose==43){
		EditMapMode=0;
		ItemChoose=mcmSingle;
	};
	if(ItemChoose==111){
		if(!PlName[0])strcpy(PlName,"Player");
		memset(PINFO,0,sizeof PINFO);
		strcpy(PINFO[0].name,PlName);
		EditMapMode=0;
		ItemChoose=mcmSingle;
		strcpy(CurrentMap,USERMISSPATH);
		CreateNationalMaskForMap(CurrentMap);
		CurrentCampagin=-1;
		CurrentMission=-1;
		PrepareGameMedia(0,0);
		InitGame();
		ItemChoose=mcmSingle;
		RUNUSERMISSION=0;
	};
	/*

	SQPicture MMGround("MnMenu0.bpx");
	RLCFont menu32yw(GETS("@MMFONT0"));
	RLCFont menu32w(GETS("@MMFONT1"));
	MMGround.Draw(0,0);
	SQPicture MnPanel("MnMenu01.bpx");
	
	int mmlx=MnPanel.PicPtr[0];
	int mmly=MnPanel.PicPtr[1];
	PlayerMenuMode=1;
	FlipPages();
	//IMPLEMENTATION
	DialogsSystem MMenu(0,0);
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	int mmnx=GETV("MMMENUX");
	TextButton* ExitBtn=MMenu.addTextButton(PIC,mmnx,GETV("MMEXITY"),GETS("@MMEXIT"),&menu32w,&menu32yw,&menu32yw,1);
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;
	TextButton* BTN1=MMenu.addTextButton(PIC,mmnx,GETV("MMSINGLEY"),GETS("@MMSINGLE"),&menu32w,&menu32yw,&menu32yw,1);
	BTN1->UserParam=mcmSingle;
	BTN1->OnUserClick=&MMItemChoose;
	TextButton* BTN2=MMenu.addTextButton(PIC,mmnx,GETV("MMNETY"),GETS("@MMNET"),&menu32w,&menu32yw,&menu32yw,1);
	BTN2->UserParam=mcmMulti;
	BTN2->OnUserClick=&MMItemChoose;
	TextButton* BTNL=MMenu.addTextButton(PIC,mmnx,GETV("MMLOADGY"),GETS("@MMLOADG"),&menu32w,&menu32yw,&menu32yw,1);
	BTNL->UserParam=mcmLoad;
	BTNL->OnUserClick=&MMItemChoose;
	TextButton* BTN4=MMenu.addTextButton(PIC,mmnx,GETV("MMEDITY"),GETS("@MMEDIT"),&menu32w,&menu32yw,&menu32yw,1);
	BTN4->UserParam=mcmEdit;
	BTN4->OnUserClick=&MMItemChoose;
	TextButton* BTN3=MMenu.addTextButton(PIC,mmnx,GETV("MMVIDEOY"),GETS("@MMVIDEO"),&menu32w,&menu32yw,&menu32yw,1);
	BTN3->UserParam=mcmVideo;
	BTN3->OnUserClick=&MMItemChoose;
	if(CHKV("MMHELPY")){
		TextButton* BTN5=MMenu.addTextButton(PIC,mmnx,GETV("MMHELPY"),GETS("@MMHELP"),&menu32w,&menu32yw,&menu32yw,1);
	};
	int nn=0;
	do{
		ProcessMessages();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(!nn){
			SlowLoadPalette("1w.pal");
			//LoadFog(1);
		};
		nn++;
	}while(ItemChoose==-1);
	LoadPointer("cursor_y.rlc");
	if(ItemChoose==mcmSingle)processSinglePlayer();
	if(ItemChoose==mcmEdit){
		PrepareEditMedia(0);
		ItemChoose=mcmSingle;
	};
	if(ItemChoose==mcmLoad){
		processMLoadGame();
	};
	if(ItemChoose==mcmVideo){
		ProcessMissions();
	};
	if(ItemChoose==mcmMulti){
		processMultiplayer();
	};
	//if(ItemChoose==mcmMulti)processMultiplayer();
	*/
	GameMode=0;
	//SlowUnLoadPalette("1w.pal");
	return ItemChoose;

};
//--------------=< G A M E   S C R E E N >=------------//
extern int PrpX;
extern int PrpY;
extern int PrpNx;
extern int PrpNy;
extern int AblX;
extern int AblY;
extern int AblNx;
extern int AblNy;
extern int IconLx;
extern int AddIconLx;
extern int AddIconLy;
//extern int IconLx;
extern int IconLy;
DialogsSystem GSYS(0,0);
SimpleDialog* GVPort;
SimpleDialog* MiniVPort;
SimpleDialog* AblVPort;
SimpleDialog* PrpVPort;
void GSYSDRAW(){
	GSYS.RefreshView();
};
//Picture* Pan1;
//Picture* Pan2;
//Picture* Pan3;
ColoredBar* Pan4;
ColoredBar* Pan5;
bool GameExit;
int MenuType;
bool MakeMenu;

int NNames;
char* names[128];
char* fnames[128];
int   serials[128];
void ClearNames(){
	for(int i=0;i<128;i++)names[i]=NULL;
	NNames=0;
};
void FreeNames(){
	for(int i=0;i<128;i++)if(names[i]){
		free(names[i]);
		free(fnames[i]);
		names[i]=NULL;
		fnames[i]=NULL;
	};
	NNames=0;
};
void ErrorBox(char* str){
	return;
};
extern int sfVersion;
#ifdef MAKE_PTC
void InstallName(ListBox* LB,WIN32_FIND_DATA* FD,char* StartDir){
	char CCC[256];
	sprintf(CCC,"%s%s",StartDir,FD->cFileName);
	ResFile ff1=RReset(CCC);
	if(ff1!=INVALID_HANDLE_VALUE){
		int sig,lap;
		RBlockRead(ff1,&sig,4);
		if(sig=='FSAK'||sig=='[CER'||sig==']CER'){
			if(sig=='[CER'||sig==']CER')sig=sfVersion;
			else{
				RBlockRead(ff1,&sig,4);
				RBlockRead(ff1,&lap,4);
			};
			if(sig==sfVersion&&NNames<512){
				//int nlen=0;
				//RBlockRead(ff1,&nlen,2);
				//nlen=0;
				//RBlockRead(ff1,&nlen,1);
				//RBlockRead(ff1,nam,nlen);
				RClose(ff1);
				LB->AddItem(CCC,NNames);
				//names[NNames]=new char[strlen(nam)+1];
				fnames[NNames]=new char[strlen(CCC)+1];
				//serials[NNames]=lap;
				//strcpy(names[NNames],nam);
				strcpy(fnames[NNames],CCC);
				NNames++;
			}else RClose(ff1);
		}else RClose(ff1);
	};
};
#endif
#ifdef MAKE_PTC
SFLB_DLLEXPORT SFLB_CreateGamesList(ListBox* LB){
	WIN32_FIND_DATA FD;
	ClearNames();
	HANDLE HF=FindFirstFile("*.sav",&FD);
	if(HF!=INVALID_HANDLE_VALUE){
		InstallName(LB,&FD,"");
		while(FindNextFile(HF,&FD))InstallName(LB,&FD,"");
	};
};
#endif
void CreateRecList(ListBox* LB){
	WIN32_FIND_DATA FD;
	//ClearNames();
	HANDLE HF=FindFirstFile("*.rec",&FD);
	if(HF!=INVALID_HANDLE_VALUE){
		InstallName(LB,&FD,"");
		while(FindNextFile(HF,&FD))InstallName(LB,&FD,"");
		FindClose(HF);
	};
	HF=FindFirstFile("Autorecord\\*.rec",&FD);
	if(HF!=INVALID_HANDLE_VALUE){
		InstallName(LB,&FD,"Autorecord\\");
		while(FindNextFile(HF,&FD))InstallName(LB,&FD,"Autorecord\\");
		FindClose(HF);
	};
};
//----------------LOAD GAME--------------//
void CmdLoadNetworkGame(byte NI,int ID,char* Name);
SFLB_DLLEXPORT SFLB_LoadGame(char* fnm,bool LoadNation);
void OldProcessGLoadGame(){
	
};
extern EXBUFFER EBufs[MaxPL];
DWORD MAPREPL[8];
bool CheckFileIdentity(char* Name){
	if(NPlayers==1)return true;
	DWORD FID[512];
	FID[0]='FIDN';
	DWORD S=GetMapSUMM(Name);
	FID[1]=S;
	if(FID[1]==0xFFFFFFFF)return false;
	memset(FID+2,0,128);
	strcpy((char*)(FID+2),Name);
	memset(MAPREPL,0,8*4);
	for(int i=0;i<NPlayers;i++)
		if(PINFO[i].PlayerID==MyDPID)MAPREPL[i]=S;
	SendToAllPlayers(128+8,FID);
	int t0=GetTickCount();
	int t1=t0;
	do{
		if(GetTickCount()-t1>500){
			t1=GetTickCount();
			SendToAllPlayers(128+8,FID);
		};
		ProcessMessages();
		int OK=1;
		for(int i=0;i<NPlayers;i++)if(EBufs[i].Enabled){
			if(MAPREPL[i]){
				if(MAPREPL[i]!=S)return false;
			}else OK=0;
		};
		if(OK)return true;
	}while(GetTickCount()-t0<10000);
	return false;
};
void ProcessGLoadGame(){
	LocalGP BTNS("Interface\\G_Load_Game");
	LocalGP SCROL("Interface\\GScroll");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	//LoadPointer("cur_mn.rlc");
	int dx=(RealLx-470)>>1;
	int dy=(RealLy-415)>>1;
	DialogsSystem MMenu(dx,dy);
	GPS.ShowGP(dx,dy,BTNS.GPID,4,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	MMenu.addGPPicture(NULL,0,0,BTNS.GPID,5);
	VScrollBar* VSB=MMenu.addNewGP_VScrollBar(NULL,436,55,276,1,0,SCROL.GPID,0);
	ListBox* LB=MMenu.addGP_ListBox(NULL,29,61,10,BTNS.GPID,6,26,&WhiteFont,&YellowFont,VSB);

	//VScrollBar* VS=DSY.addVScrollBar(PIC1,LB->x-DSY.BaseX+LB->oneLx-1,1+LB->y-DSY.BaseY,1000,4,&sb_up_d,&sb_up_e,&sb_up_p,&sb_dn_d,&sb_dn_e,&sb_dn_p,&sb_vbare,&sb_vbar,&sb_btn);
	//LB->VS=VS;226x241
	GP_Button* OkBtn=MMenu.addGP_Button(NULL,49,353,BTNS.GPID,0,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=MMenu.addGP_Button(NULL,269,353,BTNS.GPID,2,3);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	DLL1(SFLB_CreateGamesList,LB);
	ItemChoose=-1;
	int pp=1;
	int LastCTime=GetRealTime();
	LastKey=0;
	int StartTime=GetTickCount();
	do{
		if(GetTickCount()-StartTime>10000&&NPlayers>1){
			ItemChoose=mcmCancel;
			ShowOptMessage("#LOOKOPT",0);
			//SpecCmd=199;
			//IAmLeft();
		};
		MMenu.MarkToDraw();
		ProcessMessages();
		StdKeys();
		if(LB->CurItem==-1){
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		}else OkBtn->Enabled=true;
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk&&LB->CurItem!=-1){
		//if(CheckFileIdentity(fnames[LB->CurItem])){
			strcpy(SaveFileName,fnames[LB->CurItem]);
			if(NPlayers>1)CmdLoadNetworkGame(MyNation,serials[LB->CurItem],SaveFileName);
			else DLL2(SFLB_LoadGame,SaveFileName,1);
		//}else{
		//	AssignHint1(GetTextByID("SFNID"),100,1);
		//};
	};
	ContinueGame=true;
	FreeNames();
	ClearMStack();
};
void ProcessFranceMission(){
	SQPicture Pan1("Interface\\Missions\\MTFrance_Back_1.bmp");
	SQPicture Pan2("Interface\\Missions\\MTFrance_Back_2.bmp");
	SlowUnLoadPalette("1\\agew_1.pal");
	Pan1.Draw(0,0);
	FlipPages();
	SlowLoadPalette("1\\agew_1.pal");
	int t0=GetRealTime();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(!(GetRealTime()-t0>15000||Lpressed||KeyPressed));
	if(LastKey==27)return;
	LastKey=0;
	SlowUnLoadPalette("1\\agew_1.pal");
	Pan2.Draw(0,0);
	FlipPages();
	SlowLoadPalette("1\\agew_1.pal");
	t0=GetRealTime();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(!(GetRealTime()-t0>15000||Lpressed||KeyPressed));
	if(LastKey==27)return;

	strcpy(CurrentMap,MISSLIST.MISS[0].MapName);
	CreateNationalMaskForMap(CurrentMap);
	CurrentCampagin=-1;
	CurrentMission=-1;
	PrepareGameMedia(0,0);
	InitGame();
	ItemChoose=mcmSingle;
	//InitExplosions();
	MISSLIST.CurrentMission=0;
	SCENINF.Load(MISSLIST.MISS[0].DLLPath,MISSLIST.MISS[0].Description);
};
#ifdef MAKE_PTC
void processMLoadGame(){
	//SlowUnLoadPalette("1\\agew_1.pal");
	LocalGP BTNS("Interface\\Load_Game");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	LoadPointer("cur_mn.rlc");
	SQPicture MnPanel("Interface\\Background_Load_Game.bmp");
	DialogsSystem MMenu(0,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	LoadFog(2);
	//int dx=((RealLx-GPS.GetGPWidth(BTNS.GPID,1))>>1)-85-125;
	//int dy=(RealLy-GPS.GetGPHeight(BTNS.GPID,1))>>1;
	Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,1);
	VScrollBar* VS=MMenu.addNewGP_VScrollBar(NULL,500,166,403,1000,0,BTNS.GPID,7);
	ListBox* LB=MMenu.addGP_ListBox(NULL,92,172,15,BTNS.GPID,15,26,&WhiteFont,&YellowFont,VS);
	LB->M_Over=4;
	LB->Active=true;
	//LB->VS=VS;
	GP_Button* OkBtn=MMenu.addGP_Button(NULL,113,594,BTNS.GPID,0,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=MMenu.addGP_Button(NULL,333,594,BTNS.GPID,2,3);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;


	DLL1(SFLB_CreateGamesList,LB);
	CreateRecList(LB);
	ItemChoose=-1;
	int pp=1;
	int LastCTime=GetRealTime();
	VS->ScrDy=14;
	KeyPressed=0;
	SetMyNation(0);
	do{
		MMenu.MarkToDraw();
		ProcessMessages();
		StdKeys();
		if(LB->CurItem==-1||!LB->NItems){
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		}else OkBtn->Enabled=true;
		OkBtn->Visible=OkBtn->Enabled;
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		/*
		if(ItemChoose==1||(UpBtn->MouseOver&&realLpressed&&GetRealTime()-LastCTime>180)){//up
			if(LB->FLItem>0)LB->FLItem--;
			LastCTime=GetRealTime();
			if(ItemChoose!=-1)LastCTime+=600;
			ItemChoose=-1;
			Lpressed=false;
		};
		if(ItemChoose==2||(DnBtn->MouseOver&&realLpressed&&GetRealTime()-LastCTime>180)){//dn
			if(LB->NItems-LB->FLItem>LB->ny)LB->FLItem++;
			LastCTime=GetRealTime();
			if(ItemChoose!=-1)LastCTime+=600;
			ItemChoose=-1;
			Lpressed=false;
		};
		*/
		if(pp){
			SlowLoadPalette("2\\agew_1.pal");
			pp=0;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk&&LB->CurItem!=-1){
		ShowLoading();
		PrepareToGame();
		if(strstr(fnames[LB->CurItem],".rec")||strstr(fnames[LB->CurItem],".REC")){
			RGAME.ReadStream(fnames[LB->CurItem]);
			if(RGAME.Size){
					PlayGameMode=2;
					//ItemChoose=43;
					//RetryVideo=1;
					KeyPressed=0;
					EditMapMode=0;
					ItemChoose=mcmSingle;
				};
		}else{
			DLL2(SFLB_LoadGame,fnames[LB->CurItem],1);
			HideFlags();
			ContinueGame=true;
			ItemChoose=mcmSingle;
		};
	}else{
		SlowUnLoadPalette("2\\agew_1.pal");
	};
	FreeNames();
};
#endif
//----------------SAVE GAME--------------//
void CmdSaveNetworkGame(byte NI,int ID,char* Name);
bool CheckName(char* str){
	for(int i=0;i<NNames;i++)if(strstr(names[i],str))return false;
	return true;
};
bool ChangeNation;
bool MultiTvar;
extern int FogMode;
bool EnterVal(int * val,char* Message){
	Lpressed=false;
	char passw[128];
	passw[0]=0;
	ItemChoose=-1;
	sprintf(passw,"%d",*val);
	DialogsSystem DSY(smapx+(nsmaplx<<4)-(288>>1),smapy+(mul3(nsmaply)<<2)-(288>>1));
	//Picture* PIC1=DSY.addPicture(NULL,0,0,&y288x128,&y288x128,&y288x128);
	TextButton* LoadBtn=DSY.addTextButton(NULL,288>>1,5,Message,&FActive,&FPassive,&FDisable,1);
	InputBox* IB=DSY.addInputBox(NULL,30,45,passw,20,224,28,&WhiteFont,&WhiteFont);
	IB->Active=true;
	TextButton* OkBtn=DSY.addTextButton(NULL,55+164/2,90,"OK",&WhiteFont,&YellowFont,&YellowFont,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	KeyPressed=false;
	do{
		DrawStdBar(DSY.BaseX,DSY.BaseY,DSY.BaseX+288,DSY.BaseY+128);
		DSY.MarkToDraw();
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13){
				ItemChoose=mcmOk;
				KeyPressed=false;
			};
			if(LastKey==27){
				ItemChoose=mcmCancel;
				KeyPressed=false;
			};
		};
		DSY.ProcessDialogs();
		DSY.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		int z=sscanf(passw,"%d",val);
		if(z==0)return false;
		else return true;
	}else return false;
};
bool EnterStr(char * str,char* Message){
	Lpressed=false;
	char passw[128];
	passw[0]=0;
	ItemChoose=-1;
	DialogsSystem DSY(smapx+(nsmaplx<<4)-(288>>1),smapy+(mul3(nsmaply)<<2)-(288>>1));
	//Picture* PIC1=DSY.addPicture(NULL,0,0,&y288x128,&y288x128,&y288x128);
	TextButton* LoadBtn=DSY.addTextButton(NULL,288>>1,5,Message,&YellowFont,&YellowFont,&YellowFont,1);
	InputBox* IB=DSY.addInputBox(NULL,30,45,str,20,224,28,&WhiteFont,&WhiteFont);
	IB->Active=true;
	TextButton* OkBtn=DSY.addTextButton(NULL,55+164/2,90,"OK",&WhiteFont,&YellowFont,&YellowFont,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	KeyPressed=false;
	do{
		DrawStdBar(DSY.BaseX,DSY.BaseY,DSY.BaseX+288,DSY.BaseY+128);
		DSY.MarkToDraw();
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13){
				ItemChoose=mcmOk;
				KeyPressed=false;
			};
			if(LastKey==27){
				ItemChoose=mcmCancel;
				KeyPressed=false;
			};
		};
		DSY.ProcessDialogs();
		DSY.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		return true;
	}else return false;
};
void MemScreenPart(int x,int y,int lx,int ly,byte* Ptr){
	for(int yy=0;yy<ly;yy++){
		int ofs=x+(y+yy)*ScrWidth;
		memcpy(Ptr,((byte*)ScreenPtr)+ofs,lx);
		Ptr+=lx;
	};
};
int EnterHi(int * val,int Type){
	
	LocalGP LONGBOX("Interface\\LongBox0");
	Lpressed=false;
	char passw[128];
	passw[0]=0;
	ItemChoose=-1;
	sprintf(passw,"%d",*val);
	int LX=400;
	int LY=118;
	byte* PTR=new byte[(LX+64)*(LY+200)];
	MemScreenPart(((RealLx-LX)>>1)-32,((RealLy-LY)>>1)-16,LX+64,LY+200,PTR);
	DialogsSystem DSY((RealLx-LX)>>1,(RealLy-LY)>>1);
	DSY.addBPXView(NULL,-32,-16,LX+64,LY+200,1,1,1,PTR,NULL);
	DSY.addBorder(0,0,LX,LY,0,1);
	DSY.addGPPicture(NULL,LX/4-75,LY+6,LONGBOX.GPID,8);
	DSY.addGPPicture(NULL,LX/4-75,LY+6,LONGBOX.GPID,11);
	DSY.addGPPicture(NULL,3*LX/4-75,LY+6,LONGBOX.GPID,8);
	DSY.addGPPicture(NULL,3*LX/4-75,LY+6,LONGBOX.GPID,11);
	GP_TextButton* OkBtn=DSY.addGP_TextButton(NULL,LX/4-75+10,LY+6+21,GetTextByID("@OK"),LONGBOX.GPID,9,&WhiteFont,&YellowFont);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_TextButton* CancelBtn=DSY.addGP_TextButton(NULL,3*LX/4-75+10,LY+6+21,GetTextByID("@CANCEL"),LONGBOX.GPID,9,&WhiteFont,&YellowFont);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	//Picture* PIC1=DSY.addPicture(NULL,0,0,&y288x256,&y288x256,&y288x256);
	DSY.addTextButton(NULL,6,6,GetTextByID("$#HIHDR"),&YellowFont,&YellowFont,&YellowFont,0);
	TextButton* LoadBtn=DSY.addTextButton(NULL,10,87,GetTextByID("$#HEIGHT"),&YellowFont,&YellowFont,&YellowFont,0);
	InputBox* IB=DSY.addInputBox(NULL,120,80,passw,20,224,28,&WhiteFont,&WhiteFont);
	ColoredBar* CBR=DSY.addColoredBar(120,80,LX-140,23,0x4c);
	CBR->Style=1;
	DSY.addTextButton(NULL,10,51,GetTextByID("$#ACTION"),&YellowFont,&YellowFont,&YellowFont,0);
	ComboBox* CB=DSY.addGP_ComboBoxDLX(NULL,120,44,LX-140,LONGBOX.GPID,0,9,9,&WhiteFont,&YellowFont,NULL);
	CB->AddLine("Cubic line");
	CB->AddLine("Quad. line");
	CB->AddLine("Softing");
	CB->AddLine("Road1");
	CB->AddLine("Road2");
	CB->AddLine("Road3");
	CB->CurLine=Type-1;
	IB->Active=true;
	
	KeyPressed=false;
	do{
		//DrawStdBar(DSY.BaseX,DSY.BaseY,DSY.BaseX+288,DSY.BaseY+256);
		DSY.MarkToDraw();
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13){
				ItemChoose=mcmOk;
				KeyPressed=false;
			};
			if(LastKey==27){
				ItemChoose=mcmCancel;
				KeyPressed=false;
			};
		};
		DSY.ProcessDialogs();
		DSY.RefreshView();
	}while(ItemChoose==-1);
	free(PTR);
	if(ItemChoose==mcmOk){
		int z=sscanf(passw,"%d",val);
		if(z==0)return false;
		else return CB->CurLine+1;
	}else return false;
};
DLLEXPORT
void ShowVictory();
DLLEXPORT
void SelChangeNation(byte SrcNat,byte DstNat);
void EnterChat(){
	if(NPlayers>1)return;
	Lpressed=false;
	char passw[128];
	passw[0]=0;
	ItemChoose=-1;
	DialogsSystem DSY(smapx+(nsmaplx<<4)-(288>>1),smapy+(mul3(nsmaply)<<2)-(288>>1));
	//Picture* PIC1=DSY.addPicture(NULL,0,0,&y288x128,&y288x128,&y288x128);
	TextButton* LoadBtn=DSY.addTextButton(NULL,288>>1,5,"Enter password:",&FActive,&FPassive,&FDisable,1);
	InputBox* IB=DSY.addInputBox(NULL,30,45,passw,20,224,28,&WhiteFont,&WhiteFont);
	IB->Active=true;
	TextButton* OkBtn=DSY.addTextButton(NULL,55+164/2,90,"OK",&WhiteFont,&YellowFont,&YellowFont,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	KeyPressed=false;
	do{
		DrawStdBar(DSY.BaseX,DSY.BaseY,DSY.BaseX+288,DSY.BaseY+128);
		DSY.MarkToDraw();
		ProcessMessages();
		if(KeyPressed&&LastKey==13){
			ItemChoose=mcmOk;
			KeyPressed=false;
		};
		DSY.ProcessDialogs();
		DSY.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		if(!strcmp(passw,"www")){
			ChangeNation=1;
			MultiTvar=1;
			FogMode=0;
		}else
		if(!strcmp(passw,"VICTORY")){
			if(NPlayers<2)ShowVictory();
		}else
		if(!strcmp(passw,"IZMENA")||!strcmp(passw,"izmena"))ChangeNation=!ChangeNation;
		if(!strcmp(passw,"MULTITVAR")||!strcmp(passw,"multitvar"))MultiTvar=!MultiTvar;
		if(!strcmp(passw,"SUPERVIZOR")||!strcmp(passw,"supervizor"))FogMode=!FogMode;
		if(!strcmp(passw,"MONEY")||!strcmp(passw,"money")){
			AddXRESRC(MyNation,0,150000);
			AddXRESRC(MyNation,1,150000);
			AddXRESRC(MyNation,2,150000);
			AddXRESRC(MyNation,3,150000);
			AddXRESRC(MyNation,4,150000);
			AddXRESRC(MyNation,5,150000);
		}else
		if(!strcmp(passw,"AI")||!strcmp(passw,"ai")){
			Nation* NT=&NATIONS[MyNation];
			if(NT->AI_Enabled)NT->AI_Enabled=false;
			else{
				NT->AI_Enabled=true;
				NT->NMask=0x7E;
				for(int i=0;i<MAXOBJECT;i++){
					OneObject* OB=Group[i];
					if(OB&&OB->NNUM==MyNation&&OB->BrigadeID==0xFFFF){
						NT->CITY->RegisterNewUnit(OB);
						OB->NMask=0x7E;
					};
				};
				
			};
		}else{
			char cc1[64];
			int n1,n2;
			int z=sscanf(passw,"%s%d%d",cc1,&n1,&n2);
			if(z==3&&!strcmp(cc1,"change")){
				if(n1>=0&&n1<8&&n2>=0&&n2<=8)SelChangeNation(n1,n2);
			};
			if(NPlayers==1){
				char cc2[128];
				z=sscanf(passw,"%s%s",cc1,cc2);
				if(z==2&&!strcmp(cc1,"changeunit")){
					word Type=0xFFFF;
					for(int i=0;i<NATIONS->NMon;i++){
						if(!strcmp(cc2,NATIONS->Mon[i]->MonsterID)){
							GeneralObject* GO=NATIONS->Mon[i];
							if(!GO->newMons->Building){
								//found!!!
								int N=NSL[MyNation];
								word* IDS=Selm[MyNation];
								word* SMS=SerN[MyNation];
								for(int j=0;j<N;j++){
									word MID=IDS[j];
									if(MID!=0xFFFF){
										OneObject* OB=Group[MID];
										if(OB&&!OB->Sdoxlo){
											OB->Ref.General=GO;
											OB->NIndex=i;
											OB->newMons=GO->newMons;
										};
									};
								};
							};
						};
					};
				};
			};
		};
	};
};
void SaveGame(char* fnm,char* Messtr,int ID);
void ProcessGSaveGame(){
	if(strstr(GameName,".m3d")||strstr(GameName,".M3D"))GameName[0]=0;
	LocalGP BTNS("Interface\\G_Save_Game");
	LocalGP SCROL("Interface\\GScroll");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	//LoadPointer("cur_mn.rlc");
	int dx=(RealLx-470)>>1;
	int dy=(RealLy-415)>>1;
	DialogsSystem MMenu(dx,dy);
	GPS.ShowGP(dx,dy,BTNS.GPID,4,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	MMenu.addGPPicture(NULL,0,0,BTNS.GPID,5);
	VScrollBar* VSB=MMenu.addNewGP_VScrollBar(NULL,436,55,247,1,0,SCROL.GPID,0);
	ListBox* LB=MMenu.addGP_ListBox(NULL,29,61,9,BTNS.GPID,6,26,&WhiteFont,&YellowFont,VSB);

	//VScrollBar* VS=DSY.addVScrollBar(PIC1,LB->x-DSY.BaseX+LB->oneLx-1,1+LB->y-DSY.BaseY,1000,4,&sb_up_d,&sb_up_e,&sb_up_p,&sb_dn_d,&sb_dn_e,&sb_dn_p,&sb_vbare,&sb_vbar,&sb_btn);
	//LB->VS=VS;226x241
	GP_Button* OkBtn=MMenu.addGP_Button(NULL,49,353,BTNS.GPID,0,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=MMenu.addGP_Button(NULL,269,353,BTNS.GPID,2,3);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	InputBox* IB=MMenu.addInputBox(NULL,114,306,GameName,35,310,20,&YellowFont,&WhiteFont);
	IB->Active=true;
	ItemChoose=-1;
	DLL1(SFLB_CreateGamesList,LB);
	LB->CurItem=-1;
	int LastCTime=GetRealTime();
	int PrevListVal=LB->CurItem;
	KeyPressed=false;
	int StartTime=GetTickCount();
	do{
		if(GetTickCount()-StartTime>15000&&NPlayers>1){
			ItemChoose=mcmCancel;
			ShowOptMessage("#LOOKOPT",0);
			//SpecCmd=199;
			//IAmLeft();
		};
		if(PrevListVal!=LB->CurItem){
			PrevListVal=LB->CurItem;
			strcpy(GameName,LB->GetItem(LB->CurItem)->Message);
			GameName[strlen(GameName)-4]=0;
		};
		MMenu.MarkToDraw();
		ProcessMessages();
		StdKeys();
		//if(LB->CurItem==-1)OkBtn->Enabled=false;
		//else OkBtn->Enabled=true;
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(strlen(IB->Str)){
			OkBtn->Enabled=true;
		}else{
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		CmdSaveNetworkGame(MyNation,GetRealTime(),IB->Str);
	};
	ContinueGame=true;
	FreeNames();
	ClearMStack();
};
//----------------SAVE MAP--------------//
void NormalName(char* s){
	if(!strstr(s,".m3d")){
		strcat(s,".m3d");
	};
};
bool LBCLICK(SimpleDialog* SD){
	ListBox* LB=(ListBox*)SD;
	if(LB->CurItem!=-1){
		strcpy(GameName,(LB->GetItem(LB->CurItem))->Message);
	};
	return false;
};
void SaveExtendedMap(char* fnm);
void PushScreen(byte** Ptr);
void PopScreen(byte* Ptr);
bool ProcessSavingFile(char* Mask,char* DestName,int Header,bool clear);
void ProcessGSaveMap(){
	byte* p;
	PushScreen(&p);
	if(strstr(GameName,".sav")||strstr(GameName,".SAV"))GameName[0]=0;
	if(ProcessSavingFile("*.m3d",GameName,7,0)){
		NormalName(GameName);
		ResFile F=RReset(GameName);
		if(F!=INVALID_HANDLE_VALUE){
			RClose(F);
			char ccc[128];
			strcpy(ccc,GameName);
			char* cc=strstr(ccc,".m3d");
			if(cc){
				strcpy(cc,".bak");
				DeleteFile(cc);
				rename(GameName,ccc);
			};
		};
		Save3DMap(GameName);
	};
	PopScreen(p);
};
//----------------LOAD Map--------------//
void PreLoadExtendedMap(char* fnm);
void PostLoadExtendedMap(char* fnm);
bool ProcessLoadingFile(char* Mask,char* DestName,int Header);
extern bool PeaceMode;
void ProcessGLoadMap(){
	byte* p;
	PushScreen(&p);
	if(ProcessLoadingFile("*.m3d",GameName,4)){
		Load3DMap(GameName);
		PeaceMode=1;
	};
	PopScreen(p);
	/*
	SQPicture Pan("Pan15.bpx");
	SQPicture scr_U("scr_v_u.bpx");
	SQPicture scr_D("scr_v_d.bpx");
	SQPicture scr_V("scr_v.bpx");
	SQPicture scr_Line("scr_15.bpx");
	RLCFont gf24w(GETS("@SMFONT1"));
	RLCFont gf24y(GETS("@SMFONT0"));
	RLCFont ListF1(GETS("@CULISTF1"));
	RLCFont ListF0(GETS("@CULISTF0"));
	int mmlx=Pan.GetLx();
	int mmly=Pan.GetLy();

	DialogsSystem DSY(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=DSY.addPicture(NULL,0,0,&Pan,&Pan,&Pan);
	//TextButton* LoadBtn=DSY.addTextButton(PIC1,352>>1,30,"ÇÀÃÐÓÇÈÒÜ ÊÀÐÒÓ",&FActive,&FPassive,&FDisable,1);
	ListBox* LB=DSY.addListBox(PIC1,GETV("LMLSTX"),GETV("LMLSTY"),GETV("LMLSTNY"),GETV("LMLSTLX"),GETV("LMLSTLY"),&ListF1,&ListF0,NULL);
	VScrollBar* VS=DSY.addVScrollBar(PIC1,GETV("LMSCRX"),GETV("LMSCRY"),1000,4,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);
	LB->VS=VS;
	TextButton* OkBtn=DSY.addTextButton(PIC1,GETV("LMOKX"),GETV("LMOKY"),GETS("@LMOKSTR"),&gf24w,&gf24y,&gf24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=DSY.addTextButton(PIC1,GETV("LMNOX"),GETV("LMNOY"),GETS("@LMNOSTR"),&gf24w,&gf24y,&gf24y,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	CreateNewMapsList(LB);
	ItemChoose=-1;
	do{
		DSY.MarkToDraw();
		ProcessMessages();
		StdKeys();
		if(LB->CurItem==-1){
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		}else OkBtn->Enabled=true;
		DSY.ProcessDialogs();
		DSY.MarkToDraw();
		DSY.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk&&LB->CurItem!=-1){
		Load3DMap((LB->GetItem(LB->CurItem))->Message);
		strcpy(GameName,(LB->GetItem(LB->CurItem))->Message);
	};
	//FreeNames();
	*/
};
//-----------------OPTIONS---------------//
	

//---------------------------------------//
void NewMap(int szX,int szY);
extern byte mapPos[16];
void ClearAllZones();
void CreateNewMap(int SizeX,int SizeY){
	UnLoading();
	InitAllGame();
	NewMap(SizeX,SizeY);
	SetMyNation(0);
	ItemChoose=mcmSingle;
	msx=SizeX;
	msy=SizeY;
	InitExplosions();
	//ClearAllZones();
};
//--------Choose units Dialog------------//
void CreateUnitList(ListBox* LB,int Country){
	Nation* NT=&NATIONS[MyNation];
	LB->CurItem=0;
	LB->FirstItem=0;
	LB->FLItem=0;
	LB->VS->SPos=0;
	if(!Country){
		LB->AddStaticItem("UNITS:    ",0);
		for(int i=0;i<NT->NMon;i++){
			NewMonster* NM=NT->Mon[i]->newMons;
			if(!NM->Building)
				LB->AddItem(NM->Message,i);
		};
		LB->AddStaticItem("BUILDINGS:   ",0);
		for(i=0;i<NT->NMon;i++){
			NewMonster* NM=NT->Mon[i]->newMons;
			if(NM->Building)
				LB->AddItem(NM->Message,i);
		};
		return;
	};
	Country--;
	int NUNITS=NT->NUnits[Country];
	if(NUNITS){
		for(int j=0;j<NUNITS;j++){
			int UIDS=NT->UnitsIDS[Country][j];
			if(UIDS==0xFFFF){
				LB->AddStaticItem(NT->UnitNames[Country][j],0xFFFF);
			}else{
				NewMonster* NM=NT->Mon[UIDS]->newMons;
				LB->AddItem(NM->Message,UIDS);
			};
		};
	};
};
extern int NNations;
extern char** NatNames;
void UnPress();
void ChooseUnit(){
	ItemChoose=-1;
	SQPicture Pan("Units.bpx");
	//SQPicture Lstr("195x20.bpx");
	SQPicture scr_U("scr_v_u.bpx");
	SQPicture scr_D("scr_v_d.bpx");
	SQPicture scr_V("scr_v.bpx");
	SQPicture scr_Line("scr_13.bpx");
	RLCFont BtnF0(GETS("@CUFONT0"));
	RLCFont BtnF1(GETS("@CUFONT1"));
	RLCFont BtnL0(GETS("@CULISTF0"));
	RLCFont BtnL1(GETS("@CULISTF1"));
	RLCFont SelF (GETS("@CULISTF2"));
	int mmlx=Pan.GetLx();
	int mmly=Pan.GetLy();
	DialogsSystem DSY(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=DSY.addPicture(NULL,0,0,&Pan,&Pan,&Pan);
	//TextButton* LoadBtn=DSY.addTextButton(PIC1,352>>1,30,"ÂÛÁÎÐ ÎÁÚÅÊÒÀ",&FActive,&FPassive,&FDisable,1);
	ListBox* LBU=DSY.addListBox(PIC1,GETV("CUUNITX"),GETV("CUUNITY"),GETV("CUNY"),GETV("CULX"),GETV("CULY"),&BtnL1,&BtnL0,NULL);
	ListBox* LBB=DSY.addListBox(PIC1,GETV("CUBUILDX"),GETV("CUBUILDY"),GETV("CUNY"),GETV("CULX"),GETV("CULY"),&BtnL1,&BtnL0,NULL);
	LBB->DFont=&SelF;
	VScrollBar* VSU=DSY.addVScrollBar(PIC1,GETV("CUUNITSX"),GETV("CUUNITSY"),1000,4,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);
	VScrollBar* VSB=DSY.addVScrollBar(PIC1,GETV("CUBUILDSX"),GETV("CUBUILDSY"),1000,4,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);

	LBU->VS=VSU;
	LBB->VS=VSB;

	TextButton* OkBtn=DSY.addTextButton(PIC1,GETV("CUOKX"),GETV("CUOKY"),GETS("@CUOKSTR"),&BtnF0,&BtnF1,&BtnF1,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=DSY.addTextButton(PIC1,GETV("CUNOX"),GETV("CUNOY"),GETS("@CUNOSTR"),&BtnF0,&BtnF1,&BtnF1,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	Nation* NT=&NATIONS[MyNation];
	LBU->AddItem("ALL UNITS",0);
	for(int j=0;j<NNations;j++){
		LBU->AddItem(NatNames[j],j+1);
	};
	LBU->CurItem=0;
	LBU->FLItem=0;
	LBB->CurItem=0;
	LBB->FLItem=0;
	VSU->SPos=0;
	VSB->SPos=0;
	int CurNation=0;
	CreateUnitList(LBB,CurNation);
	ItemChoose=-1;
	int curpan=-1;
	do{
		ProcessMessages();
		if(!LBB->NItems)OkBtn->Enabled=false;
		else OkBtn->Enabled=true;
		DSY.MarkToDraw();
		DSY.ProcessDialogs();
		//DSY.MarkToDraw();
		DSY.RefreshView();
		if(CurNation!=LBU->CurItem){
			LBB->ClearItems();
			CurNation=LBU->CurItem;
			CreateUnitList(LBB,CurNation);
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		if(LBB->NItems){
			Creator=(LBB->GetItem(LBB->CurItem))->Param1;
		}else Creator=4096+255;
		ContinueGame=true;
	};
	UnPress();
};
void ChooseUnitOld(){
	ItemChoose=-1;
	SQPicture Pan("Units.bpx");
	SQPicture Lstr("195x20.bpx");
	SQPicture scr_U("scr_v_u.bpx");
	SQPicture scr_D("scr_v_d.bpx");
	SQPicture scr_V("scr_v.bpx");
	SQPicture scr_Line("scr_13.bpx");
	RLCFont BtnF0(GETS("@CUFONT0"));
	RLCFont BtnF1(GETS("@CUFONT1"));
	RLCFont BtnL0(GETS("@CULISTF0"));
	RLCFont BtnL1(GETS("@CULISTF1"));
	int mmlx=Pan.GetLx();
	int mmly=Pan.GetLy();
	DialogsSystem DSY(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=DSY.addPicture(NULL,0,0,&Pan,&Pan,&Pan);
	//TextButton* LoadBtn=DSY.addTextButton(PIC1,352>>1,30,"ÂÛÁÎÐ ÎÁÚÅÊÒÀ",&FActive,&FPassive,&FDisable,1);
	ListBox* LBU=DSY.addListBox(PIC1,GETV("CUUNITX"),GETV("CUUNITY"),GETV("CUNY"),GETV("CULX"),GETV("CULY"),&BtnL1,&BtnL0,NULL);
	ListBox* LBB=DSY.addListBox(PIC1,GETV("CUBUILDX"),GETV("CUBUILDY"),GETV("CUNY"),GETV("CULX"),GETV("CULY"),&BtnL1,&BtnL0,NULL);
	
	VScrollBar* VSU=DSY.addVScrollBar(PIC1,GETV("CUUNITSX"),GETV("CUUNITSY"),1000,4,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);
	VScrollBar* VSB=DSY.addVScrollBar(PIC1,GETV("CUBUILDSX"),GETV("CUBUILDSY"),1000,4,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);

	LBU->VS=VSU;
	LBB->VS=VSB;

	TextButton* OkBtn=DSY.addTextButton(PIC1,GETV("CUOKX"),GETV("CUOKY"),GETS("@CUOKSTR"),&BtnF0,&BtnF1,&BtnF1,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=DSY.addTextButton(PIC1,GETV("CUNOX"),GETV("CUNOY"),GETS("@CUNOSTR"),&BtnF0,&BtnF1,&BtnF1,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	Nation* NT=&NATIONS[MyNation];
	for(int j=0;j<NT->NMon;j++){
		NewMonster* NM=NT->Mon[j]->newMons;
		if(NM->Building)LBB->AddItem(NT->Mon[j]->Message,j);
		else LBU->AddItem(NT->Mon[j]->Message,j);
	};
	LBU->CurItem=0;
	LBU->FLItem=0;
	LBB->CurItem=0;
	LBB->FLItem=0;
	
	ItemChoose=-1;
	int curpan=-1;
	do{
		ProcessMessages();
		if(curpan==-1)OkBtn->Enabled=false;
		else OkBtn->Enabled=true;
		DSY.MarkToDraw();
		DSY.ProcessDialogs();
		//DSY.MarkToDraw();
		DSY.RefreshView();
		if(curpan==-1){
			if(LBU->CurItem!=-1)curpan=1;
			if(LBB->CurItem!=-1)curpan=2;
		};
		if(curpan==1&&LBB->CurItem!=-1){
			LBU->CurItem=-1;
			curpan=2;
		};
		if(curpan==2&&LBU->CurItem!=-1){
			LBB->CurItem=-1;
			curpan=1;
		};
	}while(ItemChoose==-1);
	if(curpan!=-1&&ItemChoose==mcmOk){
		if(curpan==1)Creator=(LBU->GetItem(LBU->CurItem))->Param1;
		if(curpan==2)Creator=(LBB->GetItem(LBB->CurItem))->Param1;
		ContinueGame=true;
	};
	UnPress();
};
//------MAIN MENU IN MAP EDITOR----------//

int ProcessE_GMainMenu();
int ProcessGMapEditMainMenu(){
	return ProcessE_GMainMenu();
	ContinueGame=false;
	SQPicture EPanel("edmenu.bpx");
	int mmlx=EPanel.GetLx();
	int mmly=EPanel.GetLy();
	RLCFont gf32w(GETS("@EMFONT1"));
	RLCFont gf32y(GETS("@EMFONT0"));
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&EPanel,&EPanel,&EPanel);
	int emmx=GETV("EMMENUX");
	TextButton* ExitBtn=GMM.addTextButton(PIC1,emmx,GETV("EMRETY"),GETS("@EMRET"),&gf32w,&gf32y,&gf32y,1);
	TextButton* SaveBtn=GMM.addTextButton(PIC1,emmx,GETV("EMSAVEMY"),GETS("@EMSAVEM"),&gf32w,&gf32y,&gf32y,1);
	SaveBtn->UserParam=mcmSave;
	SaveBtn->OnUserClick=&MMItemChoose;
	TextButton* LoadBtn=GMM.addTextButton(PIC1,emmx,GETV("EMLOADMY"),GETS("@EMLOADM"),&gf32w,&gf32y,&gf32y,1);
	LoadBtn->UserParam=mcmLoad;
	LoadBtn->OnUserClick=&MMItemChoose;
	TextButton* NewBtn=GMM.addTextButton(PIC1,emmx,GETV("EMNEWMY"),GETS("@EMNEWM"),&gf32w,&gf32y,&gf32y,1);
	TextButton* HelpBtn=GMM.addTextButton(PIC1,emmx,GETV("EMOPTY"),GETS("@EMOPT"),&gf32w,&gf32y,&gf32y,1);
	HelpBtn->UserParam=mcmOptions;
	HelpBtn->OnUserClick=&MMItemChoose;
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;
	TextButton* ResumeBtn=
		GMM.addTextButton(PIC1,emmx,GETV("EMCANCELY"),GETS("@EMCANCEL"),&gf32w,&gf32y,&gf32y,1);
	ResumeBtn->UserParam=mcmResume;
	ResumeBtn->OnUserClick=&MMItemChoose;
stg:
	ItemChoose=-1;
	do{
		ProcessMessages();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmLoad){
		ProcessGLoadMap();
		GMM.MarkToDraw();
		ItemChoose=mcmResume;
		//if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmSave){
		ProcessGSaveMap();
		GMM.MarkToDraw();
		ItemChoose=mcmResume;
		//if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmOptions){
		ProcessGameOptions();
		//ProcessOptions(smapx+(nsmaplx<<4)-(288>>1),smapy+(nsmaply<<3)-(288>>1));
		ContinueGame=true;
		ItemChoose=mcmResume;
	};
	return ItemChoose;	
}; 
//------------------Selecting Texture dialog--------------
extern byte *tex1;
extern byte EditMedia;
extern bool MEditMode;
extern bool EditMapMode;
extern int HeightEditMode;
word TexList[128];
word NTextures;
word GetTexture(){
	if(!NTextures)return 0;
	return TexList[(rando()*NTextures)>>15];
};
extern int MaxTex;
int SelectTexture(){
	ContinueGame=false;
	GameMode=2;
	NTextures=0;
	bool MIMOD=MiniMode;
	int mmmx=mapx;
	int mmmy=mapy;
	//ClearMiniMode();
	SQPicture Pan("textur.bpx");
	//SQPicture Lstr("195x20.bpx");
	SQPicture scr_U("scr_v_u.bpx");
	SQPicture scr_D("scr_v_d.bpx");
	SQPicture scr_V("scr_v.bpx");
	SQPicture scr_Line("scr_12.bpx");
	RLCFont f24y(GETS("@STFONT0"));
	RLCFont f24w(GETS("@STFONT1"));
	int mmlx=Pan.GetLx();
	int mmly=Pan.GetLy();
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(mmlx>>1),smapy+(mul3(nsmaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&Pan,&Pan,&Pan);
	TextButton* OkBtn=
		GMM.addTextButton(PIC1,GETV("STOKX"),GETV("STOKY"),GETS("@STOKMESS"),&f24w,&f24y,&f24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=
		GMM.addTextButton(PIC1,GETV("STCANCELX"),GETV("STCANCELY"),GETS("@STNOMESS"),&f24w,&f24y,&f24y,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	VScrollBar* VS=GMM.addVScrollBar(PIC1,GETV("STSCRX"),GETV("STSCRY"),(MaxTex>>2)-4,0,&scr_U,&scr_U,&scr_U,&scr_D,&scr_D,&scr_D,&scr_Line,&scr_Line,&scr_V);
	BPXView* BV=GMM.addBPXView(PIC1,GETV("STWINX"),GETV("STWINY"),48,48,4,4,MaxTex>>2,tex1,VS);
	BV->DECLX=16;
	ItemChoose=-1;
	do{
		ProcessMessages();
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1&&BV->ChoosedPos==-1);
	if(ItemChoose==mcmCancel){
		UnPress();
		return false;
	};
	if(BV->ChoosedPos!=-1){
		EditMedia=BV->ChoosedPos;
		HeightEditMode=false;
		MEditMode=true;
		Lpressed=false;
		TexList[0]=BV->ChoosedPos;
		NTextures=1;
	}else{
		int ntx=0;
		int nn=BV->Nx*BV->RealNy;
		for(int i=0;i<nn;i++){
			if(BV->Choosed[i]){
				for(int j=0;j<BV->Choosed[i];j++){
					if(ntx<256){
						TexList[ntx]=i;
						ntx++;
					};
				};
			};
		};
		if(ntx){
			NTextures=ntx;
			HeightEditMode=false;
			MEditMode=true;
			Lpressed=false;
		};
	};
	GameMode=0;
	UnPress();
	return ItemChoose;	
};
//----------MAIN MENU IN GAME------------//
bool IsGameActive();
int LastLookTime=0;
int ProcessGMainMenu(){
	if(NPlayers>1){
		if(LastLookTime&&(GetTickCount()-LastLookTime<180000)){
			int v=(180000-GetTickCount()+LastLookTime)/1000;
			ShowOptMessage("#F12LOCK",v);
			return mcmResume;
		};
	};
	LastLookTime=GetTickCount();
	LocalGP BTNS("Interface\\GameMenu");
	ContinueGame=false;
	GameMode=2;
	//bool MIMOD=MiniMode;
	int mmmx=mapx;
	int mmmy=mapy;
	//ClearMiniMode();
	//int dx=smapx+(nsmaplx<<4)-(GPS.GetGPWidth(BTNS.GPID,1)>>1);
	//int dy=smapy+(mul3(nsmaply)<<2)-(GPS.GetGPHeight(BTNS.GPID,1)>>1);
	int dx=((RealLx-470)>>1)-14;
	int dy=(RealLy-415)>>1;
	GPS.ShowGP(dx,dy,BTNS.GPID,0,0);
	DialogsSystem GMM(dx,dy);

	//GMM.addGPPicture(NULL,0,0,BTNS.GPID,0);
	GMM.addGPPicture(NULL,0,0,BTNS.GPID,1);

	GP_Button* ResumeBtn=GMM.addGP_Button(NULL,43,70,BTNS.GPID,3,2);
	ResumeBtn->UserParam=mcmResume;
	ResumeBtn->OnUserClick=&MMItemChoose;
	GP_Button* SaveBtn=GMM.addGP_Button(NULL,43,70+31*1,BTNS.GPID,7,6);
	SaveBtn->UserParam=mcmSave;
	SaveBtn->OnUserClick=&MMItemChoose;
	if(!(IsGameActive()||UseGSC_Login)){
		GP_Button* LoadBtn=GMM.addGP_Button(NULL,43,70+31*2,BTNS.GPID,5,4);
		LoadBtn->UserParam=mcmLoad;
		LoadBtn->OnUserClick=&MMItemChoose;
	}else{
		GP_Button* LoadBtn=GMM.addGP_Button(NULL,43,70+31*2,BTNS.GPID,4,4);
	};
	GP_Button* OptionsBtn=GMM.addGP_Button(NULL,43,70+31*3,BTNS.GPID,9,8);
	OptionsBtn->UserParam=mcmOptions;
	OptionsBtn->OnUserClick=&MMItemChoose;
	GP_Button* ExitBtn=GMM.addGP_Button(NULL,43,70+31*4,BTNS.GPID,11,10);
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;
	//TextButton* HelpBtn=GMM.addTextButton(PIC1,352>>1,30+160,"ÏÎÌÎÙÜ",&FActive,&FPassive,&FDisable,1);
	//HelpBtn->UserParam=mcmHelp;
	//HelpBtn->OnUserClick=&MMItemChoose;
stg:
	ItemChoose=-1;
	int StartTime=GetTickCount();
	do{
		ProcessMessages();
		GMM.ProcessDialogs();
		GMM.RefreshView();
		if(GetTickCount()-StartTime>15000&&NPlayers>1){
			ShowOptMessage("#LOOKOPT",0);
			ItemChoose=mcmResume;
			//SpecCmd=199;
			//IAmLeft();
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmLoad){
		ProcessGLoadGame();
		GMM.MarkToDraw();
		if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmSave){
		ProcessGSaveGame();
		GMM.MarkToDraw();
		if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmOptions){
		//ProcessOptions(smapx+(nsmaplx<<4)-(288>>1),smapy+(nsmaply<<4)-(288>>1));
		ProcessGameOptions();
		ContinueGame=true;
		ItemChoose=mcmResume;
	};
	if(ItemChoose==mcmHelp){
		ProcessHelp();
	};
	//if(MIMOD)SetMiniMode();
	mapx=mmmx;
	mapy=mmmy;
	GameMode=0;
	ClearMStack();
	return ItemChoose;	
};
int ProcessE_GMainMenu(){
	LocalGP BTNS("Interface\\E_GameMenu");
	ContinueGame=false;
	GameMode=2;
	//bool MIMOD=MiniMode;
	int mmmx=mapx;
	int mmmy=mapy;
	//ClearMiniMode();
	//int dx=smapx+(nsmaplx<<4)-(GPS.GetGPWidth(BTNS.GPID,1)>>1);
	//int dy=smapy+(mul3(nsmaply)<<2)-(GPS.GetGPHeight(BTNS.GPID,1)>>1);
	int dx=((RealLx-470)>>1)-14;
	int dy=(RealLy-415)>>1;
	GPS.ShowGP(dx,dy,BTNS.GPID,0,0);
	DialogsSystem GMM(dx,dy);

	//GMM.addGPPicture(NULL,0,0,BTNS.GPID,0);
	GMM.addGPPicture(NULL,0,0,BTNS.GPID,1);

	GP_Button* ResumeBtn=GMM.addGP_Button(NULL,43,70,BTNS.GPID,3,2);
	ResumeBtn->UserParam=mcmResume;
	ResumeBtn->OnUserClick=&MMItemChoose;
	GP_Button* SaveBtn=GMM.addGP_Button(NULL,43,70+31*1,BTNS.GPID,7,6);
	SaveBtn->UserParam=mcmSave;
	SaveBtn->OnUserClick=&MMItemChoose;
	GP_Button* LoadBtn=GMM.addGP_Button(NULL,43,70+31*2,BTNS.GPID,5,4);
	LoadBtn->UserParam=mcmLoad;
	LoadBtn->OnUserClick=&MMItemChoose;
	GP_Button* OptionsBtn=GMM.addGP_Button(NULL,43,70+31*3,BTNS.GPID,9,8);
	OptionsBtn->UserParam=mcmOptions;
	OptionsBtn->OnUserClick=&MMItemChoose;
	GP_Button* ExitBtn=GMM.addGP_Button(NULL,43,70+31*4,BTNS.GPID,11,10);
	ExitBtn->UserParam=mcmExit;
	ExitBtn->OnUserClick=&MMItemChoose;
	//TextButton* HelpBtn=GMM.addTextButton(PIC1,352>>1,30+160,"ÏÎÌÎÙÜ",&FActive,&FPassive,&FDisable,1);
	//HelpBtn->UserParam=mcmHelp;
	//HelpBtn->OnUserClick=&MMItemChoose;
stg:
	ItemChoose=-1;
	do{
		ProcessMessages();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmLoad){
		ProcessGLoadMap();
		GMM.MarkToDraw();
		if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmSave){
		ProcessGSaveMap();
		GMM.MarkToDraw();
		if(!ContinueGame)goto stg;
	};
	if(ItemChoose==mcmOptions){
		ProcessGameOptions();
		//ProcessOptions(smapx+(nsmaplx<<4)-(288>>1),smapy+(nsmaply<<3)-(288>>1));
		ContinueGame=true;
		ItemChoose=mcmResume;
	};

	mapx=mmmx;
	mapy=mmmy;
	GameMode=0;
	ClearMStack();
	return ItemChoose;	
};
//---------------------------------------//
extern int HintX;
extern int HintY;
byte ZoneOpt[128];
//  /-------------------------------------------------------\
//  | /--------\  2    3    4    5    6    7    8   /------\|       
//  | | 1      |                                    |      ||
//  | |        |  9    10   11   12  ...            |      ||
//  | |        |                                    |      ||
//  | \--------/  ...                               \------/|
//  \-------------------------------------------------------/
// ZoneOpt[i]:  0   -   empty
//              |1  -   used now
//              |2  -   was used
int Zone1X;
int Zone1Y;
int Zone1LX;
int Zone1LY;
int ZonesNy;
int ZonesNx;
int LeftListNx;
int PanelY;
int MessageUX;
int MessageUY;
int PropertyX;
int PropertyY;
//---------
int BrigPnX;
int BrigPnY;
int BrigNx;
int BrigNy;
extern IconSet PrpPanel;
extern IconSet AblPanel;
extern IconSet UpgPanel;
extern IconSet BrigPanel;
void CopyBPX2SCR(int xs,int ys,int xb,int yb,int Lx,int Ly,SQPicture* P){
    if(!Ly)return;
    word* Pic=P->PicPtr;
    int BLx=Pic[0];
    int BLy=Pic[1];
    int bofs=xb+yb*BLx+4+int(Pic);
    int sofs=xs+ys*SCRSizeX+int(ScreenPtr);
    int badd=BLx-Lx;
    int sadd=SCRSizeX-Lx;
    int Lx4=Lx>>2;
    int Lx1=Lx&3;
    __asm{
        pushf
        push    esi
        push    edi
        cld
        mov     esi,bofs
        mov     edi,sofs
        mov     edx,Ly
lpp1:   mov     ecx,Lx4
        rep     movsd
        mov     ecx,Lx1
        rep     movsb
        add     esi,badd
        add     edi,sadd
        dec     edx
        jnz     lpp1
        pop     edi
        pop     esi
        popf
    };

};
void ShowTextDiscription();
void DelUnusedZones(){
    for(int i=0;i<128;i++)if(ZoneOpt[i])ZoneOpt[i]=2;
    if(PrpPanel.NIcons==1){
        //CopyBPX2SCR(Zone1X,PanelY+Zone1Y,Zone1X,Zone1Y,Zone1LX,Zone1LY,&LoPanel);
		//Xbar(Zone1X,PanelY+Zone1Y+1,Zone1LX,Zone1LY,0xD0+(MyNation<<2));
		//Xbar(Zone1X-1,PanelY+Zone1Y,Zone1LX+2,Zone1LY+2,0xD0+(MyNation<<2)+1);
        ZoneOpt[0]|=1;
		int N=AblPanel.NIcons;
        for(i=0;i<N;i++){
            div_t ddt=div(i,AblNx);
            if(AblPanel.Icons[i].Visible)ZoneOpt[ddt.rem+ddt.quot*ZonesNx+1]=1;
        };
		/*
		N=UpgPanel.NIcons;
        for(i=0;i<N;i++){
            div_t ddt=div(i,AblNx);
            ZoneOpt[ddt.rem+ddt.quot*ZonesNx+1]|=1;
        };
		*/
    }else{
        //if(ZoneOpt[0])
        //    CopyBPX2SCR(Zone1X,PanelY+Zone1Y,Zone1X,Zone1Y,Zone1LX,Zone1LY,&LoPanel);
		/*
        int N=PrpPanel.NIcons;
        for(int i=0;i<N;i++){
            div_t ddt=div(i,PrpNx);
            ZoneOpt[ddt.rem+ddt.quot*ZonesNx+1]|=1;
        };
		*/
        int N=AblPanel.NIcons;
        for(i=0;i<N;i++){
            div_t ddt=div(i,AblNx);
            if(AblPanel.Icons->Visible)ZoneOpt[ddt.rem+ddt.quot*ZonesNx+1]=1;
        };
    };
    int maxzon=ZonesNx*ZonesNy;
    for(i=1;i<=maxzon;i++){
        if(ZoneOpt[i]==2){
            div_t ddt=div(i-1,ZonesNx);
            int x=ddt.rem*(IconLx+AddIconLx)+PrpX;
            int y=ddt.quot*(IconLy+AddIconLy)+PropertyY;
            //CopyBPX2SCR(x,y+PanelY,x,y,IconLx+2,IconLy+2,&LoPanel);
        };
    };
    for(i=0;i<maxzon;i++)if(ZoneOpt[i]==2)ZoneOpt[i]=0;
};
void EconomePostDraw();
extern bool ECOSHOW;
extern byte PlayGameMode;
void DrawZones(){
	if(PlayGameMode==1)return;
    if(PrpPanel.NIcons==1){
		int Max1=AblPanel.GetMaxX(12);
		int Max2=UpgPanel.GetMaxX(12);
		if(Max2>Max1)Max1=Max2;
		int x0=Zone1X+6;
		int y0=Zone1Y+PanelY;
		int x1=AblX-4+2;
		int y1=y0+(IconLy*3)+5;
		if(Max1){
			DrawLeftRect(x0,y0,x1,y1);
			DrawRightRect(x1,y0,x1+(IconLx+2)*Max1+2,y1);
		}else{
			DrawStdRect(x0,y0,x1,y1);
		};
		PrpPanel.DrawIconSet(Zone1X+6,Zone1Y+PanelY,1,1,0);
        AblPanel.DrawIconSet(AblX,AblY,AblNx,AblNy,0);
		UpgPanel.DrawIconSet(PrpX,PrpY,PrpNx,PrpNy,0);
        ShowTextDiscription();
		if(ECOSHOW)EconomePostDraw();
    }else{
		int Max1=AblPanel.GetMaxX(12);
		int Max2=PrpPanel.GetMaxX(12);
		if(Max2>Max1)Max1=Max2;
		if(Max1){
			int y0=Zone1Y+PanelY;
			int x1=AblX-4+2;
			int y1=y0+(IconLy*3)+5;
			DrawStdRect(x1,y0,x1+(IconLx+2)*Max1+2,y1);
			PrpPanel.DrawIconSet(PrpX,PrpY,PrpNx,PrpNy,0);
			AblPanel.DrawIconSet(AblX,AblY,AblNx,AblNy,0);
		};
    };
	if(!EditMapMode)BrigPanel.DrawIconSet(BrigPnX,BrigPnY,BrigNx,BrigNy,0);
	ECOSHOW=0;
};
void CopyZonesToScreen(){
    if(ZoneOpt[0]){
        CopyToScreen(Zone1X,Zone1Y,Zone1LX,Zone1LY);
    };
    int maxzon=ZonesNx*ZonesNy;
    for(int i=1;i<=maxzon;i++)if(ZoneOpt[i]){
        div_t ddt=div(i-1,ZonesNx);
        int x=ddt.rem*(IconLx+AddIconLx)+PrpX;
        int y=ddt.quot*(IconLy+AddIconLy)+PropertyY;
        CopyToScreen(x,y,IconLx+2,IconLy+2);
    };
};
bool NeedLoadGamePalette;
bool FullScreenMode=1;
void CreateINFORM();
extern int InfAddY;
extern int InfDY;
extern int InfDX;
extern int InfY1;
extern int InfY2;
void GSSetup800(){
	SetDarkPalette();
	CBar(0,0,SCRSizeX,SCRSizeY,0);
    memset(ZoneOpt,0,128);
	int DMiniX,DMiniY;
	int PanelLy;

	BrigPnX=6;
	BrigPnY=16+15;
	BrigNx=5;
	BrigNy=7;
	//if(RealLy>=768)
	InfAddY=16;
	//else InfAddY=0;
	InfDY=32+InfAddY;
	InfY1=450+InfAddY;
	InfY2=450-22+InfAddY;
	if(RealLy<=600){
		InfAddY=8;
		InfDY=32+InfAddY;
		InfY2=450-22-12-8;
		InfY1=450-12-8;
	}else{
		InfAddY=16;
		InfDY=32+InfAddY;
		InfY1=450+InfAddY;
		InfY2=450-22+InfAddY;
		if(RealLy<768){
			InfY1+=RealLy-768;
			InfY2+=RealLy-768;
		};
	};
	CreateINFORM();

	if(!CHKV("Zone1X")){
		Zone1X=6;
		Zone1Y=6;
		Zone1LX=132;
		Zone1LY=100;
		ZonesNy=6;
		ZonesNx=12;
		LeftListNx=3;
		MessageUX=75;
		MessageUY=8;
		PanelLy=144;
		PropertyX=142;
		PropertyY=6;
		IconLx=40;
		IconLy=40;
		DMiniX=152;
		DMiniY=7;
		AddIconLx=2;
		AddIconLy=2;
	}else{
		Zone1X=GETV("Zone1X");;
		Zone1Y=GETV("Zone1Y");
		Zone1LX=GETV("Zone1LX");
		Zone1LY=GETV("Zone1LY");
		ZonesNy=GETV("ZonesNy");
		ZonesNx=GETV("ZonesNx");
		LeftListNx=GETV("LeftListNx");
		MessageUX=GETV("MessageUX");;
		MessageUY=GETV("MessageUY");
		PanelLy=GETV("PanelLy");
		PropertyX=GETV("PropertyX");
		PropertyY=GETV("PropertyY");
		IconLx=GETV("IconLx");
		IconLy=GETV("IconLy");
		DMiniX=GETV("DMiniX");
		DMiniY=GETV("DMiniY");
		AddIconLx=GETV("AddIconLx");
		AddIconLy=GETV("AddIconLy");
	};
	MiniMode=false;
	Shifter=5;
	Multip=0;
    //-------
    int scly=RealLy;
	if(!FullScreenMode)scly-=PanelLy;
    int CLY=mul3(32)>>2;
    int Y1=RealLy-PanelLy;
    smaply=div(scly,CLY).quot;
    smaplx=RealLx>>5;
    smapx=0;
    smapy=RealLy-smaply*16;//scly-smaply*CLY;
    minix=RealLx-DMiniX;
    miniy=RealLy-PanelLy+DMiniY;
    nsmaplx=smaplx;
	nsmaply=smaply;
	HintX=smapx+4;
	HintY=Y1-40;
    MiniMode=false;
    //ZonesNx=div(RealLx-PropertyX-DMiniX,IconLx+AddIconLx).quot;
    //if(ZonesNx<=7)PrpNx=3;else PrpNx=4;
	Shifter=5;
	Multip=0;
    PrpX=PropertyX;
    PrpY=Y1+PropertyY;
	PrpNx=ZonesNx>>1;
    PrpNy=ZonesNy;

    AblX=PrpX;//+(PrpNx)*(IconLx+2);
    AblY=Y1+PropertyY;
    AblNy=ZonesNy;
    AblNx=PrpNx=ZonesNx;

    GSYS.~DialogsSystem();
	
    LoPanel.~SQPicture();
	//LoPanel.LoadPicture("800.bmp");
	/*
    switch(RealLx){
    case 1024:
        //LoPanel.LoadPicture("1024.bpx");
        break;
    case 1152:
        //LoPanel.LoadPicture("1152.bpx");
        break;
    case 1280:
        //LoPanel.LoadPicture("1280.bpx");
        break;
    default:
        LoPanel.LoadPicture("800.bmp");
    };
	*/
	GVPort=GSYS.addViewPort(smapx,smapy,smaplx<<5,smaply<<4);
    PanelY=RealLy-PanelLy;
    MessageUY+=PanelY;
	//GSYS.addPicture(NULL,0,PanelY,&LoPanel,&LoPanel,&LoPanel);
	//MiniVPort=GSYS.addViewPort(minix,miniy,msx>>1,msy>>1);
	//AblVPort=GSYS.addViewPort(AblX,AblY,AblNx*(IconLx+2),AblNy*(IconLy+2));
	//PrpVPort=GSYS.addViewPort(PrpX,PrpY,PrpNx*(IconLx+2),PrpNy*(IconLy+2));
	//agew.pal");//grassw.pal");//dmw.pal");//"darkw.pal");
	NeedLoadGamePalette=true;
	if(mapx+smaplx>msx+1)mapx=msx-smaplx+1;
	if(mapy+smaply>msy+1)mapy=msy-smaply+1;
};
void GFieldShow();
void GMiniShow();
void GlobalHandleMouse();
void DRAW_MAP_TMP();
void DrawAllScreen(){
	//COUNTER++;
	GFieldShow();
	//Pan1->OnDraw(Pan1);
	//LoPanel.Draw(0,PanelY);
	GMiniShow();
	//Pan2->OnDraw(Pan2);
	ShowProp();
	//Pan3->OnDraw(Pan3);
	ShowAbility();
	//Pan4->OnDraw(Pan4);
	//if(Pan5)Pan5->OnDraw(Pan5);
    memset(ZoneOpt,0,128);
    DrawZones();
	DRAW_MAP_TMP();
	CopyToScreen(0,0,RealLx,RSCRSizeY);
	GlobalHandleMouse();//mouseX,mouseY);
	MFix();
	if(NeedLoadGamePalette){
		if(IgnoreSlow){
			LoadPalette("0\\agew_1.pal");
			LoadFog(0);
		}else{
			SlowLoadPalette("0\\agew_1.pal");
			LoadFog(0);
		};
		CreateMiniMap();
	};
	NeedLoadGamePalette=false;
};
void GlobalHandleMouse();
void FastScreenProcess(){
//	SERROR2();
	///RunPF(14);
	SUSP("GFIELDSHOW");
	GFieldShow();
	ProcessMessages();
	if(SHOWSLIDE){
		SUSP("GMINISHOW");
		GMiniShow();
		//Pan1->OnDraw(Pan1);
		//Pan3->OnDraw(Pan3);
		SUSP("SHOWPROP");
		ShowProp();
		ShowAbility();
	  //DelUnusedZones();
		SUSP("DRAWZONES");
		DrawZones();
		//Pan1->NeedToDraw=false;
		SUSP("PRDIALOGS");
		DRAW_MAP_TMP();
		GSYS.ProcessDialogs();
		//Pan1->NeedToDraw=false;
		//Pan2->NeedToDraw=false;
		//Pan3->NeedToDraw=false;
		GVPort->NeedToDraw=true;
		//MiniVPort->NeedToDraw=true;
		//AblVPort->NeedToDraw=true;
		//PrpVPort->NeedToDraw=true;
	};
	SUSP("HANDLEMOUS");
	//HandleMouse(mouseX,mouseY);
	GlobalHandleMouse();
	MFix();
	if(SHOWSLIDE){
	//	SERROR2();
		int time0=GetRealTime();
		//CopyToScreen(0,0,RealLx,RSCRSizeY);
		SUSP("REFRESHVIEW");
		GSYS.RefreshView();
		 //CopyZonesToScreen();
		//FlipPages();
		time8=GetRealTime()-time0;
	};
	SUSP("ENDFAST");
	if(NeedLoadGamePalette){
		if(IgnoreSlow){
			LoadPalette("0\\agew_1.pal");
			LoadFog(0);
		}else{
			SlowLoadPalette("0\\agew_1.pal");
			LoadFog(0);
		};
		CreateMiniMap();
	};
	NeedLoadGamePalette=false;
	//StopPF(14);
//	SERROR1();
};
void PreDrawGameProcess();
void PostDrawGameProcess();
void IAmLeft();
extern bool LockPause;
bool ShowStatistics();
extern bool ShowStat;
extern int WaitState;
void CmdEndGame(byte NI,byte state,byte cause);
int StartAboutTime=0;
int NAboutLn=-1;
void ShowAbout(){
	TempWindow TM;
	PushWindow(&TM);
	IntersectWindows(0,smapy,smaplx*32,smaply*16);
	int y0=RealLy-(GetTickCount()-StartAboutTime)/50;
	char pp[100];
	if(NAboutLn==-1){
		for(int i=0;i<200;i++){
			sprintf(pp,"ABLINE%d",i);
			if(pp==GetTextByID(pp)){
				NAboutLn=i;
				i=300;
			};
		};
	};
	if(NAboutLn==-1)return;
	int LDis=35;
	if(y0<-NAboutLn*LDis);
	for(int i=0;i<NAboutLn;i++){
		sprintf(pp,"ABLINE%d",i);
		char* tx=GetTextByID(pp);
		if(y0>-LDis){
			ShowString(2+(RealLx-GetRLCStrWidth(tx,&BigYellowFont))>>1,2+y0,tx,&BigBlackFont);
			ShowString((RealLx-GetRLCStrWidth(tx,&BigYellowFont))>>1,y0,tx,&BigYellowFont);
		}
		y0+=LDis;
	};
	PopWindow(&TM);
};
bool Lobby=0;
void REPLAY();
void LOOSEANDEXITFAST();
void EndGSC_Reporting();
void PlayGame(){
	GSSetup800();
	LoadFog(0);
	InitGame();
	if(exRealLx!=RealLx)SetGameDisplayModeAnyway(exRealLx,exRealLy);
	DrawAllScreen();
	GameNeedToDraw=false;
	GameExit=false;
	MakeMenu=false;
	InGame=true;
	if(PlayGameMode)StartAboutTime=GetTickCount();
StartPlay:
	do{
		if(RUNMAPEDITOR||RUNUSERMISSION){
			GameExit=true;
		};
		time1=GetRealTime();
		ProcessMessages();
		if(bActive){
			GameMode=0;
			PreDrawGameProcess();
			//time3=GetRealTime()-time1;
			SUSP("Process1");
			ProcessMessages();
			if(GameNeedToDraw){
				//COUNTER++;
				SUSP("DrawAllScr");
				DrawAllScreen();
				GameNeedToDraw=false;
			}else{
				SUSP("FastScreen");
				FastScreenProcess();
			};
			//DrawAllScreen();
			//DrawAllScreen();
			SUSP("Process2");
			ProcessMessages();
			time1=GetRealTime();
			SUSP("PostDraw");
			PostDrawGameProcess();
			time5=GetRealTime()-time1;
			if(MakeMenu){
				switch(MenuType){
				case 1:	if(ProcessGMainMenu()==mcmExit){
							if(NPlayers>1&&!NATIONS[MyNation].VictState){
								LockPause=1;
								WaitState=1;
								if(SCENINF.hLib&&!SCENINF.StandartVictory){
									SCENINF.LooseGame=1;
								};
								if(NATIONS[MyNation].VictState!=2)CmdEndGame(MyNation,1,101);
								int t0=GetRealTime();
								do{
									ProcessMessages();
								}while(GetRealTime()-t0<500);
							};
							GameExit=true;
							ShutdownMultiplayer(0);
							CloseMPL();
							//IAmLeft();
						};
						break;
				case 2: ChooseUnit();
					    break;
				case 3: EnterChat();
						break;
				case 4: ProcessHelp();
						break;
				case 5: SelectTexture();
						break;
				};
				MakeMenu=false;
			}else{
				if(GameExit){
					IAmLeft();
					LOOSEANDEXITFAST();
					CloseMPL();
					ShutdownMultiplayer(0);
				};
			};
		}else GameNeedToDraw=true;
resgame:;
	}while(!GameExit);
	Lobby=0;
	PlayGameMode=0;
	if(RecordMode){
		RGAME.Save();
		RecordMode=0;
	};
	EndGSC_Reporting();
	UseGSC_Login=0;
	if(RetryVideo&&!(RUNMAPEDITOR||RUNUSERMISSION)){
		GFILE* f=Gopen("Demo\\demo.run","r");
		if(f){
			int N;
			int z=Gscanf(f,"%d",&N);
			if(z==1){
				int M=GetRndVid(N);
				char NAME[64];
				for(int i=0;i<M;i++)Gscanf(f,"%s",NAME);
				Gscanf(f,"%s",NAME);
				RGAME.ReadStream(NAME);
				if(RGAME.Size){
					PlayGameMode=1;
					RecordMode=0;
					RetryVideo=1;
					KeyPressed=0;
				};
			};
			Gclose(f);
			GameExit=0;
			goto StartPlay;
		}else RetryVideo=0;
	};
	IgnoreSlow=true;
	//SlowUnLoadPalette("0\\agew_1.pal");
	int ExRX=RealLx;
	int ExRY=RealLy;
	if(RealLx!=1024||RealLy!=768)SetGameDisplayModeAnyway(1024,768);
	if(ShowStat){
		if(!ShowStatistics()){
			GameExit=false;
			WaitState=1;
			if(RealLx!=ExRX||RealLy!=ExRY)SetGameDisplayModeAnyway(ExRX,ExRY);
			if(ItemChoose==131)REPLAY();
			goto resgame;
		};
		SlowUnLoadPalette("0\\agew_1.pal");
	};
	ClearScreen();
	IgnoreSlow=false;
};
void DrawAllEditScreen(){
	GFieldShow();
	//Pan1->OnDraw(Pan1);
	GMiniShow();
	//Pan2->OnDraw(Pan2);
	ShowProp();
	//Pan3->OnDraw(Pan3);
	ShowAbility();
	//Pan4->OnDraw(Pan4);
	//if(Pan5)Pan5->OnDraw(Pan5);
	DRAW_MAP_TMP();
	CopyToScreen(0,0,RealLx,RSCRSizeY);
};
void DRAW_MAP_TMP();
void FastEditScreenProcess(){
	//RunPF(14);
	GFieldShow();
	ProcessMessages();
	GMiniShow();
	//Pan1->OnDraw(Pan1);
	//Pan3->OnDraw(Pan3);
	ShowProp();
	ShowAbility();
	//Pan1->NeedToDraw=false;
	DRAW_MAP_TMP();
	GSYS.ProcessDialogs();
	//Pan1->NeedToDraw=false;
	//Pan2->NeedToDraw=false;
	//Pan3->NeedToDraw=false;
	GVPort->NeedToDraw=true;
	MiniVPort->NeedToDraw=true;
	AblVPort->NeedToDraw=true;
	PrpVPort->NeedToDraw=true;
	//HandleMouse(mouseX,mouseY);
	GlobalHandleMouse();
	MFix();
	GSYS.RefreshView();
	//StopPF(14);
};
void CheckGP();
void EditGame(){
	LoadFog(0);
	GSSetup800();
	if(exRealLx!=RealLx)SetGameDisplayModeAnyway(exRealLx,exRealLy);
	DrawAllEditScreen();
	GameNeedToDraw=false;
	GameExit=false;
	MakeMenu=false;
	do{
		ProcessMessages();
		if(bActive){
			if(RUNUSERMISSION){
				GameExit=true;
			};
			if(RUNMAPEDITOR){
				Load3DMap(USERMISSPATH);
				strcpy(GameName,USERMISSPATH);
				RUNMAPEDITOR=0;
			};
			//SERROR2();
			RunPF(15);
			PreDrawGameProcess();
			//SERROR1();
			SUSP("Process3");
			ProcessMessages();
			//if(GameNeedToDraw){
			//	DrawAllScreen();
			//	GameNeedToDraw=false;
			//}else 
			SUSP("FastScreen1");
			StopPF(15);
			FastScreenProcess();
			//DrawAllScreen();
			//SERROR();
			SUSP("Process4");
			ProcessMessages();
			SUSP("PostDraw");
			RunPF(16);
			PostDrawGameProcess();
			StopPF(16);
			if(MakeMenu){
				switch(MenuType){
				case 1:	if(ProcessGMapEditMainMenu()==mcmExit)GameExit=true;
						break;
				case 2: ChooseUnit();
					    break;
				case 3: EnterChat();
						break;
				case 31: ProcessResEdit();
						break;
				case 5: SelectTexture();
						break;
				case 6: EditMiniMap();
						break;
				case 7: ChooseInterior(0);
						break;
				case 8: ChooseInterior(1);
						break;
				case 9: ChooseInterior(2);
						break;
				};
				MakeMenu=false;
			};
		}else GameNeedToDraw=true;
	}while(!GameExit);
	IgnoreSlow=true;
	SetGameDisplayModeAnyway(1024,768);
	IgnoreSlow=false;
};
//--------------ALL GAME IS IN THIS PROCEDURE!-------------//
BOOL FAR PASCAL EnumAddressCallback1(
	REFGUID guidDataType,
	DWORD dwDataSize,
	LPCVOID lpData,
	LPVOID lpContext
  ){
	if(guidDataType==DPAID_INet){
		strcpy(IPADDR,(char*)lpData);
		return false;
	};
	return true;
};

void ShowFailure(int CreateGame){
	ClearScreen();
	LoadFog(0);
	LoadPalette("0\\agew_1.pal");
	KeyPressed=0;
	bool NEEDDRAW=1;
	do{
		if(bActive){
			if(NEEDDRAW){
				CBar(0,0,RealLx,RealLy,0);
				char* ss[5];
				int NS=0;
				//if(CreateGame){
				char ccx[256];
				if(CreateGame==1){
					ss[0]=GetTextByID("LOBUNC");
					ss[1]=GetTextByID("LOBPR");
					NS=2;
				}else if(CreateGame==0){
					ss[0]=GetTextByID("LOBUNJ1");
					sprintf(ccx,GetTextByID("LOBUNJ5"),IPADDR);
					ss[1]=GetTextByID("LOBUNJ2");
					ss[2]=ccx;
					ss[3]=GetTextByID("LOBPR");
					NS=4;
				}else{
					ss[0]=GetTextByID("LOBUNJ3");
					sprintf(ccx,GetTextByID("LOBUNJ5"),IPADDR);
					ss[1]=GetTextByID("LOBUNJ4");
					ss[2]=ccx;
					ss[3]=GetTextByID("LOBPR");
					NS=4;
				};
				int L=0;
				for(int i=0;i<NS;i++){
					int LL=GetRLCStrWidth(ss[i],&BigWhiteFont);
					if(LL>L)L=LL;
				};
				DrawStdBar(512-32-L/2,380-NS*15-15,512+32+L/2,380+NS*15+15);
				for(i=0;i<NS;i++)
					ShowString(512-GetRLCStrWidth(ss[i],&BigWhiteFont)/2,380-NS*15+i*30,ss[i],&BigWhiteFont);
				FlipPages();
			};
			NEEDDRAW=0;
		}else NEEDDRAW=true;
		ProcessMessages();
	}while(!KeyPressed);
	KeyPressed=0;
	ClearScreen();
	LoadFog(2);
	LoadPalette("2\\agew_1.pal");
};
void WaitWithMessage(char* Message);
bool AskQuestion2(char* Header,char* Text,char* OKTXT,char* CANCELTXT){
	ItemChoose=-1;
	int MPPLX=450;
	int MPPLY=350;
	int MPLDX=20;
	int MPRDX=20;
	int MPDDY=20;
	int MPUDY=20;
	LocalGP BOR2("Interface\\Bor2");
	DialogsSystem GMM((RealLx-MPPLX)>>1,(RealLy-MPPLY)>>1);
	
	
	int DY=0;
	
	int LX=0;
	int LY=0;
	GMM.addTextButton(NULL,MPPLX/2,20,Header,&BigWhiteFont,&BigWhiteFont,&BigWhiteFont,1);
	DY+=40;
	LY=40;
	TextViewer* TV;
	TV=GMM.addTextViewer(NULL,MPLDX,MPUDY+LY,MPPLX-MPLDX-MPRDX,MPPLY-LY-MPDDY-MPUDY-40,Text,&YellowFont);
	ItemChoose=-1;
	LY+=TV->NLines*TV->SymSize;
	TV->y1=TV->y;
	TextButton* YesBtn=GMM.addTextButton(NULL,MPPLX/4,LY+30,OKTXT,&BigWhiteFont,&BigYellowFont,&BigYellowFont,1);
	YesBtn->UserParam=mcmOk;
	YesBtn->OnUserClick=&MMItemChoose;
	TextButton* NoBtn=GMM.addTextButton(NULL,MPPLX*3/4,LY+30,CANCELTXT,&BigWhiteFont,&BigYellowFont,&BigYellowFont,1);
	NoBtn->UserParam=mcmCancel;
	NoBtn->OnUserClick=&MMItemChoose;
	LY+=70;
	int DDD=(MPPLY-LY)/2;
	GMM.BaseY+=DDD;
	for(int i=0;i<512;i++)if(GMM.DSS[i]){
		GMM.DSS[i]->y+=DDD;
		GMM.DSS[i]->y1+=DDD;
	};
	MPPLY=LY;
	DrawStdBar2(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY,BOR2.GPID);
	ItemChoose=-1;
	do{
		DrawStdBar2(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY,BOR2.GPID);
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13)ItemChoose=mcmOk;
			else if(LastKey==27)ItemChoose=mcmCancel;
			KeyPressed=false;
		};
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	UnPress();
	if(ItemChoose==mcmOk){
		ItemChoose=-1;
		return true;
	}else{
		ItemChoose=-1;
		return false;
	};
};
bool NotifyFirewallState(){
	char* txt=GetTextByID("FRW_TXT");
	ResFile F=RRewrite("tmp.txt");
	RBlockWrite(F,txt,strlen(txt));
	RClose(F);
	return AskQuestion2(GetTextByID("FRW_0"),"tmp.txt",GetTextByID("FRW_YES"),GetTextByID("FRW_IGN"));
};
bool DPL_CreatePlayer(LPDIRECTPLAY3A lpDirectPlay3A,
					  LPGUID lpguidSessionInstance, LPDPNAME lpszPlayerName,bool Host);
#ifdef MAKE_PTC
int CheckLobby(){
	WindX=0;
	WindY=0;
	WindX1=1023;
	WindY1=767;
	WindLx=1024;
	WindLy=768;
	LPDIRECTPLAYLOBBYA	lpDPlayLobbyA = NULL;
	LPDIRECTPLAYLOBBY2A	lpDPlayLobby2A = NULL;
	if FAILED(DirectPlayLobbyCreate(NULL, &lpDPlayLobbyA, NULL, NULL, 0)) return false;
	// get ANSI DirectPlayLobby2 interface
	HRESULT hr = lpDPlayLobbyA->QueryInterface(IID_IDirectPlayLobby2A, (LPVOID *) &lpDPlayLobby2A);
	if FAILED(hr)return false;
	DWORD Size=0;
	HRESULT dpres=lpDPlayLobby2A->GetConnectionSettings(0,NULL,&Size);
	if(!Size){
		lpDPlayLobby2A->Release();
		return false;
	};
	LPDPLCONNECTION cset=(LPDPLCONNECTION)malloc(Size);
	dpres=lpDPlayLobby2A->GetConnectionSettings(0,cset,&Size);
	if(dpres==DP_OK){
		LPDIRECTPLAY2A lpd2A;
		CreateMultiplaterInterface();
		if(lpDirectPlay3A){
			LoadFog(2);
			LoadPalette("2\\agew_1.pal");
			ShowLoading();
			//assert(0);
			char cc[128]="";
			if(cset->lpSessionDesc->lpszSessionNameA)
				strcpy(cc,cset->lpSessionDesc->lpszSessionNameA);
			cc[8]=0;
			bool BATTL=!strcmp(cc,"[BATTLE]");
			if(BATTL){
				cset->lpSessionDesc->dwMaxPlayers=2;
				cset->lpSessionDesc->dwUser2=1;
			}else{
				cset->lpSessionDesc->dwMaxPlayers=7;
				cset->lpSessionDesc->dwUser2=0;
			};
			dpres=lpDPlayLobby2A->Connect(0,&lpd2A,NULL);
			lpDPlayLobby2A->EnumAddress(&EnumAddressCallback1,cset->lpAddress,cset->dwAddressSize,NULL);

			if(dpres!=DP_OK){
				if(BATTL){
					if(cset->lpSessionDesc->dwFlags==DPLCONNECTION_CREATESESSION)ShowFailure(1);
					else ShowFailure(2);
				}else{
					//lpDPlayLobby2A->EnumAddress(&EnumAddressCallback1,cset->lpAddress,cset->dwAddressSize,NULL);
					ShowFailure(cset->lpSessionDesc->dwFlags==DPLCONNECTION_CREATESESSION);
				};
				lpDPlayLobby2A->Release();
				return false;
			};
			lpDPlayLobby2A->Release();
			dpres= lpd2A->QueryInterface(IID_IDirectPlay3A, (LPVOID*)&lpDirectPlay3A);
			if(dpres!=DP_OK)return false;
			ClearScreen();
			LoadFog(2);
			LoadPalette("2\\agew_1.pal");
			if(dpres==DP_OK){
				if(cset->dwFlags==DPLCONNECTION_CREATESESSION){
					DPL_CreatePlayer(lpDirectPlay3A,&cset->guidSP,cset->lpPlayerName,1);
					if(!BATTL){
						if(!MPL_WaitingGame(true,0))return false;
					}else{
						int BTLID=1;//ProcessWars();
						if(!MPL_WaitingBattleGame(true,1))return false;
					};
					StopConnectionToSession(lpDirectPlay3A);
					StartIGame(0);
				}else{
					DPL_CreatePlayer(lpDirectPlay3A,&cset->guidSP,cset->lpPlayerName,1);
					if(!BATTL){
						if(!MPL_WaitingGame(false,0))return false;
					}else{
						if(!MPL_WaitingBattleGame(false,1))return false;
					};
				};
				return 1;
			}else{
				return false;
			};
		}else{
			return false;
		};
	}else{
		return false;
	};
};
#endif
int prevVid=-1;
int prevVid1=-1;
int prevVid2=-1;
int prevVid3=-1;
int GetRndVid(int N){
	int dt=GetTickCount()&1023;
	for(int i=0;i<dt;i++)rand();
	int cv=-1;
	if(N>4){
		int na=0;
		do{
			int n=rand()%N;
			if(n!=prevVid&&n!=prevVid1&&n!=prevVid2&&n!=prevVid3)cv=n;
			na++;
		}while(cv==-1&&na<100);
	};
	if(cv==-1&&N>3){
		int na=0;
		do{
			int n=rand()%N;
			if(n!=prevVid&&n!=prevVid1&&n!=prevVid2)cv=n;
			na++;
		}while(cv==-1&&na<100);
	};
	if(cv==-1&&N>2){
		int na=0;
		do{
			int n=rand()%N;
			if(n!=prevVid&&n!=prevVid1)cv=n;
			na++;
		}while(cv==-1&&na<100);
	};
	if(cv==-1&&N>1){
		int na=0;
		do{
			int n=rand()%N;
			if(n!=prevVid)cv=n;
			na++;
		}while(cv==-1&&na<100);
	};
	if(cv==-1)cv=0;
	prevVid3=prevVid2;
	prevVid2=prevVid1;
	prevVid1=prevVid;
	prevVid=cv;
	return cv;
};
void PlayVideo();
#ifdef MAKE_PTC
void AllGame(){
	if(CheckLobby()){
		EditMapMode=0;
		Lobby=1;
	}else{
		PlayVideo();
		ShowPreview();
	};
stgame:
	int mret;
	if(Lobby)mret=mcmSingle;
	else mret=processMainMenu();
	if(mret==mcmExit)return;
	if(mret==mcmSingle){
        if(EditMapMode){
            EditGame();
        }
		else PlayGame();
		UnLoading();
		goto stgame;
	}else goto stgame;
};
#else
void AllGame(){
	GFILE* f=Gopen("Demo\\demo.run","r");
	if(f){
		int N;
		int z=Gscanf(f,"%d",&N);
		if(z==1){
			int M=GetRndVid(N);
			char NAME[64];
			for(int i=0;i<M;i++)Gscanf(f,"%s",NAME);
			Gscanf(f,"%s",NAME);
			RGAME.ReadStream(NAME);
			if(RGAME.Size){
				PlayGameMode=1;
				RecordMode=0;
				ItemChoose=43;
				RetryVideo=1;
				KeyPressed=0;
			};
		};
		Gclose(f);
		PlayGame();
	};
};
#endif
extern int PLNAT[8];
void PrepareGameMedia(byte myid,bool);
void MakeGlobalReport();
void FreeArrays();
void SetupArrays();
void CreateTotalLocking();
void TestRoads();
void ResearchIslands();
void PrepareEditMedia(byte myid){
		FreeArrays();
		ADDSH=1;
		SetupArrays();
		rpos=0;
		setCoor();
		UnLoading();
		NewMap(240<<ADDSH,240<<ADDSH);
		SetMyNation(0);
		for(int i=0;i<8;i++){
			if(!PLNAT[i])
				LoadAllNations(1<<i,i);
			else LoadAllNations(1<<i,i);
			SetMyNation(myid);
		};
		ItemChoose=mcmSingle;
		//MultiplayerStart=true;
		InitExplosions();
		PrepareToEdit();
		ItemChoose=mcmSingle;
		InitGame();
		MakeGlobalReport();
		EraseAreas();
		rando();//!!
		CreateTotalLocking();
		TestRoads();
		ResearchIslands();
};
void RedrawGameBackground(){
	if(GameMode==1){//main menu
		//int mmlx=MainMenuGround.PicPtr[0];
		//int mmly=MainMenuGround.PicPtr[1];
		//MainMenuGround.Draw((RealLx-mmlx)>>1,(RSCRSizeY-mmly)>>1);
		FlipPages();
	}else{
		DrawAllScreen();		
	};
};
void ProcessHelp(){
	if(!SCENINF.hLib)return;
	ResFile F=RReset("miss.txt");
	int sz=0;
	if(F!=INVALID_HANDLE_VALUE){
		sz=RFileSize(F);
		RClose(F);
	};
	if(!sz)return;
	int MPPLX=GETV("MPPLX");
	int MPPLY=GETV("MPPLY");
	int MPLDX=GETV("MPLDX");
	int MPRDX=GETV("MPRDX");
	int MPDDY=GETV("MPDDY");
	int MPUDY=GETV("MPDDY");
	MPUDY+=40;
	//char* BmpName=GETS("@MISSPANEL");
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(MPPLX>>1),smapy+(mul3(nsmaply)<<2)-(MPPLY>>1));
	//SQPicture SP(BmpName);

	LocalGP FONTB("vinBig");
	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTB.GPID);
	RLCFont fntw(FONTB.GPID);
	fntrb.SetRedColor();
	//LoadOptionalTable(5,"2\\orange.grd");
	//fntw.SetColorTable(5);
	
	SQPicture SPU;
	SPU.PicPtr=NULL;
	//LocalGP LGP;
	//LGP.Load(BmpName);
	//GPS.ShowGP(GMM.BaseX,GMM.BaseY,LGP.GPID,0,0);
	//GMM.addGPPicture(NULL,0,0,LGP.GPID,1);
	int LX=0;
	int LY=0;
	TextViewer* TV;
	GMM.addTextButton(NULL,(MPPLX>>1)+1,-20,GetTextByID("MISSOBJ"),&BigBlackFont,&BigBlackFont,&BigBlackFont,1);
	GMM.addTextButton(NULL,MPPLX>>1,-21,GetTextByID("MISSOBJ"),&BigYellowFont,&BigYellowFont,&BigYellowFont,1);
	if(SCENINF.hLib){
		TV=GMM.addTextViewer(NULL,MPLDX,MPUDY+LY,MPPLX-MPLDX-MPRDX,MPPLY-MPDDY-MPUDY-LY-40,"miss.txt",&BlackFont);
	}else{
		TV=GMM.addTextViewer(NULL,MPLDX,MPUDY+LY,MPPLX-MPLDX-MPRDX,MPPLY-MPDDY-MPUDY-LY-40,"help.txt",&BlackFont);
	};
	TV->SymSize+=3;
	TV->PageSize=div(TV->y1-TV->y+1,TV->SymSize).quot;

	TextButton* YesBtn=GMM.addTextButton(NULL,MPPLX>>1,MPPLY-60,GetTextByID("@MSOK"),&fntrb,&fntb,&fntb,1);
	YesBtn->UserParam=mcmOk;
	YesBtn->OnUserClick=&MMItemChoose;
	ItemChoose=-1;
	DrawPaperPanelShadow(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
	do{
		DrawPaperPanel(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
		ProcessMessages();
		if(KeyPressed&&(LastKey==13||LastKey==27)){
			KeyPressed=false;
			ItemChoose=mcmOk;
		};
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	ContinueGame=true;
	UnPress();
};
extern bool ProtectionMode;
int ProcessComplexQuestion(int Nx,char* Bmp1,byte or1,char* Text1,char* Bmp2,byte or2,char* Text2,char* Quest){
	int Lx=Nx<<6;
	DialogsSystem GMM((RealLx-Lx)>>1,80);
	SQPicture SPU;
	SPU.PicPtr=NULL;
	LocalGP CPIC1;
	LocalGP CPIC2;
	int pid1=-1;
	int pid2=-1;
	char cc1[100];
	if(or1>2)or1=0;
	if(or2>2)or2=0;
	if(strcmp(Bmp1,"NONE")){
		sscanf(Bmp1,"%s%d",cc1,&pid1);
		if(pid1!=-1){
			CPIC1.Load(cc1);
		};
	};
	if(strcmp(Bmp2,"NONE")){
		sscanf(Bmp2,"%s%d",cc1,&pid2);
		if(pid2!=-1){
			CPIC2.Load(cc1);
		};
	};

	ResFile RF=RRewrite("tmp1.txt");
	RBlockWrite(RF,Text1,strlen(Text1));
	RClose(RF);
	RF=RRewrite("tmp2.txt");
	RBlockWrite(RF,Text2,strlen(Text2));
	RClose(RF);

	LocalGP LGP;
	LocalGP FONT("rom11");
	//LocalGP FONT1("rom11r");
	LocalGP FONTB("vinBig");
	LocalGP FONTRB("vinBig");

	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTRB.GPID);
	RLCFont f16x16w(FONT.GPID);
	RLCFont f16x16g(FONT.GPID);
	f16x16w.SetRedColor();
	fntrb.SetRedColor();

	int y0=16;
	int LX1=0;
	int LY1=0;
	int x0=16;
	int plx=0;
	if(pid1!=-1){
		LX1=GPS.GetGPWidth(CPIC1.GPID,pid1);
		LY1=GPS.GetGPHeight(CPIC1.GPID,pid1)+16;
		if(or1==1){
			GMM.addGPPicture(NULL,x0,y0,CPIC1.GPID,pid1);
			x0+=LX1;
			plx=LX1;
		}else if(or1==2){
			GMM.addGPPicture(NULL,Lx-16-LX1,y0,CPIC1.GPID,pid1);
			plx=LX1;
		}else{
			GMM.addGPPicture(NULL,(Lx-LX1)>>1,y0,CPIC1.GPID,pid1);
			y0+=LY1+8;
		};
	};
	TextViewer* TV1;
	TextViewer* TV2;
	TV1=GMM.addTextViewer(NULL,x0,y0,Lx-32-plx,1000,"tmp1.txt",&f16x16w);
	TV1->Enabled=0;
	int dy=TV1->NLines*TV1->SymSize;
	if(or1)y0+=dy>LY1?dy:LY1;
	else y0+=dy;
	int LX2=0;
	int LY2=0;
	x0=16;
	plx=0;
	if(pid2!=-1){
		LX2=GPS.GetGPWidth(CPIC2.GPID,pid2);
		LY2=GPS.GetGPHeight(CPIC2.GPID,pid2)+16;
		if(or2==1){
			GMM.addGPPicture(NULL,x0,y0,CPIC2.GPID,pid2);
			x0+=LX2;
			plx=LX2;
		}else if(or2==2){
			GMM.addGPPicture(NULL,Lx-16-LX2,y0,CPIC2.GPID,pid2);
			plx=LX2;
		}else{
			GMM.addGPPicture(NULL,(Lx-LX1)>>1,y0,CPIC2.GPID,pid2);
			y0+=LY2+8;
		};
	}else y0+=18;;
	TV2=GMM.addTextViewer(NULL,x0,y0,Lx-32-plx,1000,"tmp2.txt",&f16x16g);
	TV2->Enabled=0;
	dy=TV2->NLines*TV2->SymSize;
	if(or1)y0+=dy>LY2?dy:LY2;
	else y0+=dy;
	int Ny=((y0+38)>>6)+1;
	int NTB=1;
	int LL=strlen(Quest);
	for(int j=0;j<LL;j++)if(Quest[j]=='|')NTB++;
	x0=Lx/2/NTB;
	int DX=Lx/NTB;
	char cc[128];
	int pos;
	for(int q=0;q<NTB;q++){
		pos=0;
		char c;
		do{
			c=Quest[0];
			if(c!='|'){
				cc[pos]=c;
				pos++;
				cc[pos]=0;
			};
			Quest++;
		}while(c!=0&&c!='|');
		TextButton* TB=GMM.addTextButton(NULL,x0+q*DX,Ny*64-33,GetTextByID(cc),&fntrb,&fntb,&fntb,1);
		TB->OnUserClick=&MMItemChoose;
		TB->UserParam=q;
		if(PlayGameMode){
			TB->Enabled=0;
			if(q==CurrentAnswer)TB->PassiveFont=&fntrb;
		};
	};
	int DDY=(RealLy-64*Ny)/2-80;
	GMM.BaseY+=DDY;
	for(int p=0;p<512;p++){
		if(GMM.DSS[p]&&GMM.DSS[p]->Visible){
			GMM.DSS[p]->y+=DDY;
			GMM.DSS[p]->y1+=DDY;
		};
	};
	ItemChoose=-1;
	DrawPaperPanelShadow((RealLx-Lx)>>1,80+DDY-32,((RealLx-Lx)>>1)+Lx,80+DDY+Ny*64+20);
	int T0=GetTickCount();
	do{
		ProcessMessages();
		//if(KeyPressed&&(LastKey==13||LastKey==27)){
		//	KeyPressed=false;
		//	ItemChoose=mcmOk;
		//};
		DrawPaperPanel((RealLx-Lx)>>1,80+DDY-32,((RealLx-Lx)>>1)+Lx,80+DDY+Ny*64+20);
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
		if(PlayGameMode&&GetTickCount()-T0>5000)ItemChoose=CurrentAnswer;
	}while(ItemChoose==-1);
	ContinueGame=true;
	UnPress();
	return ItemChoose;
};
int ProcessMultilineQuestion(int Nx,char* Bmp1,byte or1,char* Text1,char* Quest){
	int Lx=Nx<<6;
	DialogsSystem GMM((RealLx-Lx)>>1,80);
	SQPicture SPU;
	SPU.PicPtr=NULL;
	LocalGP CPIC1;
	int pid1=-1;
	int pid2=-1;
	char cc1[100];
	if(or1>2)or1=0;
	if(strcmp(Bmp1,"NONE")){
		sscanf(Bmp1,"%s%d",cc1,&pid1);
		if(pid1!=-1){
			CPIC1.Load(cc1);
		};
	};

	ResFile RF=RRewrite("tmp1.txt");
	RBlockWrite(RF,Text1,strlen(Text1));
	RClose(RF);

	LocalGP LGP;
	LocalGP FONT("rom11");
	LocalGP FONT1("rom11r");
	LocalGP FONTB("vinBig");
	LocalGP FONTRB("vinBig");

	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTRB.GPID);
	RLCFont f16x16w(FONT.GPID);
	RLCFont f16x16g(FONT.GPID);
	f16x16w.SetRedColor();
	fntrb.SetRedColor();

	int y0=16;
	int LX1=0;
	int LY1=0;
	int x0=16;
	int plx=0;
	if(pid1!=-1){
		LX1=GPS.GetGPWidth(CPIC1.GPID,pid1);
		LY1=GPS.GetGPHeight(CPIC1.GPID,pid1)+16;
		if(or1==1){
			GMM.addGPPicture(NULL,x0,y0,CPIC1.GPID,pid1);
			x0+=LX1;
			plx=LX1;
		}else if(or1==2){
			GMM.addGPPicture(NULL,Lx-16-LX1,y0,CPIC1.GPID,pid1);
			plx=LX1;
		}else{
			GMM.addGPPicture(NULL,(Lx-LX1)>>1,y0,CPIC1.GPID,pid1);
			y0+=LY1+8;
		};
	};
	TextViewer* TV1;
	
	TV1=GMM.addTextViewer(NULL,x0,y0,Lx-32-plx,1000,"tmp1.txt",&f16x16w);
	TV1->Enabled=0;
	int dy=TV1->NLines*TV1->SymSize;
	if(or1)y0+=dy>LY1?dy:LY1;
	else y0+=dy;
	
	int NTB=1;
	int LL=strlen(Quest);
	for(int j=0;j<LL;j++)if(Quest[j]=='|')NTB++;
	x0=0;//Lx/2;
	//int DX=Lx/NTB;
	//int Ny=((y0+38)>>6)+1;
	int dst=40;
	//int Ny1=Ny+((NTB*dst)>>6);
	int qy0=y0+32;//Ny1*64-dst*NTB+10;
	char cc[128];
	int pos;
	TextViewer* TVQ[16];
	for(int q=0;q<NTB;q++){
		pos=0;
		char c;
		do{
			c=Quest[0];
			if(c!='|'){
				cc[pos]=c;
				pos++;
				cc[pos]=0;
			};
			Quest++;
		}while(c!=0&&c!='|');
		char fc[100];
		sprintf(fc,"tmpf%d.txt",q);
		GFILE* f=Gopen(fc,"w");
		Gprintf(f,"%s",GetTextByID(cc));
		Gclose(f);
		TVQ[q]=GMM.addTextViewer(NULL,x0+32,qy0,Lx-64,300,fc,&f16x16g);
		TVQ[q]->y1=TVQ[q]->y+TVQ[q]->NLines*TVQ[q]->SymSize+4;
		qy0+=TVQ[q]->NLines*TVQ[q]->SymSize+16;
		//TextButton* TB=GMM.addTextButton(NULL,x0,qy0+q*dst,GetTextByID(cc),&fntrb,&fntb,&fntb,1);
		TVQ[q]->OnUserClick=&MMItemChoose;
		TVQ[q]->UserParam=q;
		if(PlayGameMode){
			TVQ[q]->Enabled=0;
		};
	};
	qy0+=32;
	int DDY=(RealLy-qy0)/2-80;//(RealLy-64*Ny1)/2-80;
	GMM.BaseY+=DDY;
	for(int p=0;p<512;p++){
		if(GMM.DSS[p]&&GMM.DSS[p]->Visible){
			GMM.DSS[p]->y+=DDY;
			GMM.DSS[p]->y1+=DDY;
		};
	};
	ItemChoose=-1;
	//DrawPaperPanelShadow((RealLx-Lx)>>1,80+DDY-32,((RealLx-Lx)>>1)+Lx,80+DDY+Ny1*64+20);
	DrawPaperPanel((RealLx-Lx)>>1,80+DDY-32,((RealLx-Lx)>>1)+Lx,80+DDY+qy0/*Ny1*64+20*/);
	int T0=GetTickCount();
	do{
		if(PlayGameMode){
			for(int i=0;i<NTB;i++){
				if(i==CurrentAnswer)TVQ[i]->Font=&f16x16w;
				else TVQ[i]->Font=&f16x16g;
			};
		}else{
			for(int i=0;i<NTB;i++){
				if(TVQ[i]->MouseOver)TVQ[i]->Font=&f16x16w;
				else TVQ[i]->Font=&f16x16g;
			};
		};
		ProcessMessages();
		//if(KeyPressed&&(LastKey==13||LastKey==27)){
		//	KeyPressed=false;
		//	ItemChoose=mcmOk;
		//};
		DrawPaperPanel((RealLx-Lx)>>1,80+DDY-32,((RealLx-Lx)>>1)+Lx,80+DDY+qy0/*Ny1*64+20*/);
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
		if(PlayGameMode&&GetTickCount()-T0>5000)ItemChoose=CurrentAnswer;
	}while(ItemChoose==-1);
	ContinueGame=true;
	UnPress();
	return ItemChoose;
};
void ProcessMissionText(char* Bmp,char* Text){
	ItemChoose=-1;
	int MPPLX=GETV("MPPLX");
	int MPPLY=GETV("MPPLY");
	int MPLDX=GETV("MPLDX");
	int MPRDX=GETV("MPRDX");
	int MPDDY=GETV("MPDDY");
	int MPUDY=GETV("MPDDY");
	//char* BmpName=GETS("@MISSPANEL");
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(MPPLX>>1),smapy+(mul3(nsmaply)<<2)-(MPPLY>>1));
	//SQPicture SP(BmpName);
	
	SQPicture SPU;
	SPU.PicPtr=NULL;
	LocalGP CPIC;
	int pid=-1;
	char cc1[100];
	if(strcmp(Bmp,"NONE")){
		sscanf(Bmp,"%s%d",cc1,&pid);
		if(pid!=-1){
			CPIC.Load(cc1);
		};
	};

	ResFile RF=RRewrite("tmp.txt");
	RBlockWrite(RF,Text,strlen(Text));
	RClose(RF);
	LocalGP LGP;
	LocalGP FONT("rom11");
	LocalGP FONTB("vinBig");
	//LocalGP FONTRB("vinrBig");
	RLCFont f16x16w(FONT.GPID);//"rom11.rlc");
	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTB.GPID);
	fntrb.SetRedColor();
	//RLCFont f16x16w(FONT.GPID);//"rom11.rlc");
	/*
	if(strstr(BmpName,".bmp")){
		//GMM.addPicture(NULL,0,0,&SP,&SP,&SP);
	}else{
		LGP.Load(BmpName);
		GPS.ShowGP(GMM.BaseX,GMM.BaseY,LGP.GPID,0,0);
		GMM.addGPPicture(NULL,0,0,LGP.GPID,1);
	};
	*/
	//int DY=0;
	//if(SPU.PicPtr){
	//	GMM.addPicture(NULL,0,0,&SPU,&SPU,&SPU);
	//	DY=SPU.GetLy();
	//};
	int LX=0;
	int LY=0;
	if(pid!=-1){
		LX=GPS.GetGPWidth(CPIC.GPID,pid);
		LY=GPS.GetGPHeight(CPIC.GPID,pid)+16;
		GMM.addGPPicture(NULL,(MPPLX-LX)>>1,MPUDY,CPIC.GPID,pid);
	};
	LocalGP SCROL("Interface\\PScroll");
	VScrollBar* SB=GMM.addNewGP_VScrollBar(NULL,MPPLX-MPRDX+5-4,MPUDY+LY,MPPLY-MPDDY-MPUDY-LY-40,1,0,SCROL.GPID,0);
	TextViewer* TV;
	TV=GMM.addTextViewer(NULL,MPLDX-6,MPUDY+LY,MPPLX-MPLDX-MPRDX-6,MPPLY-MPDDY-MPUDY-LY-40,"tmp.txt",&f16x16w);
	TV->AssignScroll(SB);
	TextButton* YesBtn=GMM.addTextButton(NULL,MPPLX>>1,MPPLY-60,GetTextByID("@MSOK"),&fntrb,&fntb,&fntb,1);
	YesBtn->UserParam=mcmOk;
	YesBtn->OnUserClick=&MMItemChoose;
	if(PlayGameMode){
		YesBtn->Enabled=0;
	};
	ItemChoose=-1;
	DrawPaperPanelShadow(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
	int T0=GetTickCount();
	do{
		DrawPaperPanel(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
		ProcessMessages();
		if(KeyPressed&&(LastKey==13||LastKey==27)){
			KeyPressed=false;
			ItemChoose=mcmOk;
		};
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
		if(PlayGameMode&&GetTickCount()-T0>5000)ItemChoose=mcmOk;
	}while(ItemChoose==-1);
	ContinueGame=true;
	UnPress();
};
int ShowHistryItem(char* Bmp,char* Text,bool Shadow){
	ItemChoose=-1;
	int MPPLX=GETV("MPPLX");
	int MPPLY=GETV("MPPLY");
	int MPLDX=GETV("MPLDX");
	int MPRDX=GETV("MPRDX");
	int MPDDY=GETV("MPDDY");
	int MPUDY=GETV("MPDDY");
	//char* BmpName=GETS("@MISSPANEL");
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(MPPLX>>1),smapy+(mul3(nsmaply)<<2)-(MPPLY>>1));
	//SQPicture SP(BmpName);
	
	SQPicture SPU;
	SPU.PicPtr=NULL;
	//if(strcmp(Bmp,"NONE")){
	//	SPU.LoadPicture(Bmp);
	//};

	ResFile RF=RRewrite("tmp.txt");
	RBlockWrite(RF,Text,strlen(Text));
	RClose(RF);
	LocalGP LGP;
	LocalGP FONT("rom11");
	LocalGP FONTB("vinBig");
	//LocalGP FONTRB("vinrBig");
	RLCFont f16x16w(FONT.GPID);//"rom11.rlc");
	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTB.GPID);
	fntrb.SetRedColor();
	RLCFont fntw(FONTB.GPID);
	fntw.SetWhiteColor();
	//RLCFont f16x16w(FONT.GPID);//"rom11.rlc");
	LocalGP CPIC;
	int pid=-1;
	char cc1[100];
	if(strcmp(Bmp,"NONE")){
		sscanf(Bmp,"%s%d",cc1,&pid);
		if(pid!=-1){
			CPIC.Load(cc1);
		};
	};
	/*
	if(strstr(BmpName,".bmp")){
		//GMM.addPicture(NULL,0,0,&SP,&SP,&SP);
	}else{
		LGP.Load(BmpName);
		if(Shadow)GPS.ShowGP(GMM.BaseX,GMM.BaseY,LGP.GPID,0,0);
		GMM.addGPPicture(NULL,0,0,LGP.GPID,1);
	};
	*/
	int DY=0;
	if(SPU.PicPtr){
		GMM.addPicture(NULL,0,0,&SPU,&SPU,&SPU);
		DY=SPU.GetLy();
	};
	int LX=0;
	int LY=0;
	if(pid!=-1){
		LX=GPS.GetGPWidth(CPIC.GPID,pid);
		LY=GPS.GetGPHeight(CPIC.GPID,pid);
		GMM.addGPPicture(NULL,(MPPLX-LX)>>1,MPUDY,CPIC.GPID,pid);
	};
	LocalGP SCROL("Interface\\PScroll");
	GMM.addTextButton(NULL,MPPLX>>1,-27,GetTextByID("MHISTORY"),&fntw,&fntw,&fntw,1);
	VScrollBar* SB=GMM.addNewGP_VScrollBar(NULL,MPPLX-MPRDX+5-6,MPUDY+LY,MPPLY-MPDDY-MPUDY-LY-40,1,0,SCROL.GPID,0);
	TextViewer* TV;
	TV=GMM.addTextViewer(NULL,MPLDX-6,MPUDY+LY,MPPLX-MPLDX-MPRDX-6,MPPLY-MPDDY-MPUDY-LY-40,"tmp.txt",&f16x16w);
	TV->AssignScroll(SB);
	ItemChoose=-1;

	TextButton* YesBtn=GMM.addTextButton(NULL,MPPLX/6,MPPLY-60,GetTextByID("@MSPREV"),&fntrb,&fntb,&fntb,1);
	YesBtn->UserParam=1;
	YesBtn->OnUserClick=&MMItemChoose;

	TextButton* NoBtn=GMM.addTextButton(NULL,MPPLX/2,MPPLY-60,GetTextByID("@MSNEXT"),&fntrb,&fntb,&fntb,1);
	NoBtn->UserParam=2;
	NoBtn->OnUserClick=&MMItemChoose;

	TextButton* CBtn=GMM.addTextButton(NULL,5*MPPLX/6,MPPLY-60,GetTextByID("@MSCANCEL"),&fntrb,&fntb,&fntb,1);
	CBtn->UserParam=3;
	CBtn->OnUserClick=&MMItemChoose;

	DrawPaperPanelShadow(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
	do{
		DrawPaperPanel(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13)ItemChoose=3;
			else if(LastKey==27)ItemChoose=3;
			KeyPressed=false;
		};
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
	}while(ItemChoose==-1);
	return ItemChoose;
	ContinueGame=true;
	UnPress();
};
bool AskMissionQuestion(char* Bmp,char* Text){
	ItemChoose=-1;
	int MPPLX=GETV("MPPLX");
	int MPPLY=GETV("MPPLY");
	int MPLDX=GETV("MPLDX");
	int MPRDX=GETV("MPRDX");
	int MPDDY=GETV("MPDDY");
	int MPUDY=GETV("MPDDY");
	//char* BmpName=GETS("@MISSPANEL");
	DialogsSystem GMM(smapx+(nsmaplx<<4)-(MPPLX>>1),smapy+(mul3(nsmaply)<<2)-(MPPLY>>1));
	//SQPicture SP(BmpName);
	
	SQPicture SPU;
	SPU.PicPtr=NULL;
	//if(strcmp(Bmp,"NONE")){
	//	SPU.LoadPicture(Bmp);
	//};

	ResFile RF=RRewrite("tmp.txt");
	RBlockWrite(RF,Text,strlen(Text));
	RClose(RF);
	LocalGP LGP;
	LocalGP FONT("rom11");
	LocalGP FONTB("vinBig");
	//LocalGP FONTRB("vinrBig");
	RLCFont f16x16w(FONT.GPID);//"rom11.rlc");
	RLCFont fntb(FONTB.GPID);
	RLCFont fntrb(FONTB.GPID);
	fntrb.SetRedColor();
	LocalGP CPIC;
	int pid=-1;
	char cc1[100];
	if(strcmp(Bmp,"NONE")){
		sscanf(Bmp,"%s%d",cc1,&pid);
		if(pid!=-1){
			CPIC.Load(cc1);
		};
	};
	/*
	if(strstr(BmpName,".bmp")){
		//GMM.addPicture(NULL,0,0,&SP,&SP,&SP);
	}else{
		LGP.Load(BmpName);
		GPS.ShowGP(GMM.BaseX,GMM.BaseY,LGP.GPID,0,0);
		GMM.addGPPicture(NULL,0,0,LGP.GPID,1);
	};
	*/
	int DY=0;
	if(SPU.PicPtr){
		GMM.addPicture(NULL,0,0,&SPU,&SPU,&SPU);
		DY=SPU.GetLy();
	};
	int LX=0;
	int LY=0;
	if(pid!=-1){
		LX=GPS.GetGPWidth(CPIC.GPID,pid);
		LY=GPS.GetGPHeight(CPIC.GPID,pid);
		GMM.addGPPicture(NULL,(MPPLX-LX)>>1,MPUDY,CPIC.GPID,pid);
	};
	TextViewer* TV;
	TV=GMM.addTextViewer(NULL,MPLDX,MPUDY+LY,MPPLX-MPLDX-MPRDX,MPPLY-LY-MPDDY-MPUDY-40,"tmp.txt",&f16x16w);
	ItemChoose=-1;

	TextButton* YesBtn=GMM.addTextButton(NULL,MPPLX/4,441,GetTextByID("@MSYES"),&fntrb,&fntb,&fntb,1);
	YesBtn->UserParam=mcmOk;
	YesBtn->OnUserClick=&MMItemChoose;
	if(PlayGameMode){
		if(CurrentAnswer)YesBtn->PassiveFont=&fntrb;
		YesBtn->Enabled=1;
	};

	TextButton* NoBtn=GMM.addTextButton(NULL,MPPLX*3/4,441,GetTextByID("@MSNO"),&fntrb,&fntb,&fntb,1);
	NoBtn->UserParam=mcmCancel;
	NoBtn->OnUserClick=&MMItemChoose;
	if(PlayGameMode){
		if(!CurrentAnswer)NoBtn->PassiveFont=&fntrb;
		NoBtn->Enabled=1;
	};

	DrawPaperPanelShadow(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
	int T0=GetTickCount();
	do{
		DrawPaperPanel(GMM.BaseX,GMM.BaseY,GMM.BaseX+MPPLX,GMM.BaseY+MPPLY);
		ProcessMessages();
		if(KeyPressed){
			if(LastKey==13)ItemChoose=mcmOk;
			else if(LastKey==27)ItemChoose=mcmCancel;
			KeyPressed=false;
		};
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		GMM.RefreshView();
		if(PlayGameMode&&GetTickCount()-T0>5000){
			ItemChoose=CurrentAnswer==0?mcmCancel:mcmOk;
		};
	}while(ItemChoose==-1);
	ContinueGame=true;
	UnPress();
	if(ItemChoose==mcmOk)return true;
	else return false;
};
//----------------------MiniMap editor interface------------------
SQPicture trans1u;
SQPicture trans1p;
SQPicture trans2u;
SQPicture trans2p;
SQPicture trans3u;
SQPicture trans3p;
SQPicture trans4u;
SQPicture trans4p;
SQPicture trans5u;
SQPicture trans5p;
SQPicture trans6u;
SQPicture trans6p;
SQPicture pen1u;
SQPicture pen1p;
SQPicture pen2u;
SQPicture pen2p;
SQPicture x480;
SQPicture getc_p;
SQPicture getc_u;
SQPicture btflu;
SQPicture btflu0;
SQPicture btrough;
SQPicture btrough0;
SQPicture btsoft;
SQPicture btsoft0;
SQPicture btless;
SQPicture btless0;
SQPicture prepu;
SQPicture prepp;
byte* higrad;
int grsize;
#ifdef MAKE_PTC
SFLB_DLLEXPORT SFLB_LoadMEDButtons(){
	
	ResFile f1=RReset("higrad.set");
	grsize=RFileSize(f1);
	higrad=new byte[grsize];
	RBlockRead(f1,higrad,grsize);
	RClose(f1);
};
#endif
//-------------------MiniMap images----------------
int HiLx;
int HiLy;
int HiStepX;
int HiStepY;
int winX;
int winY;
int winX1;
int winY1;
byte* HiMap;
byte* HiMap1;

void SetupHiMap(){
	if(RealLx>=1024){
		HiLx=496;//248;
		HiLy=496;
	}else{
		HiLx=248;
		HiLy=248;
	};
	HiStepX=div(msx<<(8+5),HiLx).quot;
	HiStepY=div(msy<<(8+5),HiLy).quot;
	HiMap=new byte[HiLx*HiLy];
	HiMap1=new byte[HiLx*HiLy];
};
void DeleteHiMap(){
	free(HiMap);
	free(HiMap1);
};
void CreateHiMap(){
	int mpx=256;
	int mpy=256;
	for(int iy=0;iy<HiLy;iy++){
		for(int ix=0;ix<HiLx;ix++){
			int Hig=GetHeight(mpx>>8,mpy>>8)>>4;
			if(Hig<0)Hig=0;
			if(Hig<grsize)Hig=higrad[Hig];else Hig=higrad[grsize-1];
			HiMap[ix+iy*HiLx]=Hig;
			mpx+=HiStepX;
		};
		mpx=256;
		mpy+=HiStepY;
	};
};
//----------------------LOADING THE FILE--------------------//
void CreateFilesList(char* Mask,ListBox* LB){
	WIN32_FIND_DATA FD;
	HANDLE H=FindFirstFile(Mask,&FD);
	if(H!=INVALID_HANDLE_VALUE){
		do{
			LB->AddItem(FD.cFileName,0);
		}while(FindNextFile(H,&FD));
		FindClose(H);
	};
};
bool ProcessLoadingFile(char* Mask,char* DestName,int Header){
	LocalGP HBTN("Interface\\LoadSaveBM");
	LocalGP BTNS("Interface\\G_Load_Game");
	LocalGP SCROL("Interface\\GScroll");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	//LoadPointer("cur_mn.rlc");
	int dx=(RealLx-470)>>1;
	int dy=(RealLy-415)>>1;
	DialogsSystem MMenu(dx,dy);
	GPS.ShowGP(dx,dy,BTNS.GPID,4,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	MMenu.addGPPicture(NULL,0,0,BTNS.GPID,5);
	VScrollBar* VSB=MMenu.addNewGP_VScrollBar(NULL,436,55,276,1,0,SCROL.GPID,0);
	ListBox* LB=MMenu.addGP_ListBox(NULL,29,61,10,BTNS.GPID,6,26,&WhiteFont,&YellowFont,VSB);

	//VScrollBar* VS=DSY.addVScrollBar(PIC1,LB->x-DSY.BaseX+LB->oneLx-1,1+LB->y-DSY.BaseY,1000,4,&sb_up_d,&sb_up_e,&sb_up_p,&sb_dn_d,&sb_dn_e,&sb_dn_p,&sb_vbare,&sb_vbar,&sb_btn);
	//LB->VS=VS;226x241
	GPPicture* HDR=MMenu.addGPPicture(NULL,28,31,HBTN.GPID,Header);
	GP_Button* OkBtn=MMenu.addGP_Button(NULL,49,353,HBTN.GPID,2,0);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=MMenu.addGP_Button(NULL,269,353,BTNS.GPID,2,3);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	CreateFilesList(Mask,LB);
	ItemChoose=-1;
	int pp=1;
	int LastCTime=GetRealTime();
	LastKey=0;
	do{
		MMenu.MarkToDraw();
		ProcessMessages();
		StdKeys();
		if(LB->CurItem==-1){
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		}else OkBtn->Enabled=true;
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk&&LB->CurItem!=-1&&LB->NItems){
		strcpy(DestName,LB->GetItem(LB->CurItem)->Message);
		ClearMStack();
		ItemChoose=-1;
		UnPress();
		return true;
	};
	ClearMStack();
	ItemChoose=-1;
	UnPress();
	return false;
};
bool ProcessSavingFile(char* Mask,char* DestName,int Header,bool clear){
	LocalGP HBTN("Interface\\LoadSaveBM");
	LocalGP BTNS("Interface\\G_Save_Game");
	LocalGP SCROL("Interface\\GScroll");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	//LoadPointer("cur_mn.rlc");
	int dx=(RealLx-470)>>1;
	int dy=(RealLy-415)>>1;
	DialogsSystem MMenu(dx,dy);
	GPS.ShowGP(dx,dy,BTNS.GPID,4,0);
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;
	//Picture* PIC=MMenu.addPicture(NULL,0,0,&MnPanel,&MnPanel,&MnPanel);
	//MMenu.addGPPicture(NULL,dx,dy,BTNS.GPID,0);
	MMenu.addGPPicture(NULL,0,0,BTNS.GPID,5);
	VScrollBar* VSB=MMenu.addNewGP_VScrollBar(NULL,436,55,247,1,0,SCROL.GPID,0);
	ListBox* LB=MMenu.addGP_ListBox(NULL,29,61,9,BTNS.GPID,6,26,&WhiteFont,&YellowFont,VSB);

	GPPicture* HDR=MMenu.addGPPicture(NULL,28,31,HBTN.GPID,Header);
	GP_Button* OkBtn=MMenu.addGP_Button(NULL,49,353,HBTN.GPID,5,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=MMenu.addGP_Button(NULL,269,353,BTNS.GPID,2,3);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	if(clear)DestName[0]=0;
	InputBox* IB=MMenu.addInputBox(NULL,114,306,DestName,35,310,20,&YellowFont,&WhiteFont);
	IB->Active=true;
	ItemChoose=-1;
	CreateFilesList(Mask,LB);
	LB->CurItem=-1;
	int LastCTime=GetRealTime();
	int PrevListVal=LB->CurItem;
	KeyPressed=false;
	do{
		if(PrevListVal!=LB->CurItem){
			PrevListVal=LB->CurItem;
			strcpy(IB->Str,LB->GetItem(LB->CurItem)->Message);
			//IB->Str[strlen(IB->Str)-4]=0;
		};
		MMenu.MarkToDraw();
		ProcessMessages();
		StdKeys();
		//if(LB->CurItem==-1)OkBtn->Enabled=false;
		//else OkBtn->Enabled=true;
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(strlen(IB->Str)){
			OkBtn->Enabled=true;
		}else{
			OkBtn->Enabled=false;
			if(ItemChoose==mcmOk)ItemChoose=-1;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		ClearMStack();
		ItemChoose=-1;
		UnPress();
		return true;
	};
	ClearMStack();
	ItemChoose=-1;
	UnPress();
	return false;
};
//------------------TRANSFORMATIONS LIBRARY-----------------
int xc,yc;//center of the transformation
static int HiMode=0;
static int tpr1=256;//Height
static int tpr2=0;  //R1
static int tpr3=256;//R2
static int tpr4=512;//frquency
static int tpr5=512;//Amplitude
static int tpr6=512;//Phase
static int HiBrush=0;
static int HiRound=0;
int getR(double a,int r){
	int nn=tpr4>>6;
	double tm=double(GetRealTime())/1000;
	return int(r*((sin(a*(nn)+tpr6/256+tm)+
				   sin(a*(nn+1)+tpr6/256+tm*1.5)+
				   sin(a*(nn+2)+tpr6/256-tm/2)+
				   sin(a*(nn+3)+tpr6/256+tm*1.4)+
				   sin(a*(nn+4)+tpr6/256-tm*1.5)+
				   sin(a*(nn+5)+tpr6/256+tm*1.3)+
				   sin(a*(nn+6)+tpr6/256-tm*1.1)+
				   sin(a*(nn+7)+tpr6/256+tm*0.8)+
				   sin(a*(nn+8)+tpr6/256+tm*0.7)+
				   sin(a*(nn+9)+tpr6/256+tm*0.6)
				   )/10+
		+1+(tpr5>>6))/(2+(tpr5>>6)));
};
void Pix(int x,int y,byte c){
	if(x>=winX&&y>=winY&&x<winX1&&y<winY1){
		(HiMap1+x-winX+(y-winY)*HiLx)[0]=c;
		//((byte*)(int(ScreenPtr)+x+y*SCRSizeX))[0]=c;
		//((byte*)(int(RealScreenPtr)+x+y*RSCRSizeX))[0]=c;
	};
};
void Circ(int x,int y,int r,int n,byte c){
	r=(r*HiLx)/496;
	if(HiRound==1){
		for(int i=0;i<n;i++){
			double alpha=3.1415*2*i/n;
			int r2=getR(alpha,r);
			Pix(int(x+r2*sin(alpha)),int(y+r2*cos(alpha)),c);
		};
	}else{
		double time=double(GetRealTime())/1000;
		for(int i=0;i<n;i++){
			double alpha=3.1415*2*i/n;
			Pix(int(x+r*sin(alpha)),int(y+r*cos(alpha)),c);
		};
	};
};
int func1(int r){
	if(r<tpr2)return 1024;
	if(r>tpr2+tpr3)return 0;
	int dr=r-tpr2-(tpr3>>1);
	if(dr>0)return div((tpr2+tpr3-r)*(tpr2+tpr3-r)<<11,tpr3*tpr3).quot;
	else return 1024-div((r-tpr2)*(r-tpr2)<<11,tpr3*tpr3).quot;
};

int func2(int r){
	if(r<tpr2)return 1024;
	if(r>tpr2+tpr3)return 0;
	int dr=r-tpr2-tpr3;
	return div((dr*dr)<<10,tpr3*tpr3).quot;
};
int func3(int r){
	if(r<tpr2)return 1024;
	if(r>tpr2+tpr3)return 0;
	int dr=tpr2-r;
	return 1024-div((dr*dr)<<10,tpr3*tpr3).quot;
};
int func4(int r){
	if(r<tpr2)return 1024;
	if(r>tpr2+tpr3)return 0;
	int dr=r-tpr2;
	return div(dr<<10,tpr3).quot;
};
int func5(int r){
	if(r<tpr2)return 1024;
	if(r>tpr2+tpr3)return 0;
	int dr=r-tpr2-(tpr3>>1);
	if(dr>0)return div((tpr2+tpr3-r)*(tpr2+tpr3-r)<<11,tpr3*tpr3).quot;
	else return 1024-div((r-tpr2)*(r-tpr2)<<11,tpr3*tpr3).quot;
};
typedef int fpar(int);
int UniTrans(int x,int y,int Hi,fpar* ff1){
	if(!tpr3)tpr3=1;
	int pk;
	int r=int(sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc)));
	if(HiRound==1){
		int tp2=tpr2;
		int tp3=tpr3;
		double ang=atan2(x-xc,y-yc);
		tpr2=getR(ang,tpr2);
		tpr3=getR(ang,tpr3);
		pk=ff1(r);
		tpr2=tp2;
		tpr3=tp3;
	}else pk=ff1(r);
	switch(HiMode){
	case 0:
		return Hi+(((tpr1-Hi)*pk)>>10);
	case 1:{
				int za=(GetHeight(x-32,y)+GetHeight(x+32,y)+
				   GetHeight(x,y-32)+GetHeight(x,y+32))>>2;
				return div(tpr1*za+(Hi<<9),512+tpr1).quot;
		   };
	case 2:
		return Hi+((tpr1*pk)>>15);
	case 3:
		pk=Hi-((tpr1*pk)>>15);
		if(pk<0)pk=0;
		return pk;
	default:
		return Hi;
	};
};
int Transf1(int x,int y,int Hi){
	return UniTrans(x,y,Hi,&func1);
};
int Transf2(int x,int y,int Hi){
	return UniTrans(x,y,Hi,&func2);
};
int Transf3(int x,int y,int Hi){
	return UniTrans(x,y,Hi,&func3);
};
int Transf4(int x,int y,int Hi){
	return UniTrans(x,y,Hi,&func4);
};
int Transf5(int x,int y,int Hi){
	return UniTrans(x,y,Hi,&func5);
};
//----------------------------------------------------------
void CopyToOffScreen(int zx,int zy,
					 int srLx,int srLy,
					 byte* data);
void CopyToRealScreen(int zx,int zy,
					 int srLx,int srLy,
					 byte* data);
void CreateMiniMap();
void ClearRender();
int mul3(int);
bool PrepareMap(SimpleDialog* SD){
	for(int x=0;x<VertInLine;x++){
		for(int y=MaxTH-2;y>0;y--){
			int vert=x+y*VertInLine;
			int hi0=(mul3(GetTriY(vert))>>2)-THMap[vert];
			int hi1=(mul3(GetTriY(vert+VertInLine))>>2)-THMap[vert+VertInLine];
			if(hi1-hi0<0)THMap[vert]+=hi0-hi1;
		};
	};
	ItemChoose=-2;
	return true;
};
bool RandomMap(SimpleDialog* SD){
	for(int x=0;x<VertInLine;x++){
		for(int y=MaxTH-2;y>0;y--){
			int vert=x+y*VertInLine;
			THMap[vert]+=((rando()&3)<<1)-3;
		};
	};
	ItemChoose=-2;
	return true;
};
bool LoadBitmapLikeGrayscale(char* Name,int* Lx,int* Ly,byte** res);
int GetResVal(byte* res,int LX,int LY,int RLX,int RLY,int x,int y);
bool LoadClick(SimpleDialog* SD){
	char BMPS[128];
	if(ProcessLoadingFile("UserBitmaps\\*.bmp",BMPS,3)){
		byte* DATA;
		char NAME[128];
		sprintf(NAME,"UserBitmaps\\%s",BMPS);
		int LX,LY;
		if(LoadBitmapLikeGrayscale(NAME,&LX,&LY,&DATA)){
			int maxx=7680<<ADDSH;
			int maxv=(MaxTH+1)*MaxTH;
			for(int i=0;i<maxv;i++){
				int x=GetTriX(i);
				int y=GetTriY(i);
				THMap[i]=GetResVal(DATA,LX,LY,maxx,maxx,x,y);
			};
		};
	};
	ItemChoose=-2;
	return true;
};
int MapGP=-1;
void ProcessTerrainEditor();
void EditMiniMap(){
	SetupHiMap();
	CreateHiMap();
	//Loading resources
	LocalGP BTNS("Interface\\EditRelief");
	int BTDX;
	int BTDY;
	int SCROLDX;
	int SCROLDY;
	int TLX;
	int TLY;
	int SID;
	int pdx;
	int pdy;
	int LOADDX;
	if(RealLx<1024){
		BTDX=0;
		BTDY=0;
		SCROLDX=0;
		SCROLDY=0;
		TLX=519;
		TLY=466;
		SID=0;
		pdx=4;
		pdy=3;
		LOADDX=0;
	}else{
		BTDX=121;
		BTDY=659-421+2;
		SCROLDX=540-301;
		SCROLDY=0;
		TLX=760;
		TLY=698;
		SID=47;
		pdx=0;
		pdy=0;
		LOADDX=656-415-1;
	};

	//Implementation
	short* VERHI=new short[(MaxTH+1)*MaxTH];
	memcpy(VERHI,THMap,(MaxTH+1)*MaxTH*2);
	DialogsSystem EMM((RealLx-TLX)>>1,(RealLy-TLY)>>1);
	GPPicture* PIC=EMM.addGPPicture(NULL,0,0,BTNS.GPID,SID);

	//EMM.addGPPicture(NULL,0,0,BTNS.GPID,1);
	

	GP_Button* PrepareBtn=EMM.addGP_Button(NULL,199+BTDX,421+BTDY,BTNS.GPID,6,7);
	PrepareBtn->OnUserClick=&PrepareMap;

	GP_Button* CancelBtn=EMM.addGP_Button(NULL,361+BTDX,421+BTDY,BTNS.GPID,3,2);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;

	GP_Button* OkBtn=EMM.addGP_Button(NULL,37+BTDX,421+BTDY,BTNS.GPID,5,4);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* LoadBtn=EMM.addGP_Button(NULL,415+LOADDX,343+BTDY,BTNS.GPID,33,32);
	LoadBtn->OnUserClick=&LoadClick;

	int scrox=GETV("RESCRX");
	int scroy=GETV("RESCRY");
	int DYY=12;

	VScrollBar* HB1=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,71+DYY,1024,64,MapGP+1,4,195,12,0,0);
	VScrollBar* HB2=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,116+DYY,1024,256,MapGP+1,4,195,12,0,0);
	VScrollBar* HB3=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,161+DYY,1024,512,MapGP+1,4,195,12,0,0);
	VScrollBar* HB4=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,206+DYY,1024,64,MapGP+1,4,195,12,0,0);
	VScrollBar* HB5=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,251+DYY,1024,64,MapGP+1,4,195,12,0,0);
	VScrollBar* HB6=EMM.addGP_ScrollBarL(NULL,302+SCROLDX,296+DYY,1024,64,MapGP+1,4,195,12,0,0);
	HB1->SPos=tpr1;
	HB2->SPos=tpr2;
	HB3->SPos=tpr3;
	HB4->SPos=tpr4;
	HB5->SPos=tpr5;
	HB6->SPos=tpr6;
	scrox=320-40;
	scroy=30;
	CheckBox* TRN1=EMM.addGP_CheckBox(NULL,31,358+BTDY,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,8,9,10);	
	CheckBox* TRN3=EMM.addGP_CheckBox(NULL,59,358+BTDY,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,11,12,13);
	CheckBox* TRN4=EMM.addGP_CheckBox(NULL,87,358+BTDY,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,14,15,16);	
	CheckBox* TRN5=EMM.addGP_CheckBox(NULL,115,358+BTDY,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,17,18,19);	
	CheckBox* TRN6=EMM.addGP_CheckBox(NULL,143,358+BTDY,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,20,21,22);	
	if(HiBrush==0)TRN1->State=1;
	if(HiBrush==1)TRN3->State=1;
	if(HiBrush==2)TRN4->State=1;
	if(HiBrush==3)TRN5->State=1;
	if(HiBrush==4)TRN6->State=1;
	
	CheckBox* Absolut=EMM.addGP_CheckBox(NULL,183,358+BTDY,"",&YellowFont,&YellowFont,2,0,BTNS.GPID,35,36,37);	
	CheckBox* Soft   =EMM.addGP_CheckBox(NULL,211,358+BTDY,"",&YellowFont,&YellowFont,2,0,BTNS.GPID,38,39,40);	
	CheckBox* More   =EMM.addGP_CheckBox(NULL,239,358+BTDY,"",&YellowFont,&YellowFont,2,0,BTNS.GPID,41,42,43);	
	CheckBox* Less   =EMM.addGP_CheckBox(NULL,267,358+BTDY,"",&YellowFont,&YellowFont,2,0,BTNS.GPID,44,45,46);	
	if(HiMode==0)Absolut->State=1;
	if(HiMode==1)Soft   ->State=1;
	if(HiMode==2)More   ->State=1;
	if(HiMode==3)Less   ->State=1;
	CheckBox* PEN1=EMM.addGP_CheckBox(NULL,307,358+BTDY,"",&YellowFont,&YellowFont,3,0,BTNS.GPID,23,24,25);	
	CheckBox* PEN2=EMM.addGP_CheckBox(NULL,335,358+BTDY,"",&YellowFont,&YellowFont,3,0,BTNS.GPID,26,27,28);	
	if(HiRound==0)PEN1->State=1;
	if(HiRound==1)PEN2->State=1;
	if(HiMode==0)Absolut->State=1;
	CheckBox* GETCL=EMM.addGP_CheckBox(NULL,375,358+BTDY,"",&YellowFont,&YellowFont,4,0,BTNS.GPID,29,30,31);	
	GETCL->Transparent=false;
	BPXView* BV=EMM.addBPXView(NULL,33+pdx,59+pdy,HiLx,HiLy,1,1,1,HiMap1,NULL);
	BV->EnableSelection=false;
	ItemChoose=-1;
	winX=BV->x;
	winY=BV->y;
	winX1=BV->x1;
	winY1=BV->y1;
	do{
		tpr1=HB1->SPos;
		tpr2=HB2->SPos;
		tpr3=HB3->SPos;
		tpr4=HB4->SPos;
		tpr5=HB5->SPos;
		tpr6=HB6->SPos;
		if(Absolut->State)HiMode=0;
		if(Soft   ->State)HiMode=1;
		if(More   ->State)HiMode=2;
		if(Less   ->State)HiMode=3;
		if(PEN1->State)HiRound=0;
		if(PEN2->State)HiRound=1;
		if(TRN1->State)HiBrush=0;
		if(TRN3->State)HiBrush=1;
		if(TRN4->State)HiBrush=2;
		if(TRN5->State)HiBrush=3;
		if(TRN6->State)HiBrush=4;
		if(ItemChoose==-2){
			CreateHiMap();
			ItemChoose=-1;
		};
		if(BV->MouseOver&&Lpressed&&!GETCL->State){
			xc=int((mouseX-BV->x)*HiStepX)>>8;
			yc=int((mouseY-BV->y)*HiStepY)>>8;
			if(TRN1->State)
				CreateEffect(xc,yc,tpr2+tpr3,&Transf1);
			//if(TRN2->State)
			//	CreateEffect(xc,yc,tpr2+tpr3,&Transf2);
			if(TRN3->State)
				CreateEffect(xc,yc,tpr2+tpr3,&Transf2);
			if(TRN4->State)
				CreateEffect(xc,yc,tpr2+tpr3,&Transf3);
			if(TRN5->State)
				CreateEffect(xc,yc,tpr2+tpr3,&Transf4);
			if(TRN6->State)
				CreateEffect(xc,yc,tpr2+tpr3,&Transf5);
			if(!HiMode)Lpressed=false;
			CreateHiMap();
			//EMM.MarkToDraw();
			GETCL->State=0;
			GETCL->NeedToDraw=true;
		};
		if(BV->MouseOver&&GETCL->State){
			xc=int((mouseX-BV->x)*HiStepX)>>8;
			yc=int((mouseY-BV->y)*HiStepY)>>8;
			HB1->SPos=GetHeight(xc,yc);
			CreateHiMap();
			if(Lpressed)GETCL->State=0;
			Lpressed=false;
			//EMM.MarkToDraw();
		};
		memcpy(HiMap1,HiMap,HiLx*HiLy);
		Circ(mouseX,mouseY,tpr2>>5,tpr2>>2,255);
		Circ(mouseX,mouseY,(tpr2+tpr3)>>5,(tpr2+tpr3)>>2,255);
		ProcessMessages();
		EMM.MarkToDraw();
		EMM.ProcessDialogs();
		//CopyToRealScreen(EMM.BaseX+24,EMM.BaseY+24,HiLx,HiLy,HiMap);
		EMM.RefreshView();
	}while(ItemChoose<0);
	DeleteHiMap();
	if(ItemChoose==mcmCancel){
		memcpy(THMap,VERHI,(MaxTH+1)*MaxTH*2);
	};
	free(VERHI);
	ItemChoose=-1;
	CreateMiniMap();
	ClearRender();
	UnPress();
};
//---------------------------------------------------------------//
//-------------/    Choosing elements of interface     \---------//
//-------------\         trees,stones,....             /---------//
//---------------------------------------------------------------//
int InteriorType;
word TreeItems[256];
word NTreeItems;
extern int BlobMode;
void ChooseTree(){
	SQPicture PAD("trees.bpx");
	SQPicture scr_Line("Scr_10.bpx");
	SQPicture scr_L("Scr_L.bpx");
	SQPicture scr_R("Scr_R.bpx");
	SQPicture scr_U_G("Scr_U_G.bpx");
	RLCFont f24y("gf24y.rlc");
	RLCFont f24w("gf24w.rlc");
	int mmlx=PAD.GetLx();
	int mmly=PAD.GetLy();
	DialogsSystem GMM(smapx+(smaplx<<4)-(mmlx>>1),smapy+(mul3(smaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&PAD,&PAD,&PAD);
	int RT;
	if(!GPS.RLCImage[TREES.FileID]){
		GPS.LoadGP(TREES.FileID);
	};
	RT=TREES.FileID;
	RLCListBox* RB=GMM.addRLCListBox(PIC1,83,62,384,255,RT,0,254);
	//RLCListBox* RB=GMM.addRLCListBox(PIC1,83,62,384,127,RT,0,254);
	//RLCListBox* RB1=GMM.addRLCListBox(PIC1,83,62+128,384,127,RT,0,254);
	VScrollBar* SB=GMM.addHScrollBar(PIC1,65,328,RB->MaxXpos,0,&scr_L,&scr_L,&scr_L,&scr_R,&scr_R,&scr_R,&scr_Line,&scr_Line,&scr_U_G);
	TextButton* OkBtn=GMM.addTextButton(PIC1,181,379-3,"Äà",&f24w,&f24y,&f24y,1);
	TextButton* CancelBtn=GMM.addTextButton(PIC1,365-3,379-3,"Îòìåíà",&f24w,&f24y,&f24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	ItemChoose=-1;
	do{
		ProcessMessages();
		RB->XPos=SB->SPos;
		//RB1->XPos=SB->SPos+322;
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		//if(RB->Done){
		//	memset(RB1->Choosed,0,RB->NItems);
		//	RB->Done=false;
		//};
		//if(RB1->Done){
		//	memset(RB->Choosed,0,RB->NItems);
		//	RB1->Done=false;
		//};
		//for(int z=0;z<RB->NItems;z++){
		//	RB->Choosed[z]|=RB1->Choosed[z];
		//	RB1->Choosed[z]|=RB->Choosed[z];
		//};
		GMM.RefreshView();
	}while(ItemChoose==-1);
	NTreeItems=0;
	if(ItemChoose==mcmOk){
		for(int z=0;z<RB->NItems;z++)if(RB->Choosed[z]&&NTreeItems<256){
			TreeItems[NTreeItems]=z;
			NTreeItems++;
		};
		if(NTreeItems){
			HeightEditMode=2;
			MEditMode=false;
			BlobMode=-1;
			InteriorType=0;
		};
	};
	UnPress();
};
void ChooseStone(){
	SQPicture PAD("stones.bpx");
	SQPicture scr_Line("Scr_10.bpx");
	SQPicture scr_L("Scr_L.bpx");
	SQPicture scr_R("Scr_R.bpx");
	SQPicture scr_U_G("Scr_U_G.bpx");
	RLCFont f24y("gf24y.rlc");
	RLCFont f24w("gf24w.rlc");
	int mmlx=PAD.GetLx();
	int mmly=PAD.GetLy();
	DialogsSystem GMM(smapx+(smaplx<<4)-(mmlx>>1),smapy+(mul3(smaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&PAD,&PAD,&PAD);
	int RT;
	if(!GPS.RLCImage[STONES.FileID]){
		GPS.LoadGP(STONES.FileID);
	};
	RT=STONES.FileID;
	RLCListBox* RB=GMM.addRLCListBox(PIC1,83,62,384,127,RT,0,254);
	RLCListBox* RB1=GMM.addRLCListBox(PIC1,83,62+128,384,127,RT,0,254);
	VScrollBar* SB=GMM.addHScrollBar(PIC1,65,328,RB->MaxXpos,0,&scr_L,&scr_L,&scr_L,&scr_R,&scr_R,&scr_R,&scr_Line,&scr_Line,&scr_U_G);
	TextButton* OkBtn=GMM.addTextButton(PIC1,181,379-3,"Äà",&f24w,&f24y,&f24y,1);
	TextButton* CancelBtn=GMM.addTextButton(PIC1,365-3,379-3,"Îòìåíà",&f24w,&f24y,&f24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	ItemChoose=-1;
	do{
		ProcessMessages();
		RB->XPos=SB->SPos;
		RB1->XPos=SB->SPos+322;
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		if(RB->Done){
			memset(RB1->Choosed,0,RB->NItems);
			RB->Done=false;
		};
		if(RB1->Done){
			memset(RB->Choosed,0,RB->NItems);
			RB1->Done=false;
		};
		for(int z=0;z<RB->NItems;z++){
			RB->Choosed[z]|=RB1->Choosed[z];
			RB1->Choosed[z]|=RB->Choosed[z];
		};
		GMM.RefreshView();
	}while(ItemChoose==-1);
	NTreeItems=0;
	if(ItemChoose==mcmOk){
		for(int z=0;z<RB->NItems;z++)if(RB->Choosed[z]&&NTreeItems<256){
			TreeItems[NTreeItems]=z;
			NTreeItems++;
		};
		if(NTreeItems){
			HeightEditMode=2;
			MEditMode=false;
			BlobMode=-1;
			InteriorType=1;
		};
	};
	UnPress();
};
void ChooseHole(){
	SQPicture PAD("stones.bpx");
	SQPicture scr_Line("Scr_10.bpx");
	SQPicture scr_L("Scr_L.bpx");
	SQPicture scr_R("Scr_R.bpx");
	SQPicture scr_U_G("Scr_U_G.bpx");
	RLCFont f24y("gf24y.rlc");
	RLCFont f24w("gf24w.rlc");
	int mmlx=PAD.GetLx();
	int mmly=PAD.GetLy();
	DialogsSystem GMM(smapx+(smaplx<<4)-(mmlx>>1),smapy+(mul3(smaply)<<2)-(mmly>>1));
	Picture* PIC1=GMM.addPicture(NULL,0,0,&PAD,&PAD,&PAD);
	int RT;
	if(!GPS.RLCImage[HOLES.FileID]){
		GPS.LoadGP(HOLES.FileID);
	};
	RT=HOLES.FileID;
	RLCListBox* RB=GMM.addRLCListBox(PIC1,83,62,384,127,RT,0,254);
	RLCListBox* RB1=GMM.addRLCListBox(PIC1,83,62+128,384,127,RT,0,254);
	VScrollBar* SB=GMM.addHScrollBar(PIC1,65,328,RB->MaxXpos,0,&scr_L,&scr_L,&scr_L,&scr_R,&scr_R,&scr_R,&scr_Line,&scr_Line,&scr_U_G);
	TextButton* OkBtn=GMM.addTextButton(PIC1,181,379-3,"Äà",&f24w,&f24y,&f24y,1);
	TextButton* CancelBtn=GMM.addTextButton(PIC1,365-3,379-3,"Îòìåíà",&f24w,&f24y,&f24y,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	ItemChoose=-1;
	do{
		ProcessMessages();
		RB->XPos=SB->SPos;
		RB1->XPos=SB->SPos+322;
		GMM.MarkToDraw();
		GMM.ProcessDialogs();
		if(RB->Done){
			memset(RB1->Choosed,0,RB->NItems);
			RB->Done=false;
		};
		if(RB1->Done){
			memset(RB->Choosed,0,RB->NItems);
			RB1->Done=false;
		};
		for(int z=0;z<RB->NItems;z++){
			RB->Choosed[z]|=RB1->Choosed[z];
			RB1->Choosed[z]|=RB->Choosed[z];
		};
		GMM.RefreshView();
	}while(ItemChoose==-1);
	NTreeItems=0;
	if(ItemChoose==mcmOk){
		for(int z=0;z<RB->NItems;z++)if(RB->Choosed[z]&&NTreeItems<256){
			TreeItems[NTreeItems]=z;
			NTreeItems++;
		};
		if(NTreeItems){
			HeightEditMode=2;
			MEditMode=false;
			BlobMode=-1;
			InteriorType=2;
		};
	};
	UnPress();
};
void ChooseInterior(int Type){
	switch(Type){
	case 0:
		ChooseTree();
		return;
	case 1:
		ChooseStone();
		return;
	case 2:
		ChooseHole();
		return;
	};
};

int GetTreeItem(){
	return TreeItems[(rando()*NTreeItems)>>15];
};
//Multiplayer Interface

//-------------Multiplayer settings--------------

bool WaitingGame(bool Host){
	char STRI[128];
	SQPicture   MPL    ("multi_m0.bpx");
	InputBox*   MNAME  [8];
	ComboBox*   MNATION[8];
	ColoredBar* MCOLOR [8];
	TextButton* MGRP   [8];
	RLCFont     FontA(GETS("@MNMENUACTF"));
	RLCFont     FontP(GETS("@MNMENUPASF"));
	DialogsSystem MPLAY(0,0);
	MPLAY.addPicture(NULL,0,0,&MPL,&MPL,&MPL);
	char NAMY[16];
	int NameX=GETV("MINAMEX");
	int NatX=GETV("MINATX");
	int ClrX=GETV("MICLRX");
	int CmdX=GETV("MIGRPX");
	int NameLx=GETV("MINAMELX");
	int StrLy=GETV("MINAMELY");
	int ClrLx=GETV("MICLRLX");
	int NatLx=GETV("MINATLX");
	InputBox* IBB1=MPLAY.addInputBox(NULL,0,0,STRI,64,300,32,&FontP,&FontP);
	LoadPalette("2w.pal");
	for(int i=0;i<8;i++){
		sprintf(NAMY,"MIY%d",i+1);
		int y1=GETV(NAMY);
		MNAME[i]=MPLAY.addInputBox(NULL,NameX,y1,PINFO[i].name,16,NameLx,StrLy,&FontP,&FontA);
		MNATION[i]=MPLAY.addComboBox(NULL,NatX+8,y1+3,NatLx-16,StrLy-3,20,0,3,&FontA,&FontP,NULL);
		for(int j=0;j<GlobalAI.NAi;j++){
			MNATION[i]->AddLine(GlobalAI.Ai[j].Message);
		};
		MNATION[i]->FontDx=4;
		MNATION[i]->FontDy=2;
		MCOLOR[i]=MPLAY.addColoredBar(ClrX,y1,ClrLx,StrLy,0x80);
		MCOLOR[i]->OnMouseOver=&ColorMouseOver;
		sprintf(NAMY,"%d",i);
		MGRP[i]=MPLAY.addTextButton(NULL,CmdX,y1,NAMY,&FontA,&FontP,&FontP,0);
		

	};
	TextButton* OkBtn;
	if(Host)OkBtn=MPLAY.addTextButton(NULL,GETV("MIOKX"),GETV("MIOKY"),GETS("@MIHOSTOK"),&FontA,&FontP,&FontP,1);
	else OkBtn=MPLAY.addTextButton(NULL,GETV("MIOKX"),GETV("MIOKY"),GETS("@MIJOINOK"),&FontA,&FontP,&FontP,1);
	TextButton* CancelBtn=MPLAY.addTextButton(NULL,GETV("MICANCELX"),GETV("MICANCELY"),GETS("@MICANCEL"),&FontA,&FontP,&FontP,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	ItemChoose=-1;
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	PIEnumeratePlayers(PINFO,0);
	byte CUSED=0;
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID!=MyDPID){
			CUSED|=(1<<PINFO[i].ColorID);
		};
	};
	int cc1=0;
	byte mss1=1;
	while(CUSED&mss1){
		cc1++;
		mss1<<=1;
	};
	for(i=0;i<NPlayers;i++){
		if(PINFO[i].PlayerID==MyDPID){
			PINFO[i].ColorID=cc1;
			MCOLOR[i]->color=cc1+0x80;
			if(Host)PINFO[i].Ready=1;
			else PINFO[i].Ready=0;
		}else{
			PINFO[i].Ready=0;
		};
	};
	do{
		tmm1=GetRealTime();
		ProcessMessages();
		tmm1=GetRealTime()-tmm1;
		tmm2=GetRealTime();
		AnalyseMessages();
		tmm2=GetRealTime()-tmm2;
		MPLAY.MarkToDraw();
		MPLAY.ProcessDialogs();
		tmm3=GetRealTime();
		MPLAY.RefreshView();
		tmm3=GetRealTime()-tmm3;
		sprintf(STRI,"%d %d %d %d",COUN,tmm1,tmm2,tmm3);
		for(int i=0;i<8;i++){
			if(i<NPlayers){
				if(PINFO[i].PlayerID==MyDPID){
					PINFO[i].NationID=MNATION[i]->CurLine;
					PINFO[i].ColorID=MCOLOR[i]->color-0x80;
					lpDirectPlay3A->SetPlayerData(MyDPID,(void*)&PINFO[i].NationID,4,DPSET_REMOTE);
					DPNAME dpName;
					ZeroMemory(&dpName, sizeof(DPNAME));
					dpName.dwSize = sizeof(DPNAME);
					dpName.lpszShortNameA = MNAME[i]->Str;
					dpName.lpszLongNameA = NULL;
					lpDirectPlay3A->SetPlayerName(MyDPID,&dpName,DPSET_REMOTE);
					MNATION[i]->Enabled=true;
					MCOLOR[i]->Enabled=true;
					MGRP[i]->Enabled=true;
				}else{
					MNATION[i]->Enabled=false;
					MCOLOR[i]->Enabled=false;
					MGRP[i]->Enabled=false;
				};
				MNATION[i]->Visible=true;
				MCOLOR[i]->Visible=true;
				MGRP[i]->Visible=true;
			}else{
				MNATION[i]->Enabled=false;
				MCOLOR[i]->Enabled=false;
				MGRP[i]->Enabled=false;
				MNATION[i]->Visible=false;
				MCOLOR[i]->Visible=false;
				MGRP[i]->Visible=false;
			};
		};
		PIEnumeratePlayers(PINFO,0);
		for(i=0;i<8;i++){
			if(i<NPlayers){
				MNATION[i]->CurLine=PINFO[i].NationID;
				MCOLOR[i]->color=PINFO[i].ColorID+0x80;
			};
		};
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID==MyDPID&&ItemChoose==mcmOk&&!Host){
				PINFO[i].Ready=1;
			};
		};
		bool GMREADY=true;
		for(i=0;i<NPlayers;i++){
			if(PINFO[i].PlayerID!=MyDPID&&!PINFO[i].Ready)GMREADY=false;
		};
		int MSS1=0;
		for(i=0;i<NPlayers;i++){
			byte MSS2=1<<PINFO[i].ColorID;
			if(MSS1&MSS2)GMREADY=false;
			MSS1|=MSS2;
			if(!PINFO[i].Ready)GMREADY=false;
		};
		if(Host){
			OkBtn->Enabled=GMREADY;
		};
		//checking readyness
		if(ItemChoose==mcmOk&&!Host)ItemChoose=-1;
	}while(ItemChoose==-1&&PlayerMenuMode==1);
	return true;
};
bool WaitingHostGame(int ID){
	if(ID)MPL_WaitingBattleGame(true,ID-1);
	else MPL_WaitingGame(true,0);
	
	if(ItemChoose==mcmCancel){
		CloseMPL();
		ItemChoose=-1;
	}else{
		if(ItemChoose==mcmOk){
			//ShowLoading();
			StopConnectionToSession(lpDirectPlay3A);
			StartIGame(0);
			return true;
		};
	};
	return false;
};
bool WaitingJoinGame(int ID){
	PlayerMenuMode=1;
	if(ID)MPL_WaitingBattleGame(false,ID-1);
	else MPL_WaitingGame(false,0);
	if(ItemChoose==mcmCancel){
		CloseMPL();
		ItemChoose=-1;
	}else{
		//ShowLoading();
		if(!PlayerMenuMode)return true;
	};
	return false;
};
extern bool NotInGame;
void CenterScreen();
extern bool NoWinner;
void CreateInfoMap();
extern word COMPSTART[8];
DLLEXPORT
void StartAI(byte Nat,char* Name,int Land,int Money,int ResOnMap,int Difficulty);
extern int RM_LandType;
extern int RM_Resstart;
extern int RM_Restot;
void FreeArrays();
void SetupArrays();
extern byte* RivDir;
extern char** NatsIDS;
extern byte XVIIIState;
void PerformNewUpgrade(Nation* NT,int UIndex,OneObject* OB);
extern int RunDataSize;
extern byte RunData[2048];
void StartAIEx(byte Nat,char* Name,int Land,int Money,int ResOnMap,int Difficulty);
void CleanRec();
void LoadMessagesFromFile(char* Name);
extern byte BaloonState;
extern byte CannonState;
extern byte XVIIIState;
extern byte CaptState;
extern byte SaveState;
void GetOptionsFromMap(char* Name){
	if(Name[0]=='R'&&Name[1]=='N'&&Name[3]==' '){
		int v1,v2,v3,ADD_PARAM;
		char ccc[32];
		int z=sscanf(Name,"%s%x%x%x%d",ccc,&v1,&v2,&v3,&ADD_PARAM);
		if(z==5){
			BaloonState=(ADD_PARAM/10)%10;
			CannonState=(ADD_PARAM/100)%10;
			XVIIIState=(ADD_PARAM/10000)%10;
			CaptState=(ADD_PARAM/100000)%10;
			SaveState=(ADD_PARAM/1000000)%10;
		};
	};
};
void PrepareGameMedia(byte myid,bool SaveNR){
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
		rpos=0;
		setCoor();
		//FreeArrays();
		if(!(strstr(CurrentMap,".SAV")||strstr(CurrentMap,".sav"))){
			if(CurrentMap[0]=='R'&&CurrentMap[1]=='N'&&CurrentMap[3]==' '){
				ADDSH=CurrentMap[2]-'0'+1;
			}else{
			};
		}else{
			NoWinner=1;
		};
		SetupArrays();
		NewMap(240<<ADDSH,240<<ADDSH);
		byte NRTB[8];
		memcpy(NRTB,NatRefTBL,8);
		UnLoading();
		if(SaveNR)memcpy(NatRefTBL,NRTB,8);
		
		SetMyNation(0);
		SetMyNation(PINFO[myid].ColorID);
		for(int i=0;i<8;i++){
			//Loading nation
			LoadAllNations(1<<i/*PINFO[i].ColorID*/,i/*PINFO[i].ColorID*/);
		};
		PrepareToGame();
		int RD_VERSION=101;
		//RUN DATA
		RunMethod=0xFFFFFFFE;
		RunData[0]=101;//version of the run data
		RunData[1]=dwVersion;//version of the game
		RunData[2]=MyNation;
		RunDataSize=3;
		memcpy(RunData+RunDataSize,PINFO,sizeof PINFO);
		RunDataSize+=sizeof PINFO;
		memcpy(RunData+RunDataSize,COMPSTART,sizeof COMPSTART);
		RunDataSize+=sizeof COMPSTART;
		memcpy(RunData+RunDataSize,&RM_LandType,4);
		RunDataSize+=4;
		memcpy(RunData+RunDataSize,&RM_Resstart,4);
		RunDataSize+=4;
		memcpy(RunData+RunDataSize,&RM_Restot,4);
		RunDataSize+=4;
		memcpy(RunData+RunDataSize,NRTB,8);
		RunDataSize+=8;
		assert(RunDataSize<2048);
		//----------
		//Aliances
			for(i=NPlayers;i<7;i++){
				if(COMPSTART[i]){
					word W=COMPSTART[i];
					int Nat=W>>11;
					int Color=W&15;
					int Diff=(W>>8)&7;
					int Team=(W>>4)&15;
					PINFO[i].ColorID=Color;
					PINFO[i].NationID=Nat;
					PINFO[i].GroupID=Team;
					PINFO[i].MapStyle=Diff;
					switch(Diff){
					case 1:
						strcpy(PINFO[i].name,"Easy");
						break;
					case 2:
						strcpy(PINFO[i].name,"Normal");
						break;
					case 3:
						strcpy(PINFO[i].name,"Hard");
						break;
					case 4:
						strcpy(PINFO[i].name,"Very hard");
						break;
					};
				}else{
					PINFO[i].MapStyle=0;
				};
			};

			for(i=0;i<7;i++)if(PINFO[i].name[0]||i<NPlayers||PINFO[i].MapStyle){
				if(PINFO[i].GroupID==0)NATIONS[NatRefTBL[PINFO[i].ColorID]].NMask=1<<NatRefTBL[PINFO[i].ColorID];
				else{
					int gid=PINFO[i].GroupID;
					byte mas=0;
					for(int j=0;j<7;j++)if(PINFO[j].name[0]||j<NPlayers||PINFO[j].MapStyle){
						if(PINFO[j].GroupID==gid)mas|=1<<NatRefTBL[PINFO[j].ColorID];
					};
					NATIONS[NatRefTBL[PINFO[i].ColorID]].NMask=mas;
				};
			};
//#ifndef SINGLETESTNETWORK
		//};
//#endif
		CheapMode=false;
		ItemChoose=mcmSingle;
		MultiplayerStart=true;
		InitExplosions();
		InitGame();
		NotInGame=true;
		if(!(strstr(CurrentMap,".SAV")||strstr(CurrentMap,".sav"))){
			byte RRR[8];
			memcpy(RRR,NatRefTBL,8);
			byte NMASKS[8];
			for(int i=0;i<8;i++)NMASKS[i]=NATIONS[i].NMask;
			Load3DMap(CurrentMap);
			GetOptionsFromMap(CurrentMap);
			for(i=0;i<8;i++)NATIONS[i].NMask=NMASKS[i];
			if(MapScenaryDLL[0]){
				char ccc[128];
				char cc3[128];
				strcpy(ccc,MapScenaryDLL);
				char* cc1=strstr(ccc,".");
				if(cc1)strcpy(cc1,".txt");
				strcpy(cc3,MapScenaryDLL);
				cc1=strstr(cc3,".");
				if(cc1)strcpy(cc1,".str");
				FILE* F=fopen(cc1,"r");
				if(F){
					fclose(F);
					LoadMessagesFromFile(cc3);
				};
				SCENINF.Load(MapScenaryDLL,ccc);//"Battles\\Battles.txt");
			}else{
				for(i=NPlayers;i<7;i++){
					if(COMPSTART[i]){
						int Diff=PINFO[i].MapStyle;
						int c=PINFO[i].ColorID;
						int Nat=-1;
						for(int j=0;j<MAXOBJECT;j++){
							OneObject* OB=Group[j];
							if(OB&&OB->NNUM==c&&(!OB->Sdoxlo)&&OB->newMons->Peasant){
								Nat=OB->Ref.General->NatID;
								j=MAXOBJECT+1;
							};
						};
						if(Nat!=-1){
							char ccx[48];
							char* NtID=NatsIDS[Nat];
							sprintf(ccx,"%s.%d",NtID,0);
							StartAIEx(PINFO[i].ColorID,ccx,RMP.STY[RM_LandType].AI_Style,RM_Resstart,RM_Restot,Diff-1);
						};
					};
				};
			};
			memcpy(NatRefTBL,RRR,8);
		}else{
			NoWinner=1;
		};
		GNFO.Clear();
		GNFO.Setup();
//#ifdef SINGLETESTNETWORK
		//running AI
		
		/*
#else
		if(NPlayers>1){
			//running AI
			for(int i=NPlayers;i<7;i++){
				if(COMPSTART[i]){
					int Diff=PINFO[i].MapStyle;
					int Nat=PINFO[i].NationID;
					char ccx[48];
					char* NtID=GlobalAI.Ai[Nat].NationID;
					sprintf(ccx,"%s.%d",NtID,0);
					StartAI(PINFO[i].ColorID,ccx,RM_LandType,RM_Resstart,RM_Restot,Diff-1);
				};
			};
		};
#endif
		*/
		HideFlags();
		NotInGame=false;
		for(int q=0;q<8;q++){
			for(int p=0;p<8;p++){
				SetXRESRC(q,p,RES[q][p]);
			};
		};
		CenterScreen();
		CreateInfoMap();
		InitExplosions();
		for(i=0;i<8;i++){
			CITY[i].EnumUnits();
			CITY[i].RefreshAbility();
		};
		if(XVIIIState==2){
			int N=NATIONS[0].NUpgrades;
			for(int i=0;i<N;i++){
				for(int NI=0;NI<7;NI++){
					NewUpgrade* NU=NATIONS[NI].UPGRADE[i];
					if((!NU->Done)&&NU->Options&8){
						PerformNewUpgrade(NATIONS+NI,i,NULL);
						NU->Done=1;
						NU->PermanentEnabled=0;
					};
				};
			};
		};
		for(i=0;i<MAXOBJECT;i++){
			OneObject* OB=Group[i];
			if(OB){
				OB->NMask=NATIONS[OB->NNUM].NMask;
			};
		};
		CleanRec();
};
//----------------------RANDOM MAP GENERATING DIALOG------------------
void RandomMapDialog(char* Result){
	DialogsSystem DSY((RealLx-352)>>1,(RealLy-352)>>1);
	RLCFont FONT1("rf32y.rlc");
	RLCFont FONT2(GETS("@SMPASSIVE"));
	RLCFont FONT3(GETS("@SMACTIVE"));
	DSY.addTextButton(NULL,352>>1,20,GETS("@RMIHEADER"),&FONT1,&FONT1,&FONT1,1);
	int y=60;
	int x0=20;
	int x=195;
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
	DSY.addTextButton(NULL,x0,y,GETS("@RMISTYLE"),&FONT2,&FONT2,&FONT2,0);
	ComboBox* CBSTYLE=DSY.addComboBox(NULL,x,y,144,25,20,0,255,&FONT2,&FONT3,NULL);
	for(int p=0;p<RMP.NSTY;p++){
		CBSTYLE->AddLine(RMP.STY[p].Name);
	};
	y+=40;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIMOUNTAINS"),&FONT2,&FONT2,&FONT2,0);
	ComboBox* CBMOUNT=DSY.addComboBox(NULL,x,y,144,25,20,0,255,&FONT2,&FONT3,NULL);
	for(p=0;p<RMP.NRelief;p++){
		CBMOUNT->AddLine(RMP.Relief[p]);
	};
	y+=40;
	int CurSty=0;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIPLAYERS"),&FONT2,&FONT2,&FONT2,0);
	ComboBox* CBPLAY=DSY.addComboBox(NULL,x,y,144,25,20,0,255,&FONT2,&FONT3,NULL);
	for(p=0;p<RMP.STY[CurSty].NPl;p++){
		char ccc[16];
		sprintf(ccc," %d",RMP.STY[CurSty].Players[p].NPlayers);
		CBPLAY->AddLine(ccc);
	};
	y+=40;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIRESSTART"),&FONT2,&FONT2,&FONT2,0);
	ComboBox* CBRESST=DSY.addComboBox(NULL,x,y,144,25,20,0,255,&FONT2,&FONT3,NULL);
	for(p=0;p<RMP.NRES;p++){
		CBRESST->AddLine(RMP.RES[p].Name);
	};
	y+=40;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIRESTOT"),&FONT2,&FONT2,&FONT2,0);
	ComboBox* CBRESTOT=DSY.addComboBox(NULL,x,y,144,25,20,0,255,&FONT2,&FONT3,NULL);
	for(p=0;p<RMP.NMINES;p++){
		CBRESTOT->AddLine(RMP.MINES[p].Name);
	};
	y+=40;
	DSY.addTextButton(NULL,x0,y,"Code:",&FONT2,&FONT2,&FONT2,0);
	char ccc[128];
	sprintf(ccc,"%d",GetRealTime()&32767);
	InputBox* IB=DSY.addInputBox(NULL,x,y,ccc,20,144,28,&FONT2,&FONT2);
	y+=40;
	TextButton* OkBtn=DSY.addTextButton(NULL,10+164/2,315,"OK",&FONT2,&FONT3,&FONT3,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=DSY.addTextButton(NULL,180+164/2,315,"ÎÒÌÅÍÀ",&FONT2,&FONT3,&FONT3,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	ItemChoose=-1;
	do{
		ProcessMessages();
		if(KeyPressed&&(LastKey==13||LastKey==27)){
			KeyPressed=false;
			ItemChoose=mcmOk;
		};
		DrawStdBar(DSY.BaseX,DSY.BaseY,DSY.BaseX+351,DSY.BaseY+351);
		DSY.MarkToDraw();
		DSY.ProcessDialogs();
		DSY.RefreshView();
		if(CurSty!=CBSTYLE->CurLine){
			CurSty=CBSTYLE->CurLine;
			CBPLAY->Clear();
			for(p=0;p<RMP.STY[CurSty].NPl;p++){
				char ccc[16];	
				sprintf(ccc," %d",RMP.STY[CurSty].Players[p].NPlayers);
				CBPLAY->AddLine(ccc);
			};
		};
	}while(ItemChoose==-1);
	UnPress();
	if(ItemChoose==mcmOk){
		int r=GetRealTime()&65535;
		sscanf(ccc,"%d",&r);
		int q=CBSTYLE->CurLine+(CBPLAY->CurLine<<4)+(CBMOUNT->CurLine<<8)+(CBRESST->CurLine<<12)+
			(CBRESTOT->CurLine<<16);
		sprintf(Result,"RND %X %X 11111111.m3d",r,q);
	}else Result[0]=0;
};
int RM_LandType =0;
int RM_Resstart =0;
int RM_Restot   =0;
void EnterRandomParams(){
	DialogsSystem DSY((RealLx-64*6)>>1,(RealLy-64*5)>>1);
	LocalGP vinB("vinBig");
	LocalGP vin("vin");
	RLCFont fnti(vinB.GPID);
	RLCFont fntir(vinB.GPID);
	fntir.SetRedColor();
	RLCFont fntis(vin.GPID);
	RLCFont fntisr(vin.GPID);
	fntisr.SetRedColor();
	DSY.addTextButton(NULL,32*6,10,GetTextByID("AIPARM"),&BigYellowFont,&BigYellowFont,&BigYellowFont,1);
	int y=85;
	int x0=10;
	int x=200;
	RandomMapDesc RMP;
	RMP.Load("Terrain\\Res.dat");
	DSY.addTextButton(NULL,x0,y,GETS("@RMISTYLE"),&fntis,&fntis,&fntis,0);
	ComboBox* CBSTYLE=DSY.addComboBox(NULL,x,y,164,25,20,0x3B,255,&fntisr,&fntis,NULL);
	for(int p=0;p<RMP.NSTY;p++){
		CBSTYLE->AddLine(RMP.STY[p].Name);
	};
	CBSTYLE->CurLine=RM_LandType;
	y+=50;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIRESSTART"),&fntis,&fntis,&fntis,0);
	ComboBox* CBRESST=DSY.addComboBox(NULL,x,y,164,25,20,0x3B,255,&fntisr,&fntis,NULL);
	for(p=0;p<RMP.NRES;p++){
		CBRESST->AddLine(RMP.RES[p].Name);
	};
	CBRESST->CurLine=RM_Resstart;
	y+=45;
	DSY.addTextButton(NULL,x0,y,GETS("@RMIRESTOT"),&fntis,&fntis,&fntis,0);
	ComboBox* CBRESTOT=DSY.addComboBox(NULL,x,y,164,25,20,0x3B,255,&fntisr,&fntis,NULL);
	for(p=0;p<RMP.NMINES;p++){
		CBRESTOT->AddLine(RMP.MINES[p].Name);
	};
	CBRESTOT->CurLine=RM_Restot;
	y+=55;
	TextButton* OkBtn=DSY.addTextButton(NULL,92-5,y,"OK",&fntir,&fnti,&fnti,1);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	TextButton* CancelBtn=DSY.addTextButton(NULL,180+82,y,"Cancel",&fntir,&fnti,&fnti,1);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;

	ItemChoose=-1;
	do{
		int x0=(RealLx-64*6)>>1;
		int y0=(RealLy-64*4)>>1;
		DrawPaperPanel(x0,y0,x0+64*6,y0+64*4);
		ProcessMessages();
		DSY.MarkToDraw();
		DSY.ProcessDialogs();
		DSY.RefreshView();
		if(KeyPressed){
			if(LastKey==13)ItemChoose=mcmOk;
			if(LastKey==27)ItemChoose=mcmCancel;
			KeyPressed=false;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		RM_LandType=CBSTYLE->CurLine;
		RM_Resstart=CBRESST->CurLine;
		RM_Restot=CBRESTOT->CurLine;
	};
	UnPress();
};
void RandomMapDialog1(char* Result,int NPlayers,char* Nats){
	
};
int CurrentCampagin=-1;
int CurrentMission=-1;
bool ProcessSingleMission(int n,int Diff){
	MaxPingTime=0;
	SingleMission* SMS=MISSLIST.MISS+n;
	/*
	for(int i=0;i<SMS->NIntro;i++){
		if(!strstr(SMS->Intro[i],".txt")){
			SQPicture Pan1(SMS->Intro[i]);
			SlowUnLoadPalette("1\\agew_1.pal");
			Pan1.Draw(0,0);
			FlipPages();
			SlowLoadPalette("1\\agew_1.pal");
			int t0=GetRealTime();
			KeyPressed=0;
			LastKey=0;
			Lpressed=false;
			do{
				ProcessMessages();
			}while(!(GetRealTime()-t0>15000||Lpressed||KeyPressed));
			Lpressed=false;
			if(LastKey==27)return false;
		};
	};
	*/
	if(SMS->NIntro==4){
		ResFile f=RReset(SMS->Intro[2]);
		if(f!=INVALID_HANDLE_VALUE){
			byte crlf[6]={0x20,0x0D,0x0A,0x0D,0x0A};
			int sz=RFileSize(f);
			byte* buf=new byte[sz];
			RBlockRead(f,buf,sz);
			RClose(f);
			f=RRewrite("tmp.txt");
			RBlockWrite(f,crlf,sizeof crlf);
			RBlockWrite(f,buf,sz);
			RBlockWrite(f,crlf,sizeof crlf);
			RClose(f);
			free(buf);
		};
		LoadOptionalTable(5,"2\\dark.grd");
		LocalGP BTNS("Interface\\Mission_text");
		LocalGP PIC(SMS->Intro[1]);
		LocalGP ITL("it_Small");
		RLCFont itsm(ITL.GPID);
		//itsm.SetColorTable(5);
		LocalGP HDR("vinBig");
		RLCFont hdrf(HDR.GPID);
		//hdrf.SetColorTable(5);
		SQPicture Back("Interface\\Background_Mission_Text.bmp");
		DialogsSystem MISS(0,0);
		MISS.addPicture(NULL,0,0,&Back,&Back,&Back);
		MISS.addGPPicture(NULL,48,119,PIC.GPID,0);
		//GPS.SetOptionalColor(PIC.GPID,5);
		//GPS.SetOptionalColor(PIC.GPID,2);
		//Back.Draw(0,0);
		//GPS.ShowGP(48,119,
		TextViewer* TV=MISS.addTextViewer(NULL,532,258,445,424,"tmp.txt",&itsm);
		TV->SymSize=25;
		TV->PageSize=18;
		TV->Active=0;
		TV->Enabled=0;

		MISS.addGPPicture(NULL,522,258-25,BTNS.GPID,2);
		MISS.addGPPicture(NULL,522+233,258-25,BTNS.GPID,3);
		MISS.addGPPicture(NULL,522,656,BTNS.GPID,0);
		MISS.addGPPicture(NULL,522+233,656,BTNS.GPID,1);
		MISS.addTextButton(NULL,522,204,SMS->Name,&hdrf,&hdrf,&hdrf,0);
		int z=0;
		sscanf(SMS->Intro[0],"%d",&z);
		int LX=GPS.GetGPWidth(BTNS.GPID,8+z);
		MISS.addGPPicture(NULL,512-LX/2,7,BTNS.GPID,8+z);
		MISS.addGPPicture(NULL,512-LX/2-425,7,BTNS.GPID,6);
		MISS.addGPPicture(NULL,512+LX/2,7,BTNS.GPID,7);
		char* tex=GetTextByID(SMS->Intro[3]);
		LX=GetRLCStrWidth(tex,&YellowFont);
		MISS.addGPPicture(NULL,512-LX/2-502,736,BTNS.GPID,4);
		MISS.addGPPicture(NULL,512+LX/2,736,BTNS.GPID,5);
		MISS.addTextButton(NULL,512,736+3,tex,&YellowFont,&YellowFont,&YellowFont,1);

		int LinesUp=0;
		int LinesDn=0;
		int ShiftY=0;
		bool exit=false;
		do{
			if(KeyPressed&&LastKey==27)exit=true;
			if(Lpressed||(KeyPressed&&(LastKey==34||LastKey==13||LastKey==' '))){
				LinesUp=8;
				LinesDn=0;
				KeyPressed=0;
				if(TV->NLines-TV->Line<16){
					if(!ShiftY)LinesUp=0;
					else LinesUp=1;
					if(Lpressed)exit=true;
				};
			};
			if(KeyPressed&&LastKey==33){
				LinesUp=0;
				LinesDn=9;
				KeyPressed=0;
			};
			if(LinesUp){
				if(ShiftY<25){
					switch(ShiftY){
					case 0:
						ShiftY=9;
						break;
					case 9:
						ShiftY=9+8;
						break;
					case 9+8:
						ShiftY=25;
						break;
					};
				}else{
					TV->Line++;
					LinesUp--;
					if(!TV->Line)LinesUp=0;
					ShiftY=0;
				};
			};
			if(LinesDn){
				if(!ShiftY){
					if(TV->Line){
						TV->Line--;
						ShiftY=9+8;
						LinesDn--;
					}else LinesDn=0;
				}else{
					switch(ShiftY){
					case 9+8:
						ShiftY=9;
						break;
					case 9:
						ShiftY=0;
						break;
					};
				};
			};
			TV->y=258-ShiftY;
			ProcessMessages();
			MISS.MarkToDraw();
			MISS.ProcessDialogs();
			MISS.RefreshView();
		}while(!exit);
	};
	//ShowTable(GetTextByID("LOADING"),GetTextByID("WAITPL"));
	SetMyNation(0);
	ShowLoading();
	//FlipPages();
	strcpy(CurrentMap,MISSLIST.MISS[n].MapName);
	CreateNationalMaskForMap(CurrentMap);
	PrepareGameMedia(0,0);
	InitGame();
	ItemChoose=mcmSingle;
	//InitExplosions();
	for(int i=0;i<7;i++){
		CITY[i].Difficulty=Diff;
		PINFO[i].ColorID=i;
		if(i)strcpy(PINFO[i].name,"???");
	};
	SetMyNation(0);
	strcpy(PINFO[0].name,PlName);
	PINFO[0].GameTime=0;
	PINFO[0].VictCond=0;
	MISSLIST.CurrentMission=n;
	SCENINF.Load(MISSLIST.MISS[n].DLLPath,MISSLIST.MISS[n].Description);
	UnPress();
	RunMethod=0x12340000+n+(Diff<<8);
	return true;
};
bool ProcessSingleCampagin(int n){
	KeyPressed=0;
	LastKey=0;
	//SlowUnLoadPalette("1\\agew_1.pal");
	SQPicture Back(CAMPAGINS.SCamp[n].CampBmp);

	LocalGP BTNS("Interface\\One_Campaign");
	LocalGP BTN1("Interface\\Single_mission");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP SCROL("Interface\\_Slider");
	LoadFog(2);
	_strupr(CAMPAGINS.SCamp[n].CampBmp);
	bool Style=strstr(CAMPAGINS.SCamp[n].CampBmp,".NEW.")!=NULL;
/*
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"1\\orange.grd");
	RLCFont FontW(FONT.GPID);
	FontW.SetColorTable(4);
	LoadOptionalTable(4,"1\\white.grd");
*/
	DialogsSystem MMenu(0,0);
	MMenu.OkSound=GetSound("START");
	MMenu.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MMenu.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");
	
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=731;
	MMenu.HintX=18;

	SingleCampagin* SCM=CAMPAGINS.SCamp+n;
	TextViewer* TV[32];
	VScrollBar* TSB[32];

	VScrollBar* SB;
	if(Style)SB=MMenu.addNewGP_VScrollBar(NULL,450,157,221-52,1,0,SCROL.GPID,0);
	else SB=MMenu.addNewGP_VScrollBar(NULL,450,157,221,1,0,SCROL.GPID,0);
	for(int i=0;i<SCM->NMiss&&i<8;i++){
		if((SCM->OpenIndex[i]&255)&&i<8-Style-Style)MMenu.addGPPicture(NULL,46,166+26*i,BTNS.GPID,6);
	};
	ListBox* LB;
	if(Style)LB=MMenu.addGP_ListBox(NULL,46,166,6,BTNS.GPID,3,26,&WhiteFont,&YellowFont,SB);
	else LB=MMenu.addGP_ListBox(NULL,46,166,8,BTNS.GPID,3,26,&WhiteFont,&YellowFont,SB);
	LB->M_Over=0;
	LB->Active=1;
	LB->FontDy=-2;
	int MaxMiss=0;
	for(i=0;i<SCM->NMiss;i++){
		if(SCM->OpenIndex[i]&255)MaxMiss=i+1;
	};
	bool VISMASK[64];
	memset(VISMASK,0,sizeof VISMASK);
	for(i=0;i<MaxMiss;i++){
		//if(SCM->OpenIndex[i]&255){
		LB->AddItem(MISSLIST.MISS[SCM->Miss[i]].Name,0);
		LB->CurItem=LB->NItems-1;
		if(LB->CurItem-LB->FLItem>LB->ny){
			LB->FLItem=LB->CurItem-LB->ny+1;
			SB->SPos=LB->FLItem*32;
		};
		//};
		if(MISSLIST.MISS[SCM->Miss[i]].NIntro&&strstr(MISSLIST.MISS[SCM->Miss[i]].Intro[0],".txt")){
			if(Style)TV[i]=MMenu.addTextViewer(NULL,54,431-52,386,196-12,MISSLIST.MISS[SCM->Miss[i]].Intro[0],&YellowFont);
			else TV[i]=MMenu.addTextViewer(NULL,54,431,386,196,MISSLIST.MISS[SCM->Miss[i]].Intro[0],&YellowFont);
			TV[i]->SymSize=21;
			TV[i]->PageSize=(TV[i]->y1-TV[i]->y)/TV[i]->SymSize;
			TV[i]->Visible=0;
			if(Style)TSB[i]=MMenu.addNewGP_VScrollBar(NULL,450,416-52,213-18,1,0,SCROL.GPID,0);
			else TSB[i]=MMenu.addNewGP_VScrollBar(NULL,450,416,213,1,0,SCROL.GPID,0);
			TSB[i]->Visible=0;
			TSB[i]->ScrDy=7;
			TV[i]->AssignScroll(TSB[i]);
		}else{
			TV[i]=NULL;
			TSB[i]=NULL;
		};
		VISMASK[i]=strstr(MISSLIST.MISS[SCM->Miss[i]].ID,"@")!=NULL;
	};
	ComboBox* DIFF;
	if(Style)DIFF=MMenu.addGP_ComboBoxDLX(NULL,143,601,314,BTN1.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	else DIFF=MMenu.addGP_ComboBox(NULL,584,422,BTN1.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	DIFF->CurLine=0;
	FILE* f=fopen("smiss.opt","r");
	if(f){
		int v=0;
		fscanf(f,"%d",&v);
		fclose(f);
		DIFF->CurLine=v;
	};
	DIFF->AddLine(GetTextByID("@RMID_EASY"));
	DIFF->AddLine(GetTextByID("@RMID_NORMAL"));
	DIFF->AddLine(GetTextByID("@RMID_HARD"));
	DIFF->AddLine(GetTextByID("@RMID_VERYHARD"));
	DIFF->Hint=GetTextByID("DIFFICULTY");
	VideoButton* OkBtn=MMenu.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	OkBtn->Hint=GetTextByID("MISS_RUN");
	VideoButton* CancelBtn=MMenu.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->Hint=GetTextByID("MISS_CANCEL");
HHH1:
	ItemChoose=-1;
	int mm=1;
	KeyPressed=0;
	do{
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		for(int j=0;j<MaxMiss;j++){
			if(TV[j]){
				if(j==LB->CurItem){
					TV[j]->Visible=1;
					TSB[j]->Visible=1;
					TV[j]->Active=0;
				}else{
					TV[j]->Visible=0;
					TSB[j]->Visible=0;
					TV[j]->Active=0;
				};
			};
			if(j==LB->CurItem){
				DIFF->Visible=VISMASK[j];
				DIFF->Enabled=DIFF->Visible;
			};
		};
		LB->Active=1;
		if(mm){
			SlowLoadPalette("2\\agew_1.pal");
			mm=0;
		};
		StdKeys();
	}while(ItemChoose==-1);
	f=fopen("smiss.opt","w");
	if(f){
		int v=0;
		fprintf(f,"%d",DIFF->CurLine);
		fclose(f);
	};
	if(ItemChoose==mcmOk){
		CurrentCampagin=n;
		CurrentMission=LB->CurItem;
		if(!ProcessSingleMission(SCM->Miss[LB->CurItem],DIFF->CurLine)){
			SlowUnLoadPalette("2\\agew_1.pal");
			CurrentCampagin=-1;
			CurrentMission=-1;
			goto HHH1;
		}else return true;
	}else{
		CurrentCampagin=-1;
		CurrentMission=-1;
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	return false;
};
struct OneAddMission{
	char Title[128];
	char Map[128];
	char Preview[128];
	char Bitmap[128];
};
class AddMissionsPack{
public:
	OneAddMission* Pack;
	int NMiss;
	AddMissionsPack();
	~AddMissionsPack();
};

AddMissionsPack::AddMissionsPack(){
	Pack=NULL;
	NMiss=0;
	WIN32_FIND_DATA SR;
	HANDLE H=FindFirstFile("UserMissions\\*.add",&SR);
	if(H!=INVALID_HANDLE_VALUE){
		do{
			char ccc[128];
			sprintf(ccc,"UserMissions\\%s",SR.cFileName);
			GFILE* F=Gopen(ccc,"r");
			if(F){
				Pack=(OneAddMission*)realloc(Pack,sizeof(OneAddMission)*(NMiss+1));
				memset(Pack+NMiss,0,sizeof OneAddMission);
				ReadWinString(F,Pack[NMiss].Title,127);
				ReadWinString(F,Pack[NMiss].Map,127);
				ReadWinString(F,ccc,127);
				_strupr(ccc);
				char* c1=strstr(ccc,".DLL");
				if(!c1)c1=strstr(ccc,".CMS");
				if(c1){
					strcpy(c1,".dsc");
					strcpy(Pack[NMiss].Preview,ccc);
					strcpy(c1,".bmp");
					FILE* F1=fopen(ccc,"r ");
					if(F1){
						strcpy(Pack[NMiss].Bitmap,ccc);
						fclose(F1);
					};
				};
				Gclose(F);
				NMiss++;
			};
		}while(FindNextFile(H,&SR));
		FindClose(H);
	};
};
AddMissionsPack::~AddMissionsPack(){
	if(Pack)free(Pack);
	memset(this,0,sizeof AddMissionsPack);
};
bool SelectSingleMission(){
	if(!MISSLIST.MSMiss)return false;
	KeyPressed=0;
	LastKey=0;
	/*
	byte* Preview=new byte[(292*190)+4];
	((word*)Preview)[0]=292;
	((word*)Preview)[1]=190;
	bool PrPresent=false;
	char LastPrName[200]="";
	byte XLAT[256];
	ResFile fx=RReset("2\\0to1.xlt");
	RBlockRead(fx,XLAT,256);
	RClose(fx);
	*/

	//SlowUnLoadPalette("1\\agew_1.pal");
	AddMissionsPack AMSP;
	SQPicture Back("Interface\\Single_Mission_Background.bmp");

	LocalGP BTNS("Interface\\Single_mission");
	LocalGP OK1("Interface\\anm_start_1_on");
	LocalGP OK2("Interface\\anm_start_1_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP SCROL("Interface\\_Slider");
	LocalGP MASKA("Interface\\preview_mask");
	LoadFog(2);

/*
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"1\\orange.grd");
	RLCFont FontW(FONT.GPID);
	FontW.SetColorTable(4);
	LoadOptionalTable(4,"1\\white.grd");
*/
	DialogsSystem MMenu(0,0);
	MMenu.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MMenu.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");
	SQPicture PRV("Maps2\\Single1.bmp");
	BPXView* PREV=MMenu.addBPXView(NULL,495,162,292,190,1,1,1,(byte*)(PRV.PicPtr+2)/*Preview+4*/,NULL);
	//PREV->Visible=false;
	GPPicture* PMASK=MMenu.addGPPicture(NULL,495,162,MASKA.GPID,0);
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;

	VScrollBar* SB=MMenu.addNewGP_VScrollBar(NULL,445,157,274,1,0,SCROL.GPID,0);
	ListBox* LB=MMenu.addGP_ListBox(NULL,41,166,10,BTNS.GPID,8,26,&WhiteFont,&YellowFont,SB);
	LB->M_Over=11;
	LB->Active=1;
	LB->FontDy=-2;
	LB->FontDx-=1;
	ComboBox* DIFF=MMenu.addGP_ComboBox(NULL,584,402,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	DIFF->CurLine=0;
	FILE* f=fopen("smiss.opt","r");
	if(f){
		int v=0;
		fscanf(f,"%d",&v);
		fclose(f);
		DIFF->CurLine=v;
	};
	DIFF->AddLine(GetTextByID("@RMID_EASY"));
	DIFF->AddLine(GetTextByID("@RMID_NORMAL"));
	DIFF->AddLine(GetTextByID("@RMID_HARD"));
	DIFF->AddLine(GetTextByID("@RMID_VERYHARD"));
	DIFF->Hint=GetTextByID("DIFFICULTY");
	TextViewer* TV[128];
	VScrollBar* TSB[128];
	for(int i=0;i<MISSLIST.MSMiss;i++){
		LB->AddItem(MISSLIST.MISS[MISSLIST.SingleMS[i]].Name,0);
		if(MISSLIST.MISS[MISSLIST.SingleMS[i]].NIntro&&strstr(MISSLIST.MISS[MISSLIST.SingleMS[i]].Intro[0],".txt")){
			TV[i]=MMenu.addTextViewer(NULL,49,478,716,160,MISSLIST.MISS[MISSLIST.SingleMS[i]].Intro[0],&YellowFont);
			TV[i]->SymSize=21;
			TV[i]->PageSize=(TV[i]->y1-TV[i]->y)/TV[i]->SymSize;
			TV[i]->Visible=0;
			TSB[i]=MMenu.addNewGP_VScrollBar(NULL,777,468,161,1,0,SCROL.GPID,0);
			TSB[i]->Visible=0;
			TSB[i]->ScrDy=7;
			TV[i]->AssignScroll(TSB[i]);
		}else{
			TV[i]=NULL;
			TSB[i]=NULL;
		};
	};
	int N0=MISSLIST.MSMiss;
	for(i=0;i<AMSP.NMiss;i++){
		LB->AddItem(AMSP.Pack[i].Title,0);
		TV[N0+i]=MMenu.addTextViewer(NULL,49,478,716,160,AMSP.Pack[i].Preview,&YellowFont);
		TV[N0+i]->SymSize=21;
		TV[N0+i]->PageSize=(TV[i]->y1-TV[i]->y)/TV[i]->SymSize;
		TV[N0+i]->Visible=0;
		TSB[N0+i]=MMenu.addNewGP_VScrollBar(NULL,777,468,161,1,0,SCROL.GPID,0);
		TSB[N0+i]->Visible=0;
		TSB[N0+i]->ScrDy=7;
		TV[N0+i]->AssignScroll(TSB[i]);
	};
	VideoButton* OkBtn=MMenu.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	OkBtn->Hint=GetTextByID("MISS_RUN");
	VideoButton* CancelBtn=MMenu.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->Hint=GetTextByID("MISS_CANCEL");
	int prmiss=-1;
HHH1:
	ItemChoose=-1;
	int mm=1;
	KeyPressed=0;
	do{
		if(prmiss!=LB->CurItem){
			//if(GetPreview(MISSLIST.MISS[MISSLIST.SingleMS[LB->CurItem]].MapName,Preview+4)){
			//	PREV->Visible=1;
			//	Decode(Preview+4,XLAT,292*190);
			//}else{
			//	PREV->Visible=false;
			//};
			if(LB->CurItem>=N0){
				PRV.LoadPicture(AMSP.Pack[LB->CurItem-N0].Bitmap);
				PREV->Ptr=(byte*)(PRV.PicPtr+2);
				prmiss=LB->CurItem;
			}else{
				char ccc[200];
				sprintf(ccc,"Maps2\\single%d.bmp",LB->CurItem+1);
				PRV.LoadPicture(ccc);
				PREV->Ptr=(byte*)(PRV.PicPtr+2);
				prmiss=LB->CurItem;
			};
		};
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		for(int j=0;j<MISSLIST.MSMiss+AMSP.NMiss;j++){
			if(TV[j]){
				if(j==LB->CurItem){
					TV[j]->Visible=1;
					TSB[j]->Visible=1;
					TV[j]->Active=0;
				}else{
					TV[j]->Visible=0;
					TSB[j]->Visible=0;
					TV[j]->Active=0;
				};
			};
		};
		LB->Active=1;
		if(mm){
			SlowLoadPalette("2\\agew_1.pal");
			mm=0;
		};
		StdKeys();
	}while(ItemChoose==-1);
	f=fopen("smiss.opt","w");
	if(f){
		fprintf(f,"%d",DIFF->CurLine);
		fclose(f);
	};
	if(ItemChoose==mcmOk){
		CurrentCampagin=-1;
		CurrentMission=-1;
		if(LB->CurItem<N0){
			if(!ProcessSingleMission(MISSLIST.SingleMS[LB->CurItem],DIFF->CurLine)){
				SlowUnLoadPalette("2\\agew_1.pal");
				CurrentCampagin=-1;
				CurrentMission=-1;
				goto HHH1;
			}else return true;
		}else{
			ShowLoading();
			ItemChoose=mcmSingle;
			strcpy(CurrentMap,AMSP.Pack[LB->CurItem-N0].Map);
			CreateNationalMaskForMap(CurrentMap);
			PrepareGameMedia(0,0);
			InitGame();
			for(int i=0;i<7;i++){
				CITY[i].Difficulty=DIFF->CurLine;
				PINFO[i].ColorID=i;
				if(i)strcpy(PINFO[i].name,"???");
			};
			SetMyNation(0);
			strcpy(PINFO[0].name,PlName);
			PINFO[0].GameTime=0;
			PINFO[0].VictCond=0;
		};
	}else{
		CurrentCampagin=-1;
		CurrentMission=-1;
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	return false;
};
void ProcessCampagins(int Options){
	if(!CAMPAGINS.NCamp)return;
	KeyPressed=0;
	LastKey=0;
	LoadFog(2);
	//if(Options==-1)SlowUnLoadPalette("1\\agew_1.pal");
	SQPicture Back("Interface\\Background_Campaign_Menu.bmp");
	LocalGP BTNS("Interface\\Campaigns");
	LocalGP SCROL("Interface\\_Slider");
	LocalGP OK1("Interface\\anm_start_on");
	LocalGP OK2("Interface\\anm_start_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"2\\orange.grd");

	//LocalGP FONT6("vin");
	//RLCFont FontI(FONT6.GPID);
	//FontI.SetColorTable(3);

	RLCFont FontW(FONT.GPID);
	FontW.SetWhiteColor();
	//LoadOptionalTable(4,"2\\white.grd");
	DialogsSystem MMenu(0,0);
	MMenu.OkSound=GetSound("START");
	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;

	MMenu.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MMenu.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");

	VScrollBar* SB=MMenu.addNewGP_VScrollBar(NULL,755,156,119+26,100,0,SCROL.GPID,0);
	SB->ScrDy=3;
	ListBox* LB=MMenu.addGP_ListBox(NULL,68,166,5,BTNS.GPID,3,26,&FontW,&FontY,SB);
	LB->FontDx--;
	LB->M_Over=0;
	LB->Active=true;
	LB->FontDy-=2;
	TextViewer* TV[32];
	VScrollBar* VS[32];
	for(int i=0;i<CAMPAGINS.NCamp;i++){
		LB->AddItem(CAMPAGINS.SCamp[i].CampMessage,0);
		VS[i]=MMenu.addNewGP_VScrollBar(NULL,755,312+26,316-26,1,0,SCROL.GPID,0);
		VS[i]->ScrDy=13;
		TV[i]=MMenu.addTextViewer(NULL,77,327+26-2,665,310-26,CAMPAGINS.SCamp[i].CampText,&FontY);
		TV[i]->AssignScroll(VS[i]);
		TV[i]->SymSize=21;
		TV[i]->PageSize=(TV[i]->y1-TV[i]->y)/TV[i]->SymSize;
		TV[i]->Enabled=false;
		TV[i]->Visible=false;
	};
	VideoButton* OkBtn=MMenu.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	OkBtn->Hint=GetTextByID("WAR_RUN");
	VideoButton* CancelBtn=MMenu.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->Hint=GetTextByID("WAR_CANCEL");
HHH1:
	ItemChoose=-1;
	KeyPressed=0;
	if(Options==-1){
		int mm=1;
		do{
			ProcessMessages();
			StdKeys();
			MMenu.MarkToDraw();
			MMenu.ProcessDialogs();
			MMenu.RefreshView();
			for(i=0;i<CAMPAGINS.NCamp;i++){
				TV[i]->Enabled=false;
				TV[i]->Visible=false;
				TV[i]->Active=false;
				VS[i]->Visible=false;
			};
			TV[LB->CurItem]->Enabled=1;
			TV[LB->CurItem]->Visible=1;
			if(VS[LB->CurItem]->SMaxPos>0)VS[LB->CurItem]->Visible=1;
			else VS[LB->CurItem]->Visible=0;
			if(mm){
				SlowLoadPalette("2\\agew_1.pal");
				mm=0;
			};
			StdKeys();
		}while(ItemChoose==-1);
		if(ItemChoose==mcmOk)Options=LB->CurItem;
	};
	if(Options!=-1){
		SlowUnLoadPalette("2\\agew_1.pal");
		if(!ProcessSingleCampagin(Options)){
			//SlowLoadPalette("2\\agew_1.pal");
			//LoadFog(2);
			Options=-1;
			goto HHH1;
		};
	}else{
		SlowUnLoadPalette("2\\agew_1.pal");
	};
};
bool ProcessOneBattle(int BtlID){
	KeyPressed=0;
	LastKey=0;
	SQPicture Back("Interface\\Background_Historical_Battle_01.bmp");
	LocalGP BTNS("Interface\\Wars");
	LocalGP Mask("Interface\\Historical_mask");
	LocalGP SCROL("Interface\\_Slider");
	LocalGP OK1("Interface\\anm_start_on");
	LocalGP OK2("Interface\\anm_start_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"2\\orange.grd");
	SQPicture Preview(WARS.Battles[BtlID].BigMap);

	RLCFont FontW(FONT.GPID);
	FontW.SetWhiteColor();
	DialogsSystem MMenu(0,0);

	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;

	MMenu.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MMenu.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");
	OneBattle* OB=WARS.Battles+BtlID;
	MMenu.addTextButton(NULL,48,147-11,OB->BigHeader,&WhiteFont,&WhiteFont,&WhiteFont,0);
	if(Preview.PicPtr){
		MMenu.addPicture(NULL,39,134+26,&Preview,&Preview,&Preview);
		MMenu.addGPPicture(NULL,39,134+26,Mask.GPID,0);
		for(int i=0;i<OB->NHints;i++){
			MMenu.addTextButton(NULL,40+OB->Coor[i+i],133+26+OB->Coor[i+i+1],OB->Hints[i],&SmallBlackFont1,&SmallBlackFont1,&SmallBlackFont1,0);
			MMenu.addTextButton(NULL,38+OB->Coor[i+i],133+26+OB->Coor[i+i+1],OB->Hints[i],&SmallBlackFont1,&SmallBlackFont1,&SmallBlackFont1,0);
			MMenu.addTextButton(NULL,38+OB->Coor[i+i],135+26+OB->Coor[i+i+1],OB->Hints[i],&SmallBlackFont1,&SmallBlackFont1,&SmallBlackFont1,0);
			MMenu.addTextButton(NULL,40+OB->Coor[i+i],135+26+OB->Coor[i+i+1],OB->Hints[i],&SmallBlackFont1,&SmallBlackFont1,&SmallBlackFont1,0);
			MMenu.addTextButton(NULL,39+OB->Coor[i+i],134+26+OB->Coor[i+i+1],OB->Hints[i],&SmallWhiteFont1,&SmallWhiteFont1,&SmallWhiteFont1,0);
		};
	};
	VideoButton* OkBtn=MMenu.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	OkBtn->Hint=GetTextByID("BTL_RUN");
	VideoButton* CancelBtn=MMenu.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->Hint=GetTextByID("BTL_CANCEL");
	TextViewer* TV=MMenu.addTextViewer(NULL,50,520+3,720,118,OB->Text,&YellowFont);
	TV->SymSize=20;
	TV->PageSize=(TV->y1-TV->y)/TV->SymSize;
	VScrollBar* SB=MMenu.addNewGP_VScrollBar(NULL,777,511,118,0,1,SCROL.GPID,0);
	TV->AssignScroll(SB);
	TV->Active=1;

	ItemChoose=-1;
	int mm=1;
	KeyPressed=0;
	do{
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		if(mm){
			SlowLoadPalette("2\\agew_1.pal");
			mm=0;
		};
		StdKeys();
	}while(ItemChoose==-1);
	SlowUnLoadPalette("2\\agew_1.pal");
	return ItemChoose==mcmOk;
};
int ProcessWars(){
	if(!WARS.NWars)return false;
	KeyPressed=0;
	LastKey=0;
	SQPicture Back("Interface\\Background_Historical_Wars.bmp");
	LocalGP BTNS("Interface\\Wars");
	LocalGP OCAM("Interface\\One_Campaign");
	LocalGP SCROL("Interface\\_Slider");
	LocalGP OK1("Interface\\anm_start_on");
	LocalGP OK2("Interface\\anm_start_off");
	LocalGP CANCEL1("Interface\\anm_cancel_on");
	LocalGP CANCEL2("Interface\\anm_cancel_off");
	LocalGP ENC1("Interface\\anm_enc_on");
	LocalGP ENC2("Interface\\anm_enc_off");
	LocalGP FONT("romw");
	RLCFont FontY(FONT.GPID);
	FontY.SetColorTable(3);
	LoadOptionalTable(3,"2\\orange.grd");

	RLCFont FontW(FONT.GPID);
	FontW.SetWhiteColor();
	DialogsSystem MMenu(0,0);

	LocalGP HFONT("rom10");
	RLCFont hfnt(HFONT.GPID);
	hfnt.SetWhiteColor();
	MMenu.HintFont=&hfnt;
	MMenu.HintY=701;
	MMenu.HintX=18;

	MMenu.addPicture(NULL,0,0,&Back,&Back,&Back);
	VideoButton* ENC=MMenu.addVideoButton(NULL,862,468,ENC1.GPID,ENC2.GPID);
	ENC->UserParam=0;
	ENC->OnUserClick=&RunEnciclopia;
	ENC->Hint=GetTextByID("ENCICL");
	VideoButton* OkBtn=MMenu.addVideoButton(NULL,862,568,OK1.GPID,OK2.GPID);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	OkBtn->Hint=GetTextByID("WAR_RUN");
	VideoButton* CancelBtn=MMenu.addVideoButton(NULL,862,668,CANCEL1.GPID,CANCEL2.GPID);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->Hint=GetTextByID("WAR_CANCEL");

	for(int i=0;i<WARS.NWars&&i<5;i++)
		MMenu.addGPPicture(NULL,68,166+i*26,OCAM.GPID,6);

	GPPicture* ZBTL[5];
	for(i=0;i<5;i++){
		ZBTL[i]=MMenu.addGPPicture(NULL,444,166+26*i,OCAM.GPID,6);
		ZBTL[i]->Visible=0;
	};
	VScrollBar* CWS=MMenu.addNewGP_VScrollBar(NULL,395,156,146,1,0,SCROL.GPID,0);
	ListBox* CWar=MMenu.addGP_ListBox(NULL,68,166,5,BTNS.GPID,6,26,&WhiteFont,&YellowFont,CWS);
	CWar->FontDy-=2;
	CWar->M_Over=9;
	VScrollBar* CBS=MMenu.addNewGP_VScrollBar(NULL,755,156,146,1,0,SCROL.GPID,0);
	ListBox* CBat=MMenu.addGP_ListBox(NULL,444,166,5,BTNS.GPID,0,26,&WhiteFont,&YellowFont,CBS);
	CBat->FontDy-=2;
	CBat->M_Over=3;
	TextViewer* TV[32];
	VScrollBar* VS[32];
	for(i=0;i<WARS.NWars;i++){
		CWar->AddItem(WARS.Wars[i].Name,0);
		TV[i]=MMenu.addTextViewer(NULL,78,353,663,275,WARS.Wars[i].Text,&YellowFont);
		TV[i]->Visible=0;
		TV[i]->Active=0;
		TV[i]->Enabled=0;
		TV[i]->SymSize=19;
		TV[i]->PageSize=(TV[i]->y1-TV[i]->y)/TV[i]->SymSize;
		TV[i]->Enabled=false;
		TV[i]->Visible=false;
		VS[i]=MMenu.addNewGP_VScrollBar(NULL,755,338,291,1,0,SCROL.GPID,0);
		TV[i]->AssignScroll(VS[i]);
		VS[i]->Visible=0;
	};
	int CurWar=-1;
WStart:;
	int mm=1;
	ItemChoose=-1;
	KeyPressed=0;
	do{
		if(CWar->CurItem!=CurWar){
			CBat->ClearItems();
			CurWar=CWar->CurItem;
			for(int j=0;j<WARS.Wars[CurWar].NBatles;j++){
				CBat->AddItem(WARS.Battles[WARS.Wars[CurWar].BattleList[j]].SmallHeader,0);
			};
		};
		ProcessMessages();
		StdKeys();
		MMenu.MarkToDraw();
		MMenu.ProcessDialogs();
		MMenu.RefreshView();
		for(i=0;i<WARS.NWars;i++){
			TV[i]->Enabled=false;
			TV[i]->Visible=false;
			TV[i]->Active=false;
			VS[i]->Visible=false;
		};
		TV[CWar->CurItem]->Enabled=1;
		TV[CWar->CurItem]->Visible=1;
		TV[CWar->CurItem]->Active=1;
		VS[CWar->CurItem]->Visible=VS[CWar->CurItem]->SMaxPos>0;
		int NBTL=WARS.Wars[CWar->CurItem].NBatles;
		for(i=0;i<5;i++)ZBTL[i]->Visible=i<NBTL;
		if(mm){
			SlowLoadPalette("2\\agew_1.pal");
			mm=0;
		};
		StdKeys();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		SlowUnLoadPalette("2\\agew_1.pal");
		if(!ProcessOneBattle(WARS.Wars[CWar->CurItem].BattleList[CBat->CurItem])){
			//SlowUnLoadPalette("2\\agew_1.pal");
			goto WStart;
		};
		return WARS.Wars[CWar->CurItem].BattleList[CBat->CurItem];
	};
	SlowUnLoadPalette("2\\agew_1.pal");
	return -1;
};
void SlideShow(){
	GFILE* f=Gopen("Slides\\pic.lst","r");
	if(f){
		char cc[128];
		int z;
		do{
			z=Gscanf(f,"%s",cc);
			if(z==1){
				ResFile F=RReset(cc);
				if(F!=INVALID_HANDLE_VALUE){
					RClose(F);
					DialogsSystem DSS(0,0);
					SQPicture PIC;
					PIC.LoadPicture(cc);
					DSS.addPicture(NULL,0,0,&PIC,&PIC,&PIC);
					Lpressed=0;
					KeyPressed=0;
					PIC.Draw(0,0);
					FlipPages();
					SlowLoadPalette("2\\agew_1.pal");
					do{
						DSS.ProcessDialogs();
						DSS.RefreshView();
						ProcessMessages();
					}while(!(KeyPressed||Lpressed));
					SlowUnLoadPalette("2\\agew_1.pal");
				};
			};
		}while(z==1);
	};
};
void ShowPreview(){
	ResFile F=RReset("Slides\\Preview.bmp");
	if(F!=INVALID_HANDLE_VALUE){
		WindX=0;
		WindY=0;
		WindLx=1024;
		WindLy=768;
		WindX1=1023;
		WindY1=767;
		RClose(F);
		ClearScreen();
		LoadFog(2);
		DialogsSystem DSS(0,0);
		SQPicture PIC;
		PIC.LoadPicture("Slides\\Preview.bmp");
		DSS.addPicture(NULL,0,0,&PIC,&PIC,&PIC);
		Lpressed=0;
		KeyPressed=0;
		PIC.Draw(0,0);
		FlipPages();
		SlowLoadPalette("2\\agew_1.pal");
		int t0=GetTickCount();
		do{
			DSS.ProcessDialogs();
			DSS.RefreshView();
			ProcessMessages();
		}while(!(KeyPressed||Lpressed||GetTickCount()-t0>3000));
		SlowUnLoadPalette("2\\agew_1.pal");
	};
};
void ClearScreen();
char* ROME[6]={"II","III","IV","V","VI","VII"};
int ShowStatScreen(bool Next,bool Prev,byte Kind);
int ShowUserStat(bool Prev,bool Next);
int LPAL=1;
void PrintNum(int N,char* res){
	char tmp[32];
	int ps=0;
	while(N!=0){
		int v=N%10;
		N=N/10;
		tmp[ps]='0'+v;
		ps++;
		if((ps==3||ps==7||ps==11||ps==15)&&N!=0){
			tmp[ps]='.';
			ps++;
		};
	};
	for(int j=0;j<ps;j++)res[j]=tmp[ps-j-1];
	res[ps]=0;
};
bool ShowStatistics(){
	int res=0;
	int cur=0;
	LPAL=1;
	do{
		switch(cur){
		case 0:
			res=ShowStatScreen(true,false,0);
			break;
		case 1:
			res=ShowStatScreen(true,true,1);
			break;
		case 2:
			res=ShowUserStat(true,false);
			break;
		};
		if(res==1)cur--;
		if(res==4)cur++;
		cur%=3;
	}while(res!=2&&res!=3&&res!=131);
	return res==3; 
};
void CreateCommName(byte Nat,char* Res){
	Res[0]=0;
	for(int i=0;i<7;i++){
		if(NatRefTBL[i]==Nat){
			if(Res[0])strcat(Res,"+");
			strcat(Res,GetPName(i));
		};
	};
};
int ShowStatScreen(bool Next,bool Prev,byte Kind){
	bool ExStyle=(NPlayers<2&&!PlayGameMode);
	int x=9;
	int y=13;
	int Lx=1006;
	int Ly=690;
	//ClearScreen();
	int NNAT=0;
	int NATS[7];
	int MaxPop=0;
	int MaxUpgTime=0;
	int MaxGrTime=0;
	int ODY=24;
	LocalGP BTNS;
	if(ExStyle)BTNS.Load("Interface\\Statistic_Screen");
	else BTNS.Load("Interface\\Statistic_ScreenX");
	y+=ODY;
	Ly-=ODY;
	word* Val[8];
	int NVal[8];
	char* Header;
	if(Kind){
		for(int k=0;k<7;k++){
			Val[k]=NATIONS[k].Account;
			NVal[k]=NATIONS[k].NAccount;
		};
		Header=GetTextByID("ST_ACC");
	}else{
		for(int k=0;k<7;k++){
			Val[k]=NATIONS[k].Popul;
			NVal[k]=NATIONS[k].NPopul;
		};
		Header=GetTextByID("ST_MAX");
	};
	for(int i=0;i<7;i++){
		int max=0;
		Nation* NT=NATIONS+i;
		int N=NVal[i];
		word* VAL=Val[i];
		MaxGrTime=N<<8;
		for(int j=0;j<N;j++)if(VAL[j]>max)max=VAL[j];
		if(max){
			NATS[NNAT]=i;
			NNAT++;
			if(max>MaxPop)MaxPop=max;
		};
		N=NT->NUpgMade;
		if(N&&NT->UpgTime[N-1]>MaxUpgTime)MaxUpgTime=NT->UpgTime[N-1];
	};
	int sdx=3;
	int slx=Lx-sdx*2;
	MaxUpgTime+=(40*MaxUpgTime)/(slx-40);
	if(MaxGrTime>MaxUpgTime)MaxUpgTime=MaxGrTime;
	int LXX[8];
	int XXI;
	int YYI[8];
	if(MaxPop<5)MaxPop=5;
	if(NNAT){
		int OneLy=59+4;
		int OneDy=8+2;
		int GrLy=Ly-NNAT*OneLy;
		int GrpX=20;
		int GrpY=20;
		int GrpLx=Lx-2*GrpX;
		int GrpLy=GrLy-2*GrpY;
		int deal=(MaxPop*40)/GrpLy;
		if(deal<5)deal=5;
		else if(deal<10)deal=10;
		else if(deal<15)deal=15;
		else if(deal<20)deal=20;
		else if(deal<25)deal=25;
		else if(deal<40)deal=40;
		else if(deal<50)deal=50;
		else if(deal<75)deal=75;
		else if(deal<100)deal=100;
		else if(deal<150)deal=150;
		else if(deal<200)deal=200;
		else if(deal<250)deal=250;
		else if(deal<300)deal=300;
		else if(deal<400)deal=400;
		else if(deal<500)deal=500;
		else deal=750;
		int NGridY=(MaxPop/deal)+1;
		MaxPop=NGridY*deal;

		DialogsSystem STAT(0,0);
		int DDX=110;
		if(!ExStyle)DDX=0;
		if(ExStyle){
			GP_TextButton* BT_REPLAY=STAT.addGP_TextButton(NULL,415,723,GetTextByID("REPLAY"),BTNS.GPID,9,&WhiteFont,&YellowFont);
			BT_REPLAY->OnUserClick=&MMItemChoose;
			BT_REPLAY->UserParam=131;
		};
		//GP_Button* BT=STAT.addGP_Button(NULL,263-DDX,723,BTNS.GPID,0,1);
		GP_TextButton* RGAME=STAT.addGP_TextButton(NULL,263-DDX,723,GetTextByID("ST_GAM"),BTNS.GPID,0,&WhiteFont,&YellowFont);
		RGAME->OnUserClick=&MMItemChoose;
		RGAME->UserParam=2;

		GP_TextButton* RMENU;
		if(PlayGameMode){
			RMENU=STAT.addGP_TextButton(NULL,526+DDX,723,GetTextByID("ST_MEN"),BTNS.GPID,0,&YellowFont,&YellowFont);
			RMENU->Enabled=0;
		}else RMENU=STAT.addGP_TextButton(NULL,526+DDX,723,GetTextByID("ST_MEN"),BTNS.GPID,0,&YellowFont,&WhiteFont);
		RMENU->OnUserClick=&MMItemChoose;
		RMENU->UserParam=3;

		GP_Button* BACK=STAT.addGP_Button(NULL,196-DDX,723,BTNS.GPID,8,6);
		BACK->OnUserClick=&MMItemChoose;
		BACK->UserParam=1;
		BACK->Enabled=Prev;
		BACK->Visible=Prev;

		GP_Button* NEXT=STAT.addGP_Button(NULL,788+DDX,723,BTNS.GPID,7,5);
		NEXT->OnUserClick=&MMItemChoose;
		NEXT->UserParam=4;
		NEXT->Enabled=Next;
		NEXT->Visible=Next;

		STAT.HintFont=&SmallBlackFont1;
		STAT.HintX=-1;
		STAT.HintY=250;
		char ccc[100];
		STAT.addTextButton(NULL,x+14,y-17,Header,&WhiteFont,&WhiteFont,&WhiteFont,0);
		int yy=y+GrLy;
		int xp=-1000;
		for(int i=0;i<NNAT;i++){
			xp=-1000;
			Nation* NT=NATIONS+NATS[i];
			char commname[128];
			CreateCommName(NATS[i],commname);
			//char* pnm=GetPName(NATS[i]);
			LXX[i]=GetRLCStrWidth(commname,&SmallWhiteFont1)+40;
			int dx=x+GrpX+(GrpLx-LXX[i])/2;
			STAT.addTextButton(NULL,dx+33,yy-8,commname,&SmallWhiteFont1,&SmallWhiteFont1,&SmallWhiteFont1,0);
			STAT.addColoredBar(dx+6,yy-2,24,1,0xD0+NATS[i]*4);
			XXI=x+34;
			YYI[i]=yy;
			int N=NT->NUpgMade;
			for(int j=0;j<N;j++){
				int xx=x+3+(NT->UpgTime[j]*slx)/MaxUpgTime;
				if(xx<xp){
					xx=xp+2;
				};
				xp=xx;
				NewUpgrade* NU=NT->UPGRADE[NT->UpgIDS[j]];
				if(NU->Level<2&&NU->CtgUpgrade!=23){
					SimpleDialog* SD;
					if(NU->IconFileID!=0xFFFF)SD=STAT.addGPPicture(NULL,xx,yy+OneDy,NU->IconFileID,NU->IconSpriteID);
					else SD=STAT.addColoredBar(xx,yy+OneDy,40,40,0);
					if(SD)SD->Hint=NU->Message;
					ColoredBar* CB=STAT.addColoredBar(xx,yy+OneDy,40,40,0xD0+NATS[i]*4);
					if(CB)CB->Style=1;
					if(SD)SD->Child=CB;
					/*
					if(NU->Level>1){
						TextButton* TB=STAT.addTextButton(NULL,xx+2,yy+OneDy+25,ROME[NU->Level-2],&SmallWhiteFont,&SmallWhiteFont,&SmallWhiteFont,0);
						TB->Enabled=0;
						CB->Child=TB;
					};
					*/
				};
			};
			yy+=OneLy;
		};
		ItemChoose=-1;
		KeyPressed=0;
		Lpressed=0;
		byte mm=1;
		do{
			GPS.ShowGP(0,0,BTNS.GPID,2,0);
			DrawStatTable(x,y-ODY,Lx,GrLy+ODY,OneLy,NNAT);
			for(int i=0;i<NNAT;i++)DrawStHeader(GrpX+x+GrpLx/2,YYI[i],LXX[i]);
			int gx0=GrpX+x;
			int gx1=GrpX+x+GrpLx-1;
			int gy0=GrpY+y;
			int gy1=GrpY+y+GrpLy-1;
			Xbar(gx0-1,gy0-1,gx1-gx0+3,gy1-gy0+3,0x3B);
			Xbar(gx0-2,gy0-2,gx1-gx0+5,gy1-gy0+5,0x3A);
			Xbar(gx0-3,gy0-3,gx1-gx0+7,gy1-gy0+7,0x39);
			Xbar(gx0-4,gy0-4,gx1-gx0+9,gy1-gy0+9,0xAE);
			Xbar(gx0-5,gy0-5,gx1-gx0+11,gy1-gy0+11,0xAE);
			Xbar(gx0-6,gy0-6,gx1-gx0+13,gy1-gy0+13,0xAE);
			//drawing grids
			for(int ix=0;ix<8;ix++){
				int gx0=x+GrpX+((GrpLx*ix)>>3);
				int gx1=x+GrpX+((GrpLx*(ix+1))>>3);
				for(int iy=0;iy<NGridY;iy++){
					int gy0=y+GrpY+((GrpLy*iy)/NGridY);
					int gy1=y+GrpY+((GrpLy*(iy+1))/NGridY);
					Xbar(gx0,gy0,gx1-gx0+1,gy1-gy0+1,0x3E);
					Xbar(gx0+1,gy0+1,gx1-gx0-1,gy1-gy0-1,0x3B);
					Xbar(gx0+2,gy0+2,gx1-gx0-3,gy1-gy0-3,0x3A);
					Xbar(gx0+3,gy0+3,gx1-gx0-5,gy1-gy0-5,0x39);
					Xbar(gx0+4,gy0+4,gx1-gx0-7,gy1-gy0-7,0xAE);
					Xbar(gx0+5,gy0+5,gx1-gx0-9,gy1-gy0-9,0xAE);
					Xbar(gx0+6,gy0+6,gx1-gx0-11,gy1-gy0-11,0xAE);
					if(ix==0){
						sprintf(ccc,"%d",(NGridY-iy-1)*deal);
						ShowString(gx0+3,gy1-14,ccc,&SmallBlackFont);
					};
				};
			};
			int X0,Y0,X1,Y1;
			for(i=0;i<NNAT;i++){
				Nation* NT=NATIONS+NATS[i];
				byte c=NATS[i]*4+0xD0;
				int N=NVal[NATS[i]];
				word* VAL=Val[NATS[i]];
				for(int j=0;j<N;j++){
					if(j>0){
						X0=X1;
						Y0=Y1;
					};
					X1=x+GrpX+((j<<8)*GrpLx)/MaxUpgTime;
					Y1=y+GrpY+GrpLy-(VAL[j]*(GrpLy-10))/MaxPop;
					if(j>0){
						DrawLine(X0,Y0,X1,Y1,c);
						DrawLine(X0+1,Y0,X1+1,Y1,c);
						DrawLine(X0+1,Y0+1,X1+1,Y1+1,c);
						DrawLine(X0,Y0+1,X1,Y1+1,c);
					};
				};
			};
			ProcessMessages();
			STAT.MarkToDraw();
			STAT.ProcessDialogs();
			STAT.RefreshView();
			if(LPAL){
				SlowLoadPalette("0\\agew_1.pal");
				LPAL=0;
			};
			//if(KeyPressed||Lpressed){
			//	ItemChoose=1;
			//};
		}while(ItemChoose==-1);
	}else return 3;
	KeyPressed=false;
	Lpressed=0;
	UnPress();
	return ItemChoose;
};
int ShowUnitsList(int x,int y,int Lx,word* Value);
int ShowUserStat(bool Prev,bool Next){
	bool ExStyle=(NPlayers<2&&!PlayGameMode);
	int x=9;
	int y=13;
	int Lx=1006;
	int Ly=690;
	LocalGP BTNS;
	if(ExStyle)BTNS.Load("Interface\\Statistic_Screen");
	else BTNS.Load("Interface\\Statistic_ScreenX");
	DialogsSystem STAT(0,0);
	int DDX=110;
	if(!ExStyle)DDX=0;
	if(ExStyle){
		GP_TextButton* BT_REPLAY=STAT.addGP_TextButton(NULL,415,723,GetTextByID("REPLAY"),BTNS.GPID,9,&WhiteFont,&YellowFont);
		BT_REPLAY->OnUserClick=&MMItemChoose;
		BT_REPLAY->UserParam=131;
	};
	//GP_Button* BT=STAT.addGP_Button(NULL,263,723,BTNS.GPID,0,1);
	GP_TextButton* RGAME=STAT.addGP_TextButton(NULL,263-DDX,723,GetTextByID("ST_GAM"),BTNS.GPID,0,&WhiteFont,&YellowFont);
	RGAME->OnUserClick=&MMItemChoose;
	RGAME->UserParam=2;

	GP_TextButton* RMENU;
	if(PlayGameMode){
		RMENU=STAT.addGP_TextButton(NULL,526+DDX,723,GetTextByID("ST_MEN"),BTNS.GPID,0,&YellowFont,&YellowFont);
		RMENU->Enabled=0;
	}else RMENU=STAT.addGP_TextButton(NULL,526+DDX,723,GetTextByID("ST_MEN"),BTNS.GPID,0,&WhiteFont,&YellowFont);
	RMENU->OnUserClick=&MMItemChoose;
	RMENU->UserParam=3;

	GP_Button* BACK=STAT.addGP_Button(NULL,196-DDX,723,BTNS.GPID,8,6);
	BACK->OnUserClick=&MMItemChoose;
	BACK->UserParam=1;
	BACK->Enabled=Prev;
	BACK->Visible=Prev;

	GP_Button* NEXT=STAT.addGP_Button(NULL,788+DDX,723,BTNS.GPID,7,5);
	NEXT->OnUserClick=&MMItemChoose;
	NEXT->UserParam=4;
	NEXT->Enabled=Next;
	NEXT->Visible=Next;
	ListBox* LB=STAT.addListBox(NULL,x+25,y+35,30,180,26,&WhiteFont,&YellowFont,NULL);
	byte NATS[8];
	int NNAT=0;
	for(int i=0;i<7;i++){
		int max=0;
		Nation* NT=NATIONS+i;
		int N=NT->NPopul;
		word* VAL=NT->Popul;
		for(int j=0;j<N;j++)if(VAL[j]>max)max=VAL[j];
		if(max){
			NATS[NNAT]=i;
			NNAT++;
			char commname[256];
			CreateCommName(i,commname);
			LimitString(commname,&YellowFont,200);
			LB->AddItem(commname,i);
		};
	};
	LB->CurItem=0;
	ItemChoose=-1;
	int mm=1;
	char* hdrs[8];
	hdrs[0]=GetTextByID("ST_TOTAL");
	hdrs[1]=GetTextByID("ST_UPGR");
	hdrs[2]=GetTextByID("ST_MINE");
	hdrs[3]=GetTextByID("ST_UNITS");
	hdrs[4]=GetTextByID("ST_BLD");
	hdrs[5]=GetTextByID("ST_LIFE");
	hdrs[6]=GetTextByID("ST_BUY");
	hdrs[7]=GetTextByID("ST_SELL");
	char* STHDR=GetTextByID("ST_UHDR");
	char* KHDR=GetTextByID("ST_KILL");
	char* PHDR=GetTextByID("ST_PROD");
	int curnat=0;

	int ux=230;
	int uy=320;
	int ulx=353;
	int uly=373;
	int kx=ux+ulx+45;
	VScrollBar* PBR=STAT.addNewGP_VScrollBar(NULL,ux+ulx+11,uy+1,uly-2,1,0,3,0);
	VScrollBar* KBR=STAT.addNewGP_VScrollBar(NULL,kx+ulx+11,uy+1,uly-2,1,0,3,0);
	PBR->ScrDy=200;
	KBR->ScrDy=200;
	do{
		curnat=LB->CurItem;
		int cnt=NATS[curnat];
		int* ResSrc=(int*)(&NATIONS[cnt].ResTotal);
		GPS.ShowGP(0,0,BTNS.GPID,2,0);
		DrawStatTable1(x,y,x+Lx-1,y+Ly-1,x+200);
		for(int i=0;i<LB->NItems;i++){
			CBar(LB->x-15,LB->y+15+i*25,12,3,0xD0+NatRefTBL[NATS[i]]*4);
		};
		ShowString(x+10,y+8,STHDR,&YellowFont);
		ShowString(ux+(ulx>>1)+7-(GetRLCStrWidth(PHDR,&YellowFont)>>1),uy-22,PHDR,&YellowFont);
		ShowString(kx+(ulx>>1)+7-(GetRLCStrWidth(KHDR,&YellowFont)>>1),uy-22,KHDR,&YellowFont);
		int rx=220;
		int ry=y+40;
		int rx1=rx+219+5;
		int rxl=80;
		for(int q=0;q<6;q++){
			ShowString(rx1+rxl*q+rxl+(rxl>>1)-(GetRLCStrWidth(RDS[q].Name,&YellowFont)>>1),ry+6,RDS[q].Name,&YellowFont);
		};
		Hline(rx,ry,rx1+rxl*7,70);
		ry+=26;
		Vline(rx,ry-26,ry+8*26,70);
		for(q=0;q<8;q++){
			Hline(rx,ry,rx1+rxl*7,70);
			ShowString(rx+15,ry+6,hdrs[q],&YellowFont);
			for(int j=0;j<6;j++){
				char cc1[32];
				PrintNum(ResSrc[q*8+j],cc1);
				//sprintf(cc1,"%d",ResSrc[q*8+j]);
				ShowString(rx1+rxl*j+rxl+(rxl>>1)-(GetRLCStrWidth(cc1,&YellowFont)>>1),ry+6,cc1,&YellowFont);
				if(q==0){
					Vline(rx1+rxl*j+rxl,ry-26,ry+8*26,70);
				};
			};
			if(q==0){
				Vline(rx1+rxl*7,ry-26,ry+8*26,70);
			};
			ry+=26;
		};
		Hline(rx,ry,rx1+rxl*7,70);
		TempWindow TMW;
		PushWindow(&TMW);
		Xbar(ux-10,uy,ulx+25+10,uly,70);
		IntersectWindows(ux-8,uy+1,ux+ulx+15,uy+uly-2);
		int y0=uy-PBR->SPos;
		int yfin=ShowUnitsList(ux,y0,ulx,NATIONS[cnt].NProduced);
		int mps=yfin-uly-2;
		if(mps>0){
			PBR->Visible=1;
			PBR->Enabled=1;
			PBR->SMaxPos=mps;
		}else{
			PBR->Visible=0;
			PBR->Enabled=0;
			PBR->SPos=0;
		};
		PopWindow(&TMW);
		Xbar(kx-10,uy,ulx+25+10,uly,70);
		IntersectWindows(kx-8,uy+1,kx+ulx+15,uy+uly-2);
		y0=uy-KBR->SPos;
		yfin=ShowUnitsList(kx,y0,ulx,NATIONS[cnt].NKilled);
		mps=yfin-uly-2;
		if(mps>0){
			KBR->Visible=1;
			KBR->Enabled=1;
			KBR->SMaxPos=mps;
		}else{
			KBR->Visible=0;
			KBR->Enabled=0;
			KBR->SPos=0;
		};
		PopWindow(&TMW);
		ProcessMessages();
		STAT.MarkToDraw();
		STAT.ProcessDialogs();
		STAT.RefreshView();
		if(mm){
			//SlowLoadPalette("0\\agew_1.pal");
			//mm=0;
		};
		//if(KeyPressed||Lpressed){
		//	ItemChoose=1;
		//};
	}while(ItemChoose==-1);
	KeyPressed=false;
	Lpressed=0;
	UnPress();
	return ItemChoose;
};
void CenterScreen(){
	int xc=0;
	int yc=0;
	int N=0;
	int mnt=NatRefTBL[MyNation];
	for(int i=0;i<MAXOBJECT;i++){
		OneObject* OB=Group[i];
		if(OB&&OB->NNUM==mnt){
			xc+=OB->RealX>>4;
			yc+=OB->RealY>>4;
			N++;
		};
	};
	if(N){
		int x=xc/N;
		int y=yc/N;
		x=(x-(RealLx>>1))>>5;
		y=(y-RealLy)>>5;
		if(x<1)x=1;
		if(y<1)y=1;
		if(x+smaplx>=msx-1)x=msx-smaplx-1;
		if(y+smaply>=msy-1)y=msy-smaply-1;
		mapx=x;
		mapy=y;
	};
};
extern bool EnterChatMode;
extern char ChatString[128];
bool Superuser=0;
void AssignHint1(char* s,int time);
void CmdGiveMoney(byte SrcNI,byte DstNI,byte Res,int Amount);
void CmdMoney(byte NI);
int ReadKey();
extern int NKeys;
extern char CHATSTRING[256];
int ChatCursPos=0;
bool CheckFNSend(int idx);
extern byte LastAscii;
void HandleSMSChat(char* Mess);
void HandlwSMSMouse();
void CmdOfferVoting();
void ProcessChatKeys(){
KRT:
	if(!NKeys)return;
	LastKey=ReadKey();
	KeyPressed=0;
	if(LastKey==27){
		EnterChatMode=0;
		ChatString[0]=0;
		return;
	};
	if(LastKey==13){
		HandleSMSChat(ChatString);
		EnterChatMode=0;
		AssignHint1(ChatString,250,16+NatRefTBL[MyNation]);
		SendChat(ChatString,GetKeyState(VK_CONTROL)&0x8000);
		ChatCursPos=0;
		if(NPlayers<2){
			if(!strcmp(ChatString,"www")){
				ChangeNation=1;
				MultiTvar=1;
				FogMode=0;
			}else
			if(!strcmp(ChatString,"VICTORY")){
				if(NPlayers<2)ShowVictory();
			}else
			if(!strcmp(ChatString,"IZMENA")||!strcmp(ChatString,"izmena"))ChangeNation=!ChangeNation;
			if(!strcmp(ChatString,"MULTITVAR")||!strcmp(ChatString,"multitvar"))MultiTvar=!MultiTvar;
			if(!strcmp(ChatString,"SUPERVIZOR")||!strcmp(ChatString,"supervizor"))FogMode=!FogMode;
			if(!strcmp(ChatString,"MONEY")||!strcmp(ChatString,"money"))CmdMoney(MyNation);
			else if(NPlayers<2){
				char cc1[64];
				int n1,n2;
				int z=sscanf(ChatString,"%s%d%d",cc1,&n1,&n2);
				if(z==3&&!strcmp(cc1,"change")){
					if(n1>=0&&n1<8&&n2>=0&&n2<=8)SelChangeNation(n1,n2);
				};
				char cc2[128];
				z=sscanf(ChatString,"%s%s",cc1,cc2);
				if(z==2&&!strcmp(cc1,"changeunit")){
					word Type=0xFFFF;
					for(int i=0;i<NATIONS->NMon;i++){
						if(!strcmp(cc2,NATIONS->Mon[i]->MonsterID)){
							GeneralObject* GO=NATIONS->Mon[i];
							if(!GO->newMons->Building){
								//found!!!
								int N=NSL[MyNation];
								word* IDS=Selm[MyNation];
								word* SMS=SerN[MyNation];
								for(int j=0;j<N;j++){
									word MID=IDS[j];
									if(MID!=0xFFFF){
										OneObject* OB=Group[MID];
										if(OB&&!OB->Sdoxlo){
											OB->Ref.General=GO;
											OB->NIndex=i;
											OB->newMons=GO->newMons;
										};
									};
								};
							};
						};
					};
				};
			};
		}else{
			//if(!strcmp(ChatString,"SuPeRuSeR"))Superuser=1;
		};
		if(ChatString[0]=='g'&&ChatString[1]=='i'&&ChatString[2]=='v'&&ChatString[3]=='e'&&ChatString[4]==' '){
			char* sss=ChatString+5;
			char cc1[100];
			int p=0;
			char c;
			while(sss[0]==' ')sss++;
			do{
				c=sss[0];
				cc1[p]=c;
				if(c!=' ')p++;
				sss++;
			}while(c!=0&&c!=' '&&p<20);
			cc1[p]=0;
			if(c==0)return;
			int res=-1;
			if(!strcmp(cc1,"wood"))res=0;
			else if(!strcmp(cc1,"gold"))res=1;
			else if(!strcmp(cc1,"stone"))res=2;
			else if(!strcmp(cc1,"food"))res=3;
			else if(!strcmp(cc1,"iron"))res=4;
			else if(!strcmp(cc1,"coal"))res=5;
			if(res==-1)return;
			while(sss[0]==' ')sss++;
			p=0;
			do{
				c=sss[0];
				cc1[p]=c;
				if(c>='0'&&c<='9')c=0;
				cc1[p]=c;
				if(c){
					sss++;
					p++;
				};
			}while(c!=0&&p<40);
			int L;
			do{
				L=strlen(cc1);
				if(L&&cc1[L-1]==' ')cc1[L-1]=0;
				else L=0;
			}while(L);
			int Him=-1;
			for(int i=0;i<NPlayers;i++){
				if(!strcmp(cc1,PINFO[i].name))Him=PINFO[i].ColorID;
			};
			if(Him==-1)return;
			while(sss[0]==' ')sss++;
			int Amn;
			int z=sscanf(sss,"%d",&Amn);
			if(z!=1)return;
			CmdGiveMoney(MyNation,Him,res,Amn);
		};
		ChatString[0]=0;
		return;
	};
	if(LastKey>=VK_F1&&LastKey<VK_F9){
		if(CheckFNSend(LastKey-VK_F1)){
			EnterChatMode=0;	
			NKeys=0;
			return;
		};
	};
	
	if(LastKey==VK_LEFT){
		if(ChatCursPos>0)ChatCursPos--;
		KeyPressed=0;
		LastKey=0;
		goto KRT;
	}else
	if(LastKey==VK_RIGHT){
		if(ChatCursPos<strlen(ChatString))ChatCursPos++;
		KeyPressed=0;
		LastKey=0;
		goto KRT;
	}else
	if(LastKey==VK_END){
		ChatCursPos=strlen(ChatString);
		KeyPressed=0;
		LastKey=0;
		goto KRT;
	}else
	if(LastKey==VK_HOME){
		ChatCursPos=0;
		KeyPressed=0;
		LastKey=0;
		goto KRT;
	}else
	if(LastKey==VK_BACK){
		if(ChatCursPos>0){
			strcpy(ChatString+ChatCursPos-1,ChatString+ChatCursPos);
			ChatCursPos--;
		};
		//if(strlen(IB->Str)>0)IB->Str[strlen(IB->Str)-1]=0;
		goto KRT;
	}else
	if(LastKey==46){//VK_DEL
		if(ChatCursPos<strlen(ChatString))strcpy(ChatString+ChatCursPos,ChatString+ChatCursPos+1);
		//if(strlen(IB->Str)>0)IB->Str[strlen(IB->Str)-1]=0;
		goto KRT;
	}else{
		if(LastAscii){
			LastKey=LastAscii;
			char xx[2];
			xx[1]=0;
			xx[0]=char(LastKey);
			if(strlen(ChatString)+1<120){
				char ccc[2048];
				strcpy(ccc,ChatString);
				ccc[ChatCursPos]=0;
				strcat(ccc,xx);
				strcat(ccc,ChatString+ChatCursPos);
				strcpy(ChatString,ccc);
				ChatCursPos++;
			};
			goto KRT;
		};
	};
	if(NKeys)goto KRT;
	if(ChatCursPos>strlen(ChatString))ChatCursPos=strlen(ChatString);
/*







	//if(!KeyPressed)return;
KRT:
	if(!NKeys)return;
	LastKey=ReadKey();
	KeyPressed=0;
	if(LastKey==27){
		EnterChatMode=0;
		ChatString[0]=0;
		return;
	};
	if(LastKey>=VK_F1&&LastKey<=VK_F9){
		if(CheckFNSend(LastKey-VK_F1)){
			EnterChatMode=0;	
			NKeys=0;
			return;
		};
	};
	if(LastKey==13){
		EnterChatMode=0;
		AssignHint1(ChatString,250,16+MyNation);
		SendChat(ChatString,GetKeyState(VK_CONTROL)&0x8000);
		if(NPlayers<2){
			if(!strcmp(ChatString,"www")){
				ChangeNation=1;
				MultiTvar=1;
				FogMode=0;
			}else
			if(!strcmp(ChatString,"VICTORY")){
				if(NPlayers<2)ShowVictory();
			}else
			if(!strcmp(ChatString,"IZMENA")||!strcmp(ChatString,"izmena"))ChangeNation=!ChangeNation;
			if(!strcmp(ChatString,"MULTITVAR")||!strcmp(ChatString,"multitvar"))MultiTvar=!MultiTvar;
			if(!strcmp(ChatString,"SUPERVIZOR")||!strcmp(ChatString,"supervizor"))FogMode=!FogMode;
			if(!strcmp(ChatString,"MONEY")||!strcmp(ChatString,"money"))CmdMoney(MyNation);
			else if(NPlayers<2){
				char cc1[64];
				int n1,n2;
				int z=sscanf(ChatString,"%s%d%d",cc1,&n1,&n2);
				if(z==3&&!strcmp(cc1,"change")){
					if(n1>=0&&n1<8&&n2>=0&&n2<=8)SelChangeNation(n1,n2);
				};
			};
		}else{
			//if(!strcmp(ChatString,"SuPeRuSeR"))Superuser=1;
		};
		if(ChatString[0]=='g'&&ChatString[1]=='i'&&ChatString[2]=='v'&&ChatString[3]=='e'&&ChatString[4]==' '){
			char* sss=ChatString+5;
			char cc1[100];
			int p=0;
			char c;
			while(sss[0]==' ')sss++;
			do{
				c=sss[0];
				cc1[p]=c;
				if(c!=' ')p++;
				sss++;
			}while(c!=0&&c!=' '&&p<20);
			cc1[p]=0;
			if(c==0)return;
			int res=-1;
			if(!strcmp(cc1,"wood"))res=0;
			else if(!strcmp(cc1,"gold"))res=1;
			else if(!strcmp(cc1,"stone"))res=2;
			else if(!strcmp(cc1,"food"))res=3;
			else if(!strcmp(cc1,"iron"))res=4;
			else if(!strcmp(cc1,"coal"))res=5;
			if(res==-1)return;
			while(sss[0]==' ')sss++;
			p=0;
			do{
				c=sss[0];
				cc1[p]=c;
				if(c>='0'&&c<='9')c=0;
				cc1[p]=c;
				if(c){
					sss++;
					p++;
				};
			}while(c!=0&&p<40);
			int L;
			do{
				L=strlen(cc1);
				if(L&&cc1[L-1]==' ')cc1[L-1]=0;
				else L=0;
			}while(L);
			int Him=-1;
			for(int i=0;i<NPlayers;i++){
				if(!strcmp(cc1,PINFO[i].name))Him=PINFO[i].ColorID;
			};
			if(Him==-1)return;
			while(sss[0]==' ')sss++;
			int Amn;
			int z=sscanf(sss,"%d",&Amn);
			if(z!=1)return;
			CmdGiveMoney(MyNation,Him,res,Amn);
		};
		ChatString[0]=0;
		return;
	};
	if(LastKey==VK_BACK){
		if(strlen(ChatString)>0)ChatString[strlen(ChatString)-1]=0;
		return;
	}else{
		LastKey=LastAscii;
		if(LastKey){
		
			char xx[2];
			xx[1]=0;
			xx[0]=char(LastKey);
			if(strlen(ChatString)<80)strcat(ChatString,xx);
		};
	};
	if(NKeys)goto KRT;
	*/
};
extern char CHATSTRING[256];
extern DWORD CHATDPID;
void ShowMultiplayerChat();
void ShowChat(){
	if(NPlayers>0){
		ShowMultiplayerChat();
		return;
	};
	if(EnterChatMode){
		int y0=smapy+(smaply<<(Shifter-2));
		int x0=smapx+(smaplx<<(Shifter-1));
		int Dy=GetRLCHeight(BigYellowFont.RLC,'y')+5;
		int L0=GetRLCStrWidth(ENCHAT,&BigYellowFont);
		int L=(GetRLCStrWidth(ChatString,&YellowFont)+L0)>>1;
		if(L<100)L=100;
		DrawStdBar(x0-L-16,y0-8,x0+L+16,y0+20+7);
		ShowString(x0-L-4,y0-5,ENCHAT,&BigWhiteFont);
		char cc2[300];
		if((GetRealTime()/200)&1)ShowString(x0-L+L0+4,y0-4+7,ChatString,&YellowFont);
		else{
			int xx=0;
			for(int i=0;i<ChatCursPos;i++)xx+=GetRLCWidth(YellowFont.RLC,ChatString[i]);
			//sprintf(cc2,"%s|",ChatString);
			ShowString(x0-L+L0+4,y0-4+7,ChatString,&YellowFont);
			ShowString(x0-L+L0+xx+4,y0-4+7,"|",&YellowFont);
		};
	};
	if(CHATSTRING[0]){
		for(int i=0;i<NPlayers;i++)if(PINFO[i].PlayerID==CHATDPID){
			char cc1[250];
			sprintf(cc1,"%s: %s",PINFO[i].name,CHATSTRING);
			AssignHint1(cc1,250,16+NatRefTBL[PINFO[i].ColorID]);
			PlayEffect(GetSound("START"),0,0);
			CHATSTRING[0]=0;
			i=NPlayers;
		};
	};
};
int NGSPlayers;
char GSPLAYERS[9][32];
bool ProcessIndividualMessages(char* nick,char* message){
	if(GameInProgress){
		char cc3[1024];
		sprintf(cc3,GetTextByID("COMCHAT"),nick,message);
		AssignHint1(cc3,400,0);
		PlayEffect(GetSound("START"),0,0);
		if(NGSPlayers>7)return true;
		for(int i=0;i<NGSPlayers;i++){
			if(!_stricmp(GSPLAYERS[i],nick))return true;
		};
		strcpy(GSPLAYERS[NGSPlayers],nick);
		NGSPlayers++;
		return true;
	}else return false;
};

char* CHATHELP1=NULL;
char* CHATHELP2=NULL;
char* CHATHELP3=NULL;
void DrawDoubleTable2(int x0,int y0,int x1,int y1,int ym);
void ShowMultiplayerChat(){
	if(EnterChatMode){
		if(!CHATHELP1){
			CHATHELP1=GetTextByID("CHATHELP1");
			CHATHELP2=GetTextByID("CHATHELP2");
			CHATHELP3=GetTextByID("CHATHELP3");
		};
		int DDD=20;
		int y0=smapy+(smaply<<(Shifter-2))-50-DDD/2;
		int x0=smapx+(smaplx<<(Shifter-1));
		int Dy=GetRLCHeight(BigYellowFont.RLC,'y')+5;
		int L0=GetRLCStrWidth(ENCHAT,&BigYellowFont);
		int L=GetRLCStrWidth(ChatString,&YellowFont)+L0;
		int L1=GetRLCStrWidth(CHATHELP1,&SmallWhiteFont);
		int L2=GetRLCStrWidth(CHATHELP2,&SmallWhiteFont);
		if(L2>L1)L1=L2;
		char cc3[256];
		for(int i=0;i<NGSPlayers;i++){
			sprintf(cc3,CHATHELP3,i+1,GSPLAYERS);
			L2=GetRLCStrWidth(cc3,&SmallWhiteFont);
			if(L2>L1)L1=L2;
		};
		if(L<L1)L=L1;
		L>>=1;
		if(L<100)L=100;
		//DrawStdBar(x0-L-16,y0-8,x0+L+16,y0+20+7);
		DrawDoubleTable2(x0-L-16,y0-8,x0+L+16,y0+20+7+DDD*(2+NGSPlayers)+16,y0+20+7);
		ShowString(x0-L-4,y0-5,ENCHAT,&BigWhiteFont);
		char cc2[300];
		if((GetRealTime()/200)&1)ShowString(x0-L+L0+4,y0-4+7,ChatString,&YellowFont);
		else{
			int xx=0;
			for(int i=0;i<ChatCursPos;i++)xx+=GetRLCWidth(YellowFont.RLC,ChatString[i]);
			//sprintf(cc2,"%s|",ChatString);
			ShowString(x0-L+L0+4,y0-4+7,ChatString,&YellowFont);
			ShowString(x0-L+L0+xx+4,y0-4+7,"|",&YellowFont);
		};
		ShowString(x0-GetRLCStrWidth(CHATHELP1,&SmallYellowFont)/2,y0+20+7+DDD/2,CHATHELP1,&SmallYellowFont);
		ShowString(x0-GetRLCStrWidth(CHATHELP2,&SmallYellowFont)/2,y0+20+7+DDD/2+DDD,CHATHELP2,&SmallYellowFont);
		for(i=0;i<NGSPlayers;i++){
			sprintf(cc3,CHATHELP3,i+1,GSPLAYERS[i]);
			L2=GetRLCStrWidth(cc3,&SmallWhiteFont);
			ShowString(x0-L2/2,y0+20+7+DDD/2+DDD*(i+2),cc3,&SmallYellowFont);
		};
	};
	if(CHATSTRING[0]){
		for(int i=0;i<NPlayers;i++)if(PINFO[i].PlayerID==CHATDPID){
			char cc1[250];
			sprintf(cc1,"%s: %s",PINFO[i].name,CHATSTRING);
			AssignHint1(cc1,250,16+NatRefTBL[PINFO[i].ColorID]);
			PlayEffect(GetSound("START"),0,0);
			CHATSTRING[0]=0;
			i=NPlayers;
		};
	};
};
bool CheckFNSend(int idx){
	if(!EnterChatMode)return false;
	if(idx<NGSPlayers){
		if(TPEN.Peer&&TPEN.Connected&&ChatString[0]){
			peerMessagePlayer(TPEN.Peer,GSPLAYERS[idx],ChatString);
			char cc3[1024];
			sprintf(cc3,GetTextByID("CHATHELP4"),GSPLAYERS[idx],ChatString);
			AssignHint1(cc3,100,0);
			ChatString[0]=0;
		};
		EnterChatMode=0;
		return true;
	};
	return false;
};
void GetTimeString(int t,char* str){
	int h=t/3600;
	int m=(t/60)%60;
	int s=(t%60);
	sprintf(str,"%d:%d%d:%d%d",h,m/10,m%10,s/10,s%10);
};
int SortPlayers(byte* Res,int* par);
void ShowVictInFormat(char* Res,int idx,byte Type);
void SendInfoString(char* nick){
	if(!(TPEN.Peer&&TPEN.Connected&&!TPEN.ChatConnected))return;
	char BIGINFO[2048];
	sprintf(BIGINFO,"@@@GMRIN %s\\",TPEN.HostMessage);
	switch(PINFO[0].VictCond){
	case 0:
		strcat(BIGINFO,"Total Destruction\\");
		break;
	case 1 :
		strcat(BIGINFO,"Territory Capture ");
		GetTimeString(PINFO[0].GameTime,BIGINFO+strlen(BIGINFO));
		strcat(BIGINFO,"\\");
		break;
	case 2 :
		strcat(BIGINFO,"Game on score ");
		GetTimeString(PINFO[0].GameTime,BIGINFO+strlen(BIGINFO));
		strcat(BIGINFO,"\\");
		break;
	default:
		return;
	};
	byte ord[8];
	int  par[8];
	int no=SortPlayers(ord,par);
	byte prevms=0;
	int teamidx=0;
	if(no){
		byte prevms=0;
		for(int q=0;q<no;q++){
			byte ms=NATIONS[ord[q]].NMask;
			if(!(ms&prevms))teamidx++;
			prevms=ms;
			char ccr[64];
			ShowVictInFormat(ccr,ord[q],PINFO[0].VictCond);
			sprintf(BIGINFO+strlen(BIGINFO),"%d %s (%s)\\",teamidx,GetPName(ord[q]),ccr);
		};
	};
	if(strlen(BIGINFO)<200)peerMessagePlayer(TPEN.Peer,nick,BIGINFO);
};
//---------------------MAP EDITOR INTERFACE--------------//
byte MI_Mode=1;

int CurrentEditMode;
DialogsSystem MAPTOOLS(2,0);
void LoadMapInterface(){
	MapGP=GPS.PreLoadGPImage("Interface\\ToolBox");
	GPS.PreLoadGPImage("Interface\\ToolOpt");
};
void ClearModes();
extern int WaterEditMode;
extern byte LockMode;
extern int ZoneCmd;
void CreateTOOL_PARAM_UNIT();
void CreateTOOL_PARAM_SPRITE(byte ID);
void CreateTOOL_PARAM_DEFAULT();
void CreateTOOL_PARAM_TEXTURE();
void CreateTOOL_PARAM_PIECES();
void CreateTOOL_PARAM_WATER();
void CreateTOOL_PARAM_BRIGHTNESS(byte type);
void CreateTOOL_PARAM_RELIEF(byte);
void PressCurrentEdModeButton(int cn){
	if(!EditMapMode)return;
	GP_Button* GB=(GP_Button*)MAPTOOLS.DSS[cn+1];
	if(CurrentEditMode!=-1){
		GP_Button* GBO=(GP_Button*)MAPTOOLS.DSS[CurrentEditMode+1];
		GBO->PassiveFrame=GBO->UserParam*3+2;
		GBO->ActiveFrame=GBO->UserParam*3+3;
	};
	GB->PassiveFrame=GB->UserParam*3+1;
	GB->ActiveFrame=GB->PassiveFrame;
	CurrentEditMode=GB->UserParam;
};
extern int HiStyle;
extern bool RiverEditMode;
extern int Inform;
extern bool OptHidden;
bool ON_TOOL_CLICK(SimpleDialog* SD){
	GP_Button* GB=(GP_Button*)SD;
	if(CurrentEditMode!=-1){
		GP_Button* GBO=(GP_Button*)MAPTOOLS.DSS[CurrentEditMode+1];
		GBO->PassiveFrame=GBO->UserParam*3+2;
		GBO->ActiveFrame=GBO->UserParam*3+3;
	};
	GB->PassiveFrame=GB->UserParam*3+1;
	GB->ActiveFrame=GB->PassiveFrame;
	CurrentEditMode=GB->UserParam;
	ClearModes();
	Creator=4096+255;
	OptHidden=0;
	Inform=0;
	switch(GB->UserParam){
	case 0:
		CreateTOOL_PARAM_DEFAULT();
		break;
	case 1://SelectTexture
		CreateTOOL_PARAM_TEXTURE();
		break;
	case 2://select trees
		CreateTOOL_PARAM_SPRITE(0);
		break;
	case 3://select stones
		CreateTOOL_PARAM_SPRITE(1);
		break;
	case 4://erase objects
		CreateTOOL_PARAM_RELIEF(1);
		HeightEditMode=3;
		MEditMode=false;
		EditMedia=5;
		break;
	case 5:
		CreateTOOL_PARAM_DEFAULT();
		RiverEditMode=1;
		break;
	case 6://set water
		CreateTOOL_PARAM_WATER();
		WaterEditMode=1;
		break;
	case 7://clear water
		CreateTOOL_PARAM_WATER();
		WaterEditMode=2;
		break;
	case 8://set bright water
		CreateTOOL_PARAM_BRIGHTNESS(0);
		WaterEditMode=3;
		break;
	case 9://clear bright water
		CreateTOOL_PARAM_BRIGHTNESS(1);
		WaterEditMode=4;
		break;
	case 10://Hill up/down
		CreateTOOL_PARAM_RELIEF(0);
		HeightEditMode=1;
		HiStyle=0;
		break;
	case 11://plane up/down
		CreateTOOL_PARAM_RELIEF(0);
		HeightEditMode=10;
		HiStyle=0;
		break;
	case 12://equalise/distort surface
		CreateTOOL_PARAM_RELIEF(0);
		HeightEditMode=11;
		HiStyle=0;
		break;
	case 13://soft/distort surface
		CreateTOOL_PARAM_RELIEF(0);
		HeightEditMode=12;
		HiStyle=0;
		break;
	case 14://draw curve with relief
		CreateTOOL_PARAM_DEFAULT();
		HeightEditMode=13;
		HiStyle=0;
		break;
	case 15://paste piece
		CreateTOOL_PARAM_PIECES();
		break;
	case 16://unblock mode
		CreateTOOL_PARAM_DEFAULT();
		LockMode=1;
		break;
	case 17://block mode
		CreateTOOL_PARAM_DEFAULT();
		LockMode=2;
		break;
	case 18://default blocking
		CreateTOOL_PARAM_DEFAULT();
		LockMode=3;
		break;
	case 19://set unit
		CreateTOOL_PARAM_UNIT();
		break;
	case 20://create zone
		CreateTOOL_PARAM_DEFAULT();
		ZoneCmd=1;
		break;
	case 21://create group
		CreateTOOL_PARAM_DEFAULT();
		ZoneCmd=2;
		break;
	};
	Lpressed=0;
	UnPress();
	return true;
};
char* UNKED="???";

bool ToolsHidden=0;
bool OptHidden=0;
void ProcessTerrainEditor();
void CreateTotalLocking();
void ResearchIslands();
void Reset3D();
extern bool PeaceMode;
bool TBOX_DIALOGS(SimpleDialog* SD){
	switch(SD->UserParam){
	case 1:
		EditMiniMap();
		break;
	case 2:
		ProcessTerrainEditor();
		break;
	case 3:
		EraseAreas();
		rando();//!!
		CreateTotalLocking();
		ResearchIslands();
		break;
	case 4:
		Reset3D();
		break;
	case 5:
		ProcessResEdit();
		break;
	case 6:
		PeaceMode=!PeaceMode;
		break;
	};
	return true;
};
bool HideTool(SimpleDialog* SD){
	ToolsHidden=1;
	return true;
};
void CreateMapInterface(){
	MAPTOOLS.CloseDialogs();
	MAPTOOLS.HintX=-1;
	MAPTOOLS.HintY=280;
	MAPTOOLS.HintFont=&SmallBlackFont1;
	int x0=0;
	int y0=32;
	MAPTOOLS.addGPPicture(NULL,x0,y0,MapGP,0);
	
	for(int i=0;i<22;i++){
		GP_Button* BT=MAPTOOLS.addGP_Button(NULL,x0+13+(i&1)*30,y0+42+(i/2)*30,MapGP,3+i*3,2+i*3);
		BT->OnUserClick=&ON_TOOL_CLICK;
		BT->UserParam=i;
		char HINID[32];
		sprintf(HINID,"$EHIN_%d",i);
		BT->Hint=GetTextByID(HINID);
		if(BT->Hint[0]=='$')BT->Hint=UNKED;
	};
	int DYY=132;
	GP_Button* B2=MAPTOOLS.addGP_Button(NULL,13,279+DYY,MapGP,69,68);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=1;
	B2->Hint=GetTextByID("$EHIN__0");

	B2=MAPTOOLS.addGP_Button(NULL,13+30,279+DYY,MapGP,72,71);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=2;
	B2->Hint=GetTextByID("$EHIN__1");

	B2=MAPTOOLS.addGP_Button(NULL,13,279+30+DYY,MapGP,75,74);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=3;
	B2->Hint=GetTextByID("$EHIN__2");

	B2=MAPTOOLS.addGP_Button(NULL,13+30,279+30+DYY,MapGP,78,77);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=4;
	B2->Hint=GetTextByID("$EHIN__3");

	B2=MAPTOOLS.addGP_Button(NULL,13,279+60+DYY,MapGP,81,80);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=5;
	B2->Hint=GetTextByID("$EHIN__4");

	B2=MAPTOOLS.addGP_Button(NULL,13+30,279+60+DYY,MapGP,84,83);
	B2->OnUserClick=&TBOX_DIALOGS;
	B2->UserParam=6;
	B2->Hint=GetTextByID("$EHIN__5");

	GP_Button* HIDE=MAPTOOLS.addGP_Button(NULL,48,13+32,MapGP,85,86);
	HIDE->OnUserClick=&HideTool;
};
bool DRAWLOCK=0;
void ClearUnderDialog(DialogsSystem* DSS){
	for(int i=0;i<512;i++){
		SimpleDialog* SD=DSS->DSS[i];
		if(SD&&SD->Visible&&mouseX>=SD->x&&mouseY>=SD->y&&mouseX<=SD->x1&&mouseY<=SD->y1){
			UnPress();
			Lpressed=0;
			ClearMStack();
			DRAWLOCK=1;
		};
	};
};
void ProcessTOOL_PARAM();
extern int CUR_TOOL_MODE;
extern byte NeedToPopUp;
void ProcessMapInterface(){
	DRAWLOCK=0;
	if(PlayGameMode){
		if(CUR_TOOL_MODE){
			NeedToPopUp=1;
		};
	};
	if(EditMapMode){
		if(MI_Mode==1){
			MI_Mode=2;
			CreateMapInterface();
		};
		if(MI_Mode==2&&!ToolsHidden){
			MAPTOOLS.ProcessDialogs();
			ClearUnderDialog(&MAPTOOLS);
		};
	};
	ProcessTOOL_PARAM();
};
ColoredBar* NCLB=NULL;
DialogsSystem TOOL_PARAM(0,0);
bool TP_Made=0;
int CUR_TOOL_MODE=0;
bool CH_NATION_CLICK(SimpleDialog* SD){
	NCLB->x=SD->x-2;
	NCLB->y=SD->y-2;
	NCLB->x1=NCLB->x+23-1;
	NCLB->y1=NCLB->y+17-1;
	SetMyNation(SD->UserParam);
	NCLB->color=((ColoredBar*)SD)->color;
	return true;
};
void CmdChangeNatRefTBL(byte* TBL);
extern bool BuildMode;
bool CH_NATION_CLICK_MP(SimpleDialog* SD){
	BuildMode=0;
	NCLB->x=SD->x-2;
	NCLB->y=SD->y-2;
	NCLB->x1=NCLB->x+23-1;
	NCLB->y1=NCLB->y+17-1;
	byte RTB[8];
	memcpy(RTB,NatRefTBL,8);
	RTB[MyNation]=SD->UserParam;
	CmdChangeNatRefTBL(RTB);
	NCLB->color=((ColoredBar*)SD)->color;
	return true;
};
bool CloseToolOpt(SimpleDialog* SD){
	OptHidden=1;
	return true;
};
bool CheckFlagsNeed(){
	if(NPlayers<2)return false;
	if(SCENINF.hLib)return false;
	byte Mask=NATIONS[NatRefTBL[MyNation]].NMask;
	int N=0;
	for(int i=0;i<7;i++){
		if(NATIONS[i].NMask&Mask&&NATIONS[i].VictState!=1&&NATIONS[i].VictState!=2)N++;
	};
	return N>1;
};
void CreateFlags(int x0,int y0){
	if(NPlayers>1){
		byte Mask=NATIONS[NatRefTBL[MyNation]].NMask;
		for(int i=0;i<8;i++){
			if(NATIONS[i].NMask&Mask&&NATIONS[i].VictState!=1&&NATIONS[i].VictState!=2){
				ColoredBar* BCX=TOOL_PARAM.addColoredBar(x0+2+i*28,y0+2,18,12,0xD0+i*4);
				BCX->OnUserClick=&CH_NATION_CLICK_MP;
				BCX->UserParam=i;
				if(i==NatRefTBL[MyNation]){
					NCLB=TOOL_PARAM.addColoredBar(x0+i*24,y0,22,16,0xD0+i*4);
					NCLB->x=BCX->x-2;
					NCLB->y=BCX->y-2;
					NCLB->x1=NCLB->x+23-1;
					NCLB->y1=NCLB->y+17-1;
					NCLB->Style=1;
				};
			}else{
				ColoredBar* BCX=TOOL_PARAM.addColoredBar(x0+2+i*28+7,y0+2+4,18-14,12-8,0xD0+i*4);
				BCX->Style=1;
			};
		};
	}else{
		for(int i=0;i<8;i++){
			ColoredBar* BCX=TOOL_PARAM.addColoredBar(x0+2+i*28,y0+2,18,12,0xD0+i*4);
			BCX->OnUserClick=&CH_NATION_CLICK;
			BCX->UserParam=i;
			if(i==MyNation){
				NCLB=TOOL_PARAM.addColoredBar(x0+i*24,y0,22,16,0xD0+i*4);
				NCLB->x=BCX->x-2;
				NCLB->y=BCX->y-2;
				NCLB->x1=NCLB->x+23-1;
				NCLB->y1=NCLB->y+17-1;
				NCLB->Style=1;
			};
		};
	};
	GP_Button* B=TOOL_PARAM.addGP_Button(NULL,InfDX-32,-27,MapGP,86,85);
	B->OnUserClick=&CloseToolOpt;
};
extern int UNI_LINEDLY1;
extern int UNI_LINEDY1;
extern int  ReliefBrush;
void StdWheel(){
	if(WheelDelta){
		ReliefBrush+=WheelDelta/120;
	};
	if(ReliefBrush<1)ReliefBrush=1;
	if(ReliefBrush>110)ReliefBrush=110;
	WheelDelta=0;
};
void CreateTOOL_PARAM_DEFAULT(){
	CUR_TOOL_MODE=0;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,38,0,1);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR00"),&YellowFont,&YellowFont,&YellowFont,0);
	CreateFlags(10,10);
};
//UNIT parameters
int TP_CurNation=0;
ComboBox* TP_GPB=NULL;
VScrollBar* TP_Scroll=NULL;
SimpleDialog* TP_STARTSCROLL;
SimpleDialog* TP_ENDSCROLL;
int TP_YPREV=0;
//----------------

bool TP_UNIT_CLICK(SimpleDialog* SD){
	ColoredBar* CB=(ColoredBar*)SD;
	byte CC=0x65;
	for(int i=0;i<512;i++)if(TOOL_PARAM.DSS[i]&&TOOL_PARAM.DSS[i]->UserParam>=10000){
		((ColoredBar*)TOOL_PARAM.DSS[i])->color=CC;
	};
	CB->color=0xFF;
	Creator=CB->UserParam-10000;
	return true;
};
void CreateTOOL_PARAM_UNIT(){
	CUR_TOOL_MODE=1;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,386,48+26,3);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR01"),&YellowFont,&YellowFont,&YellowFont,0);
	CreateFlags(10,10);
	TP_GPB=TOOL_PARAM.addGP_ComboBoxDLX(NULL,10,10+26,224,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	for(int i=0;i<NNations;i++)TP_GPB->AddLine(NatNames[i]);
	TP_GPB->CurLine=TP_CurNation;
	//Units list
	TP_Scroll=TOOL_PARAM.addNewGP_VScrollBar(NULL,InfDX-21,48+26+1,312,100,0,3,0);
	TP_Scroll->ScrDy=200;
	TP_Scroll->OnesDy=32;
	TOOL_PARAM.addClipper(TOOL_PARAM.BaseX+4,TOOL_PARAM.BaseY+48+26+1,RealLx,TOOL_PARAM.BaseY+311+48+26+1);
	TP_STARTSCROLL=NULL;
	int NUNITS=NATIONS->NUnits[TP_CurNation];
	int xx=0;
	int yy=48+26+6;
	byte CC=0x65;
	for(int j=0;j<NUNITS;j++){
		int UIDS=NATIONS->UnitsIDS[TP_CurNation][j];
		if(UIDS==0xFFFF){
			if(xx)yy+=44;
			TextButton* TB=TOOL_PARAM.addTextButton(NULL,10,yy,GetTextByID(NATIONS->UnitNames[TP_CurNation][j]),&YellowFont,&YellowFont,&YellowFont,0);
			if(!TP_STARTSCROLL)TP_STARTSCROLL=TB;
			yy+=20;
			xx=0;
		}else{
			GeneralObject* GO=NATIONS->Mon[UIDS];
			if(xx>4){
				xx=0;
				yy+=44;
			};
			if(GO->newMons->IconID>=0)TOOL_PARAM.addGPPicture(NULL,6+xx*44,yy,0,GO->newMons->IconID);
			ColoredBar* CB=TOOL_PARAM.addColoredBar(5+xx*44,yy-1,41,41,CC);
			CB->Style=1;
			CB->OnUserClick=&TP_UNIT_CLICK;
			CB->UserParam=10000+UIDS;
			CB->Hint=GO->Message;
			xx++;
		};
	};
	if(xx)yy+=44;
	TP_ENDSCROLL=TOOL_PARAM.addClipper(0,0,RealLx-1,RealLy-1);
	TP_YPREV=0;
	TP_Scroll->SMaxPos=yy-48-26-4-312+8;
	if(TP_Scroll->SMaxPos<0)TP_Scroll->Visible=0;
};
extern bool NoPress;
void ProcessTOOL_PARAM_UNIT(){
	if(TP_GPB){
		if(TP_GPB->CurLine!=TP_CurNation){
			TP_CurNation=TP_GPB->CurLine;
			CreateTOOL_PARAM_UNIT();
		};
		bool StartChange=0;
		int CURRPOS=TP_Scroll->SPos;
		for(int i=0;i<512;i++){
			SimpleDialog* SD=TOOL_PARAM.DSS[i];
			if(SD){
				if(SD==TP_STARTSCROLL)StartChange=1;
				if(SD==TP_ENDSCROLL)StartChange=0;
				if(StartChange){
					SD->y+=TP_YPREV-CURRPOS;
					SD->y1+=TP_YPREV-CURRPOS;
				};
			};
		};
		TP_YPREV=CURRPOS;
	};
};
//---------SPRITES---------
void GetRealGPSize(int File,int spr,int* dx,int* dy);
SprGroup* CURSG;
#define AC_COLOR 0xFF
#define PS_COLOR 0x5C
bool ON_SPRITE_CLICK(SimpleDialog* SD){
	ColoredBar* CB=(ColoredBar*)SD;
	if(GetKeyState(VK_CONTROL)&0x8000){
		if(CB->color==PS_COLOR)CB->color=AC_COLOR;
		else CB->color=PS_COLOR;
	}else{
		for(int i=0;i<512;i++)if(TOOL_PARAM.DSS[i]){
			if(TOOL_PARAM.DSS[i]->UserParam>=10000){
				((ColoredBar*)TOOL_PARAM.DSS[i])->color=PS_COLOR;
			};
		};
		CB->color=AC_COLOR;
	};
	NTreeItems=0;
	for(int i=0;i<512;i++)if(TOOL_PARAM.DSS[i]){
		if(TOOL_PARAM.DSS[i]->UserParam>=10000){
			if(((ColoredBar*)TOOL_PARAM.DSS[i])->color==AC_COLOR){
				TreeItems[NTreeItems]=TOOL_PARAM.DSS[i]->UserParam-10000;
				NTreeItems++;
			};
		};
	};
	if(NTreeItems){
		HeightEditMode=2;
		MEditMode=false;
		BlobMode=-1;
		if(CURSG==&TREES)InteriorType=0;
		if(CURSG==&STONES)InteriorType=1;
		if(CURSG==&HOLES)InteriorType=2;
	}else{
		ClearModes();
		HeightEditMode=false;
		BlobMode=-1;
		WaterEditMode=0;
		Creator=4096+255;
	};
	return true;
};
VScrollBar* TP_BRS;
int PrevRelBr=10;
void CreateTOOL_PARAM_SPRITE(byte ID){
	
	CUR_TOOL_MODE=2;
	ClearModes();
	BlobMode=-1;
	WaterEditMode=0;
	Creator=4096+255;
	HeightEditMode=2;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	int DL=24;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,386,48+DL,3);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR02"),&YellowFont,&YellowFont,&YellowFont,0);
	CreateFlags(10,10);

	int Y0=36;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,110,ReliefBrush,MapGP+1,4,195,12,0,0);

	
	//Units list
	TP_Scroll=TOOL_PARAM.addNewGP_VScrollBar(NULL,InfDX-21,48+1+DL,312+26-DL,100,0,3,0);
	TP_Scroll->ScrDy=200;
	TP_Scroll->OnesDy=32;
	TOOL_PARAM.addClipper(TOOL_PARAM.BaseX,TOOL_PARAM.BaseY+48+1+DL,RealLx,TOOL_PARAM.BaseY+311+48+26+1);
	if(ID==0)CURSG=&TREES;
	else if(ID==1)CURSG=&STONES;
	else CURSG=&HOLES;
	int xx=0;
	int yy=48+4+DL;
	int MaxLy=0;
	int Nx=0;
	int TotLx=0;
	int MaxLx=InfDX-25;
	TP_STARTSCROLL=NULL;
	for(int i=0;i<=CURSG->NSpr;i++){
		int Lx=GPS.GetGPWidth(CURSG->FileID,i);
		int Ly=GPS.GetGPHeight(CURSG->FileID,i);
		int dxx,dyy;
		GetRealGPSize(CURSG->FileID,i,&dxx,&dyy);
		Lx-=dxx;
		Ly-=dyy;

		if((Nx==0||TotLx+Lx<MaxLx)&&i<CURSG->NSpr){
			Nx++;
			TotLx+=Lx;
			if(Ly>MaxLy)MaxLy=Ly;
		}else{
			if(Nx)i--;
			int dx=MaxLx-TotLx;
			for(int j=i-Nx+1;j<=i;j++){
				int tdx0=((j-i+Nx-1)*dx)/Nx;
				int tdx1=((j-i+Nx)*dx)/Nx;
				int L1=tdx1-tdx0;
				Lx=GPS.GetGPWidth(CURSG->FileID,j);
				Ly=GPS.GetGPHeight(CURSG->FileID,j);
				int dxx,dyy;
				GetRealGPSize(CURSG->FileID,j,&dxx,&dyy);
				Lx-=dxx;
				Ly-=dyy;
				GPPicture* GPP=TOOL_PARAM.addGPPicture(NULL,xx+tdx0+L1/2-dxx,yy-dyy+(MaxLy-Ly)/2,CURSG->FileID,j);
				if(!TP_STARTSCROLL)TP_STARTSCROLL=GPP;
				ColoredBar* CB=TOOL_PARAM.addColoredBar(xx+tdx0,yy,L1+Lx-1,MaxLy-1,PS_COLOR);
				CB->OnUserClick=&ON_SPRITE_CLICK;
				CB->UserParam=j+10000;
				CB->Style=1;
				xx+=Lx;
			};
			xx=0;
			yy+=MaxLy;
			TotLx=0;
			MaxLy=0;
			Nx=0;
		};
	};
	TP_ENDSCROLL=TOOL_PARAM.addClipper(0,0,RealLx-1,RealLy-1);
	TP_YPREV=0;
	TP_Scroll->SMaxPos=yy-48-4-312+8-20;
	if(TP_Scroll->SMaxPos<0)TP_Scroll->Visible=0;
};
void ProcessTOOL_PARAM_SPRITES(){
	if(ReliefBrush!=PrevRelBr){
		PrevRelBr=ReliefBrush;
		TP_BRS->SPos=ReliefBrush;
	};
	ReliefBrush=TP_BRS->SPos;
	bool StartChange=0;
	int CURRPOS=TP_Scroll->SPos;
	for(int i=0;i<512;i++){
		SimpleDialog* SD=TOOL_PARAM.DSS[i];
		if(SD){
			if(SD==TP_STARTSCROLL)StartChange=1;
			if(SD==TP_ENDSCROLL)StartChange=0;
			if(StartChange){
				SD->y+=TP_YPREV-CURRPOS;
				SD->y1+=TP_YPREV-CURRPOS;
			};
		};
	};
	TP_YPREV=CURRPOS;
	StdWheel();
};

char HEIGHTSTR[12]="";

ComboBox* ED_CB0;
ComboBox* ED_CB1;
ComboBox* ED_CB2;
ComboBox* ED_CB3;

BPXView* ED_BV;
byte BT_COLOR=0x4E;
int CurrTexSet=0;

//Textures dialog
//void CreatePlus(DialogsSystem* DSS,int x,int y,VCall* UPR){
//	DSS->Add
//};

bool MINHI_CLICK(SimpleDialog* SD){
	TM_Height0+=SD->UserParam;
	return true;
};
bool MAXHI_CLICK(SimpleDialog* SD){
	TM_Height1+=SD->UserParam;
	return true;
};
bool MINANG_CLICK(SimpleDialog* SD){
	TM_Angle0+=SD->UserParam;
	return true;
};
bool MAXANG_CLICK(SimpleDialog* SD){
	TM_Angle1+=SD->UserParam;
	return true;
};
extern int  ReliefBrush;
void CreateTOOL_PARAM_TEXTURE(){
	char ccc[128];
	sprintf(ccc,"Data\\TEXSET%d.DAT",CurrTexSet);
	FILE* F=fopen(ccc,"r");
	if(F){
		int v;
		fscanf(F,"%d %d %d %d %d ",&TM_Height0,&TM_Height1,&TM_Angle0,&TM_Angle1,&v);
		NTextures=v;
		for(int i=0;i<NTextures;i++){
			fscanf(F,"%d",&v);
			TexList[i]=v;
		};
		fclose(F);
	};
	CUR_TOOL_MODE=3;
	ClearModes();
	HeightEditMode=false;
	BlobMode=-1;
	WaterEditMode=0;
	Creator=4096+255;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	int DLY=107+56;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,386,48+DLY,3);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR04"),&YellowFont,&YellowFont,&YellowFont,0);
	//CreateFlags(10,10);

	int Y0=4;
	int X0=5;
	int ODY=26;
	int maxx=0;
	char ccx[128];
	for(int i=0;i<5;i++){
		sprintf(ccx,"EDTP_0%d",i);
		int LX=GetRLCStrWidth(GetTextByID(ccx),&YellowFont);
		if(LX>maxx)maxx=LX;
	};
	maxx+=16;

	VScrollBar* VS;
	int CMLX=InfDX-20-maxx;

	TOOL_PARAM.addTextButton(NULL,X0,Y0,GetTextByID("EDTP_01"),&YellowFont,&YellowFont,&YellowFont,0);
	ED_CB0=TOOL_PARAM.addGP_ComboBoxDLX(NULL,X0+maxx,Y0,CMLX,CBB_GPFILE,0,9,0,&YellowFont,&WhiteFont,NULL);
	ED_CB0->CreateRuler(-200,1200);
	ED_CB0->AssignScroll(&TOOL_PARAM,&VS,3,0,10);
	ED_CB0->CurLine=TM_Height0+200;

	Y0+=ODY;
	TOOL_PARAM.addTextButton(NULL,X0,Y0,GetTextByID("EDTP_02"),&YellowFont,&YellowFont,&YellowFont,0);
	ED_CB1=TOOL_PARAM.addGP_ComboBoxDLX(NULL,X0+maxx,Y0,CMLX,CBB_GPFILE,0,9,0,&YellowFont,&WhiteFont,NULL);
	ED_CB1->CreateRuler(-200,1200);
	ED_CB1->AssignScroll(&TOOL_PARAM,&VS,3,0,10);
	ED_CB1->CurLine=TM_Height1+200;


	Y0+=ODY;
	TOOL_PARAM.addTextButton(NULL,X0,Y0,GetTextByID("EDTP_03"),&YellowFont,&YellowFont,&YellowFont,0);
	ED_CB2=TOOL_PARAM.addGP_ComboBoxDLX(NULL,X0+maxx,Y0,CMLX,CBB_GPFILE,0,9,0,&YellowFont,&WhiteFont,NULL);
	ED_CB2->CreateRuler(0,90);
	ED_CB2->AssignScroll(&TOOL_PARAM,&VS,3,0,12);
	ED_CB2->CurLine=TM_Angle0;

	Y0+=ODY;
	TOOL_PARAM.addTextButton(NULL,X0,Y0,GetTextByID("EDTP_04"),&YellowFont,&YellowFont,&YellowFont,0);
	ED_CB3=TOOL_PARAM.addGP_ComboBoxDLX(NULL,X0+maxx,Y0,CMLX,CBB_GPFILE,0,9,0,&YellowFont,&WhiteFont,NULL);
	ED_CB3->CreateRuler(0,90);
	ED_CB3->AssignScroll(&TOOL_PARAM,&VS,3,0,12);
	ED_CB3->CurLine=TM_Angle1;

	Y0+=ODY;
	TOOL_PARAM.addTextButton(NULL,X0,Y0,GetTextByID("EDTP_05"),&YellowFont,&YellowFont,&YellowFont,0);
	InputBox* IB=TOOL_PARAM.addInputBox(NULL,X0+maxx,Y0-5,HEIGHTSTR,20,150,20,&YellowFont,&YellowFont);
	IB->Enabled=0;
	Y0+=ODY;
	TP_GPB=TOOL_PARAM.addGP_ComboBoxDLX(NULL,0,Y0,InfDX-15,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	TP_GPB->CurLine=CurrTexSet;
	char* IDX=GetTextByID("EDTX_S0");
	
	for(i=0;i<10;i++){
		sprintf(ccx,IDX,i+1);
		TP_GPB->AddLine(ccx);
	};
	
	Y0+=ODY+10;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,110,ReliefBrush,MapGP+1,4,195,12,0,0);
	
	TP_Scroll=TOOL_PARAM.addNewGP_VScrollBar(NULL,InfDX-21,48+1+DLY,312+26-DLY,100,0,3,0);
	TP_Scroll->ScrDy=3;
	ED_BV=TOOL_PARAM.addBPXView(NULL,2,48+1+DLY+4,56,56,4,3,MaxTex>>2,tex1,TP_Scroll);
	ED_BV->DECLX=8;
	int N=ED_BV->Nx*ED_BV->RealNy;
	for(i=0;i<N;i++){
		ED_BV->Choosed[i]=0;
	};
	for(i=0;i<NTextures;i++){
		ED_BV->Choosed[TexList[i]]++;
	};

};

void ProcessTOOL_PARAM_TEXTURE(){
	if(ReliefBrush!=PrevRelBr){
		PrevRelBr=ReliefBrush;
		TP_BRS->SPos=ReliefBrush;
	};
	ReliefBrush=TP_BRS->SPos;
	if(TP_GPB->CurLine!=CurrTexSet){
		CurrTexSet=TP_GPB->CurLine;
		char ccc[128];
		sprintf(ccc,"Data\\TEXSET%d.DAT",CurrTexSet);
		FILE* F=fopen(ccc,"r");
		if(F){
			int v;
			fscanf(F,"%d %d %d %d %d ",&TM_Height0,&TM_Height1,&TM_Angle0,&TM_Angle1,&v);
			NTextures=v;
			for(int i=0;i<NTextures;i++){
				fscanf(F,"%d",&v);
				TexList[i]=v;
			};
			fclose(F);
			ED_CB0->CurLine=TM_Height0+200;
			ED_CB1->CurLine=TM_Height1+200;
			ED_CB2->CurLine=TM_Angle0;
			ED_CB3->CurLine=TM_Angle1;
			int N=ED_BV->Nx*ED_BV->RealNy;
			for(i=0;i<N;i++){
				ED_BV->Choosed[i]=0;
			};
			for(i=0;i<NTextures;i++){
				ED_BV->Choosed[TexList[i]]++;
			};
		};
	};
	bool Change=0;
	if(TM_Height0!=ED_CB0->CurLine+ED_CB0->MinDeal){
		TM_Height0=ED_CB0->CurLine+ED_CB0->MinDeal;
		Change=1;
	};
	if(TM_Height1!=ED_CB1->CurLine+ED_CB1->MinDeal){
		TM_Height1=ED_CB1->CurLine+ED_CB1->MinDeal;
		Change=1;
	};
	if(TM_Angle0!=ED_CB2->CurLine+ED_CB2->MinDeal){
		TM_Angle0=ED_CB2->CurLine+ED_CB2->MinDeal;
		Change=1;
	};
	if(TM_Angle1!=ED_CB3->CurLine+ED_CB3->MinDeal){
		TM_Angle1=ED_CB3->CurLine+ED_CB3->MinDeal;
		Change=1;
	};

	if(TM_Angle0!=90)TM_Tan0=int(tan(double(TM_Angle0)*3.1415/180)*256);else TM_Tan0=100000;
	if(TM_Angle1!=90)TM_Tan1=int(tan(double(TM_Angle1)*3.1415/180)*256);else TM_Tan1=100000;
	int ntx=0;
	int nn=ED_BV->Nx*ED_BV->RealNy;
	for(int i=0;i<nn;i++){
		if(ED_BV->Choosed[i]){
			for(int j=0;j<ED_BV->Choosed[i];j++){
			if(ntx<256){
					TexList[ntx]=i;
					ntx++;
				};
			};
		};
	};
	if(ntx!=NTextures)Change=1;
	if(ntx){
		NTextures=ntx;
		HeightEditMode=false;
		MEditMode=true;
		TexMapMod=true;
	}else{
		HeightEditMode=false;
		MEditMode=false;
		TexMapMod=false;
	};
	if(Change){
		char ccc[128];
		sprintf(ccc,"Data\\TEXSET%d.DAT",CurrTexSet);
		FILE* F=fopen(ccc,"w");
		if(F){
			fprintf(F,"%d %d %d %d %d ",TM_Height0,TM_Height1,TM_Angle0,TM_Angle1,NTextures);
			for(int i=0;i<NTextures;i++){
				fprintf(F,"%d ",TexList[i]);
			};
			fclose(F);
		};
	};
	StdWheel();
};
byte NeedToPopUp=0;
//------------------COPY PIECES------------------//
char** PIECES_NAMES=NULL;
int NPIECES=0;
int MAX_PIECES=0;
void AddPiece(char* str){
	if(NPIECES>=MAX_PIECES){
		MAX_PIECES+=256;
		PIECES_NAMES=(char**)realloc(PIECES_NAMES,MAX_PIECES<<2);
	};
	for(int i=0;i<NPIECES;i++){
		if(_stricmp(str,PIECES_NAMES[i])<0){
			if(i<NPIECES){
				for(int j=NPIECES-1;j>=i;j--)PIECES_NAMES[j+1]=PIECES_NAMES[j];
				PIECES_NAMES[i]=new char[strlen(str)+1];
				strcpy(PIECES_NAMES[i],str);
				NPIECES++;
				return;
			};
		};
	};
	PIECES_NAMES[NPIECES]=new char[strlen(str)+1];
	strcpy(PIECES_NAMES[NPIECES],str);
	NPIECES++;
};
void ClearPieces(){
	for(int i=0;i<NPIECES;i++)free(PIECES_NAMES[i]);
	if(PIECES_NAMES)free(PIECES_NAMES);
	PIECES_NAMES=NULL;
	NPIECES=0;
	MAX_PIECES=0;
};
void ReadAllPieces(){
	ClearPieces();
	WIN32_FIND_DATA FD;
	HANDLE H=FindFirstFile("UserPieces\\*.smp",&FD);
	if(H!=INVALID_HANDLE_VALUE){
		do{
			AddPiece(FD.cFileName);
		}while(FindNextFile(H,&FD));
		FindClose(H);
	};
};
ListBox* ED_PLIST;
extern int CurrPiece=-1;
void CreateTOOL_PARAM_PIECES(){
	CurrPiece=-1;
	CUR_TOOL_MODE=4;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,386,48+26,3);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR05"),&YellowFont,&YellowFont,&YellowFont,0);
	CreateFlags(10,10);
	TP_Scroll=TOOL_PARAM.addNewGP_VScrollBar(NULL,InfDX-21,48+26+1,312,100,0,3,0);
	TP_Scroll->ScrDy=20;
	ED_PLIST=TOOL_PARAM.addListBox(NULL,5,48+26+1,16,200,20,&WhiteFont,&YellowFont,TP_Scroll);
	ReadAllPieces();
	for(int i=0;i<NPIECES;i++){
		ED_PLIST->AddItem(PIECES_NAMES[i],i);
	};
	CurrPiece=-1;
	ED_PLIST->CurItem=-1;
};
void ProcessRM_LoadEx(int x,int y,char* Name);
void ProcessTOOL_PARAM_PIECES(){
	if(ED_PLIST->NItems){
		if(WheelDelta<0){
			ED_PLIST->SetCurrentItem(ED_PLIST->CurItem+1);
			//if(ED_PLIST->CurItem>=ED_PLIST->NItems)ED_PLIST->CurItem=ED_PLIST->NItems-1;
			if(ED_PLIST->CurItem>=ED_PLIST->FLItem+ED_PLIST->ny)ED_PLIST->FLItem=ED_PLIST->CurItem-ED_PLIST->ny+1;
			if(ED_PLIST->FLItem<0)ED_PLIST->FLItem=0;
			TP_Scroll->SPos=ED_PLIST->FLItem*32;
		};
		if(WheelDelta>0){
			ED_PLIST->SetCurrentItem(ED_PLIST->CurItem-1);
			//if(ED_PLIST->CurItem<0)ED_PLIST->CurItem=0;
			if(ED_PLIST->CurItem<=ED_PLIST->FLItem)ED_PLIST->FLItem=ED_PLIST->CurItem;
			TP_Scroll->SPos=ED_PLIST->FLItem*32;
		};
		WheelDelta=0;
	};
	if(CurrPiece!=ED_PLIST->CurItem){
		CurrPiece=ED_PLIST->CurItem;
		ProcessRM_LoadEx((mapx<<5)+(RealLx>>1)-100,(mapy<<5)+(RealLy),(ED_PLIST->GetItem(CurrPiece))->Message);
	};
};
//-----------------------WATER EDITOR---------------------//
VScrollBar* TP_BRS1;
VScrollBar* TP_BRS2;
extern int CostThickness;
void CreateTOOL_PARAM_WATER(){
	
	CUR_TOOL_MODE=5;
	ClearModes();
	BlobMode=-1;
	WaterEditMode=0;
	Creator=4096+255;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	int DL=24;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,150,0,1);
	TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR06"),&YellowFont,&YellowFont,&YellowFont,0);
	CreateFlags(10,10);

	int Y0=36;
	TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM01"),&YellowFont,&YellowFont,&YellowFont,0);
	Y0+=24;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,110,ReliefBrush,MapGP+1,4,195,12,0,0);
	Y0+=26;
	TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM02"),&YellowFont,&YellowFont,&YellowFont,0);
	Y0+=24;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS2=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,25,CostThickness,MapGP+1,4,195,12,0,0);
	Y0+=26;
};
int PrevCostW=-1;
void ProcessTOOL_PARAM_WATER(){
	StdWheel();
	if(ReliefBrush!=PrevRelBr){
		PrevRelBr=ReliefBrush;
		TP_BRS->SPos=ReliefBrush;
	};
	ReliefBrush=TP_BRS->SPos;
	if(CostThickness!=PrevCostW){
		PrevCostW=CostThickness;
		TP_BRS2->SPos=CostThickness;
	};
	CostThickness=TP_BRS2->SPos;
};
void CreateTOOL_PARAM_BRIGHTNESS(byte type){
	
	CUR_TOOL_MODE=6;
	ClearModes();
	BlobMode=-1;
	WaterEditMode=0;
	Creator=4096+255;
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	int DL=24;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,95,0,1);
	int Y0=36;
	if(type){
		TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR08"),&YellowFont,&YellowFont,&YellowFont,0);
		TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM04"),&YellowFont,&YellowFont,&YellowFont,0);
	}else{
		TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR07"),&YellowFont,&YellowFont,&YellowFont,0);
		TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM03"),&YellowFont,&YellowFont,&YellowFont,0);
	};
	CreateFlags(10,10);
	Y0+=24;
	if(ReliefBrush>20)ReliefBrush=20;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,20,ReliefBrush,MapGP+1,4,195,12,0,0);
	Y0+=26;
};
void ProcessTOOL_PARAM_BRIGHTNESS(){
	StdWheel();
	if(ReliefBrush>20)ReliefBrush=20;
	if(ReliefBrush!=PrevRelBr){
		PrevRelBr=ReliefBrush;
		TP_BRS->SPos=ReliefBrush;
	};
	ReliefBrush=TP_BRS->SPos;
};
void CreateTOOL_PARAM_RELIEF(byte type){
	
	CUR_TOOL_MODE=7;
	if(!type){
		ClearModes();
		BlobMode=-1;
		WaterEditMode=0;
		Creator=4096+255;
	};
	int DY=16+UNI_LINEDLY1;
	int DDY=UNI_LINEDY1;
	
	TOOL_PARAM.CloseDialogs();
	int DD1=75;
	int D=18;
	int x0=RealLx-InfDX;
	int y0=InfDY;
	TOOL_PARAM.HintFont=&SmallBlackFont;
	TOOL_PARAM.HintX=-1;
	TOOL_PARAM.HintY=450;
	TOOL_PARAM.BaseX=x0-1;
	TOOL_PARAM.BaseY=y0+31;
	int DL=24;
	TOOL_PARAM.addBorder(0,-31,InfDX-10,95,0,1);
	int Y0=36;
	if(type){
		TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR09"),&YellowFont,&YellowFont,&YellowFont,0);
		TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM01"),&YellowFont,&YellowFont,&YellowFont,0);
	}else{
		TOOL_PARAM.addTextButton(NULL,10,-24,GetTextByID("ED_HDR03"),&YellowFont,&YellowFont,&YellowFont,0);
		TOOL_PARAM.addTextButton(NULL,5,Y0,GetTextByID("ED_PARM01"),&YellowFont,&YellowFont,&YellowFont,0);
	};
	CreateFlags(10,10);
	Y0+=24;
	TOOL_PARAM.addGP_Button(NULL,10,Y0,MapGP+1,0,0);
	TOOL_PARAM.addGP_Button(NULL,10+34,Y0,MapGP+1,3,2);
	TP_BRS=TOOL_PARAM.addGP_ScrollBarL(NULL,10+34,Y0+12,110,ReliefBrush,MapGP+1,4,195,12,0,0);
	Y0+=26;
};
void ProcessTOOL_PARAM_RELIEF(){
	StdWheel();
	if(ReliefBrush!=PrevRelBr){
		PrevRelBr=ReliefBrush;
		TP_BRS->SPos=ReliefBrush;
	};
	ReliefBrush=TP_BRS->SPos;
};
int PrevScrLx=1024;
void ProcessTOOL_PARAM(){
	if(NoPress&&mouseX>RealLx-InfDX-32)return;
	if(TP_Made&&PrevScrLx!=RealLx){
		TP_Made=0;
	};
	PrevScrLx=RealLx;
	if(NeedToPopUp){
		Inform=0;
		OptHidden=0;
		ClearModes();
		HeightEditMode=false;
		BlobMode=-1;
		WaterEditMode=0;
		Creator=4096+255;
		switch(NeedToPopUp){
		case 1://default
			CreateTOOL_PARAM_DEFAULT();
			PressCurrentEdModeButton(0);
			break;
        case 2://units
			CreateTOOL_PARAM_UNIT();
			PressCurrentEdModeButton(19);
			break;
		case 3://trees
			CreateTOOL_PARAM_SPRITE(0);
			PressCurrentEdModeButton(2);
			break;
		case 4://stones
			CreateTOOL_PARAM_SPRITE(1);
			PressCurrentEdModeButton(3);
			break;
		case 5://holes???
			CreateTOOL_PARAM_SPRITE(2);
			PressCurrentEdModeButton(3);
			break;
		case 6://texture
			CreateTOOL_PARAM_TEXTURE();
			PressCurrentEdModeButton(1);
			break;
		case 7://erase sprites
			CreateTOOL_PARAM_RELIEF(1);
			PressCurrentEdModeButton(4);
			HeightEditMode=3;
			MEditMode=false;
			EditMedia=5;
			break;
		case 8://Set water
			CreateTOOL_PARAM_WATER();
			PressCurrentEdModeButton(6);
			WaterEditMode=1;
			break;
		case 9://clear water
			CreateTOOL_PARAM_WATER();
			PressCurrentEdModeButton(7);
			WaterEditMode=2;
			break;
		case 10://Set brightness
			CreateTOOL_PARAM_BRIGHTNESS(0);
			PressCurrentEdModeButton(8);
			WaterEditMode=3;
			break;
		case 11://clear brightness
			CreateTOOL_PARAM_BRIGHTNESS(1);
			PressCurrentEdModeButton(9);
			WaterEditMode=4;
			break;
		case 12://unlock mode
			CreateTOOL_PARAM_DEFAULT();
			PressCurrentEdModeButton(16);
			LockMode=1;
			break;
		case 13://lock mode
			CreateTOOL_PARAM_DEFAULT();
			PressCurrentEdModeButton(17);
			LockMode=2;
			break;
		case 14://default lock mode
			CreateTOOL_PARAM_DEFAULT();
			PressCurrentEdModeButton(18);
			LockMode=3;
			break;
		case 15://edit height (1) hill
			CreateTOOL_PARAM_RELIEF(0);
			HeightEditMode=1;
			HiStyle=0;
			break;
		case 16://edit height (2) plane
			CreateTOOL_PARAM_RELIEF(0);
			HeightEditMode=10;
			HiStyle=0;
			break;
		case 17://edit height (3) equ
			CreateTOOL_PARAM_RELIEF(0);
			HeightEditMode=11;
			HiStyle=0;
			break;
		case 18://edit height (4) soft
			CreateTOOL_PARAM_RELIEF(0);
			HeightEditMode=12;
			HiStyle=0;
			break;
		case 19://edit height (5) line
			CreateTOOL_PARAM_DEFAULT();
			HeightEditMode=13;
			HiStyle=0;
			break;
		case 20:
			CreateTOOL_PARAM_PIECES();
			PressCurrentEdModeButton(15);
			break;
		};
		NeedToPopUp=0;
	};
	if(!TP_Made){
		TP_GPB=NULL;
		switch(CUR_TOOL_MODE){
		case 0:
			CreateTOOL_PARAM_DEFAULT();
			break;
        case 1:
			CreateTOOL_PARAM_UNIT();
			break;
		case 2:
			CreateTOOL_PARAM_SPRITE(0);
			break;
		case 3:
			CreateTOOL_PARAM_TEXTURE();
			break;
		case 4:
			CreateTOOL_PARAM_PIECES();
			break;
		case 5:
			CreateTOOL_PARAM_WATER();
			break;
		case 6:
			CreateTOOL_PARAM_BRIGHTNESS(0);
			break;
		case 7:
			CreateTOOL_PARAM_RELIEF(0);
			break;
		};
		TP_Made=1;
	};
	if(!OptHidden)TOOL_PARAM.ProcessDialogs();
	//ProcessTOOL_PARAM_UNIT();
	switch(CUR_TOOL_MODE){
	case 1:
		ProcessTOOL_PARAM_UNIT();
		break;
	case 2:
		ProcessTOOL_PARAM_SPRITES();
		break;
	case 3:
		ProcessTOOL_PARAM_TEXTURE();
		break;
	case 4:
		ProcessTOOL_PARAM_PIECES();
		break;
	case 5:
		ProcessTOOL_PARAM_WATER();
		break;
	case 6:
		ProcessTOOL_PARAM_BRIGHTNESS();
		break;
	case 7:
		ProcessTOOL_PARAM_RELIEF();
		break;
	};
	if(!OptHidden){
		if(mouseY<TOOL_PARAM.BaseY+394&&mouseX>RealLx-InfDX-7)ClearUnderDialog(&TOOL_PARAM);
	};
};
#define PenLX 60
#define Pen2 30
#define PenLY 60
void ClearPen(byte* BUF){
	memset(BUF,0,PenLX*PenLY);
};
void DrawTreePen(byte* BUF,int v1,int v2){
	ClearPen(BUF);
	int r=(Pen2*v1)>>10;
	int N=v2;
	BUF[30+30*PenLX]=0x9A;
	for(int i=0;i<N;i++){
		int x=(int(randoma[i+i])%PenLX)-Pen2;
		int y=int(randoma[i+i+1])%PenLY-Pen2;
		int rr=sqrt(x*x+y*y);
		if(rr<r)BUF[x+30+(y+30)*PenLX]=0x9A;
	};
};
void DrawPenCircle(byte* BUF,int r,byte c){
	ClearPen(BUF);
	int r2=r*r+r;
	for(int i=0;i<=r;i++){
		int v=sqrt(r2-i*i);
		memset(BUF+(Pen2-i)*PenLX+Pen2-v,c,v+v);
		memset(BUF+(Pen2+i)*PenLX+Pen2-v,c,v+v);
	};
};
void DrawWaterPen(byte* BUF,int v1){
	int r=(Pen2*v1)>>10;
	DrawPenCircle(BUF,r,0xB4);
};
void DrawHillPen(byte* BUF,int v1){
	int r=(Pen2*v1)>>10;
	DrawPenCircle(BUF,r,0x78);
};
void DrawSoftPen(byte* BUF,int v1){
	int r=(Pen2*v1)>>10;
	DrawPenCircle(BUF,r,0xA7);
};
double GetPenH(int x,int y,int r,int v);
void DrawHeightPen(byte* BUF,int v1,int v2){
	ClearPen(BUF);
	int r0=(Pen2*v1)>>10;
	if(r0<1)r0=1;
	int pos=0;
	for(int ix=0;ix<PenLX;ix++){
		for(int iy=0;iy<PenLY;iy++){
			BUF[pos]=0x60+byte(GetPenH(ix-Pen2,iy-Pen2,r0,v2)*15);
			pos++;
		};
	};
};
#define TERRSH 8
byte* TerrHI;
byte* SoftArea;
byte* TerrMap;
byte* ResultMap;
extern byte trans8[65536];
void RenderToResult(int x0,int y0,int x1,int y1){
	for(int iy=y0;iy<=y1;iy++){
		int ofs=(iy<<TERRSH)+x0;
		for(int ix=x0;ix<=x1;ix++){
			byte b=TerrMap[ofs];
			if(b==255)b=0x60+(TerrHI[ofs]>>4);
			if(SoftArea[ofs])b=trans8[b+0xA700];
			ResultMap[ofs]=b;
			ofs++;
		};
	};
};
struct UndoChunk{
	byte* UndoData;
	int Size;
	int MaxSize;
};
class PixUndo{
public:
	UndoChunk* Chunks;
	int NChunks;
	PixUndo();
	~PixUndo();
	void AddUndoData(byte Type,byte x,byte y,byte color);
	void OpenNewChunk();
	void PerformUndo();
	void Clear();
};
void PixUndo::Clear(){
	for(int i=0;i<NChunks;i++){
		if(Chunks[i].UndoData)free(Chunks[i].UndoData);
	};
	if(NChunks)free(Chunks);
	Chunks=NULL;
	NChunks=0;
};

PixUndo::PixUndo(){
	NChunks=0;
	Chunks=NULL;
};
PixUndo::~PixUndo(){
	Clear();
};
void PixUndo::OpenNewChunk(){
	if((!NChunks)||Chunks[NChunks-1].Size){
		Chunks=(UndoChunk*)realloc(Chunks,(NChunks+1)*sizeof UndoChunk);
		Chunks[NChunks].Size=0;
		Chunks[NChunks].MaxSize=0;
		Chunks[NChunks].UndoData=NULL;
		NChunks++;
	};
};
void PixUndo::AddUndoData(byte Type,byte x,byte y,byte color){
	if(NChunks){
		if(Chunks[NChunks-1].Size+5>Chunks[NChunks-1].MaxSize){
			Chunks[NChunks-1].MaxSize+=512;
			Chunks[NChunks-1].UndoData=(byte*)realloc(Chunks[NChunks-1].UndoData,Chunks[NChunks-1].MaxSize);
		};
		byte* data=Chunks[NChunks-1].UndoData+Chunks[NChunks-1].Size;
		Chunks[NChunks-1].Size+=4;
		data[3]=Type;
		data[0]=x;
		data[1]=y;
		data[2]=color;
	};
};
void PixUndo::PerformUndo(){
	if(NChunks){
		byte* data=Chunks[NChunks-1].UndoData;
		int sz=Chunks[NChunks-1].Size;
		int sz0=sz;
		while(sz>0){
			switch(data[sz-1]){
			case 0:
				TerrHI[(int(data[sz-3])<<8)+data[sz-4]]=data[sz-2];
				sz-=4;
				break;
			case 1:
				SoftArea[(int(data[sz-3])<<8)+data[sz-4]]=data[sz-2];
				sz-=4;
				break;
			case 2:
				TerrMap[(int(data[sz-3])<<8)+data[sz-4]]=data[sz-2];
				sz-=4;
				break;
			};
		};
		Chunks[NChunks-1].Size=0;
		Chunks[NChunks-1].MaxSize=0;
		free(Chunks[NChunks-1].UndoData);
		Chunks[NChunks-1].UndoData=NULL;
		NChunks--;
		if(!sz0)PerformUndo();
	};
};
PixUndo* CURRUNDO;
void PutTerrPixel(byte Map,int x,int y,byte c){
	if(x<0||x>255||y<0||y>255)return;
	int ofs=x+(y<<TERRSH);
	switch(Map){
	case 0:
		if(TerrHI[ofs]!=c){
			CURRUNDO->AddUndoData(0,x,y,TerrHI[ofs]);
			TerrHI[ofs]=c;
		};
		break;
	case 1:
		if(SoftArea[ofs]!=c){
			CURRUNDO->AddUndoData(1,x,y,SoftArea[ofs]);
			SoftArea[ofs]=c;
		};
		break;
	case 2:
		if(TerrMap[ofs]!=c){
			CURRUNDO->AddUndoData(2,x,y,TerrMap[ofs]);
			TerrMap[ofs]=c;
		};
		break;
	};
};
extern bool realRpressed;
void DrawTerrCircle(byte Type,int x,int y,int r,byte c);
void TerrDrawTrees(int x,int y,int v1,int v2){
	if(realRpressed){
		DrawTerrCircle(2,x,y,(Pen2*v1)>>10,0);
		return;
	};
	int r=(Pen2*v1)>>10;
	int N=v2;
	PutTerrPixel(2,x,y,0x9A);
	for(int i=0;i<N;i++){
		int xx=(int(randoma[i+i])%PenLX)-Pen2;
		int yy=int(randoma[i+i+1])%PenLY-Pen2;
		int rr=sqrt(xx*xx+yy*yy);
		if(rr<r)PutTerrPixel(2,x+xx,y+yy,0x9A);
	};
};
void DrawTerrCircle(byte Type,int x,int y,int r,byte c){
	int r2=r*r+r;
	for(int i=0;i<=r;i++){
		int v=sqrt(r2-i*i);
		for(int j=-v;j<=v;j++){
			PutTerrPixel(Type,x+j,y-i,c);
			PutTerrPixel(Type,x+j,y+i,c);
		};
	};
};
void TerrDrawHills(int x,int y,int v1){
	if(realRpressed)DrawTerrCircle(2,x,y,(Pen2*v1)>>10,0);
	else DrawTerrCircle(2,x,y,(Pen2*v1)>>10,0xFF);
};
void TerrDrawWater(int x,int y,int v1){
	if(realRpressed)DrawTerrCircle(2,x,y,(Pen2*v1)>>10,0);
	else DrawTerrCircle(2,x,y,(Pen2*v1)>>10,0xB4);
};
void TerrDrawSoft(int x,int y,int v1){
	if(realRpressed)DrawTerrCircle(1,x,y,(Pen2*v1)>>10,0);
	else DrawTerrCircle(1,x,y,(Pen2*v1)>>10,0xFF);
};
double GetPenH(int x,int y,int r,int v){
	int rr=sqrt(x*x+y*y);
	if(rr>r)return 0;
	if(!r)return 255;
	double D=double(rr)/double(r);
	return 1.0-exp((double(v)/128.0+1)*log(D));
};
void TerrDrawHi(int x,int y,int v1,int v2){
	int r=(Pen2*v1)>>10;
	double DD=double(GetTickCount()%10)/10.0;
	for(int ix=-r;ix<r;ix++){
		for(int iy=-r;iy<r;iy++){
			int xx=x+ix;
			int yy=y+iy;
			if(xx>=0&&yy>=0&&xx<256&&yy<256){
				double DH=GetPenH(ix,iy,r,v2);
				int DY=int(DH*5.0+DD);
				int ofs=xx+(yy<<TERRSH);
				int v=TerrHI[ofs];
				if(realRpressed)v-=DY;
				else v+=DY;
				if(v<0)v=0;
				if(v>255)v=255;
				PutTerrPixel(0,xx,yy,v);
			};
		};
	};
};
void SaveHData(char* Name,byte* data){
	ResFile F=RRewrite(Name);
	if(F!=INVALID_HANDLE_VALUE){
		RBlockWrite(F,data,65535);
		RClose(F);
	};
};
void LoadHData(char* Name,byte* data){
	ResFile F=RReset(Name);
	if(F!=INVALID_HANDLE_VALUE){
		RBlockRead(F,data,65535);
		RClose(F);
	};
};
void SetupTerr(){
	TerrHI=new byte[65536];
	SoftArea=new byte[65536];
	TerrMap=new byte[65536];
	ResultMap=new byte[65536];
	memset(TerrHI,0xFF,65536);
	memset(SoftArea,0,65536);
	memset(TerrMap,0,65536);
	memset(ResultMap,0,65536);
	LoadHData("Data\\TerrHI.dat",TerrHI);
	LoadHData("Data\\SoftArea.dat",SoftArea);
	LoadHData("Data\\TerrMap.dat",TerrMap);
	RenderToResult(0,0,255,255);
};
void FreeTerr(){
	SaveHData("Data\\TerrHI.dat",TerrHI);
	SaveHData("Data\\SoftArea.dat",SoftArea);
	SaveHData("Data\\TerrMap.dat",TerrMap);
	free(TerrHI);
	free(SoftArea);
	free(TerrMap);
	free(ResultMap);
};
void DrawCircle(int x,int y,int r,byte c){
	char* xi=Rarr[r].xi;
	char* yi=Rarr[r].yi;
	int N=Rarr[r].N;
	for(int i=0;i<N;i++)Hline(x+xi[i],y+yi[i],x+xi[i],c);
};
//-------------------TERRAIN EDITOR----------------//
void PushScreen(byte** Ptr){
	*Ptr=new byte[ScrWidth*RealLy];
	memcpy(*Ptr,ScreenPtr,ScrWidth*RealLy);
};
void PopScreen(byte* Ptr){
	memcpy(ScreenPtr,Ptr,ScrWidth*RealLy);
	free(Ptr);
};

void SaveToBMP24(char* Name,int Lx,int Ly,byte* data);
void SaveTerrainBitmap(char* Name){
	byte* TMP24=new byte [256*(256+1)*3*3];
	byte* DATA24=TMP24;
	int ofs3=0;
	for(int i=0;i<65536;i++){
		byte v=TerrMap[i];
		if(v==0x9A){//tree
			DATA24[ofs3]=0;
			DATA24[ofs3+1]=255;
			DATA24[ofs3+2]=0;
		}else if(v==0xFF){//hills
			DATA24[ofs3]=0xFF;
			DATA24[ofs3+1]=0xFF;
			DATA24[ofs3+2]=0xFF;
		}else if(v==0xB4){//water
			DATA24[ofs3]=0xFF;
			DATA24[ofs3+1]=0;
			DATA24[ofs3+2]=0;
		}else{
			DATA24[ofs3]=0;
			DATA24[ofs3+1]=0;
			DATA24[ofs3+2]=0;
		};
		ofs3+=3;
	};
	DATA24+=65536*3;
	for(i=0;i<768;i++){
		if((i&3)==1)DATA24[0]=0xFF;
		else DATA24[0]=0;
		DATA24++;
	};
	ofs3=0;
	for(i=0;i<65536;i++){
		byte v=TerrHI[i];
		DATA24[ofs3]=v;
		DATA24[ofs3+1]=v;
		DATA24[ofs3+2]=v;
		ofs3+=3;
	};
	DATA24+=65536*3;
	for(i=0;i<768;i++){
		if((i&3)==1)DATA24[0]=0xFF;
		else DATA24[0]=0;
		DATA24++;
	};
	ofs3=0;
	for(i=0;i<65536;i++){
		byte v=SoftArea[i];
		if(v){
			DATA24[ofs3]=0;
			DATA24[ofs3+1]=0;
			DATA24[ofs3+2]=0xFF;
		}else{
			DATA24[ofs3]=0;
			DATA24[ofs3+1]=0;
			DATA24[ofs3+2]=0;
		};
		ofs3+=3;
	};
	DATA24+=65536*3;
	for(i=0;i<768;i++){
		if((i&3)==1)DATA24[0]=0xFF;
		else DATA24[0]=0;
		DATA24++;
	};
	SaveToBMP24(Name,256,256*3+3,TMP24);
	free(TMP24);
};
bool LoadTerrainBitmap(char* Name){
	byte* TMP24;
	BMPformat BM;
	if(ReadBMP24(Name,&BM,&TMP24)){
		if(BM.biWidth!=256||BM.biHeight!=256*3+3){
			free(TMP24);
			return false;
		};
		byte* DATA24=TMP24;
		int ofs3=0;
		for(int i=0;i<65536;i++){
			int B=DATA24[ofs3  ];
			int G=DATA24[ofs3+1];
			int R=DATA24[ofs3+2];
			byte v=0;
			if(G>(B+R)*2)v=0x9A;
			else if(B>200&&G>200&&R>200)v=0xFF;
			else if(B>(G+R)*2)v=0xB4;
			TerrMap[i]=v;
			ofs3+=3;
		};
		DATA24+=65536*3+256*3;
		ofs3=0;
		for(i=0;i<65536;i++){
			TerrHI[i]=DATA24[ofs3+1];
			ofs3+=3;
		};
		DATA24+=65536*3+256*3;
		ofs3=0;
		for(i=0;i<65536;i++){
			if(DATA24[ofs3+2]>=128)SoftArea[i]=0xFF;
			else SoftArea[i]=0;
			ofs3+=3;
		};
		free(TMP24);
		return true;
	}else return false;
};
void WaitWithError(char* ID,int GPID);
void ProcessLoadBitmap(){
	byte* p;
	PushScreen(&p);
	LocalGP BOR2("Interface\\Bor2");
	char BMPS[128];
	if(ProcessLoadingFile("UserTerrain\\*.bmp",BMPS,3)){
		char ccc[128];
		sprintf(ccc,"UserTerrain\\%s",BMPS);
		if(!LoadTerrainBitmap(ccc)){
			WaitWithError("INCRBMFORM",BOR2.GPID);
		};
	};
	RenderToResult(0,0,255,255);
	PopScreen(p);
	CURRUNDO->Clear();
	ItemChoose=-1;
};
void ProcessSaveBitmap(){
	byte* p;
	PushScreen(&p);
	char BMPS[128];
	if(ProcessSavingFile("UserTerrain\\*.bmp",BMPS,6,1)){
		char ccc[128];
		_strupr(BMPS);
		if(!strstr(BMPS,".BMP"))strcat(BMPS,".BMP");
		sprintf(ccc,"UserTerrain\\%s",BMPS);
		SaveTerrainBitmap(ccc);
	};
	RenderToResult(0,0,255,255);
	PopScreen(p);
	ItemChoose=-1;
};
void GenerateMapForMission(char* Relief,char* Ground,char* Mount,char* Soft);
void ProcessTerrainEditor(){
	PixUndo PUNDO;
	CURRUNDO=&PUNDO;
	SetupTerr();
	byte PenBuf[PenLX*PenLY];
	LocalGP BTNS("Interface\\EditTerra");
	DialogsSystem DSS((RealLx-524)>>1,(RealLy-400)>>1);
	DSS.HintX=-1;
	DSS.HintY=180;
	DSS.HintFont=&SmallBlackFont;
	byte* BACK=new byte[640*400];
	MemScreenPart(DSS.BaseX,DSS.BaseY,640,400,BACK);
	//GPS.ShowGP((RealLx-524)>>1,(RealLy-400)>>1,BTNS.GPID,1,0);
	DSS.addBPXView(NULL,0,0,640,400,1,1,1,BACK,NULL);
	DSS.addGPPicture(NULL,0,0,BTNS.GPID,0);
	DSS.addGPPicture(NULL,0,0,BTNS.GPID,1);
	GP_Button* OkBtn=DSS.addGP_Button(NULL,79,356,BTNS.GPID,5,4);
	OkBtn->UserParam=mcmOk;
	OkBtn->OnUserClick=&MMItemChoose;
	GP_Button* CancelBtn=DSS.addGP_Button(NULL,300,356,BTNS.GPID,3,2);
	CancelBtn->UserParam=mcmCancel;
	CancelBtn->OnUserClick=&MMItemChoose;
	GP_Button* Load=DSS.addGP_Button(NULL,301,260,BTNS.GPID,7,6);
	Load->UserParam=1;
	Load->OnUserClick=&MMItemChoose;
	GP_Button* Save=DSS.addGP_Button(NULL,301,291,BTNS.GPID,9,8);
	Save->UserParam=2;
	Save->OnUserClick=&MMItemChoose;
	CheckBox* TREES =DSS.addGP_CheckBox(NULL,301,58,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,10,11,12);
	TREES->Hint=GetTextByID("$TE_HN1");
	CheckBox* WATER =DSS.addGP_CheckBox(NULL,333,58,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,13,14,15);
	WATER->Hint=GetTextByID("$TE_HN2");
	CheckBox* HILLS =DSS.addGP_CheckBox(NULL,365,58,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,16,17,18);
	HILLS->Hint=GetTextByID("$TE_HN3");
	CheckBox* SOFT  =DSS.addGP_CheckBox(NULL,397,58,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,19,20,21);
	SOFT->Hint=GetTextByID("$TE_HN4");
	CheckBox* HEIGHT=DSS.addGP_CheckBox(NULL,429,58,"",&YellowFont,&YellowFont,1,0,BTNS.GPID,22,23,24);
	HEIGHT->Hint=GetTextByID("$TE_HN5");
	GP_Button* UNDO  =DSS.addGP_Button(NULL,467,58,BTNS.GPID,27,26);
	UNDO->Hint=GetTextByID("$TE_HN6");
	UNDO->UserParam=3;
	UNDO->OnUserClick=&MMItemChoose;
	VScrollBar* HB1=DSS.addGP_ScrollBarL(NULL,301,116+8,1024,64,MapGP+1,4,195,12,0,0);
	VScrollBar* HB2=DSS.addGP_ScrollBarL(NULL,301,162+7,1024,64,MapGP+1,4,195,12,0,0);
	DSS.addBPXView(NULL,302,190,60,60,1,1,1,PenBuf,NULL);
	ItemChoose=-1;
	int CurPen=-1;
	ClearPen(PenBuf);
	BPXView* VIEW=DSS.addBPXView(NULL,31,59,256,256,1,1,1,ResultMap,NULL);
	int spp1=-1;
	int spp2=-1;
	int pcp=-1;
	do{
		if(!(realLpressed||realRpressed))PUNDO.OpenNewChunk();
		ProcessMessages();
		if(KeyPressed&&LastKey=='Z'){
			PUNDO.PerformUndo();
			RenderToResult(0,0,255,255);
			LastKey=0;
			KeyPressed=0;
		};
		DSS.ProcessDialogs();
		if(VIEW->MouseOver){
			TempWindow TW;
			PushWindow(&TW);
			IntersectWindows(VIEW->x,VIEW->y,VIEW->x1,VIEW->y1);
			DrawCircle(mouseX,mouseY,(HB1->SPos*30)>>10,0xFF);
			PopWindow(&TW);
		};
		DSS.RefreshView();
		if(TREES->State)CurPen=0;
		if(WATER->State)CurPen=1;
		if(HILLS->State)CurPen=2;
		if(SOFT->State)CurPen=3;
		if(HEIGHT->State)CurPen=4;
		//DrawTreePen(PenBuf,HB1->SPos,HB2->SPos);
		//DrawWaterPen(PenBuf,HB1->SPos);
		if(spp1!=HB1->SPos||spp2!=HB2->SPos||pcp!=CurPen){
			spp1=HB1->SPos;
			spp2=HB2->SPos;
			pcp=CurPen;
			switch(CurPen){
			case 0:
				DrawTreePen(PenBuf,HB1->SPos,HB2->SPos);
				break;
			case 1:
				DrawWaterPen(PenBuf,HB1->SPos);
				break;
			case 2:
				DrawHillPen(PenBuf,HB1->SPos);
				break;	
			case 3:
				DrawSoftPen(PenBuf,HB1->SPos);
				break;
			case 4:
				DrawHeightPen(PenBuf,HB1->SPos,HB2->SPos);
				break;
			};
		};
		if((realLpressed||realRpressed)&&VIEW->MouseOver){
			int x=mouseX-VIEW->x;
			int y=mouseY-VIEW->y;
			switch(CurPen){
			case 0:
				TerrDrawTrees(x,y,HB1->SPos,HB2->SPos);
				break;
			case 1:
				TerrDrawWater(x,y,HB1->SPos);
				break;
			case 2:
				TerrDrawHills(x,y,HB1->SPos);
				break;
			case 3:
				TerrDrawSoft(x,y,HB1->SPos);
				break;
			case 4:
				TerrDrawHi(x,y,HB1->SPos,HB2->SPos);
				//DrawHeightPen(PenBuf,HB1->SPos,HB2->SPos);
				break;
			};
			RenderToResult(0,0,255,255);
		};
		HB1->SPos+=WheelDelta/4;
		if(HB1->SPos<0)HB1->SPos=0;
		if(HB1->SPos>HB1->SMaxPos)HB1->SPos=HB1->SMaxPos;
		WheelDelta=0;
		if(ItemChoose==1){
			ProcessLoadBitmap();
			ItemChoose=-1;
		};
		if(ItemChoose==2){
			ProcessSaveBitmap();
			ItemChoose=-1;
		};
		if(ItemChoose==3){
			PUNDO.PerformUndo();
			RenderToResult(0,0,255,255);
			LastKey=0;
			KeyPressed=0;
			ItemChoose=-1;
		};

	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		//generating
		byte* DATA24=new byte[65536*3];
		int ofs3=0;
		for(int i=0;i<65536;i++){
			byte v=TerrMap[i];
			if(v==0x9A){//tree
				DATA24[ofs3]=0;
				DATA24[ofs3+1]=255;
				DATA24[ofs3+2]=0;
			}else if(v==0xFF){//hills
				DATA24[ofs3]=0xFF;
				DATA24[ofs3+1]=0xFF;
				DATA24[ofs3+2]=0xFF;
			}else if(v==0xB4){//water
				DATA24[ofs3]=0xFF;
				DATA24[ofs3+1]=0;
				DATA24[ofs3+2]=0;
			}else{
				DATA24[ofs3]=0;
				DATA24[ofs3+1]=0;
				DATA24[ofs3+2]=0;
			};
			ofs3+=3;
		};
		SaveToBMP24("Data\\01.bmp",256,256,DATA24);
		ofs3=0;
		for(i=0;i<65536;i++){
			byte v=TerrHI[i];
			DATA24[ofs3]=v;
			DATA24[ofs3+1]=v;
			DATA24[ofs3+2]=v;
			ofs3+=3;
		};
		SaveToBMP24("Data\\02.bmp",256,256,DATA24);
		ofs3=0;
		for(i=0;i<65536;i++){
			byte v=SoftArea[i];
			if(v){
				DATA24[ofs3]=0;
				DATA24[ofs3+1]=0;
				DATA24[ofs3+2]=0xFF;
			}else{
				DATA24[ofs3]=0;
				DATA24[ofs3+1]=0;
				DATA24[ofs3+2]=0;
			};
			ofs3+=3;
		};
		SaveToBMP24("Data\\03.bmp",256,256,DATA24);
		free(DATA24);
		GenerateMapForMission("Data\\01.bmp","hehe","Data\\02.bmp","Data\\03.bmp");
	};
	free(BACK);
	FreeTerr();
};
#define CM_WLx 352
#define CM_WLy 90
void DrawHdrTable(int x0,int y0,int x1,int y1);
void DeleteAllSprites();
void DeleteAllUnits();
void ClearAllZones();
void CreateNEWMAP(){
	int X0=(RealLx-CM_WLx)>>1;
	int Y0=(RealLy-CM_WLy)>>1;
	
	byte* p=new byte[(CM_WLx+64)*(CM_WLy+140)];
	MemScreenPart(X0-32,Y0-32,(CM_WLx+64),(CM_WLy+140),p);
	DialogsSystem DSS(X0,Y0);
	DSS.addBPXView(NULL,-32,-32,(CM_WLx+64),(CM_WLy+140),1,1,1,p,NULL);
	DSS.addBorder(0,0,CM_WLx,CM_WLy,0,1);
	int FDY=40;
	DSS.addTextButton(NULL,16,5    ,GetTextByID("NEWMPHDR"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,16,FDY   ,GetTextByID("SELMSZ"),&YellowFont,&YellowFont,&YellowFont,0);
	ComboBox* CB=DSS.addGP_ComboBoxDLX(NULL,150,FDY   ,180,CBB_GPFILE,0,9,0,&WhiteFont,&YellowFont,NULL);
	CB->AddLine(GetTextByID("SEL_MS0"));
	CB->AddLine(GetTextByID("SEL_MS1"));
	CB->AddLine(GetTextByID("SEL_MS2"));
	
	int XB=10;
	int YB=CM_WLy+7;
	DSS.addGPPicture(NULL,XB,YB,CBB_GPFILE,8);
	DSS.addGPPicture(NULL,XB,YB,CBB_GPFILE,11);
	GP_TextButton* OKBTN=DSS.addGP_TextButton(NULL,XB+9,YB+20,GetTextByID("@OK"),CBB_GPFILE,9,&WhiteFont,&YellowFont);
	OKBTN->OnUserClick=&MMItemChoose;
	OKBTN->UserParam=mcmOk;
	XB=180;
	YB=CM_WLy+7;
	DSS.addGPPicture(NULL,XB,YB,CBB_GPFILE,8);
	DSS.addGPPicture(NULL,XB,YB,CBB_GPFILE,11);
	GP_TextButton* CANCELBTN=DSS.addGP_TextButton(NULL,XB+9,YB+20,GetTextByID("@CANCEL"),CBB_GPFILE,9,&WhiteFont,&YellowFont);
	CANCELBTN->OnUserClick=&MMItemChoose;
	CANCELBTN->UserParam=0;
	ItemChoose=-1;
	do{
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		DeleteAllSprites();
		DeleteAllUnits();
		ClearAllZones();
		FreeArrays();
		ADDSH=1+CB->CurLine;
		msx=240<<ADDSH;
		msy=240<<ADDSH;
		SetupArrays();
		EraseAreas();
		rando();//!!
		CreateTotalLocking();
		TestRoads();
		ResearchIslands();
	};
	free(p);
};
//-----------------Clans support----------------//
struct ClanInfo{
	char* ClanName;
	SQPicture Passive;
	SQPicture Active;
	SQPicture Over;
};
ClanInfo* CLINFO=NULL;
int NClans=0;
extern bool SafeLoad;
void ReadClanData(){
	SafeLoad=1;
	WIN32_FIND_DATA FD;
	HANDLE H=FindFirstFile("Clans\\*.clan",&FD);
	if(H!=INVALID_HANDLE_VALUE){
		do{
			char ccc[128];
			sprintf(ccc,"Clans\\%s",FD.cFileName);
			FILE* F=fopen(ccc,"r");
			if(F){
				char cc1[128];
				char cc2[128];
				char cc3[128];
				int z=fscanf(F,"%s%s%s",cc1,cc2,cc3);
				if(z==3){
					SQPicture P1;
					sprintf(ccc,"Clans\\%s",cc1);
					P1.LoadPicture(ccc);
					if(P1.GetLx()<256&&P1.GetLy()==20){
						sprintf(ccc,"Clans\\%s",cc2);
						P1.LoadPicture(ccc);
						if(P1.GetLx()<256&&P1.GetLy()==20){
							sprintf(ccc,"Clans\\%s",cc3);
							P1.LoadPicture(ccc);
							if(P1.GetLx()<256&&P1.GetLy()==20){
								CLINFO=(ClanInfo*)realloc(CLINFO,(NClans+1)*sizeof ClanInfo);
								memset(CLINFO+NClans,0,sizeof ClanInfo);
								sprintf(ccc,"Clans\\%s",cc1);
								CLINFO[NClans].Over.LoadPicture(ccc);
								sprintf(ccc,"Clans\\%s",cc2);
								CLINFO[NClans].Active.LoadPicture(ccc);
								sprintf(ccc,"Clans\\%s",cc3);
								CLINFO[NClans].Passive.LoadPicture(ccc);
								strcpy(ccc,FD.cFileName);
								char* ccx=strstr(ccc,".clan");
								if(!ccx)ccx=strstr(ccc,".CLAN");
								if(!ccx)ccx=strstr(ccc,".Clan");
								if(ccx)ccx[0]=0;
								CLINFO[NClans].ClanName=new char[strlen(ccc)+1];
								strcpy(CLINFO[NClans].ClanName,ccc);
								NClans++;
							};
						};
					};
				};
				fclose(F);
			};
		}while(FindNextFile(H,&FD));
		FindClose(H);
	};
	SafeLoad=0;
	//sorting
	bool change;
	ClanInfo CIN;
	do{
		change=0;
		for(int i=1;i<NClans;i++){
			if(strlen(CLINFO[i-1].ClanName)<strlen(CLINFO[i].ClanName)){
				CIN=CLINFO[i-1];
				CLINFO[i-1]=CLINFO[i];
				CLINFO[i]=CIN;
				change=1;
			};
		};
	}while(change);
	memset(&CIN,0,sizeof CIN);

};
CEXPORT
void ShowClanString(int x,int y,char* s,byte State,RLCFont* Fn,RLCFont* Fn1,int DY){
	char ccc[64];
	char NICK[128];
	char CLAN[128];
	strcpy(NICK,s);
	_strupr(NICK);
	strcpy(ccc,s);
	for(int i=0;i<NClans;i++){
		strcpy(CLAN,CLINFO[i].ClanName);
		_strupr(CLAN);
		char* cc=strstr(NICK,CLAN);
		if(cc&&cc==NICK){
			//ok, found!
			cc=ccc;
			cc+=strlen(CLINFO[i].ClanName);
			SQPicture* p;
			switch(State){
			case 0:
				p=&CLINFO[i].Passive;
				break;
			case 1:
				p=&CLINFO[i].Active;
				break;
			case 2:
				p=&CLINFO[i].Over;
				break;
			};
			p->Draw(x,y-2);
			if(Fn1)ShowString(x+p->GetLx()+1+3,y+DY+1,cc,Fn1);
			ShowString(x+p->GetLx()+3,y+DY,cc,Fn);
			return;
		};
	};
	if(Fn1)ShowString(x+1,y+DY+1,s,Fn1);
	ShowString(x,y+DY,s,Fn);
	return;
};
void WaitWithError4(char* ID,int GPID);
void ERRMESSAGE(char* STR){
	LocalGP BOR2("Interface\\bor2");
	WaitWithError4(STR,BOR2.GPID);
};
__declspec(dllexport)
bool CheckUsingAI(){
	for(int i=0;i<8;i++)if(NATIONS[i].AI_Enabled)return true;
	return false;
};