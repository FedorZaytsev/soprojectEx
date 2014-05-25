/*
*	S.T.A.L.K.E.R. Online - logging
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <Windows.h>
#include <stdarg.h>
#include <time.h>

#include "log.h"

void (_cdecl * Msg)(char const *, ...);

CLog::CLog(char* filename)
{
	 fopen_s(&LogFile,filename,"a");
	 Msg = reinterpret_cast<void (_cdecl *)(char const *, ...)>(GetProcAddress(GetModuleHandle(L"xrCore.dll"),"?Msg@@YAXPBDZZ"));
}

CLog::~CLog(void)
{
	if(LogFile) 
	{
		fclose(LogFile);
		delete LogFile;
	}
}

void CLog::Write(const char *string, ...)
{
	if(!LogFile) return;
	// arg list save
	va_list arglist;
	va_start(arglist, string);
	// timestamp
#if defined TIMESTAMP
	time_t now;
	tm tm;
	time(&now);
	localtime_s(&tm,&now);
	fprintf(LogFile,"[%02d:%02d:%02d] ",tm.tm_hour,tm.tm_min,tm.tm_sec);
#endif
	// build string
	vsprintf_s(temp,256,string,arglist);
	// log
	fputs(temp,LogFile);
	if(Msg) Msg(temp);
	// next line
	fprintf(LogFile, "\n");
	fflush(LogFile);
	// arg list null
	va_end(arglist);
}