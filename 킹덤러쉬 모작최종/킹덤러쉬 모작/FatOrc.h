#pragma once
#include "Unit.h"
class CFatOrc :
	public CUnit
{
public:
	void SetRoute(vector<Vec2>& _route) { m_vMoveRoute = _route; }
	virtual void update();
	virtual void Move();
	virtual void Move(Vec2 _vPos);
	virtual void OnCollision(CCollider* _other);
	CFatOrc();
	virtual ~CFatOrc();
};

