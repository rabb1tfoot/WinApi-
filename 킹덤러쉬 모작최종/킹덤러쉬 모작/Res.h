#pragma once
class CRes
{
private:
	wstring m_strResKey;
	wstring m_strResPath;

private:
	void SetKey(const wstring& _key) { m_strResKey = _key; }
	void SetPath(const wstring& _path) { m_strResPath = _path; }

public:
	const wstring& GetKey() { return m_strResKey; }
	const wstring& GetPath() { return m_strResPath; }

public:
	virtual int Load(const wstring& _strPath) = 0;

public:
	CRes();
	virtual ~CRes();

	friend class CResMgr;
};

