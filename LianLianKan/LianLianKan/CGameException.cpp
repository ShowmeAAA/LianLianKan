#include "stdafx.h"
#include<iostream>
#include "CGameException.h"


CGameException::CGameException()
{
	//Ĭ���쳣��ʾ���
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);	// ����д
	std::cout << "��Ϸ�쳣";
	FreeConsole();
}

CGameException::CGameException(const std::string theMessage)
{
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);	// ����д
	std::cout << theMessage;
	FreeConsole();
}

CGameException::~CGameException()
{
}
