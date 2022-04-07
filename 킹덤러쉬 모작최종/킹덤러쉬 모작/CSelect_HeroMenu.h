#pragma once
#include "UI.h"
class CSelect_HeroMenu :
	public CUI
{
private:
	bool  m_bMouseAttach;
	bool  m_bCreated;
	CObj* m_pPanel;
	CUI*  m_pResume;
	CObj*  m_check;

	CUI* m_HeroFace[HERO_TYPE::HERO_END];

private:
	void CreateSubMenu();

public:
	CObj * GetCheck() { return m_check; }
	CObj*   GetPanel() { return m_pPanel; }
	CUI*    GetResume() { return m_pResume; }
	CUI**   GetHeroFace() { return m_HeroFace; }

	virtual void update();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);

public:
	CSelect_HeroMenu();
	virtual ~CSelect_HeroMenu();
};

