#include "stdafx.h"
#include "Arrow.h"
#include "Animator.h"
#include "Animation.h"
#include  "Collider.h"
#include "Stage.h"
#include "StageMgr.h"
#include "Unit.h"
#include "SoundMgr.h"


CArrow::CArrow()
	:CObj()
{
}

CArrow::CArrow(Vec2 _pos, CUnit * _Other)
	: CObj(_pos)
	, m_ctarget(_Other)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_Arrow.wav", L"Sound_Arrow.wav");
	CSoundMgr::GetInst()->Play(L"Sound_Arrow.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


CArrow::~CArrow()
{
}

void CArrow::Init(int _pow, UNIT_DIRECTION _eDir)
{
	this->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
	m_iPow = _pow;
	CAnimator* anim = new CAnimator(this);
	CAnimation* ani = CResMgr::GetInst()->LoadAnimation(L"arrow_top");
	anim->AddAnimation(L"arrow_top", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_right");
	anim->AddAnimation(L"arrow_right", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_left");
	anim->AddAnimation(L"arrow_left", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_bottom");
	anim->AddAnimation(L"arrow_bottom", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_rt");
	anim->AddAnimation(L"arrow_rt", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_rb");
	anim->AddAnimation(L"arrow_rb", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_lt");
	anim->AddAnimation(L"arrow_lt", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"arrow_lb");
	anim->AddAnimation(L"arrow_lb", ani);
	this->SetAnim(anim);

	//애니메이션 설정
	if (_eDir == UNIT_DIRECTION::TOP)
	{
		anim->PlayAnim(L"arrow_top", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::RIGHT)
	{
		anim->PlayAnim(L"arrow_right", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::LEFT)
	{
		anim->PlayAnim(L"arrow_left", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::BOTTOM)
	{
		anim->PlayAnim(L"arrow_bottom", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::LT)
	{
		anim->PlayAnim(L"arrow_lt", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::LB)
	{
		anim->PlayAnim(L"arrow_lb", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::RT)
	{
		anim->PlayAnim(L"arrow_rt", this, true);
	}
	else if (_eDir == UNIT_DIRECTION::RB)
	{
		anim->PlayAnim(L"arrow_rb", this, true);
	}


	CCollider* pCol = new CCollider(this);
	pCol->SetFinalPos(this->GetPos());
	pCol->SetSize(Vec2(15.f, 15.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	this->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(this, OBJ_TYPE::ALLY_UNIT_RANGE);

}


void CArrow::update()
{
	this->GetCollider()->update();

	Vec2 _vPos = m_ctarget->GetPos();
	if(m_ctarget->GetPos().x < 0.f || m_ctarget->GetPos().y < 0.f)
		this->SetDead();

	Vec2 movePos = GetPos();
	Vec2 vDir = _vPos - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 400.f;
	movePos.y += vDir.y * DT * 400.f;

	SetPos(movePos);
}

void CArrow::OnCollision(CCollider * _other)
{
	tUnitInfo Otherinfo = ((CUnit*)_other->GetObj())->GetInfo();
	Otherinfo.iCurHealth -= m_iPow;
	((CUnit*)_other->GetObj())->SetInfo(Otherinfo);

	this->SetDead();
}
