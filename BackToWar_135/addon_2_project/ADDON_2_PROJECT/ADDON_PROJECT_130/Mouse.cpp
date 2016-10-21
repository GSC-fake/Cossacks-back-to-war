#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mode.h"
#define MaxMX 32
#define MsizeX 28
extern int SCRSizeX;
extern int SCRSizeY;
extern int RSCRSizeX;
extern int RSCRSizeY;
extern int COPYSizeX;
typedef byte arr[MaxMX][MaxMX];
RLCTable mptr;
bool realLpressed;
bool realRpressed;
int curptr;
int mouseX;
int mouseX1;
int mouseX2;
int	mouseY;
int mouseY1;
int	mouseY2;
bool Lpressed;
bool Rpressed;
bool MouseOn;
bool Transferred;
int mouseX1a;
int mouseY1a;
arr buf1a;
arr buf2a;
bool Transferreda;
arr buf1;
arr buf2;
int curdx;
int curdy;
void LoadPointer(LPCSTR s){
	LoadRLC(s,&mptr);
	curptr=0;
	mouseX=0;
	mouseY=0;
	mouseX1=0;
	mouseY1=0;
	memset(buf1,0,sizeof buf1);
	memset(buf2,0,sizeof buf2);
	MouseOn=false;
	Transferred=true;
	curdx=0;
	curdy=0;
};
void SetMPtr(int x,int y,int key){
	if(x>RSCRSizeX-1)x=RSCRSizeX-1;
	if ((x!=mouseX)|(y!=mouseY)){
		mouseX=x;
		mouseY=y;
		Transferred=false;
		Transferreda=false;
		realLpressed=key&MK_LBUTTON;
		realRpressed=key&MK_RBUTTON;
	};
};
void ShowMPtra();
void ShowMPtr(){
	//return;
	int i;
	int j;
	//void* Sp1=ScreenPtr;
	//ScreenPtr=RealScreenPtr;
	char* xx=(char*)(ScreenPtr);
	byte b;
	
	//if(!Transferred){
	for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
		int xt1=mouseX1+i;
		int yt1=mouseY1+j;
		if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY){
			int of=(i+mouseX1)+(j+mouseY1)*SCRSizeX;
			b=xx[of];
			if(b==buf2[i][j])xx[of]=buf1[i][j];
		};
	}
	//};
	mouseX2=mouseX-curdx;
	mouseY2=mouseY-curdy;
	mouseX1=mouseX2;
	mouseY1=mouseY2;
	Transferred=true;
	for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
		int xt1=mouseX1+i;
		int yt1=mouseY1+j;
		if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY)
			buf1[i][j]=xx[xt1+yt1*SCRSizeX];
	};
	ShowRLCItem(mouseX2,mouseY2,&mptr,curptr,0);
	for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
		int xt1=mouseX1+i;
		int yt1=mouseY1+j;
		if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY)
			buf2[i][j]=xx[xt1+yt1*SCRSizeX];
	};
	//ScreenPtr=Sp1;
	ShowMPtra();
};
void ShowMPtra(){
	if(DDDebug)return;
	int i;
	int j;
	if(!int(RealScreenPtr))return; 
	bool Rpnt=0;
	char* xx=(char*)(RealScreenPtr);
	byte b;
	
	if(mouseX!=mouseX1a||mouseY!=mouseY1a)Rpnt=true;
	if(Rpnt){
		for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
			int xt1=mouseX1a+i;
			int yt1=mouseY1a+j;
			if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY){
				int of=xt1+yt1*RSCRSizeX;
				b=xx[of];
				if(b==buf2a[i][j])
					xx[of]=buf1a[i][j];
			};
		}
	};
	mouseX1a=mouseX2;
	mouseY1a=mouseY2;
	Transferreda=true;
	if(Rpnt){
		for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
			int xt1=mouseX1+i;
			int yt1=mouseY1+j;
			if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY)
				buf1a[i][j]=xx[xt1+yt1*RSCRSizeX];
		};
	};
	void* z=ScreenPtr;
	ScreenPtr=RealScreenPtr;
	int SSX=ScrWidth;
	ScrWidth=RSCRSizeX;
	ShowRLCItem(mouseX2,mouseY2,&mptr,curptr,0);
	ScrWidth=SSX;
	ScreenPtr=z;
	for(i=0;i<MaxMX;i++)for(j=0;j<MaxMX;j++){
		int xt1=mouseX1+i;
		int yt1=mouseY1+j;
		if(xt1>=0&&xt1<RSCRSizeX&&yt1>=0&&yt1<RSCRSizeY)
			buf2a[i][j]=xx[xt1+yt1*RSCRSizeX];
	};
};
