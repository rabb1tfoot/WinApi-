#include "stdafx.h"
#include "Building.h"
#include "Animator.h"
#include "BuildMenu.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Collider.h"
#include "SoundMgr.h"


CBuilding::CBuilding()
	: m_bClicked(false)
	, m_pSelectTex(nullptr)
	, m_eBuildType(BUILD_SELETE::NONE)
	, m_iBuildTier(0)
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");
}


CBuilding::~CBuilding()
{
}

void CBuilding::update()
{
	CUI::update();
	// 선택이 되면 차일드도 업데이트해준다.
	if (m_bClicked)
	{
		for (UINT i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->update();
		}
	}
}

void CBuilding::render(HDC _hdc)
{
	CUI::render(_hdc);
	// 선택이 되면 차일드도 랜더링해준다.
	if (m_bClicked)
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

void CBuilding::Init()
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");

	//아처아이콘 생성
	CBuildMenu* archer = new CBuildMenu;
	archer->SetParent(this);
	archer->SetTexture(pTex);
	archer->SetObjType(OBJ_TYPE::UI);
	archer->SetPos(Vec2(-80.f, -80.f));
	archer->SetFinalPos(Vec2(GetPos().x -80.f, GetPos().y - 80.f));
	archer->SetSize(Vec2(82.f, 72.f));
	archer->SetTexPos(Vec2(772, 664));
	archer->SetEnable(false);
	archer->SetSelectType(BUILD_SELETE::BUILD_ARCHER);
	this->AddChild(archer);

	//배럭아이콘 생성
	CBuildMenu* barracks = new CBuildMenu;
	barracks->SetParent(this);
	barracks->SetTexture(pTex);
	barracks->SetObjType(OBJ_TYPE::UI);
	barracks->SetPos(Vec2(-80.f, 80.f));
	barracks->SetFinalPos(Vec2(GetPos().x - 80.f, GetPos().y + 80.f));
	barracks->SetSize(Vec2(82.f, 72.f));
	barracks->SetTexPos(Vec2(256, 587));
	barracks->SetEnable(false);
	barracks->SetSelectType(BUILD_SELETE::BUILD_BARRACKS);
	this->AddChild(barracks);

	//캐논아이콘 생성
	CBuildMenu* cannon = new CBuildMenu;
	cannon->SetParent(this);
	cannon->SetTexture(pTex);
	cannon->SetObjType(OBJ_TYPE::UI);
	cannon->SetPos(Vec2(80.f, 80.f));
	cannon->SetFinalPos(Vec2(GetPos().x + 80.f, GetPos().y + 80.f));
	cannon->SetSize(Vec2(82.f, 72.f));
	cannon->SetTexPos(Vec2(344, 587));
	cannon->SetEnable(false);
	cannon->SetSelectType(BUILD_SELETE::BUILD_CANNON);
	this->AddChild(cannon);

	//메이지아이콘 생성
	CBuildMenu* mage = new CBuildMenu;
	mage->SetParent(this);
	mage->SetTexture(pTex);
	mage->SetObjType(OBJ_TYPE::UI);
	mage->SetPos(Vec2(80.f, -80.f));
	mage->SetFinalPos(Vec2(GetPos().x + 80.f, GetPos().y - 80.f));
	mage->SetSize(Vec2(82.f, 72.f));
	mage->SetTexPos(Vec2(258, 742));
	mage->SetEnable(false);
	mage->SetSelectType(BUILD_SELETE::BUILD_MAGE);
	this->AddChild(mage);
}


void CBuilding::MouseOn(Vec2 _vMousePos)
{
	if (GetBuildType() == BUILD_SELETE::NONE)
		this->GetAnim()->PlayAnim(L"archer_unbuild_on", this, true);
}

void CBuilding::MouseOff()
{
	if (!m_bClicked)
	{
		if (GetBuildType() == BUILD_SELETE::NONE)
			this->GetAnim()->PlayAnim(L"archer_unbuild_none", this, true);
	}
}

void CBuilding::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);

	m_bClicked = !m_bClicked;
	if (m_bClicked)
	{
		vector<CUI*> vChild = this->GetChild();
		for (int i = 0; i < vChild.size(); ++i)
			vChild[i]->SetEnable(true);
	}
	else
	{
		vector<CUI*> vChild = this->GetChild();
		for (int i = 0; i < vChild.size(); ++i)
			vChild[i]->SetEnable(false);
	}
	

}

