#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include <math.h>
#include <tchar.h>

#pragma comment(lib,"Dll1.lib")
EXTERN_C LONG WINAPI Api_GetModuleBase(ULONG64 pid, char* name, PULONG64 base);
EXTERN_C LONG WINAPI Api_ReadProcMemory(ULONG64 pid, ULONG64 dst, ULONG64 buf, ULONG64 len, ULONG64 way);
EXTERN_C LONG WINAPI Api_WriteProcMemory(ULONG64 pid, ULONG64 dst, ULONG64 buf, ULONG64 len, ULONG64 way);
EXTERN_C LONG WINAPI Api_LoadDriver();
EXTERN_C LONG WINAPI Api_HideProcessByPid(ULONG64 pid, ULONG64 dstpid, ULONG64 needClearObj);
EXTERN_C LONG WINAPI Api_DeleteFileForce(char* path);
EXTERN_C LONG WINAPI Api_RemoteCall(ULONG64 pid, ULONG64 tid, ULONG64 mode, ULONG64 shellcode, ULONG64 len);


LONG WINAPI Api_DwmDrInit();
BOOL WINAPI Api_DwmDrStartDraw();
void WINAPI Api_DwmDrEndDraw();
void WINAPI Api_DwmDrDrawBox(float X, float Y, float W, float H, float R, float G, float B, float A, int T);
void WINAPI Api_DwmDrDrawLine(float X1, float Y1, float X2, float Y2, float R, float G, float B, float A, int T);
void WINAPI Api_DwmDrDrawString(float X, float Y, float R, float G, float B, float A, const char* text);
void WINAPI Api_DwmDrDrawCircle(float X, float Y, float radius, float R, float G, float B, float A, int num_segments, float W);
void WINAPI Api_DwmDrDrawStrokeText(float X, float Y, float R, float G, float B, float A, float R1, float G1, float B1, float A1, const char* text);
void WINAPI Api_DwmDrDrawCornerframe(float x, float y, float w, float h, float R, float G, float B, float A, int T);


typedef struct _POS {
	float x;
	float y;
	float z;
}POS,*PPOS;

#define AIMPOS_HEAD 6
#define AIMPOS_RANDOM 0


