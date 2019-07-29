#pragma once
#include<Windows.h>

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
	void EncryptBuff(char* Base,DWORD dwRV,DWORD Size);
	void MakePER(char* pDecryptBuff,DWORD dwSize);
	void MyMakePER(char *pDecryptBuff,DWORD dwSize);
	void MyEasyEncrypt(char* pDecryptBuff,DWORD dwSize);
};