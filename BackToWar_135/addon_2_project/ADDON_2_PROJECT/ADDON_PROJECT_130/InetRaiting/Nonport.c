/******
nonport.c
GameSpy Developer SDK 
  
Copyright 1999 GameSpy Industries, Inc

Suite E-204
2900 Bristol Street
Costa Mesa, CA 92626
(714)549-7689
Fax(714)549-0757

******/
#include "nonport.h"



#ifdef __cplusplus
extern "C" {
#endif


#ifdef UNDER_CE
time_t time(time_t *timer)
{
	static time_t ret;
	SYSTEMTIME systime;
	FILETIME ftime;
	LONGLONG holder;

	GetLocalTime(&systime);
	SystemTimeToFileTime(&systime, &ftime);
	holder = (ftime.dwHighDateTime << 32) + ftime.dwLowDateTime;
	if (timer == NULL)
		timer = &ret;
	*timer = (time_t)((holder - 116444736000000000) / 10000000);
	return *timer; 
}

int isdigit( int c )
{
	return (c >= '0' && c <= '9');
}

int isxdigit( int c )
{
	return ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
}

int isalnum( int c )
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}


#endif

#ifdef __KATANA__
/*
631152000 -- diff b/t 1950 & 1970 GMT
631126800 -- diff b/t 1950 GMT & 1970 PDT
*/
time_t time(time_t *timer)
{
	static time_t ret;
	SYS_RTC_DATE date;
	Uint32 count;
	syRtcGetDate(&date);
	syRtcDateToCount(&date, &count);
	if (timer == NULL)
		timer = & ret;
	*timer = (time_t)(count - 631152000);	
}

#endif

#ifdef __mips64
unsigned long goa_frame_ct = 0;

#endif

unsigned long current_time()  //returns current time in msec
{ 
#ifdef _WIN32
	return (GetTickCount()); 
#endif
#ifdef _MACOS
	return (TickCount() * 50) / 3;
#endif
#ifdef __KATANA__
	return (syTmrCountToMicro(syTmrGetCount()))/1000;
#endif
#ifdef __mips64
	/*struct SysClock mc;
	int sec, int usec;
	GetSystemTime(&mc);
	SysClock2USec(&mc, sec, usec);
	return (sec * 1000 + usec / 1000);*/
//	return 0;//MUSTFIX
//	return clock();
//	return time(NULL)*1000;
	return goa_frame_ct * 1000 / 60;
	//return goa_frame_ct += 100;
#endif
#ifdef UNDER_UNIX
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
#endif
}

#ifdef __KATANA__
extern void DrawScreen(void);
#endif

void msleep(unsigned long msec)
{
#ifdef _WIN32
	Sleep(msec);
#endif
#ifdef __KATANA__
	//wait for the approx msec based on vertical refreshes
	unsigned long stoptime = current_time() + msec;
	do
	{
		//vsWaitVSync(1);
		njWaitVSync();
		DrawScreen();
	} while (current_time() < stoptime);
#endif
#ifdef _MACOS
//	EventRecord rec;
	WaitNextEvent(everyEvent,/*&rec*/NULL, (msec*1000)/60, NULL);
#endif
#ifdef __mips64
	sn_delay(msec);
#endif
#ifdef UNDER_UNIX
	usleep(msec * 1000);
#endif
}

void SocketStartUp()
{
#if defined(_WIN32) || defined(_MACOS)
	WSADATA data;
	WSAStartup(0x0101, &data);
#endif


}

void SocketShutDown()
{
#if defined(_WIN32) || defined(_MACOS)
	WSACleanup();
#endif

}

#if defined(_WIN32) && !defined(UNDER_CE)
//do nothign
#else
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char *_strdup(const char *src)
{
	char *res;
	if(src == NULL)      //PANTS|02.11.00|check for NULL before strlen
		return NULL;
	res = (char *)malloc(strlen(src) + 1);
	if(res != NULL)      //PANTS|02.02.00|check for NULL before strcpy
		strcpy(res, src);
	return res;
}

char *_strlwr(char *string)
{
	char *hold = string;
	while (*string)
	{
		*string = tolower(*string);
		string++;
	}

	return hold;
}
char *_strupr(char *string)
{
	char *hold = string;
	while (*string)
	{
		*string = toupper(*string);
		string++;
	}

	return hold;
}
#endif

int SetSockBlocking(SOCKET sock, int isblocking)
{
#ifdef __KATANA__
	#ifdef KGTRN_ACCESS
		short   argp;
	#endif
	#ifdef KGTRN_PLANET_WEB
		long argp;
	#endif
	#ifdef KGTRN_NEXGEN
		int argp;
	#endif
#else
	unsigned long argp;
#endif
	int rcode; 
	
	if (isblocking)
		argp = 0;
	else
		argp = 1;
#ifdef __KATANA__

	#ifdef KGTRN_ACCESS
		rcode = setsockopt(sock, SOL_SOCKET, SO_NOBLK,(char *)&argp, sizeof(argp));
	#endif
	#ifdef KGTRN_PLANET_WEB
		if ( (argp = net_fcntl( sock, F_GETFL, 0)) < 0 )
			return -1;
		if (isblocking)
			argp &= ~O_NONBLOCK;	
		else
			argp |= O_NONBLOCK;	
		rcode = net_fcntl( sock, F_SETFL, argp );
	#endif
	#ifdef KGTRN_NEXGEN
		if ( (argp = fcntlsocket( sock, F_GETFL, 0)) < 0 )
			return -1;
		if (isblocking)
			argp &= ~O_NONBLOCK;	
		else
			argp |= O_NONBLOCK;	
		rcode = fcntlsocket( sock, F_SETFL, argp );		
	#endif
#else
	#ifdef __mips64
		rcode = setsockopt(sock, SOL_SOCKET, (isblocking) ? SO_BIO : SO_NBIO, &argp, sizeof(argp));
	#else
		rcode = ioctlsocket(sock, FIONBIO, &argp);
	#endif
#endif
	if (rcode == 0)
		return 1;
	else
		return 0;
}



#if defined(_MACOS) || defined(UNDER_CE) || defined(__KATANA__)
int strcasecmp(const char *string1, const char *string2)
{
	while (tolower(*string1) == tolower(*string2) && *string1 != 0 && *string2 != 0)
	{
		*string1++; *string2++;
	}
	return tolower(*string1) - tolower(*string2);
}

int strncasecmp(const char *string1, const char *string2, size_t count)
{
	while (--count > 0 && tolower(*string1) == tolower(*string2) && *string1 != 0 && *string2 != 0)
	{
		*string1++; *string2++;
	}
	return tolower(*string1) - tolower(*string2);
}
#endif

#ifdef __KATANA__

#ifndef __GNUC__
void abort(void)
{
	//called by assert on dreamcast but not present
	//could do a hardware break in here if needed	
	
}
#endif

unsigned long fixed_inet_addr (const char * cp)
{
	int idata[4];
	unsigned char data[4];
	int pc = 0;
	char *pos;
	
	//validate the IP
	for (pos = (char *)cp ; *pos != 0; pos++)
	{
		if( (*pos < '0' || *pos > '9') && *pos != '.')
			return INADDR_NONE;
		if (*pos == '.')
			pc++; //increment the period counter
	}
	if (pc != 3)
		return INADDR_NONE; //not enough periods
		
	sscanf(cp, "%d.%d.%d.%d", idata, idata+1,idata+2,idata+3);
	data[0] = (unsigned char)idata[0]; data[1] = (unsigned char)idata[1]; data[2] = (unsigned char)idata[2]; data[3] = (unsigned char)idata[3];
	return *(unsigned long *)data;
}


void *grealloc(void *ptr, int newlen)
{
	return realloc(ptr,newlen);
	/*void *outptr;
	if (ptr == NULL &&  newlen == 0)
		return NULL;
	if (ptr == NULL)
		return malloc(newlen);
	if (newlen == 0)
	{
		free(ptr);
		return NULL;		
	}	
	outptr = malloc(newlen);
	if (!outptr)
		return NULL;
	//note: this is NOT optimal, since we may copy more than we need to
	memcpy(outptr, ptr, newlen);
	return outptr;	*/
}

#ifdef KGTRN_PLANET_WEB

#define MAX_HOST_ADDRS 16
struct hostent *pwgethostbyname(const char *name)
{
	static char *aliases = NULL;
	static struct in_addr *paddrs[MAX_HOST_ADDRS];
	static struct hostent hent;
	int i;
	int err;
	static struct addrinfo *ai = NULL;
	struct addrinfo *curai = NULL;
	
	if (ai != NULL)
		freeaddrinfo(ai);
	ai = NULL;
	err = getaddrinfo(name, NULL, NULL, &ai);
	if (err != 0 || ai == NULL)
	{
		return NULL;
	}
	hent.h_name = ai->ai_canonname;
	hent.h_aliases = &aliases;
	hent.h_addrtype = 2;
	hent.h_length = 4;
	
	for (i = 0, curai = ai ; i < MAX_HOST_ADDRS - 1, curai != NULL ; i++, curai = curai->ai_next)
		paddrs[i] = &((struct sockaddr_in *)curai->ai_addr)->sin_addr;
	paddrs[i] = NULL;
	hent.h_addr_list = (char **)paddrs;
	 
	return &hent;
}

#endif //PWEB

 
#endif //KATANA

#ifdef __mips64
void GOAClearSocketError(SOCKET s)
{
	int val;
	int soval = sizeof(val);
	getsockopt(s,SOL_SOCKET,SO_ERROR,&val,&soval);
}

#endif
#ifdef __cplusplus
}
#endif
