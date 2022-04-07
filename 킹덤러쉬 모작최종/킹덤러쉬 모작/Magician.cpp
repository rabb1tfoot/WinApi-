#include "stdafx.h"
#include "Magician.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Magicbolt.h"
#include "Mage.h"
#include "Bomb.h"


CMagician::CMagician()
{
}


CMagician::~CMagician()
{
}



void CMagician::update()
{
	GetCollider()->update();
	m_bframeEnter = true;
}

void CMagician::OnCollision(CCollider * _other)
{
	if (_other->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_UNIT)
	{
		SetState(UNIT_STATE::ATTACK);
		if (m_bframeEnter)
		{
			m_fAttTime += 0.5f * DT;
			m_bframeEnter = false;
		}
		if (m_fAttTime > 1.f)
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"mage_attack_left", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"mage_attack_right", this, false);
			if (0 == GetTier())
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build1_attack", this, false, Vec2{ 0.f, 53.f });
			}
			else if (2 ==  GetTier())
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build2_attack", this, false, Vec2{ 0.f, 43.f });
			}
			else
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build3_attack", this, false, Vec2{ -10.f, 38.f});
			}
			Attack((CUnit*)(_other->GetObj()));
			m_fAttTime = -1.f;
		}
		if (GetAnim()->GetCurAni()->IsEnd())
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"mage_idle_left", this, true);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"mage_idle_right", this, true);
			if (0 == GetTier())
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build1_idle", this, true, Vec2{ 0.f, 53.f });
			}
			else if (2 == GetTier())
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build2_idle", this, true, Vec2{ 0.f, 43.f });
			}
			else
			{
				m_cMage->GetAnim()->PlayAnim(L"mage_build3_idle", this, true, Vec2{ -10.f, 38.f });
			}
		}
	}
}

void CMagician::Attack(CUnit * _Other)
{
	//오브젝트 생성
	CObj* bolt = new CMagicbolt(GetPos(),_Other);
	((CMagicbolt*)bolt)->Init(GetPow());
}

void CMagician::SetBuild(CMage * _build)
{
	m_cMage = _build;
}
