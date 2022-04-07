#include "stdafx.h"
#include "Hero_Hammer.h"
#include "Collider.h"
#include "Unit.h"
#include "Obj_Coll.h"
#include "Animation.h"
#include "Animator.h"
#include "SoundMgr.h"

CHero_Hammer::CHero_Hammer()
	:CHero()
{
	m_vMovingPos = Vec2(0.f, 0.f);
}



CHero_Hammer::~CHero_Hammer()
{
}

void CHero_Hammer::update()
{

	GetCollider()->update();
	CHero::update();
	//체력이 다하면 죽음처리
	if (GetInfo().iCurHealth <= 0)
	{
		this->SetDead();
		if (nullptr != GetObjColl())
		{
			GetObjColl()->SetDead();
		}
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
		return;
	}
	if (UNIT_STATE::IDLE == GetState())
	{
		if (m_bMoving)
			return;
		GetAnim()->PlayAnim(L"hero_hammer_idle_right", this, true);
	}
}

void CHero_Hammer::Move(Vec2 _vPos)
{
	if (UNIT_STATE::ATTACK == GetState())
		return;
	//x축 애니메이션 실행
	if (_vPos.x - GetPos().x > 0)
	{
		GetAnim()->PlayAnim(L"hero_hammer_move_right", this, true);
	}
	else
	{
		GetAnim()->PlayAnim(L"hero_hammer_move_left", this, true);
	}
	Vec2 movePos = GetPos();
	Vec2 vDir = Vec2(_vPos.x - GetPos().x, _vPos.y - GetPos().y);
	vDir.Normalize();

	movePos.x += vDir.x * DT * 25.f;
	movePos.y += vDir.y * DT * 25.f;

	if (movePos.x >  GetPos().x)
		SetDirAtt(UNIT_DIRECTION::LEFT);
	else
		SetDirAtt(UNIT_DIRECTION::RIGHT);

	SetPos(movePos);

	if (abs(_vPos.x - movePos.x) < 2.f && abs(_vPos.y - movePos.y) < 2.f)
	{
		m_bMoving = false;
		m_vMovingPos = Vec2(0.f, 0.f);
		return;
	}
	m_bMoving = true;
	m_vMovingPos = _vPos;
}


void CHero_Hammer::OnCollision(CCollider * _other)
{
	// 적군과 부뒷쳤을 때
	if (_other->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_UNIT)
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
			int random = rand();
			if (random % 3 != 0)
			{
				if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
					GetAnim()->PlayAnim(L"hero_hammer_attack_right", this, false);
				if (GetDirAtt() == UNIT_DIRECTION::LEFT)
					GetAnim()->PlayAnim(L"hero_hammer_attack_left", this, false);
			}
			else
			{
				if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
					GetAnim()->PlayAnim(L"hero_hammer_sattack_right", this, false);
				if (GetDirAtt() == UNIT_DIRECTION::LEFT)
					GetAnim()->PlayAnim(L"hero_hammer_sattack_left", this, false);
			}
			Attack((CUnit*)(_other->GetObj()));
			m_fAttTime = 0.f;
		}
		if (GetAnim()->GetCurAni()->IsEnd())
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"hero_hammer_idle_right", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"hero_hammer_idle_left", this, false);
		}
	}
}



void CHero_Hammer::Attack(CUnit * _Other)
{
	tUnitInfo* tInfo = &_Other->GetInfo();
	tInfo->iCurHealth -= this->GetInfo().iAtt_pow;

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_Hit.wav", L"Sound_Hit.wav");
	CSoundMgr::GetInst()->Play(L"Sound_Hit.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	//상대방 사망시 타깃과 상태초기화
	if (tInfo->iCurHealth <= 0)
	{
		SetState(UNIT_STATE::IDLE);
		SetTarget(nullptr);
		m_bMoving = false;
		m_vMovingPos = GetPos();
	}
}
