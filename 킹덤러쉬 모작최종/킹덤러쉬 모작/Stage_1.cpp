#include "stdafx.h"
#include "Stage_1.h"
#include "MapMgr.h"
#include "Obj.h"
#include "Texture.h"
#include "wave.h"


CStage_1::CStage_1()
{
}


CStage_1::~CStage_1()
{
	Exit();
}



void CStage_1::update()
{
	CStage_Field::update();
}

void CStage_1::render(HDC _hdc)
{
	CStage::render(_hdc);
	if (!m_myWave->GetStageEnd())
	{
		CStage_Field::render(_hdc);
	}
}

void CStage_1::Enter()
{
	//배경 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Stage1bg.bmp", L"Texture\\Stage1bg.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	pObj->SetObjType(OBJ_TYPE::BACKGROUND);

	AddObject(pObj, OBJ_TYPE::BACKGROUND);
	CStage_Field::Enter();
	CMapMgr::GetInst()->LoadMap(L"stage1_6");
}

void CStage_1::Exit()
{
	CStage_Field::Exit();
}

void CStage_1::LoadingTex()
{
	CStage_Field::LoadingTex();
}

void CStage_1::InitHud()
{
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Quickmenu.bmp", L"Texture\\Quickmenu.bmp");
	CUI* CWaveUI = new CWave;
	CWaveUI->SetTexture(pTex);
	CWaveUI->SetObjType(OBJ_TYPE::UI);
	CWaveUI->SetPos(Vec2(WINSIZE_X / 2.f - 30, 30.f));
	CWaveUI->SetFinalPos(CWaveUI->GetPos());
	CWaveUI->SetSize(Vec2(71.f, 70.f));
	CWaveUI->SetTexPos(Vec2(463, 35));
	((CWave*)CWaveUI)->SetStartPoint(Vec2(500.f, 50.f));
	((CWave*)CWaveUI)->SetStageNum(1);
	CWaveUI->SetEnable(true);
	((CWave*)CWaveUI)->AddWave(1, MONSTER_TYPE::GOBLIN, 3);
	((CWave*)CWaveUI)->AddWave(2, MONSTER_TYPE::GOBLIN, 4);
	((CWave*)CWaveUI)->AddWave(3, MONSTER_TYPE::GOBLIN, 4);
	((CWave*)CWaveUI)->AddWave(4, MONSTER_TYPE::GOBLIN, 4);
	AddObject(CWaveUI, OBJ_TYPE::UI);
	m_myWave = (CWave*)CWaveUI;
	CStage_Field::InitHud();
}

void CStage_1::InitRoute()
{
	m_vRoute.push_back(Vec2(500, 288));
	m_vRoute.push_back(Vec2(326, 345));
	m_vRoute.push_back(Vec2(343, 516));
	m_vRoute.push_back(Vec2(706, 530));
	m_vRoute.push_back(Vec2(706, 460));
	m_vRoute.push_back(Vec2(1000, 430));

	CMapMgr::GetInst()->DeleteRoute();
	CMapMgr::GetInst()->AddRoute(Vec2(500, 288));
	CMapMgr::GetInst()->AddRoute(Vec2(326, 345));
	CMapMgr::GetInst()->AddRoute(Vec2(343, 516));
	CMapMgr::GetInst()->AddRoute(Vec2(706, 530));
	CMapMgr::GetInst()->AddRoute(Vec2(706, 460));
	CMapMgr::GetInst()->AddRoute(Vec2(1000, 430));
}

void CStage_1::Init()
{
	CMapMgr::GetInst()->SetGold(2000);
	CMapMgr::GetInst()->SetLife(200);
	CMapMgr::GetInst()->SetMaxWave(4);
	CMapMgr::GetInst()->SetCurrentWave(0);
}