#pragma once
#include"CGameLogic.h"
class CGameControl
{
private:
						//�������ݽṹ������
	int** m_pGameMap = 0;   //��Ϸ��ͼ��ά��������
						//m_pGameMap[x][y]��ʾ��ͼ�и�λ�÷ŵ��Ǽ���ˮ��
						//ˮ���ܹ���8�֣���������ȡֵӦΪ1-8
	
	
	CGameLogic m_GameLogic;                        //��Ϸ�߼���������

public:
	static const int s_nRows = 10;                 //��Ϸ����
	static const int s_nCols = 16;                 //��Ϸ����
	static const int s_nPicNum = 10;                //ͼƬ��

	CGameControl();
	~CGameControl();

	void StartGame();					//��ʼ��Ϸ
	int GetElement(int nRow, int nCol); //�õ�ĳһ��Ԫ��
};

