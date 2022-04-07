#pragma once
#include "Stage.h"
class CStage_Title :
	public CStage
{
public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
	virtual void render(HDC _hdc);
public:
	CStage_Title();
	virtual ~CStage_Title();
};

