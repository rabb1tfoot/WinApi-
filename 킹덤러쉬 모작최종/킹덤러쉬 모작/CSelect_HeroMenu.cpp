#include "stdafx.h"
#include "CSelect_HeroMenu.h"
#include "ResMgr.h"
#include "Texture.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Select_Resume.h"
#include "Select_HeroDone.h"
#include "HeroFace_Hammer.h"
#include "HeroFace_Light.h"
#include "HeroFace_None.h"
#include "MapMgr.h"
#include "SoundMgr.h"

CSelect_HeroMenu::CSelect_HeroMenu()
	: m_bMouseAttach(false)
	, m_bCreated(false)
	, m_pPanel(nullptr)
	, m_pResume(nullptr)
{
	for (UINT i = 0; i < (UINT)HERO_TYPE::HERO_NONE; ++i)
	{
		m_HeroFace[i] = nullptr;
	}
}


CSelect_HeroMenu::~CSelect_HeroMenu()
{
}

void CSelect_HeroMenu::update()
{
	//if (nullptr == m_check)
	//{
	//	return;
	//}
	//if (HERO_TYPE::HERO_HAMMER == CMapMgr::GetInst()->GetHero())
	//{
	//	m_check->SetPos(Vec2{ float(WINSIZE_X / 2 + 150.f - 360.f), float(WINSIZE_Y / 2 - 180.f) });
	//}
	//else if (HERO_TYPE::HERO_LIGHT == CMapMgr::GetInst()->GetHero())
	//{
	//	m_check->SetPos(Vec2{ float(WINSIZE_X / 2 + 75.f - 360.f), float(WINSIZE_Y / 2 - 180.f) });
	//}
	//else if(HERO_TYPE::HERO_NONE == CMapMgr::GetInst()->GetHero())
	//{
	//	m_check->SetPos(Vec2{ float(WINSIZE_X / 2 + 225.f - 360.f), float(WINSIZE_Y / 2 - 180.f) });
	//}
}

void CSelect_HeroMenu::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(1183.f, 537.f));
	if (!m_bMouseAttach)
	{
		m_bMouseAttach = true;
		SetFinalPos(Vec2(GetPos().x, GetPos().y - 20.f));
		SetPos(Vec2(GetPos().x, GetPos().y - 20.f));
		SetSize(Vec2{ 160.f, 190.f });
	}
}

void CSelect_HeroMenu::MouseOff()
{
	SetTexPos(Vec2(1179.f, 729.f));
	if (m_bMouseAttach)
	{
		m_bMouseAttach = false;
		SetFinalPos(Vec2(GetPos().x, GetPos().y + 20.f));
		SetPos(Vec2(GetPos().x, GetPos().y + 20.f));
		SetSize(Vec2{ 160.f, 160.f });
	}
}

void CSelect_HeroMenu::MouseLbtnClicked(Vec2 _vMousePos)
{
	//瓤苞澜 积己
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
		m_check->SetEnable(true);
		m_pPanel->SetEnable(true);
		m_HeroFace[(UINT)HERO_TYPE::HERO_LIGHT]->SetEnable(true);
		m_HeroFace[(UINT)HERO_TYPE::HERO_HAMMER]->SetEnable(true);
		m_HeroFace[(UINT)HERO_TYPE::HERO_NONE]->SetEnable(true);

	}
}


void CSelect_HeroMenu::CreateSubMenu()
{
	//菩澄 积己
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"OptionsMaterial.bmp", L"Texture\\OptionsMaterial.bmp");
	pTex = CResMgr::GetInst()->LoadTexture(L"HeroRoom.bmp", L"Texture\\HeroRoom.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ 852.f,735.f });
	pObj->SetTexPos(Vec2(1.f, 289.f));
	pObj->SetObjType(OBJ_TYPE::ELDER_PANEL);
	m_pPanel = pObj;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pObj, OBJ_TYPE::ELDER_PANEL);

	//滚瓢积己
	pTex = CResMgr::GetInst()->FindTexture(L"HeroRoom.bmp");
	CUI* pResume = new CSelect_Resume;
	pResume->SetTexture(pTex);
	pResume->SetSize(Vec2{ 130.f, 67.f });
	pResume->SetPos(Vec2{ float(WINSIZE_X / 2 + 250.f), float(WINSIZE_Y / 2 + 250.f) });
	pResume->SetTexPos(Vec2(858.f, 514.f));
	pResume->SetFinalPos(pResume->GetPos());
	pResume->SetObjType(OBJ_TYPE::ELDER_UI);
	((CSelect_Resume*)pResume)->SetParnet(this);
	m_pResume = pResume;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pResume, OBJ_TYPE::ELDER_UI);

	//檬惑拳 积己
	CUI* pHammer = new CHeroFace_Hammer;
	pHammer->SetTexture(pTex);
	pHammer->SetSize(Vec2{ 70.f, 70.f });
	pHammer->SetPos(Vec2{ float(WINSIZE_X / 2 + 150.f -360.f), float(WINSIZE_Y / 2 - 180.f)});
	pHammer->SetTexPos(Vec2(860.f, 369.f));
	pHammer->SetFinalPos(pHammer->GetPos());
	pHammer->SetObjType(OBJ_TYPE::ELDER_UI);
	((CHeroFace_Hammer*)pHammer)->SetParentMenu(this);
	m_HeroFace[(UINT)HERO_TYPE::HERO_HAMMER] = pHammer;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pHammer, OBJ_TYPE::ELDER_UI);

	CUI* pLight = new CHeroFace_light;
	pLight->SetTexture(pTex);
	pLight->SetSize(Vec2{ 70.f, 70.f });
	pLight->SetPos(Vec2{ float(WINSIZE_X / 2 + 75.f -360.f), float(WINSIZE_Y / 2 - 180.f) });
	pLight->SetTexPos(Vec2(930.f, 150.f));
	pLight->SetFinalPos(pLight->GetPos());
	pLight->SetObjType(OBJ_TYPE::ELDER_UI);
	((CHeroFace_light*)pLight)->SetParentMenu(this);
	m_HeroFace[(UINT)HERO_TYPE::HERO_LIGHT] = pLight;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pLight, OBJ_TYPE::ELDER_UI);

	CUI* pNone = new CHeroFace_None;
	pNone->SetTexture(pTex);
	pNone->SetSize(Vec2{ 70.f, 70.f });
	pNone->SetPos(Vec2{ float(WINSIZE_X / 2 + 225.f -360.f), float(WINSIZE_Y / 2 - 180.f) });
	pNone->SetTexPos(Vec2(930.f, 77.f));
	pNone->SetFinalPos(pNone->GetPos());
	pNone->SetObjType(OBJ_TYPE::ELDER_UI);
	((CHeroFace_None*)pNone)->SetParentMenu(this);
	m_HeroFace[(UINT)HERO_TYPE::HERO_NONE] = pNone;
	CStageMgr::GetInst()->GetCurStage()->AddObject(pNone, OBJ_TYPE::ELDER_UI);

	//眉农酒捞能 积己
	CTexture* cTex = CResMgr::GetInst()->FindTexture(L"HeroRoom.bmp");
	CObj* check = new CObj;
	check->SetPos(Vec2(float(WINSIZE_X / 2 + 225.f -360.f), float(WINSIZE_Y / 2 - 180.f)));
	check->SetObjType(OBJ_TYPE::MAP_INGREDIENT);
	check->SetTexture(cTex);
	check->SetEnable(true);
	check->SetTexPos(Vec2(1.f, 3.f));
	check->SetSize(Vec2(21.f, 23.f));
	m_check = check;

	CStageMgr::GetInst()->GetCurStage()->AddObject(check, OBJ_TYPE::MAP_INGREDIENT);
}
