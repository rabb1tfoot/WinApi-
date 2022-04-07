#include "stdafx.h"
#include "CannonBound.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "CCannon.h"
#include "Bomb.h"


CCannonBound::CCannonBound()
{
}


CCannonBound::~CCannonBound()
{
}


void CCannonBound::update()
{
	GetCollider()->update();
	m_bframeEnter = true;
}

void CCannonBound::OnCollision(CCollider * _other)
{
	if (_other->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_UNIT)
	{
		if (m_bframeEnter)
		{
			m_fAttTime += 0.5f * DT;
			m_bframeEnter = false;
		}
		if (m_fAttTime > 1.f)
		{
			m_cCannon->GetAnim()->PlayAnim(L"cannon_attack1", this, false, Vec2(0,40));

			Attack((CUnit*)(_other->GetObj()));
			m_fAttTime = -1.f;
		}
		if (m_cCannon->GetAnim()->GetCurAni()->IsEnd())
		{
			m_cCannon->GetAnim()->PlayAnim(L"cannon_build1", this, true, Vec2(0, 40));
		}
	}
}

void CCannonBound::Attack(CUnit * _Other)
{
	CObj* bomb = new CBomb(GetPos(), _Other);
	((CBomb*)bomb)->Init(m_fPow);
}
