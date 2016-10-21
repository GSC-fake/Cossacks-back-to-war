/*
gp.h
GameSpy Presence SDK 
Dan "Mr. Pants" Schoenblum

Copyright 1999 GameSpy Industries, Inc

Suite E-204
2900 Bristol Street
Costa Mesa, CA 92626
(714)549-7689
Fax(714)549-0757

***********************************************************************
Please see the GameSpy Presence SDK documentation for more information
**********************************************************************/

#ifndef _GP_H_
#define _GP_H_

#ifdef __cplusplus
extern "C" {
#endif

//ENUMS
////////
typedef enum _GPEnum
{
	// Callbacks
	////////////
	GP_ERROR = 0,
	GP_RECV_BUDDY_REQUEST,
	GP_RECV_BUDDY_STATUS,
	GP_RECV_BUDDY_MESSAGE,
	GP_RECV_GAME_INVITE,

	// Global States.
	/////////////////
	GP_INFO_CACHING = 0x0100,
	GP_SIMULATION,

	// Blocking
	///////////
	GP_BLOCKING = 1,
	GP_NON_BLOCKING = 0,

	// Firewall
	///////////
	GP_FIREWALL = 1,
	GP_NO_FIREWALL = 0,

	// Check Cache
	//////////////
	GP_CHECK_CACHE = 1,
	GP_DONT_CHECK_CACHE = 0,

	// Is Valid Email.
	// PANTS|02.15.00
	//////////////////
	GP_VALID = 1,
	GP_INVALID = 0,

	// Fatal Error.
	///////////////
	GP_FATAL = 1,
	GP_NON_FATAL = 0,

	// Sex
	//////
	GP_MALE = 0x0500,
	GP_FEMALE,
	GP_PAT,

	// Profile Search.
	//////////////////
	GP_MORE = 0x0600,
	GP_DONE,

	// Set Info
	///////////
	GP_NICK = 0x0700,
	GP_EMAIL,
	GP_PASSWORD,
	GP_FIRSTNAME,
	GP_LASTNAME,
	GP_ICQUIN,
	GP_HOMEPAGE,
	GP_ZIPCODE,
	GP_COUNTRYCODE,
	GP_BIRTHDAY,
	GP_SEX,
	GP_CPUBRANDID,
	GP_CPUSPEED,
	GP_MEMORY,
	GP_VIDEOCARD1STRING,
	GP_VIDEOCARD1RAM,
	GP_VIDEOCARD2STRING,
	GP_VIDEOCARD2RAM,
	GP_CONNECTIONID,
	GP_CONNECTIONSPEED,
	GP_HASNETWORK,
	GP_OSSTRING,

	// New Profile.
	///////////////
	GP_REPLACE = 0x0800,
	GP_DONT_REPLACE,

	// Public mask.
	///////////////
	GP_MASK_NONE        = 0x00000000,
	GP_MASK_HOMEPAGE    = 0x00000001,
	GP_MASK_ZIPCODE     = 0x00000002,
	GP_MASK_COUNTRYCODE = 0x00000004,
	GP_MASK_BIRTHDAY    = 0x00000008,
	GP_MASK_SEX         = 0x00000010,
	GP_MASK_ALL         = 0xFFFFFFFF,

	// Status
	/////////
	GP_OFFLINE  = 0,
	GP_ONLINE   = 1,
	GP_PLAYING  = 2,
	GP_STAGING  = 3,
	GP_CHATTING = 4,
	GP_AWAY     = 5,

	// CPU Brand ID
	///////////////
	GP_INTEL = 1,
	GP_AMD,
	GP_CYRIX,
	GP_MOTOROLA,
	GP_ALPHA,

	// Connection ID.
	/////////////////
	GP_MODEM = 1,
	GP_ISDN,
	GP_CABLEMODEM,
	GP_DSL,
	GP_SATELLITE,
	GP_ETHERNET,
	GP_WIRELESS
} GPEnum;

//RESULTS
//////////
typedef enum _GPResult
{
	GP_NO_ERROR,
	GP_MEMORY_ERROR,
	GP_PARAMETER_ERROR,
	GP_NETWORK_ERROR,
	GP_SERVER_ERROR
} GPResult;

//ERROR CODES
/////////////
//#define GP_ERROR_TYPE(errorCode)  ((errorCode) >> 8)
typedef enum _GPErrorCode
{
	// General.
	///////////
	GP_GENERAL = 0x0000,
	GP_PARSE,
	GP_NOT_LOGGED_IN,
	GP_BAD_SESSKEY,
	GP_DATABASE,
	GP_NETWORK,
	GP_FORCED_DISCONNECT,
	GP_CONNECTION_CLOSED,

	// Login.
	/////////
	GP_LOGIN = 0x0100,
	GP_LOGIN_TIMEOUT,
	GP_LOGIN_BAD_NICK,
	GP_LOGIN_BAD_EMAIL,
	GP_LOGIN_BAD_PASSWORD,
	GP_LOGIN_BAD_PROFILE,
	GP_LOGIN_PROFILE_DELETED,
	GP_LOGIN_CONNECTION_FAILED,
	GP_LOGIN_SERVER_AUTH_FAILED,

	// Newuser.
	///////////
	GP_NEWUSER = 0x0200,
	GP_NEWUSER_BAD_NICK,
	GP_NEWUSER_BAD_PASSWORD,

	// Updateui.
	////////////
	GP_UPDATEUI = 0x0300,
	GP_UPDATEUI_BAD_EMAIL,

	// Newprofile.
	//////////////
	GP_NEWPROFILE = 0x0400,
	GP_NEWPROFILE_BAD_NICK,
	GP_NEWPROFILE_BAD_OLD_NICK,

	// Updatepro.
	/////////////
	GP_UPDATEPRO = 0x0500,
	GP_UPDATEPRO_BAD_NICK,

	// Addbuddy.
	////////////
	GP_ADDBUDDY = 0x0600,
	GP_ADDBUDDY_BAD_FROM,
	GP_ADDBUDDY_BAD_NEW,
	GP_ADDBUDDY_ALREADY_BUDDY,

	// Authadd.
	///////////
	GP_AUTHADD = 0x0700,
	GP_AUTHADD_BAD_FROM,
	GP_AUTHADD_BAD_SIG,

	// Status.
	//////////
	GP_STATUS = 0x0800,

	// Bm.
	//////
	GP_BM = 0x0900,
	GP_BM_NOT_BUDDY,

	// Getprofile.
	//////////////
	GP_GETPROFILE = 0x0A00,
	GP_GETPROFILE_BAD_PROFILE,

	// Delbuddy.
	////////////
	GP_DELBUDDY = 0x0B00,
	GP_DELBUDDY_NOT_BUDDY,

	//Delprofile.
	/////////////
	GP_DELPROFILE = 0x0C00,
	GP_DELPROFILE_LAST_PROFILE,

	// Search.
	//////////
	GP_SEARCH = 0x0D00,
	GP_SEARCH_CONNECTION_FAILED
} GPErrorCode;

//STRING LENGTHS
////////////////
#define GP_NICK_LEN                 31
#define GP_FIRSTNAME_LEN            31
#define GP_LASTNAME_LEN             31
#define GP_EMAIL_LEN                51
#define GP_PASSWORD_LEN             31
#define GP_HOMEPAGE_LEN             76
#define GP_ZIPCODE_LEN              11
#define GP_COUNTRYCODE_LEN          3
#define GP_REASON_LEN               1025
#define GP_STATUS_STRING_LEN        256
#define GP_LOCATION_STRING_LEN      256
#define GP_ERROR_STRING_LEN         256

//TYPES
////////
// GPConnection
///////////////
typedef void * GPConnection;

// GPProfile
////////////
typedef int GPProfile;

// GPCallback
/////////////
typedef void (* GPCallback)(
  GPConnection * connection,
  void * arg,
  void * param
);

//STRUCTURES
/////////////
// GPErrorArg
/////////////
typedef struct
{
  GPResult result;
  GPErrorCode errorCode;
  char * errorString;
  GPEnum fatal;
} GPErrorArg;

// GPConnectResponseArg
////////////////////////
typedef struct
{
  GPResult result;
  GPProfile profile;
} GPConnectResponseArg;

// GPNewProfileResponseArg
//////////////////////////
typedef struct
{
  GPResult result;
  GPProfile profile;
} GPNewProfileResponseArg;

// GPProfileSearchMatch
///////////////////////
typedef struct
{
  GPProfile profile;
  char nick[GP_NICK_LEN];
  char firstname[GP_FIRSTNAME_LEN];
  char lastname[GP_LASTNAME_LEN];
  char email[GP_EMAIL_LEN];
} GPProfileSearchMatch;

// GPProfileSearchResponseArg
/////////////////////////////
typedef struct
{
  GPResult result;
  int numMatches;
  GPEnum more;
  GPProfileSearchMatch * matches;
} GPProfileSearchResponseArg;

// GPGetInfoResponseArg
///////////////////////
typedef struct
{
  GPResult result;
  GPProfile profile;
  char nick[GP_NICK_LEN]; 
  char email[GP_EMAIL_LEN]; 
  char firstname[GP_FIRSTNAME_LEN]; 
  char lastname[GP_LASTNAME_LEN]; 
  char homepage[GP_HOMEPAGE_LEN]; 
  int icquin;
  char zipcode[GP_ZIPCODE_LEN]; 
  char countrycode[GP_COUNTRYCODE_LEN]; 
  int birthday;
  int birthmonth;
  int birthyear;
  GPEnum sex;
  GPEnum publicmask;
} GPGetInfoResponseArg;

// GPRecvBuddyRequestArg
////////////////////////
typedef struct
{ 
  GPProfile profile;
  unsigned int date;
  char reason[GP_REASON_LEN];
} GPRecvBuddyRequestArg;

// GPBuddyStatus
////////////////
typedef struct
{ 
  GPProfile profile; 
  GPEnum status;
  char statusString[GP_STATUS_STRING_LEN];
  char locationString[GP_LOCATION_STRING_LEN];
  unsigned int ip; 
  int port;
} GPBuddyStatus;

// GPRecvBuddyStatusArg
///////////////////////
typedef struct
{
  GPProfile profile; 
  unsigned int date;
  int index;
} GPRecvBuddyStatusArg;

// GPRecvBuddyMessageArg
////////////////////////
typedef struct
{ 
  GPProfile profile;
  unsigned int date;
  char * message;
} GPRecvBuddyMessageArg;

// GPIsValidEmailResponseArg
////////////////////////////
typedef struct
{
  GPResult result;
  char email[GP_EMAIL_LEN];
  GPEnum isValid;
} GPIsValidEmailResponseArg;

// GPGetUserNicksResponseArg
////////////////////////////
typedef struct
{
  GPResult result;
  char email[GP_EMAIL_LEN];
  int numNicks;  // If 0, then the nick/password did not match.
  char ** nicks;
} GPGetUserNicksResponseArg;

// GPRecvGameInviteArg
//////////////////////
typedef struct
{
  GPProfile profile;
  int productID;
} GPRecvGameInviteArg;

// GPFindPlayerMatch
////////////////////
typedef struct
{
	GPProfile profile;
	char nick[GP_NICK_LEN];
	char locationString[GP_LOCATION_STRING_LEN];
} GPFindPlayerMatch;

// GPFindPlayersResponseArg
///////////////////////////
typedef struct
{
  GPResult result;
  int productID;  //PANTS|06.06.00 - added by request for JED
  int numMatches;
  GPFindPlayerMatch * matches;
} GPFindPlayersResponseArg;

//FUNCTIONS
////////////
// gpInitialize
///////////////
GPResult gpInitialize
(
  GPConnection * connection
);

// gpDestroy
////////////
void gpDestroy(
  GPConnection * connection
);

// gpEnable
///////////
GPResult gpEnable
(
  GPConnection * connection, 
  GPEnum state
);

// gpDisable
////////////
GPResult gpDisable
(
  GPConnection * connection, 
  GPEnum state
);

// gpProcess
////////////
GPResult gpProcess
(
  GPConnection * connection
);

// gpSetCallback
////////////////
GPResult gpSetCallback
(
  GPConnection * connection,
  GPEnum func,
  GPCallback callback,
  void * param
);

// gpConnect
////////////
GPResult gpConnect
(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  GPEnum firewall,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpConnectNewUser
///////////////////
GPResult gpConnectNewUser
(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  GPEnum firewall,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpDisconnect
///////////////
void gpDisconnect
(
  GPConnection * connection
);

// gpGetErrorCode
/////////////////
GPResult gpGetErrorCode(
  GPConnection * connection,
  GPErrorCode * errorCode
);

// gpGetErrorString
///////////////////
GPResult gpGetErrorString(
  GPConnection * connection,
  char errorString[GP_ERROR_STRING_LEN]
);

// gpNewProfile
///////////////
GPResult gpNewProfile(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  GPEnum replace,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpDeleteProfile
//////////////////
GPResult gpDeleteProfile(
  GPConnection * connection
);

// gpProfileFromID
// PANTS|09.11.00 - A GPProfile is now the same
// as a profileid.  This function is no longer needed
// and will be removed in a future version of GP.
/////////////////////////////////////////////////////
GPResult gpProfileFromID(
  GPConnection * connection, 
  GPProfile * profile, 
  int id
);

// gpIDFromProfile
// PANTS|09.11.00 - A GPProfile is now the same
// as a profileid.  This function is no longer needed
// and will be removed in a future version of GP.
/////////////////////////////////////////////////////
GPResult gpIDFromProfile(
  GPConnection * connection,
  GPProfile profile,
  int * id
);

// gpUserIDFromProfile
//////////////////
GPResult gpUserIDFromProfile(
  GPConnection * connection,
  GPProfile profile,
  int * userid
);

// gpProfileSearch
//////////////////
GPResult gpProfileSearch(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char firstname[GP_FIRSTNAME_LEN],
  const char lastname[GP_LASTNAME_LEN],
  int icquin,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpGetInfo
////////////
GPResult gpGetInfo(
  GPConnection * connection,
  GPProfile profile, 
  GPEnum checkCache,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpSetInfoi
/////////////
GPResult gpSetInfoi(
  GPConnection * connection, 
  GPEnum info, 
  int value
);

// gpSetInfos
/////////////
GPResult gpSetInfos(
  GPConnection * connection,
  GPEnum info,
  const char * value
);

// gpSetInfod
/////////////
GPResult gpSetInfod(
  GPConnection * connection,
  GPEnum info,
  int day,
  int month,
  int year
);

// gpSetInfoMask
////////////////
GPResult gpSetInfoMask(
  GPConnection * connection,
  GPEnum mask
);

// gpSendBuddyRequest
/////////////////////
GPResult gpSendBuddyRequest(
  GPConnection * connection,
  GPProfile profile,
  const char reason[GP_REASON_LEN]
);

// gpAuthBuddyRequest
/////////////////////
GPResult gpAuthBuddyRequest(
  GPConnection * connection,
  GPProfile profile
);

// gpDenyBuddyRequest
// PANTS|09.11.00
/////////////////////
GPResult gpDenyBuddyRequest(
  GPConnection * connection,
  GPProfile profile
);

// gpDeleteBuddy
////////////////
GPResult gpDeleteBuddy(
  GPConnection * connection,
  GPProfile profile
);

// gpGetNumBuddies
//////////////////
GPResult gpGetNumBuddies(
  GPConnection * connection,
  int * numBuddies
);

// gpGetBuddyStatus
///////////////////
GPResult gpGetBuddyStatus(
  GPConnection * connection,
  int index, 
  GPBuddyStatus * status
);

// gpGetBuddyIndex
//////////////////
GPResult gpGetBuddyIndex(
  GPConnection * connection, 
  GPProfile profile, 
  int * index
);

// gpSetStatus
//////////////
GPResult gpSetStatus(
  GPConnection * connection,
  GPEnum status,
  const char statusString[GP_STATUS_STRING_LEN],
  const char locationString[GP_LOCATION_STRING_LEN]
);

// gpSendBuddyMessage
/////////////////////
GPResult gpSendBuddyMessage(
  GPConnection * connection,
  GPProfile profile,
  const char * message
);

// PANTS|02.15.00
// Added gpIsValidEmail and gpGetUserNicks for login wizard.
////////////////////////////////////////////////////////////

// gpIsValidEmail
/////////////////
GPResult gpIsValidEmail(
  GPConnection * connection,
  const char email[GP_EMAIL_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpGetUserNicks
/////////////////
GPResult gpGetUserNicks(
  GPConnection * connection,
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// PANTS|05.10.00
// Added invitable game stuff
/////////////////////////////

// gpSetInvitableGames
//////////////////////
GPResult gpSetInvitableGames(
  GPConnection * connection,
  int numProductIDs,
  int * productIDs
);

// gpFindPlayers
////////////////
GPResult gpFindPlayers(
  GPConnection * connection,
  int productID,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

// gpInvitePlayer
/////////////////
GPResult gpInvitePlayer(
  GPConnection * connection,
  GPProfile profile,
  int productID
);

#ifdef _DEBUG
// gpProfilesReport
// PANTS|09.11.00
///////////////////
void gpProfilesReport(
  GPConnection * connection,
  void (* report)(const char * output)
);
#endif

#ifdef __cplusplus
}
#endif

#endif
