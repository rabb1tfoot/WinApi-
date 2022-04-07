#include "stdafx.h"
#include "Unit.h"
#include "Obj_Coll.h"
#include "Hero.h"
#include "SoundMgr.h"


CUnit::CUnit()
	: CObj()
	, m_eAttType(ATTACK_TYPE::MELEE)
	, m_eState(UNIT_STATE::IDLE)
	, m_fAttTime(0.f)
	, m_CTarget(nullptr)
{
	m_eDir[(UINT)DIRECITON_MODE::DIR_NOMAL] = UNIT_DIRECTION::BOTTOM;
	m_eDir[(UINT)DIRECITON_MODE::DIR_ATTACK] = UNIT_DIRECTION::LEFT;
}


CUnit::~CUnit()
{
	if (nullptr != ((CUnit*)this)->GetObjColl())
		((CUnit*)this)->GetObjColl()->SetDead();
}


void CUnit::Attack(CUnit * _Other)
{
	tUnitInfo* tInfo = &_Other->GetInfo();
	tInfo->iCurHealth -= this->m_tInfo.iAtt_pow;
	//상대방 사망시 자신의 타깃과 상태초기화

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_Hit.wav", L"Sound_Hit.wav");
	CSoundMgr::GetInst()->Play(L"Sound_Hit.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	if (tInfo->iCurHealth <= 0)
	{
		SetState(UNIT_STATE::IDLE);
		SetTarget(nullptr);
		m_bMoving = false;
	}
}

void CUnit::Attack(CHero * _Other)
{
	tUnitInfo* tInfo = &_Other->GetInfo();
	tInfo->iCurHealth -= this->m_tInfo.iAtt_pow;
	//상대방 사망시 자신의 타깃과 상태초기화

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_Hit.wav", L"Sound_Hit.wav");
	CSoundMgr::GetInst()->Play(L"Sound_Hit.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	if (tInfo->iCurHealth <= 0)
	{
		SetState(UNIT_STATE::IDLE);
		SetTarget(nullptr);
		m_bMoving = false;
	}

}

void CUnit::update()
{
	CObj::update();
}

void CUnit::render(HDC _hdc)
{
	CObj::render(_hdc);
}
