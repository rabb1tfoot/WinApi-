#include "stdafx.h"
#include "KeyMgr.h"

#include "App.h"

extern int g_CurrentScrollx;
extern int g_CurrentScrolly;

int arrVK[(UINT)KEY_TYPE::KEY_END] =
{
	VK_LBUTTON,
	VK_RBUTTON,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Init()
{
	for (int i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
	{
		m_vecKey.push_back(tKeyState{ KEY_STATE::STATE_NONE, false });
	}
}

void CKeyMgr::update()
{
	// 현재 윈도우가 Active(활성화, 포커싱) 상태가 아니라면, 
	// 모든 키 상태를 초기상태로 변경한다.

	HWND hActive = GetActiveWindow();

	if (nullptr == hActive || CApp::GetInst()->GetAnimHWND() == hActive)
	{
		for (UINT i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
		{
			m_vecKey[i].bPrevPress = false;
			m_vecKey[i].eState = KEY_STATE::STATE_NONE;
		}
		return;
	}

	// 윈도우가 활성상태라면 키를 정상적으로 update 한다.
	for (UINT i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
	{
		// 현재 키가 눌려있다.
		if (GetAsyncKeyState(arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPress) // 이전 프레임에 눌려있었다.
			{
				m_vecKey[i].eState = KEY_STATE::STATE_HOLD;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::STATE_TAB;
				m_pClickMouse.x = m_ptMouse.x;
				m_pClickMouse.y = m_ptMouse.y;
			}
			m_vecKey[i].bPrevPress = true;
		}
		else // 키가 눌리지 않은 상태
		{
			if (m_vecKey[i].bPrevPress) // 이전 프레임에 눌려있었다.
			{
				m_vecKey[i].eState = KEY_STATE::STATE_AWAY;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::STATE_NONE;
			}
			m_vecKey[i].bPrevPress = false;
		}
	}

	// 마우스 좌표	
	m_ptOldMouse = m_ptMouse;

	GetCursorPos(&m_ptMouse);
	ScreenToClient(CApp::GetInst()->GetWINHWND(), &m_ptMouse);
	m_ptMouse.x += g_CurrentScrollx;
	m_ptMouse.y += g_CurrentScrolly;
}

void CKeyMgr::render(HDC _hdc)
{
	wchar_t szCount[100] = L"";
	_stprintf_s(szCount, L"mousePos : %d, %d , ClickPos : %d, %d",
		int(m_ptMouse.x), int(m_ptMouse.y), int(m_pClickMouse.x), int(m_pClickMouse.y));
	TextOut(_hdc, 10, 30, szCount, wcslen(szCount));
}
