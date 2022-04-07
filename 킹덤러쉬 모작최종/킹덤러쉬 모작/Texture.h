#pragma once
#include "Res.h"
class CTexture :
	public CRes
{
private:
	HBITMAP m_hBit;
	HDC m_hdc;
	BITMAP m_tBitmap;

public:
	HDC GetDC() { return m_hdc; }
	float GetWidth() { return (float)m_tBitmap.bmWidth; }
	float GetHeight() { return (float)m_tBitmap.bmHeight; }

public:
	virtual int Load(const wstring& _strPath);
	void Create(UINT _iWidth, UINT _iHeight);
public:
	CTexture();
	virtual ~CTexture();
};

