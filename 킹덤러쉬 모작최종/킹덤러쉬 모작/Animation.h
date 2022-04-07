#pragma once

class CObj;

class CAnimation
{
private:
	CObj * m_pOwner;
	vector<tAnimFrm> m_vecFrm;
	int m_iFrmIndex;
	wstring m_strName;

	float m_fAccTime;
	Vec2  m_vOffset;
	bool m_bEnd;

public:
	void upate();
	void render(HDC _dc);

public:
	wchar_t* GetName();
	void SetOffset(Vec2 _off) { m_vOffset = _off; }
	void Create(const wstring& _strName, CTexture* _pTex, tAnimFrm* _frm, int iMaxFrm);
	void Create(const wstring& _strName, CTexture* _pTex, tSaveAnimFrm* _frm, int iMaxFrm);
	void SetOwner(CObj* _pObj) { m_pOwner = _pObj; }
	bool IsEnd() { return m_bEnd; }
	void SetFrame(UINT _iFrameIdx);

public:
	CAnimation();
	~CAnimation();
};
