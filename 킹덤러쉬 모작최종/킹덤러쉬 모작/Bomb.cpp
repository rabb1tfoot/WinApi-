#include "stdafx.h"
#include "Bomb.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Stage.h"
#include "StageMgr.h"
#include "Unit.h"
#include "SoundMgr.h"

CBomb::CBomb()
	:CObj()
{
}

CBomb::CBomb(Vec2 _pos, CUnit * _Other)
	: CObj(_pos)
	, m_cTarget(_Other)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_Bomb.wav", L"Sound_Bomb.wav");
	CSoundMgr::GetInst()->Play(L"Sound_Bomb.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}

CBomb::~CBomb()
{
	m_cTarget = nullptr;
	if (nullptr != m_cBoundary)
		delete m_cBoundary;
}

void CBomb::Init(int _pow)
{
	this->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
	m_iPow = _pow;
	CAnimator* anim = new CAnimator(this);
	CAnimation* ani = CResMgr::GetInst()->LoadAnimation(L"cannon_bomb");
	anim->AddAnimation(L"cannon_bomb", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"cannon_cloude");
	anim->AddAnimation(L"cannon_cloude", ani);
	this->SetAnim(anim);

	this->GetAnim()->PlayAnim(L"cannon_bomb", this, true);

	CCollider* pCol = new CCollider(this);
	pCol->SetFinalPos(this->GetPos());
	pCol->SetSize(Vec2(15.f, 15.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	this->SetCollider(pCol);
	pCol = new CCollider(this);
	pCol->SetFinalPos(this->GetPos());
	pCol->SetSize(Vec2(120.f, 120.f));
	pCol->SetColliderType(COLLIDER_TYPE::ELLIPSE);
	m_cBoundary = pCol;

	CStageMgr::GetInst()->GetCurStage()->AddObject(this, OBJ_TYPE::ALLY_UNIT_RANGE);
}

void CBomb::update()
{
	GetCollider()->update();

	if(nullptr == m_cTarget)
		this->SetDead();

	Vec2 _vPos = m_cTarget->GetPos();

	Vec2 movePos = GetPos();
	Vec2 vDir = _vPos - GetPos();
	vDir.Normalize();

	movePos.x += vDir.x * DT * 300.f;
	movePos.y += vDir.y * DT * 300.f;

	SetPos(movePos);
}

void CBomb::OnCollision(CCollider * _other)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_BombHit.wav", L"Sound_BombHit.wav");
	CSoundMgr::GetInst()->Play(L"Sound_BombHit.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	tUnitInfo Otherinfo = ((CUnit*)_other->GetObj())->GetInfo();
	this->GetAnim()->PlayAnim(L"cannon_cloude", this, false, Vec2{ 0.f, -40.f });
	if (GetAnim()->GetCurAni()->IsEnd())
	{
		Otherinfo.iCurHealth -= m_iPow;
		((CUnit*)_other->GetObj())->SetInfo(Otherinfo);
		this->SetDead();
	}
}
