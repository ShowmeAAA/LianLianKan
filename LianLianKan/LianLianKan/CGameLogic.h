#pragma once
#include"CGameException.h"
#include<string>

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	int** InitMap(); //初始化游戏地图
	void ReleaseMap(int** &pGameMap); //释放地图
};

