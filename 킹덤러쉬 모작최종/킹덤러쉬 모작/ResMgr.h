#pragma once
class CTexture;
class CAnimation;
class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CTexture*> m_mapTex;
	map<wstring, vector<tSaveAnimFrm>> m_mapAni;

public:
	CTexture * FindTexture(const wstring& _strKey);
	CTexture * DelTexture(const wstring& _strKey);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strPath);
	CTexture* LoadFromToolTex(wchar_t* _strKey);

	CAnimation* LoadAnimation(const wstring& _strName);
	CAnimation* FindAnimation(const wstring& _strName);
};

