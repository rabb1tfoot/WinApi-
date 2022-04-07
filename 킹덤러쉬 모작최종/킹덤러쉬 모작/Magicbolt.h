#pragma once
#include "Obj.h"

class CUnit;
class Collider;

class CMagicbolt :
	public CObj
{
private:
	CUnit * m_ctarget;
	int m_ipow;

public:
	virtual void update();
	virtual void Init(int _pow);
	virtual void OnCollision(CCollider* _other);

public:
	CMagicbolt();
	CMagicbolt(Vec2 _pos, CUnit * _Other);
	virtual ~CMagicbolt();
};

