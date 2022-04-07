#include "stdafx.h"
#include "CCannon.h"
#include "ResMgr.h"
#include "BuildMenu.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Bomb.h"
#include "CannonBound.h"
#include "StageMgr.h"
#include "Stage.h"
#include "SoundMgr.h"


CCannon::CCannon()
	:m_fAttTime(0.f)
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Artillery_Ready.wav", L"Artillery_Ready.wav");
	CSoundMgr::GetInst()->Play(L"Artillery_Ready.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


CCannon::~CCannon()
{
	m_cBound->SetDead();
}


void CCannon::Init()
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

	//범위 오브젝트 생성

	CUnit* CannonBound = new CCannonBound;
	((CCannonBound*)CannonBound)->SetBuild(this);
	((CCannonBound*)CannonBound)->SetPow(m_tInfo.iAtt_pow);
	CannonBound->SetTier(0);
	((CCannonBound*)CannonBound)->SetPow(m_tInfo.iAtt_pow);
	CannonBound->SetPos(Vec2(this->GetPos().x, this->GetPos().y - 40.f));
	CannonBound->SetTier(0);
	CannonBound->SetAttTime(0.f);
	CannonBound->SetSize(Vec2{ 0,0 });
	CannonBound->SetObjType(OBJ_TYPE::ALLY_UNIT_IGNORE);
	m_cBound = CannonBound;

	CCollider* pCol = new CCollider(CannonBound);
	pCol->SetFinalPos(CannonBound->GetPos());
	pCol->SetSize(Vec2(300.f, 300.f));
	pCol->SetColliderType(COLLIDER_TYPE::ELLIPSE);
	CannonBound->SetCollider(pCol);
	CStageMgr::GetInst()->GetCurStage()->AddObject(CannonBound, OBJ_TYPE::ALLY_UNIT_IGNORE);
}

void CCannon::update()
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

void CCannon::render(HDC _hdc)
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

void CCannon::MouseLbtnClicked(Vec2 _vMousePos)
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


void CCannon::UpgradeBuild(int _tier)
{
	//건물자체공격력이 올라간다
	tUnitInfo info = GetInfo();
	info.iAtt_pow += 10 * _tier;
	info.eAttType = ATTACK_TYPE::MELEE;

	SetInfo(info);
}
