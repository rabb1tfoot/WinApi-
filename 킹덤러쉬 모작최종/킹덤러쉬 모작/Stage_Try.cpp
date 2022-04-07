#include "stdafx.h"
#include "Stage_Try.h"
#include "Stage.h"
#include "StageMgr.h"
#include "SoundMgr.h"


CStage_Try::CStage_Try()
{
}


CStage_Try::~CStage_Try()
{
}

void CStage_Try::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(243.f, 433.f));
}

void CStage_Try::MouseOff()
{
	SetTexPos(Vec2(544.f, 297.f));
}

void CStage_Try::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	CStageMgr::GetInst()->GetCurStage()->Exit();
	CStageMgr::GetInst()->GetCurStage()->Enter();
}
