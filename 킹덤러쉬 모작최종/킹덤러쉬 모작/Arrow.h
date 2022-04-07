#pragma once
#include "Obj.h"

class CUnit;

class CArrow :
	public CObj
{
private:
	CUnit *		m_ctarget;
	int			m_iPow;

public:
	virtual void update();
	virtual void Init(int _pow, UNIT_DIRECTION _eDir);
	virtual void OnCollision(CCollider* _other);

public:
	CArrow();
	CArrow(Vec2 _pos, CUnit * _Other);
	virtual ~CArrow();
};

