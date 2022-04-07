#pragma once
#include "UI.h"
class CTitle_StartUI :
	public CUI
{
private:
	bool m_bMouseAttach;

public:
	CTitle_StartUI();
	virtual ~CTitle_StartUI();
public:
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

