#include "stdafx.h"
#include "Bandit.h"
#include "Animator.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animation.h"
#include "Obj_coll.h"
#include "MapMgr.h"
#include "Hero.h"
#include "SoundMgr.h"


CBandit::CBandit()
	: CUnit()
{
}


CBandit::~CBandit()
{
	if (nullptr != GetTarget())
	{
		((CUnit*)GetTarget())->SetState(UNIT_STATE::IDLE);
		((CUnit*)GetTarget())->SetTarget(nullptr);
	}
	m_vMoveRoute.clear();
}


void CBandit::update()
{
	GetCollider()->update();
	//체력이 다하면 죽음처리
	if (GetInfo().iCurHealth < 0)
	{
		this->SetDead();
		//효과음 생성
		CSoundMgr::GetInst()->LoadSound(L"Sound_Dead.wav", L"Sound_Dead.wav");
		CSoundMgr::GetInst()->Play(L"Sound_Dead.wav");
		//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
		CSoundMgr::GetInst()->SetBGMVolume(100);
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() + 10);
		((CUnit*)this)->GetObjColl()->SetDead();
		CObj* myTarget = GetTarget();
		///상대방이 살아있다면 전투후 상태와 타깃값을 초기화한다.
		if (nullptr != myTarget)
		{
			if (OBJ_TYPE::ALLY_UNIT == myTarget->GetObjType())
			{

				((CUnit*)myTarget)->SetState(UNIT_STATE::IDLE);
				((CUnit*)myTarget)->SetTarget(nullptr);
				((CUnit*)myTarget)->SetMoving(false);
			}
			else if (OBJ_TYPE::ALLY_HERO == myTarget->GetObjType())
			{
				((CHero*)myTarget)->SetState(UNIT_STATE::IDLE);
				((CHero*)myTarget)->SetTarget(nullptr);
				((CHero*)myTarget)->SetMoving(false);
			}
		}
		return;
	}
	if (UNIT_STATE::ATTACK == GetState())
		return;
	//목표에 도착했으므로 목숨를 깍는다.
	if (m_currentRoute == m_vMoveRoute.size())
	{
		//효과음 생성
		CSoundMgr::GetInst()->LoadSound(L"Sound_Life.wav", L"Sound_Life.wav");
		CSoundMgr::GetInst()->Play(L"Sound_Life.wav");
		//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
		CSoundMgr::GetInst()->SetBGMVolume(100);

		this->SetDead();
		((CUnit*)this)->GetObjColl()->SetDead();
		CMapMgr::GetInst()->SetLife(CMapMgr::GetInst()->GetLife() - 1);
		return;
	}

	if (UNIT_STATE::TRACKING == this->GetState())
		return;
	Move();

	if ((int(m_vMoveRoute[m_currentRoute].x - 1) < GetPos().x && int(m_vMoveRoute[m_currentRoute].x + 1) > GetPos().x)
		&& (int(m_vMoveRoute[m_currentRoute].y - 1) < GetPos().y && int(m_vMoveRoute[m_currentRoute].y + 1) > GetPos().y))
	{
		m_currentRoute++;
	}
}

void CBandit::Move()
{
	if (abs(int(m_vMoveRoute[m_currentRoute].x - GetPos().x)) > abs(int(m_vMoveRoute[m_currentRoute].y - GetPos().y)))
	{
		//x축 애니메이션 실행
		if (m_vMoveRoute[m_currentRoute].x - GetPos().x > 0)
		{
			GetAnim()->PlayAnim(L"bandit_move_right", this, true);
		}
		else
		{
			GetAnim()->PlayAnim(L"bandit_move_left", this, true);
		}
	}
	Vec2 movePos = GetPos();
	Vec2 vDir = m_vMoveRoute[m_currentRoute] - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 25.f;
	movePos.y += vDir.y * DT * 25.f;

	if (movePos.x > GetPos().x)
		SetDirAtt(UNIT_DIRECTION::RIGHT);
	else
		SetDirAtt(UNIT_DIRECTION::LEFT);

	SetPos(movePos);
}

void CBandit::Move(Vec2 _vPos)
{
	if (abs(int(_vPos.x - GetPos().x)) > abs(int(_vPos.y - GetPos().y)))
	{
		//x축 애니메이션 실행
		if (_vPos.x - GetPos().x > 0)
		{
			GetAnim()->PlayAnim(L"bandit_move_right", this, true);
		}
		else
		{
			GetAnim()->PlayAnim(L"bandit_move_left", this, true);
		}
	}
	else
	{
		//y축 애니메이션 실행
		GetAnim()->PlayAnim(L"bandit_move_front", this, true);
	}
	Vec2 movePos = GetPos();
	Vec2 vDir = _vPos - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 12.5f;
	movePos.y += vDir.y * DT * 12.5f;

	if (movePos.x > GetPos().x)
		SetDirAtt(UNIT_DIRECTION::RIGHT);
	else
		SetDirAtt(UNIT_DIRECTION::LEFT);

	SetPos(movePos);
}

void CBandit::OnCollision(CCollider * _other)
{
	// 솔저와 부뒷쳤을 때
	if (_other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_UNIT
		|| _other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_HERO)
	{
		// 내 타깃이 일치하는경우 공격한다.
		if (_other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_UNIT)
			if (((CUnit*)_other->GetObj()) != GetTarget())
				return;
			else if (_other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_HERO)
				if (((CHero*)_other->GetObj()) != GetTarget())
					return;
		SetState(UNIT_STATE::ATTACK);
		if (nullptr == GetTarget())
			SetState(UNIT_STATE::IDLE);

		if (_other->GetFinalPos().x > GetPos().x)
			SetDirAtt(UNIT_DIRECTION::RIGHT);
		else
			SetDirAtt(UNIT_DIRECTION::LEFT);

		m_fAttTime += 1.f * DT;

		if (m_fAttTime > 3.f)
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"bandit_attack_right", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"bandit_attack_left", this, false);
			if (_other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_UNIT)
				Attack((CUnit*)(_other->GetObj()));
			else if (_other->GetObj()->GetObjType() == OBJ_TYPE::ALLY_HERO)
				Attack((CHero*)(_other->GetObj()));
			m_fAttTime = 0.f;
		}
		if (GetAnim()->GetCurAni()->IsEnd())
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"bandit_idle_right", this, true);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"bandit_idle_left", this, true);
		}
	}
}
