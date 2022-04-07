#include "stdafx.h"
#include "Stage_Pause.h"
#include "ResMgr.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Stage_Quit.h"
#include "Stage_Resume.h"
#include "App.h"
#include "SoundMgr.h"

CStage_Pause::CStage_Pause()
{
}


CStage_Pause::~CStage_Pause()
{
}

void CStage_Pause::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(399.f, 12.f));
}

void CStage_Pause::MouseOff()
{
	SetTexPos(Vec2(324.f, 14.f));
}

void CStage_Pause::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CApp::GetInst()->SetbPause(true);

	if (!m_bCreated)
	{
		CreateSubMenu();
		m_bCreated = true;
	}
	else
	{
		((CObj*)m_pResume)->SetEnable(true);
		((CObj*)m_pPanel)->SetEnable(true);
		((CObj*)m_pQuit)->SetEnable(true);
	}
}


void CStage_Pause::CreateSubMenu()
{
	//패널 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"OptionsMaterial.bmp", L"Texture\\OptionsMaterial.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ 351.f,272.f });
	pObj->SetTexPos(Vec2(9.f, 70.f));
	pObj->SetObjType(OBJ_TYPE::ELDER_PANEL);
	m_pPanel = pObj;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pObj, OBJ_TYPE::ELDER_PANEL);

	//버튼생성
	pTex = CResMgr::GetInst()->FindTexture(L"OptionsMaterial.bmp");
	CUI* pResume = new CStage_Resume;
	pResume->SetTexture(pTex);
	pResume->SetSize(Vec2{ 94.f, 35.f });
	pResume->SetPos(Vec2{ float(WINSIZE_X / 2 + 50.f), float(WINSIZE_Y / 2) });
	pResume->SetTexPos(Vec2(356.f, 161.f));
	pResume->SetFinalPos(pResume->GetPos());
	pResume->SetObjType(OBJ_TYPE::ELDER_UI);
	((CStage_Resume*)pResume)->SetParnet(this);
	m_pResume = pResume;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pResume, OBJ_TYPE::ELDER_UI);

	pTex = CResMgr::GetInst()->FindTexture(L"OptionsMaterial.bmp");
	CUI* pQuit = new CStage_Quit;
	pQuit->SetTexture(pTex);
	pQuit->SetSize(Vec2{ 94.f, 35.f });
	pQuit->SetPos(Vec2{ float(WINSIZE_X / 2 - 50.f), float(WINSIZE_Y / 2) });
	pQuit->SetTexPos(Vec2(356.f, 232.f));
	pQuit->SetFinalPos(pQuit->GetPos());
	pQuit->SetObjType(OBJ_TYPE::ELDER_UI);
	((CStage_Quit*)pQuit)->SetOptionState(true);
	m_pQuit = pQuit;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pQuit, OBJ_TYPE::ELDER_UI);
}
