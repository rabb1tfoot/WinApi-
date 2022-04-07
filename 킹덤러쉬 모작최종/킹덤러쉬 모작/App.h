#pragma once
class CTexture;
class CApp
{
	SINGLE(CApp);

private:
	HWND		m_hWnd;
	HWND		m_hAnimWnd;
	HWND		m_hMapWnd;
	bool		m_bMenu;
	bool		m_bGameOver;
	bool		m_bPause;
	HDC			m_hdc;

	CTexture*	m_pMemTex;

public:
	HDC GetHDC() { return m_hdc; }
	HWND GetWINHWND() { return m_hWnd; }
	HWND GetAnimHWND() { return m_hAnimWnd; }
	HWND GetMapHWND() { return m_hMapWnd; }
public:
	void SetGameOver(bool _over) { m_bGameOver = _over; }
	void SetbPause(bool _pause) { m_bPause = _pause; }
	void SetbMenu(bool _menu);
	void SetWindowMenu();
	int  progress();
	void init(HWND _hWnd);
	void AnimInit(HWND _anim) { m_hAnimWnd = _anim; }
	void MapInit(HWND _map) { m_hMapWnd = _map; }

private:
	void update();
	void render();
};

