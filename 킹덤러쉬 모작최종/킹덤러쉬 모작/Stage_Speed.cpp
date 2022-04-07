#include "stdafx.h"
#include "Stage_Speed.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

CStage_Speed::CStage_Speed()
	:m_bDouble(false)
{
}


CStage_Speed::~CStage_Speed()
{
}

void CStage_Speed::MouseOn(Vec2 _vMousePos)
{
	if (!m_bDouble)
	{
		SetTexPos(Vec2(197.f, 342.f));
	}
	else
	{
		SetTexPos(Vec2(346.f, 342.f));
	}
}

void CStage_Speed::MouseOff()
{
	if (!m_bDouble)
	{
		SetTexPos(Vec2(122.f, 342.f));
	}
	else
	{
		SetTexPos(Vec2(272.f, 342.f));
	}
}

void CStage_Speed::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	if (!m_bDouble)
	{
		m_bDouble = true;
		CTimeMgr::GetInst()->SetDouble(true);
	}
	else
	{
		m_bDouble = false;
		CTimeMgr::GetInst()->SetDouble(false);
	}
}
