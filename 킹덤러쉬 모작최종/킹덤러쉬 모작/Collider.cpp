#include "stdafx.h"
#include "Collider.h"
#include "Obj.h"

DWORD CCollider::g_id = 0;

CCollider::~CCollider()
{
}


void CCollider::update()
{
	m_vFinalPos = m_pObj->GetPos() + m_vOffset;
}

void CCollider::render(HDC _hdc)
{
	if (m_bPaint)
	{
		// 라인그리기
		HPEN hPen = CreatePen(PS_SOLID, 2, m_iColor);
		HPEN hOriginPen = (HPEN)SelectObject(_hdc, hPen);
		SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		if (MAP_SETTING::MAP_GROUND == this->GetObj()->GetMapSetting())
		{
			m_iColor = RGB(255, 255, 0);
			this->SetSize(Vec2{ 108.f, 57 });
			Rectangle(_hdc, int(m_vFinalPos.x), int(m_vFinalPos.y)
				, int(m_vFinalPos.x + m_vSize.x), int(m_vFinalPos.y + m_vSize.y));
			SelectObject(_hdc, hOriginPen);
			DeleteObject(hPen);
			return;
		}
		else if (MAP_SETTING::MAP_NOTBLOCK == this->GetObj()->GetMapSetting())
		{
			m_iColor = RGB(0, 255, 255);
			Rectangle(_hdc, int(m_vFinalPos.x), int(m_vFinalPos.y)
				, int(m_vFinalPos.x + m_vSize.x), int(m_vFinalPos.y + m_vSize.y));
			SelectObject(_hdc, hOriginPen);
			DeleteObject(hPen);
			return;
		}
		else if (MAP_SETTING::MAP_BLOCK == this->GetObj()->GetMapSetting())
		{
			m_iColor = RGB(255, 100, 20);
			Rectangle(_hdc, int(m_vFinalPos.x), int(m_vFinalPos.y)
				, int(m_vFinalPos.x + m_vSize.x), int(m_vFinalPos.y + m_vSize.y));
			SelectObject(_hdc, hOriginPen);
			DeleteObject(hPen);
			return;
		}


		if (COLLIDER_TYPE::RECT == m_eType)
		{
			Rectangle(_hdc, int(m_vFinalPos.x - m_vSize.x / 2), int(m_vFinalPos.y - m_vSize.y / 2)
				, int(m_vFinalPos.x + m_vSize.x / 2), int(m_vFinalPos.y + m_vSize.y / 2));
		}
		else
		{
			Ellipse(_hdc, int(m_vFinalPos.x - m_vSize.x / 2), int(m_vFinalPos.y - m_vSize.y / 2)
				, int(m_vFinalPos.x + m_vSize.x / 2), int(m_vFinalPos.y + m_vSize.y / 2));
		}

		SelectObject(_hdc, hOriginPen);
		DeleteObject(hPen);
		//SelectObject(_hdc, hOriginBrush);
		//DeleteObject(hBrush);
	}
}

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	m_iColor = RGB(255, 20, 20);
	m_pObj->OnCollisionEnter(_pOther);
}

void CCollider::OnCollision(CCollider * _pOther)
{
	m_pObj->OnCollision(_pOther);
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	m_iColor = RGB(20, 255, 20);
	m_pObj->OnCollisionExit(_pOther);
}
