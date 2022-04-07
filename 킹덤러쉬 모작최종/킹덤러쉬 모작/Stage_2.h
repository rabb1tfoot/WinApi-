#pragma once
#include "CStage_Field.h"
class CStage_2 :
	public CStage_Field
{
private:
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
	CStage_2();
	virtual ~CStage_2();
};

