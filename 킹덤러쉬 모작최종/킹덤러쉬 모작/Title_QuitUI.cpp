#include "stdafx.h"
#include "Title_QuitUI.h"
#include "StageMgr.h"
#include "Stage.h"
#include "App.h"
#include "SoundMgr.h"



CTitle_QuitUI::CTitle_QuitUI()
	:m_bMouseAttach(false)
{
}


CTitle_QuitUI::~CTitle_QuitUI()
{
}

void CTitle_QuitUI::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(946.f, 369.f));
	if (!m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x, GetPos().y - 10.f));
		m_bMouseAttach = true;
	}
}

void CTitle_QuitUI::MouseOff()
{
	SetTexPos(Vec2(493.f, 140.f));
	if (m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x, GetPos().y + 10.f));
		m_bMouseAttach = false;
	}
}

void CTitle_QuitUI::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CStageMgr::GetInst()->GetCurStage()->Exit();
	DestroyWindow(CApp::GetInst()->GetWINHWND());
	CApp::GetInst()->SetGameOver(true);
}
