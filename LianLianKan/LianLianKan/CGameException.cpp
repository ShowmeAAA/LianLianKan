#include "stdafx.h"
#include<iostream>
#include "CGameException.h"


CGameException::CGameException()
{
	//默认异常提示语句
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);	// 申请写
	std::cout << "游戏异常";
	FreeConsole();
}

CGameException::CGameException(const std::string theMessage)
{
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);	// 申请写
	std::cout << theMessage;
	FreeConsole();
}

CGameException::~CGameException()
{
}
