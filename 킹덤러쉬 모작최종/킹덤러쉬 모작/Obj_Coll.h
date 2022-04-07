#pragma once
#include "Obj.h"
class CObj_Coll :
	public CObj
{
private:
	CObj * m_Owner;

public:
	void SetOwner(CObj* _obj) { m_Owner = _obj; }
	CObj* GetOwner() { return m_Owner; }

public:
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void OnCollision(CCollider * _other);
	virtual void OnCollisionEnter(CCollider* _other);
	CObj_Coll();
	virtual ~CObj_Coll();

};

