//#include "stdafx.h";
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "PeerClass.h";
TotalPeerEngine TPEN;
void SendInfoString(char* nick);
void CheckOriginalNick(int ProfileID);
void PEER_GetPlayerProfileIDCallback(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * nick,  // The player's nick.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
	){
	for(int i=0;i<TPEN.NPlayers;i++)if(!strcmp(nick,TPEN.Players[i].Name)){
		TPEN.Players[i].ProfileID=profileID;
		TPEN.Players[i].ProfState=3;
		if(profileID)CheckOriginalNick(profileID);
	};
};
void CreateAnswerString(char*);
char JOIN_nick[128]="";
byte RespType=0;
char RespTo[64]="";
char RespWhat[128]="";
void TotalPeerEngine::Process(){
	if(!Peer)return;
	if(ChatConnected){
		if(GetTickCount()-PTIME>500&&Connected){
			RefreshPlayers();
			if(MyRoom&&MyRoom->RoomConnected){
				MyRoom->Refresh();
			};
			PTIME=GetTickCount();
			ProcessRoomsInGame();
		};
		ABPL.Process();
		int NP=2;
		for(int i=0;i<NPlayers;i++){
			if(Players[i].ProfState==0){
				Players[i].ProfState=1;
				peerGetPlayerProfileID(Peer,Players[i].Name,
					&PEER_GetPlayerProfileIDCallback,this,PEERFalse);
				NP--;
				if(!NP)i=NPlayers;
			};
		};
	};
	peerThink(Peer);
	if(Connected&&!ChatConnected){
		if(GetTickCount()-LastSpyBotSignalTime>180000){
			//peerMessagePlayer(Peer,"spybot","\\launched\\1\\gamename\\cossacks\\");
			LastSpyBotSignalTime=GetTickCount();
		};
	};
	if(InfoRequest[0]){
		SendInfoString(InfoRequest);
		InfoRequest[0]=0;
	};
	if(Connected){
		if(JOIN_nick[0]){
			char ccc[256];
			CreateAnswerString(ccc);
			peerMessagePlayer(TPEN.Peer,JOIN_nick,ccc);
			JOIN_nick[0]=0;
		};
		if(RespType){
			RespType=0;
			peerMessagePlayer(Peer,RespTo,RespWhat);
		};
	};
};
int GetMyProfile();
void TotalPeerEngine::SendGlobalChat(char* Message){
	if(!Connected)return;
	if(!strcmp(Message,"@@@GETID")){
		char ccc[128];
		sprintf(ccc,"PROFILE# %d",GetMyProfile());
		GlobalChat.Add(MyNick,ccc);
	}else peerMessageRoom(Peer,TitleRoom,Message);
};
void TotalPeerEngine::AddPlayer(char* nick){
	if(!Connected)return;
	//LN speed algorythm to insert player
	int InsIndex=-1;
	if(NPlayers>1){
		int FP=0;
		int LP=NPlayers-1;
		int ResF=_stricmp(nick,Players[0].Name);
		if(!ResF){
			Players[0].Status&=1023;
			return;
		};
		int ResL=_stricmp(nick,Players[LP].Name);
		if(!ResL){
			Players[LP].Status&=1023;
			return;
		};
		if(ResF<0)InsIndex=0;
		else if(ResL>0)InsIndex=-1;
		else{
			bool doit=true;
			do{
				if(LP-FP==1){
					InsIndex=LP;
					doit=false;
				}else{
					int MP=(FP+LP)>>1;
					int res=_stricmp(nick,Players[MP].Name);
					if(!res){
						Players[MP].Status&=1023;
						return;
					};
					if(res<0){
						LP=MP;
					}else{
						FP=MP;
					};
				};
			}while(doit);
		};
	}else{
		if(NPlayers==1){
			int res=_stricmp(nick,Players[0].Name);
			if(!res){
				Players[0].Status&=1023;
				return;
			};
			if(res<0)InsIndex=0;
		};
	};
	/*
	int InsIndex=-1;
	for(int i=0;i<NPlayers;i++){
		int s=_stricmp(nick,Players[i].Name);
		if(!s){
			Players[i].Status&=1023;
			return;
		};
		if(s<0&&InsIndex==-1)InsIndex=i;
	};
	*/
	if(NPlayers>=MaxPlayers){
		MaxPlayers+=32;
		Players=(TPE_Player*)realloc(Players,MaxPlayers*sizeof TPE_Player);
	};
	if(InsIndex==-1){
		strcpy(Players[NPlayers].Name,nick);
		Players[NPlayers].Ping=-1;
		Players[NPlayers].Status=0;
		Players[NPlayers].ProfileID=0;
		Players[NPlayers].ProfState=0;
		Players[NPlayers].Muted=0;
		NPlayers++;
	}else{
		for(int j=NPlayers;j>InsIndex;j--)Players[j]=Players[j-1];
		strcpy(Players[InsIndex].Name,nick);
		Players[InsIndex].Ping=-1;
		Players[InsIndex].Status=0;
		Players[InsIndex].ProfileID=0;
		Players[InsIndex].ProfState=0;
		Players[InsIndex].Muted=0;
		NPlayers++;
	};
	Change=1;
};
void TotalPeerEngine::DelPlayer(char* nick){
	if(!Connected)return;
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,nick)){
		if(i<NPlayers-1)
			memcpy(Players+i,Players+i+1,(NPlayers-i-1)*sizeof TPE_Player);
		NPlayers--;
		i--;
	};
	Change=1;
};
void TotalPeerEngine::SetPing(char* nick,int Ping){
	if(!Connected)return;
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,nick)){
		Players[i].Ping=Ping;
	};
	Change=1;
};
TotalPeerEngine::TotalPeerEngine(){
	memset(this,0,sizeof TotalPeerEngine);
	PTIME=GetTickCount();
};
TotalPeerEngine::~TotalPeerEngine(){
	Disconnect();
};
void TotalPeerEngine::Disconnect(){
	if(Connected&&Peer){
		LeaveMyRoom();
		if(ChatConnected)peerLeaveRoom(Peer,TitleRoom);
		peerClearTitle(Peer);
		peerDisconnect(Peer);
		if(Peer)peerShutdown(Peer);
		Peer=NULL;
	};
	if(MaxPlayers)free(Players);
	if(Room)free(Room);
	if(FiltRef)free(FiltRef);
	for(int i=0;i<NRInGame;i++){
		RoomInGame* RIG=RInGame+i;
		free(RIG->Name);
		for(int q=0;q<RIG->NPlayers;q++)free(RIG->Players[q]);
		if(CurrentPlRoom<NRInGame-1){
			memcpy(RInGame+CurrentPlRoom,RInGame+CurrentPlRoom+1,(NRInGame-1-CurrentPlRoom)*sizeof RoomInGame);
		};
		NRInGame++;
	};
	memset(this,0,sizeof TotalPeerEngine);
};
// Called when the connection to the server gets disconnected.
//////////////////////////////////////////////////////////////
void PEER_DisconnectCallback(
		PEER peer,  // The peer object.
		const char * reason,  // The reason for the disconnection.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->Connected=0;
	TPE->State=2;
	if(TPE->MyRoom){
		if(TPE->MyRoom->RoomConnected){
			if(TPE->Players)free(TPE->MyRoom->Players);
		};
		free(TPE->MyRoom);
		TPE->MyRoom=NULL;

	};
	if(TPE->MaxPlayers)free(TPE->Players);
	if(TPE->Room)free(TPE->Room);
	if(TPE->FiltRef)free(TPE->FiltRef);
	TPE->ABPL.Clear();
	memset(TPE,0,sizeof TotalPeerEngine);
	//TPE->Connect(TPE->MyNick);
};

// Called when a message is sent to a room the local player is in.
//////////////////////////////////////////////////////////////////
void PEER_RoomMessageCallback(
		PEER peer,  // The peer object.
		RoomType roomType,  // The type of room that the message was in.
		const char * nick,  // The nick of the player who sent the message.
		const char * message,  // The text of the message.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(roomType==TitleRoom){
		if(strstr(message,"@@@[ADM@XYL]")){
			TPE->AddRoomInGame((char*)message);
		}else{
			if(message[0]=='@'&&message[1]=='@'&&message[2]=='@'){
				char* cc=strstr(message,"@@@NFO \\$flags$\\");
				if(cc){
					cc+=16;
					if(strchr(cc,'g')){
						TPE->ABPL.AddPlayer((char*)nick);
					};
				};
				cc=strstr(message,"@@@ADDABPL ");
				if(cc){
					cc+=11;
					do{
						char cc3[128];
						char* cc1=strstr(cc," ");
						if(cc1){
							int L=cc1-cc;
							memcpy(cc3,cc,L);
							cc3[L]=0;
							cc=cc1+1;
						}else{
							strcpy(cc3,cc);
							cc=NULL;
						};
						bool PRESENT=0;
						for(int i=0;i<TPE->NPlayers;i++)if(!strcmp(TPE->Players[i].Name,cc3))PRESENT=1;
						for(i=0;i<TPE->ABPL.NPlayers;i++)if(!strcmp(TPE->ABPL.Names[i],cc3))PRESENT=1;
						if(!PRESENT)TPE->ABPL.AddPlayer(cc3);
					}while(cc);
				};
			}else{
				for(int i=0;i<TPE->NPlayers;i++){
					if((!strcmp(TPE->Players[i].Name,nick))&&TPE->Players[i].Muted)return;
				};
				TPE->GlobalChat.Add((char*)nick,(char*)message);
				TPE->ChangeChat=1;
			};
		};
	}else{
		if(TPE->MyRoom&&TPE->MyRoom->RoomConnected)
			TPE->LocalChat.Add((char*)nick,(char*)message);
		TPE->ChangeLocalChat=1;
	};
};

// Called when the name of a room the player is in changes.
// The new name can be checked with peerGetRoomName.
// PANTS|09.11.00
///////////////////////////////////////////////////////////
void PEER_RoomNameChangedCallback(
		PEER peer,  // The peer object.
		RoomType roomType,  // The type of room that the name changed in.
		void * param  // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;

};

// Called when a private message is received from another player.
/////////////////////////////////////////////////////////////////
char* GetTextByID(char* ID);
bool ProcessIndividualMessages(char* nick,char* message);
extern int  RESPOND;
extern DWORD  PASSHASH;
extern char IPADDR[128];
char RESPNICK[128];
extern unsigned short dwVersion;
void PlayEffect(int n,int pan,int vol);
int GetSound(char* Name);
int GetStrHASH2(char* s){
	int L=strlen(s);
	DWORD S=0;
	for(int i=0;i<L;i++){
		S+=177*s[i];
	};
	for(i=0;i<L-1;i++){
		S+=27*int(s[i])*int(s[i+1]);
	};
	for(i=0;i<L-2;i++){
		S-=13*int(s[i])*int(s[i+1])*int(s[i+2]);
	};
	for(i=0;i<L-3;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3]);
	};
	for(i=0;i<L-4;i++){
		S-=3*int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4]);
	};
	for(i=0;i<L-5;i++){
		S+=int(s[i])*int(s[i+1])*int(s[i+2])*int(s[i+3])*int(s[i+4])*int(s[i+5]);
	};
	return S;
};

extern bool RejectThisPlayer;
void ERRMESSAGE(char*);

void PEER_PlayerMessageCallback(
		PEER peer,  // The peer object.
		const char * nick,  // The nick of the player who sent the message.
		const char * message,  // The text of the message.
		void * param  // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(!_stricmp(nick,"spybot")){
		if(strstr(message,"\\llist\\")){
			char* cc=strstr(message,"\\cossacks\\");
			if(cc){
				cc+=strlen("\\cossacks\\");
				int NP=0;
				int z=sscanf(cc,"%d",&NP);
				if(z==1){
					cc=strstr(cc,"\\");
					if(cc){
						char ccx[256];
						cc++;
						for(int i=0;i<NP;i++){
							ccx[0]=0;
							while(cc[0]&&cc[0]!='\\'){
								int L=strlen(ccx);
								ccx[L]=cc[0];
								ccx[L+1]=0;
								cc++;
							};
							if(cc[0]=='\\'){
								cc++;
								TPE->ABPL.AddPlayer(ccx);
							};
						};
					};
				};
			};
		};
		return;
	};
	if(TPE->Connected){
		if(!strcmp(message,"@@@RMISFULL")){
			RESPOND=4;
			strcpy(RESPNICK,nick);
		}else
		if(!strcmp(message,"@@@GMINPROGR")){
			RESPOND=6;
			strcpy(RESPNICK,nick);
		}else
		if(!strcmp(message,"@@@NORCRT")){
			RESPOND=5;
			strcpy(RESPNICK,nick);
		}else
		if(strstr(message,"@@@KU")){
			int hash=0;
			int z=sscanf(message+6,"%d",&hash);
			char CCC[256];
			strcpy(CCC,TPE->MyNick);
			strcat(CCC,nick);
			if(GetStrHASH2(CCC)==hash){
				RejectThisPlayer=1;
			};
		}else
		if(strstr(message,"@@@KM")){
			int hash=0;
			char ccc[256];
			char STR[256];
			int z=sscanf(message+6,"%s%d",ccc,&hash);
			char CCC[256];
			strcpy(CCC,TPE->MyNick);
			strcat(CCC,nick);
			if(GetStrHASH2(CCC)==hash){
				sprintf(STR,GetTextByID("NO_CLAN_MEMBER_[%s]"),ccc);
				ERRMESSAGE(STR);
				RejectThisPlayer=1;
			};
		}else
		if(strstr(message,"@@@KR")){
			int hash=0;
			char ccc[256];
			char STR[256];
			int z=sscanf(message+6,"%d",&hash);
			char CCC[256];
			strcpy(CCC,TPE->MyNick);
			strcat(CCC,nick);
			if(GetStrHASH2(CCC)==hash){
				char* cc=strstr(message,">>");
				if(cc){
					ERRMESSAGE(cc+2);
					RejectThisPlayer=1;
				};
			};
		}else
		if(strstr(message,"@@@VER")){
			strcpy(RespTo,nick);
			sprintf(RespWhat,"VERSION INFO: %d E",dwVersion);
#ifdef RUSSIAN
			sprintf(RespWhat,"VERSION INFO: %d R",dwVersion);
#endif
#ifdef FRANCEVERSION
			sprintf(RespWhat,"VERSION INFO: %d F",dwVersion);
#endif
			RespType=1;
		}else
		if(strstr(message,"@@@PASREX")){
			strcpy(RESPNICK,nick);
			char cmd[128];
			int ver=0;
			int tmp=0;
			int z=sscanf(message,"%s%d%d%s%d",cmd,&PASSHASH,&tmp,IPADDR,&ver);
			if(z==5){
				if(ver==dwVersion){
					RESPOND=2;
					char* s=strstr(message,"#");
					if(s)strcpy(TPEN.HostMessage,s+1);
					else RESPOND=3;
				}else RESPOND=3;
			}else RESPOND=5;
		}else
		if(strstr(message,"@@@WELCOMX")){
			strcpy(RESPNICK,nick);
			char cmd[128];
			int ver=0;
			int tmp=0;
			int z=sscanf(message,"%s%d%s%d",cmd,&tmp,IPADDR,&ver);
			if(z==4){
				if(ver==dwVersion){
					RESPOND=1;
					char* s=strstr(message,"#");
					if(s)strcpy(TPEN.HostMessage,s+1);
					else RESPOND=3;
				}else RESPOND=3;
			}else RESPOND=5;
		}else
		if(!strcmp(message,"@@@[ADM@GPL]")){
			if(TPE->RPRO.ICanAnswer&&!TPE->RPRO.IAnswer){
				TPE->RPRO.IAnswer=1;
				TPE->RPRO.LastAnswerTime=GetTickCount()-1000;
				strcpy(TPE->RPRO.RCNick,nick);
				TPE->RPRO.LastSendIndex=-1;
			};
		};
		if(strstr(message,"@@@[ADM@XYL]")){
			TPE->AddRoomInGame((char*)message);
			TPE->RPRO.LastSendReqTime=GetTickCount();
		}else
		if(!strcmp(message,"@@@GETINFO")){
			strcpy(TPE->InfoRequest,nick);
		}else
		if(!strcmp(message,"@@@I_WANT_TO_JOIN")){
			strcpy(JOIN_nick,nick);
		}else
		if(!strcmp(message,"@@@[ADM@NOPLAY]")){
			TPE->RPRO.LastSendReqTime=GetTickCount();
			TPE->RPRO.ICanAnswer=1;
		}else{
			if(!(message[0]=='@'&&message[1]=='@'&&message[2]=='@')){
				char xx[64];
				if(!ProcessIndividualMessages((char*)nick,(char*)message)){
					for(int i=0;i<TPE->NPlayers;i++){
						if((!strcmp(TPE->Players[i].Name,nick))&&TPE->Players[i].Muted)return;
					};
					sprintf(xx,"%s%s",nick,GetTextByID("ONLYOU"));
					TPE->GlobalChat.Add(xx,(char*)message);
					TPE->ChangeChat=1;
					PlayEffect(GetSound("START"),0,0);
				};
			}else{
				if(message[3]=='G'&&message[4]=='M'&&message[5]=='R'&&
					message[6]=='I'&&message[7]=='N'){
					char* ccc=(char*)(message+9);
					char tmp[256];
					int p=0;
					char c;
					do{
						c=ccc[0];
						ccc++;
						if(c!='\\'){
							tmp[p]=c;
							tmp[p+1]=0;
							p++;
						}else{
							TPE->GlobalChat.Add(":::",tmp);
							p=0;
						};
					}while(c);
				};
			};
		};
	};
};

// Called when a player's ready state changes,
// from a call to peerSetReady().
//////////////////////////////////////////////
void PEER_ReadyChangedCallback(
		PEER peer,  // The peer object.
		const char * nick,  // The nick of the player who's ready state changed.
		PEERBool ready,  // The player's new ready state.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(TPE->MyRoom&&TPE->MyRoom->RoomConnected){
		TPE->MyRoom->SetReady((char*)nick,ready);
	};
};

// Called when the host of a staging room launches the game,
// with a call to peerGameStart().
////////////////////////////////////////////////////////////
void PEER_GameStartedCallback(
		PEER peer,  // The peer object.
		unsigned int IP,  // The IP of the host, in network-byte order. PANTS|09.11.00 - was unsigned long
		const char * message,  // A message that was passed into peerGameStart().
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->Runned=1;
	TPE->HOSTIP=IP;
	//strcpy(TPE->HostMessage,message);
};

// A player joined a room.
//////////////////////////
void PEER_PlayerJoinedCallback(
		PEER peer,  // The peer object.
		RoomType roomType,  // The type of room that the player joined.
		const char * nick,  // The nick of the player that joined.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(roomType==StagingRoom){
		if(TPE->MyRoom&&TPE->MyRoom->RoomConnected){
			//TPE->MyRoom->ChangeMyReady();
			//TPE->MyRoom->ChangeMyReady();
		};
	};
	TPE->AddPlayer((char*)nick);
};

// A player left a room.
////////////////////////
void PEER_PlayerLeftCallback(
		PEER peer,  // The peer object.
		RoomType roomType,  // The type of room that the player left.
		const char * nick,  // The nick of the player that left.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->DelPlayer((char*)nick);
};

// A player in one of the rooms changed his nick.
/////////////////////////////////////////////////
void PEER_PlayerChangedNickCallback(
		PEER peer,  // The peer object.
		RoomType roomType,  // The type of the room the nick changed was in.
		const char * oldNick,  // The player's old nick.
		const char * newNick,  // The player's new nick.
		void * param  // User-data.
	){

};

// An updated ping for a player, who may be in any room(s).
///////////////////////////////////////////////////////////
void PEER_PingCallback(
		PEER peer,  // The peer object.
		const char * nick,  // The other player's nick.
		int ping,  // The ping.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->SetPing((char*)nick,ping);
	if(TPE->MyRoom&&TPE->MyRoom->RoomConnected)TPE->MyRoom->SetPing((char*)nick,ping);
};

// An updated cross-ping between two players in the staging room.
/////////////////////////////////////////////////////////////////
void PEER_CrossPingCallback(
		PEER peer,  // The peer object.
		const char * nick1,  // The first player's nick.
		const char * nick2,  // The second player's nick.
		int crossPing,  // The cross-ping.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
};
extern unsigned short dwVersion;
#define CEXPORT __declspec(dllexport)
CEXPORT
char LobbyVersion[32]="1.35";
// Type used for the GOA callbacks (basic, info, rules, players).
/////////////////////////////////////////////////////////////////
bool BasicCalled=0;
void PEER_GOABasic(
		PEER peer,  // The peer object.
		PEERBool playing,  // PEERTrue if the game is being played.
		char * outbuf,  // Output buffer.
		int maxlen,  // Max data that can be written to outbuf
		void * param // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	sprintf(outbuf,"\\gamever\\%s",LobbyVersion);
	BasicCalled=1;
};
void PEER_GOAInfo(
		PEER peer,  // The peer object.
		PEERBool playing,  // PEERTrue if the game is being played.
		char * outbuf,  // Output buffer.
		int maxlen,  // Max data that can be written to outbuf
		void * param // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	outbuf[0]=0;
	char* BTLS[3]={"Deathmatch","Battle","Rated deathmatch"};
	char* STT[2]={"wait","closedplaying"};
	int pos=0;
	int pos1=TPE->GameType;
	if(pos1<0)pos1=0;
	if(pos1>2)pos1=2;
	if(TPE->Connected){
		if(!TPE->ChatConnected)pos=1;
		sprintf(outbuf,"\\gamemode\\%s\\gametype\\%s(Inside the Cossacks shell)\\mapname\\CEW%d%d000000|Host:%s\\",STT[pos],BTLS[pos1],pos1,TPE->Level,TPE->MyNick);
	};
};
int GetCEW(GServer G,int Index){
	char* cc=ServerGetStringValue(G,"mapname","");
	if(cc[0]=='C'&&cc[1]=='E'&&cc[2]=='W'){
		int v=cc[3+Index]-'0';
		if(v<0||v>9)v=0;
		return v;
	}else return 0;
};
void PEER_GOAPlayers(
		PEER peer,  // The peer object.
		PEERBool playing,  // PEERTrue if the game is being played.
		char * outbuf,  // Output buffer.
		int maxlen,  // Max data that can be written to outbuf
		void * param // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
};
void PEER_GOARules(
		PEER peer,  // The peer object.
		PEERBool playing,  // PEERTrue if the game is being played.
		char * outbuf,  // Output buffer.
		int maxlen,  // Max data that can be written to outbuf
		void * param // User-data
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	
};
char* VALCHAR="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-";
bool NormName(char* cc){
	int L=strlen(cc);
	bool ch=0;
	for(int i=0;i<L;i++){
		unsigned char c=cc[i];
		if(!strchr(VALCHAR,c)){
			cc[i]='_';
			ch=1;
		};
	};
	if((cc[0]>='0'&&cc[0]<='9')||cc[0]=='-'){
		cc[0]='_';
		ch=1;
	};
	if(strlen(cc)>16){
		cc[16]=0;
		ch=1;
	};

	return ch;
};

void PEER_NickErrorCallback(
		PEER peer,  // The peer object.
		int type,  // The type of nick error
			// PEER_IN_USE:  The nick is already being used by someone else.
			// PEER_INVALID: The nick contains invalid characters.
		const char * nick,  // The bad nick.
		void * param  // User-data.
	){
	char ccx[128];
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(type==PEER_IN_USE){
		TPE->State=1;
		strcpy(ccx,nick);
		char* cc0=strstr(ccx,"{1}");
		if(cc0)strcpy(cc0,"{2}");
		else{
			cc0=strstr(ccx,"{2}");
			if(cc0)strcpy(cc0,"{3}");
			else{
				cc0=strstr(ccx,"{3}");
				if(cc0)strcpy(cc0,"{4}");
				else{
					cc0=strstr(ccx,"{4}");
					if(cc0)strcpy(cc0,"{5}");
					else{
						cc0=strstr(ccx,"{5}");
						if(cc0){
							TPE->ErrorType=2;
							TPE->State=2;
						}else{
							strcat(ccx,"{1}");
						};
					};
				};
			};
		};
		if(TPE->State==1){
			strcpy(TPE->MyNick,ccx);
			peerRetryWithNick(TPE->Peer,ccx);
		};
	}else{
		strcpy(ccx,nick);
		if(NormName(ccx)){
		}else{
			TPE->State=2;
			TPE->ErrorType=2;
		};
	};
};
void PEER_EnumPlayersCallback(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The room whose players are being enumerated.
		int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
		const char * nick,  // The nick of the player.
		PEERBool host,  // PEERTrue if this player is a host in this room (has ops).
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(success){
		if(roomType==TitleRoom){
			TPE->AddPlayer((char*)nick);
		};
	};
};
void PEER_ListingGamesCallback(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		const char * name,  // The name of the game being listed.
		GServer server,  // The server object for this game.
		PEERBool staging,  // If PEERTrue, this is a staging room and not a running game.
		int msg,  // The type of message this is.
			// PEER_CLEAR:
			//   Clear the list.  This has the same effect as if this was called
			//   with PEER_REMOVE for every server listed.
			// PEER_ADD:
			//   This is a new server. Add it to the list.
			// PEER_UPDATE:
			//   This server is already on the list, and its been updated.
			// PEER_REMOVE:
			//   Remove this server from the list.  The server object for this server
			//   should not be used again after this callback returns.
		int progress,  // The percent of servers that have been added.
		void * param  // User-data.
	){
	if(!success)return;
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->FILTER.CRC++;
	switch(msg){
	case PEER_CLEAR:
		TPE->ClearServers();
		break;
	case PEER_ADD:
		TPE->AddServer((char*)name,server);
		break;
	case PEER_UPDATE:
		TPE->UpdateServer((char*)name,server);
		break;
	case PEER_REMOVE:
		TPE->DelServer((char*)name,server);
		break;
	};
};
// This gets called when the connection attempt finishes.
/////////////////////////////////////////////////////////
bool FirewallNotified=0;
bool UnderFirewall=0;
bool CheckFirewall(DWORD IP){
	char cc[128];
	DWORD L=128;
	GetComputerName(cc,&L);
	hostent* ht=gethostbyname(cc);
	int p=0;
	do{
		if(ht->h_addr_list[p]){
			if( ((DWORD*)(ht->h_addr_list[p]))[0]==IP)return false;
			p++;
		};
	}while(ht->h_addr_list[p]);
	return true;
};
bool NotifyFirewallState();
bool GetPLIP(char* Nick,char* IP);
void PEER_JoinRoomCallback(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The type of room joined/created.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(success&&roomType==TitleRoom){
		TPE->Connected=1;
		TPE->ChatConnected=1;
		TPE->State=5;
		if(!FirewallNotified){
			//if(CheckFirewall(peerGetMyIP(peer)))
			//	UnderFirewall=1;
			FirewallNotified=1;
		};
		peerEnumPlayers(TPE->Peer,TitleRoom,&PEER_EnumPlayersCallback,param);
		peerStartListingGames(TPE->Peer,&PEER_ListingGamesCallback,param);
		//peerMessagePlayer(TPE->Peer,"spybot","\\launched\\0\\gamename\\cossacks\\");
		//peerMessagePlayer(TPE->Peer,"spybot","\\llist\\cossacks\\");
	};

};
void PEER_ConnectCallback(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	TPE->State=1;
	if(success){
		TPE->Connected=0;
		TPE->State=3;
		PEERBool PINGS[NumRooms];
		PINGS[TitleRoom]=PEERTrue;
		PINGS[GroupRoom]=PEERFalse;//PEERTrue;
		PINGS[StagingRoom]=PEERFalse;//PEERTrue;
		PEERBool PINGS_CROSS[NumRooms];
		PINGS_CROSS[TitleRoom]=PEERFalse;
		PINGS_CROSS[GroupRoom]=PEERFalse;
		PINGS_CROSS[StagingRoom]=PEERFalse;
		//peerSetTitle(TPE->Peer,"gmtest","HA6zkS", "gmtest", "HA6zkS", 20, PINGS, PINGS_CROSS);
		peerSetTitle(TPE->Peer,"cossacks","p2vPkJ", "cossacks", "p2vPkJ", 10,PINGS, PINGS_CROSS);
		//peerSetTitle(TPE->Peer,"cossacks","p2vPkJ", "gmtest", "HA6zkS", 20, PINGS, PINGS_CROSS);
		peerJoinTitleRoom(TPE->Peer,&PEER_JoinRoomCallback,param,PEERFalse);
	}else{
		if(GetTickCount()-TPE->ConnStartTime<60000){
			peerConnect(TPE->Peer,TPE->MyNick,0,&PEER_NickErrorCallback,&PEER_ConnectCallback,param,PEERFalse);
		}else 
			TPE->ErrorType=1;
	};
};
bool ProcessMessagesEx();
extern "C" BOOL BLOCKFN(){
	return ProcessMessagesEx();
};
int CurProfileID;
//ERRORS:
//0-No error
//1-Unable to connect to chat server
//2-Invalid user name
void TotalPeerEngine::Connect(char* Nick){
	if(Connected){
		Disconnect();
	};
	/*
	if(Connected&&ChatConnected)return;
	if(Connected&&!ChatConnected){
		ABPL.Clear();
		peerMessagePlayer(Peer,"spybot","\\launched\\0\\gamename\\cossacks\\");
		peerJoinTitleRoom(TPE->Peer,&PEER_JoinRoomCallback,param,PEERFalse);
		peerStartListingGames(Peer,&PEER_ListingGamesCallback,this);
		return;
	};
	*/
	PEERCallbacks PCB;
	ConnStartTime=GetTickCount();
	strcpy(MyNick,Nick);
	//if(!strstr(MyNick,"[inside]")){
	//	strcat(MyNick,"[inside]");
	//};
	ABPL.TPE=this;
	ABPL.Clear();
	NormName(MyNick);
	PCB.crossPing=&PEER_CrossPingCallback;
	PCB.disconnected=&PEER_DisconnectCallback;
	PCB.gameStarted=&PEER_GameStartedCallback;
	PCB.ping=&PEER_PingCallback;
	PCB.playerChangedNick=&PEER_PlayerChangedNickCallback;
	PCB.playerJoined=&PEER_PlayerJoinedCallback;
	PCB.playerLeft=&PEER_PlayerJoinedCallback;
	PCB.playerMessage=&PEER_PlayerMessageCallback;
	PCB.readyChanged=&PEER_ReadyChangedCallback;
	PCB.roomMessage=&PEER_RoomMessageCallback;
	PCB.roomNameChanged=&PEER_RoomNameChangedCallback;
	PCB.GOABasic=&PEER_GOABasic;
	PCB.GOAInfo=&PEER_GOAInfo;
	PCB.GOAPlayers=&PEER_GOAPlayers;;
	PCB.GOARules=&PEER_GOARules;
	PCB.param=(void*)this;
	Runned=0;
	Peer=peerInitialize(&PCB);
	State=1;
	ErrorType=0;
	Connected=0;
	peerConnect(Peer,MyNick,CurProfileID,&PEER_NickErrorCallback,&PEER_ConnectCallback,this,PEERFalse);
};
void TotalPeerEngine::RefreshPlayers(){
	if(!Peer)return;
	if(!Connected)return;
	//NPlayers=0;
	int N0=NPlayers;
	int S=0;
	for(int i=0;i<NPlayers;i++){
		int L=strlen(Players[i].Name);
		char* c=Players[i].Name;
		for(int j=0;j<L;j++)S+=c[j]+(int(c[j+1])<<8);
		Players[i].Status|=1024;
	};
	peerEnumPlayers(Peer,TitleRoom,&PEER_EnumPlayersCallback,this);
	for(i=0;i<NPlayers;i++){
		if(Players[i].Status&1024){
			char cc2[64];
			strcpy(cc2,Players[i].Name);
			DelPlayer(cc2);
		};
	};
	int S1=0;
	for(i=0;i<NPlayers;i++){
		int L=strlen(Players[i].Name);
		char* c=Players[i].Name;
		for(int j=0;j<L;j++)S1+=c[j]+(int(c[j+1])<<8);
	};
	if(N0==NPlayers&&S1==S)Change=false;
};
void ChatQueue::Clear(){
	for(int i=0;i<NCStr;i++){
		free(CStr[i].Message);
		free(CStr[i].PlName);
	};
	if(CStr){
		free(CStr);
	};
	memset(this,0,sizeof ChatQueue);
};
void ChatQueue::Add(char* nick,char* Message){
	if(NCStr>=MaxCStr){
		MaxCStr+=16;
		CStr=(ChatString*)realloc(CStr,MaxCStr*sizeof ChatString);
	};
	CStr[NCStr].Message=new char[strlen(Message)+1];
	strcpy(CStr[NCStr].Message,Message);
	CStr[NCStr].PlName=new char[strlen(nick)+1];
	strcpy(CStr[NCStr].PlName,nick);
	NCStr++;
};
void PEER_EnumPlayersCallback2(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The room whose players are being enumerated.
		int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
		const char * nick,  // The nick of the player.
		PEERBool host,  // PEERTrue if this player is a host in this room (has ops).
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(success&&roomType==StagingRoom&&TPE->MyRoom){
		TPE->MyRoom->AddPlayer((char*)nick);
	};
};
void PEER_EnumPlayersCallback3(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The room whose players are being enumerated.
		int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
		const char * nick,  // The nick of the player.
		PEERBool host,  // PEERTrue if this player is a host in this room (has ops).
		void * param  // User-data.
	){
	TPE_MyRoom* TPR=(TPE_MyRoom*)param;
	if(success&&roomType==StagingRoom&&TPR){
		TPR->AddPlayer((char*)nick);
		PEERBool PB;
		peerGetReady(TPR->Peer,nick,&PB);
		TPR->SetReady((char*)nick,bool(PB));
	};
};
void PEER_JoinRoomCallback2(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The type of room joined/created.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(!TPE->MyRoom)return;
	if(success&&roomType==StagingRoom){
		TPE->MyRoom->RoomConnected=1;
		//peerEnumPlayers(TPE->Peer,StagingRoom,&PEER_EnumPlayersCallback2,param);
		TPE->MyRoom->Host=1;
	}else{
		free(TPE->MyRoom);
		TPE->MyRoom=NULL;
	};

};
void PEER_JoinRoomCallback3(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The type of room joined/created.
		void * param  // User-data.
	){
	TotalPeerEngine* TPE=(TotalPeerEngine*)param;
	if(success&&roomType==StagingRoom){
		TPE->MyRoom->RoomConnected=1;
		//peerEnumPlayers(TPE->Peer,StagingRoom,&PEER_EnumPlayersCallback2,param);
		TPE->MyRoom->Host=0;
	}else{
		free(TPE->MyRoom);
		TPE->MyRoom=NULL;
	};
};
bool ProcessMessages();
void TotalPeerEngine::CreateStagingRoom(char* Name,char* Password,int MaxPlayers,int Type,int Lev){
	if(!Connected)return;
	MyRoom=new TPE_MyRoom;
	memset(MyRoom,0,sizeof TPE_MyRoom);
	MyRoom->TPE=this;
	strcpy(MyRoom->Name,Name);
	MyRoom->MaxPlayer=MaxPlayers;
	MyRoom->Peer=Peer;
	MyRoom->Type=Type;
	MyRoom->Level=Lev;
	Level=Lev;
	GameType=Type;
	BasicCalled=0;
	peerCreateStagingRoom(Peer,Name,MaxPlayers,Password,&PEER_JoinRoomCallback2,this,PEERFalse);
	int T0=GetTickCount();
	do{
		ProcessMessages();
	}while(GetTickCount()-T0<40000&&!BasicCalled);
	if(!BasicCalled){
		TPEN.LeaveMyRoom();
	};
};
void TotalPeerEngine::AddServer(char* Name,GServer server){
	if(!Connected)return;
	for(int i=0;i<NRooms;i++)if(!strcmp(Name,Room[i].Name)){
		try{
			char* s1=ServerGetStringValue(Room[i].G,"mapname","");
			char* s2=ServerGetStringValue(server,"mapname","");
			if(!strcmp(s1,s2))return;
		}catch(...){};
		return;
	};
	if(NRooms>=MaxRooms){
		MaxRooms+=32;
		Room=(TPE_Room*)realloc(Room,MaxRooms*sizeof(TPE_Room));
	};
	Room[NRooms].G=server;
	strcpy(Room[NRooms].Name,Name);
	NRooms++;
	ChangeServer=1;
};
void TotalPeerEngine::DelServer(char* Name,GServer server){
	if(!Connected)return;
	for(int i=0;i<NRooms;i++)if(Room[i].G==server||!strcmp(Room[i].Name,Name)){
		if(i<NRooms-1)memcpy(Room+i,Room+i+1,(NRooms-i-1)*sizeof TPE_Room);
		NRooms--;
		ChangeServer=1;
		return;
	};
};
void TotalPeerEngine::UpdateServer(char* Name,GServer server){
};
void TotalPeerEngine::ClearServers(){
	NRooms=0;
	NFRooms=0;
	ChangeServer=1;
};
void TPE_MyRoom::AddPlayer(char* nick){
	//LN speed algorythm to insert player
	int InsIndex=-1;
	if(NPlayers>1){
		int FP=0;
		int LP=NPlayers-1;
		int ResF=_stricmp(nick,Players[0].Name);
		if(!ResF){
			Players[0].Status&=1023;
			return;
		};
		int ResL=_stricmp(nick,Players[LP].Name);
		if(!ResL){
			Players[LP].Status&=1023;
			return;
		};
		if(ResF<0)InsIndex=0;
		else if(ResL>0)InsIndex=-1;
		else{
			bool doit=true;
			do{
				if(LP-FP==1){
					InsIndex=LP;
					doit=false;
				}else{
					int MP=(FP+LP)>>1;
					int res=_stricmp(nick,Players[MP].Name);
					if(!res){
						Players[MP].Status&=1023;
						return;
					};
					if(res<0){
						LP=MP;
					}else{
						FP=MP;
					};
				};
			}while(doit);
		};
	}else{
		if(NPlayers==1){
			int res=_stricmp(nick,Players[0].Name);
			if(!res){
				Players[0].Status&=1023;
				return;
			};
			if(res<0)InsIndex=0;
		};
	};
	/*
	int InsIndex=-1;
	for(int i=0;i<NPlayers;i++){
		int s=_stricmp(nick,Players[i].Name);
		if(!s){
			Players[i].Status&=1023;
			return;
		};
		if(s<0&&InsIndex==-1)InsIndex=i;
	};
	*/
	if(NPlayers>=MaxPlayers){
		MaxPlayers+=32;
		Players=(TPE_Player*)realloc(Players,MaxPlayers*sizeof TPE_Player);
	};
	if(InsIndex==-1){
		strcpy(Players[NPlayers].Name,nick);
		Players[NPlayers].Ping=-1;
		Players[NPlayers].Status=0;
		Players[NPlayers].ready=0;
		NPlayers++;
	}else{
		for(int j=NPlayers;j>InsIndex;j--)Players[j]=Players[j-1];
		strcpy(Players[InsIndex].Name,nick);
		Players[InsIndex].Ping=-1;
		Players[InsIndex].Status=0;
		Players[InsIndex].ready=0;
		NPlayers++;
	};
	Change=1;
};
void TPE_MyRoom::DelPlayer(char* nick){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,nick)){
		if(i<NPlayers-1)
			memcpy(Players+i,Players+i+1,(NPlayers-i-1)*sizeof TPE_Player);
		NPlayers--;
		i--;
	};
	Change=1;
};
void TPE_MyRoom::SetPing(char* nick,int Ping){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,nick)){
		Players[i].Ping=Ping;
	};
	Change=1;
};
void TPE_MyRoom::SetReady(char* nick,bool State){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,nick)){
		Players[i].ready=State;
	};
	Change=1;
};
void TPE_MyRoom::Refresh(){
	if(!(this&&RoomConnected))return;
	int N0=NPlayers;
	int S=0;
	for(int i=0;i<NPlayers;i++){
		int L=strlen(Players[i].Name);
		char* c=Players[i].Name;
		for(int j=0;j<L;j++)S+=c[j]+(int(c[j+1])<<8);
		S+=Players[i].ready;
		Players[i].Status|=1024;
	};
	peerEnumPlayers(Peer,StagingRoom,&PEER_EnumPlayersCallback3,this);
	for(i=0;i<NPlayers;i++){
		if(Players[i].Status&1024){
			char cc[128];
			strcpy(cc,Players[i].Name);
			DelPlayer(cc);
		};
	};
	bool PRHOST=0;
	int S1=0;
	for(i=0;i<NPlayers;i++){
		int L=strlen(Players[i].Name);
		char* c=Players[i].Name;
		for(int j=0;j<L;j++)S1+=c[j]+(int(c[j+1])<<8);
		S1+=Players[i].ready;
		if(peerIsPlayerHost(Peer,Players[i].Name,StagingRoom))PRHOST=1;
	};
	if(N0==NPlayers&&S1==S)Change=false;
	if(!PRHOST)TPE->LeaveMyRoom();
};
void TotalPeerEngine::RefreshSessions(){
	peerStartListingGames(Peer,&PEER_ListingGamesCallback,this);
};
void TotalPeerEngine::SendLocalChat(char* Message){
	if(!Connected)return;
	if(MyRoom&&MyRoom->RoomConnected){
		peerMessageRoom(Peer,StagingRoom,Message);
	};
};
void TotalPeerEngine::JoinRoom(TPE_Room* Room,char* password){
	if(!Connected)return;
	if(MyRoom)return;
	MyRoom=new TPE_MyRoom;
	memset(MyRoom,0,sizeof TPE_MyRoom);
	MyRoom->TPE=this;
	strcpy(MyRoom->Name,Room->Name);
	MyRoom->MaxPlayer=Room->MaxPlayer;
	MyRoom->Peer=Peer;
	peerJoinStagingRoom(Peer,Room->G,password,PEER_JoinRoomCallback2,this,PEERFalse);
};
void TotalPeerEngine::LeaveMyRoom(){
	if(!Connected)return;
	if(MyRoom&&MyRoom->RoomConnected){
		peerLeaveRoom(Peer,StagingRoom);
		if(MyRoom->Players){
			free(MyRoom->Players);
		};
		free(MyRoom);
		MyRoom=NULL;
	}else{
		if(MyRoom){
			free(MyRoom);
			MyRoom=NULL;
		};
	};
};
void TPE_MyRoom::ChangeMyReady(){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,TPE->MyNick)){
		peerSetReady(Peer,PEERBool(!Players[i].ready));
	};
};
void TPE_MyRoom::ResetMyReady(){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Players[i].Name,TPE->MyNick)){
		peerSetReady(Peer,PEERBool(Players[i].ready));
	};
};
void TPE_MyRoom::SetMyReady(bool State){
	peerSetReady(Peer,PEERBool(PEERBool(State)));
};
void TPE_MyRoom::RunGame(){
	if(Host){
		peerStartGame(Peer,"GO GO GO",PEERFalse);
		TPE->Runned=1;
		TPE->HOSTIP=0;
	};
};
void TotalPeerEngine::ProcessFilter(){
	if(!Peer)return;
	int NP=0;
	bool change=0;
	if(NRooms>1){
		do{
			CurrentRoom=(CurrentRoom+1)%(NRooms-1);
			int r=CompareRooms(Room+CurrentRoom,Room+CurrentRoom+1);
			if(r>0){
				TPE_Room rr=Room[CurrentRoom];
				Room[CurrentRoom]=Room[CurrentRoom+1];
				Room[CurrentRoom+1]=rr;
				change=1;
			};
			NP++;
		}while(NP<20);
	};
	NP=0;
	if(NRInGame){
		do{
			for(int i=0;i<NRInGame-1;i++){
				int r=CompareGRooms(RInGame+i,RInGame+i+1);
				if(r>0){
					RoomInGame rr=RInGame[i];
					RInGame[i]=RInGame[i+1];
					RInGame[i+1]=rr;
					change=1;
				};
				NP++;
			};
			NP++;
		}while(NP<100&&change);
	};
	if(change)FILTER.CRC++;

	byte* D=(byte*)&FILTER;
	int L=sizeof(FILTER)-4;
	DWORD S=0;
	for(int i=0;i<L;i++)S+=D[i];
	if(S!=FILTER.CRC){
		FILTER.CRC=S;
		NFRooms=0;
		for(int i=0;i<NRooms;i++){
			if(CheckInFilter(Room+i)){
				if(NFRooms>=MaxFRooms){
					MaxFRooms+=32;
					FiltRef=(int*)realloc(FiltRef,4*MaxFRooms);
				};
				FiltRef[NFRooms]=i;
				NFRooms++;
			};
		};
		for(i=0;i<NRInGame;i++){
			if(CheckGInFilter(RInGame+i)){
				if(NFRooms>=MaxFRooms){
					MaxFRooms+=32;
					FiltRef=(int*)realloc(FiltRef,4*MaxFRooms);
				};
				FiltRef[NFRooms]=i+1000000;
				NFRooms++;
			};
		};
	};
	
};
extern unsigned short dwVersion;
bool TotalPeerEngine::CheckInFilter(TPE_Room* R){
	if(FILTER.CHK_Ping&&ServerGetPing(R->G)>=FILTER.MinPing)return false;
	int np=ServerGetIntValue(R->G,"numplayers",0);
	if(FILTER.CHK_Players&&np!=FILTER.NPlayers)return false;
	if(FILTER.CHK_MinPlayers&&np<=FILTER.NPlayers)return false;
	if(FILTER.CHK_Type){
		int N=GetCEW(R->G,0);
		if(N==1&&FILTER.CHK_Type==1)return false;
		if(N==0&&FILTER.CHK_Type==2)return false;
	};
	if(FILTER.CHK_Ver){
		char cc1[32];
		sprintf(cc1,"%s",LobbyVersion);
		char* ccx=ServerGetStringValue(R->G,"gamever","?");
		if(strcmp(ccx,cc1))return false;
	};
	if(FILTER.MASKSTR[0]){
		if(!strstr(R->Name,FILTER.MASKSTR))return false;
	};
	if(FILTER.CHK_Level)
		if(GetCEW(R->G,1)!=FILTER.CHK_Level)return false;
	return true;
};
bool TotalPeerEngine::CheckGInFilter(RoomInGame* R){
	int np=R->NPlayers;
	if(FILTER.CHK_Players&&np!=FILTER.NPlayers)return false;
	if(FILTER.CHK_MinPlayers&&np<=FILTER.NPlayers)return false;
	if(FILTER.CHK_Type){
		if(R->Type==1&&FILTER.CHK_Type==1)return false;
		if(R->Type==0&&FILTER.CHK_Type==2)return false;
	};
	if(FILTER.MASKSTR[0]){
		if(!strstr(R->Name,FILTER.MASKSTR))return false;
	};
	return true;
};
int TotalPeerEngine::CompareGRooms(RoomInGame* R1,RoomInGame* R2){
	switch(SORTTYPE){
	case 0:
		return 0;
	case 1://name
		return _stricmp(R1->Name,R2->Name);
		break;
	case -1://-name
		return -_stricmp(R1->Name,R2->Name);
		break;
	case 2://players
		{
			int N1=R1->NPlayers;
			int N2=R2->NPlayers;
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -2://-players
		{
			int N1=R1->NPlayers;
			int N2=R2->NPlayers;
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;
	case 3://ping
		return 0;
	case -3://-ping
		return 0;
	case 4://version
		return 0;
	case -4://version
		return 0;
	case 5://Type
		{
			int N1=R1->Type;
			int N2=R2->Type;
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -5://Type
		{
			int N1=R1->Type;
			int N2=R2->Type;
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;

	};
};
//<0 if R1<R2
//>0 if R1>R2
// 0 if R1==R2
int TotalPeerEngine::CompareRooms(TPE_Room* R1,TPE_Room* R2){
	bool modex1=0;
	char* ccx=ServerGetStringValue(R1->G,"gamemode","x");
	if(!strcmp(ccx,"closedplaying")){
		modex1=0;
	}else
	if(strcmp(ccx,"wait")){
		modex1=1;
	}else modex1=2;
	bool modex2=0;
	ccx=ServerGetStringValue(R2->G,"gamemode","x");
	if(!strcmp(ccx,"closedplaying")){
		modex2=0;
	}else
	if(strcmp(ccx,"wait")){
		modex2=1;
	}else modex2=2;
	if(modex1!=modex2){
		return modex1>modex2?-1:1;
	};
	switch(SORTTYPE){
	case 0:
		return 0;
	case 1://name
		return _stricmp(R1->Name,R2->Name);
		break;
	case -1://-name
		return -_stricmp(R1->Name,R2->Name);
		break;
	case 2://players
		{
			int N1=ServerGetIntValue(R1->G,"numplayers",0);
			int N2=ServerGetIntValue(R2->G,"numplayers",0);
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -2://-players
		{
			int N1=ServerGetIntValue(R1->G,"numplayers",0);
			int N2=ServerGetIntValue(R2->G,"numplayers",0);
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;
	case 3://ping
		{
			int N1=ServerGetPing(R1->G);
			int N2=ServerGetPing(R2->G);
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -3://-ping
		{
			int N1=ServerGetPing(R1->G);
			int N2=ServerGetPing(R2->G);
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;
	case 4://version
		{
			char* N1=ServerGetStringValue(R1->G,"gamever",0);
			char* N2=ServerGetStringValue(R2->G,"gamever",0);
			return strcmp(N1,N2);
		};
		break;
	case -4://version
		{
			char* N1=ServerGetStringValue(R1->G,"gamever","0.00");
			char* N2=ServerGetStringValue(R2->G,"gamever","0.00");
			return -strcmp(N1,N2);
		};
		break;
	case 5://Type
		{
			int N1=GetCEW(R1->G,0);
			int N2=GetCEW(R2->G,0);
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -5://Type
		{
			int N1=GetCEW(R1->G,0);
			int N2=GetCEW(R2->G,0);
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;
	case 6://level
		{
			int N1=GetCEW(R1->G,1);
			int N2=GetCEW(R2->G,1);
			if(N1<N2)return -1;
			else if(N1>N2)return 1;
			else return 0;
		};
		break;
	case -6://level
		{
			int N1=GetCEW(R1->G,1);
			int N2=GetCEW(R2->G,1);
			if(N1>N2)return -1;
			else if(N1<N2)return 1;
			else return 0;
		};
		break;

	};
};
struct EnumPSTR{
	int N;
	char Nick[8][128];
};
void PEER_EnumPlayersCallback4(
		PEER peer,  // The peer object.
		PEERBool success,  // PEERTrue if success, PEERFalse if failure.
		RoomType roomType,  // The room whose players are being enumerated.
		int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
		const char * nick,  // The nick of the player.
		PEERBool host,  // PEERTrue if this player is a host in this room (has ops).
		void * param  // User-data.
	){
	EnumPSTR* EPS=(EnumPSTR*)param;
	if(success){
		if(EPS->N<8){
			strcpy(EPS->Nick[EPS->N],nick);
			EPS->N++;
		};
	};
};
void TotalPeerEngine::CreateMyRoomInfoString(char* s){
	if(!Peer)return;
	if((!MyRoom)||(!MyRoom->RoomConnected))return;
	s[0]=0;
	strcat(s,TPEN.MyRoom->Name);
	/*
	EnumPSTR EPS;
	EPS.N=0;
	peerEnumPlayers(Peer,StagingRoom,&PEER_EnumPlayersCallback4,&EPS);
	sprintf(s,"@@@[ADM@XYL]%d %s 7200000 %d %d []",strlen(MyRoom->Name),MyRoom->Name,MyRoom->Type,EPS.N);
	for(int i=0;i<EPS.N;i++){
		char cc1[128];
		sprintf(cc1," %d %s",strlen(EPS.Nick[i]),EPS.Nick[i]);
		strcat(s+strlen(s),cc1);
	};
	*/
};
void TotalPeerEngine::AddRoomInGame(char* s){
	if(!Peer)return;
	int L=0;
	int z=sscanf(s+12,"%d",&L);
	if(z!=1)return;
	char ccc1[128];
	memset(ccc1,0,128);
	char* cc1=strstr(s," ");
	if(cc1){
		memcpy(ccc1,cc1+1,L);
		cc1+=L+2;
		int TP,NP,GT;
		z=sscanf(cc1,"%d%d%d",&GT,&TP,&NP);
		if(z!=3)return;
		char NAMES[8][64];
		memset(&NAMES,0,sizeof NAMES);
		cc1=strstr(cc1,"[]");
		if(!cc1)return;
		cc1+=3;
		for(int i=0;i<NP;i++){
			z=sscanf(cc1,"%d",&L);
			if(z!=1)return;
			cc1=strstr(cc1," ");
			if(!cc1)return;
			cc1++;
			memcpy(NAMES[i],cc1,L);
			cc1+=L+1;
			if(i<NP-1){
				//cc1=strstr(cc1," ");	
				//if(!cc1)return;
			};
		};
		for(i=0;i<NRInGame;i++){
			if(!strcmp(RInGame[i].Name,ccc1))return;
		};
		if(NRInGame>=MaxRInGame){
			MaxRInGame+=32;
			RInGame=(RoomInGame*)realloc(RInGame,MaxRInGame*sizeof RoomInGame);
		};
		if(NP>8)NP=8;
		RoomInGame* RIG=RInGame+NRInGame;
		NRInGame++;
		RIG->Name=new char[strlen(ccc1)+1];
		strcpy(RIG->Name,ccc1);
		RIG->Type=TP;
		RIG->StartTime=GetTickCount();
		RIG->MaxTime=GT;
		RIG->NPlayers=NP;
		for(i=0;i<NP;i++){
			RIG->Players[i]=new char[strlen(NAMES[i])+1];
			strcpy(RIG->Players[i],NAMES[i]);
		};
		ChangeServer=1;
		FILTER.CRC++;
		DelServer(RIG->Name,NULL);
	};
	ProcessRoomsInGame();
};
void TotalPeerEngine::ProcessRoomsInGame(){
	return;
	if(!Peer)return;
	int NOP=0;
	do{
		if(NRInGame){
			CurrentPlRoom=(CurrentPlRoom+1)%NRInGame;
			RoomInGame* RIG=RInGame+CurrentPlRoom;
			if(GetTickCount()-RIG->StartTime>20000){
				int NPLPRESENT=0;
				for(int j=0;j<RIG->NPlayers;j++){
					char* sss=RIG->Players[j];
					for(int q=0;q<NPlayers;q++){
						NOP++;
						if(!strcmp(sss,Players[q].Name)){
							free(RIG->Players[j]);
							if(j<RIG->NPlayers-1)
								memcpy(RIG->Players+j,RIG->Players+j+1,(RIG->NPlayers-j-1)*4);
							RIG->NPlayers--;
							q=NPlayers;
							j--;
						};
					};
				};
				if(RIG->NPlayers<2||GetTickCount()-RIG->StartTime>RIG->MaxTime){
					//delete room
					free(RIG->Name);
					for(int q=0;q<RIG->NPlayers;q++)free(RIG->Players[q]);
					if(CurrentPlRoom<NRInGame-1){
						memcpy(RInGame+CurrentPlRoom,RInGame+CurrentPlRoom+1,(NRInGame-1-CurrentPlRoom)*sizeof RoomInGame);
					};
					NRInGame--;
					ChangeServer=1;
					FILTER.CRC++;
				};
			}else NOP+=20;
		};
	}while(NOP<500&&NRInGame);
	NRoomPlayers=0;
	for(int i=0;i<NRInGame;i++){
		RoomInGame* RIG=RInGame+i;
		for(int j=0;j<RIG->NPlayers;j++){
			if(NRoomPlayers<1024){
				RoomPlNames[NRoomPlayers]=RIG->Players[j];
				NRoomPlayers++;
			};
		};
	};
	int GTT=GetTickCount();
	if(GTT-ConnStartTime>10000&&!RPRO.ICanAnswer){
		if(NPlayers>1&&((!RPRO.LastSendReqTime)||GTT-RPRO.LastSendReqTime>10000)){
			//need to find a new client
			int rc;
			char* cnick;
			int NTC=0;
			do{
				rc=(GTT/100)%NPlayers;
				cnick=Players[rc].Name;
				if((!strcmp(cnick,MyNick))||(!strstr(cnick,"[inside]")))cnick=NULL;
				NTC++;
			}while(NTC<20&&!cnick);
			if(NTC<20){
				strcpy(RPRO.RCNick,cnick);
				RPRO.LastSendReqTime=GetTickCount();
				peerMessagePlayer(Peer,cnick,"@@@[ADM@GPL]");
			};
		};
		if(NPlayers<=1)RPRO.ICanAnswer=1;
	};
	if(RPRO.ICanAnswer&&RPRO.IAnswer){
		if(GTT-RPRO.LastAnswerTime>1000){
			RPRO.LastAnswerTime=GTT;
			int SENDIDX=-1;
			int DTTIME;
			if(RPRO.LastSendIndex==-1){
				int DTMAX=1000000;
				for(int i=0;i<NRInGame;i++){
					int dt=RInGame[i].StartTime-GTT;
					if(dt<DTMAX){
						DTMAX=dt;
						SENDIDX=i;
						DTTIME=RInGame[i].StartTime;
					};
				};
				if(SENDIDX!=-1)RPRO.LastSendIndex=DTTIME;
			}else{
				int DTMAX=0;
				DTTIME=RPRO.LastSendIndex;
				for(int i=0;i<NRInGame;i++){
					int dt=RInGame[i].StartTime-DTTIME;
					if(dt>0&&(dt<DTMAX||DTMAX==0)){
						DTMAX=dt;
						SENDIDX=i;
					};
				};
				if(SENDIDX!=-1)RPRO.LastSendIndex=RInGame[SENDIDX].StartTime;
			};
			if(SENDIDX!=-1){
				RoomInGame* RIG=RInGame+SENDIDX;
				char s[256];
				sprintf(s,"@@@[ADM@XYL]%d %s %d %d %d []",strlen(RIG->Name),RIG->Name,
					RIG->MaxTime-GTT+RIG->StartTime,RIG->Type,RIG->NPlayers);
				for(int i=0;i<RIG->NPlayers;i++){
					char cc1[128];
					sprintf(cc1," %d %s",strlen(RIG->Players[i]),RIG->Players[i]);
					strcat(s+strlen(s),cc1);
				};
				peerMessagePlayer(Peer,RPRO.RCNick,s);
			}else{
				peerMessagePlayer(Peer,RPRO.RCNick,"@@@[ADM@NOPLAY]");
				RPRO.IAnswer=0;
			};
		};
	};
	
};
void AbsentPlayers::AddPlayer(char* Nick){
	int InsIndex=-1;
	for(int i=0;i<NPlayers;i++){
		int s=_stricmp(Nick,Names[i]);
		
		if(s<0&&InsIndex==-1)InsIndex=i;
	};
	if(NPlayers>=MaxPlayers){
		MaxPlayers+=32;
		Names=(char**)realloc(Names,4*MaxPlayers);
		StartTime=(int*)realloc(StartTime,4*MaxPlayers);
	};
	if(InsIndex==-1){
		Names[NPlayers]=new char[strlen(Nick)+1];
		StartTime[NPlayers]=GetTickCount();
		strcpy(Names[NPlayers],Nick);
		NPlayers++;
	}else{
		for(int j=NPlayers;j>InsIndex;j--){
			Names[j]=Names[j-1];
			StartTime[j]=StartTime[j-1];
		};
		Names[InsIndex]=new char[strlen(Nick)+1];
		StartTime[InsIndex]=GetTickCount();
		strcpy(Names[InsIndex],Nick);
		NPlayers++;
	};
};
void AbsentPlayers::DelPlayer(char* Nick){
	for(int i=0;i<NPlayers;i++)if(!strcmp(Nick,Names[i])){
		free(Names[i]);
		if(i<NPlayers-1){
			memcpy(Names+i,Names+i+1,(NPlayers-i-1)*4);
			memcpy(StartTime+i,StartTime+i+1,(NPlayers-i-1)*4);
		};
		NPlayers--;
	};
};
void AbsentPlayers::Clear(){
	if(!Names)return;
	for(int i=0;i<NPlayers;i++)free(Names[i]);
	free(Names);
	free(StartTime);
	TotalPeerEngine* t=TPE;
	memset(this,0,sizeof AbsentPlayers);
	TPE=t;
};
void AbsentPlayers::Process(){
	if(!NPlayers)return;
	int tt=GetTickCount();
	for(int i=0;i<3&&NPlayers;i++){
		Index=(Index+1)%NPlayers;
		if(tt-StartTime[Index]>5000){
			char* nick=Names[Index];
			int N=TPE->NPlayers;
			for(int j=0;j<N&&nick;j++){
				if(!strcmp(TPE->Players[j].Name,nick)){
					DelPlayer(nick);
					nick=NULL;
				};
			};
		};
	};
};
void TotalPeerEngine::StartGame(bool Host){
	if(Connected&&ChatConnected){
		peerMessageRoom(Peer,TitleRoom,"@@@NFO \\$flags$\\g\\");
		peerStopListingGames(Peer);
		peerLeaveRoom(Peer,TitleRoom);
		ChatConnected=0;
		char ccc[256];
		//peerMessagePlayer(Peer,"spybot","\\launched\\1\\gamename\\cossacks\\");
		LastSpyBotSignalTime=GetTickCount();
		if(MyRoom){
			if(MyRoom->RoomConnected){
				GameType=MyRoom->Type;
				if(MyRoom->Players){
					free(MyRoom->Players);
				};
				free(MyRoom);
				MyRoom=NULL;
			}else{
				free(MyRoom);
				MyRoom=NULL;
			};
		};
		NPlayers=0;
		NRooms=0;
		ABPL.Clear();
		if(Host)peerStateChanged(Peer);
	};
};
void MarkNameLikeUnical(int Profile,bool Uniq){
	for(int i=0;i<TPEN.NPlayers;i++)if(TPEN.Players[i].ProfileID==Profile){
		if(Uniq)TPEN.Players[i].ProfState=15;
		else TPEN.Players[i].ProfState=7;
	};
};

void PEER_GetPlayerIPCallback(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * nick,  // The player's nick.
	unsigned int IP,  // The player's IP, in network byte order.  PANTS|09.11.00 - was unsigned long
	void * param  // User-data.
	){
	if(success){
		char* IPS=(char*)param;
		sprintf(IPS,"%d.%d.%d.%d",IP&255,(IP>>8)&255,(IP>>16)&255,(IP>>24)&255);
	};
};
bool GetPLIP(char* Nick,char* IP){
	IP[0]=0;
	peerGetPlayerIP(TPEN.Peer,Nick,&PEER_GetPlayerIPCallback,IP,PEERFalse);
	int T0=GetTickCount();
	do{
		ProcessMessages();
	}while(GetTickCount()-T0<30000&&!IP[0]);
	return IP[0]!=0;
};