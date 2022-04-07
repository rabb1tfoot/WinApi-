#pragma once
class CMapMgr
{
	SINGLE(CMapMgr);

private:
	int m_iGold;
	int m_iLife;
	int m_iMaxWave;
	int m_iCurrnetWave;
	int m_iCurOpenStage;
	int m_iMaxStage;
	bool m_bClick;
	bool m_bClear[STAGE_NUM];
	bool m_bSelectedHero[HERO_TYPE::HERO_END];
	MAP_SETTING m_eOption = MAP_SETTING::NONE;
	vector<Vec2> m_vRoute;

public:
	int GetGold() { return m_iGold; }
	int GetLife() { return m_iLife; }
	int GetMaxWave() { return m_iMaxWave; }
	int GetCurrentWave() { return m_iCurrnetWave; }
	int GetMaxStage() { return m_iMaxStage; }
	int GetCurOpenStage() { return m_iCurOpenStage; }
	int GetHero();
	bool GetClear(int _num) { return m_bClear[_num]; }
	void SetGold(int _gold) { m_iGold = _gold; }
	void SetLife(int _life) { m_iLife = _life; }
	void SetMaxWave(int _maxWave) { m_iMaxWave = _maxWave; }
	void SetCurrentWave(int _curwave) { m_iCurrnetWave =_curwave; }
	void SetMaxStage(int _max) { m_iMaxStage = _max; }
	void SetCurStage(int _cur) { m_iCurOpenStage = _cur; }
	void SetHero(HERO_TYPE _etype);
	void Init();
	void SetClear(int _num) { m_bClear[_num] = true; }

public:
	void AddRoute(Vec2 _pos) { m_vRoute.push_back(_pos); }
	vector<Vec2>& GetRoute() { return m_vRoute; }
	void DeleteRoute() { m_vRoute.clear(); }
	void CLickModeOn() { m_bClick = true; }
	void CLickModeOff() { m_bClick = false; }
	bool GetClickMode() { return m_bClick; }
	void SetClickOption(MAP_SETTING _etype) { m_eOption = _etype; }
	MAP_SETTING GetClickOption() { return m_eOption; }
	void LoadMap(const wchar_t* _Filename);
	void CreateHero();

private:
	void CreateHeroLight();
	void CreateHeroHammer();

};

