#include "stdafx.h"
#include "HeroFace_Hammer.h"
#include "MapMgr.h"
#include "SoundMgr.h"
#include "CSelect_HeroMenu.h"


CHeroFace_Hammer::CHeroFace_Hammer()
	:CUI()
{
}


CHeroFace_Hammer::~CHeroFace_Hammer()
{
}


void CHeroFace_Hammer::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CMapMgr::GetInst()->SetHero(HERO_TYPE::HERO_HAMMER);
	m_ParentMenu->GetCheck()->SetPos(Vec2{ float(WINSIZE_X / 2 + 150.f - 360.f), float(WINSIZE_Y / 2 - 180.f) });
}
