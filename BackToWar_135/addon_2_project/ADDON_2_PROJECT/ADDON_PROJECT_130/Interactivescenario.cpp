/*
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
#pragma pack(4)
#include "InetRaiting\stats\gstats.h"
#include "InetRaiting\stats\gpersist.h"
#include "InetRaiting\gp.h"
#pragma pack(1)
#include "IR.H"
#include "bmptool.h"
#define MaxFparam 8

#define ip_Zone  1
#define ip_Group 2
#define ip_Integer 3
#define ip_AddUnits 4
#define ip_Nation 5
#define ip_NMask 6

#define is_NTypes 6
char* is_Types[is_NTypes]={"Zone","Group","Integer","AddUnits","Nation","Nmask"};

class OneIntrFunction{
public:
	void* FPTR;
	bool HaveIntResult:1;
	int NParam;
	byte ParamList[MaxFparam];
	char ParamName[MaxFparam][32];
	char NameInDLL[32];
	char Message[128];
	char Brief[64];
};
//list of real types:
// 0 integer value -> Precomp=IntParam
// 1 string value -> Precomp=lpChar
// 2 lpChar is identifier -> Precomp=GetValueOfID(lpChar);
class OneParameter{
public:
	byte  Kind;//method of input, the same as in function definition
	byte  Type;//really the type, see list upper
	bool  Reference:1;//1 if *Precomp is a parameter value , 0 if Precomp is a value
	bool  Allocated:1;//1 if lpChar is allocated
	char* lpChar;
	int   IntParam;
	DWORD Precomp;
};
class OneAction{
public:
	int IFN_Index;
	OneParameter Parms[MaxFparam];
	char* ResultVariable;
};
class OneCondition:public OneAction{
public:
	byte Op_Kind;
	int CmpValue;
};
class OneScenarioItem{
public:
	bool OneTime:1;
	bool Done:1;
	char Remark[128];
	int NCond;
	int NAct;
	OneCondition* COND;
	OneAction* ACTS;
};
#define vt_StaticZone 1
#define vt_StaticGroup 2
#define vt_DynZone 3
#define vt_DynGroup 4
#define vt_Integer 5
class OneVariable{
public:
	byte Type;
	char* Name;
	int Value;
};
class InteractiveScenario{
public:
	int NFunc;
	int MaxFNS;
	OneIntrFunction* FNS;
	int NItems;
	OneScenarioItem* ITEMS;
	int NVar;
	OneVariable* VARS;
	InteractiveScenario();
	~InteractiveScenario();
	void LoadFunctions();
	bool LoadScenario(char* Name);
	bool SaveScenario(char* Name);
	void InitScenario();
	void ExecuteOneStep();
	void ClearScenario();
	int InsertTrigger(int Index);
};
InteractiveScenario::InteractiveScenario(){
	memset(this,0,sizeof InteractiveScenario);
	LoadFunctions();
};
InteractiveScenario::~InteractiveScenario(){
};
void IS_Error(char* s,...){
	va_list va;
    va_start( va, s);
	char cc2[256];
	int NP=0;
	vsprintf(cc2,s,va);
	ErrM(cc2);
	va_end( va );
};
int sc_Line;
void is_Syntax(){
	IS_Error("Loading functions syntax error, FnList.dat, line %d",sc_Line);
};
char* ReadStrItem(char* s){
	while(s[0]==' ')s++;
	while(s[0]!=' '&&s[0]!=0)s++;
	return s;
};
bool ReadWinString(GFILE* F,char* STR,int Max);
char* GetTextByID(char* ID);
void InteractiveScenario::LoadFunctions(){
	HMODULE H=GetModuleHandle("dmcr.exe");
	if(H==INVALID_HANDLE_VALUE){
		IS_Error("Unable to find DMCR.EXE");
		return;
	};
	GFILE* F=Gopen("Interactive\\FnList.dat","r");
	int sc_Line=0;
	if(F){
		char str[257];
		bool ReadDone;
		do{
			ReadDone=ReadWinString(F,str,256);
			sc_Line++;
			if(str[0]=='#'&&ReadDone){
				//new function definition
				char* s=strchr(str,' ');
				if(!s){
					is_Syntax();
					Gclose(F);
					return;
				}else{
					s++;
					if(NFunc>=MaxFNS){
						MaxFNS+=32;
						FNS=(OneIntrFunction*)realloc(FNS,MaxFNS*sizeof OneIntrFunction);
					};
					OneIntrFunction* OIF=FNS+NFunc;
					int z=sscanf(s,"%s",OIF->NameInDLL);
					if(z==1){
						OIF->FPTR=GetProcAddress(H,OIF->NameInDLL);
						if(!OIF->FPTR){
							IS_Error("Unknown export function: %s",OIF->NameInDLL);
							Gclose(F);
							return;
						};
						ReadWinString(F,str,256);
						sc_Line++;
						char rettp[32];
						int Nprm;
						z=sscanf(str,"%s%d",rettp,&Nprm);
						if(z==2){
							if(Nprm>=MaxFparam){
								IS_Error("FnList.dat : %s : too many parameters",OIF->NameInDLL);
								is_Syntax();
								Gclose(F);
								return;
							};
							char* s1=ReadStrItem(ReadStrItem(str));
							char sp1[64],sp2[64];
							OIF->NParam=Nprm;
							for(int i=0;i<Nprm;i++){
								z=sscanf(s1,"%s%s",sp1,sp2);
								if(z!=2){
									is_Syntax();
									Gclose(F);
									return;
								};
								char* ptxt=GetTextByID(sp2);
								if(strlen(ptxt)>31){
									IS_Error("FnList.dat : %s : too long parameter: %s",OIF->NameInDLL,ptxt);
									is_Syntax();
									Gclose(F);
								};
								strcpy(OIF->ParamName[i],ptxt);
								OIF->ParamList[i]=0;
								for(int j=0;j<is_NTypes;j++){
									if(!strcmp(is_Types[j],sp1)){
										OIF->ParamList[i]=j+1;
									};
								};
								if(!OIF->ParamList[i]){
									IS_Error("FnList.dat : %s : Unknown data type: %s",OIF->NameInDLL,sp1);
									is_Syntax();
									Gclose(F);
								};
								s1=ReadStrItem(ReadStrItem(s1));
							};
							ReadWinString(F,str,256);
							sc_Line++;
							strcpy(OIF->Message,GetTextByID(str));
							ReadWinString(F,str,256);
							sc_Line++;
							strcpy(OIF->Brief,GetTextByID(str));
						}else{
							is_Syntax();
							Gclose(F);
							return;
						};
						NFunc++;
					}else{
						is_Syntax();
						Gclose(F);
						return;
					};
				};
			};
		}while(ReadDone);
	}else{
		ErrM("Unable to load Interactive\\FnList.dat");
	};
};
char* InvOprList[6]={"!=","==","<",">","<=",">="};
bool InteractiveScenario::SaveScenario(char* Name){
	FILE* F=fopen(Name,"w");
	if(F){
		fprintf(F,"//Scenario for Cossacks mission\n//Variables section\n");
		fprintf(F,"#VAR\n");
		for(int i=0;i<NVar;i++){
			fprintf(F,"%s %d",VARS[i].Name,VARS[i].Type);
		};
		for(i=0;i<NItems;i++){
			fprintf(F,"#SECTION %s\n#CONDITIONS\n",ITEMS[i].Remark);
			int N=ITEMS[i].NCond;
			for(int j=0;j<N;j++){
				fprintf(F,"%d %s %s ",ITEMS[i].COND[j].CmpValue,InvOprList[ITEMS[i].COND[j].Op_Kind],FNS[ITEMS[i].COND[j].IFN_Index].NameInDLL);
				int N1=FNS[ITEMS[i].COND[j].IFN_Index].NParam;
				for(int k=0;k<N1;k++){
					OneParameter* PARM=ITEMS[i].COND[j].Parms+k;
					switch(PARM->Type){
					case 0:
						fprintf(F,"%d ",PARM->IntParam);
						break;
					case 1:
					case 2:
						fprintf(F,"'%d' ",PARM->lpChar);
						break;
					};
				};
				fprintf(F,"\n");
			};
			fprintf(F,"#ACTIONS\n",ITEMS[i].Remark);
			N=ITEMS[i].NAct;
			for(j=0;j<N;j++){
				fprintf(F,"%s ",FNS[ITEMS[i].COND[j].IFN_Index].NameInDLL);
				int N1=FNS[ITEMS[i].ACTS[j].IFN_Index].NParam;
				for(int k=0;k<N1;k++){
					OneParameter* PARM=ITEMS[i].COND[j].Parms+k;
					switch(PARM->Type){
					case 0:
						fprintf(F,"%d ",PARM->IntParam);
						break;
					case 1:
					case 2:
						fprintf(F,"'%d' ",PARM->lpChar);
						break;
					};
				};
				fprintf(F,"\n");
			};
		};
		fprintf(F,"#END");
		return true;
	}else return false;
};
void SC_Error(char* s,...){
	va_list va;
    va_start( va, s);
	char cc2[256];
	int NP=0;
	vsprintf(cc2,s,va);
	char cc3[256];
	sprintf(cc3,"Line %d : %s",cc2);
	MessageBox(hwnd,"Script loading error!",cc3,0);
	va_end( va );
};
bool InteractiveScenario::LoadScenario(char* Name){
	GFILE* F=fopen(Name,"r");
	if(F){
		bool Success;
		sc_Line=0;
		char str[256];
		do{
			Success=ReadWinString(F,str,256);
			sc_Line++;
			if(Success){
				if(str[0]=='#'){
START_READ_SECTION:
					int v=0;
					while(str[v]!=' '&&str[v]!=0&&str[v]!=9)v++;
					str[v]=0;
					if(!strcmp(str,"#VAR")){
						do{
							Success=ReadWinString(F,str,256);
							sc_Line++;
							if(Success){
								if(str[0]=='#')goto STRT_READ_SECTION;
								if(str[0]!='/'){
									char VarName[64];
									int Type;
									int z=Gscanf(F,"%s%d",VarName,&Type);
									if(z==2){
										VARS=(OneVariable*)realloc(VARS,(NVar+1)*SIZEOF oNEvARIABLE);
										VARS[NVar].Name=new char[strlen(VarName)+1];
										strcpy(VARS[NVar].Name,VarName);
										VARS[NVar].Type=Type;
										VARS[NVar].Value=0;
										NVar++;
									}else{
										SC_Error("Incorrect variables description string");
									};
								};
							};
						}while(Success);
					}else if(!strcmp(str,"#CONDITIONS")){
						ITEMS=(OneScenarioItem*)realloc(ITEMS,(NItems+1)*sizeof OneScenarioItem);
						memset(ITEMS+NItems,0,sizeof OneScenarioItem);
						OneScenarioItem* OSI=ITEMS+NItems;
						bool ActSect=0;
						do{
RE_READ_ACTION:;
							Suceess=ReadWinString(F,str,256);
							if(Success&&str[0]!='/'){
								char cc1[128],cc2[128],cc3[128];
								z=sscanf(str,"%s%s%s",cc1,cc2,cc3);
								if(z&&cc1[0]=='#'){
									if(!strcmp(cc1,"#ACTIONS")){
										ActSect=1;
									}else{
										SC_Error("Expected #ACTIONS directive, but found: %s",cc1);
									};
								}else{
									OneAction* RACT=NULL;
									char* par=NULL;
									if(ActSect){
										OSI->ACTS=(OneAction*)realloc(OSI->ACTS,(OSI->NAct+1)*sizeof OneAction);
										OneAction* CACT=OSI->ACTS+OSI->NAct;
										memset(CACT,0,sizeof OneAction);
										OSI->NAct++;
										CACT->
										char* ParamPtr=NULL;
										if(z==3&&!strcmp(cc2,"=")){
											//return result to variable
											CACT->ResultVariable=new char[strlen(cc1)+1];
											strcpy(CACT->ResultVariable,cc1);
											strcpy(cc1,cc3);
										}else if(z==0) goto RE_READ_ACTION;
										RACT=CACT;
										par=
									}else{
										OneCondition* CACT=OSI->COND+OSI->NCond;
										memset(CACT,0,sizeof OneCondition);
										OSI->NCond++;
										RACT=CACT;
									};
									RACT->IFN_Index=-1;
									for(int i=0;i<NFunc;i++)if(!strcmp(FNS[i].NameInDLL,cc1){
										RACT->IFN_Index=i;
										i=NFunc;
									};
									if(RACT->IFN_Index==-1){
										SC_Error("Unknown function: %s",cc1);
									}else{
										//recognising parameters
										OneIntrFunction* OFU=FNS+RACT->IFN_Index;

										OFU->NParam
									};
								}else{
									if(ActSect)SC_Error("Uncompleted expression in #ACTIONS section");
									else SC_Error("Uncompleted expression in #CONDITIONS section");
								};
							};
						}while(Success);
						NItems++;
					}else if(str[0]=='#'){
						SC_Error("Uexpected directive %s",str);
					};
				}else;
			};
		return true;
	}else return false;
};
void InteractiveScenario::InitScenario(){
};
void InteractiveScenario::ExecuteOneStep(){
};
void InteractiveScenario::ClearScenario(){

};
InteractiveScenario SCRIPT;*/