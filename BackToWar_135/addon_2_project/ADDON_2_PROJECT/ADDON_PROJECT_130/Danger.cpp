#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "fog.h"
#include "Megapolis.h"
#include "FlyObj.h"
#include <assert.h>
#include "walls.h"
#include "mode.h"
#include "GSound.h"
#include "MapSprites.h"
#include "NewMon.h"
#include "Math.h"
#include "GP_Draw.h"
#include "RealWater.h"
#include "NewUpgrade.h"
#include "ZBuffer.h"
#include "Path.h"
#include "Transport.h"
#include "3DBars.h"
#include "CDirSnd.h"
#include "NewAI.h"
#include "3DMapEd.h"
#include "TopoGraf.h"
#include "Towers.h"
#include "Fonts.h"
#include "Safety.h"
#include "3DGraph.h"
#include "Nature.h"
int NDOBJ;
word DOBJ[512];
word DOBJSN[512];
int DOBJLastTime=0;
extern int DangLx;
extern int DangSH;
byte* DANGMAP;
word* DCHTIME;
void InitDANGER(){
	NDOBJ=0;
	DOBJLastTime=0;
	memset(DOBJ,0,sizeof DOBJ);
	memset(DOBJSN,0,sizeof DOBJSN);
	memset(DANGMAP,0,sizeof DANGMAP);
	memset(DCHTIME,0,sizeof DCHTIME);
};
byte OBJDANG[48] ={0,0,0,0,0,0,0,0, 0,1,1,0,0,0,6,0,
                   0,0,0,0,0,0,0,0, 0,3,0,2,1,0,1,0,
				   0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
byte OBJDTYPE[48]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,2,0,
                   0,0,0,0,0,0,0,0, 0,2,0,1,1,0,1,0,
				   0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
extern int tmtmt;
int CheckDamageAbility(OneObject* OB,int x,int y,int z,byte Nation,int Soft);
void CheckDOBJS(){
	if(tmtmt-DOBJLastTime>256+(rando()&63)){
		NDOBJ=0;
		for(int i=0;i<MAXOBJECT&&NDOBJ<511;i++){
			OneObject* OB=Group[i];
			if(OB&&OB->NNUM==0&&!OB->Sdoxlo){
				byte USE=OB->newMons->Usage;
				if(OBJDANG[USE]){
					DOBJ[NDOBJ]=OB->Index;
					DOBJSN[NDOBJ]=OB->Serial;
					NDOBJ++;
				};
			};
		};
		DOBJLastTime=tmtmt;
	};
};
byte GetDangValue(int x,int y){
	CheckDOBJS();
	int ofs=x+(y<<DangSH);
	word tm=word(tmtmt);
	if(tm-DCHTIME[ofs]>255){
		int xx=(x<<7)+64;
		int yy=(y<<7)+64;
		int zz=GetHeight(xx,yy)+32;
		int dam=0;
		int wat=0;
		DCHTIME[ofs]=tm-(rando()&127);
		for(int i=0;i<NDOBJ;i++){
			OneObject* OB=Group[DOBJ[i]];
			if(OB&&OB->Serial==DOBJSN[i]){
				int USE=OB->newMons->Usage;
				int w=OBJDTYPE[USE];
				int w1=w;
				if(!OB->Selected)w1=0;
				if(CheckDamageAbility(OB,xx,yy,zz,OB->NNUM,1+w1)>=0){
					if(w)wat=128;
					dam+=OBJDANG[USE];
				};
			};
		};
		return DANGMAP[ofs]=dam|wat;
	};
	return DANGMAP[ofs];
};
void DrawDangerMap(){
	return;
	if((GetKeyState(VK_CONTROL)&0x8000)&&(GetKeyState(VK_SHIFT)&0x8000)){
		int x0=(mapx>>2)-1;
		int y0=(mapy>>2)-1;
		int x1=x0+(smaplx>>2)+2;
		int y1=y0+(smaply>>2)+4;
		int mx=msx>>2;
		if(x0<0)x0=0;
		if(y0<0)y0=0;
		if(x1>=mx)x1=mx-1;
		if(y1>=mx)y1=mx-1;
		int SDX=mapx<<5;
		int SDY=mapy<<4;
		int SLX=smaplx<<5;
		int SLY=smaply<<4;
		for(int x=x0;x<=x1;x++){
			for(int y=y0;y<=y1;y++){
				int xx=(x<<7)+64-SDX;
				int yy=(y<<6)+32-SDY-GetHeight((x<<7)+64,(y<<7)+64);
				if(xx>-32&&yy>-32&&xx<SLX&&yy<SLY){
					char cc[64];
					int v=GetDangValue(x,y);
					if(v){
						sprintf(cc,"%d",v);
						ShowString(xx,yy,cc,&fn8);
					};
				};
			};
		};
	};
};