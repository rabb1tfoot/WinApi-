#pragma once
#include "Stage.h"

class CWave;

class CStage_Field :
	public CStage
{
protected:
	vector<Vec2> m_vRoute;
	CWave* m_myWave;

public:
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void Enter();
	virtual void Exit();

protected:
	virtual void InitHud();
	virtual void InitRoute();
	virtual void Init();
	virtual void LoadingTex();

public:
	CStage_Field();
	virtual ~CStage_Field();
};

