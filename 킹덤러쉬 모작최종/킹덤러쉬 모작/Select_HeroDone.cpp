#include "stdafx.h"
#include "Select_HeroDone.h"


CSelect_HeroDone::CSelect_HeroDone()
	:m_bMouseAttach(false)
{
}


CSelect_HeroDone::~CSelect_HeroDone()
{
}

void CSelect_HeroDone::MouseOn(Vec2 _vMousePos)
{
	SetTexPos(Vec2(857.f, 580.f));
	if (!m_bMouseAttach)
	{
		SetSize(Vec2(135.f, 74.f));
		m_bMouseAttach = true;
	}
}

void CSelect_HeroDone::MouseOff()
{
	SetTexPos(Vec2(861.f, 512.f));
	if (m_bMouseAttach)
	{
		SetSize(Vec2(132.f, 68.f));
		m_bMouseAttach = false;
	}
}

void CSelect_HeroDone::MouseLbtnClicked(Vec2 _vMousePos)
{

}
