#include "stdafx.h"
#include "Title_StartUI.h"
#include "StageMgr.h"
#include "Stage.h"
#include "SoundMgr.h"


CTitle_StartUI::CTitle_StartUI()
	:m_bMouseAttach(false)
{
}


CTitle_StartUI::~CTitle_StartUI()
{
}

void CTitle_StartUI::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(554, 335.f));
	if (!m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x - 5.f, GetPos().y));
		m_bMouseAttach = true;
	}
}

void CTitle_StartUI::MouseOff()
{
	SetTexPos(Vec2(717.f, 333.f));
	if (m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x + 5.f, GetPos().y));
		m_bMouseAttach = false;
	}
}

void CTitle_StartUI::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	//설렉트 스테이지로 이동
	CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::SELECT);
}
