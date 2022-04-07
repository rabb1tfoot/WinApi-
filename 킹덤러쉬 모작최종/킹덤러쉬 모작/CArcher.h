#pragma once
#include "Building.h"

class CRanger;

class CArcher :
	public CBuilding
{
private:
	CTexture *  m_pSelectTex;
	CRanger*	m_cMyRanger[2];
private:
	void CreateRangers(int _tier);

public:
	void Init();

public:
	CArcher();
	virtual ~CArcher();
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void UpgradeBuild(int _tier);
};

