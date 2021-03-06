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

//为游戏地图二维数组开辟内存区域并用1-8的随机数初始化它
//因为CGameControl::s_nPicNum为8，即只有8种水果，所以随机数范围是1-8
//而且还保证了每种水果的出现次数一样
int** CGameLogic::InitMap()
{
	// 获取地图大小和有几多种水果
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

    //为游戏地图二维数组开辟内存区域
	int** pGameMap = new int*[nRows];
	if (NULL == pGameMap)
	{
		throw new CGameException("内存操作异常！\n");
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = new int[nCols];
			if (NULL == pGameMap)
			{
				throw new CGameException("内存操作异常！\n");
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}

	//根据花色的种类计算出每种花色的图片的平均个数，依次给游戏地图二维数组赋值。
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw new CGameException("游戏花色与游戏地图大小不匹配！");
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		// 重复数
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}


	// 随机找到两个位置的图片，进行交换	srand((int)time(NULL));	
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] 
					= pGameMap[nIndex2 /nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
	return pGameMap;
}


//释放游戏地图二维数组所占的内存空间
void CGameLogic::ReleaseMap(int** &pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}