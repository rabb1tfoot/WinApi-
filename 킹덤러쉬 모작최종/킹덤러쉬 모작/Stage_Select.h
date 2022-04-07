#pragma once
#include "Stage.h"
class CStage_Select :
	public CStage
{
private:
	int m_iMaxStage;

private:
	void CreateSelectStageUI();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void update();
	virtual void render(HDC _hdc);
public:
	CStage_Select();
	virtual ~CStage_Select();
};

