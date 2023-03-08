#pragma once
#include "MemTool.h"


ULONG64 MemTool::GetProcModuleBase(DWORD pid, const char* mName) {
	ULONG64 base = 0;
	LONG ret = Api_GetModuleBase(pid,(char*)mName,&base);
	return base;
}

LONG64 MemTool::ReadQWord(DWORD pid, ULONG64 base) {
	LONG64 val = 0;
	Api_ReadProcMemory(pid,base,(ULONG64)&val,8,0);
	return val;
}
float MemTool::ReadFloat(DWORD pid, ULONG64 base) {
	DWORD val = 0;
	Api_ReadProcMemory(pid, base, (ULONG64)&val, 4, 0);
	float t = *(float*)(&val);
	return t;
}
DWORD MemTool::ReadDWord(DWORD pid, ULONG64 base) {
	DWORD val = 0;
	Api_ReadProcMemory(pid, base, (ULONG64)&val, 4, 0);
	return val;
}
UWORD MemTool::ReadWWord(DWORD pid, ULONG64 base) {
	UWORD val = 0;
	Api_ReadProcMemory(pid, base, (ULONG64)&val, 2, 0);
	return val;
}
UCHAR MemTool::ReadByte(DWORD pid, ULONG64 base) {
	UCHAR val = 0;
	Api_ReadProcMemory(pid, base, (ULONG64)&val, 1, 0);
	return val;
}
void MemTool::ReadArr(DWORD pid, ULONG64 dst, PVOID arr, ULONG64 size) {
	Api_ReadProcMemory(pid,dst,(ULONG64)arr,size,0);
}
void MemTool::WriteDword(DWORD pid, ULONG64 base, DWORD data) {
	DWORD buf = data;
	LONG ret = Api_WriteProcMemory(pid,base,(ULONG64)&buf,4,0);
}
void MemTool::WriteFloat(DWORD pid, ULONG64 base,float val) {
	float val1 = val;
	LONG ret = Api_WriteProcMemory(pid, base, (ULONG64)&val1, 4, 0);
}

void MemTool::WriteArr(DWORD pid, ULONG64 base, PVOID arr,ULONG64 size) {
	Api_WriteProcMemory(pid, base, (ULONG64)arr, size, 0);
}


BOOLEAN MemTool::FarCall(DWORD pid, PUCHAR code,ULONG64 size) {
	LONG ret = Api_RemoteCall(pid,0,1,(ULONG64)code,size);
	if (!ret)
	{
		return TRUE;
	}
	else
	{
		char arr[500] = { 0 };
		sprintf(arr,"remote call error: %llx",ret);
		MessageBoxA(0,arr,"error",1);
		return FALSE;
	}
}