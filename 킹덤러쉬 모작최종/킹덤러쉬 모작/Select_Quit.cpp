#include "stdafx.h"
#include "Select_Quit.h"
#include "StageMgr.h"
#include "SoundMgr.h"


CSelect_Quit::CSelect_Quit()
	:m_bMouseAttach(false)
{
}


CSelect_Quit::~CSelect_Quit()
{
}

void CSelect_Quit::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(356.f, 267.f));
	if (!m_bMouseAttach)
	{
		m_bMouseAttach = true;
	}

}

void CSelect_Quit::MouseOff()
{
	SetTexPos(Vec2(356.f, 232.f));
	if (m_bMouseAttach)
	{
		m_bMouseAttach = false;
	}

}

void CSelect_Quit::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::TITLE);
}
