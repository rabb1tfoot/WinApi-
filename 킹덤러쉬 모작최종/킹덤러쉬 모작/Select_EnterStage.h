#pragma once
#include "UI.h"
class CSelect_EnterStage :
	public CUI
{
private:
	bool m_bIsClear;
	int  m_iStageNum;

public:
	void SetStageNum(int _num) { m_iStageNum = _num; }
	void SetClear(bool _clear) { m_bIsClear = _clear; }
	bool GetClear() { return m_bIsClear; }
	void Init();

public:
	CSelect_EnterStage();
	virtual ~CSelect_EnterStage();
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

