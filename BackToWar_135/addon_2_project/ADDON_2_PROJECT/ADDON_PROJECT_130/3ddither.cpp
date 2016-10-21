//-----------------------------------------------------------//
// Rasterization with dithering in shadow (4-point dithering)//
//-----------------------------------------------------------//
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
#include "dialogs.h"
#include <assert.h>
#include <math.h>
#include "Masks.h"
#include "fonts.h"
#include "3DGraph.h"



int PrecPreRenderTri64(int x1,int y1,
			   int x2,int y2,
			   int x3,int y3,
			   int bmx,int bmy,
			   int bmdxx,int bmdyx,int bmdxy,int bmdyy,
			   int fog,int fogdx,int fogdy,
			   byte* bitm,
			   byte* Dest){
	int z1=GetMin(y1,y2,y3);
	int z2=GetMax(y1,y2,y3);
	curScrOfs=x1+y1*Buf3DLx;
	CurFog=fog;
	curXT=x1;
	curYT=y1-z1;
	FogDx=fogdx;
	FogDy=fogdy;
	BMX=bmx;
	BMY=bmy;
	BMDXX=bmdxx;
	BMDYX=bmdyx;
	BMDXY=bmdxy;
	BMDYY=bmdyy;
	FOG1=fog;
	int VBpos=int(VertBuf);
	//Инициализация VertBuf
	__asm{
		push	edi
		pushf
		cld	
		mov		edi,VBpos
		mov		ecx,z2
		sub		ecx,z1
		inc		ecx
uux1:	mov		dword ptr[edi],0xFFFFFFFF;
		add		edi,16
		dec		ecx
		jnz		uux1
		popf
		pop		edi
	};
	addLine(x2,y2-z1);
	addLine(x3,y3-z1);
	addLine(x1,y1-z1);
	PrecPrepareToRender(z2-z1+1,x1,y1-z1);
	return PrecRenderTriangle64(z2-z1+1,Dest,bitm);
};

int RenderBestTriangle64(int xs1,int ys1,
						   int xs2,int ys2,
						   int xs3,int ys3,
						   int xb1,int yb1,
						   int xb2,int yb2,
						   int xb3,int yb3,
						   int f1,int f2,int f3,
						   byte * Dest,byte* Bitm){
	int dxb2=xb2-xb1;
	int dxb3=xb3-xb1;
	int dyb2=yb2-yb1;
	int dyb3=yb3-yb1;
	int dxs2=xs2-xs1;
	int dxs3=xs3-xs1;
	int dys2=ys2-ys1;
	int dys3=ys3-ys1;

	int D=dxs2*dys3-dys2*dxs3;
	if(!D){
		Dest=NULL;
		return -1;
	};
	int Axx=dys3*dxb2-dxb3*dys2;
	int Axy=dxs2*dxb3-dxb2*dxs3;
	int Ayx=dys3*dyb2-dyb3*dys2;
	int Ayy=dxs2*dyb3-dyb2*dxs3;

	Axx=div(Axx<<16,D).quot;
	Ayy=div(Ayy<<16,D).quot;
	Axy=div(Axy<<16,D).quot;
	Ayx=div(Ayx<<16,D).quot;

	int bmxy=((xb1&63)<<8)+((yb1&63)<<24);
	int bmdx=word(Axx)+(word(Ayx)<<16);
	int bmdy=word(Axy)+(word(Ayy)<<16);
	//Fogging
	int DScr=dys2*dxs3-dxs2*dys3;
	int FDx=0;
	int FDy=0;
	if(DScr){
		FDx=div(((f3-f1)*dys2-dys3*(f2-f1))<<16,DScr).quot;
		FDy=div(((f2-f1)*dxs3-dxs2*(f3-f1))<<16,DScr).quot;
	};
	return PrecPreRenderTri64(xs1,ys1,xs2,ys2,xs3,ys3,
		((xb1&255)<<16)+32768,((yb1&255)<<16)+32768,Axx,Ayx,Axy,Ayy,
		(f1<<16)+32768,FDx,FDy,Bitm,Dest);
	
};
