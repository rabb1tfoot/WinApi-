#include "stdafx.h"
#include "CStage_Title.h"
#include "Obj.h"
#include "Texture.h"
#include "UI.h"
#include "Title_StartUI.h"
#include "Title_QuitUI.h"
#include "StageMgr.h"
#include "SoundMgr.h"

CStage_Title::CStage_Title()
{
}


CStage_Title::~CStage_Title()
{
}



void CStage_Title::Enter()
{
	//배경 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Title3.bmp", L"Texture\\Title3.bmp");

	CObj* pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
	pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	pObj->SetObjType(OBJ_TYPE::BACKGROUND);
	AddObject(pObj, OBJ_TYPE::BACKGROUND);

	pTex = CResMgr::GetInst()->LoadTexture(L"TitleIcon.bmp", L"Texture\\TitleIcon.bmp");
	pObj = new CObj;
	pObj->SetTexture(pTex);
	pObj->SetPos(Vec2{ float(WINSIZE_X / 2 - 200.f), float(WINSIZE_Y / 2 - 200.f) });
	pObj->SetSize(Vec2{ pTex->GetWidth(), pTex->GetHeight() });
	pObj->SetObjType(OBJ_TYPE::BACKGROUND);
	AddObject(pObj, OBJ_TYPE::BACKGROUND);

	//메뉴생성
	pTex = CResMgr::GetInst()->LoadTexture(L"MainMenuMaterial.bmp", L"Texture\\MainMenuMaterial.bmp");
	CObj* MainMenu = new CObj;
	MainMenu->SetTexture(pTex);
	MainMenu->SetPos(Vec2{ float(WINSIZE_X / 2 - 350.f), float(WINSIZE_Y / 2) + 200.f });
	MainMenu->SetSize(Vec2{ 308.f, 235.f });
	MainMenu->SetTexPos(Vec2(1.f, 305.f));
	MainMenu->SetObjType(OBJ_TYPE::BACKGROUND);
	AddObject(MainMenu, OBJ_TYPE::BACKGROUND);

	//버튼생성
	CUI* pStart = new CTitle_StartUI;
	pStart->SetTexture(pTex);
	pStart->SetSize(Vec2{ 162, 80 });
	pStart->SetPos(Vec2{ float(WINSIZE_X / 2 - 325.f), float(WINSIZE_Y / 2) + 170.f });
	pStart->SetTexPos(Vec2(717.f, 333.f));
	pStart->SetFinalPos(pStart->GetPos());
	pStart->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pStart, OBJ_TYPE::UI);

	CUI* pQuit = new CTitle_QuitUI;
	pQuit->SetTexture(pTex);
	pQuit->SetSize(Vec2{ 102, 79 });
	pQuit->SetPos(Vec2{ float(WINSIZE_X / 2 - 450.f), float(WINSIZE_Y / 2) + 270.f });
	pQuit->SetTexPos(Vec2(493.f, 140.f));
	pQuit->SetFinalPos(pQuit->GetPos());
	pQuit->SetObjType(OBJ_TYPE::UI);
	CStageMgr::GetInst()->GetCurStage()->AddObject(pQuit, OBJ_TYPE::UI);

	//사운드
	CSoundMgr::GetInst()->LoadSound(L"BGM_Title.wav", L"BGM_Title.wav");
	//CSoundMgr::GetInst()->Play();
	CSoundMgr::GetInst()->PlayBGM(L"BGM_Title.wav");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}

void CStage_Title::Exit()
{
	this->ClearObject();
}

void CStage_Title::update()
{
	CStage::update();
}

void CStage_Title::render(HDC _hdc)
{
	CStage::render(_hdc);
}
