#include "stdafx.h"
#include "Mage.h"
#include "ResMgr.h"
#include "Magician.h"
#include "Texture.h"
#include "BuildMenu.h"
#include "Magician.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "StageMgr.h"
#include "Stage.h"
#include "SoundMgr.h"

CMage::CMage()
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Mage_Ready.wav", L"Mage_Ready.wav");
	CSoundMgr::GetInst()->Play(L"Mage_Ready.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


CMage::~CMage()
{
	m_cMyMagician->SetDead();
}


void CMage::update()
{
	CUI::update();
	if (GetClick())
	{
		for (UINT i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->update();
		}
	}
	if (5 == GetBuildTier())
	{
		vector<CUI*> myChild = GetChild();
		myChild[0]->SetTexPos(Vec2(255.f, 510.f));
	}
}

void CMage::render(HDC _hdc)
{
	CUI::render(_hdc);
	// 선택이 되면 차일드도 랜더링해준다.
	if (GetClick())
	{
		TransparentBlt(_hdc,
			(int)(GetFinalPos().x - 203 / 2),
			(int)(GetFinalPos().y - 208 / 2),
			203, 208,
			m_pSelectTex->GetDC(),
			0, 814, 203, 208,
			RGB(255, 0, 255));
		for (UINT i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->render(_hdc);
		}
	}
}

void CMage::Init()
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
	//업그레이드 아이콘 생성
	CBuildMenu* pSell = new CBuildMenu;
	pSell->SetParent(this);
	pSell->SetTexture(pTex);
	pSell->SetObjType(OBJ_TYPE::UI);
	pSell->SetPos(Vec2(0.f, -80.f));
	pSell->SetSize(Vec2(82.f, 72.f));
	pSell->SetTexPos(Vec2(432, 664));
	pSell->SetEnable(false);
	pSell->SetSelectType(BUILD_SELETE::BUILD_UPGRADE);
	this->AddChild(pSell);
	//판매 아이콘 생성
	CBuildMenu*  pUpgrde = new CBuildMenu;
	pUpgrde->SetParent(this);
	pUpgrde->SetTexture(pTex);
	pUpgrde->SetObjType(OBJ_TYPE::UI);
	pUpgrde->SetPos(Vec2(0.f, 80.f));
	pUpgrde->SetSize(Vec2(82.f, 72.f));
	pUpgrde->SetTexPos(Vec2(553, 518));
	pUpgrde->SetEnable(false);
	pUpgrde->SetSelectType(BUILD_SELETE::BUILD_SELL);
	this->AddChild(pUpgrde);

	CreateMagician(0);
}


void CMage::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	SetClick(!GetClick());
	if (GetClick())
	{

		vector<CUI*> vChild = this->GetChild();
		for (UINT i = 0; i < vChild.size(); ++i)
			vChild[i]->SetEnable(true);
	}
	else
	{
		vector<CUI*> vChild = this->GetChild();
		for (UINT i = 0; i < vChild.size(); ++i)
			vChild[i]->SetEnable(false);
	}
}

void CMage::CreateMagician(int _tier)
{
	if (0 != _tier)
	{
		m_cMyMagician->SetDead();
	}

	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;

	if (0 != _tier)
	{
		tInfo.iAtt_pow = 20 * _tier;
	}

	CMagician*  magician = new CMagician;
	((CUnit*)magician)->SetInfo(tInfo);
	magician->SetPos(Vec2(this->GetPos().x, this->GetPos().y - 55.f));
	magician->SetBuild(this);
	magician->SetTier(_tier);
	magician->SetAttTime(-1.f);
	magician->SetSize(Vec2{ 0,0 });
	magician->SetObjType(OBJ_TYPE::ALLY_UNIT_IGNORE);
	CAnimator* anim = new CAnimator(magician);
	CAnimation* ani = CResMgr::GetInst()->LoadAnimation(L"mage_idle_left");
	anim->AddAnimation(L"mage_idle_left", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"mage_idle_right");
	anim->AddAnimation(L"mage_idle_right", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"mage_attack_right");
	anim->AddAnimation(L"mage_attack_right", ani);
	ani = CResMgr::GetInst()->LoadAnimation(L"mage_attack_left");
	anim->AddAnimation(L"mage_attack_left", ani);
	magician->SetAnim(anim);

	magician->GetAnim()->PlayAnim(L"mage_idle_left", magician, true);

	CCollider* pCol = new CCollider(magician);
	pCol->SetFinalPos(magician->GetPos());
	pCol->SetSize(Vec2(350.f, 350.f));
	pCol->SetColliderType(COLLIDER_TYPE::ELLIPSE);
	magician->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(magician, OBJ_TYPE::ALLY_UNIT_IGNORE);

	m_cMyMagician = magician;

}


void CMage::UpgradeBuild(int _tier)
{
	CreateMagician(_tier);
	CAnimation * ani = nullptr;
	switch (_tier)
	{
	case 2:
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build1_idle");
		//this->GetAnim()->AddAnimation(L"mage_build1_idle", ani);
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build1_attack");
		//this->GetAnim()->AddAnimation(L"mage_build1_attack", ani);
		//this->GetAnim()->PlayAnim(L"mage_build1_idle", this, true);
		//break;
		ani = CResMgr::GetInst()->LoadAnimation(L"mage_build2_idle");
		this->GetAnim()->AddAnimation(L"mage_build2_idle", ani);
		ani = CResMgr::GetInst()->LoadAnimation(L"mage_build2_attack");
		this->GetAnim()->AddAnimation(L"mage_build2_attack", ani);
		this->GetAnim()->PlayAnim(L"mage_build2_idle", this, true, Vec2(0.f, -10.f));
		break;
	case 3:
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build2_idle");
		//this->GetAnim()->AddAnimation(L"mage_build2_idle", ani);
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build2_attack");
		//this->GetAnim()->AddAnimation(L"mage_build2_attack", ani);
		//this->GetAnim()->PlayAnim(L"mage_build2_idle", this, true);
		//break;
		ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_idle");
		this->GetAnim()->AddAnimation(L"mage_build3_idle", ani);
		ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_attack");
		this->GetAnim()->AddAnimation(L"mage_build3_attack", ani);
		this->GetAnim()->PlayAnim(L"mage_build3_idle", this, true, Vec2{ -10.f, -25.f });
		break;
	case 4:
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_idle");
		//this->GetAnim()->AddAnimation(L"mage_build3_idle", ani);
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_attack");
		//this->GetAnim()->AddAnimation(L"mage_build3_attack", ani);
		//this->GetAnim()->PlayAnim(L"mage_build3_idle", this, true, Vec2{ -10.f, -15.f });
		break;
	case 5:
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_idle");
		//this->GetAnim()->AddAnimation(L"mage_build3_idle", ani);
		//ani = CResMgr::GetInst()->LoadAnimation(L"mage_build3_attack");
		//this->GetAnim()->AddAnimation(L"mage_build3_attack", ani);
		//this->GetAnim()->PlayAnim(L"mage_build3_idle", this, true, Vec2{ -10.f, -15.f });
		break;
	}
}