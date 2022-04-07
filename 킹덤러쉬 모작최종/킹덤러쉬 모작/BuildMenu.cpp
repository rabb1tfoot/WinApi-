#include "stdafx.h"
#include "BuildMenu.h"
#include "Building.h"
#include "Texture.h"
#include "ResMgr.h"
#include "CArcher.h"
#include "Animation.h"
#include "Animator.h"
#include "Stage.h"
#include "StageMgr.h"
#include "Mage.h"
#include "CCannon.h"
#include "Collider.h"
#include "Barracks.h"
#include "MapMgr.h"
#include "SoundMgr.h"

CBuildMenu::CBuildMenu()
	: CUI()
	, m_bClicked(false)
	, m_eSelete(BUILD_SELETE::NONE)
	, m_bMouseon(false)
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
}


CBuildMenu::~CBuildMenu()
{
}



void CBuildMenu::render(HDC _hdc)
{

	CUI::render(_hdc);
	if (m_bMouseon)
	{
		TransparentBlt(_hdc,
			(int)(GetFinalPos().x - GetSize().x / 2),
			(int)(GetFinalPos().y - GetSize().y / 2),
			(int)GetSize().x,
			(int)GetSize().y,
			m_pSelectTex->GetDC(),
			490, 935, 94, 83,
			RGB(255, 0, 255));
	}
}

void CBuildMenu::MouseOn(Vec2 _vMousePos)
{
	m_bMouseon = true;
}

void CBuildMenu::MouseOff()
{
	m_bMouseon = false;
}

void CBuildMenu::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	m_bClicked = true;
	//해당건물을 짓습니다.
	if (m_eSelete == BUILD_SELETE::BUILD_ARCHER)
	{
		//돈이 부족하면 그냥 넘어간다.
		if (CMapMgr::GetInst()->GetGold() < 50)
			return;
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() - 50);
		CArcher* buildArcher = new CArcher;
		buildArcher->SetPos(GetParent()->GetPos());
		buildArcher->SetFinalPos(buildArcher->GetPos());
		buildArcher->SetSize(Vec2(75.f, 75.f));
		buildArcher->SetBuildType(BUILD_SELETE::BUILD_ARCHER);
		buildArcher->SetFinalPos(buildArcher->GetPos());
		buildArcher->SetObjType(OBJ_TYPE::UI);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"archer_build1");
		CAnimator* pAnimtor = new CAnimator(buildArcher);
		pAnimtor->AddAnimation(L"archer_build1", pAnim);
		buildArcher->SetAnim(pAnimtor);
		buildArcher->Init();
		buildArcher->SetBuildTier(1);
		buildArcher->GetAnim()->PlayAnim(L"archer_build1", buildArcher, true);
		CStageMgr::GetInst()->GetCurStage()->AddObject(buildArcher, OBJ_TYPE::UI);

		GetParent()->SetDead();
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_BARRACKS)
	{
		//돈이 부족하면 그냥 넘어간다.
		if (CMapMgr::GetInst()->GetGold() < 50)
			return;
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() - 50);
		CBarracks* buildBarrack = new CBarracks;
		buildBarrack->SetPos(GetParent()->GetPos());
		buildBarrack->SetFinalPos(buildBarrack->GetPos());
		buildBarrack->SetSize(Vec2(75.f, 75.f));
		buildBarrack->SetBuildType(BUILD_SELETE::BUILD_BARRACKS);
		buildBarrack->SetFinalPos(buildBarrack->GetPos());
		buildBarrack->SetObjType(OBJ_TYPE::UI);
		CAnimator* pAnimtor = new CAnimator(buildBarrack);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_build1");
		pAnimtor->AddAnimation(L"barrack_build1", pAnim);
		buildBarrack->SetAnim(pAnimtor);
		buildBarrack->Init();
		buildBarrack->SetBuildTier(1);
		buildBarrack->GetAnim()->PlayAnim(L"barrack_build1", buildBarrack, true);
		CStageMgr::GetInst()->GetCurStage()->AddObject(buildBarrack, OBJ_TYPE::UI);

		GetParent()->SetDead();
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_MAGE)
	{
		//돈이 부족하면 그냥 넘어간다.
		if (CMapMgr::GetInst()->GetGold() < 50)
			return;
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() - 50);
		CMage* buildMage = new CMage;
		buildMage->SetPos(GetParent()->GetPos());
		buildMage->SetFinalPos(buildMage->GetPos());
		buildMage->SetSize(Vec2(75.f, 75.f));
		buildMage->SetBuildType(BUILD_SELETE::BUILD_MAGE);
		buildMage->SetFinalPos(buildMage->GetPos());
		buildMage->SetObjType(OBJ_TYPE::UI);
		CAnimator* pAnimtor = new CAnimator(buildMage);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"mage_build1_idle");
		pAnimtor->AddAnimation(L"mage_build1_idle", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"mage_build1_attack");
		pAnimtor->AddAnimation(L"mage_build1_attack", pAnim);
		buildMage->SetAnim(pAnimtor);
		buildMage->Init();
		buildMage->SetBuildTier(1);
		buildMage->GetAnim()->PlayAnim(L"mage_build1_idle", buildMage, true);
		CStageMgr::GetInst()->GetCurStage()->AddObject(buildMage, OBJ_TYPE::UI);

		GetParent()->SetDead();
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_CANNON)
	{
		//돈이 부족하면 그냥 넘어간다.
		if (CMapMgr::GetInst()->GetGold() < 50)
			return;
		tUnitInfo tInfo;
		tInfo.iAtt_pow = 10.f;

		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() - 50);
		CCannon* buildCannon = new CCannon;
		buildCannon->SetPos(GetParent()->GetPos());
		buildCannon->SetFinalPos(GetPos());
		buildCannon->SetSize(Vec2(75.f, 75.f));
		buildCannon->SetBuildType(BUILD_SELETE::BUILD_CANNON);
		buildCannon->SetFinalPos(buildCannon->GetPos());
		buildCannon->SetObjType(OBJ_TYPE::UI);
		CAnimator* pAnimtor = new CAnimator(buildCannon);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"cannon_build1");
		pAnimtor->AddAnimation(L"cannon_build1", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"cannon_attack1");
		pAnimtor->AddAnimation(L"cannon_attack1", pAnim);
		buildCannon->SetAnim(pAnimtor);
		buildCannon->SetInfo(tInfo);
		buildCannon->Init();
		buildCannon->SetBuildTier(1);
		buildCannon->GetAnim()->PlayAnim(L"cannon_build1", buildCannon, true);

		/*CCollider* pCol = new CCollider(buildCannon);
		pCol->SetFinalPos(buildCannon->GetPos());
		pCol->SetSize(Vec2(200.f, 200.f));
		pCol->SetColliderType(COLLIDER_TYPE::ELLIPSE);
		buildCannon->SetCollider(pCol);*/
		CStageMgr::GetInst()->GetCurStage()->AddObject(buildCannon, OBJ_TYPE::UI);

		GetParent()->SetDead();
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_SELL)
	{
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() + 25);
		CObj* pUnbuild = new CBuilding;
		pUnbuild->SetPos(GetParent()->GetPos());
		((CUI*)pUnbuild)->SetFinalPos(pUnbuild->GetPos());
		pUnbuild->SetSize(Vec2{ 108.f, 57 });
		pUnbuild->SetObjType(OBJ_TYPE::UI);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"archer_unbuild_none");
		CAnimation* pAnim2 = CResMgr::GetInst()->LoadAnimation(L"archer_unbuild_on");

		CAnimator* pAnimtor = new CAnimator(pUnbuild);
		pAnimtor->AddAnimation(L"archer_unbuild_none", pAnim);
		pAnimtor->AddAnimation(L"archer_unbuild_on", pAnim2);

		pUnbuild->SetAnim(pAnimtor);
		pUnbuild->Init();
		CStageMgr::GetInst()->GetCurStage()->AddObject(pUnbuild, OBJ_TYPE::UI);
		GetParent()->SetDead();
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_UPGRADE)
	{
		//돈이 부족하면 그냥 넘어간다.
		if (CMapMgr::GetInst()->GetGold() < 50)
			return;
		CMapMgr::GetInst()->SetGold(CMapMgr::GetInst()->GetGold() - 50);
		((CBuilding*)GetParent())->SetBuildTier(((CBuilding*)GetParent())->GetBuildTier() + 1);
		((CBuilding*)GetParent())->UpgradeBuild(((CBuilding*)GetParent())->GetBuildTier());
		
	}
	else if (m_eSelete == BUILD_SELETE::BUILD_MOVEPOINT)
	{
		CMapMgr::GetInst()->CLickModeOn();
		((CBarracks*)GetParent())->CreateMovePoint();
	}
}