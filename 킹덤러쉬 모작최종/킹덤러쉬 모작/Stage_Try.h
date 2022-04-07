#pragma once
#include "UI.h"
class CStage_Try :
	public CUI
{
public:
	CStage_Try();
	virtual ~CStage_Try();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

