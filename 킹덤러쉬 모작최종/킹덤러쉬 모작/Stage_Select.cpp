#include "stdafx.h"
#include "Stage_Select.h"
#include "Obj.h"
#include "Texture.h"
#include "UI.h"
#include "Select_Menu.h"
#include "CSelect_HeroMenu.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Select_EnterStage.h"
#include "MapMgr.h"
#include "SoundMgr.h"

CStage_Select::CStage_Select()
	:m_iMaxStage(1)
{
}


CStage_Select::~CStage_Select()
{
}


void CStage_Select::Enter()
{
	//배경 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Mainbg.bmp", L"Texture\\Mainbg.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	pObj->SetObjType(OBJ_TYPE::BACKGROUND);
	AddObject(pObj, OBJ_TYPE::BACKGROUND);

	//세팅버튼생성
	pTex = CResMgr::GetInst()->LoadTexture(L"Quickmenu.bmp", L"Texture\\Quickmenu.bmp");
	CUI* pStart = new CSelect_Menu;
	pStart->SetTexture(pTex);
	pStart->SetSize(Vec2{ 94.f, 95.f});
	pStart->SetPos(Vec2{ float(WINSIZE_X / 2 - 325.f), float(WINSIZE_Y / 2 - 300.f)});
	pStart->SetTexPos(Vec2(781.f, 177.f));
	pStart->SetFinalPos(pStart->GetPos());
	pStart->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pStart, OBJ_TYPE::UI);

	//영웅선택 버튼생성
	pTex = CResMgr::GetInst()->LoadTexture(L"HeroRoom.bmp", L"Texture\\HeroRoom.bmp");
	CUI* phero = new CSelect_HeroMenu;
	phero->SetTexture(pTex);
	phero->SetSize(Vec2{ 160.f, 160.f });
	phero->SetPos(Vec2{ float(WINSIZE_X / 2 + 325.f), float(WINSIZE_Y / 2 + 300.f) });
	phero->SetTexPos(Vec2(1179.f, 729.f));
	phero->SetFinalPos(phero->GetPos());
	phero->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(phero, OBJ_TYPE::UI);


	CreateSelectStageUI();

	//사운드 생성
	CSoundMgr::GetInst()->LoadSound(L"BGM_SelectStage.wav", L"BGM_SelectStage.wav");
	//CSoundMgr::GetInst()->Play();
	CSoundMgr::GetInst()->PlayBGM(L"BGM_SelectStage.wav");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}

void CStage_Select::Exit()
{
	this->ClearObject();
}

void CStage_Select::update()
{
	CStage::update();
}

void CStage_Select::render(HDC _hdc)
{
	CStage::render(_hdc);
}


void CStage_Select::CreateSelectStageUI()
{
	//스테이지 진입버튼 초기에는 1스테이지만 보이고 나머지는 보이지않는다.
	//클리어시에 클리어 변수 트루로 바꾼다. 이전스테이지 클리어시 다음스테이지가 보인다.
	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
	CUI* pStage1 = new CSelect_EnterStage;
	pStage1->SetTexture(pTex);
	pStage1->SetPos(Vec2{ float(WINSIZE_X / 2 -100.f), float(WINSIZE_Y / 2) });
	pStage1->SetFinalPos(pStage1->GetPos());
	((CSelect_EnterStage*)pStage1)->SetStageNum(1);
	((CSelect_EnterStage*)pStage1)->SetClear(CMapMgr::GetInst()->GetClear(1));
	pStage1->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pStage1, OBJ_TYPE::UI);

	pTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
	CUI* pStage2 = new CSelect_EnterStage;
	pStage2->SetTexture(pTex);
	pStage2->SetPos(Vec2{ float(WINSIZE_X / 2 - 50.f), float(WINSIZE_Y / 2) });
	pStage2->SetSize(Vec2{ 66.f, 87.f });
	pStage2->SetFinalPos(pStage2->GetPos());
	((CSelect_EnterStage*)pStage2)->SetStageNum(2);
	((CObj*)pStage2)->SetEnable(CMapMgr::GetInst()->GetClear(1));
	((CSelect_EnterStage*)pStage2)->SetClear(CMapMgr::GetInst()->GetClear(2));
	pStage2->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pStage2, OBJ_TYPE::UI);

	pTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
	CUI* pStage3 = new CSelect_EnterStage;
	pStage3->SetTexture(pTex);
	pStage3->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pStage3->SetSize(Vec2{ 66.f, 87.f });
	pStage3->SetFinalPos(pStage3->GetPos());
	((CSelect_EnterStage*)pStage3)->SetStageNum(3);
	((CObj*)pStage3)->SetEnable(CMapMgr::GetInst()->GetClear(2));
	((CSelect_EnterStage*)pStage3)->SetClear(CMapMgr::GetInst()->GetClear(3));
	pStage3->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pStage3, OBJ_TYPE::UI);
}
