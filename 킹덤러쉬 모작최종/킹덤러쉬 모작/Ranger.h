#pragma once
#include "Unit.h"
class CRanger :
	public CUnit
{
private:
	UNIT_DIRECTION e_mArrowDir;

public:
	virtual void update();
	virtual void OnCollision(CCollider* _other);
	virtual void Attack(CUnit * _Other);

public:
	CRanger();
	virtual ~CRanger();
};

