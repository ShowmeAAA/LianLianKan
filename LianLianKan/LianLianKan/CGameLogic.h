#pragma once
#include"CGameException.h"
#include<string>

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	int** InitMap(); //��ʼ����Ϸ��ͼ
	void ReleaseMap(int** &pGameMap); //�ͷŵ�ͼ
};

