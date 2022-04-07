#include "stdafx.h"
#include "Stage_Resume.h"
#include "Stage_Pause.h"
#include "App.h"


CStage_Resume::CStage_Resume()
	: m_bMouseAttach(false)
	, m_pParentMenu(nullptr)
{
}


CStage_Resume::~CStage_Resume()
{
}


void CStage_Resume::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(356.f, 127.f));
	if (!m_bMouseAttach)
	{
		m_bMouseAttach = true;
	}

}

void CStage_Resume::MouseOff()
{
	SetTexPos(Vec2(356.f, 161.f));
	if (m_bMouseAttach)
	{
		m_bMouseAttach = false;
	}

}

void CStage_Resume::MouseLbtnClicked(Vec2 _vMousePos)
{
	CApp::GetInst()->SetbPause(false);
	((CObj*)m_pParentMenu->GetQuit())->SetEnable(false);
	((CObj*)m_pParentMenu->GetResume())->SetEnable(false);
	m_pParentMenu->GetPanel()->SetEnable(false);
}
