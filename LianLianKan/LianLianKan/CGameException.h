#pragma once
#include<string>

class CGameException
{

public:
	CGameException();
	~CGameException();
	CGameException(const std::string theMessage);

};

