#pragma once
#include "UI.h"
class CWave :
	public CUI
{
private:
	int		 m_iCurrentWave;
	int		 m_numfoMon;
	int		 m_waveStack;
	float	 m_fSpawnAccTimer;
	bool	 m_enable;
	bool	 m_StageClear;
	bool	 m_bChkStageClear;
	bool	 m_bEnd;
	float    m_fAniValue;
	int		 m_iSign;
	int		 m_iStageNum;
	Vec2	 m_vStartPoint;

	vector<tWaveInfo> m_vWaveInfo;

public:
	void SetStartPoint(Vec2 _pos) { m_vStartPoint = _pos; }
	void SetStageNum(int _num) { m_iStageNum = _num; }
	bool GetStageEnd() { return m_bEnd; }
	bool GetStageClear() { return m_StageClear; }

public:
	virtual void update();
	virtual void render(HDC _hdc);
	void AddWave(int _waveNum, MONSTER_TYPE _type, int _num);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	void CreateGoblin();
	void CreateFatorc();
	void CreateBandit();
	CWave();
	virtual ~CWave();
};

