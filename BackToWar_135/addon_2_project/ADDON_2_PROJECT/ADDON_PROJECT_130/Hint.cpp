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
#include "Fonts.h"
#include "recorder.h"
static int HintTime;
//static int HintTime1;
void ResFon(int x,int y,int Lx,int Ly);
void ScrCopy(int x,int y,int Lx,int Ly);
#define NHINT 4
char HintStr[256];
char HintStrLo[256];
char HintStr1[NHINT][256];
byte HintOpt[NHINT];//(0)-usual,(16+x)-in national bar,32-red 
static int  HintTime1[NHINT];
int HintX;
int HintY;
int HintLx;
int HintLy;
void SetupHint(){
	HintY=smapy+smaply*32-20;
	HintX=smapx;
	HintLx=720;
	HintLy=16;
	HintTime=0;
};
extern byte PlayGameMode;
void ShowHint(){
	if(PlayGameMode==1)return;
	//ResFon(HintX,HintY,HintLx,HintLy);
	if(HintTime){
		ShowString(HintX+2,HintY+2,HintStr,&BlackFont);
		ShowString(HintX,HintY,HintStr,&WhiteFont);

		ShowString(HintX+2,HintY+20+2,HintStrLo,&BlackFont);
		ShowString(HintX,HintY+20,HintStrLo,&WhiteFont);
	};
	int yy=HintY-20;
	for(int i=0;i<NHINT;i++){
		if(HintTime1[i]){
			ShowString(HintX+2,yy+2,HintStr1[i],&BlackFont);
			byte opt=HintOpt[i];
			byte opp=opt>>4;
			if(opp==2){
				int tt=(GetTickCount()/300)&1;
				if(tt)ShowString(HintX,yy,HintStr1[i],&WhiteFont);
				else ShowString(HintX,yy,HintStr1[i],&RedFont);
			}else
			if(opp==1){
				ShowString(HintX,yy,HintStr1[i],&WhiteFont);
				Xbar(HintX-2,yy,GetRLCStrWidth(HintStr1[i],&WhiteFont)+5,GetRLCHeight(WhiteFont.RLC,'y')+1,0xD0+((opt&7)<<2));
			}else{
				ShowString(HintX,yy,HintStr1[i],&WhiteFont);
			};
		};
		yy-=20;
	};
	//ScrCopy(HintX,HintY,HintLx,HintLy);
};
void ClearHints(){
	for(int i=0;i<NHINT;i++)HintStr1[i][0]=0;
	HintStrLo[0]=0;
};
void HideHint(){
	//ResFon(HintX,HintY,HintLx,HintLy);
	//ScrCopy(HintX,HintY,HintLx,HintLy);
};
void AssignHint(char* s,int time){
	strcpy(HintStr,s);
	//ShowHint();
	HintTime=time;
	HintStrLo[0]=0;
};
void AssignHintLo(char* s,int time){
	strcpy(HintStrLo,s);
	//ShowHint();
	HintTime=time;
};
void AssignHint1(char* s,int time){
	if(!strcmp(s,HintStr1[0])){
		HintTime1[0]=time;
		HintOpt[0]=0;
		return;
	};
	for(int i=NHINT-1;i>0;i--){
		strcpy(HintStr1[i],HintStr1[i-1]);
		HintTime1[i]=HintTime1[i-1];
		HintOpt[i]=HintOpt[i-1];

	};
	strcpy(HintStr1[0],s);
	HintTime1[0]=time;
	HintOpt[0]=0;
};
extern bool RecordMode;
extern byte PlayGameMode;
extern char LASTCHATSTR[512];
extern byte CHOPT;
void AssignHint1(char* s,int time,byte opt){
	if(opt>=16){
		if(RecordMode&&!PlayGameMode){
			strcpy(LASTCHATSTR,s);
			CHOPT=opt;
		};
	};
	if(!strcmp(s,HintStr1[0])){
		HintTime1[0]=time;
		HintOpt[0]=opt;
		return;
	};
	for(int i=NHINT-1;i>0;i--){
		strcpy(HintStr1[i],HintStr1[i-1]);
		HintTime1[i]=HintTime1[i-1];
		HintOpt[i]=HintOpt[i-1];

	};
	strcpy(HintStr1[0],s);
	HintTime1[0]=time;
	HintOpt[0]=opt;
};
void GetChar(GeneralObject* GO,char* s){
	Visuals* VS=(Visuals*)GO;
	strcpy(s,VS->Message);
};
void GetMonsterCapsString(char* st);
void ProcessHint(){
	ShowHint();
	if(HintTime){	
		HintTime--;
	};
	for(int i=0;i<NHINT;i++){
		if(HintTime1[i]){
			HintTime1[i]--;
		};
	};
};
