#pragma once
class CPathMgr
{

private:
	static wchar_t g_szPath[255];

public:
	static void Init();

	static wchar_t* GetResPath()
	{
		return g_szPath;
	}
};

