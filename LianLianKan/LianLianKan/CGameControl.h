#pragma once
#include"CGameLogic.h"
class CGameControl
{
private:
						//核心数据结构！！！
	int** m_pGameMap = 0;   //游戏地图二维整形数组
						//m_pGameMap[x][y]表示地图中该位置放的是几号水果
						//水果总共有8种，所有它的取值应为1-8
	
	
	CGameLogic m_GameLogic;                        //游戏逻辑操作对象

public:
	static const int s_nRows = 10;                 //游戏行数
	static const int s_nCols = 16;                 //游戏列数
	static const int s_nPicNum = 10;                //图片数

	CGameControl();
	~CGameControl();

	void StartGame();					//开始游戏
	int GetElement(int nRow, int nCol); //得到某一个元素
};

