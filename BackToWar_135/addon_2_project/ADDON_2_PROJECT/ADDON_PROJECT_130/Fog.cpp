#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "mode.h"
#include "3DGraph.h"
#include "AntiBug.h"
#define FMSHI 3
//#define FMSX 134
//#define FMSX (134<<(ADDSH-1))
//#define FMSX2 (2*FMSX)
int FMSX;
int FMSX2;
//word fmap[FMSX][FMSX];
word* fmap;
//word fmap1[FMSX][FMSX];
word* fmap1;
#define MaxShad 4528
byte fog[8192+1024];
byte wfog[8192];
byte yfog1[8192];
byte rfog[8192];

byte Optional1[8192];
byte Optional2[8192];
byte Optional3[8192];

byte darkfog[40960];
byte yfog[8192];
byte trans4[65536];
byte trans8[65536];
byte AlphaR[65536];
byte AlphaW[65536];
byte refl[3072];
byte WaterCost[65536];
byte GraySet[256];
byte Bright[8192];
void ClearFog(){
	memset(fmap,0,LX_fmap*LX_fmap*2);
	memset(fmap1,0,LX_fmap*LX_fmap*2);
};
void LoadOptionalTable(int n,char* Name){
	ResFile F=RReset(Name);
	switch(n){
	case 3:
		RBlockRead(F,Optional1,8192);
		break;
	case 4:
		RBlockRead(F,Optional2,8192);
		break;
	case 5:
		RBlockRead(F,Optional3,8192);
		break;
	};
	RClose(F);
};
int mul3(int);
int FogMode;
void ShowSuperFog();

#define FMSX_C 134
#define FMSX2_C (2*FMSX_C)

void ProcessFog1_1(){
	memcpy(fmap1,fmap,LX_fmap*LX_fmap*2);
	int mlx=(msx>>2)+FMSHI+FMSHI;
	int mly=(msy>>2)+FMSHI+FMSHI;
	int fDV=(mlx*mly)<<1;
	int fDH=(mlx<<1)-2;
	byte z=1;
	__asm{
		push	esi
		push	edi
		mov		esi,fmap1
		mov		edi,fmap
		mov		ebx,fDV
		mov		ecx,mlx
		inc		ecx

		xor		ebx,ebx
		mov		bl,byte ptr mlx
		mov		bh,byte ptr mly
		dec		bl
		dec		bh
		mov		ecx,2+FMSX2_C
lab4:	mov		dx,[esi+ecx-FMSX2_C]
		add		dx,[esi+ecx+FMSX2_C]
		add		dx,[esi+ecx-2]
		add		dx,[esi+ecx+2]
		mov		ax,dx
		shr		ax,2
		shr		dx,10
		sub		ax,dx	
ioo:	
lab6:
		mov		word ptr [edi+ecx],ax
		add		ecx,2
		dec		bl
		jnz		lab4
lab7:	sub		ecx,fDH
		add		ecx,FMSX2_C
		mov		bl,byte ptr mlx
		dec		bl
		dec		bh
		jnz		lab4
ProcessFinished:

		pop		edi
		pop		esi
	};
};

#undef FMSX_C
#undef FMSX2_C

#define FMSX_C (134<<1)
#define FMSX2_C (2*FMSX_C)

void ProcessFog1_2(){
	memcpy(fmap1,fmap,LX_fmap*LX_fmap*2);
	int mlx=(msx>>2)+FMSHI+FMSHI;
	int mly=(msy>>2)+FMSHI+FMSHI;
	int fDV=(mlx*mly)<<1;
	int fDH=(mlx<<1)-2;
	byte z=1;
	__asm{
		push	esi
		push	edi
		mov		esi,fmap1
		mov		edi,fmap
		mov		ebx,fDV
		mov		ecx,mlx
		inc		ecx

		xor		ebx,ebx
		mov		bl,byte ptr mlx
		mov		bh,byte ptr mly
		dec		bl
		dec		bh
		mov		ecx,2+FMSX2_C
lab4:	mov		dx,[esi+ecx-FMSX2_C]
		add		dx,[esi+ecx+FMSX2_C]
		add		dx,[esi+ecx-2]
		add		dx,[esi+ecx+2]
		mov		ax,dx
		shr		ax,2
		shr		dx,10
		sub		ax,dx	
ioo:	
lab6:
		mov		word ptr [edi+ecx],ax
		add		ecx,2
		dec		bl
		jnz		lab4
lab7:	sub		ecx,fDH
		add		ecx,FMSX2_C
		mov		bl,byte ptr mlx
		dec		bl
		dec		bh
		jnz		lab4
ProcessFinished:

		pop		edi
		pop		esi
	};
};


#undef FMSX_C
#undef FMSX2_C

#define FMSX_C (134<<2)
#define FMSX2_C (2*FMSX_C)

void ProcessFog1_3(){
	memcpy(fmap1,fmap,LX_fmap*LX_fmap*2);
	int mlx=(msx>>2)+FMSHI+FMSHI;
	int mly=(msy>>2)+FMSHI+FMSHI;
	int fDV=(mlx*mly)<<1;
	int fDH=(mlx<<1)-2;
	byte z=1;
	__asm{
		push	esi
		push	edi
		mov		esi,fmap1
		mov		edi,fmap
		mov		ebx,fDV
		mov		ecx,mlx
		inc		ecx

		xor		ebx,ebx
		mov		bx,word ptr mlx
		//mov		bh,byte ptr mly
		dec		bx
		dec		mly
		mov		ecx,2+FMSX2_C
lab4:	mov		dx,[esi+ecx-FMSX2_C]
		add		dx,[esi+ecx+FMSX2_C]
		add		dx,[esi+ecx-2]
		add		dx,[esi+ecx+2]
		mov		ax,dx
		shr		ax,2
		shr		dx,10
		sub		ax,dx	
ioo:	
lab6:
		mov		word ptr [edi+ecx],ax
		add		ecx,2
		dec		bx
		jnz		lab4
lab7:	sub		ecx,fDH
		add		ecx,FMSX2_C
		mov		bx,word ptr mlx
		dec		bx
		dec		mly
		jnz		lab4
ProcessFinished:

		pop		edi
		pop		esi
	};
};

void ProcessFog1(){
	switch(ADDSH){
	case 1:
		ProcessFog1_1();
		break;
	case 2:
		ProcessFog1_2();
		break;
	case 3:
		ProcessFog1_3();
		break;
	};
};

int FOGOFFS[1024];
void LoadBlobs();
CEXPORT
int CurPalette=0;
extern CurrentCursorGP;
byte graysc[256];
CEXPORT
void LoadFog(int set){
	CurrentCursorGP=set+5;
	CurPalette=set;
	char cc[128];
	sprintf(cc,"%d\\agew_1d.grd",set);
	ResFile fx=RReset(cc);//aged.grd");//grassd.grd");//darkb.grd");//004g.grd");
	RBlockRead(fx,&fog[1024],8192);
	memcpy(&fog[0],&fog[1024],256);
	memcpy(&fog[256],&fog[1024],256);
	memcpy(&fog[512],&fog[1024],256);
	memcpy(&fog[512+256],&fog[1024],256);
	RClose(fx);
	fx=RReset("0\\gray.set");//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&graysc,256);
	RClose(fx);
	//fx=RReset("003xw.grd");
	sprintf(cc,"%d\\orange.grd",set);
	fx=RReset(cc);//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&Optional1,8192);
	RClose(fx);
	sprintf(cc,"%d\\agew_1w.grd",set);
	fx=RReset(cc);//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&wfog,8192);
	RClose(fx);
	sprintf(cc,"%d\\agew_1br.grd",set);
	fx=RReset(cc);//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&Bright,8192);
	RClose(fx);
	fx=RReset("ageb.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&rfog,8192);
	RClose(fx);
	sprintf(cc,"%d\\agew_1r.grd",set);
	fx=RReset(cc);//agered.grd");
	RBlockRead(fx,&yfog,8192);
	RClose(fx);
	//sprintf(cc,"%d\\agew_1dr.grd",set);
	fx=RReset("0\\agew_1dr.grd");//darkage.grd");//darkfog.grd");
	RBlockRead(fx,&	darkfog,40960);
	RClose(fx);
	sprintf(cc,"%d\\agew_tr.grd",set);
	fx=RReset(cc);//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&trans8,65536);
	RClose(fx);
	sprintf(cc,"%d\\agew_tr4.grd",set);
	fx=RReset(cc);//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&trans4,65536);
	RClose(fx);
	fx=RReset("wcost.grd");//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&WaterCost,65536);
	RClose(fx);
	fx=RReset("refl.grd");//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	RBlockRead(fx,&refl,3072);
	RClose(fx);
	//fx=RReset("agew_t12.grd");//agew.grd");//grassw.grd");//darkw.grd");//003cm.grd");
	//RBlockRead(fx,&trans12,65536);
	//RClose(fx);
	fx=RReset("AlphaYR.grd");
	RBlockRead(fx,&AlphaR,65536);
	RClose(fx);
	fx=RReset("AlphaW.grd");
	RBlockRead(fx,&AlphaW,65536);
	RClose(fx);
	fx=RReset("agew_1gc.pal");
	RBlockRead(fx,&GraySet,256);
	RClose(fx);
	for(int i=0;i<1024;i++)FOGOFFS[i]=i*FMSX;
	LoadBlobs();
};
void SetupFog(){
	for(int i=0;i<1024;i++)FOGOFFS[i]=i*FMSX;
};
#define Shifter 7


static byte BFog[64][64];
void SetScreenFog16x16(){
	smaplx++;
	smaply++;
	int fofs=int(fmap)+((((mapy-1)<<8)+(mapx-1))<<1);
	int Saddy=(256-smaplx)<<1;
	int Daddy=(64-smaplx)<<1;
	word MinShad=(MaxShad-(32<<Shifter));
	//filling
	__asm{
		push	esi
		push	edi
		mov		cl,byte ptr smaplx
		mov		ch,byte ptr smaply
		mov		esi,fofs
		mov		edi,offset BFog+64+2
		cld
LP1:	lodsw	
		cmp		ax,MaxShad
		jae		FullColor
		cmp		ax,MinShad
		jbe		AbsBlack
		sub		ax,MaxShad
		neg		ax
		shr		ax,Shifter
		jmp		asgn1
AbsBlack:
		mov		ax,32
		jmp		asgn1
FullColor:
		xor		ax,ax
asgn1:	mov		ah,al
		mov		[edi],ax
		mov		[edi+64],ax
		add		edi,2
		dec		cl
		jnz		LP1
		mov		cl,byte ptr smaplx
		add		esi,Saddy
		add		edi,Daddy
		dec		ch
		jnz		LP1
		//set colors at the edges
		/*mov		esi,offset BFog+64+2
		mov		edi,offset BFog+2
		mov		ecx,smaplx
		rep		movsw
		mov		esi,smaply
		shl		esi,6
		add		esi,2+offset BFog
		mov		edi,esi
		add		edi,64
		mov		ecx,smaplx
		rep		movsw
		mov		esi,offset BFog+64
		mov		edi,offset BFog+65
		mov		ecx,smaply
		shl		ecx,1
cyc1:	movsb
		add		esi,63
		add		edi,63
		loop	cyc1
		mov		esi,offset BFog+64+2
		add		esi,smaplx
		add		esi,smaplx
		mov		edi,esi
		inc		edi
		mov		ecx,smaply
		shl		ecx,1
cyc2:	movsb
		add		esi,63
		add		edi,63
		loop	cyc2*/
		pop		edi
		pop		esi
	};
	smaplx--;
	smaply--;
};
void ProcessScreenFog16x16(){
	smaplx++;
	smaply++;
	int	ads=64-(smaplx<<1);
	__asm{
		push	esi
		mov		esi,offset BFog+64+2
		mov		ch,byte ptr smaply
		shl		ch,1
gt0:	mov		cl,byte ptr smaplx
gt1:	mov		ax,[esi-1]
		add		ax,[esi+1]
		add		ax,[esi-64]
		add		ax,[esi+64]
		shr		ax,2
		and		ax,0x1F1F
		mov		[esi],ax
		add		esi,2
		dec		cl
		jnz		gt1
		add		esi,ads
		dec		ch
		jnz		gt0
		pop		esi
	};
	smaplx--;
	smaply--;
};


#define zmin 0
#define zmax 32













void ShowSuperFluentFog32_160_16(int x,int y,int z1x,int z2x,int z3x,int z4x){
	if(MiniMode)return;
	int z1=z1x<<16;
	int	z2=z2x<<16;
	int z3=z3x<<16;
	int	z4=z4x<<16;
	int scrof=int(ScreenPtr)+x+y*SCRSizeX;
	int adds=SCRSizeX-32;
	if(z1x<=63&&z2x<=63&&z3x<=63&&z4x<=63)return;
	if(z1x>=96&&z2x>=96&&z3x>=96&&z4x>=96){
		__asm{
			push	edi
			mov		ebx,adds
			mov		edi,scrof
			mov		dl,16
			xor		eax,eax
			cld
iug:		mov		ecx,8
			rep		stosd
			add		edi,ebx
			dec		dl
			jnz		iug
			pop		edi
		};
		return;
	}else{
		int a,b,p,q,r;
		int c=(z3-z1)>>4;
		int d=(z1+z4-z3-z2)>>9;
		__asm{
			push	edi
			push	esi
			pushf
			mov		eax,z1
			mov		ebx,eax
			//shl		ebx,8
			mov		a,ebx
			mov		ecx,z2
			sub		ecx,eax
			sar		ecx,5
			mov		b,ecx
			/*mov		ecx,z3
			sub		ecx,eax
			sar		ecx,5
			mov		c,ecx
			mov		ecx,z4
			add		ecx,z1
			sub		ecx,z2
			sub		ecx,z3
			sar		ecx,10
			mov		d,ecx*/
			//coefficients are now calculated
			mov		ecx,0x1004
			mov		ebx,a		//bh=fogging value
			//add		ebx,256*256*3
			mov		edx,b		//dx=fog incrementor
			xor		eax,eax
			mov		esi,scrof
			mov		p,ebx
qqw1:		mov		eax,ebx
			sar		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			sar		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			sar		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			sar		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			//jnz		qqw1
			add		esi,adds
			add		edx,d
			mov		ebx,p
			add		ebx,c
			//mov		cl,4
			mov		p,ebx
			dec		ch
			jnz		qqw1
			popf
			pop		esi
			pop		edi
		};
		//Xbar(x+12,y+12,8,8,clrGreen);
		//Xbar(x,y,32,32,clrGreen);
	};
};
void ShowSuperFluentFog16_160(int x,int y,int z1x,int z2x,int z3x,int z4x){
//	if(MiniMode)return;
	int z1=z1x<<16;
	int	z2=z2x<<16;
	int z3=z3x<<16;
	int	z4=z4x<<16;
	int scrof=int(ScreenPtr)+x+y*SCRSizeX;
	int adds=SCRSizeX-16;
	if(z1x<=63&&z2x<=63&&z3x<=63&&z4x<=63)return;
	if(z1x>=96&&z2x>=96&&z3x>=96&&z4x>=96){
		__asm{
			push	edi
			mov		ebx,adds
			mov		edi,scrof
			mov		dl,16
			xor		eax,eax
			cld
iug:		mov		ecx,4
			rep		stosd
			add		edi,ebx
			dec		dl
			jnz		iug
			pop		edi
		};
		return;
	}else{
		int a,b,c,d,p,q,r;
		__asm{
			push	edi
			push	esi
			pushf
			mov		eax,z1
			mov		ebx,eax
			//shl		ebx,8
			mov		a,ebx
			mov		ecx,z2
			sub		ecx,eax
			sar		ecx,4
			mov		b,ecx
			mov		ecx,z3
			sub		ecx,eax
			sar		ecx,4
			mov		c,ecx
			mov		ecx,z4
			add		ecx,z1
			sub		ecx,z2
			sub		ecx,z3
			sar		ecx,8
			mov		d,ecx
			//coefficients are now calculated
			mov		ecx,0x1002
			mov		ebx,a		//bh=fogging value
			//add		ebx,256*256*3
			mov		edx,b		//dx=fog incrementor
			xor		eax,eax
			mov		esi,scrof
			mov		p,ebx
qqw1:		mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			//jnz		qqw1
			add		esi,adds
			add		edx,d
			mov		ebx,p
			add		ebx,c
			//mov		cl,4
			mov		p,ebx
			dec		ch
			jnz		qqw1
			popf
			pop		esi
			pop		edi
		};
		//Xbar(x+12,y+12,8,8,clrGreen);
		//Xbar(x,y,32,32,clrGreen);
	};
};
void ShowSuperFluentFog12_160(int x,int y,int z1x,int z2x,int z3x,int z4x){
//	if(MiniMode)return;
	int z1=z1x<<16;
	int	z2=z2x<<16;
	int z3=z3x<<16;
	int	z4=z4x<<16;
	int scrof=int(ScreenPtr)+x+y*SCRSizeX;
	int adds=SCRSizeX-16;
	if(z1x<=63&&z2x<=63&&z3x<=63&&z4x<=63)return;
	if(z1x>=96&&z2x>=96&&z3x>=96&&z4x>=96){
		__asm{
			push	edi
			mov		ebx,adds
			mov		edi,scrof
			mov		dl,12
			xor		eax,eax
			cld
iug:		mov		ecx,4
			rep		stosd
			add		edi,ebx
			dec		dl
			jnz		iug
			pop		edi
		};
		return;
	}else{
		int a,b;
		int c=div(z3-z1,12).quot;
		int d=div(z1+z4-z3-z2,192).quot;
		int p,q,r;
		__asm{
			push	edi
			push	esi
			pushf
			mov		eax,z1
			mov		ebx,eax
			//shl		ebx,8
			mov		a,ebx
			mov		ecx,z2
			sub		ecx,eax
			sar		ecx,4
			mov		b,ecx
			/*mov		ecx,z3
			sub		ecx,eax
			sar		ecx,4
			mov		c,ecx
			mov		ecx,z4
			add		ecx,z1
			sub		ecx,z2
			sub		ecx,z3
			sar		ecx,8
			mov		d,ecx*/
			//coefficients are now calculated
			mov		ecx,0x0C02
			mov		ebx,a		//bh=fogging value
			//add		ebx,256*256*3
			mov		edx,b		//dx=fog incrementor
			xor		eax,eax
			mov		esi,scrof
			mov		p,ebx
qqw1:		mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi]
			mov		al,[darkfog+eax]
			mov		[esi],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+1]
			mov		al,[darkfog+eax]
			mov		[esi+1],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+2]
			mov		al,[darkfog+eax]
			mov		[esi+2],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+3]
			mov		al,[darkfog+eax]
			mov		[esi+3],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+4]
			mov		al,[darkfog+eax]
			mov		[esi+4],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+5]
			mov		al,[darkfog+eax]
			mov		[esi+5],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+6]
			mov		al,[darkfog+eax]
			mov		[esi+6],al
			//inc		esi
			add		ebx,edx
			mov		eax,ebx
			shr		eax,8
			mov		al,[esi+7]
			mov		al,[darkfog+eax]
			mov		[esi+7],al
			add		esi,8
			add		ebx,edx
			//jnz		qqw1
			add		esi,adds
			add		edx,d
			mov		ebx,p
			add		ebx,c
			//mov		cl,4
			mov		p,ebx
			dec		ch
			jnz		qqw1
			popf
			pop		esi
			pop		edi
		};
		//Xbar(x+12,y+12,8,8,clrGreen);
		//Xbar(x,y,32,32,clrGreen);
	};
};
#define shf 300
#define fmin 1500
byte fden[8192];
void makeFden(){
	for(int i=0;i<8192;i++){
		if(i>shf)fden[i]=158;
		else fden[i]=5+div(i*153,shf).quot;
	};
};
int GetF(word k){
	if(k>=fmin)return 5;
	return fden[fmin-k];
};


void TurnFogOn(){
	FogMode=1;
};
void TurnFogOff(){
	FogMode=0;
};
void SetLightPoint(int x,int y){
	/*__asm{
		mov		eax,y
		shr		eax,5
		mov		ebx,eax
		shl		eax,MTHShift
		add		eax,ebx
		mov		ebx,x
		shr		ebx,5
		add		eax,ebx
		xor		ecx,ecx
		mov		cx,[THMap+eax*2]
		test	cx,0x8000
		jz		uuu
		or		ecx,0xFFFF0000;
uuu:
		sal		ecx,1
		mov		ebx,y
		sub		ebx,ecx
	*/	
	//x>>=1;
	//y>>=1;
	int xx1=x>>5;
	int yy1=y>>5;
	if(xx1<0)xx1=0;
	if(xx1>=msx)xx1=msx-1;
	if(yy1>=msy)yy1=msy-1;
	if(Mode3D)y-=THMap[xx1+yy1+(yy1<<MTHShift)]<<1;
	yy1=y>>5;
	if(yy1<0)yy1=0;
	if(yy1>=msy)yy1=msy-1;
	__asm{
		xor		eax,eax
		mov		al,byte ptr xx1
		mov		ah,byte ptr yy1
		shl		eax,1
		mov		word ptr[fmap+eax],16383;
	};
};
void FogSpot(int x,int y);
int GetHeight(int x,int y);
void UnitLight(OneObject* OB){
	//return;
	if(!OB->Ready)return;
	int xx=OB->RealX>>4;
	int yy=OB->RealY>>4;
	int rr=200;
	int rr1=rr-(rr>>2);
	yy-=(GetHeight(xx,yy)<<1);
	NewMonster* NM=OB->newMons;
	switch(NM->VisionType){
	case 0:
		FogSpot(xx,yy);
		break;
	case 1:
		FogSpot(xx+128,yy);
		FogSpot(xx-128,yy);
		FogSpot(xx,yy+128);
		FogSpot(xx,yy-128);
		break;
	case 2:
		FogSpot(xx+128,yy+128);
		FogSpot(xx-128,yy+128);
		FogSpot(xx+128,yy-128);
		FogSpot(xx-128,yy-128);
		break;
	case 3:
		FogSpot(xx+2*128,yy);
		FogSpot(xx-2*128,yy);
		FogSpot(xx,yy-2*128);
		FogSpot(xx,yy+2*128);
		FogSpot(xx+128,yy+128);
		FogSpot(xx-128,yy+128);
		FogSpot(xx+128,yy-128);
		FogSpot(xx-128,yy-128);
		break;
	case 4:
		FogSpot(xx+3*128,yy);
		FogSpot(xx-3*128,yy);
		FogSpot(xx,yy+3*128);
		FogSpot(xx,yy-3*128);
		FogSpot(xx+2*128,yy+2*128);
		FogSpot(xx-2*128,yy+2*128);
		FogSpot(xx+2*128,yy-2*128);
		FogSpot(xx-2*128,yy-2*128);
		break;
	case 5:
		FogSpot(xx+4*128,yy);
		FogSpot(xx-4*128,yy);
		FogSpot(xx,yy+4*128);
		FogSpot(xx,yy-4*128);
		FogSpot(xx+3*128,yy+3*128);
		FogSpot(xx-3*128,yy+3*128);
		FogSpot(xx+3*128,yy-3*128);
		FogSpot(xx-3*128,yy-3*128);
		break;
	case 6:
		FogSpot(xx+5*128,yy);
		FogSpot(xx-5*128,yy);
		FogSpot(xx,yy+5*128);
		FogSpot(xx,yy-5*128);
		FogSpot(xx+4*128,yy+4*128);
		FogSpot(xx-4*128,yy+4*128);
		FogSpot(xx+4*128,yy-4*128);
		FogSpot(xx-4*128,yy-4*128);
		break;
	case 7:
		FogSpot(xx+6*128,yy);
		FogSpot(xx-6*128,yy);
		FogSpot(xx,yy+6*128);
		FogSpot(xx,yy-6*128);
		FogSpot(xx+4*128,yy+4);
		FogSpot(xx-4*128,yy+4*128);
		FogSpot(xx+4*128,yy-4*128);
		FogSpot(xx-4*128,yy-4*128);
		break;
	case 8:
		FogSpot(xx+7*128,yy);
		FogSpot(xx-7*128,yy);
		FogSpot(xx,yy+7*128);
		FogSpot(xx,yy-7*128);
		FogSpot(xx+5*128,yy+3);
		FogSpot(xx-5*128,yy+5*128);
		FogSpot(xx+5*128,yy-5*128);
		FogSpot(xx-5*128,yy-5*128);
		break;
	};
};
//New fog of war
word WFSC[128*128];
int maxWFX;
int maxWFY;
void SetWF(int x,int y,word w){
	if(x<0||y<0||x>maxWFX||y>maxWFY)return;
	WFSC[x+(y<<7)]=w;
};
int maxFX,maxFY;

void CreateFogImage(){
	//return;
	maxWFX=smaplx;
	maxWFY=smaply;
	maxFX=(msx>>2)+FMSHI;
	maxFY=(msy>>2)+FMSHI;
	int mx0=mapx>>2;
	int my0=mapy>>2;
	int mx1=mapx+smaplx;
	if(mx1&3)mx1=(mx1>>2)+1;
	else mx1>>=2;
	int my1=mapy+smaply;
	if(my1&3)my1=(my1>>2)+1;
	else my1>>=2;
	word* FMAP=(word*)fmap;
	int fogof0=(my0+FMSHI)*FMSX+mx0+FMSHI;
	for(int myy=my0;myy<=my1;myy++){
		int fogof=fogof0;
		for(int mxx=mx0;mxx<=mx1;mxx++){
			int mcx=(mxx<<2)-mapx;
			int mcy=(myy<<2)-mapy;
			int F[5][5];
			F[0][0]=FMAP[fogof];
			F[0][4]=FMAP[fogof+1];
			F[4][0]=FMAP[fogof+FMSX];
			F[4][4]=FMAP[fogof+FMSX+1];

			F[2][2]=(F[0][0]+F[4][4]+F[0][4]+F[4][0])>>2;
			F[0][2]=(F[0][0]+F[0][4])>>1;
			F[2][0]=(F[0][0]+F[4][0])>>1;
			F[2][4]=(F[0][4]+F[4][4])>>1;
			F[4][2]=(F[4][0]+F[4][4])>>1;

			F[0][1]=(F[0][0]+F[0][2])>>1;
			F[0][3]=(F[0][2]+F[0][4])>>1;
			F[1][0]=(F[0][0]+F[2][0])>>1;
			F[1][1]=(F[0][0]+F[2][0]+F[0][2]+F[2][2])>>2;
			F[1][2]=(F[0][2]+F[2][2])>>1;
			F[1][3]=(F[0][2]+F[0][4]+F[2][2]+F[2][4])>>2;
			F[1][4]=(F[0][4]+F[2][4])>>1;

			F[2][1]=(F[2][0]+F[2][2])>>1;
			F[2][3]=(F[2][2]+F[2][4])>>1;

			F[3][0]=(F[2][0]+F[4][0])>>1;
			F[3][1]=(F[2][0]+F[2][2]+F[4][0]+F[4][2])>>2;
			F[3][2]=(F[2][2]+F[4][2])>>1;
			F[3][3]=(F[2][2]+F[2][4]+F[4][2]+F[4][4])>>2;
			F[3][4]=(F[2][4]+F[4][4])>>1;

			F[4][1]=(F[4][0]+F[4][2])>>1;
			F[4][3]=(F[4][2]+F[4][4])>>1;

			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++){
					int xx=mcx+i;
					int yy=mcy+j;
					SetWF(xx,yy,F[j][i]);
					SetWF(xx+1,yy,F[j+1][i]);
					SetWF(xx,yy+1,F[j][i+1]);
					SetWF(xx+1,yy+1,F[j+1][i+1]);
				};
			fogof++;
		};
		fogof0+=FMSX;
	};
};
void DrawFog(){
	//return;
	for(int y=0;y<smaply;y++)
		for(int x=0;x<smaplx;x++){
			int xx=(x<<5)+smapx;
			int yy=(y<<4)+smapy;
			int sof=x+(y<<7);
			ShowSuperFluentFog32_160_16(xx,yy,GetF(WFSC[sof]),GetF(WFSC[sof+1]),GetF(WFSC[sof+128]),GetF(WFSC[sof+129]));
		};
};
void FogSpot(int x,int y){
	int fx=((x+64)>>7)+FMSHI;
	int fy=((y+64)>>7)+FMSHI;
	if(fx<1)fx=1;
	if(fy<1)fy=1;
	if(fx>maxFX)fx=maxFX;
	if(fy>maxFY)fy=maxFY;
	fmap[FOGOFFS[fy]+fx]=8000;
};
word GetFog(int x,int y){
	int fx=((x+64)>>7)+FMSHI;
	int fy=((y+64)>>7)+FMSHI;
	if(fx<1)fx=1;
	if(fy<1)fy=1;
	if(fx>maxFX)fx=maxFX;
	if(fy>maxFY)fy=maxFY;
	return fmap[FOGOFFS[fy]+fx];
};
extern int MiniLx;
extern int MiniLy;
extern int MiniX,MiniY;
void DrawMiniFog(){
	int sofs=int(ScreenPtr)+minix+miniy*ScrWidth;
	int fofs=int(fmap)+((((MiniX>>1)<<(ADDSH-1))+FMSHI+1+FMSX*(((MiniY>>1)<<(ADDSH-1))+FMSHI+1))<<1);
	int MMSX=(MiniLx>>1);
	int MMSY=(MiniLy>>1);
	int addscr=ScrWidth+ScrWidth-MMSX-MMSX;
	int F_add=(FMSX2<<(ADDSH-1))-(MMSX<<ADDSH);
	int DDDX=1<<ADDSH;
	__asm{
		push	esi
		push	edi
		pushf
		mov		esi,fofs
		mov		edi,sofs
		mov		edx,ScrWidth
		mov		ebx,DDDX
lopx1:
		mov		ecx,MMSX
lopx3:	mov     ax,[esi]
		add		esi,ebx

		cmp		ax,1300
		ja		lopx2
		mov		word ptr [edi],0
		mov		word ptr [edi+edx],0
lopx2:	add		edi,2
		dec		ecx
		jnz		lopx3
		add		esi,F_add
		add		edi,addscr
		dec		MMSY
		jnz		lopx1
		popf
		pop		edi
		pop		esi
	};
};