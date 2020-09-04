#pragma once
#include<Windows.h>
#include<typedef.h>
using namespace SurrealTypes;

class PER
{
public:
	PER(void);
	~PER(void);
public:
	//PER
	void InitRandom();
	static void _ror(DWORD *Value,UCHAR Shift);
	static void _rol(DWORD *Value,UCHAR Shift);
	DWORD random(DWORD dwRange);
	UCHAR EncodeRoutine(UCHAR Value,UCHAR Count);
	void EncryptBuff(STu8* Base,DWORD dwRV,DWORD Size);
	void MakePER(STu8* pDecryptBuff,DWORD dwSize);
	void MyMakePER(STu8 *pDecryptBuff,DWORD dwSize);
	void MyEasyEncrypt(STu8* pDecryptBuff,DWORD dwSize);
};