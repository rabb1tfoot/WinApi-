#pragma once

#include "Obj.h"

enum class COLLIDER_TYPE
{
	RECT,
	ELLIPSE
};

class CCollider
{
private:
	static DWORD g_id;

private:
	CObj * m_pObj;
	Vec2 m_vOffset;
	Vec2 m_vSize;
	Vec2 m_vFinalPos;
	CTexture* m_pTex;

	DWORD m_id;
	UINT m_iColor;
	COLLIDER_TYPE m_eType;
	bool m_bPaint;

public:
	void update();
	void render(HDC _hdc);

public:
	void SetDrow(bool _paint) { m_bPaint = _paint; }
	bool GetDrow() { return m_bPaint; }
	void SetSize(const Vec2& _vSize) { m_vSize = _vSize; }
	void SetOffSet(const Vec2& _vOff) { m_vOffset = _vOff; }
	void SetColliderType(COLLIDER_TYPE _eType) { m_eType = _eType; }
	void SetOwner(CObj* _pOwner) { m_pObj = _pOwner; }
	void SetFinalPos(const Vec2& _vFinalPos) { m_vFinalPos = _vFinalPos; };
	void SetTex(CTexture* _pTex) { m_pTex = _pTex; }

	const Vec2& GetFinalPos() { return m_vFinalPos; }
	const Vec2& GetSize() { return m_vSize; }
	const Vec2& GetOffset() { return m_vOffset; }
	CObj* GetObj() { return m_pObj; }

	void OnCollisionEnter(CCollider* _pOther);  // 처음 충돌
	void OnCollision(CCollider* _pOther);		// 충돌 중이다.
	void OnCollisionExit(CCollider* _pOther);   // 충돌에서 벗어난다

	DWORD GetID() { return m_id; }
	COLLIDER_TYPE GetType() { return m_eType; }
public:
	CCollider(CObj* _pObj)
		: m_pObj(_pObj)
		, m_vOffset{}
		, m_vSize{}
		, m_id(g_id++)
		, m_iColor(RGB(20, 255, 20))
		, m_eType(COLLIDER_TYPE::ELLIPSE)
		, m_bPaint(false)
	{}
	~CCollider();
};

