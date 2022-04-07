#pragma once
#include "Obj.h"

class CCollider;
class CObj_Coll;
class CHero;

class CUnit :
	public CObj
{
private:
	tUnitInfo		m_tInfo;
	ATTACK_TYPE		m_eAttType;
	UNIT_STATE		m_eState;
	UNIT_DIRECTION	m_eDir[(UINT)DIRECITON_MODE::END];
	CObj_Coll*		m_Coll;
	CObj*			m_CTarget;
	int				m_iTier;

protected:
	vector<Vec2>	m_vMoveRoute;
	UINT			m_currentRoute;
	float			m_fAttTime;
	bool			m_bframeEnter;
	bool			m_bMoving;

protected:
	vector<Vec2> GetRoute() { return m_vMoveRoute; }
	UINT GetRouteSize() { return m_currentRoute; }

public:
	virtual void Attack(CUnit* _Other);
	virtual void Attack(CHero* _Other);
	virtual void Move() {};
	virtual void Move(Vec2) {};

public:
	bool GetMoving() { return m_bMoving; }
	void SetMoving(bool _moving) { m_bMoving = _moving; }
	void SetTarget(CObj* _target) { m_CTarget = _target; }
	void SetTier(int _tier) { m_iTier = _tier; }
	void SetObjColl(CObj_Coll* _coll) { m_Coll = _coll; }
	CObj_Coll* GetObjColl() { return m_Coll; }
	void SetDirNomal(UNIT_DIRECTION _enomal = UNIT_DIRECTION::BOTTOM) 
	{ m_eDir[UINT(DIRECITON_MODE::DIR_NOMAL)] = _enomal;}
	void SetDirAtt(UNIT_DIRECTION _attck = UNIT_DIRECTION::RIGHT)
	{m_eDir[UINT(DIRECITON_MODE::DIR_ATTACK)] = _attck;}
	void SetInfo(tUnitInfo _info) { m_tInfo = _info; }
	void SetAttType(ATTACK_TYPE _type) { m_eAttType = _type; }
	void SetState(UNIT_STATE _state) { m_eState = _state; }
	void SetAttTime(float _time) { m_fAttTime = _time; }
	CObj* GetTarget() { return m_CTarget; }
	float GetAttTime() { return m_fAttTime; }
	int GetTier() { return m_iTier; }

	UNIT_DIRECTION GetDirNomal() { return m_eDir[(UINT)DIRECITON_MODE::DIR_NOMAL]; }
	UNIT_DIRECTION GetDirAtt() { return m_eDir[(UINT)DIRECITON_MODE::DIR_ATTACK]; }
	tUnitInfo& GetInfo() { return m_tInfo; }
	ATTACK_TYPE GetAttType() { return m_eAttType; }
	UNIT_STATE GetState() { return m_eState; }
	int GetPow() { return m_tInfo.iAtt_pow; }

public:
	virtual void update();
	virtual void render(HDC _hdc);

public:
	CUnit();
	virtual ~CUnit();

	friend class CObj_Coll;
};

