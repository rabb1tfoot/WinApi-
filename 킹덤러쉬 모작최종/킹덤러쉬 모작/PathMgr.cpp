#include "stdafx.h"
#include "PathMgr.h"

wchar_t CPathMgr::g_szPath[255] = {};

void CPathMgr::Init()
{
	{
		GetCurrentDirectory(255, g_szPath);

		int iLen = wcslen(g_szPath);

		for (int i = iLen - 1; 0 < i; --i)
		{
			if ('\\' == g_szPath[i])
			{
				wmemset(g_szPath + (i + 1), 0, iLen - (i + 1));
				break;
			}
		}

		wcscat_s(g_szPath, L"bin\\Resources\\");
	}
}
