#pragma once

#include "TimeMgr.h"

class CCollider;
class CAnimator;
class CTexture;

class CObj
{
private:

	Vec2		m_vPos;
	Vec2		m_vSize;
	Vec2		m_texPos;
	CTexture*	m_pTex;
	bool		m_bDead;
	OBJ_TYPE	m_ObjType;

	CCollider*  m_pCollider;
	CAnimator*  m_pAnimator;
	wchar_t		m_wKey[50];
	MAP_SETTING m_eMapSetting;
	bool		m_bEnable;

public:
	void SetEnable(bool _enable) { m_bEnable = _enable; }
	bool GetEnable() { return m_bEnable; }
	void SetMapSetting(MAP_SETTING _type) { m_eMapSetting = _type; }
	MAP_SETTING GetMapSetting() { return m_eMapSetting; }
	void SetCollider(CCollider* _col) { m_pCollider = _col; }
	CCollider* GetCollider() { return m_pCollider; }
	void SetTexPos(Vec2 _pos) { m_texPos = _pos; }
	Vec2 GetTexPos() { return m_texPos; }
	const wchar_t* GetKey() { return m_wKey; }
	void SetKey(wchar_t* _key) { wcscpy_s(m_wKey, _key); }
	const Vec2& GetPos() { return m_vPos; }
	void SetPos(const Vec2& _pos) { m_vPos = _pos; }
	const Vec2& GetSize() { return m_vSize; }
	void SetSize(const Vec2& _vSize) { m_vSize = _vSize; }
	void SetTexture(CTexture* pTex) { m_pTex = pTex; }
	CTexture* GetTexture() { return m_pTex; }
	void SetObjType(OBJ_TYPE _type) { m_ObjType = _type; }
	OBJ_TYPE GetObjType() { return m_ObjType; }
	CAnimator* GetAnim() { return m_pAnimator; }
	void SetAnim(CAnimator* _anim) { m_pAnimator = _anim; }

	virtual bool IsOn(Vec2 _vCoordinate);

	virtual void Init() {};
	virtual void update() {};
	virtual void eventUpdate() {};
	virtual void render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	void SetDead() { m_bDead = true; }
	
public:
	bool IsDead() { return m_bDead; }

public:
	CObj();
	virtual ~CObj();
	CObj(Vec2 _vPos);
};

