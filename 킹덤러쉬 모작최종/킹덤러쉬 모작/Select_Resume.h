#pragma once
#include "UI.h"

class CSelect_Menu;
class CSelect_HeroMenu;

class CSelect_Resume :
	public CUI
{
private:
	bool m_bMouseAttach;
	CSelect_Menu* m_pParentMenu;
	CSelect_HeroMenu* m_pParentMenu2;

public:
	void SetParnet(CSelect_Menu* _menu) { m_pParentMenu = _menu; }
	void SetParnet(CSelect_HeroMenu* _menu) { m_pParentMenu2 = _menu; }

public:
	CSelect_Resume();
	virtual ~CSelect_Resume();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

