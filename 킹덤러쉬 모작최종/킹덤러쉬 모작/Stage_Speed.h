#pragma once
#include "UI.h"
class CStage_Speed :
	public CUI
{
private:
	bool m_bDouble;

public:
	CStage_Speed();
	virtual ~CStage_Speed();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

