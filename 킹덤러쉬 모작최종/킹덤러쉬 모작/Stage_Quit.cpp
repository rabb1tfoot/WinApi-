#include "stdafx.h"
#include "Stage_Quit.h"
#include "StageMgr.h"
#include "Stage.h"
#include "SoundMgr.h"
#include "App.h"


CStage_Quit::CStage_Quit()
	:m_bOption(false)
{
}


CStage_Quit::~CStage_Quit()
{
}

void CStage_Quit::MouseOn(Vec2 _vMousePos)
{
	CUI::MouseOn(_vMousePos);

	if (m_bOption)
		SetTexPos(Vec2(356.f, 270.f));
	else
		SetTexPos(Vec2(5.f, 430.f));
}

void CStage_Quit::MouseOff()
{
	CUI::MouseOff();

	if (m_bOption)
		SetTexPos(Vec2(356.f, 232.f));
	else
		SetTexPos(Vec2(437.f, 433.f));
}

void CStage_Quit::MouseLbtnClicked(Vec2 _vMousePos)
{
	CUI::MouseOff();
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::SELECT);
	CApp::GetInst()->SetbPause(false);
}
