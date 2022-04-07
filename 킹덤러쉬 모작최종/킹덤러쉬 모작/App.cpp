#include "stdafx.h"
#include "App.h"
#include "Resmgr.h"
#include "PathMgr.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "StageMgr.h"
#include "KeyMgr.h"
#include "CUIMgr.h"
#include "CollisionMgr.h"
#include "MapMgr.h"
#include "SoundMgr.h"


CApp::CApp()
	: m_bMenu(true)
	, m_hWnd(nullptr)
	, m_hdc(nullptr)
	, m_pMemTex(nullptr)
	, m_bGameOver(false)
	, m_bPause(false)
{
}

CApp::~CApp()
{
	ReleaseDC(m_hWnd, m_hdc);
}

void CApp::init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);

	SetbMenu(m_bMenu);

	//memdc 텍스쳐생성
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"MemTex", WINSIZE_X, WINSIZE_Y);

	//메니저 초기화
	CPathMgr::Init();
	CSoundMgr::GetInst()->init();
	CTimeMgr::GetInst()->Init();
	CStageMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CMapMgr::GetInst()->Init();
}

int CApp::progress()
{
	update();
	render();

	return SUCCESS;
}

void CApp::SetbMenu(bool _menu)
{
	m_bMenu = _menu;
	SetWindowMenu();
}

void CApp::SetWindowMenu()
{
	RECT rt = {};
	rt.top = 0;
	rt.left = 0;
	rt.right = WINSIZE_X;
	rt.bottom = WINSIZE_Y;

	if(m_bMenu)
		SetMenu(m_hWnd, GetMenu(m_hWnd));
	else
		SetMenu(m_hWnd, NULL);
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, m_bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right, rt.bottom, 0);
}

void CApp::update()
{
	CTimeMgr::GetInst()->update();
	//다른윈도우가 최상위 혹은 퍼즈시 멈춘다.
	if (GetActiveWindow() != m_hWnd)
		return;
	CKeyMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();
	CUIMgr::GetInst()->update();
	if (m_bGameOver || m_bPause)
		return;
	CStageMgr::GetInst()->update();
	CSoundMgr::GetInst()->update();
}

void CApp::render()
{
	if (m_bGameOver)
		return;
	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_pMemTex->GetDC(), GetStockObject(BLACK_BRUSH));
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZE_X + 1, WINSIZE_Y + 1);
	SelectObject(m_pMemTex->GetDC(), hOldBrush);

	// 물체 렌더링
	CStageMgr::GetInst()->render(m_pMemTex->GetDC());
	if (STAGE_TYPE::TOOL == CStageMgr::GetInst()->GetCurStageType())
	{
		CTimeMgr::GetInst()->render(m_pMemTex->GetDC());
		CKeyMgr::GetInst()->render(m_pMemTex->GetDC());
	}

	// Main Window 로 장면 옮기기
	BitBlt(m_hdc
		, 0, 0
		, WINSIZE_X, WINSIZE_Y
		, m_pMemTex->GetDC()
		, 0, 0
		, SRCCOPY);
}