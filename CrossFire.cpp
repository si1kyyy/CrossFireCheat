
#pragma once
#include "global.hpp"
#include "Game.h"

Game* game = NULL;





int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	game = new Game();
	
	LONG ret = Api_LoadDriver();
	if (ret != 0x66666666)
	{
		game->tool->Log( "驱动加载失败！", ret);
		return -1;
	}

	ret = Api_DwmDrInit();
	if (ret!=0 && ret != 0xF3000002)
	{
		game->tool->Log( "绘制加载失败！", ret);
		return -1;
	}

	game->KeysWatch();
	game->tool->Log( "加载成功！请登陆游戏，游戏请事先设置无边框模式，否则绘制将失效！", 0);
	CHAR* selfPath = game->tool->GetSelfPhyPath();
	ret = Api_DeleteFileForce(selfPath);
	ret = Api_HideProcessByPid(GetCurrentProcessId(), 0, TRUE);
	if (!game->FindGameProc())
	{
		game->tool->Log( "检测到游戏已启动，但获取游戏进程失败！请以管理员身份运行！", 1);
		return -1;
	}
	
	if (!game->InitBase())
	{
		game->tool->Log( "初始化游戏数据失败！", 2);
		return -1;
	}
	
	game->InitWindow();
	
	game->StartDraw();

	return 0;
}
