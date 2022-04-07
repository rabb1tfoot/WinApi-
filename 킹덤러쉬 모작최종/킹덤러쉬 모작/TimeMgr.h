#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_LIOldCount;
	LARGE_INTEGER m_LICurCount;
	LARGE_INTEGER m_LIFrequency;

	float		  m_fDeltaTime;
	float		  m_fAccTime;
	float		  m_fFPS;
	bool		  m_bDouble;

public:
	void SetDouble(bool _double) { m_bDouble = _double; }

public:
	void Init();
	void update();
	void render(HDC _dc);

public:
	float GetDeltaTime() { return m_fDeltaTime; }

};

