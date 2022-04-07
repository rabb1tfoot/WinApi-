#pragma once
#include "UI.h"
class CStage_Pause :
	public CUI
{
private:
	bool m_bCreated;
	CObj* m_pPanel;
	CUI*  m_pResume;
	CUI*  m_pQuit;

private:
	void CreateSubMenu();

public:
	CObj * GetPanel() { return m_pPanel; }
	CUI*  GetResume() { return m_pResume; }
	CUI*  GetQuit() { return m_pQuit; }

public:
	CStage_Pause();
	virtual ~CStage_Pause();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

