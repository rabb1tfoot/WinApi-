#pragma once
#include "UI.h"

class CSelect_HeroMenu;

class CHeroFace_None :
	public CUI
{
private:
	CSelect_HeroMenu * m_ParentMenu;
public:
	void SetParentMenu(CSelect_HeroMenu* _menu) { m_ParentMenu = _menu; }
public:
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void MouseOn(Vec2 _vMousePos) {};
	virtual void MouseOff() {};
public:
	CHeroFace_None();
	virtual ~CHeroFace_None();
};

