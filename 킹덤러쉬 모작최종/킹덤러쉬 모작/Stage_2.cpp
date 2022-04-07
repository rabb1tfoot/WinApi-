#include "stdafx.h"
#include "Stage_2.h"
#include "Obj.h"
#include "Texture.h"
#include "MapMgr.h"
#include "UI.h"
#include "Wave.h"


CStage_2::CStage_2()
{
}


CStage_2::~CStage_2()
{
	Exit();
}


void CStage_2::update()
{
	CStage_Field::update();
}

void CStage_2::render(HDC _hdc)
{
	CStage::render(_hdc);
	if (!m_myWave->GetStageEnd())
	{
		CStage_Field::render(_hdc);
	}
}

void CStage_2::Enter()
{
	//배경 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Stage2bg.bmp", L"Texture\\Stage2bg.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	pObj->SetObjType(OBJ_TYPE::BACKGROUND);

	AddObject(pObj, OBJ_TYPE::BACKGROUND);
	CStage_Field::Enter();
	CMapMgr::GetInst()->LoadMap(L"stage2_1");
}

void CStage_2::Exit()
{
	CStage_Field::Exit();
}

void CStage_2::InitHud()
{
	//텍스트 웨이브는 스테이지마다 다르다
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Quickmenu.bmp", L"Texture\\Quickmenu.bmp");
	CUI* CWaveUI = new CWave;
	CWaveUI->SetTexture(pTex);
	CWaveUI->SetObjType(OBJ_TYPE::UI);
	CWaveUI->SetPos(Vec2(992.f, 217.f));//CWaveUI->SetPos(Vec2(WINSIZE_X / 2.f - 30, 30.f));
	CWaveUI->SetFinalPos(CWaveUI->GetPos());
	CWaveUI->SetSize(Vec2(71.f, 70.f));
	CWaveUI->SetTexPos(Vec2(463, 35));
	((CWave*)CWaveUI)->SetStartPoint(Vec2(1000.f, 215.f));
	((CWave*)CWaveUI)->SetStageNum(2);
	CWaveUI->SetEnable(true);
	((CWave*)CWaveUI)->AddWave(1, MONSTER_TYPE::BANDIT, 2);
	((CWave*)CWaveUI)->AddWave(2, MONSTER_TYPE::OGRE, 1);
	((CWave*)CWaveUI)->AddWave(3, MONSTER_TYPE::GOBLIN, 3);
	((CWave*)CWaveUI)->AddWave(3, MONSTER_TYPE::BANDIT, 2);
	((CWave*)CWaveUI)->AddWave(3, MONSTER_TYPE::OGRE, 1);
	AddObject(CWaveUI, OBJ_TYPE::UI);
	m_myWave = (CWave*)CWaveUI;
	CStage_Field::InitHud();
}

void CStage_2::InitRoute()
{
	m_vRoute.push_back(Vec2(675, 261));
	m_vRoute.push_back(Vec2(620, 106));
	m_vRoute.push_back(Vec2(537, 106));
	m_vRoute.push_back(Vec2(515, 268));
	m_vRoute.push_back(Vec2(344, 290));
	m_vRoute.push_back(Vec2(370, 432));
	m_vRoute.push_back(Vec2(590, 403));
	m_vRoute.push_back(Vec2(600, 550));
	m_vRoute.push_back(Vec2(484, 569));
	m_vRoute.push_back(Vec2(470, 742));

	CMapMgr::GetInst()->DeleteRoute();
	CMapMgr::GetInst()->AddRoute(Vec2(675, 261));
	CMapMgr::GetInst()->AddRoute(Vec2(620, 106));
	CMapMgr::GetInst()->AddRoute(Vec2(537, 106));
	CMapMgr::GetInst()->AddRoute(Vec2(515, 268));
	CMapMgr::GetInst()->AddRoute(Vec2(344, 290));
	CMapMgr::GetInst()->AddRoute(Vec2(370, 432));
	CMapMgr::GetInst()->AddRoute(Vec2(590, 403));
	CMapMgr::GetInst()->AddRoute(Vec2(600, 550));
	CMapMgr::GetInst()->AddRoute(Vec2(484, 569));
	CMapMgr::GetInst()->AddRoute(Vec2(470, 742));

}

void CStage_2::Init()
{
	CMapMgr::GetInst()->SetGold(200);
	CMapMgr::GetInst()->SetLife(5);
	CMapMgr::GetInst()->SetMaxWave(3);
	CMapMgr::GetInst()->SetCurrentWave(0);
}

void CStage_2::LoadingTex()
{
}
