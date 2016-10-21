/***********************************************************************
 *Direct Draw initialisation module                    
 *
 * This module creates the Direct Draw object with the primary surface
 * and a backbuffer and sets 800x600x8 display mode.
 *
 ***********************************************************************/
#define __ddini_cpp_
#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mode.h"
#include "MapDiscr.h"
#include "fog.h"
#include "GSound.h"
#include "fonts.h"
#include "VirtScreen.h"
void Rept (LPSTR sz,...);
CEXPORT int ModeLX[32];
CEXPORT int ModeLY[32];
CEXPORT int NModes=0;
void SERROR();
void SERROR1();
void SERROR2();
void PropCopy();
void InitRLCWindows();
//#define COPYSCR
const int InitLx=1024;
const int InitLy=768;
CEXPORT int RealLx;
CEXPORT int RealLy;
CEXPORT int SCRSizeX;
CEXPORT int SCRSizeY;
CEXPORT int RSCRSizeX;
CEXPORT int RSCRSizeY;
CEXPORT int COPYSizeX;
CEXPORT int Pitch;
LPDIRECTDRAW            lpDD=NULL;      // DirectDraw object
LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE     lpDDSBack;      // DirectDraw back surface
BOOL                    bActive;        // is application active?
BOOL                    CurrentSurface; //=FALSE if backbuffer
                                        // is active (Primary surface is visible)
										//=TRUE if  primary surface is active
										// (but backbuffer is visible)
BOOL                    DDError;        //=FALSE if Direct Draw works normally 
DDSURFACEDESC           ddsd;
PALETTEENTRY            GPal[256];
LPDIRECTDRAWPALETTE     lpDDPal;
BOOL					DDDebug;
extern bool PalDone;
extern word PlayerMenuMode;
typedef struct zzz{			
	BITMAPINFO bmp;
	PALETTEENTRY XPal[255];
};
CEXPORT
byte GetPaletteColor(int r,int g,int b){
	int dmax=10000;
	int bestc=0;
	for(int i=0;i<256;i++){
		int d=abs(r-GPal[i].peRed)+abs(g-GPal[i].peGreen)+abs(b-GPal[i].peBlue);
		if(d<dmax){
			dmax=d;
			bestc=i;
		};
	};
	return bestc;
};
zzz xxt;
//typedef byte barr[ScreenSizeX*ScreenSizeY];
void* offScreenPtr;
/*
 * Flipping Pages
 */
//extern int BestBPP;
extern int SCRSZY;
void ClearRGB(){
	if(!bActive)return;
	memset(RealScreenPtr,0,RSCRSizeX*SCRSZY);
};
CEXPORT
void FlipPages(void)
{
	if(!bActive)return;
	if (DDDebug){
		if(PlayerMenuMode!=1){
		//	ProcessFog();
		//	ShowFoggedBattle();
		};
		HDC WH=GetWindowDC(hwnd);
		//memcpy(xxt.XPal,&GPal[1],sizeof xxt.XPal);
		for(int i=0;i<256;i++){
			xxt.bmp.bmiColors[i].rgbRed=GPal[i].peRed;
			xxt.bmp.bmiColors[i].rgbBlue=GPal[i].peBlue;
			xxt.bmp.bmiColors[i].rgbGreen=GPal[i].peGreen;
		};
		xxt.bmp.bmiHeader.biSize=sizeof BITMAPINFOHEADER;
		xxt.bmp.bmiHeader.biWidth=SCRSizeX;
		xxt.bmp.bmiHeader.biHeight=-SCRSizeY;
		xxt.bmp.bmiHeader.biPlanes=1;
		xxt.bmp.bmiHeader.biBitCount=8;
		xxt.bmp.bmiHeader.biCompression=BI_RGB;
		xxt.bmp.bmiHeader.biSizeImage=0;
		int z=StretchDIBits(WH,0,0,COPYSizeX,RSCRSizeY,
			0,MaxSizeY-RSCRSizeY,COPYSizeX,RSCRSizeY,RealScreenPtr,&xxt.bmp,
			DIB_RGB_COLORS,SRCCOPY);
		ReleaseDC(hwnd,WH);

		//StretchDIBits(WH,smapx,smapy,smaplx*32,smaply*32,
		//	smapx,smapy,smaplx*32,smaply*32,RealScreenPtr,&xxt.bmp,
		//	DIB_RGB_COLORS,SRCCOPY);
		return;
	};	
#ifdef COPYSCR
	/*__asm{
		push	esi
		push	edi
		mov		esi,ScreenPtr
		mov		edi,RealScreenPtr
		mov		ecx,120000
		cld
		rep		movsd
		pop		edi
		pop		esi
	}*/
	//if(PlayerMenuMode==1){
	//return;
	{
		int ofs=0;
		int	lx=COPYSizeX>>2;
		//int	ly=SCRSizeY;
		int	ly=RealLy;
		int	addOf=SCRSizeX-(lx<<2);
		int RaddOf=RSCRSizeX-(lx<<2);

		__asm{
			push	esi
			push	edi	
			mov		esi,ScreenPtr
			mov		edi,RealScreenPtr
			add		esi,ofs
			add		edi,ofs
			cld
			mov		eax,ly
xxx:
			mov		ecx,lx
			rep		movsd
			add		esi,addOf
			add		edi,RaddOf
			dec		eax
			jnz		xxx
		};
		return;
	};
	
	int ofs=smapx+smapy*SCRSizeX;
	int ofs1=smapx+smapy*RSCRSizeX;
	int	lx=smaplx<<3;
	int	ly=smaply<<5;
	if(lx==0)lx=800;
	if(ly==0)ly=600;
	int	addOf=SCRSizeX-(lx<<2);
	int		RaddOf=RSCRSizeX-(lx<<2);;
	__asm{
		push	esi
		push	edi
		mov		esi,ScreenPtr
		mov		edi,RealScreenPtr
		add		esi,ofs
		add		edi,ofs1
		cld
		mov		eax,ly
xxxx:
		mov		ecx,lx
		rep		movsd
		add		esi,addOf
		add		edi,RaddOf
		dec		eax
		jnz		xxxx
	};
	/*
	ofs=minix+miniy*SCRSizeX;
	ofs1=minix+miniy*RSCRSizeX;
	lx=msx>>3;
	ly=msy>>1;
	addOf=SCRSizeX-(lx<<2);
	RaddOf=RSCRSizeX-(lx<<2);
	__asm{
		push	esi
		push	edi
		mov		esi,ScreenPtr
		mov		edi,RealScreenPtr
		add		esi,ofs
		add		edi,ofs1
		cld
		mov		eax,ly
yyy:
		mov		ecx,lx
		rep		movsd
		add		esi,addOf
		add		edi,RaddOf
		dec		eax
		jnz		yyy
	};
	*/
	//PropCopy();
	return;
#else

	if(DDDebug) return;
	CurrentSurface=!CurrentSurface;
	while( 1 )
    {
        HRESULT ddrval;
        ddrval = lpDDSPrimary->Flip( NULL, 0 );
        if( ddrval == DD_OK )
        {
            break;
        }
        if( ddrval == DDERR_SURFACELOST )
        {
            ddrval = lpDDSPrimary->Restore();
            if( ddrval != DD_OK )
            {
                break;
            }
        }
        if( ddrval != DDERR_WASSTILLDRAWING )
        {
                break;
        }
    }
	LockSurface();
	UnlockSurface();
#endif
}
/*
 * Getting Screen Pointer
 *
 * You will ge the pointer to the invisible area of the screen
 * i.e, if primary surface is visible, then you will obtain the
 * pointer to the backbuffer.
 * You must call UnlockSurface() to allow Windows draw on the screen
 */
int SCRSZY=0;
void LockSurface(void)
{
	long dderr=0;
	if (DDDebug)
	{
		ScreenPtr=(void*)(int(offScreenPtr)+MaxSizeX*32);
		ddsd.lpSurface=ScreenPtr;
		RealScreenPtr=ScreenPtr;
		return;
	}
	if (DDError)  return;
#ifdef COPYSCR
	if ((dderr=lpDDSPrimary->Lock(NULL,&ddsd,
							    DDLOCK_SURFACEMEMORYPTR|
								DDLOCK_WAIT,NULL))!=DD_OK) DDError=true ;
	RSCRSizeX=ddsd.lPitch;
#else
	if ((dderr=lpDDSBack->Lock(NULL,&ddsd,
							    DDLOCK_SURFACEMEMORYPTR|
								DDLOCK_WAIT,NULL))!=DD_OK) DDError=true ;
	RSCRSizeX=ddsd.lPitch;
#endif
#ifdef COPYSCR
	ScreenPtr=(void*)(int(offScreenPtr)+MaxSizeX*32);
	//ddsd.lpSurface=ScreenPtr;
	RealScreenPtr=ScreenPtr;
	RealScreenPtr=ddsd.lpSurface;
	SCRSZY=ddsd.dwHeight;
	//Rept("RealPtr:%d\n",int(ddsd.lpSurface));
	ClearScreen();
#else
	ScreenPtr=ddsd.lpSurface;
	offScreenPtr=ScreenPtr;
	if (lpDDSPrimary->Lock(NULL,&ddsd,
							    DDLOCK_SURFACEMEMORYPTR|
								DDLOCK_WAIT,NULL)!=DD_OK) DDError=true ;
	RealScreenPtr=ScreenPtr;
#endif
}
/*
 *  Unlocking the surface 
 *
 *  You must unlock the Video memory for Windows to work properly
 */
void UnlockSurface(void)
{
	if(DDDebug) return;
	if (DDError)  return;
	//Back Buffer is active
#ifdef COPYSCR
	if (lpDDSPrimary->Unlock(NULL)!=DD_OK) DDError=true ;
#else
	if (lpDDSBack->Unlock(NULL)!=DD_OK) DDError=true ;
	if (lpDDSPrimary->Unlock(NULL)!=DD_OK) DDError=true ;
#endif
}
/*
 * Getting then DC of the active (invisible) area of the screen
 */
HDC GetSDC(void)
{
	if(DDDebug) return 0;
	HDC hdc;
	if (DDError) return 0;
	if (CurrentSurface)
	{
		//Back Buffer is active
		if (lpDDSPrimary->GetDC(&hdc)!=DD_OK) DDError=true ;
	}else
	{
		//Primary Surface is active
		if (lpDDSBack->GetDC(&hdc)!=DD_OK) DDError=true;
	}
	return hdc;
}
/*
 * Timer Callback 
 */
bool m640_16=0;
bool m640_24=0;
bool m640_32=0;
bool m1024_768=0;
int BestVX=640;
int BestVY=480;
int BestBPP=32;
HRESULT CALLBACK ModeCallback(LPDDSURFACEDESC pdds, LPVOID lParam)
{
	//Rept("ModeCallBack\n");
    int width  = pdds->dwWidth;
    int height = pdds->dwHeight;
    int bpp    = pdds->ddpfPixelFormat.dwRGBBitCount;
	if(width==640&&height==480){
		if(bpp==32)m640_32=1;
		if(bpp==24)m640_24=1;
		if(bpp==16)m640_16=1;
	};
	if(bpp==8&&NModes<32&&width>=800){
		if(width==1024&&height==768)m1024_768=1;
		ModeLX[NModes]=width;
		ModeLY[NModes]=height;
		NModes++;
		//Rept("AddMode: %dx%d \n",width,height);
	};
    //return S_TRUE to stop enuming modes, S_FALSE to continue
    return S_FALSE;
}
bool EnumModesOnly(){
	HRESULT ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
	if(ddrval==DD_OK){
		lpDD->EnumDisplayModes(0,NULL,NULL,ModeCallback);
		lpDD->Release();
		lpDD=NULL;
		if(m640_32)BestBPP=32;
		else if(m640_24)BestBPP=24;
		else if(m640_16)BestBPP=16;
		if(!m1024_768){
			if(MessageBox(hwnd,"Dilplay mode 1024x768x8 not found. Cossacks should not run.","Loading error",MB_RETRYCANCEL)!=IDRETRY)
				exit(0);
		};
		return true;
	}else{
		MessageBox(hwnd,"Unable to initialise Direct Draw. Cossacks should not run.","Loading error",MB_ICONSTOP);
		exit(0);
	};
	return false;
};
bool CreateDDObjects(HWND hwnd)
{
	HRESULT ddrval;
	DDSCAPS ddscaps;
	char    buf[256];
	DDError=false;
	CurrentSurface=true;
	if (DDDebug)
	{
	
		SVSC.SetSize(RealLx,RealLy);
		DDError=false;
		SCRSizeX=MaxSizeX;
		SCRSizeY=MaxSizeY;
		COPYSizeX=RealLx;
		RSCRSizeX=RealLx;
		RSCRSizeY=RealLy;
		ScrHeight=SCRSizeY;
		ScrWidth=SCRSizeX;
		InitRLCWindows();
		WindX=0;
		WindY=0;
		WindLx=RealLx;
		WindLy=RealLy;
		WindX1=WindLx-1;
		WindY1=WindLy-1;
		BytesPerPixel=1;
		offScreenPtr=(malloc(SCRSizeX*(SCRSizeY+32*4)));
		NModes=2;
		ModeLX[0]=800;
		ModeLY[0]=600;
		ModeLX[1]=1024;
		ModeLY[1]=768;
		return true;
	}
#ifdef COPYSCR

	//offScreenPtr=offScreenPtr=(malloc(MaxSizeX*(MaxSizeY+32*4)));
	SVSC.SetSize(RealLx,RealLy);
	offScreenPtr=offScreenPtr=(malloc(MaxSizeX*(MaxSizeY+32*4)));
#endif
	if(lpDD){
		lpDDSPrimary->Release();
		goto SDMOD;
	};
	lpDD=NULL;
	ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    if( ddrval == DD_OK )
    {
		//Rept("DD_OK\n");
        // Get exclusive mode
SDMOD:;
        ddrval = lpDD->SetCooperativeLevel( hwnd,
                                DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
        if(ddrval == DD_OK )
        {
			//Rept("SetCoopLevel: DD_OK\n");
			ShowCursor(false);
			//Rept("SetDisplayMode(%d,%d)\n",RealLx,RealLy);
            ddrval = lpDD->SetDisplayMode(RealLx,RealLy,8); //COPYSizeX,RSCRSizeY, 8 );
            if( ddrval == DD_OK )
            {
				//Rept("SetDisplayMode: DD_OK\n");
                // Create the primary surface with 1 back buffer
                ddsd.dwSize = sizeof( ddsd );
                ddsd.dwFlags = DDSD_CAPS;
                ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
                ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
                if( ddrval == DD_OK )
                {
					//Rept("CreateSurface: DD_OK\n");
                    // Get a pointer to the back buffer
                    //ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
                    //ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, 
                    //                                      &lpDDSBack);
					//if (ddrval==DD_OK)
					//{
						//Rept("GetAttachedSurface: DD_OK\n");
						DDError=false;
						SCRSizeX=MaxSizeX;
						SCRSizeY=MaxSizeY;
						RSCRSizeX=RealLx;//ddsd.lPitch;
						Pitch=ddsd.lPitch;
						COPYSizeX=RealLx;
						RSCRSizeY=RealLy;
						ScrHeight=SCRSizeY;
						ScrWidth=SCRSizeX;
						WindX=0;
						WindY=0;
						WindLx=RealLx;
						WindLy=RealLy;
						WindX1=WindLx-1;
						WindY1=WindLy-1;
						BytesPerPixel=1;
						/*
						NModes=0;
						Rept("lpDD=%d\n",int(lpDD));
						lpDD->EnumDisplayModes(0,NULL,NULL,ModeCallback);
						if(NModes==0){
							NModes=1;
							ModeLX[0]=1024;
							ModeLY[0]=768;
						};
						*/
						Rept("Enum:OK\n");
						return true;
					//}
                        // Create a timer to flip the pages
                      /*  if( SetTimer( hwnd, TIMER_ID, 50, NULL ) )
                        {
                             return TRUE;
                        }*/
                }
            }
        }
    }
    wsprintf(buf, "Direct Draw Init Failed (%08lx)\n", ddrval );
    MessageBox( hwnd, buf, "ERROR", MB_OK );
	return false;
}
BOOL CreateRGBDDObjects(HWND hwnd)
{
	HRESULT ddrval;
	DDSCAPS ddscaps;
	char    buf[256];
	DDError=false;
	CurrentSurface=true;
	if (DDDebug)
	{
		
		DDError=false;
		SCRSizeX=MaxSizeX;
		SCRSizeY=MaxSizeY;
		COPYSizeX=RealLx;
		RSCRSizeX=RealLx;
		RSCRSizeY=RealLy;
		ScrHeight=SCRSizeY;
		ScrWidth=SCRSizeX;
		InitRLCWindows();
		WindX=0;
		WindY=0;
		WindLx=RealLx;
		WindLy=RealLy;
		WindX1=WindLx-1;
		WindY1=WindLy-1;
		BytesPerPixel=1;
		offScreenPtr=(malloc(SCRSizeX*(SCRSizeY+32*4)));
		return true;
	}
#ifdef COPYSCR
	offScreenPtr=offScreenPtr=(malloc(MaxSizeX*(MaxSizeY+32*4)));
#endif
	if(lpDD){
		lpDDSPrimary->Release();
		goto SDMOD;
	};
	ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    if( ddrval == DD_OK )
    {
        // Get exclusive mode
        ddrval = lpDD->SetCooperativeLevel( hwnd,
                                DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
        if(ddrval == DD_OK )
        {
SDMOD:;
            ddrval = lpDD->SetDisplayMode(800,600,32); //COPYSizeX,RSCRSizeY, 8 );
            if( ddrval == DD_OK )
            {
                // Create the primary surface with 1 back buffer
                ddsd.dwSize = sizeof( ddsd );
                ddsd.dwFlags = DDSD_CAPS;
                ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
                ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
                if( ddrval == DD_OK )
                {
					DDError=false;
					SCRSizeX=MaxSizeX;
					SCRSizeY=MaxSizeY;
					RSCRSizeX=RealLx;//ddsd.lPitch;
					Pitch=ddsd.lPitch;
					COPYSizeX=RealLx;
					RSCRSizeY=RealLy;
					ScrHeight=SCRSizeY;
					ScrWidth=SCRSizeX;
					WindX=0;
					WindY=0;
					WindLx=SCRSizeX;
					WindLy=SCRSizeY;
					WindX1=WindLx-1;
					WindY1=WindLy-1;
					BytesPerPixel=1;
					return true;
				}
            }
        }
    }
    wsprintf(buf, "Direct Draw Init Failed (%08lx)\n", ddrval );
    MessageBox( hwnd, buf, "ERROR", MB_OK );
	return false;
}
BOOL CreateRGB640DDObjects(HWND hwnd)
{
	HRESULT ddrval;
	DDSCAPS ddscaps;
	char    buf[256];
	DDError=false;
	CurrentSurface=true;
	if (DDDebug)
	{
		
		DDError=false;
		SCRSizeX=MaxSizeX;
		SCRSizeY=MaxSizeY;
		COPYSizeX=RealLx;
		RSCRSizeX=RealLx;
		RSCRSizeY=RealLy;
		ScrHeight=SCRSizeY;
		ScrWidth=SCRSizeX;
		InitRLCWindows();
		WindX=0;
		WindY=0;
		WindLx=SCRSizeX;
		WindLy=SCRSizeY;
		WindX1=WindLx-1;
		WindY1=WindLy-1;
		BytesPerPixel=1;
		offScreenPtr=(malloc(SCRSizeX*(SCRSizeY+32*4)));
		return true;
	}
#ifdef COPYSCR
	offScreenPtr=offScreenPtr=(malloc(MaxSizeX*(MaxSizeY+32*4)));
#endif
	if(lpDD){
		lpDDSPrimary->Release();
		goto SDMOD;
	};
	ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    if( ddrval == DD_OK )
    {
SDMOD:;
        // Get exclusive mode
        ddrval = lpDD->SetCooperativeLevel( hwnd,
                                DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
        if(ddrval == DD_OK )
        {
            ddrval = lpDD->SetDisplayMode(640,480,BestBPP); //COPYSizeX,RSCRSizeY, 8 );
            if( ddrval == DD_OK )
            {
                // Create the primary surface with 1 back buffer
                ddsd.dwSize = sizeof( ddsd );
                ddsd.dwFlags = DDSD_CAPS;
                ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
                ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
                if( ddrval == DD_OK )
                {
					DDError=false;
					SCRSizeX=MaxSizeX;
					SCRSizeY=MaxSizeY;
					RSCRSizeX=RealLx;//ddsd.lPitch;
					Pitch=ddsd.lPitch;
					COPYSizeX=RealLx;
					RSCRSizeY=RealLy;
					ScrHeight=SCRSizeY;
					ScrWidth=SCRSizeX;
					WindX=0;
					WindY=0;
					WindLx=SCRSizeX;
					WindLy=SCRSizeY;
					WindX1=WindLx-1;
					WindY1=WindLy-1;
					BytesPerPixel=1;
					return true;
                }
            }
        }
    }
    wsprintf(buf, "Direct Draw Init Failed (%08lx)\n", ddrval );
    MessageBox( hwnd, buf, "ERROR", MB_OK );
	return false;
}
/*   Direct Draw palette loading*/
void LoadPalette(LPCSTR lpFileName)
{
	if(!lpDDPal)return;
	AFile((char*)lpFileName);
	//if (DDDebug) return;
	if (DDError) return;
	ResFile pf=RReset(lpFileName);
	memset(&GPal,0,1024);
	if (pf!=INVALID_HANDLE_VALUE)
	{
		for(int i=0;i<256;i++){
			RBlockRead(pf,&GPal[i],3);
			//RBlockRead(pf,&xx.bmp.bmiColors[i],3);
		};
		RClose(pf);
		if(!strcmp(lpFileName,"agew_1.pal")){
			int DCL=6;
			int C0=65;//128-DCL*4;
			for(int i=0;i<12;i++){
				int gray=0;
				if(i>2)gray=(i-2)*2;
				if(i>7)gray+=(i-7)*8;
				if(i>9)gray+=(i-10)*10;
				if(i>10)gray+=50;
				gray=gray*6/3;
				//gray=(i+5)*6;
				int rr=0*C0/150+gray*8/2;
				int gg=80*C0/150+gray*6/2;//80
				int bb=132*C0/150+gray*4/2;
				if(rr>255)rr=255;
				if(gg>255)gg=255;
				if(bb>255)bb=255;
				if(i<5){
					rr=rr-((rr*(5-i))/6);
					gg=gg-((rr*(5-i))/6);
					bb=bb-((rr*(5-i))/6);
				};
				if(i<3){
					rr=rr-((rr*(3-i))/4);
					gg=gg-((rr*(3-i))/4);
					bb=bb-((rr*(3-i))/4);
				};
				if(i<2){
					rr=rr-((rr*(2-i))/3);
					gg=gg-((rr*(2-i))/3);
					bb=bb-((rr*(2-i))/3);
				};
				//if(!i){
				//	rr=rr*10/11;
				//	gg=gg*10/11;
				//	bb=bb*10/11;
				//};
				GPal[0xB0+i].peBlue=bb;
				GPal[0xB0+i].peRed=rr;
				GPal[0xB0+i].peGreen=gg;
				C0+=5;
			};
			ResFile pf=RRewrite(lpFileName);
			for(i=0;i<256;i++)RBlockWrite(pf,&GPal[i],3);
			RClose(pf);
		};
		if(!DDDebug){
			if(!PalDone){
				lpDD->CreatePalette(DDPCAPS_8BIT,&GPal[0],&lpDDPal,NULL);
				PalDone=true;
				lpDDSPrimary->SetPalette(lpDDPal);
				//lpDDSBack->SetPalette(lpDDPal);
			}else{
				lpDDPal->SetEntries(0,0,256,GPal);
			};
			//lpDDSPrimary->SetPalette(lpDDPal);
			//lpDDSBack->SetPalette(lpDDPal);
		};
	}
}
void CBar(int x,int y,int Lx,int Ly,byte c);
void Susp(char* str){
	return;
	if(!DDDebug){
		void* oldsof=ScreenPtr;
		ScreenPtr=RealScreenPtr;
		int ScLx=ScrWidth;
		ScrWidth=RealLx;
		CBar(700,1,100,5,0x93);
		ShowString(700,0,str,&fn8);
		ScrWidth=ScLx;
		ScreenPtr=oldsof;
	}else{
		CBar(700,1,100,5,0x93);
		ShowString(700,0,str,&fn8);

		HDC WH=GetWindowDC(hwnd);

		xxt.bmp.bmiHeader.biSize=sizeof BITMAPINFOHEADER;
		xxt.bmp.bmiHeader.biWidth=SCRSizeX;
		xxt.bmp.bmiHeader.biHeight=SCRSizeY;
		xxt.bmp.bmiHeader.biPlanes=1;
		xxt.bmp.bmiHeader.biBitCount=8;
		xxt.bmp.bmiHeader.biCompression=BI_RGB;
		xxt.bmp.bmiHeader.biSizeImage=0;
		int z=StretchDIBits(WH,700,1,100,5,
			700,1,100,5,ScreenPtr,&xxt.bmp,
			DIB_RGB_COLORS,SRCCOPY);
			
	};
};
void SetDarkPalette(){
	if (DDError) return;
	memset(&GPal,0,1024);
	if(!DDDebug){
		if(!PalDone){
			lpDD->CreatePalette(DDPCAPS_8BIT,&GPal[0],&lpDDPal,NULL);
			PalDone=true;
			lpDDSPrimary->SetPalette(lpDDPal);
		}else{
			lpDDPal->SetEntries(0,0,256,GPal);
		};
	}
};
CEXPORT
void SlowLoadPalette(LPCSTR lpFileName)
{
	PALETTEENTRY            NPal[256];
	if (DDError) return;
	SetDarkPalette();
	ResFile pf=RReset(lpFileName);
	memset(&GPal,0,1024);
	if (pf!=INVALID_HANDLE_VALUE)
	{
		for(int i=0;i<256;i++){
			RBlockRead(pf,&GPal[i],3);
			//RBlockRead(pf,&xx.bmp.bmiColors[i],3);
		};
		RClose(pf);
		
		if(!strcmp(lpFileName,"agew_1.pal")){
			int DCL=6;
			int C0=65;//128-DCL*4;
			for(int i=0;i<12;i++){
				int gray=0;
				if(i>2)gray=(i-2)*2;
				if(i>7)gray+=(i-7)*8;
				if(i>9)gray+=(i-10)*10;
				if(i>10)gray+=50;
				gray=gray*6/3;
				//gray=(i+5)*6;
				int rr=0*C0/150+gray*8/2;
				int gg=80*C0/150+gray*6/2;//80
				int bb=132*C0/150+gray*4/2;
				if(rr>255)rr=255;
				if(gg>255)gg=255;
				if(bb>255)bb=255;
				if(i<5){
					rr=rr-((rr*(5-i))/6);
					gg=gg-((rr*(5-i))/6);
					bb=bb-((rr*(5-i))/6);
				};
				if(i<3){
					rr=rr-((rr*(3-i))/4);
					gg=gg-((rr*(3-i))/4);
					bb=bb-((rr*(3-i))/4);
				};
				if(i<2){
					rr=rr-((rr*(2-i))/3);
					gg=gg-((rr*(2-i))/3);
					bb=bb-((rr*(2-i))/3);
				};
				//if(!i){
				//	rr=rr*10/11;
				//	gg=gg*10/11;
				//	bb=bb*10/11;
				//};
				GPal[0xB0+i].peBlue=bb;
				GPal[0xB0+i].peRed=rr;
				GPal[0xB0+i].peGreen=gg;
				C0+=5;
			};
			ResFile pf=RRewrite(lpFileName);
			for(i=0;i<256;i++)RBlockWrite(pf,&GPal[i],3);
			RClose(pf);
		};
		
		if(!DDDebug){
			byte* pal=(byte*)NPal;
			byte* pal0=(byte*) GPal;
			int mul=0;
			int t0=GetTickCount();
			int mul0=0;
			do{
				mul=(GetTickCount()-t0)*2;
				if(mul>255)mul=255;
				if(mul!=mul0){
					for(int j=0;j<1024;j++){
						pal[j]=byte((int(pal0[j])*mul)>>8);
					};
					pal[1023]=0;
					pal[1022]=0;
					pal[1021]=0;
					pal[1020]=0;
					lpDDPal->SetEntries(0,0,255,NPal);
				};
				mul0=mul;
			}while(mul!=255);
		};
	}
}
CEXPORT
void SlowUnLoadPalette(LPCSTR lpFileName)
{
	PALETTEENTRY            NPal[256];
	if (DDError) return;
	//ResFile pf=RReset(lpFileName);
	//memset(&GPal,0,1024);
	//if (pf!=INVALID_HANDLE_VALUE)
	//{
		//for(int i=0;i<256;i++){
		//	RBlockRead(pf,&GPal[i],3);
		//	//RBlockRead(pf,&xx.bmp.bmiColors[i],3);
		//};
		//RClose(pf);
		if(!DDDebug){
			byte* pal=(byte*)NPal;
			byte* pal0=(byte*) GPal;
			int mul=0;
			int t0=GetTickCount();
			int mul0=0;
			do{
				mul=(GetTickCount()-t0)*2;
				if(mul>255)mul=255;
				if(mul!=mul0){
					for(int j=0;j<1024;j++){
						pal[j]=byte((int(pal0[j])*(255-mul))>>8);
					};
					pal[1023]=0;
					pal[1022]=0;
					pal[1021]=0;
					pal[1020]=0;
					lpDDPal->SetEntries(0,0,255,NPal);
				};
				mul0=mul;
			}while(mul!=255);
		};
	//}
}	
/*     Closing all Direct Draw objects
 *
 * This procedure must be called before the program terminates,
 * otherwise Windows can occur some problems.
 */
void FreeDDObjects( void )
{
	free(offScreenPtr);
	offScreenPtr=NULL;
	if (DDDebug)
	{
		//free(offScreenPtr);
		return;
	}
    if( lpDD != NULL )
    {
		/*if( lpDDSBack != NULL )
        {
            lpDDSBack->Release();
            lpDDSBack = NULL;
        };*/
		//ClearScreen();
        if( lpDDSPrimary != NULL )
        {
            lpDDSPrimary->Release();
            lpDDSPrimary = NULL;
        };
		lpDD->Release();
        lpDD = NULL;
    }
}
void SetDebugMode()
{
	DDDebug=true;
}
void NoDebugMode()
{
	DDDebug=false;
}
CEXPORT
void GetPalColor(byte idx,byte* r,byte* g,byte* b){
	*r=GPal[idx].peRed;
	*g=GPal[idx].peGreen;
	*b=GPal[idx].peBlue;
};