#include "stdafx.h"
#include "Magicbolt.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "ResMgr.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Unit.h"

CMagicbolt::CMagicbolt()
	:CObj()
{
}

CMagicbolt::CMagicbolt(Vec2 _pos, CUnit * _Other)
	: CObj(_pos)
	, m_ctarget(_Other)
{

}


CMagicbolt::~CMagicbolt()
{
}

void CMagicbolt::Init(int _pow)
{
	this->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
	m_ipow = _pow;
	CAnimator* anim = new CAnimator(this);
	CAnimation* ani = CResMgr::GetInst()->LoadAnimation(L"mage_bolt");
	anim->AddAnimation(L"mage_bolt", ani);
	this->SetAnim(anim);

	this->GetAnim()->PlayAnim(L"mage_bolt", this, true);

	CCollider* pCol = new CCollider(this);
	pCol->SetFinalPos(this->GetPos());
	pCol->SetSize(Vec2(15.f, 15.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	this->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(this, OBJ_TYPE::ALLY_UNIT_RANGE);

}

void CMagicbolt::update()
{
	GetCollider()->update();

	Vec2 _vPos = m_ctarget->GetPos();

	Vec2 movePos = GetPos();
	Vec2 vDir = _vPos - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 200.f;
	movePos.y += vDir.y * DT * 200.f;

	SetPos(movePos);
}

void CMagicbolt::OnCollision(CCollider * _other)
{
	tUnitInfo Otherinfo = ((CUnit*)_other->GetObj())->GetInfo();
	Otherinfo.iCurHealth -= m_ipow;
	((CUnit*)_other->GetObj())->SetInfo(Otherinfo);
	
	this->SetDead();

}
