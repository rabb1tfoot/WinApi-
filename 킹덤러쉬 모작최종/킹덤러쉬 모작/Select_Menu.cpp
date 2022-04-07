#include "stdafx.h"
#include "Select_Menu.h"
#include "ResMgr.h"
#include "Texture.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Select_Quit.h"
#include "Select_Resume.h"
#include "SoundMgr.h"

CSelect_Menu::CSelect_Menu()
	: m_bMouseAttach(false)
	, m_bCreated(false)
	, m_pPanel(nullptr)
	, m_pResume(nullptr)
	, m_pQuit(nullptr)
{
}


CSelect_Menu::~CSelect_Menu()
{
}

void CSelect_Menu::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(619.f, 160.f));
	if (!m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x, GetPos().y - 10.f));
		SetSize(Vec2(117, 114));
		m_bMouseAttach = true;
	}
}

void CSelect_Menu::MouseOff()
{
	SetTexPos(Vec2(781.f, 177.f));
	if (m_bMouseAttach)
	{
		SetPos(Vec2(GetPos().x, GetPos().y + 10.f));
		SetSize(Vec2(94, 95));
		m_bMouseAttach = false;
	}
}

void CSelect_Menu::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

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


void CSelect_Menu::CreateSubMenu()
{
	//패널 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"OptionsMaterial.bmp", L"Texture\\OptionsMaterial.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ 358.f,268.f });
	pObj->SetTexPos(Vec2(5.f, 70.f));
	pObj->SetObjType(OBJ_TYPE::ELDER_PANEL);
	m_pPanel = pObj;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pObj, OBJ_TYPE::ELDER_PANEL);

	//버튼생성
	pTex = CResMgr::GetInst()->FindTexture(L"OptionsMaterial.bmp");
	CUI* pResume = new CSelect_Resume;
	pResume->SetTexture(pTex);
	pResume->SetSize(Vec2{ 94.f, 35.f });
	pResume->SetPos(Vec2{ float(WINSIZE_X / 2 +50.f), float(WINSIZE_Y / 2 ) });
	pResume->SetTexPos(Vec2(356.f, 161.f));
	pResume->SetFinalPos(pResume->GetPos());
	pResume->SetObjType(OBJ_TYPE::ELDER_UI);
	((CSelect_Resume*)pResume)->SetParnet(this);
	m_pResume = pResume;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pResume, OBJ_TYPE::ELDER_UI);

	pTex = CResMgr::GetInst()->FindTexture(L"OptionsMaterial.bmp");
	CUI* pQuit = new CSelect_Quit;
	pQuit->SetTexture(pTex);
	pQuit->SetSize(Vec2{ 94.f, 35.f });
	pQuit->SetPos(Vec2{ float(WINSIZE_X / 2 -50.f), float(WINSIZE_Y / 2) });
	pQuit->SetTexPos(Vec2(356.f, 232.f));
	pQuit->SetFinalPos(pQuit->GetPos());
	pQuit->SetObjType(OBJ_TYPE::ELDER_UI);
	m_pQuit = pQuit;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pQuit, OBJ_TYPE::ELDER_UI);
}
