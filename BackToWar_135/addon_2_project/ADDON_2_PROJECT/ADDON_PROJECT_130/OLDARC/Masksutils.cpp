// © 2000 by ManOwaR

//#include "stdafx.h"
//#include "MasksUtils.h"

#include <stdio.h>
#include "GSCtypes.h"
#include "GSCarch.h"
#include "GSCset.h"
#include "MasksUtils.h"

BOOL MatchesMask(LPCSTR lpcsFileName, LPCSTR lpcsMask)
{
	
	if(strlen(lpcsMask)>strlen(lpcsFileName))
		return FALSE;

	CHAR lpsLeftMask[64];
	CHAR lpsRightMask[64];
	CHAR lpsLeftName[64];
	CHAR lpsRightName[64];
	CHAR lpsMidName[64];
	
	LPSTR lpsDelim=strpbrk(lpcsMask,"*");

	if(lpsDelim)
	{
		ZeroMemory(lpsLeftMask,64);
		ZeroMemory(lpsRightMask,64);
		ZeroMemory(lpsLeftName,64);
		ZeroMemory(lpsRightName,64);
		ZeroMemory(lpsMidName,64);

		strncpy(lpsLeftMask,lpcsMask,lpsDelim-lpcsMask);
		strcpy(lpsRightMask,lpsDelim+1);

		strncpy(lpsLeftName,lpcsFileName,strlen(lpsLeftMask));

		strcpy(lpsRightName,lpcsFileName+(strlen(lpcsFileName)-strlen(lpsRightMask)));

		strncpy(lpsMidName,lpcsFileName+strlen(lpsLeftMask),strlen(lpcsFileName)-strlen(lpsLeftName)-strlen(lpsRightName));

		if(strchr(lpsMidName,'\\'))
			return FALSE;

		if((!strcmp(_strupr(lpsLeftMask),_strupr(lpsLeftName))) &&
			(!strcmp(_strupr(lpsRightMask),_strupr(lpsRightName))))
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		strcpy(lpsLeftMask,lpcsFileName);
		strcpy(lpsRightMask,lpcsMask);

		if(!strcmp(_strupr(lpsLeftMask),_strupr(lpsRightMask)))
			return TRUE;
		else
			return FALSE;
	};
}