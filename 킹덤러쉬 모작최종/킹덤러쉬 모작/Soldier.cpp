#include "stdafx.h"
#include "Soldier.h"
#include "Animator.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Obj_Coll.h"
#include "Barracks.h"
#include "SoundMgr.h"


CSoldier::CSoldier()
{
	m_vMovingPos = Vec2(0.f, 0.f);
}


CSoldier::~CSoldier()
{
	if (nullptr != GetTarget())
	{
		if(nullptr != ((CUnit*)this)->GetObjColl())
			((CUnit*)this)->GetObjColl()->SetDead();
	}
	m_cParentBuild->SetmySoldierDead(m_number);
}


void CSoldier::update()
{
	GetCollider()->update();
	//체력이 다하면 죽음처리
	if (GetInfo().iCurHealth <= 0)
	{
		//상대방이 살아있다면 전투후 상태와 타깃값을 초기화한다.
		if (nullptr != GetTarget())
		{
			((CUnit*)GetTarget())->SetState(UNIT_STATE::IDLE);
			((CUnit*)GetTarget())->SetTarget(nullptr);
		}
		//효과음 생성
		CSoundMgr::GetInst()->LoadSound(L"Sound_Dead.wav", L"Sound_Dead.wav");
		CSoundMgr::GetInst()->Play(L"Sound_Dead.wav");
		//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
		CSoundMgr::GetInst()->SetBGMVolume(100);

		m_cParentBuild->SetmySoldierDead(m_number);
		this->SetDead();
		((CUnit*)this)->GetObjColl()->SetDead();
		return;
	}
	if (UNIT_STATE::IDLE == GetState())
	{
		if (m_bMoving)
			return;
		GetAnim()->PlayAnim(L"barrack_unit1_idle_right", this, true);
	}
}

void CSoldier::Move(Vec2 _vPos, int i)
{
	if (UNIT_STATE::ATTACK == GetState())
		return;
		//x축 애니메이션 실행
	if (_vPos.x - GetPos().x > 0)
	{
		GetAnim()->PlayAnim(L"barrack_unit1_move_right", this, true);
	}
	else
	{
		GetAnim()->PlayAnim(L"barrack_unit1_move_left", this, true);
	}
	Vec2 movePos = GetPos();
	Vec2 vDir = Vec2(_vPos.x + (20 * i) - GetPos().x, _vPos.y - GetPos().y);//_vPos - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 25.f;
	movePos.y += vDir.y * DT * 25.f;

	if (movePos.x >  GetPos().x)
		SetDirAtt(UNIT_DIRECTION::LEFT);
	else
		SetDirAtt(UNIT_DIRECTION::RIGHT);

	SetPos(movePos);

	if (abs(_vPos.x + float(20 * i) - movePos.x) < 2.f && abs(_vPos.y - movePos.y) < 2.f)
	{
		m_bMoving = false;
		m_vMovingPos = Vec2(0.f, 0.f);
		return;
	}
	m_bMoving = true;
	m_vMovingPos = _vPos;


}

void CSoldier::OnCollision(CCollider * _other)
{
	//아군과 부뒷쳤을 때
	if (this->GetObjType() == _other->GetObj()->GetObjType())
	{
		//y축이 부뒷쳤을 때
		if (_other->GetFinalPos().x - _other->GetSize().x / 2 < GetCollider()->GetFinalPos().x + GetCollider()->GetSize().x / 2
			&& _other->GetFinalPos().x + _other->GetSize().x > GetCollider()->GetFinalPos().x - GetCollider()->GetSize().x / 2)
		{
			if (_other->GetFinalPos().x - _other->GetSize().x / 2 < GetCollider()->GetFinalPos().x + GetCollider()->GetSize().x / 2)
			{
				Vec2 CurPos = GetPos();
				SetPos(Vec2(CurPos.x - (50.f * DT), CurPos.y - (60.f * DT)));
			}
			else
			{
				Vec2 CurPos = GetPos();
				SetPos(Vec2(CurPos.x + (50.f * DT), CurPos.y - (60.f * DT)));
			}
		}
		//x축이 부뒷쳤을 때
		if (_other->GetFinalPos().y - _other->GetSize().y / 2 < GetCollider()->GetFinalPos().y + GetCollider()->GetSize().y / 2
			&& _other->GetFinalPos().y + _other->GetSize().y > GetCollider()->GetFinalPos().y - GetCollider()->GetSize().y / 2)
		{
			if (_other->GetFinalPos().y - _other->GetSize().y / 2 < GetCollider()->GetFinalPos().y + GetCollider()->GetSize().y / 2)
			{
				Vec2 CurPos = GetPos();
				SetPos(Vec2(CurPos.x + (60.f * DT), CurPos.y - (50.f * DT)));
			}
			else
			{
				Vec2 CurPos = GetPos();
				SetPos(Vec2(CurPos.x + (60.f * DT), CurPos.y + (50.f * DT)));
			}
		}
	}
	// 적군과 부뒷쳤을 때
	else if (_other->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_UNIT)
	{
		// 내 타깃이 일치하는경우 공격한다.
		if (((CUnit*)_other->GetObj()) != GetTarget())
			return;

		SetState(UNIT_STATE::ATTACK);

		if (_other->GetFinalPos().x > GetPos().x)
			SetDirAtt(UNIT_DIRECTION::RIGHT);
		else
			SetDirAtt(UNIT_DIRECTION::LEFT);

		m_fAttTime += 1.f * DT;

		if (m_fAttTime > 3.f)
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"barrack_unit1_attack_right", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"barrack_unit1_attack_left", this, false);
			Attack((CUnit*)(_other->GetObj()));
			m_fAttTime = 0.f;
		}
		if (GetAnim()->GetCurAni()->IsEnd())
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"barrack_unit1_idle_right", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"barrack_unit1_idle_left", this, false);
		}
	}
}
