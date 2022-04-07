#include "stdafx.h"
#include "StageMgr.h"
#include "CStage_Tool.h"
#include "Stage.h"
#include "CollisionMgr.h"
#include "TimeMgr.h"
#include "CStage_Field.h"
#include "CStage_Title.h"
#include "Stage_Select.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Stage_3.h"
#include "App.h"

CStageMgr::CStageMgr()
	: m_arrStage{}
	, m_pCurStage(nullptr)
	, m_eStageType(STAGE_TYPE::END)
{
}


CStageMgr::~CStageMgr()
{
	for (UINT i = 0; i < (UINT)STAGE_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrStage[i]);
	}
}

void CStageMgr::Init()
{
	m_arrStage[(UINT)STAGE_TYPE::TOOL] = new CStage_Tool;
	m_arrStage[(UINT)STAGE_TYPE::TEST] = new CStage_Field;
	m_arrStage[(UINT)STAGE_TYPE::TITLE] = new CStage_Title;
	m_arrStage[(UINT)STAGE_TYPE::SELECT] = new CStage_Select;
	m_arrStage[(UINT)STAGE_TYPE::STAGE_1] = new CStage_1;
	m_arrStage[(UINT)STAGE_TYPE::STAGE_2] = new CStage_2;
	m_arrStage[(UINT)STAGE_TYPE::STAGE_3] = new CStage_3;

	m_eStageType = STAGE_TYPE::TITLE;
	CApp::GetInst()->SetbMenu(false);
	CApp::GetInst()->SetWindowMenu();
	m_pCurStage = m_arrStage[(UINT)m_eStageType];

	m_pCurStage->Enter();
}

void CStageMgr::update()
{
	m_pCurStage->update();
	CCollisionMgr::GetInst()->update();
	m_pCurStage->eventUpdate();
}

void CStageMgr::render(HDC _hdc)
{
	m_pCurStage->render(_hdc);
}

void CStageMgr::ChangeStage(STAGE_TYPE _etype)
{
	// 현재 스테이지와 변경되려는 스테이지가 같은 경우
	assert(m_eStageType != _etype);

	m_pCurStage->Exit();

	m_eStageType = _etype;
	m_pCurStage = m_arrStage[(UINT)m_eStageType];

	m_pCurStage->Enter();
}
