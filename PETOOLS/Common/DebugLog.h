#pragma once



//
//NOTICE
//
#define Dbg


void DebugLog(LPCSTR lpOutputString);

void DebugLog(LPCSTR lpTag, LPCSTR lpOutputString);

void DebugLogHex(LPCSTR lpTag, LPCSTR lpOutputString,DWORD lpOutputStringLen);