/******
gstats.c
GameSpy Stats/Tracking SDK 
GameSpy Persistent Storage SDK 

Copyright 1999-2000 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, CA 92614
949-798-4200
Fax 949-798-4299


******

Please see the GameSpy Stats and Tracking SDK documentation for more info

******/

/********
INCLUDES
********/
#include <stdlib.h>
#include <stdio.h>
#include "gstats.h"
#include "gpersist.h"

#if defined(applec) || defined(THINK_C) || defined(__MWERKS__) && !defined(__KATANA__)
	#include "::nonport.h"
	#include "::darray.h"
	#include "::md5.h"
#else
	#include "../nonport.h"
	#include "../darray.h"
	#include "../md5.h"
#endif
#include <string.h>

//since WinCE doesn't have remove prototyped
#if defined(UNDER_CE) || defined(__KATANA__) || defined(__mips64)
	#define remove(a) ;
#endif


#ifdef __cplusplus
extern "C" {
#endif

/********
TYPEDEFS
********/
struct statsgame_s 
{
	int connid;
	int sesskey;
	int usebuckets;
	bucketset_t buckets;
	char challenge[9];
	DArray playernums; //for player number translation
	DArray teamnums; //for team number translation
	int totalplayers, totalteams;
	unsigned long sttime;

};

typedef enum {rt_authcb, rt_datacb, rt_savecb, rt_profilecb}  reqtype_t;
typedef struct 
{
	reqtype_t reqtype;
	int localid;
	int profileid;
	persisttype_t pdtype;
	int pdindex;
	void *instance;
	void *callback;

} serverreq_t;


/********
PROTOTYPES
********/
static int ServerOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index);
static double ServerOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index);
static char *ServerOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index);

static int TeamOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index);
static double TeamOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index);
static char *TeamOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index);

static int PlayerOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index);
static double PlayerOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index);
static char *PlayerOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index);

static char *CreateBucketSnapShot(bucketset_t buckets);

#ifdef ALLOW_DISK
static void CheckDiskFile();
static void DiskWrite(char *line, int len);
#endif
static void InternalInit();
static int SendChallengeResponse(char *indata, int gameport);
static int DoSend(char *data, int len);
static void xcode_buf(char *buf, int len);
static int g_crc32(char *s, int len);
static void create_challenge(int challenge, char chstr[9]);
static char *value_for_key(const char *s, const char *key);
static char *value_for_key_safe(const char *s, const char *key);
static int get_sockaddrin(char *host, int port, struct sockaddr_in *saddr, struct hostent **savehent);
/**************
PERSISTENT STORAGE PROTOTYPES
**************/
static void AddRequestCallback(reqtype_t reqtype, int localid, int profileid, persisttype_t pdtype, int pdindex, void *callback, void *instance);
static void SendPlayerAuthRequest(char *data, int len, int localid, PersAuthCallbackFn callback, void *instance);
static void SendPlayerAuthRequest(char *data, int len, int localid, PersAuthCallbackFn callback, void *instance);
static int SocketReadable(SOCKET s);
static char *FindFinal(char *buff, int len);
static int FindRequest(reqtype_t reqtype, int localid, int profileid);
static void ProcessPlayerAuth(char *buf, int len);
static void ProcessGetPid(char *buf, int len);
static void ProcessGetData(char *buf, int len);
static void ProcessSetData(char *buf, int len);
static void ProcessStatement(char *buff, int len);
static int ProcessInBuffer(char *buff, int len);
static void CallReqCallback(int reqindex, int success, char *data, int length);
static void ClosePendingCallbacks();
static void SetPersistDataHelper(int localid, int profileid, persisttype_t type, int index, char *data, int len, PersDataSaveCallbackFn callback, void *instance, int kvset);

/********
DEFINES
********/
//#define SSHOST "207.199.80.230"
#define SSHOST "gamestats.gamespy.com"
#define SSPORT 29920

#define FIXGAME(g,r) if (g == NULL) g = g_statsgame; if (g == NULL) return r;
#define DoFunc(f,g, n, v, t, r) \
	if (g == NULL) g = g_statsgame; \
	if (!g) r = v; \
	else { \
	r = f(g->buckets, n, v); \
	if (!r) \
	r = BucketNew(g->buckets, n, t, v); }
#define DOXCODE(b, l, e) enc = e; xcode_buf(b,l);


/********
VARS
********/
char gcd_gamename[256] = "";
char gcd_secret_key[256] = "";
static statsgame_t g_statsgame = NULL;
static int connid = 0;
static int sesskey = 0;
static SOCKET sock = INVALID_SOCKET;
/*	#define enc1 "GameSpy 3D"
	#define enc2 "Industries"
	#define enc3 "ProjectAphex"
	#define STATSFILE "gstats.dat" */
/* A couple vars to help avoid the string table */
static char enc1[16] = {'\0','a','m','e','S','p','y','3','D','\0'};
static char enc2[16]= {'\0','n','d','u','s','t','r','i','e','s','\0'};
static char enc3[16] = {'\0','r','o','j','e','c','t','A','p','h','e','x','\0'};
static char statsfile[16] = {'\0','s','t','a','t','s','.','d','a','t','\0'};
static char finalstr[10] = {'\0','f','i','n','a','l','\\','\0'};
static char *enc = enc1;
static int internal_init = 0;
static char *rcvbuffer = NULL;
static int rcvmax = 0;
static int rcvlen = 0;

static DArray serverreqs = NULL; //for pre-authentication requests


BucketFunc bucketfuncs[NUMOPS] = 
{BucketSet, BucketAdd, BucketSub, BucketMult, BucketDiv, BucketConcat, BucketAvg};

void * bopfuncs[][3] = 
{
		{ServerOpInt, ServerOpFloat, ServerOpString},
		{TeamOpInt, TeamOpFloat, TeamOpString},
		{PlayerOpInt, PlayerOpFloat, PlayerOpString},
};

/****************************************************************************/
/* PUBLIC FUNCTIONS */
/****************************************************************************/
#define RAWSIZE 128
char *GenerateAuth(char *challenge,  char *password, char response[33])
{
	char rawout[RAWSIZE];
	
	/* check to make sure we weren't passed a huge pass/challenge */
	if (strlen(password) + strlen(challenge) + 20>= RAWSIZE)
	{
		strcpy(response,"CD Key or challenge too long");
		return response;
	}

	/* response = MD5(pass + challenge) */
	sprintf(rawout, "%s%s",password, challenge );

	/* do the response md5 */
	MD5Digest((unsigned char *)rawout, strlen(rawout), response);
	return response;
}

/****************************************************************************/
int InitStatsConnection(int gameport)
{
	struct   sockaddr_in saddr;
	char indata[64];
	int ret;
	
	/* Init our hidden strings if needed */
	if (!internal_init)
		InternalInit();

	SocketStartUp();
	sesskey = (unsigned int)current_time();

	/* Get connected */
	if (sock != INVALID_SOCKET)
		CloseStatsConnection();

	rcvlen = 0; //make sure ther receive buffer is cleared

	if (get_sockaddrin(SSHOST,SSPORT,&saddr,NULL) == 0)
		return GE_NODNS;

	sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (sock == INVALID_SOCKET)
		return GE_NOSOCKET;
	if (connect ( sock, (struct sockaddr *) &saddr, sizeof saddr ) != 0)
	{
		CloseStatsConnection();
		return GE_NOCONNECT; 
	}
	/* Read the challenge */
	ret = recv(sock, indata, 64,0);
	if (ret <= 0)
	{
		CloseStatsConnection();
		return GE_DATAERROR; 
	}
	indata[ret] = 0;

	/* Decode it */
	DOXCODE(indata, ret, enc1);
	/* Send a response */
	ret = SendChallengeResponse(indata, gameport);
	if (ret != GE_NOERROR)
		return ret;

#ifdef ALLOW_DISK
	/* Check for old data */
	CheckDiskFile();
#endif

	return GE_NOERROR;
}

/****************************************************************************/
void CloseStatsConnection()
{
	if (sock != INVALID_SOCKET)
	{
		shutdown(sock,2);
		closesocket(sock);
	}
	sock = INVALID_SOCKET;
	//call any pending callbacks with the data as lost
	ClosePendingCallbacks();
	if (rcvbuffer != NULL)
	{
		free(rcvbuffer);
		rcvbuffer = NULL;
		rcvmax = 0;
		rcvlen = 0;
	}

}

/****************************************************************************/
int IsStatsConnected()
{
	return (sock != INVALID_SOCKET);
}

/****************************************************************************/
#define CHALLENGEXOR 0x38F371E6
char *GetChallenge(statsgame_t game)
{
	static char challenge[9];
	if (game == NULL)
		game = g_statsgame;
	if (game == NULL)
	{
		create_challenge(connid ^ CHALLENGEXOR,challenge);
		return challenge;
	}
	return game->challenge;
}

/****************************************************************************/
statsgame_t NewGame(int usebuckets)
{
	statsgame_t game = malloc(sizeof (struct statsgame_s));
	char data[256];
	int len;

	if (!internal_init)
		InternalInit();
	game->connid = connid;
	game->sesskey = sesskey++;
	game->buckets = NULL;
	game->playernums = NULL;
	game->teamnums = NULL;
	game->usebuckets = usebuckets;
	/* If connected, try to send */
	if (sock != INVALID_SOCKET)
	{ 
		char respformat[] = "\xC\x1C\xA\x1D\x2\x2\x19\x24\x2C\x34\x6\x17\x3E\x1C\x6\xE\x39\x46\x10\x1D\x3\xD\x16\xB\x3B\x17\x16\x36\x40\x7";
		//"\newgame\\connid\%d\sesskey\%d"
		DOXCODE(respformat, sizeof(respformat)-1, enc3);
		len = sprintf(data,respformat,game->connid, game->sesskey);
		len = DoSend(data, len);
		if (len <= 0)
		{
			CloseStatsConnection();
		}
		create_challenge(game->connid ^ CHALLENGEXOR,game->challenge);
	}
	/* If send failed then write to disk */
	if (sock == INVALID_SOCKET) 
	{
#ifdef ALLOW_DISK
		char respformat[] = "\xC\x1C\xA\x1D\x2\x2\x19\x24\x2C\x34\x16\x1D\x23\x1\x4\xF\x1C\x3F\x51\x25\x2C\x34\x6\x10\x31\x1E\x3\xF\xB\x4\x11\x1D\x55\xC";
		//"\newgame\\sesskey\%d\\challenge\%d"
		DOXCODE(respformat, sizeof(respformat)-1, enc3);
		len = sprintf(data,respformat,game->sesskey, game->sesskey ^ 0x38F371E6);
		DiskWrite(data, len);
		game->connid = 0;
		create_challenge(game->sesskey ^ CHALLENGEXOR,game->challenge);

#else
		free(game);
		game = NULL;
#endif
	
	}

	if (game && game->usebuckets)
	{
		game->buckets = NewBucketSet();
		game->playernums = ArrayNew(sizeof(int),32,NULL);
		game->teamnums = ArrayNew(sizeof(int),2,NULL);
		game->totalplayers = game->totalteams = 0;
	}
	if (game)
		game->sttime = current_time();
	g_statsgame = game;
	return game;
	
}


/****************************************************************************/
void FreeGame(statsgame_t game)
{
	if (!game)
	{
		game = g_statsgame;
		g_statsgame = NULL;
	}
	if (!game)
		return;
	if (game->usebuckets)
	{
		if (game->buckets != NULL)
			FreeBucketSet(game->buckets);
		if (game->playernums != NULL)
			ArrayFree(game->playernums);
		if (game->teamnums != NULL)
			ArrayFree(game->teamnums);
	}
	free(game);
}

/****************************************************************************/
int SendGameSnapShot(statsgame_t game, const char *snapshot, int final)
{
	int snaplen;
	int len;
	int ret = GE_NOERROR;
	char *snapcopy;
	char *data;
	FIXGAME(game, GE_DATAERROR);

	/* If using buckets, get the data out of the buckets */
	if (game->usebuckets)
		snapcopy = CreateBucketSnapShot(game->buckets);
	else
		snapcopy = _strdup(snapshot);
	snaplen = strlen(snapcopy);

	data = malloc(snaplen + 256);

	/* Escape the data */
	while (snaplen--)
		if (snapcopy[snaplen] == '\\')
			snapcopy[snaplen] = '\x1';

	/* If connected, try to send it */
	if (sock != INVALID_SOCKET)
	{
		char respformat[] = "\xC\x7\x1F\xE\x2\x2\x19\x24\x2C\x34\x16\x1D\x23\x1\x4\xF\x1C\x3F\x51\x25\x2C\xC\xA\x16\x35\x2E\x4A\xE\x39\x4\x15\x2C\x15\xC\x4\xC\x31\x2E\x4A\x19";
		//	"\updgame\\sesskey\%d\done\%d\gamedata\%s"
		DOXCODE(respformat, sizeof(respformat)-1, enc3);
		len = sprintf(data, respformat, game->sesskey, final, snapcopy);
		snaplen = DoSend(data, len);
		/* If the send failed, close the socket */
		if (snaplen <= 0)
		{
			CloseStatsConnection();
		}
	}
	/* If not connected, or send failed, return error or log to disk */
	if (sock == INVALID_SOCKET)
	{
#ifdef ALLOW_DISK
		char respformat[] = "\xC\x7\x1F\xE\x2\x2\x19\x24\x2C\x34\x16\x1D\x23\x1\x4\xF\x1C\x3F\x51\x25\x2C\xB\xA\x16\x3E\x1B\xB\x36\x40\x7\x28\x25\x1F\x6\x0\x24\x75\x16\x33\xD\x4\xE\x11\x25\x11\x1C\x4\x24\x75\x1\x33\xE\x9\x3F\x45";
		//"\updgame\\sesskey\%d\connid\%d\done\%d\gamedata\%s\dl\1"
		DOXCODE(respformat, sizeof(respformat)-1, enc3);
		len = sprintf(data, respformat, game->sesskey, game->connid, final, snapcopy);
		DiskWrite(data, len);
#else
		ret = GE_NOCONNECT;
#endif
	}
	free(snapcopy);
	free(data);
	return ret;
}

/****************************************************************************/
void NewPlayer(statsgame_t game, int pnum, char *name)
{
	int i = -1;
	FIXGAME(game, ;)
	while (pnum >= ArrayLength(game->playernums))
		ArrayAppend(game->playernums, &i);
	i = game->totalplayers++;
	/* update the pnum array */
	ArrayReplaceAt(game->playernums,&i, pnum);
	BucketIntOp(game, "ctime",bo_set,(int)(current_time() - game->sttime) / 1000,bl_player,pnum);
	BucketStringOp(game,"player",bo_set,name, bl_player,pnum);

}

/****************************************************************************/
void RemovePlayer(statsgame_t game,int pnum)
{
	FIXGAME(game, ;);
	BucketIntOp(game,"dtime",bo_set,(int)(current_time() - game->sttime) / 1000, bl_player, pnum);
}

/****************************************************************************/
void NewTeam(statsgame_t game,int tnum, char *name)
{
	int i = -1;
	FIXGAME(game, ;)
	while (tnum >= ArrayLength(game->teamnums))
		ArrayAppend(game->teamnums, &i);
	i = game->totalteams++;
	/* update the tnum array */
	ArrayReplaceAt(game->teamnums,&i, tnum);
	BucketIntOp(game, "ctime",bo_set,(int)(current_time() - game->sttime) / 1000,bl_team,tnum);
	BucketStringOp(game,"team",bo_set,name, bl_team,tnum);
}

/****************************************************************************/
void RemoveTeam(statsgame_t game, int tnum)
{
	FIXGAME(game, ;);
	BucketIntOp(game,"dtime",bo_set,(int)(current_time() - game->sttime) / 1000, bl_team, tnum);
}

/****************************************************************************
 * PERSISTENT STORAGE FUNCTIONS
 ****************************************************************************/

/****************************************************************************/
void PreAuthenticatePlayerPM(int localid, int profileid,  char *challengeresponse, PersAuthCallbackFn callback, void *instance)
{
	char respformat[] = "\xC\x13\x1A\x1E\xD\x13\x28\x1D\x0\x1\x1\x24\x75\x16\x33\x18\x0\x10\x4\x1D\x55\x1B\x39\x14\x39\x16\x33\x4F\x1";
	//\authp\\pid\%d\resp\%s\lid\%d
	int len;
	char data[256];
	
	DOXCODE(respformat, sizeof(respformat)-1, enc3);
	len = sprintf(data, respformat, profileid, challengeresponse,localid);

	SendPlayerAuthRequest(data, len, localid, callback, instance);

}

/****************************************************************************/
void PreAuthenticatePlayerCD(int localid, char *nick, char *keyhash,  char *challengeresponse, PersAuthCallbackFn callback, void *instance)
{
	char respformat[] = "\xC\x13\x1A\x1E\xD\x13\x28\x1D\x1E\x1\x6\x13\xC\x57\x1C\x36\xE\x6\xD\x29\x11\x1B\xD\x24\x75\x1\x33\x18\x0\x10\x4\x1D\x55\x1B\x39\x14\x39\x16\x33\x4F\x1";
	//\authp\\nick\%s\keyhash\%s\resp\%s\lid\%d
	int len;
	char data[256];
	
	DOXCODE(respformat, sizeof(respformat)-1, enc3);
	len = sprintf(data, respformat, nick, keyhash, challengeresponse,localid);

	SendPlayerAuthRequest(data, len, localid, callback, instance);

}

/****************************************************************************/
void GetProfileIDFromCD(int localid, char *nick, char *keyhash, ProfileCallbackFn callback, void *instance)
{
	char respformat[] = "\xC\x15\xA\x1E\x15\xA\x10\x1D\x2C\x6\xC\x1B\x3B\x2E\x4A\x19\x39\x8\x11\x38\x18\x9\x16\x10\xC\x57\x1C\x36\x9\xA\x10\x1D\x55\xC";
	//\getpid\\nick\%s\keyhash\%s\lid\%d
	int len;
	char data[512];
	DOXCODE(respformat, sizeof(respformat)-1, enc3);
	len = sprintf(data, respformat, nick, keyhash,localid);

	if (sock != INVALID_SOCKET)
		len	= DoSend(data, len);

	/* If the send failed, close the socket */
	if (len <= 0)
	{
		CloseStatsConnection();
		if (callback)
			callback(0,-1,0,instance);
	} else
	{ /* set up the callback */
		AddRequestCallback(rt_profilecb, localid, 0,0,0,callback, instance);
	}
}

/****************************************************************************/
void GetPersistData(int localid, int profileid, persisttype_t type, int index, PersDataCallbackFn callback, void *instance)
{
	GetPersistDataValues(localid,profileid, type,index,"",callback, instance);
}

/****************************************************************************/
void SetPersistData(int localid, int profileid, persisttype_t type, int index, char *data, int len, PersDataSaveCallbackFn callback, void *instance)
{
	SetPersistDataHelper(localid, profileid, type, index,  data, len, callback, instance, 0);
}

/****************************************************************************/
void GetPersistDataValues(int localid, int profileid, persisttype_t type, int index, char *keys, PersDataCallbackFn callback, void *instance)
{
	char respformat[] = "\xC\x15\xA\x1E\x15\x7\x28\x1D\x0\x1\x1\x24\x75\x16\x33\x1A\x11\x1A\x4\x24\x2C\x4D\x1\x24\x34\x1B\x1\xE\x0\x1B\x28\x64\x14\x34\xE\x1D\x29\x1\x33\x4F\x16\x3F\x18\x28\x14\x34\x40\x1C";
	//\getpd\\pid\%d\ptype\%d\dindex\%d\keys\%s\lid\%d
	int len;
	char data[512];
	char tempkeys[256];
	char *p;

	DOXCODE(respformat, sizeof(respformat)-1, enc3);
	strcpy(tempkeys, keys);
	//replace the \ chars with #1
	for (p = tempkeys; *p != 0; p++)
		if (*p == '\\')
			*p = '\x1';
	
	len = sprintf(data, respformat, profileid, type, index, tempkeys, localid);

	if (sock != INVALID_SOCKET)
		len	= DoSend(data, len);

	/* If the send failed, close the socket */
	if (len <= 0)
	{
		CloseStatsConnection();
		if (callback)
			callback(localid, profileid,type, index, 0,"",0,instance);
	} else
	{ /* set up the callback */
		AddRequestCallback(rt_datacb, localid, profileid,type, index, callback, instance);
	}
}

/****************************************************************************/
void SetPersistDataValues(int localid, int profileid, persisttype_t type, int index, char *keyvalues, PersDataSaveCallbackFn callback, void *instance)
{
	SetPersistDataHelper(localid, profileid, type, index, keyvalues, strlen(keyvalues) + 1, callback, instance, 1);
}


/****************************************************************************/
int PersistThink()
{
	int len;
	int processed;

	if (sock == INVALID_SOCKET)
		return 0;

	while (SocketReadable(sock))
	{
		if (rcvmax - rcvlen < 128) //make sure there are at least 128 bytes free in the buffer
		{
			if (rcvmax == 0)
				rcvmax = 256;
			else
				rcvmax *= 2;
			rcvbuffer = realloc(rcvbuffer, rcvmax+1);
			if (rcvbuffer == NULL)
				return 0; //errcon
		}

		len = recv(sock, rcvbuffer + rcvlen, rcvmax - rcvlen, 0);
		if (len <= 0) //lost the connection
		{
			CloseStatsConnection();
			return 0;
		}
		rcvlen += len;
		rcvbuffer[rcvlen] = 0;

		processed = ProcessInBuffer(rcvbuffer, rcvlen);
		if (processed == rcvlen) //then we can just zero it
			rcvlen = 0;
		else
		{
			//shift the remaining data down
			memmove(rcvbuffer,rcvbuffer + processed, rcvlen - processed);
			rcvlen -= processed;
		}
		
		
	}
	if (sock == INVALID_SOCKET)
		return 0;
	else
		return 1;

}


/****************************************************************************
 * UTILITY FUNCTIONS
 ****************************************************************************/

void InternalInit()
{
	internal_init = 1;
	enc1[0] = 'G';
	enc2[0] = 'I';
	enc3[0] = 'P';
	statsfile[0] = 'g';
	finalstr[0] = '\\';

}


static int SendChallengeResponse(char *indata, int gameport)
{
	static char challengestr[] = {'\0','h','a','l','l','e','n','g','e','\0'};
	static char sesskeystr[] = {'\0','e','s','s','k','e','y','\0'};
	char *challenge;
	char resp[128];
	char md5val[33];
	char *stext;
	/* make this harder to find in the string table */
	char respformat[] = "\xC\x13\x1A\x1E\xD\x3F\x28\x26\x11\x5\x0\x16\x31\x1F\xA\x36\x40\x10\x28\x33\x15\x1B\x15\x17\x3E\x1\xA\x36\x40\x10\x28\x31\x1F\x1A\x11\x24\x75\x16\x33\x3\x1\x3F\x45";
 	/*  \auth\\gamename\%s\response\%s\port\%d\id\1 */
	int len;

	challengestr[0] = 'c';
	challenge = value_for_key(indata,challengestr );
	if (challenge == NULL)
	{
		closesocket(sock);
		return GE_DATAERROR;
	}
	
	len = sprintf(resp, "%d%s",g_crc32(challenge,strlen(challenge)), gcd_secret_key);
	
	MD5Digest((unsigned char *)resp, len, md5val);
	DOXCODE(respformat, sizeof(respformat)-1, enc3);
	len = sprintf(resp,respformat,gcd_gamename, md5val, gameport);
	
	if ( DoSend(resp, len) <= 0 )
	{
		closesocket(sock);
		return GE_NOCONNECT;
	}
	/* get the response */
	len = recv(sock, resp,128,0);
	if (len <= 0)
	{
		closesocket(sock);
		return GE_NOCONNECT;
	}
	resp[len] = 0;
	DOXCODE(resp, len, enc1);
	sesskeystr[0] = 's';
	stext = value_for_key(resp, sesskeystr);
	if (stext == NULL)
	{
		closesocket(sock);
		return GE_DATAERROR;
	} else
		connid = atoi(stext);

	return GE_NOERROR;

}


static int DoSend(char *data, int len)
{
	DOXCODE(data,len, enc1);
	strcpy(data+len,finalstr);
	return send(sock, data, len+7,0);
}


#ifdef ALLOW_DISK
/* Note: lots of this is byte order and type size specific, but it shouldn't
matter since the data is read/written always on the same machine */
#define DISKLENXOR 0x70F33A5F
static void CheckDiskFile()
{
	FILE *f;
	char *line;
	char *alldata;
	int len, check, alllen, fsize;
	char filemode[3];
	/* hide our file access from the string table */
	filemode[0] = 'r'; filemode[1] = 'b'; filemode[2] = 0;
	f = fopen(statsfile,filemode);
	if (!f)
		return;
	/* get the size */
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	/* make room for the whole thing */
	alldata = malloc(fsize + 2); 
	alldata[0] = 0;
	alllen = 0;
	while (!feof(f) && !ferror(f))
	{
		/* read the check and line values */
		if (fread(&check,sizeof(check),1,f) == 0 ||
			fread(&len,sizeof(len),1,f) == 0)
			break;
		len ^= DISKLENXOR;
		line = malloc(len + 1);
		/* read the data */
		if (fread(line, 1, len, f) != (size_t)len)
			break;
		line[len] = 0;
		/* decode for checking */
		DOXCODE(line, len, enc2);
		/* double "check" */
		if (check != g_crc32(line, len))
		{
			free(line);
			break;
		}
		/* encode for xmission */
		DOXCODE(line, len, enc1);
		memcpy(alldata + alllen, line, len);
		alllen += len;
		memcpy(alldata + alllen, finalstr, 7);
		alllen += 7;
		free(line);
	}
	fclose(f);
	/* try to send */
	len = send(sock, alldata, alllen, 0);
	if (len <= 0)
	{
		closesocket(sock);
		sock = INVALID_SOCKET;
	} else
		remove(statsfile);
}

static void DiskWrite(char *line, int len)
{
	FILE *f;
	int check;
	int temp;
	char filemode[3];
	/* hide our file access from the string table */
	filemode[0] = 'a'; filemode[1] = 'b'; filemode[3] = 0;
	f = fopen(statsfile,filemode);
	if (!f)
		return;
	check = g_crc32(line, len);
	fwrite(&check, sizeof(check),1,f);
	temp = len ^ DISKLENXOR;
	fwrite(&temp, sizeof(temp), 1, f);
	DOXCODE(line, len, enc2);
	fwrite(line, 1, len, f);
	fclose(f);
}

#endif /* ALLOW_DISK */

/* simple xor encoding */
static void xcode_buf(char *buf, int len)
{
	int i;
	char *pos = enc;

	for (i = 0 ; i < len ; i++)
	{
		buf[i] ^= *pos++;
		if (*pos == 0)
			pos = enc;
	}
}

#define MULTIPLIER -1664117991
static int g_crc32(char *s, int len)
{
	int i;
    int hashcode = 0;
   
    for (i = 0; i < len; i++)
	  hashcode = hashcode * MULTIPLIER + s[i];
    return hashcode;
}

static void create_challenge(int challenge, char chstr[9])
{
	char *p = chstr;
	sprintf(chstr, "%.8x",challenge);
	while (*p != 0)
	{
		*p = (*p) + ('A' - '0') + (p-chstr);
		p++;
	}
}

/* value_for_key: this returns a value for a certain key in s, where s is a string
containing key\value pairs. If the key does not exist, it returns  NULL. 
Note: the value is stored in a common buffer. If you want to keep it, make a copy! */
static char *value_for_key(const char *s, const char *key)
{
	static int valueindex;
	char *pos,*pos2;
	char keyspec[256]="\\";
	static char value[2][256];

	valueindex ^= 1;
	strcat(keyspec,key);
	strcat(keyspec,"\\");
	pos = strstr(s,keyspec);
	if (!pos)
		return NULL;
	pos += strlen(keyspec);
	pos2 = value[valueindex];
	while (*pos && *pos != '\\')
		*pos2++ = *pos++;
	*pos2 = '\0';
	return value[valueindex];
}

/* like value_for_key, but returns an empty string instead of NULL in the not-found case */
static char *value_for_key_safe(const char *s, const char *key)
{
	char *temp;

	temp = value_for_key(s, key);
	if (!temp)
		return "";
	else
		return temp;
}

/* Return a sockaddrin for the given host (numeric or DNS) and port)
Returns the hostent in savehent if it is not NULL */
static int get_sockaddrin(char *host, int port, struct sockaddr_in *saddr, struct hostent **savehent)
{
	struct hostent *hent;

	memset(saddr,0,sizeof(struct sockaddr_in));
	saddr->sin_family = AF_INET;
	saddr->sin_port = htons((unsigned short)port);
	if (host == NULL)
		saddr->sin_addr.s_addr = INADDR_ANY;
	else
		saddr->sin_addr.s_addr = inet_addr(host);
	
	if (saddr->sin_addr.s_addr == INADDR_NONE)
	{
		hent = gethostbyname(host);
		if (!hent)
			return 0;
		saddr->sin_addr.s_addr = *(unsigned int *)hent->h_addr_list[0];
	}
	if (savehent != NULL)
		*savehent = hent;
	return 1;
} 

/* adds a request callback to the list */
static void AddRequestCallback(reqtype_t reqtype, int localid, int profileid, persisttype_t pdtype, int pdindex, void *callback, void *instance)
{
	serverreq_t req;
	
	req.callback = callback;
	req.instance = instance;
	req.localid = localid;
	req.reqtype = reqtype;
	req.profileid = profileid;
	req.pdtype = pdtype;
	req.pdindex = pdindex;
	if (serverreqs == NULL) //create the callback array
	{
		serverreqs = ArrayNew(sizeof(serverreq_t),2,NULL);
	}
	ArrayAppend(serverreqs,&req);
}

/* sends the player authentication request (GP or CD) */
static void SendPlayerAuthRequest(char *data, int len, int localid, PersAuthCallbackFn callback, void *instance)
{
	int sentlen = 0;
	char connerror[] = "\x13\x1D\x1\x4\x0\x0\x0\x28\x1F\x6\x45\x34\x3F\x1\x1B";
	//"Connection Lost"

	if (sock != INVALID_SOCKET)
		sentlen	= DoSend(data, len);

		/* If the send failed, close the socket */
	if (sentlen <= 0)
	{
		CloseStatsConnection();
		DOXCODE(connerror, sizeof(connerror)-1, enc3);
		if (callback)
			callback(localid, 0,0, connerror ,instance);
	} else
	{ /* set up the callback */
		AddRequestCallback(rt_authcb, localid, 0,0,0,callback, instance);
	}
}

/* send a set request, if kvset, then only those keys/values will bet updated */
static void SetPersistDataHelper(int localid, int profileid, persisttype_t type, int index, char *data, int len, PersDataSaveCallbackFn callback, void *instance, int kvset)
{
	char respformat[] = "\xC\x1\xA\x1E\x15\x7\x28\x1D\x0\x1\x1\x24\x75\x16\x33\x1A\x11\x1A\x4\x24\x2C\x4D\x1\x24\x34\x1B\x1\xE\x0\x1B\x28\x64\x14\x34\xE\xE\xC\x57\xB\x36\x9\xA\x10\x1D\x55\xC\x39\x14\x35\x1C\x8\x1E\xD\x3F\x51\x25\x2C\xC\x4\xC\x31\x2E";
		//\setpd\\pid\%d\ptype\%d\dindex\%d\kv\%d\lid\%d\length\%d\data\ --
	int tlen;
	char tdata[512];
	char *senddata;
	
	DOXCODE(respformat, sizeof(respformat)-1, enc3);

	if (type == pd_private_ro || type ==  pd_public_ro)
	{ //can't set read-only types, check that client side
		if (callback)
			callback(localid, profileid, type, index, 0, instance);
		return;
	}
	
	tlen = sprintf(tdata, respformat, profileid, type, index, kvset, localid, len);
	if (tlen + len < 480) //we have enough room to put it in the data block
	{
		memcpy(tdata + tlen, data, len);
		senddata = tdata;

	} else //need to alloc a temp buffer
	{
		senddata = malloc(len + tlen + 256);
		memcpy(senddata, tdata, tlen);
		memcpy(senddata + tlen, data, len);
	}

	if (sock != INVALID_SOCKET)
		tlen = DoSend(senddata, tlen + len);

	/* If the send failed, close the socket */
	if (tlen <= 0)
	{
		CloseStatsConnection();
		if (callback)
			callback(localid, profileid, type, index, 0,instance);
	} else
	{ /* set up the callback */
		AddRequestCallback(rt_savecb, localid, profileid,type, index, callback, instance);
	}
	if (senddata != tdata) //if we alloc'd before sending
		free(senddata);
}

/* returns 1 if the socket is readable, 0 otherwise */
static int SocketReadable(SOCKET s)
{
	fd_set set;
	struct timeval tv = {0,0};
	int n;
	
	if (s == INVALID_SOCKET)
		return 0;

	FD_ZERO(&set);
	FD_SET(s, &set);

	n = select(FD_SETSIZE, &set, NULL, NULL, &tv);
	
	return n;
}

/* find the \final\ string */
static char *FindFinal(char *buff, int len)
{
	char *pos = buff;
	
	while (pos - buff < len - 6)
	{
		if (pos[0] == '\\' && 
			pos[1] == 'f'  && 
			pos[2] == 'i'  && 
			pos[3] == 'n'  && 
			pos[4] == 'a'  && 
			pos[5] == 'l'  && 
			pos[6] == '\\')
		{
			return pos;
		} else
			pos++;
	}
	return NULL;	
}

/* find the request in the callback list */
static int FindRequest(reqtype_t reqtype, int localid, int profileid)
{
	int i;
	serverreq_t *req;

	if (serverreqs == NULL)
		return -1;
	for (i = 0 ; i < ArrayLength(serverreqs); i++)
	{
		req = (serverreq_t *)ArrayNth(serverreqs, i);
		if (req->reqtype == reqtype && req->localid == localid && req->profileid == profileid)
			return i;
	}
	return -1;
	
}

/* process the playerauth result */
static void ProcessPlayerAuth(char *buf, int len)
{
	// \\pauthr\\100000\\lid\\1
	int reqindex;
	char *errmsg;
	int pid;
	int lid;
	pid = atoi(value_for_key_safe(buf,"pauthr"));
	lid = atoi(value_for_key_safe(buf,"lid"));
	errmsg = value_for_key_safe(buf,"errmsg");
	reqindex = FindRequest(rt_authcb,lid,0);
	if (reqindex == -1)
		return;
	((serverreq_t *)ArrayNth(serverreqs, reqindex))->profileid = pid;
	CallReqCallback(reqindex,(pid > 0),errmsg,0);
}

/* process the get profileid result */
static void ProcessGetPid(char *buf, int len)
{
	// \\getpidr\\100000\\lid\\1
	int reqindex;
	int pid;
	int lid;
	pid = atoi(value_for_key_safe(buf,"getpidr"));
	lid = atoi(value_for_key_safe(buf,"lid"));
	reqindex = FindRequest(rt_profilecb,lid,0);
	if (reqindex == -1)
		return;
	((serverreq_t *)ArrayNth(serverreqs, reqindex))->profileid = pid;
	CallReqCallback(reqindex,(pid > 0),NULL,0);
}

/* process the get data result */
static void ProcessGetData(char *buf, int len)
{
	// \\getpdr\\1\\lid\\1\\length\\5\\data\\mydata\\final
	int reqindex;
	int pid;
	int lid;
	int success;
	int length;
	char *data;
	success = atoi(value_for_key_safe(buf,"getpdr"));
	lid = atoi(value_for_key_safe(buf,"lid"));
	pid = atoi(value_for_key_safe(buf,"pid"));
	reqindex = FindRequest(rt_datacb,lid,pid);
	if (reqindex == -1)
		return;
	length = atoi(value_for_key_safe(buf,"length"));
	data = strstr(buf,"\\data\\");
	if (!data)
	{
		length = 0;
		data = "";
	} else
		data += 6; //skip the key
	CallReqCallback(reqindex,success,data,length);
}

/* process the set data result */
static void ProcessSetData(char *buf, int len)
{
	// \\setpdr\\1\\lid\\2\\pid\\100000
	int reqindex;
	int pid;
	int lid;
	int success;
	success = atoi(value_for_key_safe(buf,"setpdr"));
	pid = atoi(value_for_key_safe(buf,"pid"));
	lid = atoi(value_for_key_safe(buf,"lid"));
	reqindex = FindRequest(rt_savecb,lid,pid);
	if (reqindex == -1)
		return;
	CallReqCallback(reqindex,success,NULL,0);
}

/* process a single statement */
static void ProcessStatement(char *buff, int len)
{
	//determine the type

	buff[len] = 0;
	//	printf("GOT: %s\n",buff);
	if (strncmp(buff,"\\pauthr\\",8) == 0)
	{
		ProcessPlayerAuth(buff, len);
	} else if (strncmp(buff,"\\getpidr\\",9) == 0)
	{
		ProcessGetPid(buff, len);
	} else if (strncmp(buff,"\\getpidr\\",9) == 0)
	{
		ProcessGetPid(buff, len);
	} else if (strncmp(buff,"\\getpdr\\",8) == 0)
	{
		ProcessGetData(buff, len);
	} else if (strncmp(buff,"\\setpdr\\",8) == 0)
	{
		ProcessSetData(buff, len);
	}
	
}


/* processes statements in the buffer and returns amount processed */
static int ProcessInBuffer(char *buff, int len)
{
	char *pos;
	int oldlen = len;

	while (len > 0 && (pos = FindFinal(buff, len)))
	{
		DOXCODE(buff,pos - buff, enc1);
		ProcessStatement(buff, pos - buff);
		len -= (pos - buff) + 7;
		buff = pos + 7; //skip the final
	}
	return oldlen - len; //amount processed
}

/* call a single callback function */
static void CallReqCallback(int reqindex, int success, char *data, int length)
{
	serverreq_t *req;
	if (reqindex < 0 || reqindex >= ArrayLength(serverreqs))
		return;
	req = (serverreq_t *)ArrayNth(serverreqs, reqindex);
	if (req->callback)
		switch (req->reqtype)
		{
		case rt_authcb:
			((PersAuthCallbackFn )req->callback)(req->localid, req->profileid, success, data, req->instance);
			break;
		case rt_datacb:
			((PersDataCallbackFn )req->callback)(req->localid,req->profileid,req->pdtype, req->pdindex, success, data, length, req->instance);
			break;
		case rt_savecb:
			((PersDataSaveCallbackFn )req->callback)(req->localid, req->profileid, req->reqtype, req->pdindex,success, req->instance);
			break;
		case rt_profilecb:
			((ProfileCallbackFn )req->callback)(req->localid, req->profileid, success, req->instance);
			break;
		}
	ArrayDeleteAt(serverreqs,reqindex);
}

/* if we get disconnected while callbacks are still pending, make sure we
call all of them, with a success of 0 */
static void ClosePendingCallbacks()
{
	int i;

	if (serverreqs == NULL)
		return;
	for (i = ArrayLength(serverreqs) - 1 ; i >= 0 ; i--)
	{
		char connerror[] = "\x13\x1D\x1\x4\x0\x0\x0\x28\x1F\x6\x45\x34\x3F\x1\x1B";
	//"Connection Lost"
		DOXCODE(connerror, sizeof(connerror)-1, enc3);

		CallReqCallback(i,0,connerror,0);
		
	}
	ArrayFree(serverreqs);
	serverreqs = NULL;
}



/****************************************************************************/
/* BUCKET FUNCTIONS */
/****************************************************************************/
int GetTeamIndex(statsgame_t game, int tnum)
{
	FIXGAME(game, tnum);
	return *(int *)ArrayNth(game->teamnums,tnum);
}
int GetPlayerIndex(statsgame_t game, int pnum)
{
	FIXGAME(game, pnum);
	return *(int *)ArrayNth(game->playernums,pnum);
}

static int ServerOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index)
{
	int *ret;
	DoFunc(func, game, name, &value, bt_int, ret);
	return *(int *)ret;

}
static double ServerOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index)
{
	double *ret;
	DoFunc(func, game, name, &value, bt_float, ret);
	return *(double *)ret;

}
static char *ServerOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index)
{
	char *ret;
	DoFunc(func, game, name, value, bt_string, ret);
	return ret;
}

static int TeamOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_t%d",name, GetTeamIndex(game, index));
	return ServerOpInt(game, fullname, func, value, index);
}
static double TeamOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_t%d",name, GetTeamIndex(game, index));
	return ServerOpFloat(game, fullname, func, value, index);
}
static char *TeamOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_t%d",name, GetTeamIndex(game, index));
	return ServerOpString(game, fullname, func, value, index);
}

static int PlayerOpInt(statsgame_t game,char *name, BucketFunc func,  int value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_%d",name, GetPlayerIndex(game, index));
	return ServerOpInt(game, fullname, func, value, index);
}
static double PlayerOpFloat(statsgame_t game,char *name, BucketFunc func,  double value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_%d",name, GetPlayerIndex(game, index));
	return ServerOpFloat(game, fullname, func, value, index);
}
static char *PlayerOpString(statsgame_t game,char *name, BucketFunc func,  char *value, int index)
{
	char fullname[64];
	sprintf(fullname, "%s_%d",name, GetPlayerIndex(game, index));
	return ServerOpString(game, fullname, func, value, index);
}

static char *CreateBucketSnapShot(bucketset_t buckets)
{
	return DumpBucketSet(buckets);
}

#ifdef __cplusplus
}
#endif