#pragma once
#include "Obj.h"
class CTest :
	public CObj
{

public:
	virtual void update();
	virtual void render(HDC _hdc);
public:
	CTest();
	~CTest();
};

