#include "stdafx.h"
#include "Hero.h"
#include "MapMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"
#include "StageMgr.h"
#include "Stage.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CHero::CHero()
	: CUI()
	, m_eState(UNIT_STATE::IDLE)
	, m_CTarget(nullptr)
	, m_tInfo{}
	, m_cMovePoint(nullptr)
	, m_bClick(false)
{
}

CHero::~CHero()
{
}

void CHero::update()
{
	if (nullptr != m_cMovePoint)
	{
		if (CMapMgr::GetInst()->GetClickMode())
		{
			m_pmousepos = MOUSEPOS;
			m_vMousePos = m_pmousepos;
			((CUI*)m_cMovePoint)->SetPos(m_vMousePos);
		}

		if (MAP_SETTING::MAP_BLOCK == CMapMgr::GetInst()->GetClickOption())
		{
			m_cMovePoint->GetAnim()->PlayAnim(L"barrack_disclick", m_cMovePoint, false);

			m_bClick = false;
			CMapMgr::GetInst()->CLickModeOff();
		}
		else if (MAP_SETTING::MAP_NOTBLOCK == CMapMgr::GetInst()->GetClickOption())
		{
			m_cMovePoint->GetAnim()->PlayAnim(L"barrack_point", m_cMovePoint, false);

			m_bClick = false;
			CMapMgr::GetInst()->CLickModeOff();
			this->Move(m_vMousePos);
		}

		//애니메이션이 끝나면 지운다.
		if (m_cMovePoint->GetAnim()->GetCurAni()->IsEnd())
		{
			if (HERO_TYPE::HERO_LIGHT == m_eType && this->m_bMoving)
			{
				//효과음 생성
				CSoundMgr::GetInst()->LoadSound(L"Hero_Light.wav", L"Hero_Light.wav");
				CSoundMgr::GetInst()->Play(L"Hero_Light.wav");
				//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
				CSoundMgr::GetInst()->SetBGMVolume(100);
			}
			else if (HERO_TYPE::HERO_HAMMER == m_eType && this->m_bMoving)
			{
				//효과음 생성
				CSoundMgr::GetInst()->LoadSound(L"Hero_Hammer.wav", L"Hero_Hammer.wav");
				CSoundMgr::GetInst()->Play(L"Hero_Hammer.wav");
				//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
				CSoundMgr::GetInst()->SetBGMVolume(100);
			}
			m_cMovePoint->SetDead();
			m_cMovePoint = nullptr;
			CMapMgr::GetInst()->SetClickOption(MAP_SETTING::NONE);
		}
	}
	if (nullptr == this || this->IsDead())
		return;
	else if (this->m_bMoving)
	{
		this->Move(Vec2(this->m_vMousePos));
	}
	this->SetFinalPos(this->GetPos());
}

void CHero::MouseOn(Vec2 _vMousePos)
{
	return;
}

void CHero::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	//클릭되면 움직일 수 있다.
	if (!this->m_bMoving)
	{
		CMapMgr::GetInst()->CLickModeOn();
		CreateMovePoint();
	}

}

void CHero::CreateMovePoint()
{
	if (nullptr != m_cMovePoint)
		return;
	m_cMovePoint = new CObj;
	m_cMovePoint->SetObjType(OBJ_TYPE::MAP_INGREDIENT);
	m_cMovePoint->SetPos(Vec2(0, 0));
	CAnimator* pAnimtor = new CAnimator(m_cMovePoint);
	CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_cursering");
	pAnimtor->AddAnimation(L"barrack_cursering", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_point");
	pAnimtor->AddAnimation(L"barrack_point", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_disclick");
	pAnimtor->AddAnimation(L"barrack_disclick", pAnim);
	m_cMovePoint->SetAnim(pAnimtor);
	m_cMovePoint->GetAnim()->PlayAnim(L"barrack_cursering", m_cMovePoint, true);
	CStageMgr::GetInst()->GetCurStage()->AddObject(m_cMovePoint, OBJ_TYPE::MAP_INGREDIENT);

}
