/* Properties of the selected objects viewering and *
 * corresponding mouse handling                     */
#include "ddini.h"
#include "ResFile.h"
#include "FastDraw.h"
#include "mgraph.h"
#include "mouse.h"
#include "menu.h"
#include "MapDiscr.h"
#include "mode.h"
#include "Nature.h"
#include "fonts.h"
#include "TopZones.h"
#include "walls.h"
#include "Megapolis.h"
#include "GSound.h"
#include "IconTool.h"
#include "GP_Draw.h"
#include "ConstStr.h"
#include "GSINC.H"
#include "ActiveScenary.h"
void EconomyInterface(IconSet* ISET);
void ClearEconomy();
extern int UNGROUP_ICON;
extern int DOGROUP_ICON;
extern int GroupIconPos;
bool CheckGroupPossibility(byte NI);
bool CheckUnGroupPossibility(byte NI);
IconSet  PrpPanel;
IconSet  AblPanel;
IconSet  UpgPanel;
IconSet BrigPanel;
extern byte   WeaponFlags[32];
extern int MessageUX;
extern int MessageUY;
extern int SGenIcon;
extern int PanelY;
extern int IconLx;
void GetMonCost(byte NI,word NIndex,char* st);
void AssignHintLo(char* s,int time);
extern short WeaponIcn [32];
extern short ProtectIcn[32];
char* GetSprResourceName(OneObject* OB);
#define MaxO 200
void AssignHint1(char* s,int time);
bool SelSoundDobe;
bool SelSoundReady;
int SelSoundType;
int CreateRZone(int x,int y,int lx,int ly,HandlePro* HPro,HandlePro* RHPro,int Index,char* Hint);
int PrpX;
int PrpY;
int PrpNx;
int PrpNy;
int AblX;
int AblY;
int AblNx;
int AblNy;
static bool PropClean=false;
static bool AbltClean=false;
int IconLx;
int IconLy;
int AddIconLx;
int AddIconLy;
extern int FILLFORM_ICON;
int FillF_Pos=12;
struct MonInf{
	GeneralObject* RF;
	int Life;
	int MaxLife;
	int Magic;
	int MaxMag;
	int N;
	word Last;
	word ID;
};
struct AblInf{
	Nation* NT;
	word OInd;
	word Kind;
	word UPIND;
	char HotKey;
	char IconIndex;
};
MonInf MList[MaxO];
AblInf AList[MaxO];
word ArmList[MaxO];
int GetProgress(word ID,int* MaxProgress);
int GetAmount(word ID);
int SubIcon;
static GeneralObject* LastGO;
static Nation* LastNT;
static word LastAmount;
static word LastID;
extern int curptr;
extern int curdx;
extern int curdy;
//uniq properties
bool GetCoord;
UniqMethood* UNIM;
void InitPrpBar(){
	PrpNx=4;
	PrpNy=2;
	PrpX=10;
	PrpY=(msy>>1)+miniy+16;
	AblX=PrpX;
	AblY=PrpY+PrpNy*(IconLy+2)+16;
	AblNx=PrpNx;
	AblNy=6;
	SubIcon=-1;
};
void ResFon(int x,int y,int Lx,int Ly){

};
void ScrCopy(int x,int y,int Lx,int Ly){
	if(!bActive)return;
	//if(DDebug){
//
//		return;
//	};
	int x1=(x&(65535-3));
	int lx=((x+Lx+4)&(65535-3))-x1;
	int StDy=RSCRSizeX-lx;
	int FONDy=SCRSizeX-lx;
	int DsOf=int(RealScreenPtr)+x1+y*RSCRSizeX;
	int SrOf=int(ScreenPtr)+x1+y*SCRSizeX;
	int lx1=lx>>2;
	__asm{
		push	esi
		push	edi
		cld
		mov		eax,Ly
		mov		esi,SrOf
		mov		edi,DsOf
		mov		ebx,StDy
jj1:	mov		ecx,lx1
		rep		movsd
		add		esi,FONDy
		add		edi,ebx
		dec		eax	
		jnz		jj1
	};
};
int NINF,NABL,NARMINF;
void GetUnitCost(byte NI,word NIndex,int* Cost);
void GetMonCost(byte NI,word NIndex,char* st){
	Nation* NT=&NATIONS[NI];
	GeneralObject* GO=NT->Mon[NIndex];
	char uu[128];
	bool AddSp=false;
	uu[0]=0;
	AdvCharacter* AC=GO->MoreCharacter;
	int Cost[8];
	GetUnitCost(NI,NIndex,Cost);
	strcat(st," -");
	for(int i=0;i<8;i++){
		if(AC->NeedRes[i]){
			//if(AddSp)strcat(st," -");
			sprintf(uu," %s: %d",RDS[i].Name,Cost[i]);
			strcat(st,uu);
			AddSp=true;
		};
	};
};
void GeneralObject::GetMonsterCostString(char* st){
	st[0]=0;
};
void Nation::GetUpgradeCostString(char* st,word UI){
	char uu[128];
	bool AddSp=false;
	for(int i=0;i<8;i++){
		if(UPGRADE[UI]->Cost[i]){
			if(AddSp)strcat(st," ");
			sprintf(uu,"%s:%d",RDS[i].Name,int(UPGRADE[UI]->Cost[i]));
			strcat(st,uu);
			AddSp=true;
		};
	};
};
word SELSET[32];
int NSelSet=0;
void HPSEL(int i){
	if(GetKeyState(VK_CONTROL)&0x8000){
		CmdChooseUnSelType(MyNation,i);
	}else{
		if(GetKeyState(VK_SHIFT)&0x8000){
			if(NSelSet<32){
				SELSET[NSelSet]=i;
				NSelSet++;
			};
		}else{
			CmdChooseSelType(MyNation,i);
		};
	};
};
void HPSELBRIG(int i){
	if(GetKeyState(VK_CONTROL)&0x8000){
		CmdChooseUnSelBrig(MyNation,i);
	}else{
		if(GetKeyState(VK_SHIFT)&0x8000){
			if(NSelSet<32){
				SELSET[NSelSet]=i+32768;
				NSelSet++;
			};
		}else{
			CmdChooseSelBrig(MyNation,i);
		};
	};
};
bool IsItInSelSet(word ID){
	for(int i=0;i<NSelSet;i++)if(SELSET[i]==ID)return true;
	return false;
};
void FREEORD(int i){
	CmdErseBrigs(MyNation);
};
void MSTANDGR(int i){
	CmdMakeStandGround(MyNation);
};
void CSTANDGR(int i){
	CmdCancelStandGround(MyNation);
};
extern int Zone1X;
extern int Zone1Y;
extern int Zone1LX;
extern int Zone1LY;
extern int BrigPnX;
extern int BrigPnY;
extern int BrigNx;
extern int BrigNy;
extern int PreviewBrig;
bool FullBrigMode=false;
void OLIHPRO(int i){
	FullBrigMode=!FullBrigMode;
};
void SELBRIG(int i){
	if(GetKeyState(VK_SHIFT)&0x8000){
		CmdSelBrig(MyNation,1,i);
	}else{
		CmdSelBrig(MyNation,0,i);
		//FullBrigMode=false;
	};
};
void CmdSetSrVictim(byte NI,byte val);
void PreBrig(int i){
	PreviewBrig=i;
};
void EATTACK_Pro(int i){
	CmdSetSrVictim(MyNation,0);
};
void DATTACK_Pro(int i){
	CmdSetSrVictim(MyNation,1);
};
extern int PATROL_ICON;
extern bool PATROLMODE;
void DOPATROL(int i){
	PATROLMODE=1;
};
void PATROL_Pro(int i){
};
void GOATTA_Pro(int i){
};
void CmdMakeReformation(byte,word,byte);
void REFORMA(int i){
	CmdMakeReformation(MyNation,i&65535,i>>16);
};
void CmdFillFormation(byte NI,word BrigadeID);
void FILLFORM(int i){
	CmdFillFormation(MyNation,i);
};
bool GoAndAttackMode=0;
void GONATTACK(int i){
	GoAndAttackMode=1;
};
extern City CITY[8];
extern int GOAT_Icon;
extern int GOAT_PX;
extern int GOAT_PY;
extern int HISTORY_Icon;
void ShowHistory();
void HISTORY_Call(int i){
	ShowHistory();
};
extern bool GoAndAttackMode;
extern char** NatNames;
CEXPORT char* GetTextByID(char* ID);
extern int STOP_ICON;
bool BreefUInfo=0;
extern int ATTGR_ICON;
extern int AttGrPos;
void ATTGR_PRO(int p);
void CmdDoGroup(byte);
void CmdUnGroup(byte);
void COM_DOGROUP(int i){
	CmdDoGroup(MyNation);
};
void COM_UNGROUP(int i){
	CmdUnGroup(MyNation);
};
void ShowProp(){
	//return;
	byte c;
	NINF=0;
	NARMINF=0;
	InitZones();
    PrpPanel.ClearIconSet();
    AblPanel.ClearIconSet();
	UpgPanel.ClearIconSet();
	BrigPanel.ClearIconSet();
	word MID;
	OneObject* OBJ;
	GeneralObject* GO;
	MonInf* MI;
	int i,j;
	//ResFon(PrpX,PrpY,PrpNx*IconLx,PrpNy*IconLy);
	word Nsel=ImNSL[MyNation];
	word* SMon=ImSelm[MyNation];
	if(Nsel){
		if(SelSoundReady){
			if(SMon[0]!=0xFFFF){
				OneObject* OB=Group[SMon[0]];
				if(OB){
					if(SelSoundType)AddOrderEffect(OB->x>>1,OB->y>>1,OB->Ref.General->OrderSound);
					else AddOrderEffect(OB->x>>1,OB->y>>1,OB->Ref.General->ClickSound);
					SelSoundReady=false;
				};
			};
		};
		bool StandGround=false;
		bool NotStandGround=false;						
		bool UnitsPres=false;
		bool SrVictim=false;
		bool NoSrVictim=false;
		bool PrTowers=0;
		bool PrBuildings=0;
		word CurBrig=0xFFFE;
		for(i=0;i<Nsel;i++){
			MID=SMon[i];
			if(MID!=0xFFFF){
				OBJ=Group[MID];
				if(int(OBJ)&&!OBJ->Sdoxlo){
					if(OBJ->newMons->Usage==TowerID)PrTowers=1;
					else if(OBJ->NewBuilding)PrBuildings=1;
					if(CurBrig==0xFFFE){
						CurBrig=OBJ->BrigadeID;
					}else{
						if(CurBrig!=OBJ->BrigadeID)CurBrig=0xFFFF;
					};
					if(OBJ->newMons->CanStandGr)UnitsPres=true;
					if(OBJ->StandGround){
						StandGround=true;
					}else{
						NotStandGround=true;
					};
					if(OBJ->NoSearchVictim) NoSrVictim=true;else SrVictim=true;
					GO=OBJ->Ref.General;
					int MyID=OBJ->NIndex;
					if(OBJ->InArmy&&NARMINF<MaxO){
						word id=OBJ->BrigadeID;
						for(int k=0;k<NARMINF&&ArmList[k]!=id;k++);
						if(k>=NARMINF){
							ArmList[NARMINF]=id;
							NARMINF++;
						};
					}else{
						for(j=0;j<NINF;j++){
								if(GO==MList[j].RF)break;
						};
						MI=&(MList[j]);
						if(j>=NINF){
							for(int q=0;q<NINF;q++){
								if(MList[q].ID>MyID){
									for(int p=NINF;p>q;p--)
										MList[p]=MList[p-1];
									j=q;
									MI=MList+q;
									q=NINF;
								};
							};
							MI->Life=0;
							MI->MaxLife=0;
							MI->MaxMag=0;
							MI->N=0;
							NINF++;
							MI->Last=0;
							MI->ID=0;
						};
						MI->RF=GO;
						MI->Life+=OBJ->Life;
							MI->MaxLife+=OBJ->MaxLife;
						//MI->Magic+=OBJ->Magic;
						MI->N++;
							if(MI->N==1&&!OBJ->Ready)MI->Last=MID;
						if(OBJ->Ready)MI->Last=MID;
						MI->ID=OBJ->NIndex;
					};
				};
			};
		};
		int PN=PrpNx*PrpNy;
		if(NINF>PN)NINF=PN;
		int	xx=0;
		int x1=PrpX;
		int y1=PrpY;
		OneSlide* OC;
		char str[32];
		for(i=0;i<NINF;i++){
			MI=&(MList[i]);
			OBJ=Group[MI->Last];
			NewMonster* NM=OBJ->newMons;
			char sxt[128];
			GetChar(MI->RF,sxt);
	        OneIcon* OI=PrpPanel.AddIcon(NM->IconFileID,NM->IconID,0xD0+(NatRefTBL[MyNation]<<2),sxt);
		    OI->AssignIntVal(MI->N);
			OI->AssignHealth(MI->Life,MI->MaxLife);
			if((!OBJ->Ready)&&OBJ->NUstages)
            OI->AssignStage(OBJ->Ustage,OBJ->NUstages);
			OI->AssignLeft(&HPSEL,OBJ->NIndex);
			if(NINF==1&&i==0&&!NARMINF){
				if(BreefUInfo){
					AssignHint(OBJ->Ref.General->Message,5);
				}else{
					char ccc[130];
					sprintf(ccc,"%s (%s)",OBJ->Ref.General->Message,NatNames[OBJ->Ref.General->NatID]);
					AssignHint(ccc,5);
				};
			}else{
				if(NSelSet){
					if(GetKeyState(VK_SHIFT)&0x8000){
						if(IsItInSelSet(OBJ->NIndex)){
							OI->SelectIcon();
						};
					}else{
						if(!IsItInSelSet(OBJ->NIndex)){
							CmdChooseUnSelType(MyNation,OBJ->NIndex);
						};
					};
				};
			};
		};
		for(i=0;i<NARMINF;i++){
			int bid=ArmList[i];
			if(bid!=0xFFFF){
				City* CT=NATIONS[NatRefTBL[MyNation]].CITY;
				Brigade* BR=CT->Brigs+bid;
				GeneralObject* GO=NATIONS[MyNation].Mon[BR->MembID];
				NewMonster* NM=GO->newMons;
				OneIcon* OI=PrpPanel.AddIcon(NM->IconFileID,NM->IconID,0xD0+(NatRefTBL[MyNation]<<2),ARMYSTR);//"Army"
				int N=0;
				int Life=0;
				int MaxLife=0;
				int NU=BR->NMemb;
				for(int j=2;j<NU;j++){
					word MID=BR->Memb[j];
					if(MID!=0xFFFF){
						OneObject* OB=Group[MID];
						if(OB&&OB->Serial==BR->MembSN[j]){
							N++;
							Life+=OB->Life;
							MaxLife+=OB->MaxLife;
						};
					};
				};
				if(N){
					OI->AssignIntVal(N);
				};
				if(MaxLife){
					OI->AssignHealth(Life,MaxLife);
				};
				OI->AssignLeft(&HPSELBRIG,bid);
				OI->AssignIntParam(bid+1);
				if(NSelSet){
					if(GetKeyState(VK_SHIFT)&0x8000){
						if(IsItInSelSet(bid+32768)){
							OI->SelectIcon();
						};
					}else{
						if(!IsItInSelSet(bid+32768))CmdChooseUnSelBrig(MyNation,bid);
					};
				};
			};
		};
		if(NARMINF==1&&!NINF){
			int bid=ArmList[0];
			if(bid!=0xFFFF){
				City* CT=NATIONS[NatRefTBL[MyNation]].CITY;
				Brigade* BR=CT->Brigs+bid;
				GeneralObject* GO=NATIONS[NatRefTBL[MyNation]].Mon[BR->MembID];
				NewMonster* NM=GO->newMons;
				//Xbar(Zone1X,PanelY+Zone1Y+1,Zone1LX,Zone1LY,0xD0+(MyNation<<2));
				//Xbar(Zone1X-1,PanelY+Zone1Y,Zone1LX+2,Zone1LY+2,0xD0+(MyNation<<2)+1);
				MonInf* MI=&(MList[0]);
				char str[128];
				int DYY=-7;
				int x1=Zone1X+IconLx+4+6-4;
				int y1=PanelY+Zone1Y+6+DYY;
				AdvCharacter* ADC=GO->MoreCharacter;
				int NN=0;
				for(int i=0;i<NAttTypes;i++){
					if(ADC->MaxDamage[i]&&NN<2){
						int wk=ADC->WeaponKind[i];
						GPS.ShowGP(x1+NN*40,y1,1,WeaponIcn[wk],0);
						int dm=ADC->MaxDamage[i];
						if((WeaponFlags[wk]&4)&&BR->AddDamage){
							if(BR->AddDamage>=0)sprintf(str,"%d+%d",dm,BR->AddDamage);
							else sprintf(str,"%d-%d",dm,-BR->AddDamage);
							ShowString(x1+NN*43+21,y1+5,str,&fn10);
						}else{
							sprintf(str,"%d",dm);
							ShowString(x1+NN*43+21,y1+5,str,&fn10);
						};
						NN++;
					};
				};
				y1+=21;
				GPS.ShowGP(x1,y1,1,SGenIcon,0);
				if(BR->AddShield){
					if(BR->AddShield>=0)sprintf(str,"%d+%d",ADC->Shield,BR->AddShield);
					else sprintf(str,"%d-%d",ADC->Shield,-BR->AddShield);
				}else{
					sprintf(str,"%d",ADC->Shield);
				};
				ShowString(x1+21,y1+12+DYY,str,&fn10);
				y1=PanelY+Zone1Y+IconLx+10+9+DYY;
				x1=Zone1X+4;
				NN=0;
				for(i=0;i<16;i++){
					if(ADC->Protection[i]&&NN<6){
						int ix=x1+(NN>>1)*41;
						int iy=y1+(NN&1)*21;
						GPS.ShowGP(ix,iy,1,ProtectIcn[i],0);
						int dm=ADC->Protection[i];
						sprintf(str,"%d",dm);
						ShowString(ix+20,iy+5,str,&fn10);
						NN++;
					};
				};
				if(BR->WarType){
					OrderDescription* ODE=ElementaryOrders+BR->WarType-1;
					if(ODE->GroupID!=0xFF){
						SingleGroup* FGD=FormGrp.Grp+ODE->GroupID;
						for(int j=0;j<FGD->NCommon;j++){
							OneIcon* OI=AblPanel.AddIconFixed(0,OrderDesc[FGD->IDX[j]].IconID,OrderDesc[FGD->IDX[j]].IconPos);
							OI->CreateHint(OrderDesc[FGD->IDX[j]].Message);
							OI->AssignLeft(&REFORMA,BR->ID+(int(FGD->IDX[j])<<16));
						};
					};
					OneIcon* OI=AblPanel.AddIconFixed(0,FILLFORM_ICON,FillF_Pos);
					OI->AssignLeft(&FILLFORM,BR->ID);
					OI->CreateHint(GetTextByID("FILLFRM"));
					if(GO->newMons->Artpodgotovka&&!SCENINF.hLib){
						OneIcon* OI=AblPanel.AddIconFixed(0,ATTGR_ICON,AttGrPos);
						OI->CreateHint(ATGHINT);
						OI->AssignLeft(&ATTGR_PRO,0);
					};
				};
			};
		};
		c=0xD0+(NatRefTBL[MyNation]<<2);
		if(NARMINF&&!NINF){
			OneIcon* OI=AblPanel.AddIconFixed(0,FREE_ORDER_ICON,12*2);
			OI->AssignColor(c);
			OI->CreateHint(SFREORD);//"Распустить отряд."
			OI->AssignLeft(&FREEORD,0);
		};
	 //PrpPanel.DrawIconSet(PrpX+3,PrpY+3,PrpNx,PrpNy,0);
		if(NARMINF<=12&&!NINF){
			if(CheckUnGroupPossibility(MyNation)){
				OneIcon* OI=AblPanel.AddIconFixed(0,UNGROUP_ICON,GroupIconPos);
				OI->CreateHint(GetTextByID("CM_UNGRP"));
				OI->AssignLeft(&COM_UNGROUP,0);
			}else if(CheckGroupPossibility(MyNation)){
				OneIcon* OI=AblPanel.AddIconFixed(0,DOGROUP_ICON,GroupIconPos);
				OI->CreateHint(GetTextByID("CM_DOGRP"));
				OI->AssignLeft(&COM_DOGROUP,0);
			};
		};
		if(UnitsPres&&(NINF||NARMINF)){
			if(NINF+NARMINF<=24){
				OneIcon* OI=AblPanel.AddIconFixed(0,STAND_GROUND_ICON,12*2+1);
				OI->CreateHint(STANDGR);//"Stand ground"
				OI->AssignColor(c);
				if(NARMINF==1&&!NINF){
					int bid=ArmList[0];
					if(bid!=0xFFFF){
						City* CT=NATIONS[NatRefTBL[MyNation]].CITY;
						Brigade* BR=CT->Brigs+bid;
						if(BR->WarType&&BR->BrigDelay){
							OI->AssignHealth(150-BR->BrigDelay,150);
						};
					};
				};
				if(StandGround)OI->SelectIcon();
				OI->AssignLeft(&MSTANDGR,0);
				OI=AblPanel.AddIconFixed(0,NOT_STAND_GROUND_ICON,12*2+2);
				if(NotStandGround)OI->SelectIcon();
				OI->CreateHint(NOSTAND);//"Cancel stand ground"
				OI->AssignColor(c);
				OI->AssignLeft(&CSTANDGR,0);

				OI=AblPanel.AddIconFixed(0,GOAT_Icon,GOAT_PX+GOAT_PY*12);
				OI->CreateHint(GONATT);
				OI->AssignColor(c);
				OI->AssignLeft(&GONATTACK,0);
				if(GoAndAttackMode)OI->SelectIcon();
			};
			
			if(UnitsPres&&NINF&&NINF+NARMINF<=12){
				OneIcon* OI=AblPanel.AddIconFixed(0,PATROL_ICON,14);
				OI->CreateHint(HPATROL);
				//OI->AssignColor(c);
				OI->AssignLeft(&DOPATROL,0);
			};
		};
		if((PrTowers&&!PrBuildings)||(UnitsPres&&(NINF||NARMINF)&&NINF+NARMINF<=24)){

			OneIcon* OI=AblPanel.AddIconFixed(0,EATT_Icon,EATT_X+EATT_Y*12);
			OI->CreateHint(EATTACK);
			OI->AssignLeft(&EATTACK_Pro,0);
			if(SrVictim)OI->SelectIcon();
			OI=AblPanel.AddIconFixed(0,DATT_Icon,DATT_X+DATT_Y*12);
			OI->CreateHint(DATTACK);
			OI->AssignLeft(&DATTACK_Pro,0);
			if(NoSrVictim)OI->SelectIcon();
		};
	};
	int N=BrigNx*(BrigNy-1);
	int P=0;
	Brigade* BR0=CITY[NatRefTBL[MyNation]].Brigs;
	for(j=0;j<N;j++){
		if(BR0[j].Enabled)P++;
	};
	if(P){
		OneIcon* OI=BrigPanel.AddIconFixed(0,ORDERS_LIST_ICON,0);
		OI->AssignLeft(&OLIHPRO,0);
		if(FullBrigMode){
			for(int j=0;j<N;j++){
				Brigade* BR=BR0+j;
				if(BR->Enabled){
					bool UNFND=true;
					bool SEL=false;
					for(int i=2;i<BR->NMemb&&UNFND;i++){
						word MID=BR->Memb[i];
						if(MID!=0xFFFF){
							OneObject* OB=Group[MID];
							if(OB&&OB->Serial==BR->MembSN[i]){
								UNFND=false;
								SEL=OB->Selected&GM(MyNation);
							};
						};
					};
					if(!UNFND){
						GeneralObject* GO=NATIONS[NatRefTBL[MyNation]].Mon[BR->MembID];
						NewMonster* NM=GO->newMons;
						OI=BrigPanel.AddIconFixed(NM->IconFileID,NM->IconID,j+BrigNx);
						OI->AssignLeft(&SELBRIG,j);
						int M=BR->BM.Infantry+BR->BM.Grenaderov+BR->BM.Strelkov+BR->BM.Peons;
						if(BR->Memb[0]!=0xFFFF)M--;
						if(BR->Memb[1]!=0xFFFF)M--;
						OI->AssignIntVal(M);
						OI->AssignMoveOver(&PreBrig,BR->ID);
						OI->AssignIntParam(j+1);
						if(SEL)OI->SelectIcon();
					};
				};
			};
		};
	};
	/*
	if(NATIONS[MyNation].NHistory){
		OneIcon* OI=BrigPanel.AddIconFixed(0,HISTORY_Icon,1);
		OI->AssignLeft(&HISTORY_Call,0);
	};
	*/
	if(NSelSet&&!(GetKeyState(VK_SHIFT)&0x8000))NSelSet=0;
};

int GetRLCStrWidth(char* str,lpRLCFont lpf);
extern byte PlayGameMode;
char* ARTCAPS[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
void ShowTextDiscription(){
	if(PlayGameMode==1)return;
    if(NINF==1){
		//Xbar(Zone1X,PanelY+Zone1Y+1,Zone1LX,Zone1LY,0xD0+(MyNation<<2));
		//Xbar(Zone1X-1,PanelY+Zone1Y,Zone1LX+2,Zone1LY+2,0xD0+(MyNation<<2)+1);
		MonInf* MI=&(MList[0]);
		OneObject* OBJ=Group[MI->Last];
		if(!OBJ)return;
		if(OBJ->Kills){
			char str[128];
			sprintf(str,KILLUNI,OBJ->Kills);//"Убил:%d"
			ShowString(Zone1X+10,PanelY+Zone1Y-20,str,&fn10);
		};
		if(OBJ->Ready){
			int DYY=-7;
			char str[128];
			int x1=Zone1X+IconLx+4+6-4;
			int y1=PanelY+Zone1Y+6+DYY;
			AdvCharacter* ADC=OBJ->Ref.General->MoreCharacter;
			NewMonster* NM=OBJ->newMons;
			int NN=0;

			int EFFICACY=1000;
			if(NM->ShotPtZ){
				int NS=0;
				int MAXS=OBJ->Ref.General->MoreCharacter->MaxInside;
				for(int i=0;i<OBJ->NInside;i++){
					word MID=OBJ->Inside[i];
					if(MID!=0xFFFF){
						OneObject* IOB=Group[MID];
						if(IOB&&!IOB->Sdoxlo){
							byte USE=IOB->newMons->Usage;
							if(USE==StrelokID||USE==HorseStrelokID||USE==ArcherID)NS++;
						};
					};
				};
				if(MAXS){
					EFFICACY=(NS*1000)/MAXS;
				};
			};

			for(int i=0;i<NAttTypes;i++){
				if(ADC->MaxDamage[i]&&NN<2){
					GPS.ShowGP(x1+NN*43+1,y1+1,1,WeaponIcn[ADC->WeaponKind[i]],0);
					int DMIN=NM->MinDamage[i];
					int dm=ADC->MaxDamage[i];

					dm=DMIN+(((dm-DMIN)*EFFICACY)/1000);

					//dm=(dm+(dm>>1))>>1;
					if(OBJ->AddDamage>0)sprintf(str,"%d+%d",dm,OBJ->AddDamage);
					else if(OBJ->AddDamage<0)sprintf(str,"%d-%d",dm,-OBJ->AddDamage);
					else sprintf(str,"%d",dm);
					ShowString(x1+NN*43+21,y1+5,str,&fn10);
					NN++;
				};
			};
			sprintf(str,"%d",int(OBJ->Life));
			int LLL=GetRLCStrWidth(str,&fn10);
			ShowString(Zone1X+(IconLx-LLL>>1)+6,PanelY+Zone1Y+IconLx+1+6+DYY,str,&fn10);
			y1+=21;
			GPS.ShowGP(x1+1,y1+1,1,SGenIcon,0);
			if(OBJ->AddShield>0)sprintf(str,"%d+%d",ADC->Shield,OBJ->AddShield);
			else if(OBJ->AddShield<0)sprintf(str,"%d-%d",ADC->Shield,-OBJ->AddShield);
			else sprintf(str,"%d",ADC->Shield);
			ShowString(x1+21,y1+12+DYY,str,&fn10);
			y1=PanelY+Zone1Y+IconLx+10+9+DYY;
			x1=Zone1X+4;
			NN=0;
			for(i=0;i<16;i++){
				if(ADC->Protection[i]&&NN<6){
					int ix=x1+(NN>>1)*41;
					int iy=y1+(NN&1)*21;
					GPS.ShowGP(ix+3,iy+1,1,ProtectIcn[i],0);
					int dm=ADC->Protection[i];
					//  ;-)  //dm=((dm+1)*100)>>8;
					sprintf(str,"%d",dm);
					ShowString(ix+22,iy+5,str,&fn10);
					NN++;
				};
			};
			if(NM->FishAmount){
				sprintf(str,FISHSTR,OBJ->Ustage,ADC->FishAmount);//"Рыба:%d/%d"
				ShowString(x1,y1,str,&fn10);
				y1+=12;
			};
			if(NM->Farm){
				Nation* NT=OBJ->Nat;
				/*
				City* CT=NT->CITY;
				sprintf(str,"Всего ферм:%d",CT->ReadyAmount[OBJ->NIndex]);
				ShowString(x1,y1,str,&fn10);
				y1+=12;
				sprintf(str,"Нужно:%d",div(NT->NGidot,UnitsPerFarm).quot+1);
				ShowString(x1,y1,str,&fn8);
				y1+=12;
				*/
				sprintf(str,HABITAN,NT->NGidot);//"Обитателей:%d"
				ShowString(x1+3,y1,str,&fn10);
				y1+=12;
				sprintf(str,MAXHABI,NT->NFarms);//"Макс.обитателей:%d"
				ShowString(x1+3,y1,str,&fn10);
				y1+=12;

			};
			if(NM->ArtDepo){
				if(!ARTCAPS[0]){
					ARTCAPS[0]=GetTextByID("__ARTCAP0");
					ARTCAPS[1]=GetTextByID("__ARTCAP2");
					ARTCAPS[2]=GetTextByID("__ARTCAP1");
					ARTCAPS[3]=GetTextByID("__ARTCAP3");
				};
				Nation* NT=OBJ->Nat;
				for(int i=0;i<4;i++){
					sprintf(str,ARTCAPS[i],NT->NArtUnits[i],NM->ArtCap[i]*NT->NArtdep);//"Обитателей:%d"
					ShowString(x1+3,y1,str,&fn10);
					y1+=16;
				};

			};
			if(ADC->MaxInside){
				sprintf(str,INSISTR,OBJ->NInside);//"Внутри:%d"
				ShowString(x1,y1,str,&fn10);
				y1+=16;
				if(OBJ->AddInside){
					sprintf(str,MAXINSI,int(ADC->MaxInside),OBJ->AddInside);//"Макс.Внутри:%d+%d"
					ShowString(x1,y1,str,&fn10);
					y1+=13;
				}else{
					sprintf(str,MAXINS1,int(ADC->MaxInside));//"Макс.Внутри:%d"
					ShowString(x1,y1,str,&fn10);
					y1+=13;
				};
				char* RNAME=GetSprResourceName(OBJ);
				if(RNAME){
					ShowString(x1,y1,RNAME,&fn10);
					y1+=13;
				};
			};
			/*
			if(OBJ->Repair){
				ShowString(x1,y1,"Ремонтник",&fn10);
				y1+=16;
			};
			*/
			if(OBJ->newMons->ShowDelay){
				int L=0;
				int LMAX=(Zone1LY+25);
				if(OBJ->MaxDelay){
					L=div(LMAX*OBJ->delay,OBJ->MaxDelay).quot;
				}; 
				if(L<LMAX){
					Vline(Zone1X+Zone1LX-5,PanelY+Zone1Y+1+L,PanelY+Zone1Y+LMAX-2,clrGreen);
					Vline(Zone1X+Zone1LX-4,PanelY+Zone1Y+1+L,PanelY+Zone1Y+LMAX-2,clrGreen);
					Vline(Zone1X+Zone1LX-3,PanelY+Zone1Y+1+L,PanelY+Zone1Y+LMAX-2,clrGreen);
					Vline(Zone1X+Zone1LX-2,PanelY+Zone1Y+1+L,PanelY+Zone1Y+LMAX-2,clrGreen);
					//Vline(Zone1X/*+Zone1LX-1*/+3,PanelY+Zone1Y+1+L,PanelY+Zone1Y+Zone1LY-2,clrGreen);
					//Vline(Zone1X/*+Zone1LX-1*/+4,PanelY+Zone1Y+1+L,PanelY+Zone1Y+Zone1LY-2,clrGreen);
				};
			};
		};
	};
};
extern bool BuildMode;
extern OneSlide* OSB;
extern byte blx;
extern byte bly;
extern word BuildingID;
extern Nation* BNat;
void CmdUnProduceObj(byte NI,word Type);
void RHPR(int i){
	AblInf* AI=&AList[i];
	Nation* NT=AI->NT;
	word j=AI->OInd;
	GeneralObject* GO=NT->Mon[j];
	if(!GO->newMons->Building){
		if(GetKeyState(VK_SHIFT)&0x8000){
			CmdUnProduceObj(MyNation,j);
			CmdUnProduceObj(MyNation,j);
			CmdUnProduceObj(MyNation,j);
			CmdUnProduceObj(MyNation,j);
			CmdUnProduceObj(MyNation,j);
		}else CmdUnProduceObj(MyNation,j);
	};
};
void CmdFieldBar(byte NI,word n);
bool CheckCostHint(byte NI,word NIndex);
int GetTotalUnits();
extern bool NOPAUSE;
void HPR(int i){
	//if(!NOPAUSE)return;
	if(GetTotalUnits()>LULIMIT){
		AssignHint1(UNILIMIT,50,32);
		return;
	};
	AblInf* AI=&AList[i];
	Nation* NT=AI->NT;
	word j=AI->OInd;
	GeneralObject* GO=NT->Mon[j];
	NewMonster* NM=GO->newMons;
	if(NM->SpriteObject&&!NM->Wall){
		CmdFieldBar(MyNation,j);
		return;
	};
	if(NM->Building||NM->Wall){
		if(NM->Wall||CheckCostHint(NatRefTBL[MyNation],j)){
			BuildMode=true;
			BuildingID=j;
			BNat=NT;
		};
	}else{
		if(CheckCostHint(NatRefTBL[MyNation],j)){
			if(GetKeyState(VK_SHIFT)&0x8000){
				CmdProduceObj(MyNation,j);
				CmdProduceObj(MyNation,j);
				CmdProduceObj(MyNation,j);
				CmdProduceObj(MyNation,j);
				CmdProduceObj(MyNation,j);
			}else CmdProduceObj(MyNation,j);
		};
	}
};
void HPR1(int i){
	//if(!NOPAUSE)return;
	Nation* NT=&NATIONS[MyNation];
	GeneralObject* GO=NT->Mon[i];
	NewMonster* NM=GO->newMons;
	if(NM->Building){
		BuildMode=true;
		BuildingID=i;
		BNat=NT;
	}else{
		if(GetKeyState(VK_SHIFT)&0x8000){
			CmdProduceObj(MyNation,i);
			CmdProduceObj(MyNation,i);
			CmdProduceObj(MyNation,i);
			CmdProduceObj(MyNation,i);
			CmdProduceObj(MyNation,i);
		}else CmdProduceObj(MyNation,i);
	}
};
void DoUPG(int i){
	AblInf* AI=&AList[i];
	Nation* NT=AI->NT;
	word j=AI->OInd;
	CmdPerformUpgrade(MyNation,j);
};
void DoUPG1(int i){
	CmdPerformUpgrade(MyNation,i);
};
void EnterIn(int i){
	if(i==0xFFFF)SubIcon=-1;
	WIcon* IC=NATIONS[MyNation].wIcons[i];
	if(!IC->SubList){
		SubIcon=-1;
		return;
	};
	SubIcon=i;
};
void OrderMove(int i,int x,int y){
	CmdSendToXY(MyNation,x,y,512);
};
void OrderAttack(int i,int x,int y){
	//word MID=GetOwner((x<<5)+16,(y<<5)+16);
	/*if(MID!=0xFFFF){
		OneObject* OB=Group[MID];
		byte Msk=1<<MyNation;
		if(OB->NMask&Msk)CmdAttackToXY(MyNation,x,y);
		else CmdAttackObj(MyNation,MID);
	}else CmdAttackToXY(MyNation,x,y);
	*/
};
void OrderPatrol(int i,int x,int y){
	CmdPatrol(MyNation,x,y);
};
void CmdSetRprState(byte NI,byte State);
void OrderRepair(int i,int x,int y){
	CmdSetRprState(MyNation,1);
};
void OrderNucAtt(int i,int x,int y){
	CmdNucAtt(MyNation,x,y);
};
void OrderSetDst(int i,int x,int y){
	CmdSetDst(MyNation,x,y);
};

word MaxMagic;
void UNIPARAM(int i){
	curptr=2;
	curdx=16;
	curdy=15;
	GetCoord=true;
	UNIM=NULL;
	switch(i){
	case 1://Move to xy
		UNIM=&OrderMove;
		break;
	case 2://Attack near (x,y)
		UNIM=&OrderAttack;
		break;
	case 5://Patrol
		UNIM=&OrderPatrol;
		break;
	case 6://Repair
		UNIM=&OrderRepair;
		break;
	case 7:
		//UNIM=&OrderGetResource;
		break;
	case 8:
		//UNIM=&OrderUnload;
		break;
	case 9:
		//UNIM=&OrderAttPt;
		break;
	case 10:
		UNIM=&OrderNucAtt;
		break;
	case 11:
		UNIM=&OrderSetDst;
		break;
	};
};
void NOPARAM(int i){
	UNIM=NULL;
	switch(i){
	case 3://Stop
		CmdStop(MyNation);
		break;
	case 4://Stand Ground
		CmdStandGround(MyNation);
		break;
	case 5:
		CmdSetRprState(MyNation,1);
		break;
	case 6:
		CmdSetRprState(MyNation,0);
		break;
	case 7://Build wall
		//SetBuildWallMode();
		break;
	};
};
void OrderPointN(int i,int x,int y){
	
};
void OrderPoint0(int i,int x,int y){
	OrderPointN(0,x,y);
};
void OrderPoint1(int i,int x,int y){
	OrderPointN(1,x,y);
};
void OrderPoint2(int i,int x,int y){
	OrderPointN(2,x,y);
};
void OrderPoint3(int i,int x,int y){
	OrderPointN(3,x,y);
};
void OrderPoint4(int i,int x,int y){
	OrderPointN(4,x,y);
};
void OrderPoint5(int i,int x,int y){
	OrderPointN(5,x,y);
};
void OrderPoint6(int i,int x,int y){
	OrderPointN(6,x,y);
};
void OrderPoint7(int i,int x,int y){
	OrderPointN(7,x,y);
};
void OrderPoint8(int i,int x,int y){
	OrderPointN(8,x,y);
};
void OrderPoint9(int i,int x,int y){
	OrderPointN(9,x,y);
};
void OrderPoint10(int i,int x,int y){
	OrderPointN(10,x,y);
};
void OrderPoint11(int i,int x,int y){
	OrderPointN(11,x,y);
};
void STRANGEWEAPON(int i){
	//if(MaxMagic<NATIONS[MyNation].WMagic[i])return;
	curptr=3;
	curdx=16;
	curdy=16;
	GetCoord=true;
	UNIM=NULL;

	switch(i){
	case 0:
		UNIM=&OrderPoint0;
		break;
	case 1:
		UNIM=&OrderPoint1;
		break;
	case 2:
		UNIM=&OrderPoint2;
		break;
	case 3:
		UNIM=&OrderPoint3;
		break;
	case 4:
		UNIM=&OrderPoint4;
		break;
	case 5:
		UNIM=&OrderPoint5;
		break;
	case 6:
		UNIM=&OrderPoint6;
		break;
	case 7:
		UNIM=&OrderPoint7;
		break;
	case 9:
		UNIM=&OrderPoint9;
		break;
	case 10:
		UNIM=&OrderPoint10;
		break;
	};
};
bool CreateInsideList(IconSet* IS,byte NI);
bool ECOSHOW;
extern byte PlayGameMode;
int ShowUniqAbility(){
	if(PlayGameMode==1)return 0;
	ECOSHOW=false;
	char sxt[128];
	if(MList[0].Last>LULIMIT)return false;
	GeneralObject* GO=MList[0].RF;
	OneObject* OB=Group[MList[0].Last];
	Nation* NT=OB->Nat;
	if(NT!=LastNT||MList[0].Last!=LastID||GO!=LastGO)SubIcon=-1;
	LastNT=NT;
	LastID=MList[0].Last;
	//MaxMagic=MList[0].MaxMag;
	LastGO=GO;
	int NABL;
	WIcon* SIC;
	if(SubIcon==-1)NABL=GO->NIcons;
	else{
		SIC=NT->wIcons[SubIcon];
		NABL=SIC->Param1;
		if(!SIC->SubList){
			SubIcon=-1;
			NABL=GO->NIcons;
		};
	};
    CreateInsideList(&AblPanel,MyNation);
	if(!NABL)return 0;
	WIcon* MI;
	int IREF;
	char str[32];
	int p,q,spr,fid;
	Visuals* VS;
    OneIcon* OI;
	for(int i=0;i<NABL;i++){
		bool DrawIt=true;
		if(SubIcon==-1){
			MI=NT->wIcons[GO->IRefs[i]];
			IREF=GO->IRefs[i];
		}else{
			MI=NT->wIcons[SIC->SubList[i]];
			IREF=SIC->SubList[i];
		};
		switch(MI->Kind){
		case 0:
			//directory entry
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&EnterIn,IREF);
			break;
		case 1://uniq without param
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&NOPARAM,MI->Param2);
			break;
		case 2://uniq with param
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&UNIPARAM,MI->Param2);
			break;
		case 3://perform upgrade
			{
				/*
				SimpleUTP* SU=NT->UPG.utp[MI->Param2];
				if(SU->Enabled){
                    strcpy(sxt,SU->Message);
					strcat(sxt," (");
					NT->GetUpgradeCostString(sxt,MI->Param2);
					strcat(sxt,")");
                    OI=AblPanel.AddIcon(MI->FileID,MI->Spr,240,sxt);
                    OI->AssignLeft(&DoUPG1,MI->Param2);
				}else DrawIt=false;
				*/
			};
			break;
		case 4://produce object
			GO=NT->Mon[MI->Param2];
			if(GO->Enabled){
				if(!MI->FileID){
					fid=GO->newMons->IconFileID;
					spr=GO->newMons->IconID;
				}else{
					fid=MI->FileID;
					spr=MI->Spr;
				};
                GetChar(GO,sxt);
                OI=AblPanel.AddIcon(MI->FileID,MI->Spr);
				OI->AssignColor(0xD0+(NatRefTBL[MyNation]<<2));
				OI->CreateHint(sxt);
                OI->AssignLeft(&HPR1,MI->Param2);
			}else DrawIt=false;
			break;
		case 5://strange weapon
			//if(NT->SWP[MI->Param1].Enabled){
			//	ShowRLCItem(x1,y1,&MImage[MI->FileID],MI->Spr,MyNation);
			//	CreateZone(x1,y1,IconLx,IconLy,&STRANGEWEAPON,MI->Param2,MI->Message);
			//}else DrawIt=false;
			break;
		};
	};
	if(GO->ExtMenu)return NABL;
	return -1;
};
bool ShowCommonAbl(){
	bool isAir=false;
	bool isWater=false;
	bool isLand=false;

    OneIcon* OI;
	char sxt[128];
	if(!(isAir||isLand||isWater))return false;
	Nation* NT=&NATIONS[MyNation];
	word NIcons;
	word* Icons=NULL;
	if(isAir&&!(isLand||isWater)){
		NIcons=NT->NAmenus;
		Icons=NT->Amenus;
	};
	if(isLand&&!(isAir||isWater)){
		NIcons=NT->NLmenus;
		Icons=NT->Lmenus;
	};
	if(isWater&&!(isAir||isLand)){
		NIcons=NT->NWmenus;
		Icons=NT->Wmenus;
	};
	if(!Icons){
		NIcons=NT->NCmenus;
		Icons=NT->Cmenus;
	};
	
	if(NT!=LastNT||LastID!=7777)SubIcon=-1;
	LastID=7777;
	LastNT=NT;
	int NABL;
	WIcon* SIC;
	if(SubIcon==-1)NABL=NIcons;
	else{
		SIC=NT->wIcons[SubIcon];
		NABL=SIC->Param1;
		if(!SIC->SubList){
			SubIcon=-1;
			NABL=NIcons;
		};
	};
	int AN=AblNx*AblNy;
	if(NABL>AN)NABL=AN;
	int xx=0;
	int x1=AblX;
	int y1=AblY;
	OneSlide* OC;
	WIcon* MI;
	int IREF;
	char str[32];
	int p,q,spr,fid;
	Visuals* VS;
	//MaxMagic=0;
	for(int i=0;i<NABL;i++){
		if(SubIcon==-1){
			MI=NT->wIcons[Icons[i]];
			IREF=Icons[i];
		}else{
			MI=NT->wIcons[SIC->SubList[i]];
			IREF=SIC->SubList[i];
		};
		switch(MI->Kind){
		case 0:
			//directory entry
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&EnterIn,IREF);
			break;
		case 1://uniq without param
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&NOPARAM,MI->Param2);//IREF);
			break;
		case 2://uniq with param
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1B,MI->Message);
            OI->AssignLeft(&NOPARAM,MI->Param2);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5://strange weapon
            OI=AblPanel.AddIcon(MI->FileID,MI->Spr,0x1C,MI->Message);
            OI->AssignLeft(&STRANGEWEAPON,MI->Param2);
			break;
		};
	};
	return true;

};
bool CheckCost(byte NI,word NIndex);
extern byte BaloonState;
extern byte CannonState;
extern byte XVIIIState;
void ShowAbility(){
	if(NARMINF)return;
	char sxt[128];
	//InitZones();
	NABL=0;
	word MID;
	OneObject* OBJ;
	GeneralObject* GO;
	AblInf* MI;
	Nation* NT;
	word s;
	int i,j,k,p,q,r;
	//if(NINF)ResFon(AblX,AblY,AblNx*IconLx,AblNy*IconLy);
	if(!NINF){
		//ResFon(AblX,AblY,AblNx*IconLx,AblNy*IconLy);
		//ScrCopy(PrpX,PrpY,PrpNx*IconLx,PrpNy*IconLy);
		return;
	};
	int nability=0;
	if(NINF==1){
		nability=ShowUniqAbility();
		if(nability==-1)return;
	};
	if(NINF>1)return;
	if(ShowCommonAbl())return;
	//calculating monsters could be produced
	for(i=0;i<NINF;i++){
		OBJ=Group[MList[i].Last];
		if(OBJ->Ready){
			NT=OBJ->Nat;
			k=OBJ->Index;
			p=OBJ->NIndex;
			q=NT->PACount[p];
			for(r=0;r<q;r++){
				s=NT->PAble[p][r];	
				if(NT->Mon[s]->Enabled){
					for(j=0;j<NABL;j++){
						if(AList[j].OInd==s)break;
					};
					AList[j].OInd=s;
					AList[j].NT=NT;
					AList[j].Kind=0;
					AList[j].HotKey=NT->AHotKey[p][r];
					AList[j].IconIndex=NT->AIndex[p][r];

					if(j>=NABL)NABL=j+1;
				};
			};
		};
	};
	//calculate upgrades
	for(i=0;i<NINF;i++){
		OBJ=Group[MList[i].Last];
		if(OBJ->Ready){
			NT=OBJ->Nat;
			k=OBJ->Index;
			p=OBJ->NIndex;
			GeneralObject* GO=NT->Mon[p];
			q=GO->NUpgrades;
			for(r=0;r<q;r++){
				s=GO->Upg[r];	
				NewUpgrade* UPG=NT->UPGRADE[s];
				if((!UPG->ManualDisable)&&(UPG->Enabled||(UPG->Gray&&!UPG->Done))){
					NewUpgrade* NUPG=NT->UPGRADE[s];
					bool OKK=false;
					if(NUPG->Individual||NUPG->StageUp){
						if(NUPG->Individual&&OBJ->SingleUpgLevel==NUPG->Level)OKK=true;
#ifdef CONQUEST
						if(NUPG->StageUp){
							byte st=(OBJ->StageState>>(NUPG->Level*3))&7;
							if(st!=2)OKK=true;
						};
#endif
					}else OKK=true;

					for(j=0;j<NABL;j++){
						if(AList[j].Kind==1&&AList[j].OInd==s)break;
					};
					if(OKK){
						AList[j].OInd=s;
						AList[j].NT=NT;
						AList[j].Kind=1;
						AList[j].HotKey=0;
						AList[j].IconIndex=-1;
						if(j>=NABL)NABL=j+1;
					};
				};
			};
		};
	};
	//show abilities
	int AN=AblNx*AblNy;
	if(NABL>AN)NABL=AN;
	int xx=nability;
	int x1=AblX+(IconLx+AddIconLx)*(xx&3);
	int y1=AblY+(IconLy+AddIconLy)*(xx>>2);
	xx=xx&3;
	OneSlide* OC;
    OneIcon* OI;
    int GA,GP;
	char str[32];
	int MaxProgr;
	for(i=0;i<NABL;i++){
		MI=&(AList[i]);
		switch(MI->Kind){
		case 0:
			GO=(MI->NT)->Mon[MI->OInd];
			if(!((BaloonState&&GO->Options&2)||
			 (CannonState==1&&GO->Options&1)||
			 (XVIIIState&&GO->Options&4))){
				p=GO->newMons->IconFileID;
				q=GO->newMons->IconID;
				GA=GetAmount(MI->OInd);
				GP=GetProgress(MI->OInd,&MaxProgr);
				GetChar(GO,sxt);
				GetMonCost(NatRefTBL[MyNation],MI->OInd,sxt);
				OI=AblPanel.AddIconFixed(p,q,MI->IconIndex);
				OI->AssignColor(0xD0+(NatRefTBL[MyNation]<<2));
				OI->CreateHint(sxt);
				OI->AssignHealth(GP,MaxProgr);
				OI->AssignLeft(&HPR,i);
				OI->AssignRight(&RHPR,i);
				OI->AssignIntVal(GA);
				if(!CheckCost(NatRefTBL[MyNation],MI->OInd))OI->AssignRedPulse();
			};
			break;
		case 1://upgrade caps
			{
				NewUpgrade* SU=MI->NT->UPGRADE[MI->OInd];
				if(!(SU->ManualDisable||(BaloonState&&SU->Options&2)||
				 (CannonState==1&&SU->Options&1)||
				 (XVIIIState&&SU->Options&4))){
					sxt[0]=0;
					MI->NT->GetUpgradeCostString(sxt,MI->OInd);
		            OI=AblPanel.AddIconFixed(SU->IconFileID,SU->IconSpriteID,SU->IconPosition);
					OI->AssignColor(0xD0+(NatRefTBL[MyNation]<<2));
					OI->AssignLeft(&DoUPG,i);
					OI->AssignHealth(SU->CurStage,SU->NStages);
					OI->AssignLevel(SU->Level);
					if(SU->Gray&&!(SU->Enabled||SU->Done))OI->Disable();
					OI->CreateHint(SU->Message);
					OI->CreateHintLo(sxt);
					bool dis=0;
					for(int p=0;p<6;p++){
						if(XRESRC(NatRefTBL[MyNation],p)<SU->Cost[p])dis=1;
					};
					if(dis)OI->AssignRedPulse();
				};
			};
			break;
		};
	};
    //AblPanel.DrawIconSet(AblX+3,AblY+3,AblNx,AblNy,0);
};
void PropCopy(){
	int AY=NABL>>2;
	if(NABL&3)AY++;
	int PY=NINF>>2;
	if(NINF&3)PY++;
	if(AY>8)AY=0;
	if(PY>8)PY=0;
	AY=4;
	PY=2;
	if(PY)ScrCopy(PrpX,PrpY,PrpNx*(IconLx+AddIconLx),PY*(IconLy+AddIconLy));
	if(AY)ScrCopy(AblX,AblY,AblNx*(IconLx+AddIconLx),AY*(IconLy+AddIconLy));
};
//-------------------MESSAGES-------------------//
void LoadConstStr();
lpCHAR* GMessIDS=NULL;
lpCHAR* GMessage=NULL;
int NMess=0;
int MaxMess=0;
void DosToWin(char*);
void normstr(char* str);
extern bool ProtectionMode;
void LoadMessagesFromFile(char* Name){
	if(!strstr(Name,".dat"))ProtectionMode=1;
	GFILE* f=Gopen(Name,"r");
	ProtectionMode=0;
	AFile(Name);
	if(!f)return;
	int z,z1;
	char IDN[128];
	char STR[4096];
	do{
		z=Gscanf(f,"%s",IDN);
		if(z==1){
			if(NMess>=MaxMess){
				MaxMess+=256;
				GMessIDS=(lpCHAR*)realloc(GMessIDS,MaxMess*4);
				GMessage=(lpCHAR*)realloc(GMessage,MaxMess*4);
			};
			Ggetch(f);
			STR[0]=0;
			int cc=0;
			z1=0;
			int nn=0;
			while(!(cc==0x0A||cc==EOF)){
				cc=Ggetch(f);
				if(!(cc==0x0A||cc==EOF)){
					STR[nn]=cc;
					nn++;
				}else{
					//Ggetch(f);
				};
			};
			STR[nn]=0;
			//normstr(STR);
			//DosToWin(STR);
			GMessIDS[NMess]=new char[strlen(IDN)+1];
			GMessage[NMess]=new char[strlen(STR)+1];
			strcpy(GMessIDS[NMess],IDN);
			strcpy(GMessage[NMess],STR);
			NMess++;
		};
	}while(z==1);
	Gclose(f);
};
void LoadMessages(){
	LoadMessagesFromFile("Comment.txt");
	TGSCFindInfo* FD=GSFILES.gFindFirst("Missions\\miss_*.txt");
	if(FD){
		char cc[128];
		sprintf(cc,"Missions\\%s",FD->m_FileName);
		LoadMessagesFromFile(cc);
		bool good=false;
		do{
			good=GSFILES.gFindNext(FD);
			if(good){
				sprintf(cc,"Missions\\%s",FD->m_FileName);
				LoadMessagesFromFile(cc);
			};
		}while(good);
	};
	FD=GSFILES.gFindFirst("Text\\*.txt");
	if(FD){
		char cc[128];
		sprintf(cc,"Text\\%s",FD->m_FileName);
		LoadMessagesFromFile(cc);
		bool good=false;
		do{
			good=GSFILES.gFindNext(FD);
			if(good){
				sprintf(cc,"Text\\%s",FD->m_FileName);
				LoadMessagesFromFile(cc);
			};
		}while(good);
	};
	LoadMessagesFromFile("moretx.dat");
	LoadConstStr();
};
CEXPORT
char* GetTextByID(char* ID){
	for(int i=0;i<NMess;i++)if(!strcmp(GMessIDS[i],ID))return GMessage[i];
	return ID;
};
CEXPORT
int GetTextIDByID(char* ID){
	for(int i=0;i<NMess;i++)if(!strcmp(GMessIDS[i],ID))return i;
	return -1;
};
