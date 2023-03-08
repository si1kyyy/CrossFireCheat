#pragma once
#include "global.hpp"
#include "MemTool.h"
#include "Render.h"
#include "Tool.h"


class Game
{
public:
	MemTool* mem;
	Render* render;
	Tool* tool;

	DWORD pid;  //游戏进程ID
	HWND gameHwnd;

	ULONG64 cshellBase;
	ULONG64 cfbase;
	ULONG64 acePbcBase;

	ULONG64 gbBoneOff;
	ULONG64 gbArrSize;
	ULONG64 gbSelfBase;
	ULONG64 gbMatrixBase;
	ULONG64 gbModeBase;
	ULONG64 gbPlayerArrBase;
	ULONG64 gbPlayerBase;
	ULONG64 gbPlayerDataBase;
	ULONG64 gbIsGaming;

	ULONG64 gbAimAddr1;
	ULONG64 gbAimAddr2;
	ULONG64 gbAimAddr3;
	ULONG64 gbAimAddr4;
	ULONG64 gbAimAddr5;
	ULONG64 gbAimAddr6;
	ULONG64 gbAimAddr7;
	ULONG64 gbAimAddr8;


	LONG gameLeft;
	LONG gameTop;
	LONG weight;
	LONG hight;
	LONG centerX;
	LONG centerY;
	

	void DrawMenu();
	void DrawBox();

	DWORD GetPlayerNum();
	DWORD GetSelfPos();
	void GetSelfRect(POS* r);
	DWORD GetPlayerHp(int r);
	BOOLEAN GetBonePos(int i,POS* r,int bone);
	BOOLEAN WorldToScreen(POS* in, POS* out);
	void VectorToRotation(POS* pos, POS* enemyPos, POS* ret);
	void CalcPos(POS* pos);

public:
	BOOLEAN showMenu;
	BOOLEAN showBox;
	BOOLEAN willFuckCode;
	BOOLEAN aim;
	BOOLEAN 后座抵消;
	LONG aimPos;
	float aimScope;

	int aim幅度;
	int aim距离;

	LONG aimPawn;
	LONG lastJuli;

	Game();
	bool FindGameProc();
	bool InitBase();
	bool InitBulletTrace(LONG start,LONG HookJmp,LONG type,BOOLEAN enable);
	void InitWindow();
	void KeysWatch();
	void StartDraw();
	bool FuckCode(int index);
};

