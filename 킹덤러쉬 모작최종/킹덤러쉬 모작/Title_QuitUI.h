#pragma once
#include "UI.h"
class CTitle_QuitUI :
	public CUI
{
private:
	bool m_bMouseAttach;
public:
	CTitle_QuitUI();
	virtual ~CTitle_QuitUI();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

