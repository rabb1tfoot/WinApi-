#include "stdafx.h"
#include "HeroFace_None.h"
#include "MapMgr.h"
#include "SoundMgr.h"
#include "CSelect_HeroMenu.h"


CHeroFace_None::CHeroFace_None()
	:CUI()
{
}


CHeroFace_None::~CHeroFace_None()
{
}

void CHeroFace_None::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CMapMgr::GetInst()->SetHero(HERO_TYPE::HERO_NONE);
	m_ParentMenu->GetCheck()->SetPos(Vec2{ float(WINSIZE_X / 2 + 225.f - 360.f), float(WINSIZE_Y / 2 - 180.f) });

}