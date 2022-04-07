#pragma once

class CAnimation;
class CObj;

class CAnimator
{
private:
	wchar_t					  m_wName[100];
	CObj*					  m_pOwner;
	map<wstring, CAnimation*> m_mapAnim;
	CAnimation*				  m_pCurAnim;
	bool					  m_bRepeat;

public:
	void update();
	void render(HDC _hdc);

public:
	void SetName(wchar_t* _name) { wcscat_s(m_wName, _name); }
	wchar_t* GetName() { return m_wName; }
	CAnimation* GetCurAni() { return m_pCurAnim; }
	void AddAnimation(const wstring& _strName, CTexture* _pTex, tAnimFrm* _frm, int _iMaxFrm);
	void AddAnimation(const wstring& _strName, CTexture* _pTex, tSaveAnimFrm* _frm, int _iMaxFrm);
	void AddAnimation(const wstring& _strName, CAnimation* _pAnim);
	void PlayAnim(const wstring& _strKey, CObj* _obj, bool _bRepeat = false, Vec2 _off = { 0.f,0.f });
public:
	CAnimator(CObj* _Obj);
	CAnimator();
	~CAnimator();
};

