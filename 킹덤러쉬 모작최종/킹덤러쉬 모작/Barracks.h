#pragma once
#include "Building.h"

class CSoldier;

class CBarracks :
	public CBuilding
{
private:
	bool					m_bClicked;
	CSoldier*				m_arrMySoldier[3];
	CTexture*				m_pSelectTex;
	CObj*					m_cMovePoint;
	bool					m_bspawning[3];
	float					m_fAccSpawn[3];
	int						m_SelectSpawn;
	POINT					m_pmousepos;
	Vec2					m_vMousePos;
	Vec2					m_vBoundary;
	bool					m_bMoveCommand;

private:
	void CreateSoldier(int _tier, int _amount = 0, int _number = -1);

public:
	void Init();
	void CreateMovePoint();
	void SetmySoldierDead(int _num) { m_arrMySoldier[_num] = nullptr; }

public:
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void UpgradeBuild(int _tier);

public:
	CBarracks();
	virtual ~CBarracks();
};

