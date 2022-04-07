#include "stdafx.h"
#include "Animation.h"
#include "Obj.h"
#include "Texture.h"
#include "TimeMgr.h"

CAnimation::CAnimation()
	: m_iFrmIndex(0)
	, m_fAccTime(0)
	, m_bEnd(false)
{
}


CAnimation::~CAnimation()
{
}


void CAnimation::upate()
{
	if (m_vecFrm[m_iFrmIndex].fTerm == 10)
		return;

	if (m_bEnd)
		return;

	m_fAccTime += DT;

	//프레임 유지시간이 지나면 
	if (m_vecFrm[m_iFrmIndex].fTerm < m_fAccTime)
	{
		// 누적 시간이 현재 Frame 유지시간을 넘을 부분을 계산
		m_fAccTime = m_fAccTime - m_vecFrm[m_iFrmIndex].fTerm;
		m_iFrmIndex += 1;
		if ((int)m_vecFrm.size() <= m_iFrmIndex)
		{
			// 프레임 최대치 초과
			m_iFrmIndex = 0;
			m_bEnd = true;
		}
	}

	
}

void CAnimation::render(HDC _dc)
{
	Vec2 vPos = m_pOwner->GetPos();

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iFrmIndex].vSize.x / 2.f + m_vecFrm[m_iFrmIndex].vOffset.x + m_vOffset.x)
		, (int)(vPos.y - m_vecFrm[m_iFrmIndex].vSize.y / 2.f + m_vecFrm[m_iFrmIndex].vOffset.y + m_vOffset.y)
		, (int)m_vecFrm[m_iFrmIndex].vSize.x
		, (int)m_vecFrm[m_iFrmIndex].vSize.y
		, m_vecFrm[m_iFrmIndex].pTex->GetDC()
		, (int)m_vecFrm[m_iFrmIndex].vLT.x
		, (int)m_vecFrm[m_iFrmIndex].vLT.y
		, (int)m_vecFrm[m_iFrmIndex].vSize.x
		, (int)m_vecFrm[m_iFrmIndex].vSize.y
		, RGB(255, 0, 255));
}

wchar_t* CAnimation::GetName()
{
	wchar_t wtemp[100] = L"";
	wcscpy_s(wtemp,100, m_strName.c_str());
	
	return wtemp;
}

void CAnimation::Create(const wstring & _strName, CTexture * _pTex, tAnimFrm* _frm, int iMaxFrm)
{
	m_strName = _strName;

	tAnimFrm frm = {};
	for (int i = 0; i < iMaxFrm; ++i)
	{
		frm.pTex = _pTex;
		frm.vLT = _frm[i].vLT;
		frm.vSize = _frm[i].vSize;
		frm.fTerm = _frm[i].fTerm;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Create(const wstring & _strName, CTexture * _pTex, tSaveAnimFrm * _frm, int iMaxFrm)
{
	m_strName = _strName;

	tAnimFrm frm = {};
	for (int i = 0; i < iMaxFrm; ++i)
	{
		frm.pTex = _pTex;
		frm.vLT = _frm[i].vLT;
		frm.vSize = _frm[i].vSize;
		frm.fTerm = _frm[i].fTerm;
		frm.vOffset = _frm[i].vOffset;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::SetFrame(UINT _iFrameIdx)
{
	assert(!(m_vecFrm.size() <= _iFrameIdx));

	m_iFrmIndex = _iFrameIdx;
	m_bEnd = false;
}
