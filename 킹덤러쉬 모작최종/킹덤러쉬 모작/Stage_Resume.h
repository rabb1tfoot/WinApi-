#pragma once
#include "UI.h"

class CStage_Pause;

class CStage_Resume :
	public CUI
{
private:
	bool m_bMouseAttach;
	CStage_Pause* m_pParentMenu;

public:
	void SetParnet(CStage_Pause* _menu) { m_pParentMenu = _menu; }

public:
	CStage_Resume();
	virtual ~CStage_Resume();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

