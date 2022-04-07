#pragma once
#include "Obj.h"

class CUnit;
class CCollider;

class CBomb :
	public CObj
{
private:
	CUnit *		m_cTarget;
	int			m_iPow;
	CCollider*	m_cBoundary;

public:
	virtual void update();
	virtual void Init(int _pow);
	virtual void OnCollision(CCollider* _other);

public:
	CBomb();
	CBomb(Vec2 _pos, CUnit* _Other);
	virtual ~CBomb();
};

