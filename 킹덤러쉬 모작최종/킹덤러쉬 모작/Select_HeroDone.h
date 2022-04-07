#pragma once
#include "UI.h"
class CSelect_HeroDone :
	public CUI
{
private:
	bool m_bMouseAttach;
public:
	CSelect_HeroDone();
	virtual ~CSelect_HeroDone();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

