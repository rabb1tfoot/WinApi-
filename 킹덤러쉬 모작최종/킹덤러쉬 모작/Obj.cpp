#include "stdafx.h"
#include "Obj.h"
#include "Texture.h"
#include "Animator.h"
#include "Collider.h"
extern int g_CurrentScrollx;
extern int g_CurrentScrolly;


CObj::CObj()
	: m_vPos(0.f, 0.f)
	, m_vSize(0.f, 0.f)
	, m_texPos(0.f, 0.f)
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bDead(false)
	, m_bEnable(true)
	, m_wKey{}
	, m_ObjType(OBJ_TYPE::END)
	, m_eMapSetting(MAP_SETTING::NONE)
{
}


CObj::CObj(Vec2 _vPos)
	:m_vPos(_vPos)
	, m_texPos(0.f, 0.f)
	, m_vSize(0.f, 0.f)
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bDead(false)
	, m_bEnable(true)
	, m_ObjType(OBJ_TYPE::END)
	, m_eMapSetting(MAP_SETTING::NONE)
{
}

CObj::~CObj()
{
	SAFE_DELETE(m_pCollider);
	SAFE_DELETE(m_pAnimator);
}


bool CObj::IsOn(Vec2 _vCoordinate)
{
	if (m_vPos.x - m_vSize.x / 2.f < _vCoordinate.x && _vCoordinate.x < m_vPos.x + m_vSize.x / 2
		&& m_vPos.y - m_vSize.y / 2.f < _vCoordinate.y && _vCoordinate.y < m_vPos.y + m_vSize.y / 2)
	{
		return true;
	}
	return false;
}

void CObj::render(HDC _dc)
{
	if (!m_bEnable)
		return;
	if(nullptr != m_pAnimator)
		this->GetAnim()->render(_dc);

	if (nullptr != m_pCollider)
		this->GetCollider()->render(_dc);

	if (GetTexPos().x != 0.f && GetTexPos().y != 0.f)
	{
		TransparentBlt(_dc
			, (int)(m_vPos.x - m_vSize.x / 2)
			, (int)(m_vPos.y - m_vSize.y / 2)
			, (int)m_vSize.x
			, (int)m_vSize.y
			, m_pTex->GetDC()
			, (int)this->GetTexPos().x
			, (int)(this->GetTexPos().y)
			, (int)m_vSize.x
			, (int)m_vSize.y
			, RGB(255, 0, 255));
	}
	else if (nullptr != m_pTex && OBJ_TYPE::TEST != m_ObjType )
	{
		TransparentBlt(_dc
			, (int)(m_vPos.x - m_pTex->GetWidth() / 2.f)
			, (int)(m_vPos.y - m_pTex->GetHeight() / 2.f)
			, m_pTex->GetWidth()
			, m_pTex->GetHeight()
			, m_pTex->GetDC()
			, (int)m_texPos.x, (int)m_texPos.y
			, m_pTex->GetWidth()
			, m_pTex->GetHeight()
			, RGB(255, 0, 255));
	}
	else if (nullptr != m_pTex && OBJ_TYPE::TEST == m_ObjType)
	{
		BitBlt(_dc
			, (int)(m_vPos.x - m_pTex->GetWidth() / 2.f - g_CurrentScrollx)
			, (int)(m_vPos.y - m_pTex->GetHeight() / 2.f - g_CurrentScrolly)
			, m_pTex->GetWidth()
			, m_pTex->GetHeight()
			, m_pTex->GetDC()
			, 0, 0
			, SRCCOPY);
	}

	else
	{
		Rectangle(_dc, m_vPos.x - m_vSize.x / 2, m_vPos.y - m_vSize.y / 2
			, m_vPos.x + m_vSize.x / 2, m_vPos.y + m_vSize.y / 2);
	}
}

