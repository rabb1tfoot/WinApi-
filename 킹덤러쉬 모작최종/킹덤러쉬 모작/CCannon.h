#pragma once
#include "Building.h"

class CCollider;
class CUnit;

class CCannon :
	public CBuilding
{
private:
	CTexture * m_pSelectTex;
	tUnitInfo		m_tInfo;
	CUnit*		m_cBound;
	float m_fAttTime;

public:
	int GetPow() { return m_tInfo.iAtt_pow; }
	tUnitInfo GetInfo() { return m_tInfo; }
	void SetInfo(tUnitInfo& _info) { m_tInfo = _info; }
	void Init();


public:
	CCannon();
	virtual ~CCannon();
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void UpgradeBuild(int _tier);
};

