#pragma once
#include "Unit.h"

class CBarracks;

class CSoldier :
	public CUnit
{
private:
	CBarracks * m_cParentBuild;
	int			m_number;
	Vec2		m_vMovingPos;

public:
	Vec2 GetMovingPos() { return m_vMovingPos; }
	void SetBuild(CBarracks* _parrent) { m_cParentBuild = _parrent; };
	CBarracks * GetBuild() { return m_cParentBuild; }
	void SetNumber(int _number) { m_number = _number; }
	int GetNumber() { return m_number; }

public:
	virtual void update();
	virtual void Move(Vec2 _vPos, int i=0);
	virtual void OnCollision(CCollider* _other);

public:
	CSoldier();
	~CSoldier();
};

