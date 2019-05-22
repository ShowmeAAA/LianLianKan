#include "stdafx.h"
#include<iostream>
#include "CGameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//初始化游戏二维数组m_pGameMap
void CGameControl::StartGame()
{
	m_pGameMap = m_GameLogic.InitMap();
}

//根据地图坐标返回是哪一种水果（亦即哪一张图片）
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];
}