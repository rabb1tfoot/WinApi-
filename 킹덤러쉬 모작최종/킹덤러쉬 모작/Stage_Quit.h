#pragma once
#include "UI.h"
class CStage_Quit :
	public CUI
{
private:
	bool m_bOption;

public:
	bool GetOptionState() { return m_bOption; }
	void SetOptionState(bool _state) { m_bOption = _state; }

public:
	CStage_Quit();
	virtual ~CStage_Quit();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

