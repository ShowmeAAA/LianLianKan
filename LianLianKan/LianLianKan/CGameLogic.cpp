#include "stdafx.h"
#include "CGameLogic.h"
#include"CGameControl.h"
#include<iostream>

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

//Ϊ��Ϸ��ͼ��ά���鿪���ڴ�������1-8���������ʼ����
//��ΪCGameControl::s_nPicNumΪ8����ֻ��8��ˮ���������������Χ��1-8
//���һ���֤��ÿ��ˮ���ĳ��ִ���һ��
int** CGameLogic::InitMap()
{
	// ��ȡ��ͼ��С���м�����ˮ��
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

    //Ϊ��Ϸ��ͼ��ά���鿪���ڴ�����
	int** pGameMap = new int*[nRows];
	if (NULL == pGameMap)
	{
		throw new CGameException("�ڴ�����쳣��\n");
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = new int[nCols];
			if (NULL == pGameMap)
			{
				throw new CGameException("�ڴ�����쳣��\n");
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}

	//���ݻ�ɫ����������ÿ�ֻ�ɫ��ͼƬ��ƽ�����������θ���Ϸ��ͼ��ά���鸳ֵ��
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw new CGameException("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ�䣡");
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		// �ظ���
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}


	// ����ҵ�����λ�õ�ͼƬ�����н���	srand((int)time(NULL));	
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// ����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// ����������ֵ
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] 
					= pGameMap[nIndex2 /nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
	return pGameMap;
}


//�ͷ���Ϸ��ͼ��ά������ռ���ڴ�ռ�
void CGameLogic::ReleaseMap(int** &pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}