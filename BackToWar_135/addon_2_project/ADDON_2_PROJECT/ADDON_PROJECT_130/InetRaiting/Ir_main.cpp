#include "..\ddini.h"
#include "..\ResFile.h"
#include "..\FastDraw.h"
#include "..\mgraph.h"
#include "..\mouse.h"
#include "..\menu.h"
#include "..\MapDiscr.h"
#include "..\multipl.h"
#include "..\fog.h"
#include "..\walls.h"
#include "..\Nature.h"
#include <time.h>
#include "..\Nucl.h"
#include "..\TopZones.h"
#include "..\Megapolis.h"
#include "..\Dialogs.h"
#include "..\fonts.h"
#include "..\dpchat.h"
#include "..\dplobby.h"
#include "..\GSound.h"
#include "..\3DGraph.h"
#include "..\3DMapEd.h"
#include "..\MapSprites.h"
#include <assert.h>
#include <math.h>
#include "..\NewMon.h"
#include "..\IconTool.h"
#include "..\GP_Draw.h"
#include "..\3DRandMap.h"
#include <crtdbg.h>
#include "..\ActiveScenary.h"
#include "..\DrawForm.h"
#include "..\Conststr.h"
#include <Process.h>
#include "..\MPlayer.h"
#include "..\Recorder.h"
#include "..\GSINC.H"
#include "..\TopoGraf.h"
#include "..\PeerClass.h";
#include "..\CEngine\goaceng.h";
#include "..\StrategyResearch.h"
#include "..\Safety.h"
#include "..\EinfoClass.h"
#include "stats\gstats.h"
#include "stats\gpersist.h"
//#define DOTRACE xDOTRACE(__FILE__,__LINE__)
#define DOTRACE
extern "C" void xDOTRACE(char* file,int Line);
byte INSIDE4=0;
void CheckExistingSaves();
#pragma pack(4)
#include "GP.h"
#pragma pack(1)
int TestUNIQ(char* email,char* Nick);
void MakeUniqLastName(char* email,char* Nick,char* LastName);
void ShowCentralMessage(char* Message,int GPIDX);
extern char PlName[64];
extern int CurProfileID;
GPConnection* LOGIN_gp=0;
void DarkScreen();
char* GetTextByID(char* ID);
bool InitUser(int ProfileID,char* password);
void ProcessScreen();
void GSYSDRAW();
void SendPlayerRequest(char* Nick,char* mail);
extern int ShowGameScreen;
void ActiveProcess(){
	if(ShowGameScreen){
		ProcessScreen();
		GSYSDRAW();
	};
};
class PLAYERLOGIN{
public:
	PLAYERLOGIN();
	~PLAYERLOGIN();
	bool Connected;
	bool Logged;
	bool Error;
	byte Rank;
	GPConnection gp;
	char Nick[64];
	char EMail[128];
	char Password[64];
	GPProfile ProfileID;
	void Setup();
	bool LogIn(char* Name,char* Password);//true-logged ok, false - profile not exsists
};
PLAYERLOGIN::PLAYERLOGIN(){
	gp=NULL;
	LOGIN_gp=0;
	Setup();
};
PLAYERLOGIN::~PLAYERLOGIN(){
};
PLAYERLOGIN LOGIN;
void ErrorCallback(GPConnection * connection, void* arg, void* param){
};
void PLAYERLOGIN::Setup(){
	gpInitialize(&gp);
	gpSetCallback(&gp, GP_ERROR, &ErrorCallback, this);
	LOGIN_gp=&gp;
};

bool CHECKBOXCLICK(SimpleDialog* SD){
	GP_Button* GPB=(GP_Button*)SD;
	if(GPB->ActiveFrame==9){
		GPB->ActiveFrame=11;
		GPB->PassiveFrame=12;
	}else{
		GPB->ActiveFrame=9;
		GPB->PassiveFrame=10;
	};
	return false;
};
bool ReadWinString(GFILE* F,char* STR,int Max);
void FREEPLIST(char** PLLIST,char** EMAILS,char** PASWRD,int NPLR){
	for(int i=0;i<NPLR;i++){
		free(PLLIST[i]);
		free(EMAILS[i]);
		free(PASWRD[i]);
	};
	if(NPLR){
		free(PLLIST);
		free(EMAILS);
		free(PASWRD);
	};
};
#define FreePLRS FREEPLIST(PLLIST,EMAILS,PASWRD,NPLR)
extern int ItemChoose;
bool MMItemChoose(SimpleDialog* SD);
bool ProcessMessages();
bool AddNewProfile();
extern bool KeyPressed;
void Conn_callback(GPConnection * connection,void * arg,void * param);
void ShowCentralMessage2(char* Message,int GPIDX);
void ShowCentralMessage3(char* Message,int GPIDX);
void WaitWithError(char* ID,int GPID){
	char ccc[1256];
	strcpy(ccc,GetTextByID(ID));

	//gpGetErrorString(&LOGIN.gp,ccc);
	ShowCentralMessage3(GetTextByID(ID),GPID);
	FlipPages();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(!KeyPressed);
};
void ShowCentralMessage4(char* Message,int GPIDX,int DX);
void WaitWithError4(char* ID,int GPID){
	char ccc[4096];
	strcpy(ccc,GetTextByID(ID));

	//gpGetErrorString(&LOGIN.gp,ccc);
	ShowCentralMessage4(GetTextByID(ID),GPID,90);
	FlipPages();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(!KeyPressed);
};

void LoginError(int GPID){
	char cxx[1256];
	char* ccc=NULL;
	GPErrorCode ERR;
	gpGetErrorCode(&LOGIN.gp,&ERR);
	switch(ERR){
	case 0:
		ccc=GetTextByID("LERR_GENERAL");
		break;
	case 5:
		ccc=GetTextByID("LERR_NETWORK");
		break;
	case 0x101://timeout
		ccc=GetTextByID("LERR_TIMEOUT");
		break;
	case 0x102://Invalid nick
		ccc=GetTextByID("LERR_INVNICK");
		break;
	case 0x103:
		ccc=GetTextByID("LERR_INVEMAIL");
		break;
	case 0x104:
		ccc=GetTextByID("LERR_INVPASS");
		break;
	case 0x105:
		ccc=GetTextByID("LERR_PROF");
		break;
	case 0x106:
		ccc=GetTextByID("LERR_PROFDEL");
		break;
	case 0x107:
	case 0x108:
		ccc=GetTextByID("LERR_FAIL");
		break;
	default:
		sprintf(cxx,GetTextByID("LERR_UNKN"),int(ERR));
		ccc=cxx;
	};
	ShowCentralMessage3(ccc/*GetTextByID(ID)*/,GPID);
	FlipPages();
	KeyPressed=0;
	do{
		ProcessMessages();
	}while(!KeyPressed);
};
char* CODESTR1="AxDfRew34UinGtKv";
char* CODESTR2="KJhilurhflikhsgh";
void ProcessPlayerInfo(int ProfileID,int UNICAL);
void printhex(char* s,byte v){
	char* hids="0123456789ABCDEF";
	s[0]=hids[v>>4];
	s[1]=hids[v&15];
	s[2]=0;
};
void EncodePassword(char* Pass,char* result){
	char pass[128];
	strcpy(pass,Pass);
	int L=strlen(pass);
	for(int i=0;i<L;i++)pass[i]=(pass[i]+CODESTR1[i&15])^CODESTR2[i&15];
	sprintf(result,"{PS}");
	for(i=0;i<L;i++)printhex(result+strlen(result),pass[i]);
};
byte GetHByChar(byte v){
	if(v>='0'&&v<='9')return v-'0';
	if(v>='A'&&v<='F')return v-'A'+10;
	if(v>='a'&&v<='f')return v-'a'+10;
	return 0;
};
byte GetHex(char* s){
	return GetHByChar(s[1])+(GetHByChar(s[0])<<4);
};
void DecodePassword(char* source,char* pass){
	char* src=source;
	if(source[0]=='{'&&source[1]=='P'&&source[2]=='S'&&source[3]=='}'){
		source+=2;
		char cc1[12];
		cc1[2]=0;
		int i=0;
		do{
			source+=2;
			cc1[0]=source[0];
			cc1[1]=source[1];
			pass[i]=GetHex(cc1);
			i++;
			pass[i]=0;
		}while(source[0]&&source[1]);
		int L=(strlen(src)-4)>>1;
		for(i=0;i<L;i++)pass[i]=(pass[i]^CODESTR2[i&15])-CODESTR1[i&15];
		pass[L]=0;
	}else strcpy(pass,source);
};
bool ProcessNewInternetLogin();

bool InternetGameLogin(){
	if(UseGSC_Login){
		return ProcessNewInternetLogin();
	};
	GFILE* F=Gopen("Players\\Internet.dat","r");
	char** PLLIST=NULL;
	char** EMAILS=NULL;
	char** PASWRD=NULL;
	int NPLR=0;
	if(F){
		char S1[64];
		char S2[64];
		char S3[64];
		char S4[128];
		int z=0;
		do{
			S1[0]=0;S2[0]=0;S3[0]=0;
			ReadWinString(F,S1,64);
			ReadWinString(F,S2,64);
			ReadWinString(F,S4,128);
			DecodePassword(S4,S3);
			if(S1[0]&&S2[0]){
				NPLR++;
				PLLIST=(char**)realloc(PLLIST,NPLR*4);
				EMAILS=(char**)realloc(EMAILS,NPLR*4);
				PASWRD=(char**)realloc(PASWRD,NPLR*4);

				PLLIST[NPLR-1]=new char[strlen(S1)+1];
				strcpy(PLLIST[NPLR-1],S1);

				EMAILS[NPLR-1]=new char[strlen(S2)+1];
				strcpy(EMAILS[NPLR-1],S2);

				PASWRD[NPLR-1]=new char[strlen(S3)+1];
				strcpy(PASWRD[NPLR-1],S3);
			};
		}while(S1[0]&&S2[0]);
		Gclose(F);
	};
	if(!NPLR){
		int res=AddNewProfile();
		if(res){
			FILE* F=fopen("Players\\Internet.dat","w");
			if(F){
				char cc3[128];
				EncodePassword(LOGIN.Password,cc3);
				fprintf(F,"%s\n%s\n%s\n",LOGIN.Nick,LOGIN.EMail,cc3);
				fclose(F);
			};
			return true;
		};
		return false;//tmp
	};
	LocalGP BOR2("Interface\\Bor2");
	DialogsSystem DSS(0,0);
	SQPicture Back("Interface\\Background_Internet_Login.bmp");
	DSS.addPicture(NULL,0,0,&Back,&Back,&Back);
	
	LocalGP BTNS("Interface\\Login");
	LocalGP SCROL("Interface\\_Slider");

	GPPicture* AnonimBack=DSS.addGPPicture(NULL,93,294,BTNS.GPID,8);
	ComboBox* PLNAME=DSS.addGP_ComboBox(NULL,266,301,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VS2;
	PLNAME->AssignScroll(&DSS,&VS2,SCROL.GPID,0,8);
	for(int i=0;i<NPLR;i++)PLNAME->AddLine(PLLIST[i]);

	char PASSWORD[64]="";
	char AN_Nick[64]="";

	GP_Button* NameBack=DSS.addGP_Button(NULL,266,301,BTNS.GPID,13,14);
	NameBack->Visible=0;
	InputBox* Nick=DSS.addInputBox(NULL,266,301,AN_Nick,20,224,26,&YellowFont,&WhiteFont);
	Nick->Visible=0;
	Nick->Enabled=0;
	Nick->Active=0;

	InputBox* PASSW=DSS.addInputBox(NULL,266,327,PASSWORD,20,224,26,&YellowFont,&WhiteFont);
	PASSW->Anonim=1;

	GP_Button* RemPassw=DSS.addGP_Button(NULL,266,366,BTNS.GPID,11,12);
	RemPassw->OnUserClick=&CHECKBOXCLICK;

	GP_Button* AnonimLogin=DSS.addGP_Button(NULL,266,392,BTNS.GPID,9,10);
	AnonimLogin->OnUserClick=&CHECKBOXCLICK;

	GP_Button* BypassInfo=DSS.addGP_Button(NULL,484,366,BTNS.GPID,11,12);
	BypassInfo->OnUserClick=&CHECKBOXCLICK;

	GP_Button* RetPassword=DSS.addGP_Button(NULL,299,392,BTNS.GPID,15,16);
	RetPassword->OnUserClick=&MMItemChoose;
	RetPassword->UserParam=112;

	GP_Button* Login=DSS.addGP_Button(NULL,109,448,BTNS.GPID,17,18);
	Login->OnUserClick=&MMItemChoose;
	Login->UserParam=mcmOk;

	GP_Button* NewPlayer=DSS.addGP_Button(NULL,245,448,BTNS.GPID,21,22);
	NewPlayer->OnUserClick=&MMItemChoose;
	NewPlayer->UserParam=mcmJoin;

	GP_Button* Cancel=DSS.addGP_Button(NULL,380,448,BTNS.GPID,19,20);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;
BEGINIT:	
	ItemChoose=-1;
	int LPRV=-1;
	LoadPalette("2\\agew_1.pal");
	gpDisconnect(&LOGIN.gp);
	LOGIN.Logged=0;
	LOGIN.Error=0;
	LOGIN.ProfileID=0;
	do{
		for(int j=0;j<strlen(AN_Nick);j++){
			char c=AN_Nick[j];
			if(c=='[')c='(';
			if(c==']')c=')';
			AN_Nick[j]=c;
		};
		if(AnonimLogin->ActiveFrame==11){
			//anonimous login
			AnonimBack->Visible=1;
			AnonimBack->Enabled=1;
			RetPassword->Enabled=0;
			RetPassword->Visible=0;
			RemPassw->Enabled=0;
			RemPassw->Visible=0;
			BypassInfo->Visible=0;
			BypassInfo->Enabled=0;
			PLNAME->Visible=0;
			PLNAME->Enabled=0;
			Nick->Visible=1;
			Nick->Enabled=1;
			Nick->Active=1;
			PASSW->Enabled=0;
			PASSW->Visible=0;
		}else{
			AnonimBack->Visible=0;
			AnonimBack->Enabled=0;
			RetPassword->Enabled=1;
			RetPassword->Visible=1;
			RemPassw->Enabled=1;
			RemPassw->Visible=1;
			BypassInfo->Visible=1;
			BypassInfo->Enabled=1;
			PLNAME->Visible=1;
			PLNAME->Enabled=1;
			Nick->Visible=0;
			Nick->Enabled=0;
			Nick->Active=0;
			strcpy(Nick->Str,PLLIST[PLNAME->CurLine]);
			if(LPRV!=PLNAME->CurLine){
				strcpy(PASSW->Str,PASWRD[PLNAME->CurLine]);
				LPRV=PLNAME->CurLine;
			};
			PASSW->Enabled=1;
			PASSW->Visible=1;
		};
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
		if(ItemChoose==112){
			char ccc[256];
			sprintf(ccc,"http://gamespyarcade.com/software/reqemail.asp?email=%s",EMAILS[PLNAME->CurLine]);
			ClearScreen();
			FlipPages();
			ShellExecute(NULL,NULL,ccc,"","",SW_SHOWMAXIMIZED);
			ItemChoose=-1;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		if(AnonimLogin->ActiveFrame==11){
			LOGIN.ProfileID=0;
			LOGIN.Logged=0;
			strcpy(LOGIN.Nick,Nick->Str);
			strcpy(PlName,Nick->Str);
			CurProfileID=0;
			return true;
		}else{
			LOGIN.Logged=0;
			LOGIN.Error=0;
			LOGIN.ProfileID=0;
			
			ShowCentralMessage2(GetTextByID("WZR_LOGIN0"),BOR2.GPID);
			FlipPages();
			GPResult Res=gpConnect(&LOGIN.gp,PLLIST[PLNAME->CurLine],EMAILS[PLNAME->CurLine],
				PASSWORD,GP_FIREWALL,GP_NON_BLOCKING,&Conn_callback,&LOGIN);
			if(Res!=GP_NO_ERROR){
				//WaitWithError("WZR_ERR3",BOR2.GPID);
				LoginError(BOR2.GPID);
				goto BEGINIT;
			}else{
				int Lt0=GetTickCount();
				do{
					if(GetTickCount()-Lt0>60000)LOGIN.Error=1;
					ProcessMessages();
				}while(!(LOGIN.Logged||LOGIN.Error));
				if(LOGIN.Error||!LOGIN.ProfileID){
					//WaitWithError("WZR_LOGFAIL",BOR2.GPID);
					LoginError(BOR2.GPID);
					goto BEGINIT;
				}else{
					if(!InitUser(LOGIN.ProfileID,PASSWORD)){
						//WaitWithError("WZR_LOGFAIL",BOR2.GPID);
						//LoginError(BOR2.GPID);
						goto BEGINIT;
					};
					CheckExistingSaves();
					strcpy(LOGIN.EMail,EMAILS[PLNAME->CurLine]);
					strcpy(LOGIN.Nick,PLLIST[PLNAME->CurLine]);
					strcpy(LOGIN.Password,PASSWORD);
					strcpy(PlName,LOGIN.Nick);
					CurProfileID=LOGIN.ProfileID;
					//SendPlayerRequest(LOGIN.Nick,LOGIN.EMail);
					if(BypassInfo->ActiveFrame==9)ProcessPlayerInfo(CurProfileID,255);
					FILE* F=fopen("Players\\Internet.dat","w");
					if(F){
						if(LOGIN.Nick){
							if(RemPassw->ActiveFrame==11){
								char cc3[128];
								EncodePassword(LOGIN.Password,cc3);
								fprintf(F,"%s\n%s\n%s\n",LOGIN.Nick,LOGIN.EMail,cc3);
							}else{ 
								fprintf(F,"%s\n%s\n\n",LOGIN.Nick,LOGIN.EMail);
							};
						};
						for(int i=0;i<NPLR;i++){
							if(_stricmp(PLLIST[i],LOGIN.Nick)||
							   _stricmp(EMAILS[i],LOGIN.EMail)){
								char cc3[128];
								EncodePassword(PASWRD[i],cc3);
								fprintf(F,"%s\n%s\n%s\n",PLLIST[i],EMAILS[i],cc3);
							};
						};
						fclose(F);
						return true;
					};
					return true;
				};
			};
		};

	};
	if(ItemChoose==mcmJoin){
		int res=AddNewProfile();
		if(res){
			FILE* F=fopen("Players\\Internet.dat","w");
			if(F){
				if(LOGIN.Nick)fprintf(F,"%s\n%s\n%s\n",LOGIN.Nick,LOGIN.EMail,LOGIN.Password);
				for(int i=0;i<NPLR;i++){
					if(_stricmp(PLLIST[i],LOGIN.Nick)||
					   _stricmp(EMAILS[i],LOGIN.EMail)||
					   strcmp(PASWRD[i],LOGIN.Password)){
						char cc3[128];
						EncodePassword(PASWRD[i],cc3);
						fprintf(F,"%s\n%s\n%s\n",PLLIST[i],EMAILS[i],cc3);
					};
				};
				fclose(F);
				return true;
			};
		};
		FreePLRS;
	};
	return false;
};

bool EnterEMail(char* EMail){
	EMail[0]=0;
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Wizard.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	//-----------------------
	LocalGP B2("Interface\\bor2");
	int CR[8]={8,9,2,3,4,5,10,7};
	DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
	DSS.addGPPicture(NULL,78,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
	//-----------------------

	GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
	Prev->OnUserClick=&MMItemChoose;
	Prev->UserParam=1;

	GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;

	GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
	Next->OnUserClick=&MMItemChoose;
	Next->UserParam=2;


	DSS.addTextButton(NULL,76,188,GetTextByID("WZR_H0"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5,GetTextByID("WZR_00"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26,GetTextByID("WZR_01"),&YellowFont,&YellowFont,&YellowFont,0);
	int DX=60;
	DSS.addTextButton(NULL,76+DX,219+5+26*4,GetTextByID("WZR_02"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76+DX,219+5+26*6,GetTextByID("WZR_03"),&YellowFont,&YellowFont,&YellowFont,0);

	DSS.addGP_Button(NULL,76+DX,219+2+26*5,BTNS.GPID,13,14);
	InputBox* IB=DSS.addInputBox(NULL,76+DX,219+26*5,EMail,120,230,26,&YellowFont,&WhiteFont);
	IB->Active=1;
	ItemChoose=-1;
	do{
		Next->Enabled=(strlen(EMail)>0&&strstr(EMail,"@")&&strstr(EMail,"."));
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	return ItemChoose==2;
};
int EnterNewNick(char* Nick){
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Wizard.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	//-----------------------
	LocalGP B2("Interface\\bor2");
	int CR[8]={8,9,2,3,4,5,10,7};
	DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
	DSS.addGPPicture(NULL,78,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
	//-----------------------

	GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
	Prev->OnUserClick=&MMItemChoose;
	Prev->UserParam=1;

	GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;

	GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
	Next->OnUserClick=&MMItemChoose;
	Next->UserParam=2;


	DSS.addTextButton(NULL,76,188,GetTextByID("WZR_H4"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5,GetTextByID("WZR_40"),&YellowFont,&YellowFont,&YellowFont,0);

	DSS.addTextButton(NULL,76,219+5+26*2,GetTextByID("WZR_41"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26*3,GetTextByID("WZR_42"),&YellowFont,&YellowFont,&YellowFont,0);

	int DX=110;
	DSS.addTextButton(NULL,76+DX,219+5+26*5,GetTextByID("WZR_43"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addGP_Button(NULL,76+DX,219+2+26*6,BTNS.GPID,13,14);

	InputBox* IB=DSS.addInputBox(NULL,76+DX,219+26*6,Nick,120,230,26,&YellowFont,&WhiteFont);
	IB->Active=1;
	ItemChoose=-1;
	do{
		Next->Enabled=strlen(Nick)>0;
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	return ItemChoose;
};
int CreateNewAccount(char* EMail,char* Password,bool* Store){
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Wizard.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	//-----------------------
	LocalGP B2("Interface\\bor2");
	int CR[8]={8,9,2,3,4,5,10,7};
	DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
	DSS.addGPPicture(NULL,78,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
	//-----------------------

	GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
	Prev->OnUserClick=&MMItemChoose;
	Prev->UserParam=1;

	GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;

	GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
	Next->OnUserClick=&MMItemChoose;
	Next->UserParam=2;

	DSS.addTextButton(NULL,76,188       ,GetTextByID("WZR_H1"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5     ,GetTextByID("WZR_10"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26  ,GetTextByID("WZR_11"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26*2,GetTextByID("WZR_12"),&YellowFont,&YellowFont,&YellowFont,0);

	DSS.addTextButton(NULL,76,219+5+26*4,GetTextByID("WZR_13"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26*6,GetTextByID("WZR_14"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26*7,GetTextByID("WZR_15"),&YellowFont,&YellowFont,&YellowFont,0);

	GP_Button* RemPassw=DSS.addGP_Button(NULL,76,219+1+26*10,BTNS.GPID,11,12);
	RemPassw->OnUserClick=&CHECKBOXCLICK;
	DSS.addTextButton(NULL,76+32,219+5+26*10,GetTextByID("WZR_16"),&YellowFont,&YellowFont,&YellowFont,0);

	char CheckPass[128];
	Password[0]=0;
	CheckPass[0]=0;
	int DX=120;
	DSS.addGP_Button(NULL,76+DX,219+1+26*4,BTNS.GPID,13,14);
	InputBox* IB1=DSS.addInputBox(NULL,76+DX,219+26*4,EMail,40,240,26,&YellowFont,&WhiteFont);
	IB1->Enabled=0;
	DSS.addGP_Button(NULL,76+DX,219+1+26*6,BTNS.GPID,13,14);
	InputBox* IB2=DSS.addInputBox(NULL,76+DX,219+26*6,Password,40,240,26,&YellowFont,&WhiteFont);
	IB2->Active=1;
	DSS.addGP_Button(NULL,76+DX,219+1+26*7,BTNS.GPID,13,14);
	InputBox* IB3=DSS.addInputBox(NULL,76+DX,219+26*7,CheckPass,40,240,26,&YellowFont,&WhiteFont);
	ItemChoose=-1;
	do{
		if(strlen(Password)==0||strcmp(Password,CheckPass))Next->Enabled=0;
		else Next->Enabled=1;
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	*Store=RemPassw->ActiveFrame==11;
	return ItemChoose;
};
int EnterAccountPassword(char* Password,bool First,char* mail){
	Password[0]=0;
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Wizard.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	//-----------------------
	LocalGP B2("Interface\\bor2");
	int CR[8]={8,9,2,3,4,5,10,7};
	DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
	DSS.addGPPicture(NULL,78,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
	//-----------------------

	GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
	Prev->OnUserClick=&MMItemChoose;
	Prev->UserParam=1;

	GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;

	GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
	Next->OnUserClick=&MMItemChoose;
	Next->UserParam=2;


	DSS.addTextButton(NULL,76,188,GetTextByID("WZR_H2"),&YellowFont,&YellowFont,&YellowFont,0);
	if(First)DSS.addTextButton(NULL,76,219+5,GetTextByID("WZR_20"),&YellowFont,&YellowFont,&YellowFont,0);
	else DSS.addTextButton(NULL,76,219+5,GetTextByID("WZR_20W"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26,GetTextByID("WZR_21"),&YellowFont,&YellowFont,&YellowFont,0);
	int DX=100;
	DSS.addTextButton(NULL,76,219+5+26*5,GetTextByID("WZR_22"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76+DX,219+5+26*6,GetTextByID("WZR_23"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76+DX,219+5+26*7,GetTextByID("WZR_24"),&YellowFont,&YellowFont,&YellowFont,0);

	DSS.addGP_Button(NULL,76+DX,219+2+26*5,BTNS.GPID,13,14);
	InputBox* IB=DSS.addInputBox(NULL,76+DX,219+26*5,Password,120,230,26,&YellowFont,&WhiteFont);
	IB->Active=1;
	IB->Anonim=1;

	TextButton* TB=DSS.addTextButton(NULL,76,219+26*10,GetTextByID("WZR_25"),&WhiteFont,&YellowFont,&YellowFont,0);
	TB->OnUserClick=&MMItemChoose;
	TB->UserParam=85;
	
	ItemChoose=-1;
	do{
		Next->Enabled=strlen(Password)>0;
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
		if(ItemChoose==85){
			char ccc[256];
			sprintf(ccc,"http://gamespyarcade.com/software/reqemail.asp?email=%s",mail);
			ClearScreen();
			FlipPages();
			ShellExecute(NULL,NULL,ccc,"","",SW_SHOWMAXIMIZED);
			ItemChoose=-1;
		};
	}while(ItemChoose==-1);
	return ItemChoose;
};

char* LASTNICK;
void E_Search(GPConnection * connection,void * arg,void * param){
	GPProfileSearchResponseArg* RES=(GPProfileSearchResponseArg*)arg;
	int* par=(int*)param;
	if(RES->result==GP_NO_ERROR){
		if(RES->numMatches){
			*par=2;
			strcpy(LASTNICK,RES->matches[0].nick);
		}else *par=1;
	}else *par=3;
};
void Conn_callback(GPConnection * connection,void * arg,void * param){
	INSIDE4=5;
	DOTRACE;
	GPConnectResponseArg* CONN=(GPConnectResponseArg*)arg;
	PLAYERLOGIN* LOG=(PLAYERLOGIN*)param;
	if(CONN->result==GP_NO_ERROR){
		LOG->Error=0;
		LOG->ProfileID=CONN->profile;
		LOG->Logged=1;
	}else{
		LOG->Error=1;
	};
	DOTRACE;
	INSIDE4=6;
};
extern int RealLx;
extern int RealLy;
void ShowCentralMessage2(char* Message,int GPIDX){
	int L=GetRLCStrWidth(Message,&WhiteFont);
	int DX=200;
	int DY=25;
	DrawStdBar2((RealLx-L-64)/2-DX,(RealLy-70)/2+18-DY,(RealLx+L+64)/2-DX,(RealLy-70)/2+55-DY,GPIDX);
	ShowString((RealLx-L)/2+1-DX,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2+1-DY,Message,&BlackFont);
	ShowString((RealLx-L)/2-DX,(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2-DY,Message,&YellowFont);
};
void GetAllPar3(int LXMAX,int* N,int* LMaxX,char* Message){
	int NStr=1;
	int pos=0;
	int LM=0;
	int L=strlen(Message);
	int L0=0;
	do{
		if(L0>LM)LM=L0;
		if(Message[pos]==' '&&L0>LXMAX){
			NStr++;
			L0=0;
			pos++;
		}else{
			int DX;
			L0+=GetRLCWidthUNICODE(YellowFont.RLC,(byte*)(Message+pos),&DX);
			pos+=DX;
		};
		if(L0>LM)LM=L0;
	}while(Message[pos]);
	*N=NStr;
	*LMaxX=LM;
};
extern int CurPalette;
void ShowCentralMessage4(char* Message,int GPIDX,int DX){
	int LXMAX=400;
	char ccx[256];
	int L0=0;
	int NStr=1;
	int pos=0;
	int LM=0;
	int L=strlen(Message);
	GetAllPar3(LXMAX,&NStr,&LM,Message);
	int N1,LM1;
	int DXXX=32;
	do{
		GetAllPar3(LXMAX-DXXX,&N1,&LM1,Message);
		DXXX+=32;
	}while(N1==NStr&&N1>1);
	LXMAX-=DXXX-64;
	GetAllPar3(LXMAX,&NStr,&LM,Message);
	ccx[0]=0;
	pos=0;
	int pos1=0;
	
	int DY=25;
	if(CurPalette==2)DrawStdBar2((RealLx-64-LM)/2-DX,(RealLy-70)/2+18-DY-(NStr-1)*13,(RealLx+64+LM)/2-DX,(RealLy-70)/2+55-DY+(NStr-1)*13,GPIDX);
	else{
		DX=0;
		DrawStdBar((RealLx-64-LM)/2-DX,(RealLy-70)/2+18-DY-(NStr-1)*13,(RealLx+64+LM)/2-DX,(RealLy-70)/2+55-DY+(NStr-1)*13);
	};
	int y0=(RealLy-GetRLCHeight(YellowFont.RLC,'W'))/2+1-DY-(NStr-1)*13;
	L0=0;
	do{
		if((Message[pos]==' '&&L0>LXMAX)){
			int LL=GetRLCStrWidth(ccx,&YellowFont);
			ShowString((RealLx-LL)/2+1-DX,y0+1,ccx,&BlackFont);
			ShowString((RealLx-LL)/2-DX,y0,ccx,&YellowFont);
			pos1=0;
			ccx[0]=0;
			L0=0;
			pos++;
			y0+=26;
		}else{
			int DX;
			L0+=GetRLCWidthUNICODE(YellowFont.RLC,(byte*)(Message+pos),&DX);
			memcpy(ccx+pos1,Message+pos,DX);
			pos+=DX;
			pos1+=DX;
			ccx[pos1]=0;
		};
		if(!Message[pos]){
			int LL=GetRLCStrWidth(ccx,&YellowFont);
			ShowString((RealLx-LL)/2+1-DX,y0+1,ccx,&BlackFont);
			ShowString((RealLx-LL)/2-DX,y0,ccx,&YellowFont);
		};
	}while(Message[pos]);
};
void ShowCentralMessage3(char* Message,int GPIDX){
	ShowCentralMessage4(Message,GPIDX,206);
};
void New_profile(GPConnection * connection,void * arg,void * param){
	GPNewProfileResponseArg* RES=(GPNewProfileResponseArg*)arg;
	PLAYERLOGIN* LOG=(PLAYERLOGIN*)param;
	if(RES->result==GP_NO_ERROR){
		LOG->Error=0;
		LOG->ProfileID=RES->profile;
		LOG->Logged=1;
	}else{
		LOG->Error=1;
		LOG->Logged=0;
	};
};
void E_Search2(GPConnection * connection,void * arg,void * param){
	GPProfileSearchResponseArg* RES=(GPProfileSearchResponseArg*)arg;
	ComboBox* LB=(ComboBox*)param;
	if(RES->result==GP_NO_ERROR&&RES->numMatches){
		for(int i=0;i<RES->numMatches;i++)LB->AddLine(RES->matches[i].nick);	
	};
};
void Create_account(GPConnection * connection,void * arg,void * param){
	GPConnectResponseArg* CONN=(GPConnectResponseArg*)arg;
	PLAYERLOGIN* LOG=(PLAYERLOGIN*)param;
	if(CONN->result==GP_NO_ERROR){
		LOG->Error=0;
		LOG->ProfileID=CONN->profile;
		LOG->Logged=1;
	}else{
		LOG->Error=1;
	};
};
bool CHKCLICK(SimpleDialog* SD){
	GP_Button* GB=(GP_Button*)SD;
	GB->ActiveFrame=8;
	GB->PassiveFrame=9;
	return true;
};
//0-cancel,1-previous,2-new profile,3-existing
int SelectProfile(char* EMail,char* FinalNick){
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Wizard.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	LocalGP SCROL("Interface\\_Slider");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	//-----------------------
	LocalGP B2("Interface\\bor2");
	int CR[8]={8,9,2,3,4,5,10,7};
	DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
	DSS.addGPPicture(NULL,78,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
	DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
	//-----------------------

	GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
	Prev->OnUserClick=&MMItemChoose;
	Prev->UserParam=1;

	GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
	Cancel->OnUserClick=&MMItemChoose;
	Cancel->UserParam=mcmCancel;

	GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
	Next->OnUserClick=&MMItemChoose;
	Next->UserParam=2;


	DSS.addTextButton(NULL,76,188,GetTextByID("WZR_H3"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5   ,GetTextByID("WZR_30"),&YellowFont,&YellowFont,&YellowFont,0);
	DSS.addTextButton(NULL,76,219+5+26,GetTextByID("WZR_31"),&YellowFont,&YellowFont,&YellowFont,0);

	TextButton* CT1=DSS.addTextButton(NULL,76+32,219+5+26*3,GetTextByID("WZR_32"),&WhiteFont,&YellowFont,&YellowFont,0);
	CT1->OnUserClick=&MMItemChoose;
	CT1->UserParam=10;

	GP_Button* CHK1=DSS.addGP_Button(NULL,76,219+1+26*3,WBT.GPID,8,9);
	CHK1->OnUserClick=&CHKCLICK;

	GP_Button* GBI[5];
	GBI[0]=DSS.addGP_Button(NULL,76+32,219+1+26*4,BTNS.GPID,13,14);
	InputBox* NickIB=DSS.addInputBox(NULL,76+32,219+26*4,FinalNick,48,200,26,&YellowFont,&WhiteFont);
	FinalNick[0]=0;

	TextButton* CT2=DSS.addTextButton(NULL,76+32,219+5+26*5,GetTextByID("WZR_33"),&WhiteFont,&YellowFont,&YellowFont,0);
	CT2->OnUserClick=&MMItemChoose;
	CT2->UserParam=11;

	GP_Button* CHK2=DSS.addGP_Button(NULL,76,219+1+26*5,WBT.GPID,6,7);
	CHK2->OnUserClick=&CHKCLICK;

	ComboBox* NICKS=DSS.addGP_ComboBox(NULL,76+32,219+1+26*6,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VSN;//=DSS.addNewGP_VScrollBar(NULL,76+32+GPS.GetGPWidth(BTNS.GPID,13),219+1+26*6,4*26-2,1,0,SCROL.GPID,0);
	NICKS->AssignScroll(&DSS,&VSN,SCROL.GPID,0,6);

	gpProfileSearch(&LOGIN.gp,"",EMail,"","",0,GP_NON_BLOCKING,&E_Search2,NICKS);
	ItemChoose=-1;
	int CurChk=0;
	do{
		CHK2->Enabled=NICKS->NLines!=0;
		if(CurChk==0&&CHK2->ActiveFrame==8){
			CHK1->ActiveFrame=6;
			CHK1->PassiveFrame=7;
			CurChk=1;
		};
		if(CurChk==1&&CHK1->ActiveFrame==8){
			CHK2->ActiveFrame=6;
			CHK2->PassiveFrame=7;
			CurChk=0;
		};
		NICKS->Enabled=CurChk;
		NickIB->Enabled=!CurChk;
		NickIB->Active=!CurChk;
		if(CurChk==0){
			Next->Enabled=FinalNick[0]!=0;
		}else{
			Next->Enabled=NICKS->NLines!=0;
		};
		GBI[0]->ActiveFrame=GBI[0]->PassiveFrame-1+CurChk;
		
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
		if(ItemChoose==10){
			CHK1->ActiveFrame=8;
			CHK1->PassiveFrame=9;
			CHK2->ActiveFrame=6;
			CHK2->PassiveFrame=7;
			CurChk=0;
			ItemChoose=-1;
		};
		if(ItemChoose==11){
			CHK1->ActiveFrame=6;
			CHK1->PassiveFrame=7;
			CHK2->ActiveFrame=8;
			CHK2->PassiveFrame=9;
			CurChk=1;
			ItemChoose=-1;
		};
	}while(ItemChoose==-1);
	if(ItemChoose==2){
		if(CurChk){
			strcpy(FinalNick,NICKS->Lines[NICKS->CurLine]);
			return 3;
		}else{
			return 2;
		};
	}else if(ItemChoose==mcmCancel)return 0;
	else if(ItemChoose==1)return 1;
	return 0;
};

bool AddNewProfile(){
	LocalGP BOR2("Interface\\Bor2");
	LoadPalette("2\\agew_1.pal");
	char EMail[128];
	char Passw[128];
	char FIRSTNICK[128];
	LASTNICK=FIRSTNICK;
	bool Store=0;
ENEMAIL:
	if(EnterEMail(EMail)){
		int ES_result=0;
		ShowCentralMessage2(GetTextByID("WZR_SR0"),BOR2.GPID);
		FlipPages();
		gpProfileSearch(&LOGIN.gp,"",EMail,"","",0,GP_NON_BLOCKING,&E_Search,&ES_result);
		do{
			ProcessMessages();

		}while(ES_result==0);
		if(ES_result==3){
			WaitWithError("WZR_ERR4",BOR2.GPID);
			goto ENEMAIL;
		};
		if(ES_result==1){
REENPASS:
			int res=CreateNewAccount(EMail,Passw,&Store);
			if(res==2){
				strcpy(FIRSTNICK,EMail);
				char* cc=strchr(FIRSTNICK,'@');
				if(cc)cc[0]=0;
				res=EnterNewNick(FIRSTNICK);
				if(res==2){
					int RR=TestUNIQ(EMail,FIRSTNICK);
					if(RR==0)return false;
					if(RR==-1)goto ENEMAIL;
					//creating the new account
					LOGIN.Logged=0;
					LOGIN.ProfileID=0;
					LOGIN.Error=0;

					GPResult Res=gpConnectNewUser(&LOGIN.gp,FIRSTNICK,EMail,Passw,GP_FIREWALL,GP_NON_BLOCKING,&Create_account,&LOGIN);
					if(Res!=GP_NO_ERROR){
						WaitWithError("WZR_ERR1",BOR2.GPID);
						goto ENEMAIL;
					}else{
						ShowCentralMessage2(GetTextByID("WZR_W0"),BOR2.GPID);
						FlipPages();
						do{
							ProcessMessages();
						}while(!(LOGIN.Error||LOGIN.ProfileID));
						if(LOGIN.Error){
							WaitWithError("WZR_ERR1",BOR2.GPID);
							goto ENEMAIL;
						}else{
							if(!InitUser(LOGIN.ProfileID,Passw)){
								//WaitWithError("WZR_LOGFAIL",BOR2.GPID);
								//LoginError(BOR2.GPID);
								goto ENEMAIL;
							};
							CheckExistingSaves();
							strcpy(LOGIN.EMail,EMail);
							strcpy(LOGIN.Nick,FIRSTNICK);
							strcpy(LOGIN.Password,Passw);
							strcpy(PlName,FIRSTNICK);
							CurProfileID=LOGIN.ProfileID;
							ProcessPlayerInfo(CurProfileID,RR==2);
							//SendPlayerRequest(LOGIN.Nick,LOGIN.EMail);
							return true;
						};
					};
				}else if(res==1)goto REENPASS;
				else return false;
			}else if(res==1)goto ENEMAIL;
			else return false;
		}else{
			bool First=1;
			do{
				int res=EnterAccountPassword(Passw,First,EMail);
				if(res==2){
					ShowCentralMessage2(GetTextByID("WZR_SR1"),BOR2.GPID);
					FlipPages();
					GPResult Res=gpConnect(&LOGIN.gp,FIRSTNICK,EMail,Passw,GP_FIREWALL,GP_NON_BLOCKING,&Conn_callback,&LOGIN);
					LOGIN.Logged=0;
					LOGIN.Error=0;
					int Lt0=GetTickCount();
					do{
						if(GetTickCount()-Lt0>60000)LOGIN.Error=1;
						ProcessMessages();
					}while(!(LOGIN.Logged||LOGIN.Error||Res!=GP_NO_ERROR));
					if(LOGIN.Error||Res!=GP_NO_ERROR){
						First=0;
					};
				}else if(res==1)goto ENEMAIL;
				else return false;
			}while(LOGIN.Error);
SELPROF:
			int res=SelectProfile(EMail,FIRSTNICK);
			bool UNICAL=0;
			if(res==2){
				int rr=TestUNIQ(EMail,FIRSTNICK);
				if(rr==2)UNICAL=1;
				if(rr==-1)goto SELPROF;
				if(rr==0)return 0;
				//create the new profile
				LOGIN.Logged=0;
				LOGIN.ProfileID=0;
				LOGIN.Error=0;
				GPResult Res=gpNewProfile(&LOGIN.gp,FIRSTNICK,GP_DONT_REPLACE,GP_NON_BLOCKING,&New_profile,&LOGIN);
				if(Res!=GP_NO_ERROR){
					WaitWithError("WZR_ERR1",BOR2.GPID);
					goto ENEMAIL;
				}else{
					ShowCentralMessage2(GetTextByID("WZR_W1"),BOR2.GPID);
					FlipPages();
					do{
						ProcessMessages();
					}while(!(LOGIN.Logged||LOGIN.Error));
					if(!LOGIN.Logged){
						WaitWithError("WZR_ERR2",BOR2.GPID);
						goto ENEMAIL;	
					}else{
						gpDisconnect(&LOGIN.gp);
						LOGIN.Logged=0;
						LOGIN.Error=0;
						LOGIN.ProfileID=0;
						ShowCentralMessage2(GetTextByID("WZR_LOGIN0"),BOR2.GPID);
						FlipPages();
						GPResult Res=gpConnect(&LOGIN.gp,FIRSTNICK,EMail,Passw,GP_FIREWALL,GP_NON_BLOCKING,&Conn_callback,&LOGIN);
						if(Res!=GP_NO_ERROR){
							//WaitWithError("WZR_ERR3",BOR2.GPID);
							LoginError(BOR2.GPID);
							goto ENEMAIL;
						}else{
							int Lt0=GetTickCount();
							do{
								if(GetTickCount()-Lt0>60000)LOGIN.Error=1;
								ProcessMessages();
							}while(!(LOGIN.Logged||LOGIN.Error));
							if(LOGIN.Error){
								WaitWithError("WZR_ERR3",BOR2.GPID);
								goto ENEMAIL;
							}else{
								if(!InitUser(LOGIN.ProfileID,Passw)){
									//WaitWithError("WZR_LOGFAIL",BOR2.GPID);
									goto ENEMAIL;
								};
								CheckExistingSaves();
								strcpy(LOGIN.EMail,EMail);
								strcpy(LOGIN.Nick,FIRSTNICK);
								strcpy(LOGIN.Password,Passw);
								strcpy(PlName,LOGIN.Nick);
								CurProfileID=LOGIN.ProfileID;
								ProcessPlayerInfo(LOGIN.ProfileID,UNICAL);
								//SendPlayerRequest(LOGIN.Nick,LOGIN.EMail);
								return true;
							};
						};
						return true;
					};

				};
			}else if(res==3){
				//using the existing profile
				gpDisconnect(&LOGIN.gp);

				int rr=TestUNIQ(EMail,FIRSTNICK);
				if(rr==2)UNICAL=1;
				if(rr==-1)goto SELPROF;
				if(rr==0)return 0;

				LOGIN.Logged=0;
				LOGIN.Error=0;
				LOGIN.ProfileID=0;
				ShowCentralMessage2(GetTextByID("WZR_LOGIN0"),BOR2.GPID);
				FlipPages();
				GPResult Res=gpConnect(&LOGIN.gp,FIRSTNICK,EMail,Passw,GP_FIREWALL,GP_NON_BLOCKING,&Conn_callback,&LOGIN);
				if(Res!=GP_NO_ERROR){
					//WaitWithError("WZR_ERR3",BOR2.GPID);
					LoginError(BOR2.GPID);
					goto ENEMAIL;
				}else{
					int Lt0=GetTickCount();
					do{
						if(GetTickCount()-Lt0>60000)LOGIN.Error=1;
						ProcessMessages();
					}while(!(LOGIN.Logged||LOGIN.Error));
					if(LOGIN.Error){
						//WaitWithError("WZR_ERR3",BOR2.GPID);
						LoginError(BOR2.GPID);
						goto ENEMAIL;
					}else{
						if(!InitUser(LOGIN.ProfileID,Passw)){
							//WaitWithError("WZR_LOGFAIL",BOR2.GPID);
							//LoginError(BOR2.GPID);
							goto ENEMAIL;
						};
						CheckExistingSaves();
						strcpy(LOGIN.EMail,EMail);
						strcpy(LOGIN.Nick,FIRSTNICK);
						strcpy(LOGIN.Password,Passw);
						strcpy(PlName,LOGIN.Nick);
						CurProfileID=LOGIN.ProfileID;
						ProcessPlayerInfo(LOGIN.ProfileID,UNICAL);
						//SendPlayerRequest(LOGIN.Nick,LOGIN.EMail);
						return true;
					};
				};
			};
		};
		return false;
	};		
	return false;
};
void ProcessLogin(){
	if(LOGIN.gp)gpProcess(&LOGIN.gp);
};
void GETPROFINFO(int ProfileID){

};
bool ProcessPlayerForm(GPGetInfoResponseArg* INFO){
	DialogsSystem DSS(0,0);
	SQPicture BACK("Interface\\Background_Internet_Form.bmp");
	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	LocalGP BTNS2("Interface\\PlayerForm");
	LocalGP SCROL("Interface\\_Slider");
	DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);
	GP_Button* OkBtn=DSS.addGP_Button(NULL,139,479,BTNS2.GPID,2,3);
	OkBtn->OnUserClick=&MMItemChoose;
	OkBtn->UserParam=mcmOk;
	GP_Button* CancelBtn=DSS.addGP_Button(NULL,327,479,BTNS2.GPID,0,1);
	CancelBtn->OnUserClick=&MMItemChoose;
	CancelBtn->UserParam=mcmCancel;

	DSS.addTextButton(NULL,266+9,268+2,INFO->nick,&YellowFont,&YellowFont,&YellowFont,0);
	ComboBox* COUNTRY=DSS.addGP_ComboBox(NULL,266,294,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VS1;
	COUNTRY->AssignScroll(&DSS,&VS1,SCROL.GPID,0,14);
	GFILE* F=Gopen("Players\\Countries.dat","r");
	if(F){
		char ccc[128];
		char CCN[16];
		ReadWinString(F,CCN+1,15);
		if(INFO->countrycode[0]){
			strcpy(CCN+1,INFO->countrycode);
			_strupr(CCN);
		};
		CCN[0]='=';
		do{
			ReadWinString(F,ccc,128);
			if(ccc[0]){
				if(strstr(ccc,CCN)){
					COUNTRY->CurLine=COUNTRY->NLines;
					COUNTRY->YPos=COUNTRY->CurLine;
				};
				char* cc=strchr(ccc,'=');
				if(cc)cc[0]=0;
				COUNTRY->AddLine(ccc);
			};
		}while(ccc[0]);
		Gclose(F);
	};
	if(COUNTRY->YPos+COUNTRY->MaxLY>COUNTRY->NLines)COUNTRY->YPos=COUNTRY->NLines-COUNTRY->MaxLY;
	VS1->SPos=COUNTRY->YPos*10;
	VS1->SMaxPos=(COUNTRY->NLines-COUNTRY->MaxLY)*10;
	ComboBox* DAY=DSS.addGP_ComboBoxDLX(NULL,266,320,57,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VS2;
	DAY->AssignScroll(&DSS,&VS2,SCROL.GPID,0,12);
	for(int i=1;i<32;i++){
		char cc[12];
		sprintf(cc,"%d",i);
		DAY->AddLine(cc);
	};
	ComboBox* MONTH=DSS.addGP_ComboBoxDLX(NULL,328,320,96,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VS3;
	MONTH->AssignScroll(&DSS,&VS3,SCROL.GPID,0,12);
	for(i=0;i<12;i++){
		char cc[12];
		sprintf(cc,"MONTH_%d",i);
		MONTH->AddLine(GetTextByID(cc));
	};
	ComboBox* YEAR=DSS.addGP_ComboBoxDLX(NULL,429,320,77,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	VScrollBar* VS4;
	YEAR->AssignScroll(&DSS,&VS4,SCROL.GPID,0,12);
	for(i=1900;i<2100;i++){
		char cc[12];
		sprintf(cc,"%d",i);
		YEAR->AddLine(cc);
	};
	if(INFO->birthyear<1900)INFO->birthyear=1900;
	if(INFO->birthyear>2099)INFO->birthyear=2099;
	if(INFO->birthmonth<1)INFO->birthmonth=1;
	if(INFO->birthmonth>12)INFO->birthmonth=12;
	if(INFO->birthday<1)INFO->birthday=1;
	if(INFO->birthday>31)INFO->birthday=31;
	DAY->CurLine=INFO->birthday-1;
	MONTH->CurLine=INFO->birthmonth-1;
	YEAR->CurLine=INFO->birthyear-1900;

	ComboBox* GENDER=DSS.addGP_ComboBox(NULL,266,346,BTNS.GPID,0,9,0,&WhiteFont,&YellowFont,NULL);
	GENDER->AddLine(GetTextByID("GEN_M"));
	GENDER->AddLine(GetTextByID("GEN_F"));
	GENDER->AddLine(GetTextByID("GEN_U"));
	if(INFO->sex==GP_MALE)GENDER->CurLine=0;
	else if(INFO->sex==GP_FEMALE)GENDER->CurLine=1;
	else GENDER->CurLine=2;
	
	char icq[32];
	DSS.addTextButton(NULL,266+9,372+2,INFO->email,&YellowFont,&YellowFont,&YellowFont,0);
	sprintf(icq,"%d",INFO->icquin);
	DSS.addGP_Button(NULL,266,398,BTNS.GPID,13,14);
	DSS.addInputBox(NULL,266,398,icq,20,230,22,&YellowFont,&WhiteFont);
	DSS.addGP_Button(NULL,266,398+26,BTNS.GPID,13,14);
	DSS.addInputBox(NULL,266,398+26,INFO->homepage,GP_HOMEPAGE_LEN-1,230,22,&YellowFont,&WhiteFont);
	ItemChoose=-1;
	do{
		ProcessMessages();
		DSS.ProcessDialogs();
		DSS.RefreshView();
	}while(ItemChoose==-1);
	if(ItemChoose==mcmOk){
		//1.Country
		char* cntr=COUNTRY->Lines[COUNTRY->CurLine];
		GFILE* F=Gopen("Players\\Countries.dat","r");
		if(F){
			char ccc[128];
			ReadWinString(F,ccc,15);
			do{	
				ReadWinString(F,ccc,128);
				if(ccc[0]){
					char* cc=strchr(ccc,'=');
					if(cc)cc[0]=0;
					if(!_stricmp(ccc,cntr)){
						strcpy(INFO->countrycode,cc+1);
					};
				};
			}while(ccc[0]);
			Gclose(F);
		};
		//birthday
		INFO->birthday=DAY->CurLine+1;
		INFO->birthmonth=MONTH->CurLine+1;
		INFO->birthyear=YEAR->CurLine+1900;
		//gender
		switch(GENDER->CurLine){
		case 0:
			INFO->sex=GP_MALE;
			break;
		case 1:
			INFO->sex=GP_FEMALE;
			break;
		case 2:
			INFO->sex=GP_PAT;
			break;
		};
		//icq
		INFO->icquin=atoi(icq);
		return true;
	}else return false;
};
bool GPI_Answer=0;
void GPI_callback(GPConnection* gp,void* arg,void* par){
	INSIDE4=7;
	DOTRACE;
	GPGetInfoResponseArg* GIRA=(GPGetInfoResponseArg*)arg;
	GPGetInfoResponseArg* GPI=(GPGetInfoResponseArg*)par;
	*GPI=*GIRA;
	GPI_Answer=1;
	DOTRACE;
	INSIDE4=8;
};
void ProcessPlayerInfo(int ProfileID,int UNICAL){
	GPI_Answer=0;
	GPGetInfoResponseArg GPI;
	GPResult Res=gpGetInfo(&LOGIN.gp,ProfileID,GP_DONT_CHECK_CACHE,GP_NON_BLOCKING,&GPI_callback,&GPI);
	if(Res==GP_NO_ERROR){
		do{
			ProcessMessages();
		}while(!GPI_Answer);
		if(GPI.result==GP_NO_ERROR){
			//GPGetInfoResponseArg GPI2=GPI;
			if(UNICAL==1){
				MakeUniqLastName(GPI.email,GPI.nick,GPI.lastname);
				gpSetInfos(&LOGIN.gp,GP_LASTNAME,GPI.lastname);
				gpProcess(&LOGIN.gp);
			};
			if(ProcessPlayerForm(&GPI)){
				gpSetInfos(&LOGIN.gp,GP_COUNTRYCODE,GPI.countrycode);
				gpProcess(&LOGIN.gp);
				gpSetInfoi(&LOGIN.gp,GP_SEX,GPI.sex);
				gpProcess(&LOGIN.gp);
				gpSetInfod(&LOGIN.gp,GP_BIRTHDAY,GPI.birthday,GPI.birthmonth,GPI.birthyear);
				gpProcess(&LOGIN.gp);
				gpSetInfoi(&LOGIN.gp,GP_ICQUIN,GPI.icquin);
				gpProcess(&LOGIN.gp);
				gpSetInfos(&LOGIN.gp,GP_HOMEPAGE,GPI.homepage);
				gpProcess(&LOGIN.gp);
			};
			gpSetInfoMask(&LOGIN.gp,GP_MASK_ALL);
		};
	};
};
struct SRRESULT{
	bool NOTUNICAL;
	bool FINAL;
	bool Error;
	char* email;
};
bool CheckUNIQ(char* email,char* Nick,char* LastName);
void UNIQ_callback(GPConnection* gp,void* arg,void* par){
	INSIDE4=9;
	DOTRACE;
	GPProfileSearchResponseArg* RES=(GPProfileSearchResponseArg*)arg;
	SRRESULT* SUNI=(SRRESULT*)par;
	if(RES->result==GP_NO_ERROR){
		for(int i=0;i<RES->numMatches;i++)if(_stricmp(RES->matches[i].email,SUNI->email)){
			if(CheckUNIQ(RES->matches[i].email,RES->matches[i].nick,RES->matches[i].lastname)){
				SUNI->NOTUNICAL=1;
			};
		};
		if(RES->more==GP_DONE)SUNI->FINAL=1;
	}else SUNI->Error=1;
	INSIDE4=10;
	DOTRACE;
};
int CheckForOriginalName(char* email,char* Nick){
	SRRESULT SUNI;
	SUNI.email=email;
	SUNI.FINAL=0;
	SUNI.Error=0;
	SUNI.NOTUNICAL=0;
	LocalGP BOR2("Interface\\BOR2");
	ShowCentralMessage2(GetTextByID("UNIQ_CH0"),BOR2.GPID);
	GPResult Res=gpProfileSearch(&LOGIN.gp,Nick,"","","",0,GP_NON_BLOCKING,&UNIQ_callback,&SUNI);
	if(Res!=GP_NO_ERROR)return 0;
	do{
		ProcessMessages();
	}while(!(SUNI.FINAL||SUNI.Error));
	if(SUNI.Error)return 0;
	if(SUNI.NOTUNICAL)return -1;
	return 1;
};
bool CheckUNIQ(char* email,char* Nick,char* LastName){
	char* ss=strstr(LastName,"~@~");
	if(ss){
		int v=0;
		int z=sscanf(ss+3,"%d",&v);
		if(z==1){
			int vv=0;
			char NICK[128];
			char EMAIL[128];
			strcpy(NICK,Nick);
			strcpy(EMAIL,email);
			_strupr(NICK);
			_strupr(EMAIL);
			int L1=strlen(Nick);
			int L2=strlen(email);
			if(L1&&L2){
				int N=L1*L2;
				for(int j=0;j<N;j++)vv=vv+EMAIL[j%L2]*NICK[j%L1];
				vv^=0x543819FA;
				vv=abs(vv);
				if(vv==v)return true;
			};
			return false;
		}else return false;
	}else return false;
};
void MakeUniqLastName(char* email,char* Nick,char* LastName){
	char* ss=strstr(LastName,"~@~");
	if(ss)ss[0]=0;
	int vv=0;
	char NICK[128];
	char EMAIL[128];
	strcpy(NICK,Nick);
	strcpy(EMAIL,email);
	_strupr(NICK);
	_strupr(EMAIL);
	int L1=strlen(Nick);
	int L2=strlen(email);
	if(L1&&L2){
		int N=L1*L2;
		for(int j=0;j<N;j++)vv=vv+EMAIL[j%L2]*NICK[j%L1];
		vv^=0x543819FA;
		vv=abs(vv);
		LastName[15]=0;
		strcat(LastName,"~@~");
		sprintf(LastName+strlen(LastName),"%d",vv);
	};
};
//-1 -back,0-cancel,1-use it ,2-use it like original
int TestUNIQ(char* email,char* Nick){
	LocalGP BOR2("Interface\\BOR2");
	int r=CheckForOriginalName(email,Nick);
	if(r==0){
		//WaitWithError(GetTextByID("WZR_ERR4"),BOR2.GPID);
		LoginError(BOR2.GPID);
		return -1;
	};
	if(r==-1){
		DialogsSystem DSS(0,0);
		SQPicture BACK("Interface\\Background_Wizard.bmp");
		LocalGP WBT("Interface\\LogWizard");
		LocalGP BTNS("Interface\\Login");
		LocalGP SCROL("Interface\\_Slider");
		DSS.addPicture(NULL,0,0,&BACK,&BACK,&BACK);		
		//-----------------------
		LocalGP B2("Interface\\bor2");
		int CR[8]={8,9,2,3,4,5,10,7};
		DSS.addCustomBorder(65,181,570,512,B2.GPID,CR,CR,11,11);
		DSS.addGPPicture(NULL,78,516,B2.GPID,14);
		DSS.addGPPicture(NULL,78+247-90,516,B2.GPID,14);
		DSS.addGPPicture(NULL,78+406-90,516,B2.GPID,14);
		//-----------------------

		GP_Button* Prev=DSS.addGP_Button(NULL,90,536,WBT.GPID,4,5);
		Prev->OnUserClick=&MMItemChoose;
		Prev->UserParam=1;

		GP_Button* Cancel=DSS.addGP_Button(NULL,247,536,WBT.GPID,0,1);
		Cancel->OnUserClick=&MMItemChoose;
		Cancel->UserParam=mcmCancel;

		GP_Button* Next=DSS.addGP_Button(NULL,406,536,WBT.GPID,2,3);
		Next->OnUserClick=&MMItemChoose;
		Next->UserParam=2;


		DSS.addTextButton(NULL,76,188,GetTextByID("UNIQ_L0"),&YellowFont,&YellowFont,&YellowFont,0);
		char* tmp=GetTextByID("UNIQ_L1");
		FILE* F=fopen("tmp.txt","w");
		if(F){
			fprintf(F,"%s",tmp);
			fclose(F);
		};
		TextViewer* TV=DSS.addTextViewer(NULL,87,219+5,452,300,"tmp.txt",&YellowFont);
		TV->SymSize=26;
		ItemChoose=-1;
		do{
			ProcessMessages();
			DSS.ProcessDialogs();
			DSS.RefreshView();
		}while(ItemChoose==-1);
		if(ItemChoose==2)return 1;
		if(ItemChoose==1)return -1;
		return 0;
	}else return 2;
};
void MarkNameLikeUnical(int,bool);
GPGetInfoResponseArg GR1;
void GPI_callback2(GPConnection* gp,void* arg,void* par){
	INSIDE4=11;
	DOTRACE;
	GPGetInfoResponseArg* GIRA=(GPGetInfoResponseArg*)arg;
	GR1=*GIRA;
	if(GIRA->result==GP_NO_ERROR){
		if(CheckUNIQ(GIRA->email,GIRA->nick,GIRA->lastname)){
			MarkNameLikeUnical(GIRA->profile,true);
		}else MarkNameLikeUnical(GIRA->profile,false);
	};
	INSIDE4=12;
	DOTRACE;
};
void CheckOriginalNick(int ProfileID){
	if(!LOGIN.Logged)return;
	if(ProfileID)GPResult Res=gpGetInfo(&LOGIN.gp,ProfileID,GP_DONT_CHECK_CACHE,GP_NON_BLOCKING,&GPI_callback2,NULL);
};
//----------------------Personal user data--------------------//
struct OneRatedPlayer{
	byte Rank;
	byte State;
	byte Mask;
	byte Color;
	byte NationID;
	int  Profile;
	int  Score;
	char Nick[32];
	word MaxScore;
	word MaxPopul;
	byte ScoreG[32];
	byte Popul[32];
};
struct SysTime{
	word Year;
	word Month;
	word Day;
	word DayOfWeek;
	word Hour;
	word Min;
};
class CurrentGame{
public:
	bool Active;
	char GameName[128];
	char MapName[128];
	int  ProfileID;
	char Nick[64];
	char InGameNick[64];
	char password[64];
	char email[127];
	bool Broken;
	bool Finished;
	
	SysTime StartTime;
	SysTime LastLoadTime;
	SysTime CurTime;

	int PlayingTime;
	int  NPL;
	byte GameType;
	OneRatedPlayer PLAYERS[8];
//-----------------------------//
	void CreateGame(
		char* GameName,
		char* Map,
		char* Nick
		);
	void UpdateGame();
	void SaveGameToFile();
	void LoadGameFromFile();
	void DeleteThisGameFromFile();
	bool UpdateGlobalInfo();
	void AssignVictory(char* Nick);
	void AssignDefeat(char* Nick);
	void AssignKick(char* Nick);
	int GetAddScore();
};
extern word NPlayers;
extern City CITY[8];
extern DWORD MyDPID;
int SortPlayers(byte* Res,int* par);
void CurrentGame::CreateGame(char* pGameName,char* pMap,char* pNick){
	if(LOGIN.ProfileID){
		if(strstr(pMap,".sav")||strstr(pMap,".SAV"))return;
		Active=true;
		strcpy(GameName,pGameName);
		strcpy(MapName,pMap);
		strcpy(Nick,pNick);
		strcpy(password,LOGIN.Password);
		strcpy(email,LOGIN.EMail);
		ProfileID=LOGIN.ProfileID;
		NPL=NPlayers;
		GameType=PINFO[0].VictCond;
		strcpy(InGameNick,pNick);
		Finished=0;
		Broken=0;
		
		byte ord[8];
		int  par[8];
		int no=SortPlayers(ord,par);
		byte prevms=0;
		int CurTm=0;
		if(no){
			for(int q=0;q<no;q++){
				byte ms=NATIONS[NatRefTBL[ord[q]]].NMask;
				if(NATIONS[NatRefTBL[ord[q]]].AI_Enabled){
					Active=0;
					DeleteThisGameFromFile();
					return;
				};
				byte c=NatRefTBL[ord[q]];
				int v=ord[q];
				if(!(ms&prevms)){
					CurTm++;
				};
				int PIDIDX=-1;
				for(int w=0;w<NPlayers;w++)if(PINFO[w].ColorID==ord[q])PIDIDX=w;
				if(PIDIDX==-1){
					if(NATIONS[c].AI_Enabled){
						strcpy(PLAYERS[q].Nick,"Computer");
					}else{
						strcpy(PLAYERS[q].Nick,"???");
					};
					PLAYERS[q].Rank=0;
				}else{
					strcpy(PLAYERS[q].Nick,PINFO[PIDIDX].name);
					PLAYERS[q].Rank=PINFO[PIDIDX].Rank;
					PLAYERS[q].Profile=PINFO[PIDIDX].ProfileID;
				};
				PLAYERS[q].Mask=NATIONS[c].NMask;
				PLAYERS[q].Color=c;
				PLAYERS[q].State=3;
				PLAYERS[q].Score=CITY[c].Account;
				//determining the nation
				int NID=255;
				
				for(int j=0;j<MAXOBJECT;j++){
					OneObject* OB=Group[j];
					if(OB&&OB->NNUM==c&&OB->newMons->Peasant&&!OB->Sdoxlo){
						NID=OB->Ref.General->NatID;
					};
				};
				PLAYERS[q].NationID=NID;
				if(PINFO[q].PlayerID==MyDPID){
					strcpy(InGameNick,PINFO[q].name);
				};
				memset(PLAYERS[q].Popul,0,sizeof PLAYERS[q].Popul);
				memset(PLAYERS[q].ScoreG,0,sizeof PLAYERS[q].ScoreG);
				PLAYERS[q].MaxScore=0;
				PLAYERS[q].MaxPopul=0;
			};
			NPL=no;
		};
		SYSTEMTIME SYSTM;
		GetSystemTime(&SYSTM);
		StartTime.Year=SYSTM.wYear;
		StartTime.Month=SYSTM.wMonth;
		StartTime.Day=SYSTM.wDay;
		StartTime.Hour=SYSTM.wHour;
		StartTime.Min=SYSTM.wMinute;
		StartTime.DayOfWeek=SYSTM.wDayOfWeek;
		memcpy(&LastLoadTime,&StartTime,sizeof StartTime);
		memcpy(&CurTime,&StartTime,sizeof StartTime);
		//CurTime=StartTime;
		PlayingTime=0;
		SaveGameToFile();
	}else{
		Active=false;
	};
};
extern int GameTime;
void CurrentGame::UpdateGame(){
	if(Active){
		/*
		GetSystemTime(&SYSTM);
		CurTime.Year=SYSTM.wYear;
		CurTime.Month=SYSTM.wMonth;
		CurTime.Day=SYSTM.wDay;
		CurTime.Hour=SYSTM.wHour;
		CurTime.Min=SYSTM.wMinute;
		CurTime.DayOfWeek=SYSTM.wDayOfWeek;
		*/
		PlayingTime=GameTime;
		byte ord[8];
		int  par[8];
		int no=SortPlayers(ord,par);
		byte prevms=0;
		int CurTm=0;
		SYSTEMTIME SYSTM;
		GetSystemTime(&SYSTM);
		CurTime.Year=SYSTM.wYear;
		CurTime.Month=SYSTM.wMonth;
		CurTime.Day=SYSTM.wDay;
		CurTime.Hour=SYSTM.wHour;
		CurTime.Min=SYSTM.wMinute;
		CurTime.DayOfWeek=SYSTM.wDayOfWeek;
		
		if(no){
			for(int q=0;q<no;q++){
				byte ms=NATIONS[NatRefTBL[ord[q]]].NMask;
				if(NATIONS[NatRefTBL[ord[q]]].AI_Enabled){
					Active=0;
					DeleteThisGameFromFile();
					return;
				};
				byte c=NatRefTBL[ord[q]];
				int v=ord[q];
				if(!(ms&prevms)){
					CurTm++;
				};
				int PIDIDX=-1;
				for(int w=0;w<NPlayers;w++)if(PINFO[w].ColorID==ord[q])PIDIDX=w;
				if(PIDIDX==-1){
					if(NATIONS[c].AI_Enabled){
						strcpy(PLAYERS[q].Nick,"Computer");
					}else{
						strcpy(PLAYERS[q].Nick,"???");
					};
					PLAYERS[q].Rank=0;
				}else{
					strcpy(PLAYERS[q].Nick,PINFO[PIDIDX].name);
					PLAYERS[q].Rank=PINFO[PIDIDX].Rank;
					PLAYERS[q].Profile=PINFO[PIDIDX].ProfileID;
				};
				PLAYERS[q].Mask=NATIONS[c].NMask;
				PLAYERS[q].Color=c;
				PLAYERS[q].State=3;
				if(CITY[c].Account>=0)PLAYERS[q].Score=CITY[c].Account;
				else PLAYERS[q].Score=0;

				//determining the nation
				int NID=255;
				
				for(int j=0;j<MAXOBJECT;j++){
					OneObject* OB=Group[j];
					if(OB&&OB->NNUM==c&&OB->newMons->Peasant&&!OB->Sdoxlo){
						NID=OB->Ref.General->NatID;
					};
				};
				PLAYERS[q].NationID=NID;
				if(PINFO[q].PlayerID==MyDPID){
					strcpy(InGameNick,PINFO[q].name);
				};

				memset(PLAYERS[q].Popul,0,sizeof PLAYERS[q].Popul);
				memset(PLAYERS[q].ScoreG,0,sizeof PLAYERS[q].ScoreG);

				if(NATIONS[c].NAccount>1){
					int NN=NATIONS[c].NAccount-1;
					int MaxP=1;
					for(int i=0;i<NN;i++){
						int v=NATIONS[c].Account[i];
						if(v>MaxP)MaxP=v;
					};
					for(i=0;i<32;i++){
						PLAYERS[q].ScoreG[i]=(NATIONS[c].Account[(NN*i)/31]*100)/MaxP;
					};
					PLAYERS[q].MaxScore=MaxP;
				};
				if(NATIONS[c].NPopul>1){
					int NN=NATIONS[c].NPopul-1;
					int MaxP=1;
					for(int i=0;i<NN;i++){
						int v=NATIONS[c].Popul[i];
						if(v>MaxP)MaxP=v;
					};
					for(i=0;i<32;i++){
						PLAYERS[q].Popul[i]=(NATIONS[c].Popul[(NN*i)/31]*100)/MaxP;
					};
					PLAYERS[q].MaxPopul=MaxP;
				};
			};
			NPL=no;
		};
		SaveGameToFile();
	};
};
void CurrentGame::AssignVictory(char* Nick){
	byte MyMask=0;
	for(int i=0;i<NPL;i++)if(!strcmp(PLAYERS[i].Nick,Nick)){
		PLAYERS[i].State=0;
		MyMask=PLAYERS[i].Mask;
	};
	for(i=0;i<NPL;i++)if(PLAYERS[i].State!=1&&PLAYERS[i].Mask&MyMask){
		PLAYERS[i].State=0;
	}else{
		PLAYERS[i].State=1;
	};
	if(!Broken)Finished=1;
};
void CurrentGame::AssignDefeat(char* Nick){
	bool ALLMYLOOSE=1;
	byte MyMask=0;
	for(int i=0;i<NPL;i++)if(!strcmp(PLAYERS[i].Nick,Nick)){
		PLAYERS[i].State=1;
		MyMask=PLAYERS[i].Mask;
	};
	if(MyMask){
		byte HimMask1=0;
		byte HimMask2=0;
		for(int i=0;i<NPL;i++){
			if(PLAYERS[i].Mask&MyMask){
				if(PLAYERS[i].State!=1)ALLMYLOOSE=0;
			}else{
				if(HimMask1){
					if(!(PLAYERS[i].Mask&HimMask1))HimMask2=PLAYERS[i].Mask;
				}else{
					HimMask1=PLAYERS[i].Mask;
				};
			};
		};
		if(ALLMYLOOSE&&!HimMask2){
			for(int i=0;i<NPL;i++)if(PLAYERS[i].State!=1&&!(PLAYERS[i].Mask&MyMask)){
				PLAYERS[i].State=0;
			};
		};
	};
	if(!Broken)Finished=1;
};
void CurrentGame::AssignKick(char* Nick){
	for(int i=0;i<NPL;i++)if(!strcmp(PLAYERS[i].Nick,Nick)){
		PLAYERS[i].State=2;
	};
};
void SetNormAttr();
void CurrentGame::SaveGameToFile(){
	if(!Active)return;
	char ccc[100];
	int t0=(StartTime.Min+StartTime.Hour*60)%200;
	ResFile F1=RReset("cew.dll");
	if(F1==INVALID_HANDLE_VALUE)return;
	RSeek(F1,20532+t0);
	int v=1;
	RBlockWrite(F1,&v,1);
	RSeek(F1,20532+200+t0*(sizeof(CurrentGame)+4));
	CurrentGame XXX;
	XXX=*this;
	byte* DATA=(byte*)(&XXX);
	byte* Key=(byte*)randoma;
	for(int i=0;i<sizeof XXX;i++)DATA[i]^=Key[i];
	RBlockWrite(F1,&XXX,sizeof XXX);
	int S=0;
	for(i=0;i<sizeof CurrentGame;i++)S+=DATA[i];
	RBlockWrite(F1,&S,4);
	RClose(F1);
	SetNormAttr();
};
void CurrentGame::LoadGameFromFile(){
	ResFile F=RReset("cew.dll");
	if(F==INVALID_HANDLE_VALUE)return;
	RSeek(F,20532);
	int cur=0;
	int sz=0;
	int t=GetTickCount()&4096;
	for(int p=0;p<t;p++)rand();
	int NMAX=0;
	byte HEADR[200];
	RBlockRead(F,HEADR,200);
NEXTFILE:
	bool SUCCESS=0;
	do{
		cur=rand()%200;
		SUCCESS=HEADR[cur];
		NMAX++;
	}while((!SUCCESS)&&NMAX<5000);
	//ResFile F=RReset("Players\\INGP.DLL");
	if(SUCCESS){
		RSeek(F,20532+200+cur*(sizeof(CurrentGame)+4));
		RBlockRead(F,this,sizeof CurrentGame);
		int S;
		RBlockRead(F,&S,4);
		byte* Key=(byte*)randoma;
		byte* xx=(byte*)this;
		int S1=0;
		for(int i=0;i<sizeof CurrentGame;i++)S1+=xx[i];
		if(S!=S1)Active=false;
		else{
			for(int i=0;i<sizeof CurrentGame;i++)xx[i]^=Key[i];
		};
		if(!Finished){
			//checking the start time
			SYSTEMTIME ST;
			GetSystemTime(&ST);
			FILETIME FT;
			SystemTimeToFileTime(&ST,&FT);
			SYSTEMTIME ST0;
			memset(&ST0,0,sizeof ST0);
			ST0.wMinute=StartTime.Min;
			ST0.wHour=StartTime.Hour;
			ST0.wDay=StartTime.Day;
			ST0.wMonth=StartTime.Month;
			ST0.wYear=StartTime.Year;
			FILETIME FT0;
			SystemTimeToFileTime(&ST0,&FT0);
			LARGE_INTEGER LI0;
			LARGE_INTEGER LI;
			memcpy(&LI0,&FT0,8);
			memcpy(&LI,&FT,8);
			LI.QuadPart-=LI0.QuadPart;
			memcpy(&FT,&LI,8);
			int dt=10000000;
			if(FileTimeToSystemTime(&FT,&ST)){
				dt=(ST.wDay-1)*24+ST.wHour;
			};
			if(dt<24){//!!!!!!!!!
				RClose(F);
				Active=0;
				F=INVALID_HANDLE_VALUE;
				goto NEXTFILE;
			};
		};
	}else Active=false;
	RClose(F);
	SetNormAttr();
};
void CurrentGame::DeleteThisGameFromFile(){
	int cur=0;
	int sz=0;
	char ccc[100];
	ResFile F=RReset("cew.dll");
	if(F==INVALID_HANDLE_VALUE)return;
	int t0=(StartTime.Min+StartTime.Hour*60)%200;
	RSeek(F,20532+t0);
	int v=0;
	RBlockWrite(F,&v,1);
	RClose(F);
	SetNormAttr();
};
struct OneIChunk{
	byte Index;
	word size;
	word Summ;
	byte Data[64];
};
struct CurUpload{
	bool Authenticated:1;
	bool Started:1;
	bool Finished:1;
	bool Error:1;
	bool DataSent:1;
	int  CurProfile;
	int  CurPage;
};
struct CurDownload{
	bool Started;
	bool Finished;
	bool Error;
	int  CurProfile;
	int  CurPage;
};
class InternetStatsChunks{
public:
	int CurIndex;
	bool Ready;
	bool Error;
	int N;
	OneIChunk** Chunks;
	CurDownload CDOWN;
	CurUpload CUPLD;

	InternetStatsChunks();
	void Init();
	void Clear();
	int ReadChunkFrom(byte* Sourse);
	void WriteChunk(byte* Src,int L,byte Type);
	bool Upload(int ProfileID,char* Password,int Page);
	bool Download(int ProfileID,int Page);
	//----downloading process----//
	void StartDownload(int ProfileID,int Page);
	void ProcessDownload();
	void StartUpload(int ProfileID,char* Password,int Page);
	void ProcessUpload();
};
InternetStatsChunks::InternetStatsChunks(){
	Init();
};

void InternetStatsChunks::Init(){
	N=0;
	CurIndex=0;
	Chunks=NULL;
};
void InternetStatsChunks::Clear(){
	for(int i=0;i<N;i++)free(Chunks[i]);
	if(Chunks)free(Chunks);
	Chunks=NULL;
	N=0;
};

bool ProfIsInit=0;
void InitProfileSystem(){
	//if(!LOGIN.Logged){
	//	ProfIsInit=0;
	//	return;
	//};
	gcd_gamename[0]='g';gcd_gamename[1]='m';gcd_gamename[2]='t';gcd_gamename[3]='e';
	gcd_gamename[4]='s';gcd_gamename[5]='t';gcd_gamename[6]='\0';
	gcd_secret_key[0]='H';gcd_secret_key[1]='A';gcd_secret_key[2]='6';gcd_secret_key[3]='z';
	gcd_secret_key[4]='k';gcd_secret_key[5]='S';gcd_secret_key[6]='\0';
	//strcpy(gcd_gamename,"cossacks");
	//strcpy(gcd_secret_key,"p2vPkJ");

	if(ProfIsInit)CloseStatsConnection();
	ProfIsInit=0;
	int result = InitStatsConnection(0);
	if (result == GE_NOERROR){
		ProfIsInit=1;
	}else{
		if(CurPalette==2){
			LocalGP BOR2("Interface\\Bor2");
			WaitWithError("DATASERVERR",BOR2.GPID);
		};
		//LoginError(BOR2.GPID);
	};
};
void GetData_callback(int localid, int profileid, persisttype_t type, 
					  int index, int success, char *data, int len, 
					  void *instance){
	INSIDE4=12;
	DOTRACE;
	InternetStatsChunks* ISS=(InternetStatsChunks*)instance;
	if(success){
		ISS->Ready=1;
		if(data[0]=='G'&&data[1]=='I'&&data[2]=='R'&&data[3]=='S'){
			//1. decoding
			for(int i=4;i<len;i++)data[i]^=randoma[(i+255)&8191];
			data+=4;
			//2. splitting links
			int pos=0;
			len-=4;
			do{
				word L=*((word*)(data+1+pos));
				word S=*((word*)(data+3+pos));
				if(pos+L<=len&&L){
					word S0=0;
					for(int j=0;j<L;j++)S0+=byte(data[pos+j+5]);
					if(S==S0){
						ISS->Chunks=(OneIChunk**)realloc(ISS->Chunks,4*ISS->N+4);
						ISS->Chunks[ISS->N]=(OneIChunk*)malloc(sizeof(OneIChunk)-64+L);
						memcpy(ISS->Chunks[ISS->N],data+pos,L+5);
						ISS->N++;
						pos+=L+5;
					}else pos++;
				}else pos++;
			}while(pos<len);
		};
		ISS->Ready=1;
	}else ISS->Error=1;
	INSIDE4=13;
	DOTRACE;
};

bool InternetStatsChunks::Download(int ProfileID,int Page){
	Clear();
	Ready=0;
	Error=0;
	GetPersistData(0,ProfileID,pd_public_rw,Page,&GetData_callback,this);
	int T0=GetTickCount();
	do{
		ProcessMessages();
		PersistThink();
		ActiveProcess();
		if(GetTickCount()-T0>50000)Error=1;
	}while(!(Error||Ready));
	return Ready;
};
void GetData_callback2(int localid, int profileid, persisttype_t type,
					  int index, int success, char *data, int len, 
					  void *instance){
	INSIDE4=14;
	DOTRACE;
	InternetStatsChunks* ISS=(InternetStatsChunks*)instance;
	if(profileid==ISS->CDOWN.CurProfile){
		GetData_callback(localid,profileid,type,index,success,data,len,instance);
		if(success){
			ISS->CDOWN.Error=0;
			ISS->CDOWN.Finished=1;
		}else{
			ISS->CDOWN.Error=1;
		};
	};
	INSIDE4=15;
	DOTRACE;
};
void InternetStatsChunks::StartDownload(int ProfileID,int Page){
	Clear();
	Ready=0;
	Error=0;
	CDOWN.CurProfile=ProfileID;
	CDOWN.Error=0;
	CDOWN.Finished=0;
	CDOWN.Started=1;
	CDOWN.CurPage=Page;
	GetPersistData(0,ProfileID,pd_public_rw,Page,&GetData_callback2,this);
};
void PersAuthCallback2(int localid, int profileid, int authenticated, 
					  char *errmsg, void *instance){
	INSIDE4=17;
	DOTRACE;
	InternetStatsChunks* ISC=(InternetStatsChunks*)instance;
	if(authenticated){
		ISC->CUPLD.Authenticated=1;
	}else ISC->CUPLD.Error=1;
	INSIDE4=18;
	DOTRACE;
};
void PersDataSaveCallback2(int localid, int profileid, persisttype_t type, 
						  int index, int success, void *instance){
	INSIDE4=19;
	DOTRACE;
	InternetStatsChunks* ISC=(InternetStatsChunks*)instance;
	if(success){
		ISC->CUPLD.Finished=1;
	}else ISC->CUPLD.Error=1;
	INSIDE4=20;
	DOTRACE;
};
void InternetStatsChunks::ProcessUpload(){
	ProcessMessages();
	PersistThink();
	ActiveProcess();
	if(CUPLD.Error)return;
	if(!CUPLD.Finished){
		if(CUPLD.Authenticated&&!CUPLD.DataSent){
			int GL=4;
			for(int j=0;j<N;j++)GL+=Chunks[j]->size+5;
			byte* GData=new byte[GL];
			GData[0]='G';
			GData[1]='I';
			GData[2]='R';
				GData[3]='S';
			int pos=4;
			for(j=0;j<N;j++){
				memcpy(GData+pos,Chunks[j],5+Chunks[j]->size);
				pos+=5+Chunks[j]->size;
			};
			for(j=4;j<GL;j++)GData[j]^=randoma[(j+255)&8191];
				SetPersistData(0,CUPLD.CurProfile,pd_public_rw,CUPLD.CurPage,(char*)GData,GL,PersDataSaveCallback2,this);
			free(GData);
			CUPLD.DataSent=1;
		};
	};
};
void PersDataSaveCallback(int localid, int profileid, persisttype_t type, 
						  int index, int success, void *instance){
	INSIDE4=21;
	DOTRACE;
	int* res=(int*)instance;
	if(success){
		*res=1;
	}else *res=0;
	INSIDE4=22;
	DOTRACE;
};
void InternetStatsChunks::StartUpload(int ProfileID,char* Password,int Page){
	char validate[33];
	GenerateAuth(GetChallenge(NULL),Password,validate);
	int res=-1;
	CUPLD.Authenticated=0;
	CUPLD.Error=0;
	CUPLD.CurProfile=ProfileID;
	CUPLD.CurPage=Page;
	CUPLD.Finished=0;
	CUPLD.Started=1;
	CUPLD.DataSent=0;
	PreAuthenticatePlayerPM(0,ProfileID,validate,PersAuthCallback2,this);
};

void InternetStatsChunks::ProcessDownload(){
	PersistThink();
};
void PersAuthCallback(int localid, int profileid, int authenticated, 
					  char *errmsg, void *instance){
	INSIDE4=24;
	DOTRACE;
	int* res=(int*)instance;
	if(authenticated){
		*res=1;
	}else *res=0;
	INSIDE4=25;
	DOTRACE;
};



bool InternetStatsChunks::Upload(int ProfileID,char* Password,int Page){
	char validate[33];
	GenerateAuth(GetChallenge(NULL),Password,validate);
	int res=-1;
	PreAuthenticatePlayerPM(0,ProfileID,validate,PersAuthCallback,&res);
	int T0=GetTickCount();
	do{
		ProcessMessages();
		PersistThink();
		ActiveProcess();
		if(GetTickCount()-T0>50000)res=0;
	}while(res==-1);
	T0=GetTickCount();
	if(res==1){
		res=-1;
		int GL=4;
		for(int j=0;j<N;j++)GL+=Chunks[j]->size+5;
		byte* GData=new byte[GL];
		GData[0]='G';
		GData[1]='I';
		GData[2]='R';
		GData[3]='S';
		int pos=4;
		for(j=0;j<N;j++){
			memcpy(GData+pos,Chunks[j],5+Chunks[j]->size);
			pos+=5+Chunks[j]->size;
		};
		for(j=4;j<GL;j++)GData[j]^=randoma[(j+255)&8191];
		SetPersistData(0,ProfileID,pd_public_rw,Page,(char*)GData,GL,PersDataSaveCallback,&res);
		free(GData);

		do{
			ProcessMessages();
			PersistThink();
			ActiveProcess();
			if(GetTickCount()-T0>50000)res=0;
		}while(res==-1);
		return res;
	}else return false;
};
void InternetStatsChunks::WriteChunk(byte* Src,int L,byte Type){
	if(!L)return;
	Chunks=(OneIChunk**)realloc(Chunks,4*N+4);
	Chunks[N]=(OneIChunk*)malloc(5+L);
	Chunks[N]->Index=Type;
	Chunks[N]->size=L;
	word S=0;
	for(int i=0;i<L;i++){
		S+=Src[i];
	};
	Chunks[N]->Summ=S;
	memcpy(Chunks[N]->Data,Src,L);
	N++;
};
void CheckProfileInit(){
	if(!ProfIsInit){
		InitProfileSystem();
	};
};
#define WRDT(tp,val) (*((tp*)(BUFF+bps)))=val;bps+=sizeof(tp);
/*
bool CurrentGame::UpdateGlobalInfo(){
	if(Active){
		if(!ProfIsInit){
			InitProfileSystem();
		};
		InternetStatsChunks ISC;
		if(ISC.Download(ProfileID,0)){
			int NREC=0;
			int NVict=0;
			int CURSCORE=0;
			for(int i=0;i<ISC.N;i++){
				if(ISC.Chunks[i]->Index==0){
					int w1=*((DWORD*)ISC.Chunks[i]->Data);
					int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
					int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
					int sco1=w1^DWORD(ProfileID);
					int sco2=w2^0xFB47E6C3;
					if(sco1==sco2){
						NREC=w3;
						NVict=w3;
						CURSCORE=sco1;
					};
				};
				if(ISC.Chunks[i]->Index==27){
					int w1=*((DWORD*)ISC.Chunks[i]->Data);
					int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
					int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
					int w4=*((DWORD*)(ISC.Chunks[i]->Data+12));
					int sco1=w1^DWORD(ProfileID);
					int sco2=w2^0xFB47E6C3;
					if(sco1==sco2){
						NREC=w3;
						NVict=w4;
						CURSCORE=sco1;
					};
				};
			};
			ISC.Clear();
			if(NREC&&(NREC%10!=0)){
				if(!ISC.Download(ProfileID,2+(NREC/10))){
					//unable to save results right now
					return false;
				};
			};
			byte BUFF[2048];
			int bps=0;

			SYSTEMTIME ST;
			ST.wDay=StartTime.Day;
			ST.wDayOfWeek=StartTime.DayOfWeek;
			ST.wHour=StartTime.Hour;
			ST.wMilliseconds=0;
			ST.wMinute=StartTime.Min;
			ST.wMonth=StartTime.Month;
			ST.wSecond=0;
			ST.wYear=StartTime.Year;
			FILETIME FT;
			SystemTimeToFileTime(&ST,&FT);

			SYSTEMTIME ST1;
			ST1.wDay=CurTime.Day;
			ST1.wDayOfWeek=CurTime.DayOfWeek;
			ST1.wHour=CurTime.Hour;
			ST1.wMilliseconds=0;
			ST1.wMinute=CurTime.Min;
			ST1.wMonth=CurTime.Month;
			ST1.wSecond=0;
			ST1.wYear=CurTime.Year;
			FILETIME FT1;
			SystemTimeToFileTime(&ST1,&FT1);

			FILETIME DT;
			LARGE_INTEGER LI1;
			LARGE_INTEGER LI2;
			LARGE_INTEGER LI3;
			memcpy(&LI1,&FT,8);
			memcpy(&LI2,&FT1,8);
			LI3.QuadPart=LI2.QuadPart-LI1.QuadPart;
			memcpy(&DT,&LI3,8);
			FileTimeToSystemTime(&DT,&ST);

			DWORD Date=StartTime.Min+StartTime.Hour*60+StartTime.Day*1440+
				StartTime.Month*44640+(StartTime.Year-2000)*535680;

			WRDT(DWORD,Date);
			WRDT(byte,NPL);
			Date=ST.wMinute+ST.wHour*60+(ST.wDay-1)*60*24;
			WRDT(word,Date);
			WRDT(byte,GameType);
			WRDT(byte,0);
			WRDT(byte,strlen(MapName));
			memcpy(BUFF+bps,MapName,strlen(MapName));
			bps+=strlen(MapName);
			WRDT(byte,strlen(GameName));
			memcpy(BUFF+bps,GameName,strlen(GameName));
			bps+=strlen(GameName);
			for(i=0;i<NPL;i++){
				WRDT(byte,PLAYERS[i].Rank);
				WRDT(byte,PLAYERS[i].State);
				WRDT(DWORD,PLAYERS[i].Score);
				WRDT(byte,PLAYERS[i].Mask);
				WRDT(byte,PLAYERS[i].Color);
				WRDT(byte,PLAYERS[i].NationID);
				WRDT(byte,PLAYERS[i].Reserved[0]);
				WRDT(byte,PLAYERS[i].Reserved[1]);
				WRDT(byte,PLAYERS[i].Reserved[2]);
				WRDT(byte,PLAYERS[i].Reserved[3]);
				WRDT(byte,strlen(PLAYERS[i].Nick));
				memcpy(BUFF+bps,PLAYERS[i].Nick,strlen(PLAYERS[i].Nick));
				bps+=strlen(PLAYERS[i].Nick);
			};
			ISC.WriteChunk(BUFF,bps,2);
			NREC++;
			int dsc=GetAddScore();
			CURSCORE+=dsc;
			if(dsc>0)
			ISC.Upload(ProfileID,password,2+(NREC/10));
			ISC.Clear();
			DWORD XX[4];
			XX[0]=CURSCORE^DWORD(ProfileID);
			XX[1]=CURSCORE^0xFB47E6C3;
			XX[2]=NREC;
			XX[3]=NVict;
			ISC.WriteChunk((byte*)XX,16,27);
			bool resx=ISC.Upload(ProfileID,password,0);
			//RewriteTop100(ProfileID,CURSCORE);
			return resx;
		};
	};
	return false;
};
*/
int GetRankByScore(int Score);

void EncodeGS_Password(char* pass,char* result){
	result[0]=strlen(pass);
	char cc3[512];
	strcpy(cc3,pass);
	do{
		strcat(cc3,pass);
	}while(strlen(cc3)<64);
	cc3[64]=0;
	for(int i=0;i<1024;i++){
		int v1=randoma[i+i]&511;
		int v2=randoma[i+i+1]&511;
		int vo1=v1>>3;
		int vo2=v2>>3;
		int p1=v1&7;
		int p2=v2&7;
		byte b1=cc3[vo1];
		byte b2=cc3[vo2];
		byte mb1=b1&(1<<p1);
		byte mb2=b2&(1<<p2);
		b1&=~(1<<p1);
		b2&=~(1<<p2);
		if(mb1)b2|=1<<p2;
		if(mb2)b1|=1<<p1;
		cc3[vo1]=b1;
		cc3[vo2]=b2;
	};
	memcpy(result+1,cc3,65);
};
void DecodeGS_Password(char* pass,char* result){
	byte Len=result[0];
	char* cc3=result+1;
	for(int i=1023;i>=0;i--){
		int v1=randoma[i+i]&511;
		int v2=randoma[i+i+1]&511;
		int vo1=v1>>3;
		int vo2=v2>>3;
		int p1=v1&7;
		int p2=v2&7;
		byte b1=cc3[vo1];
		byte b2=cc3[vo2];
		byte mb1=b1&(1<<p1);
		byte mb2=b2&(1<<p2);
		b1&=~(1<<p1);
		b2&=~(1<<p2);
		if(mb1)b2|=1<<p2;
		if(mb2)b1|=1<<p1;
		cc3[vo1]=b1;
		cc3[vo2]=b2;
	};
	pass[Len]=0;
	memcpy(pass,cc3,Len);
};

bool InitUser(int ProfileID,char* password){
	//if(!ProfIsInit){
	InitProfileSystem();
	if(!ProfIsInit)return false;
	//};
	InternetStatsChunks ISC;
	bool GETSCORE=0;
	if(!ISC.Download(ProfileID,0)){
		//need to create start data
		byte xx3[65];
		InternetStatsChunks ISC1;
		EncodeGS_Password(password,(char*)xx3);
		ISC1.WriteChunk(xx3,64,0);
		ISC1.Upload(ProfileID,password,1);

		char tmp_pass[128];
		DecodeGS_Password((char*)xx3,tmp_pass);

		DWORD XX[3];
		XX[0]=DWORD(ProfileID);
		XX[1]=0xFB47E6C3;
		XX[2]=0;
		ISC.WriteChunk((byte*)XX,12,0);
		return ISC.Upload(ProfileID,password,2)&&ISC.Upload(ProfileID,password,0);
	}else{
		//if(!((GetTickCount()>>8)&7)){
			byte xx3[65];
			InternetStatsChunks ISC1;
			EncodeGS_Password(password,(char*)xx3);
			ISC1.WriteChunk(xx3,64,0);
			ISC1.Upload(ProfileID,password,1);

			char tmp_pass[128];
			DecodeGS_Password(tmp_pass,(char*)xx3);
		//};
		LOGIN.Rank=0;
		int SCORE=0;
		for(int i=0;i<ISC.N;i++){
			if(ISC.Chunks[i]->Index==0||ISC.Chunks[i]->Index==27||ISC.Chunks[i]->Index==28){
				int w1=*((DWORD*)ISC.Chunks[i]->Data);
				int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
				int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
				int sco1=w1^DWORD(ProfileID);
				int sco2=w2^0xFB47E6C3;
				if(sco1==sco2){
					LOGIN.Rank=GetRankByScore(sco1);
					SCORE=sco1;
					GETSCORE=1;
				};
			};
		};
		//SCORE=19;
		/*
		if(GetKeyState(VK_CONTROL)&0x8000){
			SCORE=0;
			DWORD XX[3];
			XX[0]=SCORE^DWORD(ProfileID);
			XX[1]=SCORE^0xFB47E6C3;
			XX[2]=0;
			ISC.Clear();
			ISC.WriteChunk((byte*)XX,12,0);
			ISC.Upload(ProfileID,password,4);
			ISC.Upload(ProfileID,password,3);
			ISC.Upload(ProfileID,password,2);
			ISC.Upload(ProfileID,password,0);
		};
		*/
		
	};
	if(LOGIN.Logged&&LOGIN.ProfileID){
		if(!GETSCORE){
			int v1,v2,z;
			FILE* F=fopen("Internet\\prof.bak","r");
			if(F){
				do{
					z=fscanf(F,"%d%d",&v1,&v2);
					if(z==2){
						if(v1==LOGIN.ProfileID)LOGIN.Rank=v2;
					};
				}while(z==2);
				fclose(F);
			};
		};
		FILE* F=fopen("Internet\\prof.bak","a");
		fprintf(F,"%d %d\n",LOGIN.ProfileID,LOGIN.Rank);
		fclose(F);
	};

	return true;
};


CurrentGame CURIGAME;
void STARTIGAME(char* GameName,char* Map,char* Nick,DWORD G_GUID){
	if(LOGIN.ProfileID&&strstr(TPEN.HostMessage,"0017")){
		char ccc3[512];
		char cc2[20];
		sprintf(cc2,"%.8X",G_GUID);
		for(int j=0;j<8;j++)if(cc2[j]==' ')cc2[j]='0';
		sprintf(ccc3,"%s #GUID:%s",GameName,cc2);
		CURIGAME.CreateGame(ccc3,Map,Nick);
	};
};
int PREVUPDATETIME=0;
void UPDATEIGAME(){
	if(CURIGAME.Active){
		if((!PREVUPDATETIME)||(GetTickCount()-PREVUPDATETIME>60000)){
			CURIGAME.UpdateGame();
			PREVUPDATETIME=GetTickCount();
		};
	};
};
extern int ShowGameScreen;
void CheckExistingSaves();
void LOOSEIGAME(char* Nick){
	if(CURIGAME.Active){
		CURIGAME.UpdateGame();
		CURIGAME.AssignDefeat(Nick);
		CURIGAME.SaveGameToFile();
		ShowGameScreen=1;
		CheckExistingSaves();
		ShowGameScreen=0;
		CURIGAME.Active=0;
	};
};
void LOOSEANDEXITFAST(){
	if(CURIGAME.Active){
		for(int i=0;i<NPlayers;i++)if(PINFO[i].ColorID==MyNation){
			CURIGAME.UpdateGame();
			CURIGAME.AssignDefeat(PINFO[i].name);
			CURIGAME.SaveGameToFile();
			CURIGAME.Active=0;
		};
	};
};
void WINIGAME(char* Nick){
	if(CURIGAME.Active){
		CURIGAME.UpdateGame();
		CURIGAME.AssignVictory(Nick);
		CURIGAME.SaveGameToFile();
		ShowGameScreen=1;
		CheckExistingSaves();
		ShowGameScreen=0;
		CURIGAME.Active=0;
	};
};
void STARTIGAME(char* GameName,char* Map,char* Nick,DWORD G_GUID);
void UPDATEIGAME();
void LOOSEIGAME(char* Nick);
void WINIGAME(char* Nick);
char WinScoreTable[162]={
	5,-2,	10,-2,	20,-2,	30,-2,	40,-2,	50,-2,	60,-2,	70,-2,	80,-2,
	5,-2,	5,-2,	10,-2,	20,-2,	30,-2,	40,-2,	50,-2,	60,-2,	70,-2,
	5,-2,	5,-2,	5,-2,	10,-2,	20,-2,	30,-2,	40,-2,	50,-2,	60,-2,
	5,-2,	5,-2,	5,-2,	5,-2,	10,-2,	20,-2,	30,-2,	40,-2,	50,-2,
	5,-4,	5,-2,	5,-2,	5,-2,	5,-2,	10,-2,	20,-2,	30,-2,	40,-2,
	5,-6,	5,-4,	5,-2,	5,-2,	5,-2,	5,-2,	10,-2,	20,-2,	30,-2,
	5,-8,	5,-6,	5,-4,	5,-2,	5,-2,	5,-2,	5,-2,	10,-2,	20,-2,
	5,-16,	5,-8,	5,-6,	5,-4,	5,-2,	5,-2,	5,-2,	5,-2,	10,-2,
	5,-32,	5,-16,	5,-8,	5,-6,	5,-4,	5,-2,	5,-2,	5,-2,	5,-2};
int CurrentGame::GetAddScore(){
	byte MyMask=0;
	int MyIndex=-1;
	for(int i=0;i<NPL;i++){
		if(!strcmp(this->PLAYERS[i].Nick,InGameNick)){
			MyMask=PLAYERS[i].Mask;
			MyIndex=i;
		};
	};
	if(MyIndex==-1)return 0;
	int NFriends=0;
	int NOpp=0;
	int MyRank=PLAYERS[MyIndex].Rank;
	int SummOpRank=0;
	int SummFrRank=0;
	int ADDSCO=0;
	for(i=0;i<NPL;i++){
		if(PLAYERS[i].Mask&MyMask){
			NFriends++;
			SummFrRank+=PLAYERS[i].Rank;
		}else{
			NOpp++;
			SummOpRank+=PLAYERS[i].Rank;
			ADDSCO+=WinScoreTable[(PLAYERS[i].Rank+MyRank*9)*2];
		};
	};
	if(!(NOpp&&NFriends))return 0;
	SummOpRank/=NOpp;
	SummFrRank/=NFriends;
	if(PLAYERS[MyIndex].State==0){//Victory!
		int ADDS=ADDSCO/NFriends;
		if(ADDS<5)ADDS=5;
		return ADDS;//WinScoreTable[(SummFrRank*9+SummOpRank)*2];
	}else{
		return WinScoreTable[(SummFrRank*9+SummOpRank)*2+1];
	};
};
int GetLogRank(){
	if(LOGIN.Logged)return LOGIN.Rank;
	else return 0;
};
void CheckExistingSaves(){
	if(!LOGIN.Logged)return;
	//CurrentGame CGM;
	CURIGAME.Active=0;
	CURIGAME.LoadGameFromFile();
	if(CURIGAME.Active){
		if(CURIGAME.UpdateGlobalInfo()){
			CURIGAME.DeleteThisGameFromFile();
		};
	};
	CURIGAME.Active=0;
};
CEXPORT
void ExplorerOpenRef(int Index,char* ref);
void DontMakeRaiting(){
	//if(UseGSC_Login){
	//	ExplorerOpenRef(0,"GW|norate");
	//};
	if(CURIGAME.Active){
		CURIGAME.DeleteThisGameFromFile();
		CURIGAME.Active=0;
	};
};
void StopRaiting(){
	if(CURIGAME.Active){
		CURIGAME.Active=0;
	};
};
int PBackTime=0;
void DontMakeRaiting();
void ProcessUpdate(){
	if(PBackTime==0){
		PBackTime=GetTickCount()-100000;
	};
	if(GetTickCount()-PBackTime>100000){
		if(NPlayers<=1)DontMakeRaiting();
		PBackTime=GetTickCount();
		if(CURIGAME.Active)CURIGAME.UpdateGame();
	};
};
void GETCOUNTRY(char* code,char* res){
	strcpy(res,code);
	GFILE* F=Gopen("Players\\Countries.dat","r");
	if(F){
		char ccc[128];
		char CCN[16];
		ReadWinString(F,CCN+1,15);
		strcpy(CCN+1,code);
		_strupr(CCN);
		CCN[0]='=';
		do{
			ReadWinString(F,ccc,128);
			if(ccc[0]){
				if(strstr(ccc,CCN)){
					char* cc=strchr(ccc,'=');
					if(cc)cc[0]=0;
					strcpy(res,ccc);
				};
			};
		}while(ccc[0]);
		Gclose(F);
	};
};
//---------------------TOP100-------------------//

struct OneTopClient{
	int ProfileID;
	int Score;
	int NBattl;
	int NVict;
	int NIncomp;
	int LastRequestTime;

	bool OLD_Profile:1;
	bool OLD_PLINF:1;
	bool OLD_PARAM:1;

	GPGetInfoResponseArg* PLINF;
};
class Top100{
public:
	int LastProcessTime;
	OneTopClient CLIENT[100];
	bool Started;
	bool Ready;
	bool Finished;
	bool Error;

	void Clear();
	void Download();
	void Process();
	void Update();
	void InsertMe(int ProfileID,int Score);

	Top100();
	~Top100();
};
void Top100::Clear(){
	for(int i=0;i<100;i++){
		CLIENT[i].OLD_PARAM=1;
		CLIENT[i].OLD_PLINF=1;
		CLIENT[i].OLD_Profile=1;
		/*
		if(CLIENT[i].PLINF)free(CLIENT[i].PLINF);
		CLIENT[i].PLINF=NULL;
		CLIENT[i].ProfileID=0;
		CLIENT[i].Score=0;
		CLIENT[i].NBattl=0;
		CLIENT[i].NVict=0;
		*/
	};
	Started=0;
	Ready=0;
	Finished=0;
	Error=0;
};
Top100::Top100(){
	for(int i=0;i<100;i++){
		memset(CLIENT+i,0,sizeof OneTopClient);
	};
	LastProcessTime=GetTickCount();
};
Top100::~Top100(){
	Clear();
};
extern Top100 T100;
void CHECKPLINF(){
	for(int i=0;i<100;i++){
		if(T100.CLIENT[i].PLINF){
			DWORD XX=((DWORD*)T100.CLIENT[i].PLINF)[0];
			assert(XX!=0xDDDDDDDD);
			assert(XX!=0xCDCDCDCD);
			assert(XX!=0xFDFDFDFD);
		};
	};
};
void GetTop100_callback(int localid, int profileid, persisttype_t type, 
					  int index, int success, char *data, int len, 
					  void *instance){
	INSIDE4=26;
	DOTRACE;
	InternetStatsChunks* ISS=(InternetStatsChunks*)instance;
	Top100* T100=(Top100*)instance;
	if(success){
		int PROFILES[100];
		int SCORES[100];
		int BATTLES[100];
		int VICTS[100];
		int INCOMPS[100];
		GPGetInfoResponseArg* PLINF[100];
		//CHECKPLINF();
		for(int u=0;u<100;u++){

			PROFILES[u]=T100->CLIENT[u].ProfileID;
			SCORES[u]=T100->CLIENT[u].Score;
			BATTLES[u]=T100->CLIENT[u].NBattl;
			INCOMPS[u]=T100->CLIENT[u].NIncomp;
			VICTS[u]=T100->CLIENT[u].NVict;

			if(T100->CLIENT[u].PLINF&&T100->CLIENT[u].PLINF->profile){
				PLINF[u]=new GPGetInfoResponseArg;
				memcpy(PLINF[u],T100->CLIENT[u].PLINF,sizeof GPGetInfoResponseArg);
			}else PLINF[u]=NULL;
		};
		//CHECKPLINF();
		if(data[0]=='T'&&data[1]=='1'&&data[2]=='0'&&data[3]=='0'&&len==604){
			//CHECKPLINF();
			T100->Clear();
			T100->Ready=1;
			T100->Finished=0;
			//CHECKPLINF();
			for(int j=0;j<100;j++){
				//CHECKPLINF();
				if(T100->CLIENT[j].PLINF){
					DWORD DAT=((DWORD*)T100->CLIENT[j].PLINF)[0];
					if(DAT!=0xDDDDDDDD&&DAT!=0xCDCDCDCD)free(T100->CLIENT[j].PLINF);
				};
				T100->CLIENT[j].PLINF=NULL;
				//CHECKPLINF();
			};
			//CHECKPLINF();
			for(j=0;j<100;j++){
				int prof=*((int*)(data+4+6*j));
				int score=*((word*)(data+8+6*j));
				memset(&T100->CLIENT[j],0,sizeof OneTopClient);
				T100->CLIENT[j].ProfileID=prof;
				T100->CLIENT[j].Score=score;
				for(int v=0;v<100;v++)if(PROFILES[v]==prof){
					if(PLINF[v]){
						T100->CLIENT[j].PLINF=new GPGetInfoResponseArg;
						memcpy(T100->CLIENT[j].PLINF,PLINF[v],sizeof GPGetInfoResponseArg);
					};
					T100->CLIENT[j].Score=SCORES[v];
					T100->CLIENT[j].NBattl=BATTLES[v];
					T100->CLIENT[j].NIncomp=INCOMPS[v];
					T100->CLIENT[j].NVict=VICTS[v];
					T100->CLIENT[j].OLD_PARAM=1;
				};
			};
		};
		for(u=0;u<100;u++)if(PLINF[u])free(PLINF[u]);
	}else T100->Error=1;
	INSIDE4=27;
	DOTRACE;
};
int TopProfile=5358612;
// Nick:     T100CEW_3742B
// Password: AV7LxvTuQ01w
//email      top100@top100.com
bool FirstTop100=1;
void RewriteTop100(int ProfileID,int Score);
void Top100::Download(){
	if(Started)return;
	Clear();
	GetPersistData(0,TopProfile,pd_public_rw,0,&GetTop100_callback,this);
};
void GET_P_SCORE(int localid, int profileid, persisttype_t type, 
					  int index, int success, char *data, int len, 
					  void *instance){
	Top100* T100=(Top100*)instance;
	if(success){
		if(data[0]=='G'&&data[1]=='I'&&data[2]=='R'&&data[3]=='S'){
			//1. decoding
			for(int i=4;i<len;i++)data[i]^=randoma[(i+255)&8191];
			data+=4;
			//2. splitting links
			int pos=0;
			len-=4;
			do{
				word L=*((word*)(data+1+pos));
				word S=*((word*)(data+3+pos));
				if(pos+L<=len&&L){
					word S0=0;
					for(int j=0;j<L;j++)S0+=byte(data[pos+j+5]);
					if(S==S0){
						if(data[pos]==0){
							int w1=*((DWORD*)(data+5));
							int w2=*((DWORD*)(data+9));
							int w3=*((DWORD*)(data+13));
							int sco1=w1^DWORD(profileid);
							int sco2=w2^0xFB47E6C3;
							if(sco1==sco2){
								for(int q=0;q<100;q++)if(T100->CLIENT[q].ProfileID==profileid){
									T100->CLIENT[q].Score=sco1+1;
									T100->CLIENT[q].NBattl=w3;
									T100->CLIENT[q].NVict=w3;
									T100->CLIENT[q].OLD_PARAM=0;
									T100->CLIENT[q].NIncomp=0;
								};

							};
						};
						if(data[pos]==27){
							int w1=*((DWORD*)(data+5));
							int w2=*((DWORD*)(data+9));
							int w3=*((DWORD*)(data+13));
							int w4=*((DWORD*)(data+17));
							int sco1=w1^DWORD(profileid);
							int sco2=w2^0xFB47E6C3;
							if(sco1==sco2){
								for(int q=0;q<100;q++)if(T100->CLIENT[q].ProfileID==profileid){
									T100->CLIENT[q].Score=sco1+1;
									T100->CLIENT[q].NBattl=w3;
									T100->CLIENT[q].NVict=w4;
									T100->CLIENT[q].NIncomp=0;
									T100->CLIENT[q].OLD_PARAM=0;
								};
							};
						};
						if(data[pos]==28){
							int w1=*((DWORD*)(data+5));
							int w2=*((DWORD*)(data+9));
							int w3=*((DWORD*)(data+13));
							int w4=*((DWORD*)(data+17));
							int w5=*((DWORD*)(data+21));
							int w6=*((DWORD*)(data+25));
							int sco1=w1^DWORD(profileid);
							int sco2=w2^0xFB47E6C3;
							int incomp1=(w5+DWORD(profileid))^(0x6523A4+DWORD(profileid));
							int incomp2=(w6+DWORD(profileid))^(0x1234E6-DWORD(profileid));
							if(sco1==sco2&&incomp1==incomp2){
								for(int q=0;q<100;q++)if(T100->CLIENT[q].ProfileID==profileid){
									T100->CLIENT[q].Score=sco1+1;
									T100->CLIENT[q].NBattl=w3;
									T100->CLIENT[q].NVict=w4;
									T100->CLIENT[q].OLD_PARAM=0;
									T100->CLIENT[q].NIncomp=incomp1;
								};
							};
						};
						pos+=L+5;
					}else pos++;
				}else pos++;
			}while(pos<len);
		};
	};
};
GPGetInfoResponseArg GLAST;
int LASTI=0;
void GPI_callback4(GPConnection* gp,void* arg,void* par){
	INSIDE4=28;
	DOTRACE;
	GPGetInfoResponseArg* GIRA=(GPGetInfoResponseArg*)arg;
	Top100* T100=(Top100*)par;
	GLAST=*GIRA;
	for(int i=0;i<100;i++)if(T100->CLIENT[i].ProfileID==GIRA->profile&&T100->CLIENT[i].PLINF){
		*T100->CLIENT[i].PLINF=*GIRA;
		T100->CLIENT[i].OLD_PLINF=0;
		GETCOUNTRY(T100->CLIENT[i].PLINF->countrycode,T100->CLIENT[i].PLINF->homepage);
		INSIDE4=49;
		LASTI=i;
		DOTRACE;
		return;
	};
	INSIDE4=29;
	DOTRACE;
};
extern "C" int CALLBACK12=0;
void Top100::Process(){
	if(!LOGIN.Logged)return;
	if(!Ready)return;
	if(GetTickCount()-LastProcessTime>1000){
		int N=2;
		for(int i=0;i<100&&N;i++){
			if(N>0){
				if(!CLIENT[i].PLINF){
					CLIENT[i].PLINF=new GPGetInfoResponseArg;
					memset(CLIENT[i].PLINF,0,sizeof GPGetInfoResponseArg);
					gpGetInfo(&LOGIN.gp,CLIENT[i].ProfileID,GP_CHECK_CACHE,GP_NON_BLOCKING,&GPI_callback4,this);
					gpProcess(&LOGIN.gp);
					PersistThink();
					GetPersistData(0,CLIENT[i].ProfileID,pd_public_rw,0,&GET_P_SCORE,this);
					gpProcess(&LOGIN.gp);
					PersistThink();
					CLIENT[i].OLD_PARAM=0;
					N--;
				}else{
					if(CLIENT[i].OLD_PARAM){
						GetPersistData(0,CLIENT[i].ProfileID,pd_public_rw,0,&GET_P_SCORE,this);
						gpProcess(&LOGIN.gp);
						PersistThink();
						CLIENT[i].OLD_PARAM=0;
						N--;
					};
				};
			};
		};
		LastProcessTime=GetTickCount();
	};
	ProcessMessages();
	ActiveProcess();
	bool change=0;
	do{
		change=0;
		for(int i=1;i<100;i++){
			if(CLIENT[i].PLINF&&CLIENT[i].Score){
				if(CLIENT[i-1].PLINF&&CLIENT[i-1].Score&&CLIENT[i].Score>CLIENT[i-1].Score){
					OneTopClient CLI=CLIENT[i-1];
					CLIENT[i-1]=CLIENT[i];
					CLIENT[i]=CLI;
					change=1;
				};
			};
		};
	}while(change);
};
Top100 T100;
void RewriteTop100(int ProfileID,int Score){
	if(!Score)return;
	Score++;
	T100.Clear();
	T100.Download();
	do{
		ProcessMessages();
		PersistThink();
		ActiveProcess();
	}while(!(T100.Ready||T100.Error));
	//T100.Ready=1;
	if(T100.Ready){
		for(int i=0;i<100;i++)if(!T100.CLIENT[i].ProfileID)T100.CLIENT[i].Score=0;
		//1. removing
		for(i=0;i<100;i++)if(T100.CLIENT[i].ProfileID==ProfileID){
			if(i<99){
				memcpy(T100.CLIENT+i,T100.CLIENT+i+1,(99-i)*sizeof OneTopClient);
				T100.CLIENT[99].ProfileID=0;
				T100.CLIENT[99].Score=0;
			}else{
				T100.CLIENT[i].ProfileID=0;
				T100.CLIENT[i].Score=0;
			};
		};
		//2.Inserting
		for(i=0;i<100;i++)if(Score>=T100.CLIENT[i].Score){
			for(int j=98;j>=i;j--)T100.CLIENT[j+1]=T100.CLIENT[j];
			T100.CLIENT[i].ProfileID=ProfileID;
			T100.CLIENT[i].Score=Score;
			i=100;
		};
		//3.Updating
		char Pass[32];
		Pass[0]='A';Pass[1]='V';Pass[2]='7';Pass[3]='L';Pass[4]='x';Pass[5]='v';
		Pass[6]='T';Pass[7]='u';Pass[8]='Q';Pass[9]='0';Pass[10]='1';Pass[11]='w';Pass[12]=0;
		char NC[32];
		NC[0]='T';NC[1]='1';NC[2]='0';NC[3]='0';NC[4]='C';NC[5]='E';NC[6]='W';NC[7]='_';
		NC[8]='3';NC[9]='7';NC[10]='4';NC[11]='2';NC[12]='B';NC[13]=0;

		byte DATA[604];
		DATA[0]='T';DATA[1]='1';DATA[2]='0';DATA[3]='0';
		for(i=0;i<100;i++){
			*((int*)(DATA+4+i*6))=T100.CLIENT[i].ProfileID;
			*((word*)(DATA+8+i*6))=T100.CLIENT[i].Score;
		};
		char validate[33];
		GenerateAuth(GetChallenge(NULL),Pass,validate);
		int res=-1;
		PreAuthenticatePlayerPM(1,TopProfile,validate,PersAuthCallback,&res);
		do{
			ProcessMessages();
			PersistThink();
			ActiveProcess();
		}while(res==-1);
		if(res==1){
			res=-1;
			SetPersistData(1,TopProfile,pd_public_rw,0,(char*)DATA,604,PersDataSaveCallback,&res);
			do{
				ProcessMessages();
				PersistThink();
				ActiveProcess();
			}while(res==-1);
		};
	};
};
int res3=-1;

int SECCOD0=0;
int SECCOD1=0;
int SECCOD2=0;
int SECCOD3=0;

void AddStrToURL(char* url,char* var,char* value,DWORD* HASH){
	char VAL[512];
	strcpy(VAL,value);
	int CODE=0;
	for(int i=0;i<strlen(VAL);i++){
		byte c=VAL[i];
		if(c<=32||c==34 ||c=='%'||c=='&' ||c=='*'
			    ||c==39 ||c=='+'||c=='\\'||c=='/'
			    ||c=='<'||c=='>'||c=='?' ||c==0xA0||c==0xAD)c='_';
		VAL[i]=c;
		CODE+=int(c)*int(c)+SECCOD0;
		CODE&=65535;
	};
	CODE*=SECCOD1;
	CODE&=0xFFFF;
	*HASH+=CODE*SECCOD2;
	*HASH&=0xFFFFFF;
	*HASH^=SECCOD3;
	sprintf(url+strlen(url),"%s=%s&",var,VAL);
};
void AddIntToURL(char* url,char* var,int value,DWORD* HASH){
	char cc2[32];
	sprintf(cc2,"%d",value);
	AddStrToURL(url,var,cc2,HASH);
};
void AddIntIdxToURL(char* url,char* var,int value,DWORD* HASH,int idx){
	char cc2[32];
	char cc3[32];
	sprintf(cc2,"%d",value);
	sprintf(cc3,"%s%d",var,idx);
	AddStrToURL(url,cc3,cc2,HASH);
};
void AddStrIdxToURL(char* url,char* var,char* value,DWORD* HASH,int idx){
	char cc3[32];
	sprintf(cc3,"%s%d",var,idx);
	AddStrToURL(url,cc3,value,HASH);
};
char HISET[100]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char GETCOD(int v){
	if(v<0)v=0;
	if(v>99)v=99;
	return HISET[v*60/100];
};
bool TestHash1(char*);				 
void RunHTTPC();
void SendPHPString(CurrentGame* CGM){
	GFILE* F=Gopen("Internet\\alternative.dat","r");
	if(!F)return;
	char ABBREV[256];
	char PHP[256];
	char MODE[128];
	bool r1,r2,r3;
	bool unfound=1;
	DWORD HASH=0;
	do{
		r1=ReadWinString(F,ABBREV,256);
		r2=ReadWinString(F,MODE,256);
		r3=ReadWinString(F,PHP,256);
		if(r1&&r2&&r3){
			if(strstr(CGM->GameName,ABBREV))unfound=false;
		}else return;
	}while(unfound);
	SECCOD0=0;
	SECCOD1=0;
	SECCOD2=0;
	SECCOD3=0;
	int L=strlen(ABBREV);
	for(int i=0;i<L;i++){
		SECCOD0+=ABBREV[i];
		SECCOD1+=ABBREV[i]*2;
		SECCOD2+=ABBREV[i]*3;
		SECCOD3+=ABBREV[i]*4;
	};
	for(i=0;i<L-1;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*4;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*3;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*2;
		SECCOD3+=ABBREV[i]*ABBREV[i+1];
	};
	for(i=0;i<L-2;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*17;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*13;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*11;
		SECCOD3+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2];
	};
	for(i=0;i<L-3;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*11;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*21;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*3;
		SECCOD3+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3];
	};
	SECCOD0&=32767;
	SECCOD1&=32767;
	SECCOD2&=32767;
	SECCOD3&=32767;

	Gclose(F);
	char ccc[4096];
	strcpy(ccc,PHP);
	char tmp[256];
	strcpy(tmp,CGM->GameName);
	char* sss=strstr(tmp," #GUID:");
	if(sss)sss[0]=0;
	if(tmp[0]==127)AddStrToURL(ccc,"GNAME",tmp+5,&HASH);
	else AddStrToURL(ccc,"GNAME",tmp,&HASH);
	//!!!!!!!
	if(sss)AddStrToURL(ccc,"GUID",sss+7,&HASH);
	else AddStrToURL(ccc,"GUID","00000000",&HASH);
	//!!!!!!!
	AddStrToURL(ccc,"MAP",CGM->MapName,&HASH);
	AddIntToURL(ccc,"GTIME",CGM->PlayingTime,&HASH);
	char cc5[32];
	sprintf(cc5,"%d,%d,%d,%d,%d",CGM->StartTime.Min,CGM->StartTime.Hour,CGM->StartTime.Day,CGM->StartTime.Month,CGM->StartTime.Year);
	AddStrToURL(ccc,"GSTART",cc5,&HASH);
	AddIntToURL(ccc,"NPLR",CGM->NPL,&HASH);
	int NTM=0;
	byte TML[8];
	for(i=0;i<CGM->NPL;i++){
		AddStrIdxToURL(ccc,"PL",CGM->PLAYERS[i].Nick,&HASH,i);
		AddIntIdxToURL(ccc,"CL",CGM->PLAYERS[i].Color,&HASH,i);
		AddIntIdxToURL(ccc,"NT",CGM->PLAYERS[i].NationID,&HASH,i);
		switch(CGM->PLAYERS[i].State){
		case 0:
			AddStrIdxToURL(ccc,"ST","V",&HASH,i);
			break;
		case 1:
			AddStrIdxToURL(ccc,"ST","D",&HASH,i);
			break;
		default:
			AddStrIdxToURL(ccc,"ST","U",&HASH,i);
			break;
		};
		int mtm=-1;
		byte ms=CGM->PLAYERS[i].Mask;
		for(int j=0;j<NTM&&mtm==-1;j++)if(TML[j]&ms)mtm=j;
		if(mtm==-1){
			TML[NTM]=ms;
			mtm=NTM;
			NTM++;
		};
		AddIntIdxToURL(ccc,"TM",mtm+1,&HASH,i);
		AddIntIdxToURL(ccc,"score",CGM->PLAYERS[i].Score,&HASH,i);
		AddIntIdxToURL(ccc,"ID",CGM->PLAYERS[i].Profile,&HASH,i);
		if(!strcmp(MODE,"FULL")){
			//population
			AddIntIdxToURL(ccc,"MXP",CGM->PLAYERS[i].MaxPopul,&HASH,i);
			char cc6[256];
			cc6[0]=0;
			for(int p=0;p<32;p++){
				cc6[p]=GETCOD(CGM->PLAYERS[i].Popul[p]);
			};
			cc6[32]=0;
			AddStrIdxToURL(ccc,"STP",cc6,&HASH,i);
			//score
			AddIntIdxToURL(ccc,"MXS",CGM->PLAYERS[i].MaxScore,&HASH,i);
			cc6[0]=0;
			for(p=0;p<32;p++){
				cc6[p]=GETCOD(CGM->PLAYERS[i].ScoreG[p]);
			};
			cc6[32]=0;
			AddStrIdxToURL(ccc,"STS",cc6,&HASH,i);
		};
	};
	sprintf(ccc+strlen(ccc),"SEQ=%d",HASH);
	//TestHash1(ccc);
	FILE* F1=fopen("Internet\\upload.dat","a");
	if(F1){
		fprintf(F1,"%s\n",ccc);
		fclose(F1);
		RunHTTPC();
	};
};
bool CheckGameTime();
bool CurrentGame::UpdateGlobalInfo(){
	//InitProfileSystem();
	if(Active){
		//SendPHPString(this);
		//if(!ProfIsInit){
			InitProfileSystem();
		//};
		if(!ProfIsInit)return false;
		InternetStatsChunks ISC;
		InternetStatsChunks ISC1;
		T100.Clear();
		T100.Download();
		if(ISC.Download(ProfileID,0)){
			int NREC=0;
			int NVict=0;
			int CURSCORE=0;
			int NINCOMP=0;
			for(int i=0;i<ISC.N;i++){
				if(ISC.Chunks[i]->Index==0){
					int w1=*((DWORD*)ISC.Chunks[i]->Data);
					int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
					int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
					int sco1=w1^DWORD(ProfileID);
					int sco2=w2^0xFB47E6C3;
					if(sco1==sco2){
						NREC=w3;
						NVict=w3;
						CURSCORE=sco1;
					};
				};
				if(ISC.Chunks[i]->Index==27){
					int w1=*((DWORD*)ISC.Chunks[i]->Data);
					int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
					int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
					int w4=*((DWORD*)(ISC.Chunks[i]->Data+12));
					int sco1=w1^DWORD(ProfileID);
					int sco2=w2^0xFB47E6C3;
					if(sco1==sco2){
						NREC=w3;
						NVict=w4;
						CURSCORE=sco1;
					};
				};
				if(ISC.Chunks[i]->Index==28){

					int w1=*((DWORD*)ISC.Chunks[i]->Data);
					int w2=*((DWORD*)(ISC.Chunks[i]->Data+4));
					int w3=*((DWORD*)(ISC.Chunks[i]->Data+8));
					int w4=*((DWORD*)(ISC.Chunks[i]->Data+12));
					int w5=*((DWORD*)(ISC.Chunks[i]->Data+16));
					int w6=*((DWORD*)(ISC.Chunks[i]->Data+20));

					int sco1=w1^DWORD(ProfileID);
					int sco2=w2^0xFB47E6C3;
					int incomp1=(w5+DWORD(ProfileID))^(0x6523A4+DWORD(ProfileID));
					int incomp2=(w6+DWORD(ProfileID))^(0x1234E6-DWORD(ProfileID));
					if(sco1==sco2&&incomp1==incomp2){
						NREC=w3;
						NVict=w4;
						CURSCORE=sco1;
						NINCOMP=incomp1;
					};
				};
			};
			ISC.Clear();
			do{
				ProcessMessages();
				PersistThink();
				ActiveProcess();
			}while(!(T100.Ready||T100.Error));
			
			byte DATA[604];
			DATA[0]=0;
			if(T100.Ready){
				for(int i=0;i<100;i++)if(!T100.CLIENT[i].ProfileID)T100.CLIENT[i].Score=0;
				//1. removing
				for(i=0;i<100;i++)if(T100.CLIENT[i].ProfileID==ProfileID){
					if(i<99){
						memcpy(T100.CLIENT+i,T100.CLIENT+i+1,(99-i)*sizeof OneTopClient);
						T100.CLIENT[99].ProfileID=0;
						T100.CLIENT[99].Score=0;
					}else{
						T100.CLIENT[i].ProfileID=0;
						T100.CLIENT[i].Score=0;
					};
				};
				//2.Inserting
				for(i=0;i<100;i++)if(CURSCORE+1>=T100.CLIENT[i].Score){
					for(int j=98;j>=i;j--)T100.CLIENT[j+1]=T100.CLIENT[j];
					T100.CLIENT[i].ProfileID=ProfileID;
					T100.CLIENT[i].Score=CURSCORE+1;
					i=100;
				};
				//3.Updating
				char Pass[32];
				Pass[0]='A';Pass[1]='V';Pass[2]='7';Pass[3]='L';Pass[4]='x';Pass[5]='v';
				Pass[6]='T';Pass[7]='u';Pass[8]='Q';Pass[9]='0';Pass[10]='1';Pass[11]='w';Pass[12]=0;
				char NC[32];
				NC[0]='T';NC[1]='1';NC[2]='0';NC[3]='0';NC[4]='C';NC[5]='E';NC[6]='W';NC[7]='_';
				NC[8]='3';NC[9]='7';NC[10]='4';NC[11]='2';NC[12]='B';NC[13]=0;	

				DATA[0]='T';DATA[1]='1';DATA[2]='0';DATA[3]='0';
				for(i=0;i<100;i++){
					*((int*)(DATA+4+i*6))=T100.CLIENT[i].ProfileID;
					*((word*)(DATA+8+i*6))=T100.CLIENT[i].Score;
				};
				char validate[33];
				GenerateAuth(GetChallenge(NULL),Pass,validate);
				res3=-1;
				PreAuthenticatePlayerPM(1,TopProfile,validate,PersAuthCallback,&res3);
			};
			do{
				ProcessMessages();
				PersistThink();
				ActiveProcess();
			}while(res3==-1);
			if(res3==1&&DATA[0]){
				res3=-1;
				SetPersistData(1,TopProfile,pd_public_rw,0,(char*)DATA,604,PersDataSaveCallback,&res3);
			};
SAVEGAME:
			if(Finished){
				byte BUFF[2048];
				int bps=0;

				DWORD Date=StartTime.Min+StartTime.Hour*60+(StartTime.Day-1)*1440+
					(StartTime.Month-1)*44640+(StartTime.Year-2000)*535680;
				WRDT(DWORD,Date);
				WRDT(byte,NPL);
				Date=PlayingTime/60;
				if(!CheckGameTime())return true;
				//if(Date<10)return true;//!!!!!!!!!!!!!!
				WRDT(word,Date);
				WRDT(byte,GameType);
				WRDT(byte,0);
				WRDT(byte,strlen(MapName));
				memcpy(BUFF+bps,MapName,strlen(MapName));
				bps+=strlen(MapName);
				char ccc7[256];
				strcpy(ccc7,GameName);
				char* s7=strstr(ccc7," #GUID:");
				if(s7)s7[0]=0;
				WRDT(byte,strlen(ccc7));
				memcpy(BUFF+bps,ccc7,strlen(ccc7));
				bps+=strlen(ccc7);
				for(i=0;i<NPL;i++){
					WRDT(byte,PLAYERS[i].Rank);
					WRDT(byte,PLAYERS[i].State);
					WRDT(DWORD,PLAYERS[i].Score);
					WRDT(byte,PLAYERS[i].Mask);
					WRDT(byte,PLAYERS[i].Color);
					WRDT(byte,PLAYERS[i].NationID);
					WRDT(DWORD,PLAYERS[i].Profile);
					/*
					WRDT(byte,PLAYERS[i].Reserved[1]);
					WRDT(byte,PLAYERS[i].Reserved[2]);
					WRDT(byte,PLAYERS[i].Reserved[3]);
					*/
					WRDT(byte,strlen(PLAYERS[i].Nick));
					memcpy(BUFF+bps,PLAYERS[i].Nick,strlen(PLAYERS[i].Nick));
					bps+=strlen(PLAYERS[i].Nick);
					//additional!!!
					WRDT(word,PLAYERS[i].MaxScore);
					WRDT(word,PLAYERS[i].MaxPopul);
					memcpy(BUFF+bps,PLAYERS[i].ScoreG,32);
					bps+=32;
					memcpy(BUFF+bps,PLAYERS[i].Popul,32);
					bps+=32;
					//-----------//
				};
				//additional!!!
				if(CURSCORE<0)CURSCORE=0;
				int dsc=GetAddScore();
				if(!Finished){
					dsc=0;
					NINCOMP++;
				};
				CURSCORE+=dsc;
				if(dsc>0)NVict++;
				if(CURSCORE<0)CURSCORE=0;
				WRDT(word,CURSCORE);
				WRDT(char,dsc);
				//------------//
				ISC.Clear();
				ISC.WriteChunk(BUFF,bps,81);
				ISC1.Clear();
			}else{
				//1. Calculating the max score&my score;
				int MaxScore=1;
				int MyScore=0;
				for(int p=0;p<NPL;p++){
					int sco=PLAYERS[p].Score;
					if(sco>MaxScore)MaxScore=sco;
					if(!strcmp(Nick,PLAYERS[p].Nick)){
						if(sco>MyScore)MyScore=sco;
						if(PLAYERS[p].State==0||PLAYERS[p].State==1){
							Finished=1;
						};
					};
				};
				if(!Finished){
					if(MyScore<((MaxScore*3)/4)){
						for(p=0;p<NPL;p++){
							if(!strcmp(Nick,PLAYERS[p].Nick)){
								if(PLAYERS[p].State!=0)PLAYERS[p].State=1;
								Finished=1;
							};
						};
					};
				};
				if(Finished){
					int ms=0;
					for(int p=0;p<NPL;p++){
						if(PLAYERS[p].State!=1)ms|=PLAYERS[p].Mask;
					};
					if(ms==1||ms==2||ms==4||ms==8||ms==16||ms==32||ms==64||ms==128){
						for(p=0;p<NPL;p++){
							if(PLAYERS[p].State!=1)PLAYERS[p].State=0;
						};
					};
					goto SAVEGAME;
				}else{
					NINCOMP++;
				};
			};

			DWORD XX[6];
			if(Finished)NREC++;

			XX[0]=CURSCORE^DWORD(ProfileID);
			XX[1]=CURSCORE^0xFB47E6C3;
			XX[2]=NREC;
			XX[3]=NVict;
			XX[4]=(NINCOMP^(0x6523A4+DWORD(ProfileID)))-DWORD(ProfileID);
			XX[5]=(NINCOMP^(0x1234E6-DWORD(ProfileID)))-DWORD(ProfileID);

			ISC1.WriteChunk((byte*)XX,24,28);
			bool B2=ISC1.Upload(ProfileID,password,0);//.StartUpload(ProfileID,password,0);
			bool B1=true;
			if(Finished)B1=ISC.Upload(ProfileID,password,2+NREC);//.StartUpload(ProfileID,password,2+(NREC/10));
			//do{
			//	ISC.ProcessUpload();
			//	ISC1.ProcessUpload();
			//}while(!((ISC.CUPLD.Finished||ISC.CUPLD.Error)&&(ISC1.CUPLD.Finished||ISC1.CUPLD.Error)&&(res3!=-1)));
			bool resx=B1&&B2;//ISC.CUPLD.Finished&&ISC1.CUPLD.Finished;
			//RewriteTop100(ProfileID,CURSCORE);
			if(resx)SendPHPString(this);
			return resx;
		};
	};
	return false;
};
void CloseLogin(){
	gpDisconnect(&LOGIN.gp);
	LOGIN.ProfileID=0;
	LOGIN.Logged=0;
	LOGIN.Connected=0;
	CloseStatsConnection();
	CURIGAME.Active=0;
};
bool IsGameActive(){
	return CURIGAME.Active;
};
int GetCurGamePtr(byte** Ptr){
	*Ptr=(byte*)&CURIGAME;
	return sizeof CURIGAME;
};
bool CheckLogin(){
	return LOGIN.Logged;
};
void UpdateCurGame(){
	if(CURIGAME.Active){
		SYSTEMTIME SYSTM;
		GetSystemTime(&SYSTM);
		CURIGAME.LastLoadTime.Year=SYSTM.wYear;
		CURIGAME.LastLoadTime.Month=SYSTM.wMonth;
		CURIGAME.LastLoadTime.Day=SYSTM.wDay;
		CURIGAME.LastLoadTime.Hour=SYSTM.wHour;
		CURIGAME.LastLoadTime.Min=SYSTM.wMinute;
		CURIGAME.LastLoadTime.DayOfWeek=SYSTM.wDayOfWeek;
		memcpy(&CURIGAME.CurTime,&CURIGAME.LastLoadTime,sizeof CURIGAME.LastLoadTime);
	};
};
bool CheckGameTime(){
	if(CURIGAME.Active){
		SYSTEMTIME ST;
		memset(&ST,0,sizeof ST);
		ST.wMinute=CURIGAME.CurTime.Min;
		ST.wHour=CURIGAME.CurTime.Hour;
		ST.wDay=CURIGAME.CurTime.Day;
		ST.wMonth=CURIGAME.CurTime.Month;
		ST.wYear=CURIGAME.CurTime.Year;
		FILETIME FT;
		SystemTimeToFileTime(&ST,&FT);
		SYSTEMTIME ST0;
		memset(&ST0,0,sizeof ST0);
		ST0.wMinute=CURIGAME.LastLoadTime.Min;
		ST0.wHour=CURIGAME.LastLoadTime.Hour;
		ST0.wDay=CURIGAME.LastLoadTime.Day;
		ST0.wMonth=CURIGAME.LastLoadTime.Month;
		ST0.wYear=CURIGAME.LastLoadTime.Year;
		FILETIME FT0;
		SystemTimeToFileTime(&ST0,&FT0);
		LARGE_INTEGER LI0;
		LARGE_INTEGER LI;
		memcpy(&LI0,&FT0,8);
		memcpy(&LI,&FT,8);
		LI.QuadPart-=LI0.QuadPart;
		memcpy(&FT,&LI,8);
		int dt=0;
		if(FileTimeToSystemTime(&FT,&ST)){
			dt=(ST.wDay-1)*24*60+ST.wHour*60+ST.wMinute;
		};
		return dt>=10;
	}else return false;
};
void SetNormAttr(){
	HANDLE H=CreateFile("cew.dll",GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(H==INVALID_HANDLE_VALUE)return;
	FILETIME F1,F2,F3;
	GetFileTime(H,&F1,&F2,&F3);
	F3=F1;
	F2=F2;
	SetFileTime(H,&F1,&F2,&F3);
	CloseHandle(H);
};
void CheckAttr(){
	/*
	HANDLE H=CreateFile("cew.dll",GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(H==INVALID_HANDLE_VALUE)return;
	FILETIME F1,F2,F3;
	GetFileTime(H,&F1,&F2,&F3);
	LONG
	if(memcmp(&F3,&F1,8)){
		CloseHandle(H);
		ResFile F=RReset("cew.dll");
		if(F!=INVALID_HANDLE_VALUE){
			RSeek(F,20532);
			byte DATA[200];
			memset(DATA,0,200);
			RBlockWrite(F,DATA,200);
			RClose(F);
		};
	}else CloseHandle(H);
	SetNormAttr();
	*/
};
bool TestHash1(char* s);
void TestHash(){
	return;
	char* ABBREV="CC@W";
	SECCOD0=0;
	SECCOD1=0;
	SECCOD2=0;
	SECCOD3=0;
	int L=strlen(ABBREV);
	for(int i=0;i<L;i++){
		SECCOD0+=ABBREV[i];
		SECCOD1+=ABBREV[i]*2;
		SECCOD2+=ABBREV[i]*3;
		SECCOD3+=ABBREV[i]*4;
	};
	for(i=0;i<L-1;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*4;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*3;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*2;
		SECCOD3+=ABBREV[i]*ABBREV[i+1];
	};
	for(i=0;i<L-2;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*17;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*13;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*11;
		SECCOD3+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2];
	};
	for(i=0;i<L-3;i++){
		SECCOD0+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*11;
		SECCOD1+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*21;
		SECCOD2+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3]*3;
		SECCOD3+=ABBREV[i]*ABBREV[i+1]*ABBREV[i+2]*ABBREV[i+3];
	};
	SECCOD0&=32767;
	SECCOD1&=32767;
	SECCOD2&=32767;
	SECCOD3&=32767;



	DWORD Hash=0;
	char URL[4096];
	SECCOD0=30209;
	SECCOD1=22165;
	SECCOD2=29993;
	SECCOD3=13245;
	TestHash1("www.mgadek.com/tools/ccaw_games_results.php?GNAME=CC@W_GAME!&GUID=9D0FE50A&MAP=RN0_5AC1_22505_00506000_5300000.m3d&GTIME=667&GSTART=13,12,20,9,2001&NPLR=2&PL0=[GSC]DEMON&CL0=5&NT0=5&ST0=V&TM0=1&score0=15401&MXP0=258&STP0=333444469BDFIJMOSTUWYabehikptxxj&MXS0=143&STS0=224479BGKNOQSUWYbccdfgghhllmmpvx&PL1=Drew&CL1=3&NT1=255&ST1=D&TM1=2&score1=653&MXP1=192&STP1=55566667ACDFGILMSVXadgjmpgjmotxl&MXS1=98&STS1=4AAAGGGKUUVVYcddklpqqrssuqrsvxsu&SEQ=3901964");
	/*
	AddStrToURL(URL,"","CC@W_GAME!",&Hash);
	//AddStrToURL(URL,"","9D0FE50A",&Hash);
	AddStrToURL(URL,"","RN0_5AC1_22505_00506000_5300000.m3d",&Hash);
	AddStrToURL(URL,"","667",&Hash);
	AddStrToURL(URL,"","13,12,20,9,2001",&Hash);
	AddStrToURL(URL,"","2",&Hash);
	AddStrToURL(URL,"","[GSC]DEMON",&Hash);
	AddStrToURL(URL,"","5",&Hash);
	AddStrToURL(URL,"","5",&Hash);
	AddStrToURL(URL,"","V",&Hash);
	AddStrToURL(URL,"","1",&Hash);
	AddStrToURL(URL,"","15401",&Hash);
	AddStrToURL(URL,"","258",&Hash);
	AddStrToURL(URL,"","333444469BDFIJMOSTUWYabehikptxxj",&Hash);
	AddStrToURL(URL,"","143",&Hash);
	AddStrToURL(URL,"","224479BGKNOQSUWYbccdfgghhllmmpvx",&Hash);
	AddStrToURL(URL,"","Drew",&Hash);
	AddStrToURL(URL,"","3",&Hash);
	AddStrToURL(URL,"","255",&Hash);
	AddStrToURL(URL,"","D",&Hash);
	AddStrToURL(URL,"","2",&Hash);
	AddStrToURL(URL,"","653",&Hash);
	AddStrToURL(URL,"","192",&Hash);
	AddStrToURL(URL,"","55566667ACDFGILMSVXadgjmpgjmotxl",&Hash);
	AddStrToURL(URL,"","98",&Hash);
	AddStrToURL(URL,"","4AAAGGGKUUVVYcddklpqqrssuqrsvxsu",&Hash);
	*/
};
bool TestHash1(char* s){
	char ccc[4096];
	strcpy(ccc,s);
	char* cc=strstr(ccc,"?");
	if(!cc)return false;
	cc++;
	char VAR[48];
	char VALUE[256];
	DWORD HASH=0;
	char URL[4096]="";
	bool FINAL=0;
	DWORD FINHASH;
	do{
		char* cc3=strstr(cc,"=");
		if(cc3){
			int L=cc3-cc;
			memcpy(VAR,cc,L);
			VAR[L]=0;
			char* cc4=strstr(cc3,"&");
			if(cc4){
				L=cc4-cc3-1;
				memcpy(VALUE,cc3+1,L);
				VALUE[L]=0;
				AddStrToURL(URL,VAR,VALUE,&HASH);
				cc=cc4+1;
			}else{ 
				FINAL=1;
				int z=sscanf(cc3+1,"%d",&FINHASH);
			};
		};
	}while(!FINAL);
	assert(FINHASH==HASH);
};
int GetGSC_Profile();
int GetMyProfile(){
	if(UseGSC_Login){
		return GetGSC_Profile();
	}else return LOGIN.ProfileID;
};

void SetBrokenState(){
	if(CURIGAME.Active){
		CURIGAME.Broken=1;
	};
};
//--------------------------CLANFILTER-----------------------
/*
struct OneClan{
	char signum[32];
	int NMembers;
	char** Mails;
	char** Nicks;
};
class ClanFilter{
public:
	int NClans;
	OneClan* CLANS;
	ClanFilter();
	~ClanFilter();
	bool CheckUser(char* nick);
	void LoadClanList();
	void LoadSimpleClanList();
	void SaveClanList(char* name);
};
ClanFilter::ClanFilter(){
	memset(this,0,sizeof ClanFilter);
};
void ClanFilter::LoadSimpleClanList(){
	GFILE* F=Gopen("CML.TXT","r");
	if(F){
		int CCLAN=-1;
		char ccc[256];
		char ccc1[256];
		int z;
		do{
			z=Gscanf(F,"%s%s",ccc,ccc1);
			if(z==1){
				if(ccc[0]=="#"){
					CLANS=(OneClan*)realloc(CLANS,(NClans+1)*sizeof OneClan);
					CLANS[NClans].Mails=NULL;
					CLANS[NClans].Nicks=NULL;
					CLANS[NClans].NMembers=0;
					strcpy(CLANS[NClans].signum,ccc1);
					NClans++;
				}else
				if(ccc[0]!='/'){
					if(NClans){
						OneClan* OC=CLANS+NClans-1;
						OC->Mails=(char**)realloc(OC->Mails,4*OC->NMembers+4);
						OC->Nicks=(char**)realloc(OC->Nicks,4*OC->NMembers+4);
						OC->Mails[OC->NMembers]=new char[strlen(ccc1)+1];
						OC->Nicks[OC->NMembers]=new char[strlen(ccc)+1];
						strcpy(OC->Mails[OC->NMembers],ccc1);
						strcpy(OC->Nicks[OC->NMembers],ccc);
						OC->NMembers++;
					};
				};
			};
		}while(z);
		Gclose(F);
	};
};
#define WRT(tp,val) ((tp*)(BUF+Bpos))[0]=val;Bpos+=sizeof val;
#define WRTS(str) WRT(byte,strlen(str)+1);strcpy(BUF+Bpos,str);Bpos+=strlen(str)+1;
void ClanFilter::SaveClanList(){
	char* BUF=new byte [1000000];
	int Bpos=0;
	WRT(int,NClans);
	for(int i=0;i<NClans;i++){
		WRT(byte,strlen(CALNS[i].signum)+1);
		WRTS(CLANS[i].signum);
		WRT(int,CLANS[i].NMembers);
		for(int j=0;j<CLANS[i].NMembers;j++){
			WRTS(CLANS[i].Mails[j]);
			WRTS(CLANS[i].Nicks[j]);
		};
	};
	if(BPos<512)BPos=512;
	
	free(BUF);
};
*/
#include "..\http\HttpComm.h"
int T0=0;
char CLANR[32]="";
char PLNICK[32]="";
CHttpComm HTTPC;
DWORD SendHTTPRequest(char* URL){
	return HTTPC.AddRequest(URL);
};
bool CheckHTTPAnswer(DWORD Handle,int* size,byte* Data){
	*size=0;
	try{
		HTTPC.ProcessRequests();
		*size=HTTPC.GetData(Handle,(void*)Data,*size);
	}catch(...){};
	return (*size)!=0;
};
bool RejectThisPlayer=0;
DWORD CHECK_HANDLE=0;
DWORD SERV_HANDLES[6];
int NSERV=0;
DWORD SendOneRequest(char* serv,char* param){
	char ccc[512];
	sprintf(ccc,"%s?%s",serv,param);
	try{
		return SendHTTPRequest(ccc);
	}catch(...){
		return 0;
	};
};
int GetStrHASH1(char* s){
	int L=strlen(s);
	DWORD S=0;
	for(int i=0;i<L;i++){
		S+=s[i];
	};
	for(i=0;i<L-1;i++){
		S+=int(s[i])*int(s[i+1]);
	};
	for(i=0;i<L-2;i++){
		S-=int(s[i])*int(s[i+1])*int(s[i+2]);
	};
	for(i=0;i<L-3;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3]);
	};
	for(i=0;i<L-4;i++){
		S-=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4]);
	};
	for(i=0;i<L-5;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4])*int(s[i+5]);
	};
	return S;
};
void SendAllRequests(char* clan,char* nick,char* mail){
	RejectThisPlayer=0;
	char ccc[512];
	sprintf(ccc,"com=check&clan=%s&user=%s&mail=%s&code=%d",clan,nick,mail,GetTickCount()&65535);
	NSERV=0;
	GFILE* F=Gopen("Internet\\serv.dat","r");
	if(F){
		char cc[256];
		int z=0;
		do{
			int hash=0;
			z=Gscanf(F,"%s%d",cc,&hash);
			if(z==2&&NSERV<6){
				if(hash==GetStrHASH1(cc)){
					SERV_HANDLES[NSERV]=SendOneRequest(cc,ccc);
					NSERV++;
				};
			};
		}while(z==2&&NSERV<6);
		Gclose(F);
	};
	if(!NSERV){
		SERV_HANDLES[NSERV]=SendOneRequest("www.gsc-game.net/games/Cossacks-AW/scripts/checkuser.php",ccc);
		NSERV++;
	};
	CHECK_HANDLE=1;
};
char CLANX[256];
void SendPlayerRequest(char* Nick,char* mail){
	char ccc[256];
	char CLAN[256];
	strcpy(CLAN,Nick);
	if(Nick[0]!='['){
		CHECK_HANDLE=0;
		return;
	};
	char* CC2=strstr(CLAN,"]");
	if(!CC2){
		CHECK_HANDLE=0;
		return;
	}else CC2[0]=0;
	_strupr(CLAN);
	char* nick=CC2+1;
	_strupr(nick);
	for(int i=0;i<strlen(nick);i++){
		char c=nick[i];
		if(c=='['||c==']'||c=='?'||c=='&'||c=='%'||c==39||c=='"'||c=='+'||c=='-'||c=='^')c='_';
		nick[i]=c;
	};
	strcpy(CLANX,CLAN+1);
	strcpy(CLANR,CLANX);
	strcpy(PLNICK,nick);
	SendAllRequests(CLANX,PLNICK,mail);
};
void SendPlayerRequest(){
	SendPlayerRequest(LOGIN.Nick,LOGIN.EMail);
};
void WaitWithMessage(char* Message);
int GetStrHASH(char* s){
	int L=strlen(s);
	DWORD S=0;
	for(int i=0;i<L;i++){
		S+=s[i];
	};
	for(i=0;i<L-1;i++){
		S+=int(s[i])*int(s[i+1]);
	};
	for(i=0;i<L-2;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2]);
	};
	for(i=0;i<L-3;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3]);
	};
	for(i=0;i<L-4;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4]);
	};
	for(i=0;i<L-5;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4])*int(s[i+5]);
	};
	return S;
};
bool CheckPlayerToExit(){
	if(CHECK_HANDLE){
		for(int i=0;i<NSERV;i++){
			char STR[4096];
			int sz=4096;
			if(!T0)T0=GetTickCount();
			if(CheckHTTPAnswer(SERV_HANDLES[i],&sz,(byte*)STR)){
				STR[255]=0;
				int HC1=0;
				int HC2=0;
				int zz=sscanf(STR,"%d%d",&HC1,&HC2);
				if(zz==2){
					if((HC1+37)*13==HC2){
						LocalGP BOR2("Interface\\bor2");
						sprintf(STR,GetTextByID("NO_CLAN_MEMBER_[%s]"),CLANX);
						WaitWithError4(STR,BOR2.GPID);
						HTTPC.FreeData(SERV_HANDLES[i]);
						CHECK_HANDLE=0;
						T0=0;
						RejectThisPlayer=1;
						return true;
					}else if((HC1+97)*17==HC2){
						HTTPC.FreeData(SERV_HANDLES[i]);
						CHECK_HANDLE=0;
						T0=0;
						return false;
					};
				};
			};
			/*
			if(T0&&GetTickCount()-T0>2000){
				//search for passport
				bool GOODPL=0;
				char STR3[128];
				sprintf(STR3,"[%s]%s",CLANR,PLNICK);
				int HASH=GetStrHASH(STR3);
				GFILE* GF=Gopen("Internet\\PASS.DAT","r");
				if(GF){
					int z=0;
					DWORD pass=0;
					do{
						z=Gscanf(GF,"%d",&pass);
						if(z==1){
							if(HASH==pass)GOODPL=1;
						};
					}while(z==1);
					Gclose(GF);
				};
				if(!GOODPL){
					LocalGP BOR2("Interface\\bor2");
					sprintf(STR,GetTextByID("CANT_CHECK[%s]"),CLANR);
					WaitWithError4(STR,BOR2.GPID);
					//HTTPC.FreeData(CHECK_HANDLE);
					CHECK_HANDLE=0;
					T0=0;
					RejectThisPlayer=1;
					return true;
				}else{
					CHECK_HANDLE=0;
					T0=0;
					return false;
				};
			};
			*/
		};
	};
	return false;
};
//char* TRFILES[1024];
//int TRLINES[1024];
//int POS=0;
//#define DOTRACE xDOTRACE(__FILE__,__LINE__)
extern "C" void xDOTRACE(char* file,int Line){
//	TRFILES[POS]=file;
//	TRLINES[POS]=Line;
//	POS=(POS+1)&1023;
};