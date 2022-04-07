#include "stdafx.h"
#include "MapMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Obj.h"
#include "Collider.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Building.h"
#include "Animation.h"
#include "animator.h"
#include "block.h"
#include "NotBlock.h"
#include "Hero_Light.h"
#include "Hero_Hammer.h"
#include "Obj_Coll.h"


CMapMgr::CMapMgr()
{
}

CMapMgr::~CMapMgr()
{
}

void CMapMgr::Init()
{
	for (int i = 0; i < STAGE_NUM; ++i)
	{
		m_bClear[i] = false;
	}
	for (int i = 0; i < HERO_TYPE::HERO_END; ++i)
	{
		m_bSelectedHero[i] = false;
	}
}

int CMapMgr::GetHero()
{
	for(UINT i=0; i<HERO_TYPE::HERO_END; ++i)
	{
		if (m_bSelectedHero[i] == true)
			return i;
	}
	return -1;
}

void CMapMgr::SetHero(HERO_TYPE _etype)
{
	for (int i = 0; i < HERO_TYPE::HERO_END; ++i)
	{
		m_bSelectedHero[i] = false;
	}
	m_bSelectedHero[(UINT)_etype] = true;
}

void CMapMgr::LoadMap(const wchar_t* _Filename)
{
	wstring strResPath = CPathMgr::GetResPath();
	strResPath += L"Data\\Map\\";
	wchar_t FileName[50];
	wcscpy_s(FileName, _Filename);
	strResPath += FileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strResPath.c_str(), L"rb");

	// 파일 입출력 실패
	if (nullptr == pFile)
	{
		assert(nullptr);
	}
	int Frmidx;
	fread(&Frmidx, sizeof(int), 1, pFile);

	tMapInfo* frm = new tMapInfo[Frmidx];

	for (int i = 0; i < Frmidx; ++i)
	{
		//레이어와 그라운드 생성
		fread(&frm[i], sizeof(tMapInfo), 1, pFile);

		frm[i].vLT.y += 150.f;
		if (MAP_SETTING::MAP_BLOCK == frm[i].tSetting)
		{
			CObj* pBlock = new CBlock;
			pBlock->SetMapSetting(MAP_SETTING::MAP_BLOCK);
			pBlock->SetPos(Vec2{ frm[i].vLT.x + frm[i].vSize.x / 2, frm[i].vLT.y + frm[i].vSize.y / 2 - 150.f });
			((CUI*)pBlock)->SetFinalPos(pBlock->GetPos());
			((CUI*)pBlock)->SetLayer(true);
			pBlock->SetSize(Vec2{ frm[i].vSize.x, frm[i].vSize.y });
			pBlock->SetObjType(OBJ_TYPE::UI);
			CCollider* pCol = new CCollider(pBlock);
			pCol->SetSize(Vec2(frm[i].vSize.x, frm[i].vSize.y));
			pCol->SetFinalPos(Vec2(pBlock->GetPos().x, pBlock->GetPos().y));
			pCol->SetColliderType(COLLIDER_TYPE::RECT);
			pCol->SetDrow(false);
			pBlock->SetCollider(pCol);
			CStageMgr::GetInst()->GetCurStage()->AddObject(pBlock, pBlock->GetObjType());
		}
		else if (MAP_SETTING::MAP_NOTBLOCK == frm[i].tSetting)
		{
			CObj* pnoBlock = new CNotBlock;
			pnoBlock->SetMapSetting(MAP_SETTING::MAP_NOTBLOCK);
			pnoBlock->SetPos(Vec2{ frm[i].vLT.x + frm[i].vSize.x / 2, frm[i].vLT.y + frm[i].vSize.y / 2  - 150.f});
			((CUI*)pnoBlock)->SetFinalPos(pnoBlock->GetPos());
			((CUI*)pnoBlock)->SetLayer(true);
			pnoBlock->SetSize(Vec2{ frm[i].vSize.x, frm[i].vSize.y });
			pnoBlock->SetObjType(OBJ_TYPE::UI);

			CCollider* pCol = new CCollider(pnoBlock);
			pCol->SetSize(Vec2(frm[i].vSize.x, frm[i].vSize.y));
			pCol->SetFinalPos(Vec2(pnoBlock->GetPos().x, pnoBlock->GetPos().y));
			pCol->SetColliderType(COLLIDER_TYPE::RECT);
			pCol->SetDrow(false);
			pnoBlock->SetCollider(pCol);
			CStageMgr::GetInst()->GetCurStage()->AddObject(pnoBlock, pnoBlock->GetObjType());

		}
		else if (MAP_SETTING::MAP_GROUND == frm[i].tSetting)
		{
			CObj* pUnbuild = new CBuilding;
			pUnbuild->SetMapSetting(MAP_SETTING::MAP_GROUND);
			pUnbuild->SetSize(Vec2{ 108.f, 57 });
			pUnbuild->SetPos(Vec2{ frm[i].vLT.x + pUnbuild->GetSize().x /2, frm[i].vLT.y + pUnbuild->GetSize().y / 2 - 150.f });
			((CUI*)pUnbuild)->SetFinalPos(pUnbuild->GetPos());
			((CUI*)pUnbuild)->SetLayer(true);
			pUnbuild->SetObjType(OBJ_TYPE::UI);
			CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"archer_unbuild_none");
			CAnimation* pAnim2 = CResMgr::GetInst()->LoadAnimation(L"archer_unbuild_on");

			CAnimator* pAnimtor = new CAnimator(pUnbuild);
			pAnimtor->AddAnimation(L"archer_unbuild_none", pAnim);
			pAnimtor->AddAnimation(L"archer_unbuild_on", pAnim2);

			pUnbuild->SetAnim(pAnimtor);
			pUnbuild->Init();
			CStageMgr::GetInst()->GetCurStage()->AddObject(pUnbuild, OBJ_TYPE::UI);

			pUnbuild->GetAnim()->PlayAnim(L"archer_unbuild_none", pUnbuild, true);
		}

	}
	fclose(pFile);
	delete frm;
}

void CMapMgr::CreateHero()
{
	for (UINT i = 0; i < HERO_TYPE::HERO_END; ++i)
	{
		if (true == m_bSelectedHero[i] && i == HERO_TYPE::HERO_LIGHT)
		{
			CreateHeroLight();
		}
		else if (true == m_bSelectedHero[i] && i == HERO_TYPE::HERO_HAMMER)
		{
			CreateHeroHammer();
		}

	}
}

void CMapMgr::CreateHeroLight()
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iMaxHealth = 30;
	tInfo.iCurHealth = tInfo.iMaxHealth;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;


	CResMgr::GetInst()->LoadTexture(L"HeroLightseeker.bmp", L"Texture\\HeroLightseeker.bmp");
	CHero_Light* Light = new CHero_Light;
	Light->SetInfo(tInfo);
	Light->SetType(HERO_TYPE::HERO_LIGHT);
	Light->SetPos(Vec2((float)WINSIZE_X /2 - 200.f, (float)WINSIZE_Y /2));
	Light->SetFinalPos(Light->GetPos());
	Light->SetSize(Vec2{ 40.f,40.f });
	Light->SetObjType(OBJ_TYPE::ALLY_HERO);
	CAnimator* pAnimtor = new CAnimator(Light);
	CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_attack_right");
	pAnimtor->AddAnimation(L"hero_light_attack_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_attack_left");
	pAnimtor->AddAnimation(L"hero_light_attack_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_move_left");
	pAnimtor->AddAnimation(L"hero_light_move_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_move_right");
	pAnimtor->AddAnimation(L"hero_light_move_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_idle_left");
	pAnimtor->AddAnimation(L"hero_light_idle_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_idle_right");
	pAnimtor->AddAnimation(L"hero_light_idle_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_sattack_right");
	pAnimtor->AddAnimation(L"hero_light_sattack_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_light_sattack_left");
	pAnimtor->AddAnimation(L"hero_light_sattack_left", pAnim);
	Light->SetAnim(pAnimtor);
	Light->GetAnim()->PlayAnim(L"hero_light_idle_left", Light, true);

	CCollider* pCol = new CCollider(Light);
	pCol->SetFinalPos(Light->GetPos());
	pCol->SetSize(Vec2(40.f, 40.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	Light->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(Light, OBJ_TYPE::ALLY_HERO);

	CObj_Coll* cObj = new CObj_Coll;
	cObj->SetOwner(Light);
	cObj->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
	pCol = new CCollider(cObj);
	pCol->SetFinalPos(Light->GetPos());
	pCol->SetSize(Vec2(100.f, 100.f));
	cObj->SetCollider(pCol);
	Light->SetObjColl((CObj_Coll*)cObj);
	CStageMgr::GetInst()->GetCurStage()->AddObject(cObj, OBJ_TYPE::ALLY_UNIT_RANGE);
}

void CMapMgr::CreateHeroHammer()
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iMaxHealth = 30;
	tInfo.iCurHealth = tInfo.iMaxHealth;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;

	CResMgr::GetInst()->LoadTexture(L"HeroHammerMaterial.bmp", L"Texture\\HeroHammerMaterial.bmp");
	CHero_Hammer* Hammer = new CHero_Hammer;
	Hammer->SetInfo(tInfo);
	Hammer->SetType(HERO_TYPE::HERO_HAMMER);
	Hammer->SetPos(Vec2((float)WINSIZE_X / 2 - 200.f, (float)WINSIZE_Y / 2));
	Hammer->SetFinalPos(Hammer->GetPos());
	Hammer->SetSize(Vec2{ 40.f,40.f });
	Hammer->SetObjType(OBJ_TYPE::ALLY_HERO);
	CAnimator* pAnimtor = new CAnimator(Hammer);
	CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_attack_right");
	pAnimtor->AddAnimation(L"hero_hammer_attack_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_attack_left");
	pAnimtor->AddAnimation(L"hero_hammer_attack_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_move_left");
	pAnimtor->AddAnimation(L"hero_hammer_move_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_move_right");
	pAnimtor->AddAnimation(L"hero_hammer_move_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_idle_left");
	pAnimtor->AddAnimation(L"hero_hammer_idle_left", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_idle_right");
	pAnimtor->AddAnimation(L"hero_hammer_idle_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_sattack_right");
	pAnimtor->AddAnimation(L"hero_hammer_sattack_right", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"hero_hammer_sattack_left");
	pAnimtor->AddAnimation(L"hero_hammer_sattack_left", pAnim);
	Hammer->SetAnim(pAnimtor);
	Hammer->GetAnim()->PlayAnim(L"hero_hammer_idle_left", Hammer, true);

	CCollider* pCol = new CCollider(Hammer);
	pCol->SetFinalPos(Hammer->GetPos());
	pCol->SetSize(Vec2(40.f, 40.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	Hammer->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(Hammer, OBJ_TYPE::ALLY_HERO);

	CObj_Coll* cObj = new CObj_Coll;
	cObj->SetOwner(Hammer);
	cObj->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
	pCol = new CCollider(cObj);
	pCol->SetFinalPos(Hammer->GetPos());
	pCol->SetSize(Vec2(100.f, 100.f));
	cObj->SetCollider(pCol);
	Hammer->SetObjColl((CObj_Coll*)cObj);
	CStageMgr::GetInst()->GetCurStage()->AddObject(cObj, OBJ_TYPE::ALLY_UNIT_RANGE);
}
