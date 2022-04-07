#pragma once
#include "UI.h"

class CBuildMenu :
	public CUI
{
private:
	CTexture * m_pSelectTex;
	BUILD_SELETE m_eSelete;
	bool m_bClicked;
	bool m_bMouseon;

public:
	void SetSelectTex(CTexture* _ptex) { m_pSelectTex = _ptex; }
	void SetSelectType(BUILD_SELETE _etpye) { m_eSelete = _etpye; }
public:
	virtual void render(HDC _hdc);

	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);

public:
	CBuildMenu();
	virtual ~CBuildMenu();
};

