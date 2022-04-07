#pragma once

extern int g_CurrentScrollx;
extern int g_CurrentScrolly;

enum class KEY_TYPE
{
	KEY_LBTN,
	KEY_RBTN,

	KEY_END
};

enum class KEY_STATE
{
	STATE_NONE,
	STATE_TAB,
	STATE_HOLD,
	STATE_AWAY
};

struct tKeyState
{
	KEY_STATE eState;
	bool bPrevPress;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyState> m_vecKey;
	POINT m_ptMouse;
	POINT m_ptOldMouse;
	POINT m_pClickMouse;

public:
	void Init();
	void update();
	void render(HDC _hdc);

public:
	KEY_STATE GetKeyState(KEY_TYPE _eKey) {return m_vecKey[(UINT)_eKey].eState;}
	const POINT& GetMousePos() 
	{
		return POINT{ m_ptMouse.x - g_CurrentScrollx
					, m_ptMouse.y - g_CurrentScrolly };
	}
	const POINT& GetPrevMousePos() 
	{
		return POINT{ m_ptOldMouse.x - g_CurrentScrollx
			, m_ptOldMouse.y - g_CurrentScrolly };
	}
	const POINT& GetClickMousePos() 
	{
		return POINT{ m_pClickMouse.x - g_CurrentScrollx
			, m_pClickMouse.y - g_CurrentScrolly };
	}
};

