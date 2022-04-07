#include "stdafx.h"
#include "Select_EnterStage.h"
#include "StageMgr.h"
#include "Stage.h"


CSelect_EnterStage::CSelect_EnterStage()
	: m_bIsClear(false)
	, m_iStageNum(-1)
{
}


CSelect_EnterStage::~CSelect_EnterStage()
{
}

void CSelect_EnterStage::Init()
{
	if (this->m_bIsClear)
	{
		this->SetSize(Vec2{ 60.f, 80.f });
		this->SetTexPos(Vec2(610.f, 350.f));
	}
	else
	{
		this->SetSize(Vec2{ 66.f, 87.f });
		this->SetTexPos(Vec2(545.f, 159.f));
	}
}


void CSelect_EnterStage::MouseOn(Vec2 _vMousePos)
{
	if (this->m_bIsClear)
	{
		this->SetSize(Vec2{ 66.f, 87.f });
		this->SetTexPos(Vec2(463.f, 163.f));
	}
	else
	{
		this->SetSize(Vec2{ 61.f, 84.f });
		this->SetTexPos(Vec2(535.f, 299.f));
	}
}

void CSelect_EnterStage::MouseOff()
{
	if (this->m_bIsClear)
	{
		this->SetSize(Vec2{ 60.f, 80.f });
		this->SetTexPos(Vec2(541.f, 161.f));
	}
	else
	{
		this->SetSize(Vec2{ 49.f, 82.f });
		this->SetTexPos(Vec2(621.f, 304.f));
	}
}

void CSelect_EnterStage::MouseLbtnClicked(Vec2 _vMousePos)
{
	//번호에 따라 스테이지로 이동
	switch (m_iStageNum)
	{
	case 1:
		CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::STAGE_1);
		break;
	case 2:
		CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::STAGE_2);
		break;
	case 3:
		CStageMgr::GetInst()->ChangeStage(STAGE_TYPE::STAGE_3);
		break;

	}
}
