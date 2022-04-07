#pragma once
#include "UI.h"
class CSelect_Quit :
	public CUI
{
private:
	bool m_bMouseAttach;
public:
	CSelect_Quit();
	virtual ~CSelect_Quit();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

