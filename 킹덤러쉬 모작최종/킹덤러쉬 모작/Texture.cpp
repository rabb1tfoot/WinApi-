#include "stdafx.h"
#include "Texture.h"

#include "App.h"


CTexture::CTexture()
	: m_hBit(nullptr)
	, m_hdc(nullptr)
{
}


CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteObject(m_hdc);
}



int CTexture::Load(const wstring & _strPath)
{
	m_hBit = (HBITMAP)LoadImage(NULL, _strPath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	// 텍스쳐 로딩 실패
	if (nullptr == m_hBit)
		return -1;

	m_hdc = CreateCompatibleDC(CApp::GetInst()->GetHDC());

	HBITMAP hOld = (HBITMAP)SelectObject(m_hdc, m_hBit);
	DeleteObject(hOld);

	// 가로 세로 길이정보	
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitmap);
	return 0;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC _dc = CApp::GetInst()->GetHDC();
	m_hBit = CreateCompatibleBitmap(_dc, _iWidth, _iHeight);
	m_hdc = CreateCompatibleDC(_dc);

	// DC 가 만들어질때 생기는 기본 BITMAP 을 받아서 지운다.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hdc, m_hBit);
	DeleteObject(hOldBit);

	// 가로 세로 길이정보	
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitmap);
}
