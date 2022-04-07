#pragma once
#include "UI.h"

class CUnit;

class CHero :
	public CUI
{
private:
	UNIT_STATE		m_eState;
	CObj*			m_CTarget;
	tUnitInfo		m_tInfo;
	CObj*			m_cMovePoint;
	POINT			m_pmousepos;
	Vec2			m_vMousePos;
	bool			m_bClick;

protected:
	bool			m_bMoving;
	HERO_TYPE		m_eType;

public:
	void SetType(HERO_TYPE _etype) { m_eType = _etype; }
	void SetMoving(bool _move) { m_bMoving = _move; }
	void SetInfo(tUnitInfo _info) { m_tInfo = _info; }
	tUnitInfo& GetInfo() { return m_tInfo; }
	void SetTarget(CObj* _target) { m_CTarget = _target; }
	UNIT_STATE GetState() { return m_eState; }
	void SetState(UNIT_STATE _etype) { m_eState = _etype; }
	CObj* GetTarget() { return m_CTarget; }

public:
	virtual void update();
	virtual void Move(Vec2 _vPos) {};
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);

private:
	void CreateMovePoint();

public:
	CHero();
	virtual ~CHero();
};

