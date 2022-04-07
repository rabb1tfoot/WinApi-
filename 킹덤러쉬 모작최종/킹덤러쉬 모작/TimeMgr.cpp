#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr()
{
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_LIFrequency);
	QueryPerformanceCounter(&m_LIOldCount);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_LICurCount);

	m_fDeltaTime = (float)(m_LICurCount.QuadPart - m_LIOldCount.QuadPart) / (float)m_LIFrequency.QuadPart;
	if (m_bDouble)
		m_fDeltaTime *= 2;
	m_LIOldCount = m_LICurCount;
	m_fAccTime += m_fDeltaTime;
}

void CTimeMgr::render(HDC _dc)
{
	if (m_fAccTime > 1.f)
	{
		QueryPerformanceFrequency(&m_LIFrequency);
		m_fAccTime = 0.f;
		m_fFPS = 1 / m_fDeltaTime;
	}

	wchar_t szCount[50] = L"";
	_stprintf_s(szCount, L"FPS : %f, DT : %f", m_fFPS, m_fDeltaTime);
	TextOut(_dc, 10, 10, szCount, wcslen(szCount));
}
