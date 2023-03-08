#include "Game.h"

Game::Game() {
	this->mem = new MemTool();
	this->render = new Render();
	this->tool = new Tool();
	this->showBox = TRUE;
	this->showMenu = TRUE;
	this->aim = TRUE;
	this->aimPos = AIMPOS_RANDOM;
	this->aimScope = 550.0;
	this->aimPawn = 0;
	this->aim幅度 = 40;
	this->aim距离 = 20;
	this->willFuckCode = FALSE;
}

bool Game::FindGameProc() {
	while (true)
	{
		this->render->DrStartDraw();
		this->render->DrDrawStrokeText(100, 500, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 520, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 540, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 560, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 580, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 600, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 620, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 640, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrDrawStrokeText(100, 660, 255, 0, 0, 1, 0, 0, 0, 1, "[踏雪测试版提示：]等待游戏启动中。。。。");
		this->render->DrEndDraw();
		//Sleep(1000);
		this->gameHwnd = FindWindowA("CrossFire", "穿越火线");
	
		if (!this->gameHwnd) 
		{ 
			continue; 
		}
		GetWindowThreadProcessId(this->gameHwnd, &this->pid);
		if (!this->pid) 
		{ 
			continue; 
		}
		return TRUE;
	}
	return FALSE;
}

bool Game::InitBase() {
	const char* mNameArr[] = {
		"cshell_x64.dll",
		"Cshell_x64.dll",
		"CShell_x64.dll",
		"cshell_x64.dll",
		"CSHELL_X64.dll",
		"cshell_x64.DLL",
		"CShell_x64.dll",
		"cshell_X64.dll",
		"CShell_X64.dll",
		"CShell_X64.DLL"
	};
	for (size_t i = 0; i < 10; i++)
	{
		this->cshellBase = this->mem->GetProcModuleBase(this->pid, mNameArr[i]);
		if (this->cshellBase!=0) break;
	}
	if (!this->cshellBase) return FALSE;


	const char* mcfNameArr[] = {
		"crossfire.exe",
		"CrossFire.exe",
		"CrossFire.EXE",
		"CROSSFIRE.EXE"
	};
	for (size_t i = 0; i < 4; i++)
	{
		this->cfbase = this->mem->GetProcModuleBase(this->pid, mcfNameArr[i]);
		if (this->cfbase != 0) break;
	}
	if (!this->cfbase) return FALSE;


	this->gbBoneOff = 10416;//骨骼偏移
	this->gbArrSize = 4144;//数组大小、数据大小
	this->gbSelfBase = 649;//本人地址、本人ID
	this->gbMatrixBase = 5372824912;//矩阵基址


	this->gbModeBase = this->cshellBase+ 43262864 ;//模式基址
	this->gbPlayerArrBase = this->cshellBase + 40742016;//玩家数组
	this->gbPlayerBase = this->mem->ReadQWord(this->pid, this->gbPlayerArrBase) + 152;//人物基址、本人偏移
	this->gbPlayerDataBase = this->mem->ReadQWord(this->pid, this->gbPlayerArrBase) + 656;//人物数据、OBJECT
	this->gbIsGaming = this->gbPlayerBase + 8;//是否游戏
	return TRUE;
}



void Game::InitWindow() {
	POINT p = { 0 };
	RECT winRect = { 0 };
	GetClientRect(this->gameHwnd, &winRect);
	ClientToScreen(this->gameHwnd, &p);
	//if ((GetWindowLongPtrA(this->gameHwnd, -16) & WS_BORDER) == WS_BORDER)
	//{
	//	GetClientRect(this->gameHwnd,&winRect);
	//	ClientToScreen(this->gameHwnd, &p);
	//}
	//else
	//{
	//	GetWindowRect(this->gameHwnd,&winRect);
	//}
	winRect.left = p.x;
	winRect.top = p.y;

	this->gameLeft = winRect.left;
	this->gameTop = winRect.top;
	this->weight = winRect.right;
	this->hight = winRect.bottom;
	this->centerX = this->weight / 2;
	this->centerY = this->hight / 2;
}

DWORD Thread_KeyWatch(PVOID param) {
	Game* g = (Game*)param;
	while (true)
	{
		if ((GetAsyncKeyState(VK_HOME) & 1) > 0)
		{
			g->showMenu = !g->showMenu;
		}
		else if ((GetAsyncKeyState(VK_F2) & 1) > 0)
		{
			g->showBox = !g->showBox;
		}
		else if ((GetAsyncKeyState(VK_F3) & 1) > 0)
		{
			//g->willFuckCode = TRUE;
			DWORD selfP = g->GetSelfPos();
			g->FuckCode(selfP);
		}
		else if ((GetAsyncKeyState(VK_ADD) & 1) > 0)
		{
			g->aimScope += 10;
		}
		else if ((GetAsyncKeyState(VK_SUBTRACT) & 1) > 0)
		{
			g->aimScope -= 10;
		}
	}

}


void Game::KeysWatch() {

	CreateThread(NULL, NULL, Thread_KeyWatch, this, NULL, NULL);
}


void Game::StartDraw() {
	while (IsWindow(this->gameHwnd))
	{
		this->InitWindow();
		this->render->DrStartDraw();

		if (this->showMenu) { this->DrawMenu(); }

		this->DrawBox();

		//瞄准范围指示器
		//this->render->DrDrawBoxEx(this->gameLeft + this->weight / 2 - this->aimScope / 2, this->gameTop + this->hight / 2 - this->aimScope / 2, this->aimScope,this->aimScope,0,255,0,1.0,5);

		this->render->DrEndDraw();
	}
}


void Game::DrawMenu() {
	this->render->DrDrawStrokeText(this->gameLeft + 50, this->gameTop + 200 + 230, 0 ,0, 255, 1,255 ,245 ,238 ,1, "[踏雪内部透追 V1.0]\0");
	if (this->showBox)
	{ 
		this->render->DrDrawStrokeText(this->gameLeft + 50, this->gameTop + 200 + 250, 0, 0, 255, 1, 255, 245, 238, 1, "F2-显示方框      [开启]\0" );
	}
	else
	{
		this->render->DrDrawStrokeText(this->gameLeft + 50, this->gameTop + 200 + 250, 0, 0, 255, 1, 255, 245, 238, 1, "F2-显示方框      [关闭]\0");
	}

	this->render->DrDrawStrokeText(this->gameLeft + 50, this->gameTop + 200 + 270, 0, 0, 255, 1, 255, 245, 238, 1, "F3-敌方掉线\0");

	this->render->DrDrawStrokeText(this->gameLeft + 50, this->gameTop + 200 + 290, 0, 0, 255, 1, 255, 245, 238, 1, "HOME 显示隐藏菜单  END 安全退出\0");
}

DWORD Game::GetPlayerNum() {
	DWORD gameMode = this->mem->ReadDWord(this->pid, this->gbModeBase);
	if (gameMode == 11 || gameMode == 24 || gameMode == 31)
	{
		return 0;
	}
	else if (gameMode == 15)
	{
		return 5;
	}
	else if (gameMode == 5 || gameMode == 12 || gameMode == 14 || gameMode == 17 || gameMode == 41 || gameMode == 47)
	{
		return 15;
	}
	else if (gameMode == 4 || gameMode == 36)
	{
		return 16;
	}
	else
	{
		return 8;
	}
}

DWORD Game::GetSelfPos() {
	ULONG64 t1 = this->mem->ReadQWord(this->pid, this->gbPlayerArrBase);
	ULONG64 t2 = this->mem->ReadQWord(this->pid, t1 + this->gbSelfBase);
	return t2 + 1;
}

void Game::GetSelfRect(POS* r) {
	ULONG64 playerLevel1 = 0;
	ULONG64 t1 = this->mem->ReadQWord(this->pid, this->gbPlayerArrBase);
	playerLevel1 = this->mem->ReadQWord(this->pid, t1 + 72);
	
	r->x = this->mem->ReadFloat(this->pid, playerLevel1 + 160);
	r->z = this->mem->ReadFloat(this->pid, playerLevel1 + 164);
	r->y = this->mem->ReadFloat(this->pid, playerLevel1 + 168);
}

DWORD Game::GetPlayerHp(int r) {
	return this->mem->ReadDWord(this->pid, (r - 1) * this->gbArrSize + (this->gbPlayerDataBase + 68));
}

BOOLEAN Game::GetBonePos(int i, POS* r, int bone) {
	ULONG64 enemyBase = this->mem->ReadQWord(this->pid, (i - 1) * this->gbArrSize + this->gbPlayerDataBase);
	if (enemyBase > 0)
	{
		ULONG64 t1 = this->mem->ReadQWord(this->pid, enemyBase + this->gbBoneOff);
		if (t1 != 0)
		{
			t1 = t1 + 64 * bone + 12;
			r->x = this->mem->ReadFloat(this->pid, t1);
			r->z = this->mem->ReadFloat(this->pid, t1+16);
			r->y = this->mem->ReadFloat(this->pid, t1+32);
			return TRUE;
		}
	}
	return FALSE;
}

BOOLEAN Game::WorldToScreen(POS* in, POS* out) {
	POS playerPos = { 0 };
	playerPos.x = in->x;
	playerPos.y = in->z;
	playerPos.z = in->y;
	ULONG64 ss = this->gbMatrixBase;

	char view[64] = { 0 };
	this->mem->ReadArr(this->pid,ss-128,&view[0],64);

	char projection[64] = { 0 };
	this->mem->ReadArr(this->pid, ss - 64, &projection[0], 64);

	char viewPort[64] = { 0 };
	this->mem->ReadArr(this->pid, ss, &viewPort[0], 64);

	char World[] = {
		0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		, 0, 0, 0, 0, 128, 63 
	};
	
	POS vScreen = { 0 };
	D3DXVec3Project((D3DXVECTOR3*)&vScreen,(D3DXVECTOR3*)&playerPos,(CONST D3DVIEWPORT9*)&viewPort[0],
		(CONST D3DXMATRIX*)&projection[0],
		(CONST D3DXMATRIX*)&view[0],(CONST D3DXMATRIX*)&World[0]);
	if (vScreen.z > 1)
	{
		return FALSE;
	}
	out->x = vScreen.x;
	out->y = vScreen.y;
	return TRUE;
}

void Game::VectorToRotation(POS* pos, POS* enemyPos, POS* ret) {
	double PI = 3.1415926535;
	double 坐标Y差 = enemyPos->y - pos->y;
	double 坐标X差 = enemyPos->x - pos->x;
	double 坐标Z差 = enemyPos->z - pos->z + 10;
	double RADPI = 180.0 / PI;
	if (坐标X差<0)
	{
		ret->x = -1 * (atan(坐标Y差 / 坐标X差) * RADPI + 270);
	}
	else {
		ret->x = -1 * (atan(坐标Y差 / 坐标X差) * RADPI + 90);
	}
	ret->y = -1 * (atan(坐标Z差 / (sqrt(坐标X差 * 坐标X差 + 坐标Y差 * 坐标Y差))) * RADPI);
	//POS* enemyPos1 = enemyPos;
	//double Xchaju = pos->x * -1 - enemyPos1->x * -1;
	//double Ychaju = pos->y - enemyPos1->y;
	//double Zchaju = pos->z - enemyPos1->z - 24;
	//double Xjiaodu = 0.0;
	//double Yjiaodu = 0.0;
	//double duibian = 0.0;
	//double linbian = 0.0;
	//double PI = 3.1415926535;
	//if (Xchaju == 0 && Ychaju < 0) { Xjiaodu = 0; }
	//else if (Xchaju == 0 && Ychaju > 0) { Xjiaodu = 180.0; }
	//else if (Xchaju > 0 && Ychaju == 90) { Xjiaodu = 90.0; }
	//else if (Xchaju < 0 && Ychaju == 0) { Xjiaodu = 270.0; }
	//else if (Xchaju > 0 && Ychaju < 0) { duibian = Ychaju; linbian = Xchaju; Xjiaodu = atan(duibian / linbian) * 180 / PI + 90; }
	//else if (Xchaju < 0 && Ychaju < 0) { duibian = Xchaju; linbian = Ychaju; Xjiaodu = 360 - atan(duibian / linbian) * 180 / PI; }
	//else if (Xchaju > 0 && Ychaju > 0) { duibian = Ychaju; linbian = Xchaju; Xjiaodu = atan(duibian / linbian) * 180.0 / PI + 90.0; }
	//else if (Xchaju < 0 && Ychaju > 0) { duibian = Xchaju; linbian = Ychaju; Xjiaodu = 180 - atan(duibian / linbian) * 180.0 / PI; }
	//else { Xjiaodu = 0; }
	//Yjiaodu = atan(Zchaju / sqrt(Ychaju * Ychaju + Xchaju * Xchaju)) * 180 / PI;
	//ret->x = Xjiaodu * PI / 180;
	//ret->y = Yjiaodu * PI / 180;
	//ret->z = 0.0;
}


void Game::DrawBox() {
	DWORD playerNum = this->GetPlayerNum();
	DWORD selfPosition = this->GetSelfPos();
	DWORD isPolice = selfPosition <= 8 ? 0 : 1;

	POS meRect = { 0 };
	this->GetSelfRect(&meRect);



	for (int i = 1; i <= 29; i++)
	{
		BOOLEAN needDraw = FALSE;

		if (i == selfPosition) { continue; }

		if (playerNum == 8)
		{
			if ((isPolice ? (i+1- isPolice)<=8 : ((i + 1 - isPolice) > 9)))
			{
				needDraw = TRUE;
			}
			else
			{
				needDraw = FALSE;
			}
		}
		else if (playerNum == 16) { needDraw = TRUE; }
		else if (playerNum == 29) { needDraw = TRUE; }
		else if (playerNum == 15) { needDraw = TRUE; }
		
		POS enemyBone = { 0 };
		POS foot = { 0 };
		POS head = { 0 };
		POS chaju = { 0 };
		DWORD retFar = 0;
		DWORD h = 0;
		DWORD w = 0;
		float x = 0;
		float y = 0;
		if (this->GetPlayerHp(i)>0 && this->GetBonePos(i,&enemyBone,0))
		{
			enemyBone.z = enemyBone.z - 140;
			if (this->WorldToScreen(&enemyBone,&foot) && this->GetBonePos(i,&enemyBone,6))
			{
				enemyBone.z = enemyBone.z + 40;
				if (this->WorldToScreen(&enemyBone,&head))
				{
					h = foot.y - head.y;
					w = h / 2;
					x = head.x - h / 4;
					y = head.y;
					chaju.x = meRect.x * -1 - enemyBone.x * -1;
					chaju.y = meRect.y - enemyBone.y;
					chaju.z = meRect.z - enemyBone.z;
					retFar = sqrt(chaju.x * chaju.x + chaju.y * chaju.y + chaju.z * chaju.z) / 100;

					if (needDraw)
					{
						if (this->showBox)
						{
							render->DrDrawBoxEx(this->gameLeft + x,
								this->gameTop + y,
								w, h, 0, 255, 0, 1, 3);

							DWORD hp = this->GetPlayerHp(i);
							char hpTxt[500] = { 0 };
							sprintf(hpTxt, "HP剩余: %d", hp);
							render->DrDrawStrokeText(this->gameLeft + x, this->gameTop + y - 30, 255, 0, 255, 1, 245, 255, 250, 1, hpTxt);
						}
					}
				}
			}
		}
	}
}


bool Game::FuckCode(int index) {
	char code1[] = {
		0x50,0x53,0x51,0x52,0x55,0x56,0x57,
		0x41,0x50,
		0x41,0x51,
		0x41,0x52,
		0x41,0x53,
		0x41,0x54,
		0x41,0x55,
		0x41,0x56,
		0x41,0x57,
		0x9C,


		0x48,0x83,0xEC,0x38,						//sub rsp,38
		0x48,0x83,0xCC,0x08,						//or rsp, 8
		0x48,0xB9,0,0,0,0,0,0,0,0,					//mov rcx,cshell_x64.dll+26DA460   ★
		//0x48,0x8B,0x09,								//mov rcx,[rcx]
		0x48,0x8B,0x01,								//mov rax,[rcx]
		0x48,0x8D,0x54,0x24,0x24,					//lea rdx,[rsp+24]
		0xFF,0x50,0x48,								//call qword ptr [rax+48]
		0x48,0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48,0x8B,0x01,								//mov rax,[rcx]
		0xFF,0x50,0x08,								//call qword ptr [rax+08]
		0x48,0xB9,0,0,0,0,0,0,0,0,					//mov rcx,cshell_x64.dll+26DAC99	★
		0x0F,0xB6,0x11,								//movzx edx,byte ptr [rcx]
		0x8B, 0xDA,									//mov ebx,edx
		0x48, 0xC1,0xE3,0x04,						//shl rbx,04
		0x8D, 0x42,0x01,							//lea eax,[rdx+01]
		0x88, 0x01,									//mov [rcx],al
		0x8B, 0xC2,									//mov eax,edx
		0x48, 0xC1,0xE8,0x04 ,						//shr rax,04
		0x48, 0x09,0xC3,							//or rbx,rax
		0x48, 0x8B,0x4C,0x24,0x24 ,					//mov rcx,[rsp+24]
		0xBA, 0xA1,0x00,0x00,0x00,					//mov edx,000000A1
		0x41, 0xB8,0x10,0x00,0x00,0x00,				//mov r8d,00000010
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0xBA, 0xF7,0xD5,0x7A,0xB2,					//mov edx,B27AD5F7
		0x41, 0xB8,0x05,0x00,0x00,0x00,				//mov r8d,00000005
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48, 0x8B,0xD3,							//mov rdx,rbx
		0x41, 0xB8,0x08,0x00,0x00,0x00,				//mov r8d,00000008 
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0xBA, 0x02,0x00,0x00,0x00,					//mov edx,00000002		敌人编号 
		0x41, 0xB8,0x08,0x00,0x00,0x00,				//mov r8d,00000008 
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0xBA, 0x01,0x00,0x00,0x00,					//mov edx,00000001 
		0x41, 0xB8,0x08,0x00,0x00,0x00,				//mov r8d,00000008 
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0xBA, 0x01,0x00,0x00,0x00,					//mov edx,00000001 
		0x41, 0xB8,0x08,0x00,0x00,0x00,				//mov r8d,00000008
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0xBA, 0x64,0x00,0x00,0x00,					//mov edx,00000064
		0x41, 0xB8,0x10,0x00,0x00,0x00,				//mov r8d,00000010
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x40,							//call qword ptr [rax+40]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48, 0x8B,0xD0,							//mov rdx,rax
		0x48, 0x0F,0xAF,0xD3,						//imul rdx,rbx
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0x41, 0xB8,0x08,0x00,0x00,0x00,				//mov r8d,00000008
		0xFF, 0x50,0x48,							//call qword ptr [rax+48]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x38,							//call qword ptr [rax+38]
		0x48,0xB9,0,0,0,0,0,0,0,0,					//mov rcx,cshell_x64.dll+26DAC88   ★
		//0x48,0x8B,0x09,								//mov rcx,[rcx]
		0x48, 0x8B,0xD0,							//mov rdx,rax
		0x41, 0xB8,0x01,0x00,0x00,0x00,				//mov r8d,00000001
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x90,0x00,0x04,0x00,0x00,				//call qword ptr [rax+00000400]
		0x48, 0x8B,0x4C,0x24,0x24,					//mov rcx,[rsp+24]
		0x48, 0x8B,0x01,							//mov rax,[rcx]
		0xFF, 0x50,0x10,							//call qword ptr [rax+10]
		0x48,0x83,0xE4,0xF8,						//and rsp, FFFFFFFFFFFFFFF0
		0x48, 0x83,0xC4,0x38,						//add rsp,38 

		0x9D,
		0x41,0x5F,
		0x41,0x5E,
		0x41,0x5D,
		0x41,0x5C,
		0x41,0x5B,
		0x41,0x5A,
		0x41,0x59,
		0x41,0x58,
		0x5F,0x5E,0x5D,0x5A,0x59,0x5B,0x58
		//0xC3                   						//ret 
	};
	//*(PULONG64)(&code[6 + 24]) = this->cshellBase + 0x26DA460;
	*(PULONG64)(&code1[6 + 24 + 4]) = this->cfbase + 0x3B9078;
	*(PULONG64)(&code1[41 + 24 - 3 + 4]) = this->cshellBase + 0x26DAC99;
	*(PULONG64)(&code1[272 + 24 - 3 + 4]) = this->cfbase + 0x3B8410;

	PUCHAR code = (PUCHAR)VirtualAlloc(0, sizeof(code1) * 20*8, MEM_COMMIT, PAGE_READWRITE);
	DWORD startI = 0;
	if (index<8)
	{
		startI = 8;
	}
	for (int j = 0; j < 8; j++)
	{
		*(PULONG32)(&code1[142 + 24 - 3 + 4]) = startI+j;
		for (int i = 0; i < 20; i++)
		{
			memcpy(code + sizeof(code1) * (i + j * 20), code1, sizeof(code1));
		}
	}
	this->mem->FarCall(this->pid, (PUCHAR)code, sizeof(code1) * 20 * 8);
	Sleep(1000);
	VirtualFree(code, sizeof(code1) * 20 * 8, MEM_FREE);
	return TRUE;
}