#pragma once
#include "Unit.h"

class CCannon;

class CCannonBound :
	public CUnit
{
private:
	float m_fPow;
private:
	CCannon * m_cCannon;
public:
	void SetPow(float _pow) { m_fPow = _pow; }
	void SetBuild(CCannon* _build) { m_cCannon = _build; }
	virtual void update();
	virtual void OnCollision(CCollider* _other);
	virtual void Attack(CUnit * _Other);

public:
	CCannonBound();
	virtual ~CCannonBound();
};

