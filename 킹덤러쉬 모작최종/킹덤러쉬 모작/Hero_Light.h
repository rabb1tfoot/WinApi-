#pragma once
#include "Hero.h"

class CCollider;
class CObj_Coll;
class CUnit;

class CHero_Light :
	public CHero
{
private:
	UNIT_DIRECTION	m_eDir[(UINT)DIRECITON_MODE::END];
	CObj_Coll*		m_Coll;
	float			m_fAttTime;
	bool			m_bframeEnter;
	Vec2			m_vMovingPos;

public:
	virtual void Attack(CUnit* _Other);
	virtual void Move(Vec2 _vPos);

public:
	void SetObjColl(CObj_Coll* _coll) { m_Coll = _coll; }
	CObj_Coll* GetObjColl() { return m_Coll; }
	void SetDirNomal(UNIT_DIRECTION _enomal = UNIT_DIRECTION::BOTTOM)
	{
		m_eDir[UINT(DIRECITON_MODE::DIR_NOMAL)] = _enomal;
	}
	void SetDirAtt(UNIT_DIRECTION _attck = UNIT_DIRECTION::RIGHT)
	{
		m_eDir[UINT(DIRECITON_MODE::DIR_ATTACK)] = _attck;
	}
	void SetAttTime(float _time) { m_fAttTime = _time; }
	float GetAttTime() { return m_fAttTime; }

	UNIT_DIRECTION GetDirNomal() { return m_eDir[(UINT)DIRECITON_MODE::DIR_NOMAL]; }
	UNIT_DIRECTION GetDirAtt() { return m_eDir[(UINT)DIRECITON_MODE::DIR_ATTACK]; }

public:
	virtual void update();
	virtual void OnCollision(CCollider* _other);

public:
	CHero_Light();
	virtual ~CHero_Light();
};

