#include "stdafx.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
#include "Obj.h"
#include "StageMgr.h"
#include "Stage.h"
#include "CStage_Tool.h"
#include "UI.h"
#include "App.h"
#include "Animation.h"

CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();

	for (; iter != m_mapTex.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapTex.clear();
}

CTexture * CResMgr::FindTexture(const wstring & _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}

CTexture * CResMgr::DelTexture(const wstring & _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	m_mapTex.erase(iter++);
	
	return iter->second;
}

CTexture * CResMgr::CreateTexture(const wstring & _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pFindTex = FindTexture(_strKey);

	assert(!pFindTex);

	CTexture* pTex = new CTexture;
	pTex->Create(_iWidth, _iHeight);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture * CResMgr::LoadTexture(const wstring & _strKey, const wstring & _strPath)
{

	CTexture* pFindTex = FindTexture(_strKey);

	// 이미 동일한 키로 텍스쳐가 존재한다.(경로도 같을경우 이전에 저장된 값 반환)
	if (nullptr != pFindTex && pFindTex->GetPath() == _strPath)
		return pFindTex;

	//이름만 같으면 에러
	assert(nullptr == pFindTex);

	wstring strFilePath = CPathMgr::GetResPath();
	strFilePath += _strPath;

	CTexture* pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetPath(_strPath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture * CResMgr::LoadFromToolTex(wchar_t* _strKey)
{
	wchar_t TotalFileName[255] = L"";
	CStage_Tool* pCurStage = (CStage_Tool*)CStageMgr::GetInst()->GetCurStage();
	vector<CObj*> arrObj = pCurStage->GetVecObj(OBJ_TYPE::TEST);
	if (arrObj.size() != 0)
	{
		//이전의 텍스처를 지운다.
		arrObj[0]->SetDead();
	}
	wcscat_s(TotalFileName, L"Texture\\");
	wcscat_s(TotalFileName, _strKey);
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(_strKey, TotalFileName);
	if (nullptr == pTex)
		return nullptr;
	CObj* obj = new CObj(Vec2(float(pTex->GetWidth() / 2 + 300.f), float(pTex->GetHeight() / 2 + 60.f)));
	obj->SetTexture(pTex);
	obj->SetKey(_strKey);

	pCurStage->AddObject(obj, OBJ_TYPE::TEST);

	return pTex;
}

CAnimation * CResMgr::LoadAnimation(const wstring & _strName)
{
	wstring strResPath = CPathMgr::GetResPath();
	strResPath += L"Data\\Anim\\";
	strResPath += _strName;

	wchar_t wName[50];
	wcscpy_s(wName, _strName.c_str());

	FILE* pFile = nullptr;
	//파일로부터 정보받기
	_wfopen_s(&pFile, strResPath.c_str(), L"rb");
	if (nullptr == pFile)
	{
		MessageBox(nullptr, L"파일이 존재하지 않습니다.", L"타일 읽기 실패", MB_OK);
		return nullptr;
	}
	int iFrameSize;
	fread(&iFrameSize, sizeof(int), 1, pFile);
	tSaveAnimFrm * tFrm = new tSaveAnimFrm[iFrameSize];
	for (int i = 0; i < iFrameSize; ++i)
	{
		fread(&tFrm[i], sizeof(tSaveAnimFrm), 1, pFile);
	}
	//파일닫기
	fclose(pFile);

	//애니메이션 만들기
	CTexture* pTex = CResMgr::GetInst()->FindTexture(tFrm->pTexName);
	CAnimation* anim = new CAnimation();
	anim->Create(tFrm->pTexName, pTex, tFrm, iFrameSize);

	vector<tSaveAnimFrm> vFrm;
	for(int i=0; i<iFrameSize; ++i)
		vFrm.push_back(tFrm[i]);
	m_mapAni.insert(make_pair(wName, vFrm));

	delete tFrm;
	return anim;

}

CAnimation * CResMgr::FindAnimation(const wstring & _strName)
{
	map<wstring, vector<tSaveAnimFrm>>::iterator iter = m_mapAni.find(_strName);

	if (iter == m_mapAni.end())
		return nullptr;

	CAnimation* anim = new CAnimation();
	CTexture* pTex = CResMgr::GetInst()->FindTexture(iter->second[0].pTexName);
	tSaveAnimFrm * tFrm = new tSaveAnimFrm[iter->second.size()];
	for (int i = 0; i < iter->second.size(); ++i)
	{
		tFrm[i] = iter->second[i];
	}
	anim->Create(iter->second[0].pTexName, pTex, tFrm, iter->second.size());
	delete tFrm;
	return anim;
}
