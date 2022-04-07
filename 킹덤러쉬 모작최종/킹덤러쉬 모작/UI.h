#pragma once
#include "Obj.h"

class CUI :
	public CObj
{
protected:
	CUI * m_pParentUI;
	vector<CUI*> m_vecChildUI;
	Vec2 m_vFinalPos;
	bool m_bButtonDown;
	bool m_bLayer;

public:
	virtual void update();
	virtual void render(HDC _hdc);

public:
	virtual void MouseOff();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseLbtnDown(Vec2 _vMousePos) { m_bButtonDown = true; };
	virtual void MouseLbtnUp(Vec2 _vMousePos) {};
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void MouseLbtnOther(Vec2 _vMousePos) {};

	virtual void MouseRbtnClicked(Vec2 _vMousePos) {};
	virtual void MouseRbtnUp(Vec2 _vMousePos) {};

public:
	void SetLayer(bool _layer) { m_bLayer = _layer; }
	void SetFinalPos(Vec2 _pos) { m_vFinalPos = _pos; }
	void SetParent(CUI* _parent) { m_pParentUI = _parent; }
	virtual bool IsOn(Vec2 _vCoordinate);
	bool IsMouseLbtnDown() { return m_bButtonDown; }
	void AddChild(CUI* _pChildUI);
	Vec2 GetFinalPos() { return m_vFinalPos; }
	vector<CUI*>& GetChild() { return m_vecChildUI; }
	CUI* GetParent() { return m_pParentUI; }
	bool GetLayer() { return m_bLayer; }

public:
	CUI();
	CUI(Vec2 _vPos);
	virtual ~CUI();

	friend class CUIMgr;
};

