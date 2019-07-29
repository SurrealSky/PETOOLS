#pragma once

//------- ERROR --------
#define MemErr					1
#define PEErr					2
#define FileErr					3
#define NoRoom4SectionErr		4
#define FsizeErr				5
#define SecNumErr				6
#define IIDErr					7
#define FileISProtect			8
#define PEnotValid				9
#define PEisCOMRuntime			10
#define DLLnotSupport			11
#define WDMnotSupport			12
#define TServernotSupport		13
#define SYSnotSupport			14
#define NOSEHnotSupport			15
#define NOBINDnotSupport		16
#define PackSectionName			17

void ShowErr(unsigned char numErr);