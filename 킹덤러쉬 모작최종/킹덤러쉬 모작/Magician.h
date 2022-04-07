#pragma once
#include "Unit.h"

class CMage;

class CMagician :
	public CUnit
{
private:
	CMage * m_cMage;

public:
	void SetBuild(CMage* _build);
	virtual void update();
	virtual void OnCollision(CCollider* _other);
	virtual void Attack(CUnit * _Other);
public:
	CMagician();
	virtual ~CMagician();
};

