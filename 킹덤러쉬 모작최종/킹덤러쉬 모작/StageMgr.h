#pragma once

class CStage;

class CStageMgr
{
	SINGLE(CStageMgr);

private:
	CStage * m_arrStage[(UINT)STAGE_TYPE::END];
	CStage* m_pCurStage;
	STAGE_TYPE m_eStageType;

public:
	void Init();
	void update();
	void render(HDC _hdc);

public:
	STAGE_TYPE GetCurStageType() { return m_eStageType; }
	CStage * GetCurStage() { return m_pCurStage; }
	void ChangeStage(STAGE_TYPE _etype);


};

