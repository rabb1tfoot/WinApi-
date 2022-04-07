#include "stdafx.h"
#include "Select_Resume.h"
#include "Select_Menu.h"
#include "CSelect_HeroMenu.h"
#include "Obj.h"
#include "SoundMgr.h"


CSelect_Resume::CSelect_Resume()
	: m_bMouseAttach(false)
	, m_pParentMenu(nullptr)
	, m_pParentMenu2(nullptr)
{
}


CSelect_Resume::~CSelect_Resume()
{
}

void CSelect_Resume::MouseOn(Vec2 _vMousePos)
{
	if (nullptr == m_pParentMenu2)
	{
		SetTexPos(Vec2(356.f, 126.f));
		if (!m_bMouseAttach)
		{
			m_bMouseAttach = true;
		}
	}
	else if (nullptr == m_pParentMenu)
	{
		CUI::MouseOn(_vMousePos);
		SetTexPos(Vec2(858.f, 581.f));
		if (!m_bMouseAttach)
		{
			m_bMouseAttach = true;
		}
	}
}

void CSelect_Resume::MouseOff()
{
	if (nullptr == m_pParentMenu2)
	{
		SetTexPos(Vec2(356.f, 161.f));
		if (m_bMouseAttach)
		{
			m_bMouseAttach = false;
		}
	}
	else if (nullptr == m_pParentMenu)
	{
		CUI::MouseOff();
		SetTexPos(Vec2(858.f, 514.f));
		if (m_bMouseAttach)
		{
			m_bMouseAttach = false;
		}
	}
}

void CSelect_Resume::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	if (nullptr == m_pParentMenu2)
	{
		((CObj*)m_pParentMenu->GetQuit())->SetEnable(false);
		((CObj*)m_pParentMenu->GetResume())->SetEnable(false);
		m_pParentMenu->GetPanel()->SetEnable(false);

	}
	else if(nullptr == m_pParentMenu)
	{
		CUI::MouseOff();
		((CObj*)m_pParentMenu2->GetResume())->SetEnable(false);
		m_pParentMenu2->GetPanel()->SetEnable(false);
		m_pParentMenu2->GetCheck()->SetEnable(false);
		m_pParentMenu2->GetHeroFace()[HERO_TYPE::HERO_NONE]->SetEnable(false);
		m_pParentMenu2->GetHeroFace()[HERO_TYPE::HERO_LIGHT]->SetEnable(false);
		m_pParentMenu2->GetHeroFace()[HERO_TYPE::HERO_HAMMER]->SetEnable(false);
	}
}
