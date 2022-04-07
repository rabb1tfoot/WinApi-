#include "stdafx.h"
#include "Ranger.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Arrow.h"


CRanger::CRanger()
{
}


CRanger::~CRanger()
{
}

void CRanger::update()
{
	GetCollider()->update();
	m_bframeEnter = true;
}

void CRanger::OnCollision(CCollider* _other)
{
	if (_other->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_UNIT)
	{
		SetState(UNIT_STATE::ATTACK);
		float angle = 180 * atan2(_other->GetFinalPos().x - GetPos().x, _other->GetFinalPos().y - GetPos().y) / 3.14f;
		if (m_bframeEnter)
		{
			m_fAttTime += 0.5f * DT;
			m_bframeEnter = false;
		}
		if (angle < 0.f)
			angle += 180.f;

		if (_other->GetFinalPos().x > GetPos().x)
		{
			SetDirAtt(UNIT_DIRECTION::RIGHT);
			if (angle > 0 && angle <= 22.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::BOTTOM;
			}
			else if (angle > 22.5f && angle <= 77.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::RB;
			}
			else if (angle > 77.5f && angle <= 122.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::RIGHT;
			}
			else if (angle > 122.5f && angle <= 167.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::RT;
			}
			else if (angle > 167.6f && angle <= 180.f)
			{
				e_mArrowDir = UNIT_DIRECTION::TOP;
			}

		}
		else
		{
			SetDirAtt(UNIT_DIRECTION::LEFT);
			if (angle > 0 && angle <= 22.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::TOP;
			}
			else if (angle > 22.5f && angle <= 77.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::LT;
			}
			else if (angle > 77.5f && angle <= 122.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::LEFT;
			}
			else if (angle > 122.5f && angle <= 167.5f)
			{
				e_mArrowDir = UNIT_DIRECTION::LB;
			}
			else if (angle > 167.6f && angle <= 180.f)
			{
				e_mArrowDir = UNIT_DIRECTION::BOTTOM;
			}
		}

		if (m_fAttTime > 1.f)
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"archer_attack_right", this, false);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"archer_attack_left", this, false);
			Attack((CUnit*)(_other->GetObj()));
			m_fAttTime = -1.f;
		}
		if (GetAnim()->GetCurAni()->IsEnd())
		{
			if (GetDirAtt() == UNIT_DIRECTION::RIGHT)
				GetAnim()->PlayAnim(L"archer_idle_right", this, true);
			if (GetDirAtt() == UNIT_DIRECTION::LEFT)
				GetAnim()->PlayAnim(L"archer_idle_left", this, true);
		}
	}
}

void CRanger::Attack(CUnit * _Other)
{
	//오브젝트 생성
	CObj* arrow = new CArrow(GetPos(), _Other);
	((CArrow*)arrow)->Init(GetPow(), e_mArrowDir);
}

