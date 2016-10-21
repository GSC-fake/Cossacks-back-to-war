#include "Peer.h";
#pragma pack(1)
struct TPE_Player{
	char Name[64];
	int Ping;
	int Status;
	bool ready:1;
	bool Muted:1;
	int ProfileID;
	byte ProfState;
};
class TPE_Room{
public:
	char Name[64];
	char version[12];
	char HostAddress[32];
	int Ping;
	int Type;
	int Nplayers;
	int MaxPlayer;
	GServer G;
};
class TotalPeerEngine;
class TPE_MyRoom:public TPE_Room{
public:
	PEER Peer;
	TotalPeerEngine* TPE;
	TPE_Player* Players;
	bool Host;
	int NPlayers;
	int MaxPlayers;
	int Type;
	int Level;
	bool RStart;
	bool Change;
	bool ChangeChat;
	bool RoomConnected;
	void AddPlayer(char* nick);
	void DelPlayer(char* nick);
	void SetPing(char* nick,int Ping);
	void SetReady(char* nick,bool State);
	void ChangeMyReady();
	void ResetMyReady();
	void SetMyReady(bool);
	void Refresh();
	void RunGame();
};
struct ChatString{
	char* PlName;
	char* Message;
};
class ChatQueue{
public:
	int NCStr;
	int MaxCStr;
	ChatString* CStr;
	void Clear();
	void Add(char* nick,char* Message);
};
class RoomFilter{
public:
	char MASKSTR[64];
	bool CHK_Ping:1;
	bool CHK_Ver:1;
	bool CHK_MinPlayers:1;
	bool CHK_Players:1;
	byte CHK_Level;
	byte CHK_Type;
	int  MinPing;
	int NPlayers;
	DWORD CRC;
	
};
struct RoomInGame{
	int NPlayers;
	char* Name;
	char* Players[8];
	int Type;
	int StartTime;
	int MaxTime;
};
class RoomPropagator{
public:
	bool ReqIsSent:1;
	bool IAnswer:1;
	bool ICanAnswer:1;
	int LastSendReqTime;
	int LastAnswerTime;
	char RCNick[64];
	int LastSendIndex;
};
class TotalPeerEngine;
class AbsentPlayers{
public:
	TotalPeerEngine* TPE;
	int Index;
	int LastResvTime;
	int NPlayers;
	int MaxPlayers;
	char** Names;
	int* StartTime;
	void AddPlayer(char* Nick);
	void DelPlayer(char* Nick);
	void Clear();
	void Process();
};
class TotalPeerEngine{
public:
	int PTIME;
	int ConnStartTime;
	RoomFilter FILTER;
	bool Change;
	bool ChangeChat;
	bool ChangeLocalChat;
	bool ChangeServer;
	int SORTTYPE;//0-unsorted,1-by name,2-by players,3-by ping
	int LastSpyBotSignalTime;
	char InfoRequest[64];
	char MyIP[32];
	//-----------------//
	bool Runned;
	DWORD HOSTIP;
	char HostMessage[256];
	int CurrentRoom;
	//-----------------//
	AbsentPlayers ABPL;
	TotalPeerEngine();
	~TotalPeerEngine();
	char MyNick[64];
	int State;
	int Level;
	int ErrorType;
	PEER Peer;
	int NPlayers;
	int MaxPlayers;
	TPE_Player* Players;
	int NRooms;
	int MaxRooms;
	int NFRooms;
	int MaxFRooms;
	int* FiltRef;
	RoomInGame* RInGame;
	
	int NRInGame;
	int MaxRInGame;
	int NRoomPlayers;
	char* RoomPlNames[1024];
	int CurrentPlRoom;
	TPE_Room* Room;
	TPE_MyRoom* MyRoom;
	bool Connected;
	bool ChatConnected;
	ChatQueue GlobalChat;
	ChatQueue LocalChat;
	RoomPropagator RPRO;
	int GameType;
	void AddPlayer(char* nick);
	void DelPlayer(char* nick);
	void SetPing(char* nick,int Ping);
	void Connect(char* Nick);
	void Disconnect();
	void StartGame(bool Host);
	void Process();
	void SendGlobalChat(char* Message);
	void SendLocalChat(char* Message);
	void RefreshPlayers();
	void ProcessFilter();
	bool CheckInFilter(TPE_Room* R);
	bool CheckGInFilter(RoomInGame* R);
	int CompareRooms(TPE_Room* R1,TPE_Room* R2);
	int CompareGRooms(RoomInGame* R1,RoomInGame* R2);
	//--------------//
	void CreateStagingRoom(char* Name,char* Password,int MaxPlayers,int Type,int Level);
	void AddServer(char* Name,GServer server);
	void DelServer(char* Name,GServer server);
	void UpdateServer(char* Name,GServer server);
	void ClearServers();
	void RefreshSessions();
	void JoinRoom(TPE_Room* Room,char* password);
	void LeaveMyRoom();
	//--------VISUAL FUNCTIONALITY-------//
	bool NeedReconnect();
	bool CanJoin();
	bool CanCreate();
	bool IsInStagingRoom();
	bool StagingStateChanged();
	void CreateMyRoomInfoString(char* s);
	void AddRoomInGame(char* s);
	void ProcessRoomsInGame();
};
extern TotalPeerEngine TPEN;
int GetCEW(GServer G,int Index);