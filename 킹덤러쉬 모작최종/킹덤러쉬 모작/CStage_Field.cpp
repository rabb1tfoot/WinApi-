#include "stdafx.h"
#include "CStage_Field.h"
#include "Test.h"
#include "Obj.h"
#include "Animator.h"
#include "KeyMgr.h"
#include "Texture.h"
#include "UI.h"
#include "Building.h"
#include "Goblin.h"
#include "Unit.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "Obj_Coll.h"
#include "Soldier.h"
#include "Magician.h"
#include "Ranger.h"
#include "MapMgr.h"
#include "Wave.h"
#include "StageMgr.h"
#include "Stage_Pause.h"
#include "Stage_Speed.h"
#include "SoundMgr.h"

CStage_Field::CStage_Field()
{
}


CStage_Field::~CStage_Field()
{
	Exit();
}


void CStage_Field::update()
{
	CStage::update();
	int Gold = CMapMgr::GetInst()->GetGold(); 
	int Life = CMapMgr::GetInst()->GetLife(); 
	int CurWave = CMapMgr::GetInst()->GetCurrentWave();
	int MaxWave = CMapMgr::GetInst()->GetMaxWave(); 

	wsprintf(m_wWave, L"wave:%d / %d", CurWave, MaxWave);
	wsprintf(m_wGold, L"%d", Gold);
	wsprintf(m_wLife, L"%d", Life);

	m_iLifeArrSize = FindDigitSize(Life);
	m_iGoldArrSize = FindDigitSize(Gold);
	m_iWaveArrSize = FindDigitSize(CurWave) + FindDigitSize(MaxWave) + 8;
}

void CStage_Field::render(HDC _hdc)
{
	CStage::render(_hdc);
	//if (!m_myWave->GetStageFail())
	//{
		//바탕색:검은색 폰트크기:18 폰트색:흰색
		HFONT font = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"궁서");
		SetTextColor(_hdc, RGB(255, 255, 255));
		SetBkColor(_hdc, RGB(0, 0, 0));
		SetBkMode(_hdc, TRANSPARENT);
		HFONT oldfont = (HFONT)SelectObject(_hdc, font);
		TextOut(_hdc, 80, 26, m_wLife, m_iLifeArrSize);
		TextOut(_hdc, 300, 26, m_wWave, m_iWaveArrSize);
		TextOut(_hdc, 160, 26, m_wGold, m_iGoldArrSize);

		SelectObject(_hdc, oldfont);
		DeleteObject(font);
	//}
}


void CStage_Field::Enter()
{
	////배경 생성
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Stage1bg.bmp", L"Texture\\Stage1bg.bmp");
	//
	//CObj* pObj = new CObj;
	//pObj->SetTexture(pTex);
	//pObj->SetPos(Vec2{ float(WINSIZE_X /2), float(WINSIZE_Y / 2) });
	//pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	//pObj->SetObjType(OBJ_TYPE::BACKGROUND);

	//AddObject(pObj, OBJ_TYPE::BACKGROUND);
	LoadingTex();
	this->InitRoute();
	InitHud();
	Init();
	//CMapMgr::GetInst()->LoadMap(L"stage1_6");

	CMapMgr::GetInst()->CreateHero();

	//사운드 생성
	CSoundMgr::GetInst()->LoadSound(L"BGM_BattleStage.wav", L"BGM_BattleStage.wav");
	//CSoundMgr::GetInst()->Play();
	CSoundMgr::GetInst()->PlayBGM(L"BGM_BattleStage.wav");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	//collision 그룹 지정
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ALLY_UNIT, OBJ_TYPE::ENEMY_UNIT_RANGE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ENEMY_UNIT, OBJ_TYPE::ALLY_UNIT_RANGE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ENEMY_UNIT, OBJ_TYPE::ALLY_UNIT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ALLY_UNIT, OBJ_TYPE::ENEMY_UNIT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ALLY_HERO, OBJ_TYPE::ENEMY_UNIT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ALLY_HERO, OBJ_TYPE::ENEMY_UNIT_RANGE);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ENEMY_UNIT, OBJ_TYPE::ALLY_HERO);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ALLY_UNIT_IGNORE, OBJ_TYPE::ENEMY_UNIT);
	CCollisionMgr::GetInst()->CollisionCheck(OBJ_TYPE::ATT_OBJECT, OBJ_TYPE::ENEMY_UNIT);

}

void CStage_Field::Exit()
{
	this->ClearObject();
	m_vRoute.clear();
}


void CStage_Field::LoadingTex()
{
	CResMgr::GetInst()->LoadTexture(L"Archer.bmp", L"Texture\\Archer.bmp");
	CResMgr::GetInst()->LoadTexture(L"Mage.bmp", L"Texture\\Mage.bmp");
	CResMgr::GetInst()->LoadTexture(L"Quickmenu.bmp", L"Texture\\Quickmenu.bmp");
	CResMgr::GetInst()->LoadTexture(L"Artillery.bmp", L"Texture\\Artillery.bmp");
	CResMgr::GetInst()->LoadTexture(L"Barracks.bmp", L"Texture\\Barracks.bmp");
	CResMgr::GetInst()->LoadTexture(L"OptionsMaterial.bmp", L"Texture\\OptionsMaterial.bmp");
}



void CStage_Field::InitHud()
{

	//테스트 웨이브HUD생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Quickmenu.bmp", L"Texture\\Quickmenu.bmp");
	//CUI* CWaveUI = new CWave;
	//CWaveUI->SetTexture(pTex);
	//CWaveUI->SetObjType(OBJ_TYPE::UI);
	//CWaveUI->SetPos(Vec2(WINSIZE_X / 2.f - 30, 30.f));
	//CWaveUI->SetFinalPos(CWaveUI->GetPos());
	//CWaveUI->SetSize(Vec2(71.f, 70.f));
	//CWaveUI->SetTexPos(Vec2(463, 35));
	//((CWave*)CWaveUI)->SetStartPoint(Vec2( 500.f, 50.f ));
	//((CWave*)CWaveUI)->SetStageNum(1);
	//CWaveUI->SetEnable(true);
	//((CWave*)CWaveUI)->AddWave(1, MONSTER_TYPE::GOBLIN, 2);
	//((CWave*)CWaveUI)->AddWave(2, MONSTER_TYPE::BANDIT, 6);
	//AddObject(CWaveUI, OBJ_TYPE::UI);
	//m_myWave = (CWave*)CWaveUI;

	//정보 페널 생성
	pTex = CResMgr::GetInst()->LoadTexture(L"HUD.bmp", L"Texture\\HUD.bmp");
	CUI* InfoHUD = new CUI;
	InfoHUD->SetTexture(pTex);
	InfoHUD->SetObjType(OBJ_TYPE::UI);
	InfoHUD->SetPos(Vec2(WINSIZE_X / 2.f - 300.f, 30.f));
	InfoHUD->SetFinalPos(InfoHUD->GetPos());
	InfoHUD->SetSize(Vec2(446.f, 68.f));
	InfoHUD->SetTexPos(Vec2(18, 728));
	AddObject(InfoHUD, OBJ_TYPE::UI);

	//퍼즈 버튼
	pTex = CResMgr::GetInst()->LoadTexture(L"OptionsMaterial.bmp", L"Texture\\OptionsMaterial.bmp");
	CUI* pPause = new CStage_Pause;
	pPause->SetTexture(pTex);
	pPause->SetSize(Vec2{ 61, 53 });
	pPause->SetPos(Vec2(WINSIZE_X / 2.f + 60.f, 30.f));
	pPause->SetTexPos(Vec2(324.f, 14.f));
	pPause->SetFinalPos(pPause->GetPos());
	pPause->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pPause, OBJ_TYPE::UI);

	//2배속 버튼
	pTex = CResMgr::GetInst()->FindTexture(L"OptionsMaterial.bmp");
	CUI* pDouble = new CStage_Speed;
	pDouble->SetTexture(pTex);
	pDouble->SetSize(Vec2{ 60, 55 });
	pDouble->SetPos(Vec2(WINSIZE_X / 2.f + 130.f, 30.f));
	pDouble->SetTexPos(Vec2(122.f, 342.f));
	pDouble->SetFinalPos(pDouble->GetPos());
	pDouble->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pDouble, OBJ_TYPE::UI);


}

void CStage_Field::InitRoute()
{
	m_vRoute.push_back(Vec2(500, 288));
	m_vRoute.push_back(Vec2(326, 345));
	m_vRoute.push_back(Vec2(343, 516));
	m_vRoute.push_back(Vec2(706, 530));
	m_vRoute.push_back(Vec2(706, 460));
	m_vRoute.push_back(Vec2(1000, 430));

	CMapMgr::GetInst()->AddRoute(Vec2(500, 288));
	CMapMgr::GetInst()->AddRoute(Vec2(326, 345));
	CMapMgr::GetInst()->AddRoute(Vec2(343, 516));
	CMapMgr::GetInst()->AddRoute(Vec2(706, 530));
	CMapMgr::GetInst()->AddRoute(Vec2(706, 460));
	CMapMgr::GetInst()->AddRoute(Vec2(1000, 430));
}

void CStage_Field::Init()
{
	CMapMgr::GetInst()->SetGold(200);
	CMapMgr::GetInst()->SetLife(5);
	CMapMgr::GetInst()->SetMaxWave(2);
	CMapMgr::GetInst()->SetCurrentWave(0);

}

