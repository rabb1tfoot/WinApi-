#pragma once
#include "UI.h"
class CBlock :
	public CUI
{
public:
	CBlock();
	virtual ~CBlock();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

