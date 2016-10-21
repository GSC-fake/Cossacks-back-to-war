/*				  Оружие дальнего действия
 *			Организация перемещающихся анимаций.*/
#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "walls.h"
#include "Nucl.h"
#include <math.h>
#define MaxExpl 8192
#define ExMask (MaxExpl-1)
extern word FlyMops[256][256];
int NUCLUSE[4];
bool EUsage[MaxExpl];
AnmObject* GAnm[MaxExpl];
short TSin[257];
short TCos[257];
short TAtg[257];
word ID_FIRE;
word ID_FIREX;
word ID_FIRE1;
word ID_MAGW;
word ID_EXPL1;
word ID_EXPL2;
word ID_GLASSFLY;
word ID_GLASSBROKEN;
word ID_FLYFIRE;
word ID_MAGEXP;
word ID_FOG;
word ID_FOG1;
int nEused;
word LastReq;
short randoma[8192];
word rpos;
void InitExplosions(){
	for(int i=0;i<MaxExpl;i++)GAnm[i]=new AnmObject;
	for(i=0;i<257;i++){
		TSin[i]=short(256*sin(2*3.1415927*i/256));
		TCos[i]=short(256*cos(2*3.1415927*i/256));
		TAtg[i]=short(128*atan2(i,256)/3.1415927);
	};
	memset(&EUsage,0,MaxExpl);
	LastReq=0;
	nEused=0;
	ResFile rf=RReset("random.lst");
	RBlockRead(rf,randoma,16384);
	RClose(rf);
//	for(i=0;i<8192;i++){
//		randoma[i]=rand();
//	};
	rpos=0;
	//ResFile rf=RRewrite("random.lst");
	//RBlockWrite(rf,randoma,16384);
	//RClose(rf);

};
//short rando(){
//	rpos++;
//	rpos&=8191;
//	return randoma[rpos];
//};
void CloseExu(int i){
	if(EUsage[i]){
		EUsage[i]=false;
		nEused--;
	};
};
void CloseExplosions(){
	for(int i=0;i<MaxExpl;i++)free(GAnm[i]);
};
void Weapon::CreateWeapon(Nation* Nat,word Ind,byte ExplCount,byte Kind){
	Vis=(Visuals*)Nat->Mon[Ind];
	NextWeapon=NULL;
	MinDamage=byte(Vis->info.Basic.MinDamage);
	MaxDamage=byte(Vis->info.Basic.MaxDamage);
	Force=byte(Vis->info.Basic.MaxLife);
	if(ExplCount>1)FDecrement=Force/ExplCount;else FDecrement=Force;
	ExplPath=Vis->info.Basic.AttackRange*3;
	atime=0;
	switch(Kind){
	case 0://simple weapon
		Probab1=0;
		Probab2=0;
		DirectFactor=0;
		break;
	case 1://weak division
		Probab1=160;
		Probab2=32;
		DirectFactor=196;
		break;
	case 2://strontg division
		Probab1=0;
		Probab2=120;
		DirectFactor=196;
		break;
	case 3://total elimination
		Probab1=0;
		Probab2=128;
		DirectFactor=196;
		break;
	default://Don't use this value. It leads to elimination of 
			//everything everywhere
		Probab1=255;
		Probab2=255;
		DirectFactor=0;
	};
};
void Weapon::CreateNWeapon(int r1,int r2,int time){
	//ar1=r1;
	//ar2=r2;
	atime=time;
};
byte CreateUniExObj(Weapon* Wep,short x,short y,
				 short v,byte Mask,
				 OneObject* Send,
				 byte dsx,byte dsy,
				 word DOBJ){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return 0;
	};
	int dx=(int(dsx)<<7)-int(x);
	int dy=(int(dsy)<<7)-int(y);
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return 0;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->Transparent=Wep->Transparent;
	AO->destX=dsx;
	AO->destY=dsy;
	AO->v=v;
	if(Send){
		AO->WATT=Send->Ref.General->WATT;
		AO->AATT=Send->Ref.General->AATT;
		AO->P100=Send->Ref.General->P100;
		AO->T3X3=Send->Ref.General->T3X3;
	};
	if(DOBJ!=0xFFFF){
		OneObject* OB=Group[DOBJ];
		if(OB){
			AO->DestObj=DOBJ;
			AO->DSerial=OB->Serial;
		}else AO->DestObj=0xFFFF;
	}else AO->DestObj=0xFFFF;
	if(dx!=0||dy!=0){
		short adx=abs(dx);
		short ady=abs(dy);
		if(adx>ady)AO->PhDir=byte(TAtg[div(ady<<8,adx).quot]);else
				   AO->PhDir=64-byte(TAtg[div(adx<<8,ady).quot]);
		if(dx<0)AO->PhDir=128-AO->PhDir;
		if(dy<0)AO->PhDir=256-AO->PhDir;
	}else AO->PhDir=64+128;
	if(int(Send))AO->MaxPath=int(Send->Ref.Visual->info.Basic.AttackRange+2)<<7;
	else AO->MaxPath=int(Wep->ExplPath+2)<<7;
	AO->NMask=Mask;
	AO->Sender=Send;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	//AO->PhDir+=(rando()-16384)>>18;
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	return AO->Direction;
};
byte CreateExObjR(Weapon* Wep,short x,short y,
				 short dx,short dy,short v,byte Mask,OneObject* Send,word Dist){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return 0;
	};
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return 0;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->destX=255;
	AO->destY=255;
	AO->v=v;
	AO->DestObj=0xFFFF;
	if(dx!=0||dy!=0){
		short adx=abs(dx);
		short ady=abs(dy);
		if(adx>ady)AO->PhDir=byte(TAtg[div(ady<<8,adx).quot]);else
				   AO->PhDir=64-byte(TAtg[div(adx<<8,ady).quot]);
		if(dx<0)AO->PhDir=128-AO->PhDir;
		if(dy<0)AO->PhDir=256-AO->PhDir;
	}else AO->PhDir=64+128;
	AO->MaxPath=(Dist+2)<<7;
	AO->Transparent=Wep->Transparent;
	AO->NMask=Mask;
	AO->Sender=Send;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	AO->PhDir+=(rando()-16384)>>18;
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	return AO->Direction;
};
byte CreateExObj(Weapon* Wep,short x,short y,
				 short dx,short dy,short v,byte Mask,OneObject* Send){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return 0;
	};
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return 0;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->destX=255;
	AO->destY=255;
	AO->v=v;
	AO->DestObj=0xFFFF;
	if(dx!=0||dy!=0){
		short adx=abs(dx);
		short ady=abs(dy);
		if(adx>ady)AO->PhDir=byte(TAtg[div(ady<<8,adx).quot]);else
				   AO->PhDir=64-byte(TAtg[div(adx<<8,ady).quot]);
		if(dx<0)AO->PhDir=128-AO->PhDir;
		if(dy<0)AO->PhDir=256-AO->PhDir;
	}else AO->PhDir=64+128;
	if(int(Send))AO->MaxPath=int(Send->Ref.Visual->info.Basic.AttackRange+2)<<7;
	else AO->MaxPath=int(Wep->ExplPath+2)<<7;
	AO->Transparent=Wep->Transparent;
	AO->NMask=Mask;
	AO->Sender=Send;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	AO->PhDir+=(rando()-16384)>>18;
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	return AO->Direction;
};
byte CreateExObjDPoint(Weapon* Wep,short x,short y,
				 short dx,short dy,short v,byte Mask,OneObject* Send,byte dsx,byte dsy){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return 0;
	};
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return 0;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->Transparent=Wep->Transparent;
	AO->destX=dsx;
	AO->destY=dsy;
	AO->v=v;
	AO->DestObj=0xFFFF;
	if(dx!=0||dy!=0){
		short adx=abs(dx);
		short ady=abs(dy);
		if(adx>ady)AO->PhDir=byte(TAtg[div(ady<<8,adx).quot]);else
				   AO->PhDir=64-byte(TAtg[div(adx<<8,ady).quot]);
		if(dx<0)AO->PhDir=128-AO->PhDir;
		if(dy<0)AO->PhDir=256-AO->PhDir;
	}else AO->PhDir=64+128;
	if(int(Send))AO->MaxPath=int(Send->Ref.Visual->info.Basic.AttackRange+2)<<7;
	else AO->MaxPath=int(Wep->ExplPath+3)<<7;
	AO->NMask=Mask;
	AO->Sender=Send;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	//AO->PhDir+=(rando()-16384)>>18;
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	return AO->Direction;
};
byte CreateExObjDPointR(Weapon* Wep,short x,short y,
				 short dx,short dy,short v,byte Mask,OneObject* Send,byte dsx,byte dsy,word Range){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return 0;
	};
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return 0;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->Transparent=Wep->Transparent;
	AO->destX=dsx;
	AO->destY=dsy;
	AO->v=v;
	AO->DestObj=0xFFFF;
	if(dx!=0||dy!=0){
		short adx=abs(dx);
		short ady=abs(dy);
		if(adx>ady)AO->PhDir=byte(TAtg[div(ady<<8,adx).quot]);else
				   AO->PhDir=64-byte(TAtg[div(adx<<8,ady).quot]);
		if(dx<0)AO->PhDir=128-AO->PhDir;
		if(dy<0)AO->PhDir=256-AO->PhDir;
	}else AO->PhDir=64+128;
	AO->MaxPath=int(Range+3)<<7;
	AO->NMask=Mask;
	AO->Sender=Send;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	//AO->PhDir+=(rando()-16384)>>18;
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	return AO->Direction;
};
void CreateExObjD(Weapon* Wep,short x,short y,
				 short PDir,short v,byte Mask,OneObject* Send){
	if(Wep->atime){
		if(Send)CreateStrangeObject(Wep->atime,Send->NNUM,x>>7,y>>7,Send->Index);
		else CreateStrangeObject(Wep->atime,255,x>>7,y>>7,0);
		return;
	};
	short i=LastReq;
	while(EUsage[i]&&i<MaxExpl)i++;	
	if(i>=MaxExpl){
		i=0;
		while(EUsage[i]&&i<LastReq)i++;
	};
	if(EUsage[i])return;
	LastReq=(i+1)&ExMask;
	EUsage[i]=true;
	nEused++;
	AnmObject* AO=GAnm[i];
	AO->Transparent=Wep->Transparent;
	AO->destX=255;
	AO->destY=255;
	AO->v=v;
	AO->DestObj=0xFFFF;
	AO->NMask=Mask;
	AO->Sender=Send;
	AO->PhDir=byte(PDir);
	AO->Direction=((AO->PhDir+80)&255)>>5;
	AO->vx=(TCos[AO->PhDir]*v)>>8;
	AO->vy=(TSin[AO->PhDir]*v)>>8;
	AO->Wpn=Wep;
	AO->Path=0;
	AO->Visible=false;
	AO->x=x;
	AO->y=y;
	AO->xm=x>>7;
	AO->xm0=AO->xm;
	AO->ym=y>>7;
	AO->ym0=AO->ym;
	Octant* OC=AO->Wpn->Vis->lpFAnim[0].Anm;
	if(AO->Wpn->Vis->cpbRotation) 
		if(AO->Direction<5)AO->Kino=OC[AO->Direction].Movie;
		else AO->Kino=OC[8-AO->Direction].Movie;
	else AO->Kino=OC->Movie;
	if(!AO->Wpn->Vis->cpbMoving)AO->OneTime=true;else AO->OneTime=false;
	AO->Nanm=OC->count;
	AO->Canm=0;
	AO->Force=Wep->Force;
	AO->Decrement=Wep->FDecrement;
	if(Send){
		AO->MinDamage=(int(Send->GetMinDam())*Send->xForce)>>4;
		AO->MaxDamage=(int(Send->GetMaxDam())*Send->xForce)>>4;
	}else{
		AO->MinDamage=Wep->MinDamage;
		AO->MaxDamage=Wep->MaxDamage;
	};
	if(int(Send))AO->MaxPath=int(Send->Ref.Visual->info.Basic.AttackRange+2)<<7;
	else AO->MaxPath=int(Wep->ExplPath+2)<<7;
};
void CreateRandObj(Weapon* Wep,short x,short y,
				 short PDir,short v,short dist,int corr,byte Mask,OneObject* Send){
	int dir1=((((255-corr)*(rando()-16384))>>15)+256+PDir)&255;
	int x1=x+(dist*TCos[dir1]>>8);
	int y1=y+(dist*TSin[dir1]>>8);
	CreateExObjD(Wep,x1,y1,dir1,v,Mask,Send);
};
word GetEnemy(int x,int y,byte NMask){
	int xs=(x>>7)&254;
	int ys=div(y,96).quot&254;
	int xs1=(x+64)>>2;
	int ys1=div(y+48,3).quot;
	word MID;
	word BMID=0xFFFF;
	int dss;
	int dst=1000;
	for(int tx=0;tx<2;tx++)
		for(int ty=0;ty<2;ty++){
			MID=Mops[ys+ty][xs+tx];
			if(MID==0xFFFF)MID=FlyMops[ys+ty][xs+tx];
			if(MID!=0xFFFF){
				OneObject* OB=Group[MID];
				if(!(OB->NMask&NMask)){
					dss=abs(((xs+tx)<<5)-xs1)+abs((mul3(ys+ty)<<2)-ys1);
					if(dss<128&&dss<dst){
						dst=dss;
						BMID=MID;
					};
				};
			};
	};
	return BMID;
};
void ProcessExpl(){
	for(int i=0;i<MaxExpl;i++)if(EUsage[i]){
		AnmObject* AO=GAnm[i];
		byte xm=(AO->x+64)>>7;
		byte ym=(AO->y+64)>>7;
		if(xm<=0||xm>=msx||ym<0||ym>=msy)
		CloseExu(i);else{
			if(AO->Force<=0&&AO->Canm>=AO->Nanm-1)CloseExu(i);
			AO->xm=xm;
			AO->ym=ym;
			if(xm>mapx-1&&xm<=mapx+smaplx&&
				ym>mapy-1&&ym<=mapy+smaply)AO->Visible=true;else
				AO->Visible=true;
			word LNK=Links[ym][xm];
			if(LNK!=0xFFFF&&AO->Canm==AO->Nanm-1){
				word CID=LIndex[ym][xm];
				WallCluster* WC=&GWALLS.GWC[LNK];
				if((1<<WC->OwnerID)&AO->NMask)goto rdea;
				WallCell* OC=&WC->Cells[CID];
				word fn=rando();
				if(fn>8000)goto rdea;
				Weapon* Wp=AO->Wpn;	
				short prob=rando()>>7;
				small dam=Wp->MinDamage+
						((int(Wp->MaxDamage-Wp->MinDamage)*rando())>>15);
				GWALLS.DamageCell(xm,ym,255,dam);
				Weapon* NW=AO->Wpn->NextWeapon;
				if(int(NW)){
					CreateExObj(NW,AO->x,AO->y,0,0,0,AO->NMask,AO->Sender);	
				};
				if(prob<AO->Wpn->Probab1){
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
				};
				if(prob<AO->Wpn->Probab2){
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
				};
				AO->Force-=AO->Decrement;
				if(AO->Force<=0)CloseExu(i);
			};
rdea:
			word MID=Mops[ym][xm];
				//GetEnemy(AO->x,AO->y,AO->NMask);
				//Mops[ym][xm];
			if(MID==0xFFFF)MID=FlyMops[ym][xm];
			if(MID!=0xFFFF&&(AO->xm0!=xm||AO->ym0!=ym)&&AO->Force>0){
				if(!AO->Canm){//AO->Nanm-1){
					OneObject* OB=Group[MID];
					Weapon* Wp=AO->Wpn;	
					if(!(AO->NMask&OB->NMask)){
						Weapon* NW=AO->Wpn->NextWeapon;
						if(!NW){
							//short dam=AO->MinDamage+
							//	((int(AO->MaxDamage-AO->MinDamage)*rando())>>15);
							//if(OB->Life>dam)OB->Life-=dam;else OB->Life=0;
							OB->MakeDamage(AO->MaxDamage,AO->MinDamage,AO->Sender);
						};
						short prob=rando()>>7;
						if(int(NW)){
							CreateExObj(NW,AO->x,AO->y,0,0,0,AO->NMask,AO->Sender);	
						};
						if(prob<AO->Wpn->Probab1){
							CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
						};
						if(prob<AO->Wpn->Probab2){
							CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
							CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,64,16,64,AO->NMask,AO->Sender);
						};
						AO->Force-=AO->Decrement;
					};
				};
			};
			AO->Path+=AO->v;
			if(AO->Path>AO->MaxPath||(xm==AO->destX&&ym==AO->destY)){
				if(AO->T3X3){
					for(int dx=-1;dx<2;dx++)
						for(int dy=-1;dy<2;dy++){
							word MID=Mops[ym+dy][xm+dx];
							if(MID!=0xFFFF){
								OneObject* OB=Group[MID];
								if(OB&&!(OB->Sdoxlo||OB->NMask&AO->NMask)){
									if(dx||dy)OB->MakeDamage(AO->MaxDamage>>2,AO->MinDamage>>2,AO->Sender);
									else OB->MakeDamage(AO->MaxDamage,AO->MinDamage,AO->Sender);
								};
							};
							if(AO->AATT){
								MID=FlyMops[ym+dy][xm+dx];
								if(MID!=0xFFFF){
									OneObject* OB=Group[MID];
									if(OB&&!(OB->Sdoxlo||OB->NMask&AO->NMask)){
										if(dx||dy)OB->MakeDamage(AO->MaxDamage>>2,AO->MinDamage>>2,AO->Sender);
										else OB->MakeDamage(AO->MaxDamage,AO->MinDamage,AO->Sender);
									};
								};
							};
						};
				};
				if(AO->DestObj!=0xFFFF&&AO->P100){
					OneObject* OB=Group[AO->DestObj];
					if(OB){
						if(OB->Serial==AO->DSerial){
							//short dam=AO->MinDamage+
							//	((int(AO->MaxDamage-AO->MinDamage)*rando())>>15);
							OB->MakeDamage(AO->MaxDamage,AO->MinDamage,AO->Sender);
						};
					};
				};
				Weapon* NW=AO->Wpn->NextWeapon;
				if(int(NW))CreateExObj(NW,AO->x,AO->y,0,0,0,AO->NMask,AO->Sender);
				CloseExu(i);
				goto CycEnd;
			};
			if(AO->Visible){
				//byte zx=AO->xm-mapx+4;
				//byte zy=AO->ym-mapy+4;
				//if(nv[zy][zx]<2)
				{
				//	nv[zy][zx]++;
					OneSlide* Oc1=&(AO->Kino[AO->Canm]);
					if(AO->Transparent==2){
						if(AO->Direction<5)
							ShowRLCItemMutno((AO->x>>2)-(mapx*32)+smapx+Oc1->dx,
										(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
									&MImage[Oc1->FileID],Oc1->spr);else
							ShowRLCItemMutno((AO->x>>2)-(mapx*32)+smapx+32-Oc1->dx,
										(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
									&MImage[Oc1->FileID],Oc1->spr+4096);
					}else if(AO->Transparent==4){
						if(AO->Direction<5)
							ShowRLCItemFired((AO->x>>2)-(mapx*32)+smapx+Oc1->dx,
										(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
									&MImage[Oc1->FileID],Oc1->spr);else
							ShowRLCItemFired((AO->x>>2)-(mapx*32)+smapx+32-Oc1->dx,
										(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
									&MImage[Oc1->FileID],Oc1->spr+4096);
					}else{
						if(AO->Direction<5)
						ShowRLCItem((AO->x>>2)-(mapx*32)+smapx+Oc1->dx,
									(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
								&MImage[Oc1->FileID],Oc1->spr,0);else
						ShowRLCItem((AO->x>>2)-(mapx*32)+smapx+32-Oc1->dx,
									(AO->y>>2)-(mapy*32)+smapy+Oc1->dy,
								&MImage[Oc1->FileID],Oc1->spr+4096,0);
					
					};
				};
			};
			AO->Canm++;
			if(AO->OneTime&&AO->Canm>=AO->Nanm){
				short prob=rando()>>7;
				Weapon* NW=AO->Wpn->NextWeapon;	
				Weapon* Wp=AO->Wpn;
				if(int(NW)){
				CreateExObj(NW,AO->x,AO->y,0,0,0,AO->NMask,AO->Sender);
				};
					if(prob<AO->Wpn->Probab1){		
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,8,16,64,AO->NMask,AO->Sender);
				};
				/*int pr2=div(AO->Wpn->Probab2*(MaxExpl-nEused),MaxExpl).quot;
					if(prob<pr2){	
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,8,0,128);
					CreateRandObj(Wp,AO->x,AO->y,AO->PhDir,8,0,128);
				};*/
			};
			if(AO->WATT&&WLock[ym][xm])
				CloseExu(i);
			if(AO->Canm>=AO->Nanm){
				if(AO->OneTime){
					Weapon* Wp=AO->Wpn;
					word MID=Mops[ym][xm];
					if(MID==0xFFFF)MID=FlyMops[ym][xm];
					if(MID!=0xFFFF){
						OneObject* OB=Group[MID];
						//short dam=AO->MinDamage+
						//((int(AO->MaxDamage-AO->MinDamage)*rando())>>15);
						//if(OB->Life>dam)OB->Life-=dam;else OB->Life=0;
						OB->MakeDamage(AO->MaxDamage,AO->MinDamage,AO->Sender);
					};
					CloseExu(i);
				}else AO->Canm=0;
			};
CycEnd:
			AO->x+=AO->vx;
			AO->y+=AO->vy;
		};
	};
};
void Nation::AssignWeapon(Weapon* Wpn,int i){
	if(i<NMon){
		Mon[i]->Weap=Wpn;
	};
}




