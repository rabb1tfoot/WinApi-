#include "stdafx.h"
#include "CArcher.h"
#include "ResMgr.h"
#include "Texture.h"
#include "BuildMenu.h"
#include "Ranger.h"
#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Stage.h"
#include "StageMgr.h"
#include "SoundMgr.h"


CArcher::CArcher()
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Archer_Ready.wav", L"Archer_Ready.wav");
	CSoundMgr::GetInst()->Play(L"Archer_Ready.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


CArcher::~CArcher()
{
	m_cMyRanger[0]->SetDead();
	m_cMyRanger[1]->SetDead();
}

void CArcher::update()
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

void CArcher::render(HDC _hdc)
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

void CArcher::Init()
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
	CBuildMenu*  pUpgrde= new CBuildMenu;
	pUpgrde->SetParent(this);
	pUpgrde->SetTexture(pTex);
	pUpgrde->SetObjType(OBJ_TYPE::UI);
	pUpgrde->SetPos(Vec2(0.f, 80.f));
	pUpgrde->SetSize(Vec2(82.f, 72.f));
	pUpgrde->SetTexPos(Vec2(553, 518));
	pUpgrde->SetEnable(false);
	pUpgrde->SetSelectType(BUILD_SELETE::BUILD_SELL);
	this->AddChild(pUpgrde);

	CreateRangers(0);
}


void CArcher::MouseLbtnClicked(Vec2 _vMousePos)
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

void CArcher::CreateRangers(int _tier)
{
	if (0 != _tier)
	{
		m_cMyRanger[0]->SetDead();
		m_cMyRanger[1]->SetDead();
	}

	for (UINT i = 0; i < 2; ++i)
	{

		tUnitInfo tInfo = {};
		tInfo.iAtt_pow = 10;
		tInfo.eAttType = ATTACK_TYPE::MELEE;

		if (0 != _tier)
		{
			tInfo.iAtt_pow = 20 * _tier;
		}

		CResMgr::GetInst()->LoadTexture(L"Arrow2.bmp", L"Texture\\Arrow2.bmp");
		CRanger*  ranger = new CRanger;
		((CUnit*)ranger)->SetInfo(tInfo);
		ranger->SetPos(Vec2(this->GetPos().x + i * 20, this->GetPos().y - 50.f));
		ranger->SetAttTime(-1.f * i);
		ranger->SetSize(Vec2{ 0,0 });
		ranger->SetTier(_tier);
		ranger->SetObjType(OBJ_TYPE::ALLY_UNIT_IGNORE);
		CAnimator* anim = new CAnimator(ranger);
		CAnimation* ani = CResMgr::GetInst()->LoadAnimation(L"archer_idle_left");
		anim->AddAnimation(L"archer_idle_left", ani);
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_idle_right");
		anim->AddAnimation(L"archer_idle_right", ani);
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_attack_right");
		anim->AddAnimation(L"archer_attack_right", ani);
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_attack_left");
		anim->AddAnimation(L"archer_attack_left", ani);
		ranger->SetAnim(anim);

		ranger->GetAnim()->PlayAnim(L"archer_idle_left", ranger, true);

		CCollider* pCol = new CCollider(ranger);
		pCol->SetFinalPos(ranger->GetPos());
		pCol->SetSize(Vec2(400.f, 400.f));
		pCol->SetColliderType(COLLIDER_TYPE::ELLIPSE);
		ranger->SetCollider(pCol);
		CStageMgr::GetInst()->GetCurStage()->AddObject(ranger, OBJ_TYPE::ALLY_UNIT_IGNORE);

		m_cMyRanger[i] = ranger;
	}
}


void CArcher::UpgradeBuild(int _tier)
{
	CreateRangers(_tier);
	CAnimation * ani = nullptr;
	switch (_tier)
	{
	case 2:
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_build2");
		this->GetAnim()->AddAnimation(L"archer_build2", ani);
		this->GetAnim()->PlayAnim(L"archer_build2", this, true);
		break;
	case 3:
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_build3");
		this->GetAnim()->AddAnimation(L"archer_build3", ani);
		this->GetAnim()->PlayAnim(L"archer_build3", this, true);
		break;
	case 4:
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_build4");
		this->GetAnim()->AddAnimation(L"archer_build4", ani);
		this->GetAnim()->PlayAnim(L"archer_build4", this, true);
		break;
	case 5:
		ani = CResMgr::GetInst()->LoadAnimation(L"archer_build5");
		this->GetAnim()->AddAnimation(L"archer_build5", ani);
		this->GetAnim()->PlayAnim(L"archer_build5", this, true);
		break;
	}
}