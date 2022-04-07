#include "stdafx.h"
#include "Obj_Coll.h"
#include "Collider.h"
#include "Unit.h"
#include "Soldier.h"
#include "Hero_Light.h"


CObj_Coll::CObj_Coll()
	:CObj()
{
}


CObj_Coll::~CObj_Coll()
{
}


void CObj_Coll::update()
{
	SetPos(m_Owner->GetPos());
	GetCollider()->update();

	if (nullptr == m_Owner)
	{
		SetDead();
	}
}

void CObj_Coll::render(HDC _hdc)
{
	CObj::render(_hdc);
}

void CObj_Coll::OnCollisionEnter(CCollider * _other)
{
	//솔저가 부뒷치는경우
	if (OBJ_TYPE::ALLY_UNIT == _other->GetObj()->GetObjType())
	{
		//자신이 아이들인 상태에서 아군도 아이들이고 타깃이 없으면 추격한다.
		if (UNIT_STATE::IDLE == ((CUnit*)(_other->GetObj()))->GetState()
			&& (nullptr == (((CUnit*)(_other->GetObj()))->GetTarget()))
			&& (UNIT_STATE::IDLE == ((CUnit*)(this->GetOwner()))->GetState()))
		{
			((CUnit*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
			((CUnit*)m_Owner)->SetTarget((CUnit*)_other->GetObj());
			((CUnit*)_other->GetObj())->SetTarget((CUnit*)m_Owner);
			((CUnit*)_other->GetObj())->SetState(UNIT_STATE::TRACKING);
		}
	}
	//영웅이 부뒷치는경우
	else if (OBJ_TYPE::ALLY_HERO == _other->GetObj()->GetObjType())
	{
		//자신이 아이들인 상태에서 아군도 아이들이고 타깃이 없으면 추격한다.
		if (UNIT_STATE::IDLE == ((CHero*)(_other->GetObj()))->GetState()
			&& (nullptr == (((CHero*)(_other->GetObj()))->GetTarget()))
			&& (UNIT_STATE::IDLE == ((CUnit*)(this->GetOwner()))->GetState()))
		{
			((CUnit*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
			((CUnit*)m_Owner)->SetTarget((CHero*)_other->GetObj());
			((CHero*)_other->GetObj())->SetTarget(m_Owner);
			((CHero*)_other->GetObj())->SetState(UNIT_STATE::TRACKING);
		}
	}
}


void CObj_Coll::OnCollision(CCollider * _other)
{
	//적 범위에 아군과 부뒷치는경우
	if (OBJ_TYPE::ALLY_UNIT == _other->GetObj()->GetObjType())
	{
		////자신이 아이들인 상태에서 아군도 아이들이고 타깃이 없으면 추격한다.
		//if (UNIT_STATE::IDLE == ((CUnit*)(_other->GetObj()))->GetState()
		//	&& (nullptr == (((CUnit*)(_other->GetObj()))->GetTarget()))
		//	&& (UNIT_STATE::IDLE == ((CUnit*)(this->GetOwner()))->GetState()))
		//{
		//	((CUnit*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
		//	((CUnit*)m_Owner)->SetTarget((CUnit*)_other->GetObj());
		//	((CUnit*)_other->GetObj())->SetTarget((CUnit*)m_Owner);
		//	((CUnit*)_other->GetObj())->SetState(UNIT_STATE::TRACKING);
		//}
		if (UNIT_STATE::TRACKING == ((CUnit*)(this->GetOwner()))->GetState()
			&& (CUnit*)GetOwner() == ((CUnit*)(_other->GetObj()))->GetTarget())
		{
			//방향에따라 이동을 나누고 타깃설정을 한다.
			if ((_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
				&&_other->GetObj()->GetPos().y > ((CUnit*)m_Owner)->GetPos().y)
				|| (_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
					&&_other->GetObj()->GetPos().y <= ((CUnit*)m_Owner)->GetPos().y))
			{
				((CUnit*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x - 20.f, _other->GetObj()->GetPos().y));
			}
			else
			{
				((CUnit*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x + 20.f, _other->GetObj()->GetPos().y));
			}
		}
	}
	//적 범위에 영웅이 부뒷치는경우
	if (OBJ_TYPE::ALLY_HERO == _other->GetObj()->GetObjType())
	{
		//자신이 아이들인 상태에서 아군도 아이들이고 타깃이 없으면 추격한다.
		//if (UNIT_STATE::IDLE == ((CHero*)(_other->GetObj()))->GetState()
		//	&& (nullptr == (((CHero*)(_other->GetObj()))->GetTarget()))
		//	&& (UNIT_STATE::IDLE == ((CUnit*)(this->GetOwner()))->GetState()))
		//{
		//	((CUnit*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
		//	((CUnit*)m_Owner)->SetTarget((CHero*)_other->GetObj());
		//	((CHero*)_other->GetObj())->SetTarget(m_Owner);
		//	((CHero*)_other->GetObj())->SetState(UNIT_STATE::TRACKING);
		//}
		if (UNIT_STATE::TRACKING == ((CUnit*)(this->GetOwner()))->GetState()
			&& (CUnit*)GetOwner() == ((CHero*)(_other->GetObj()))->GetTarget())
		{
			//방향에따라 이동을 나누고 타깃설정을 한다.
			if ((_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
				&&_other->GetObj()->GetPos().y > ((CUnit*)m_Owner)->GetPos().y)
				|| (_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
					&&_other->GetObj()->GetPos().y <= ((CUnit*)m_Owner)->GetPos().y))
			{
				((CUnit*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x - 20.f, _other->GetObj()->GetPos().y));
			}
			else
			{
				((CUnit*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x + 20.f, _other->GetObj()->GetPos().y));
			}
		}
	}

	//아군 범위에 적이 부뒷치는경우
	else if (OBJ_TYPE::ENEMY_UNIT == _other->GetObj()->GetObjType())
	{
		//적의 타깃이 자신일경우 추격한다.
		if (((CUnit*)_other->GetObj())->GetTarget() == this->GetOwner()
			&& UNIT_STATE::ATTACK != ((CUnit*)(this->GetOwner()))->GetState()
			&& OBJ_TYPE::ALLY_UNIT == m_Owner->GetObjType())
		{
			if (((CUnit*)_other->GetObj())->GetInfo().iCurHealth <= 0)
				return;
			((CUnit*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
			if ((_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
				&&_other->GetObj()->GetPos().y > ((CUnit*)m_Owner)->GetPos().y)
				|| (_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
					&&_other->GetObj()->GetPos().y <= ((CUnit*)m_Owner)->GetPos().y))
			{
				((CSoldier*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x - 20.f, _other->GetObj()->GetPos().y));
			}
			else
			{
				((CSoldier*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x + 20.f, _other->GetObj()->GetPos().y));
			}
			((CSoldier*)m_Owner)->SetTarget((CUnit*)_other->GetObj());

		}
		//솔저가 아닌 히어로일 경우
		else if (((CUnit*)_other->GetObj())->GetTarget() == this->GetOwner()
			&& UNIT_STATE::ATTACK != ((CHero*)(this->GetOwner()))->GetState()
			&& OBJ_TYPE::ALLY_HERO == m_Owner->GetObjType())
		{
			if (((CUnit*)_other->GetObj())->GetInfo().iCurHealth <= 0)
				return;
			((CHero*)(this->GetOwner()))->SetState(UNIT_STATE::TRACKING);
			if ((_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
				&&_other->GetObj()->GetPos().y > ((CUnit*)m_Owner)->GetPos().y)
				|| (_other->GetObj()->GetPos().x > ((CUnit*)m_Owner)->GetPos().x
					&&_other->GetObj()->GetPos().y <= ((CUnit*)m_Owner)->GetPos().y))
			{
				((CHero*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x - 20.f, _other->GetObj()->GetPos().y));
			}
			else
			{
				((CHero*)m_Owner)->Move(Vec2(_other->GetObj()->GetPos().x + 20.f, _other->GetObj()->GetPos().y));
			}
			((CHero*)m_Owner)->SetTarget((CUnit*)_other->GetObj());
		}
	}
}

