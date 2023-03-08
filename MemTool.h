#pragma once
#include "global.hpp"


class MemTool
{



public:
	ULONG64 GetProcModuleBase(DWORD pid, const char* mName);
	LONG64 ReadQWord(DWORD pid, ULONG64 base);
	DWORD ReadDWord(DWORD pid, ULONG64 base);
	float ReadFloat(DWORD pid, ULONG64 base);
	UWORD ReadWWord(DWORD pid, ULONG64 base);
	UCHAR ReadByte(DWORD pid, ULONG64 base);
	void ReadArr(DWORD pid, ULONG64 dst, PVOID arr, ULONG64 size);

	void WriteDword(DWORD pid, ULONG64 base, DWORD data);
	void WriteFloat(DWORD pid, ULONG64 base, float val);
	void WriteArr(DWORD pid, ULONG64 base, PVOID arr, ULONG64 size);
	BOOLEAN FarCall(DWORD pid, PUCHAR code, ULONG64 size);
};

