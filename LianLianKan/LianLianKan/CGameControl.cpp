#include "stdafx.h"
#include<iostream>
#include "CGameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

//��ʼ����Ϸ��ά����m_pGameMap
void CGameControl::StartGame()
{
	m_pGameMap = m_GameLogic.InitMap();
}

//���ݵ�ͼ���귵������һ��ˮ�����༴��һ��ͼƬ��
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];
}