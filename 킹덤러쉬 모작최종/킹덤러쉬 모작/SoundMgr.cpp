#include "stdafx.h"

#include "SoundMgr.h"
#include "PathMgr.h"

#include "app.h"

// ���� ����
bool g_bBGM = true;

CSoundMgr::CSoundMgr(void)
	: m_pSound(NULL)
	, m_pBGM(NULL)
	, m_lVolume(100)
	, m_bOffSound(false)
{
}

CSoundMgr::~CSoundMgr(void)
{
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.begin();
	for (iter; iter != m_mapSoundBuffer.end(); ++iter)
	{
		iter->second->Release();
	}
}

int CSoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	//���� ����̽� �������� ����.
	HWND hWnd = CApp::GetInst()->GetWINHWND();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

int CSoundMgr::update(void)
{
	if (!m_strCurBGM.empty())
	{
		if (!g_bBGM && !m_bOffSound)
		{
			StopSound(m_strCurBGM, false);
			m_bOffSound = true; // �Ҹ��� ����.
		}
		else if (g_bBGM && m_bOffSound)
		{
			PlayBGM(m_strCurBGM);
			m_bOffSound = false;
		}
	}
	return true;
}

int CSoundMgr::LoadWavSound(const wchar_t *_pFileName, const wchar_t *_pResourceKey)
{
	HMMIO	hFile; // File Handle

	wstring strFilePath = _pFileName;

	//CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);//wave������ ����.

																	 //Chunk ûũ ����ü, ���ڿ��� ������ �ν��ؼ� WaveFormat �� ���ۼ��������� �о�´�.
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	DSBUFFERDESC	BuffInfo;
	memset(&BuffInfo, 0, sizeof(DSBUFFERDESC));
	BuffInfo.dwBufferBytes = pChild.cksize;
	BuffInfo.dwSize = sizeof(DSBUFFERDESC);
	BuffInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	BuffInfo.lpwfxFormat = &wft;

	LPDIRECTSOUNDBUFFER	pSoundBuff;

	if (FAILED(m_pSound->CreateSoundBuffer(&BuffInfo, &pSoundBuff, NULL)))
	{
		MessageBox(NULL, L"������ۻ�������", L"", MB_OK);
		return false;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	pSoundBuff->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 > 0)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 > 0)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	pSoundBuff->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// �ʿ� ���带 ��´�.
	m_mapSoundBuffer.insert(make_pair(_pResourceKey, pSoundBuff));

	return true;
}

int CSoundMgr::LoadSound(const wchar_t *_pResourceKey, const wchar_t *_pFileName)
{
	if (!m_pSound)
		return false; // ���� ��ü �������� ����

	if (m_mapSoundBuffer.find(_pResourceKey) != m_mapSoundBuffer.end())// �̹� ������ �ε�Ǿ��ִ�.
		return false;

	// ���ϸ��� ���ҽ� ��ο� ��ģ��.
	if (_pFileName == NULL)
		return true;

	TCHAR	szPath[255] = { 0 };
	wchar_t* pPath = CPathMgr::GetResPath();
	wcscpy_s(szPath, 255, pPath);

	wcscat_s(szPath, 255, L"\\Sound\\");
	wcscat_s(szPath, 255, _pFileName);

	// Ȯ���� �̸� �����ϱ�
	TCHAR _pExtension[10] = { 0 };

	int iSize = _tcslen(_pFileName);
	int iStart = 0;

	for (int i = 0; i < iSize; ++i)
	{
		if (_pFileName[i] == '.')
		{
			iStart = i + 1;
			break;
		}
	}

	for (int i = iStart, j = 0; i < iSize; ++i, ++j)
	{
		_pExtension[j] = _pFileName[i];
	}

	if (!_tcscmp(_pExtension, _T("wav"))) // WAV ���� �ε�
	{
		if (false == LoadWavSound(szPath, _pResourceKey))
			return false;
	}
	//else if( !_tcscmp( _pExtension, _T("ogg") ) ) // OGG ���� �ε�
	//{
	//	if(RET_FAILED == LoadOggSound(szPath,_pResourceKey))
	//		return RET_FAILED;
	//}

	return true;
}

// Sound Play //
int CSoundMgr::Play(const wstring& _strSoundKey, const bool& _bLoop)
{
	// SoundMgr �� �ش� Ű�� ��ϵ� ���尡 ���ٸ�
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter == m_mapSoundBuffer.end())
	{
		MessageBox(NULL, L"���� ��� ����", L"���� ���� ����", MB_OK);
		return false;
	}

	// Play �Լ��� 1��° 2��° ���ڴ� 0 ���� �̹� ����Ǿ��ִ�.
	// 3��° ������ ���带 �ݺ���� �� ������ �ƴ����� �����Ѵ�.
	if (_bLoop)
		iter->second->Play(0, 0, DSBPLAY_LOOPING);
	else
		iter->second->Play(0, 0, 0);

	return true;
}

int CSoundMgr::PlayBGM(const wstring& _strSoundKey, const bool& _bLoop)
{
	// SoundMgr �� �ش� Ű�� ��ϵ� ���尡 ���ٸ�
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter == m_mapSoundBuffer.end())
	{
		MessageBox(NULL, L"���� ��� ����", L"���� ���� ����", MB_OK);
		return false;
	}

	m_strCurBGM = _strSoundKey;

	// BGM �� 1���� �����Ѵ�.
	//SUCCEEDED(m_pBGM->GetStatus((LPDWORD)DSBSTATUS_PLAYING))
	if (m_pBGM)
	{
		// BGM �� �ְ�, BGM �� ������̶�� Stop
		m_pBGM->Stop();
		m_pBGM->SetCurrentPosition(0);
	}

	// ���ο� BGM ���� �ٲ۴�.
	m_pBGM = iter->second;
	m_pBGM->SetVolume(m_lVolume);

	if (_bLoop)
		m_pBGM->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_pBGM->Play(0, 0, 0);

	return true;
}

void CSoundMgr::StopSound(const wstring& _strSoundKey, const bool& _bReset)
{
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter != m_mapSoundBuffer.end())
	{
		iter->second->Stop();

		if (m_pBGM == iter->second)
			m_pBGM = NULL;

		if (_bReset)
			iter->second->SetCurrentPosition(0);
	}
}

void CSoundMgr::SetBGMVolume(const double& _dVolume)
{
	double dVolume = _dVolume;
	if (dVolume > 100.0)
		dVolume = 100.0;
	else if (dVolume <= 0.0)
		dVolume = 0.00001;

	// 1 ~ 100 ���̰��� ���ú� ������ ����
	m_lVolume = (LONG)(-2000.0 * log10(100.0 / dVolume));
	if (m_lVolume < -10000)
		m_lVolume = -10000;

	if (m_pBGM)
		m_pBGM->SetVolume(m_lVolume);
}

const long& CSoundMgr::GetBGMVolume(void)
{
	return m_lVolume;
}