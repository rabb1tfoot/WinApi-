#include "stdafx.h"
#include "Barracks.h"
#include "ResMgr.h"
#include "Soldier.h"
#include "Texture.h"
#include "BuildMenu.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Obj_Coll.h"
#include "MapMgr.h"
#include "keyMgr.h"
#include "Unit.h"
#include "SoundMgr.h"

CBarracks::CBarracks()
	:m_bMoveCommand(false)
{
	m_pSelectTex = CResMgr::GetInst()->FindTexture(L"Quickmenu.bmp");

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Barrack_Ready.wav", L"Barrack_Ready.wav");
	CSoundMgr::GetInst()->Play(L"Barrack_Ready.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


CBarracks::~CBarracks()
{
	for (UINT i = 0; i < 3; ++i)
	{
		if (nullptr == m_arrMySoldier[i])
			continue;
		m_arrMySoldier[i]->SetDead();
		m_arrMySoldier[i] = nullptr;
	}
}

void CBarracks::update()
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
	//솔저가 하나라도 죽을시 솔저생성
	for (UINT i = 0; i < 3; ++i)
	{
		if (m_arrMySoldier[i] == nullptr && !m_bspawning[i])
		{
			m_bspawning[i] = true;
			m_SelectSpawn = i;
		}
	}
	if (m_bspawning[m_SelectSpawn])
	{
		m_fAccSpawn[m_SelectSpawn] += 1.f * DT;
		if (m_fAccSpawn[m_SelectSpawn] > 10.f)
		{
			CreateSoldier(GetBuildTier() - 1, 1, m_SelectSpawn);
			m_bspawning[m_SelectSpawn] = false;
			m_fAccSpawn[m_SelectSpawn] = 0.f;
			for (int i = 0; i < 3; ++i)
			{
				if (m_bspawning[i] == true)
					m_SelectSpawn = i;
			}
		}
	}

	//움직임 명령 실행
	if (nullptr != m_cMovePoint)
	{
		if (GetClick())
		{
			m_pmousepos = MOUSEPOS;
			m_vMousePos = m_pmousepos;
			((CUI*)m_cMovePoint)->SetPos(m_vMousePos);
		}

		if (m_vMousePos.x > GetPos().x - m_vBoundary.x && m_vMousePos.x < GetPos().x + m_vBoundary.x
			&&m_vMousePos.y > GetPos().y - m_vBoundary.y && m_vMousePos.y < GetPos().y + m_vBoundary.y)
		{
			if (MAP_SETTING::MAP_BLOCK == CMapMgr::GetInst()->GetClickOption())
			{
				m_cMovePoint->GetAnim()->PlayAnim(L"barrack_disclick", m_cMovePoint, false);

				SetClick(false);
				vector<CUI*> vChild = this->GetChild();
				for (UINT i = 0; i < vChild.size(); ++i)
					vChild[i]->SetEnable(false);
				CMapMgr::GetInst()->CLickModeOff();
				m_bMoveCommand = false;
			}
			else if (MAP_SETTING::MAP_NOTBLOCK == CMapMgr::GetInst()->GetClickOption())
			{
				m_cMovePoint->GetAnim()->PlayAnim(L"barrack_point", m_cMovePoint, false);

				SetClick(false);
				vector<CUI*> vChild = this->GetChild();
				for (UINT i = 0; i < vChild.size(); ++i)
					vChild[i]->SetEnable(false);
				CMapMgr::GetInst()->CLickModeOff();
				for (int i = 0; i < 3; ++i)
				{
					if (m_arrMySoldier[i] == nullptr)
						continue;
					m_arrMySoldier[i]->Move(m_vMousePos);
				}
				m_bMoveCommand = true;
			}
		}
		else
		{
			m_cMovePoint->GetAnim()->PlayAnim(L"barrack_disclick", m_cMovePoint, false);

			SetClick(false);
			vector<CUI*> vChild = this->GetChild();
			for (UINT i = 0; i < vChild.size(); ++i)
				vChild[i]->SetEnable(false);
			CMapMgr::GetInst()->CLickModeOff();
			m_bMoveCommand = false;
		}

		//애니메이션이 끝나면 지운다.
		if (m_cMovePoint->GetAnim()->GetCurAni()->IsEnd())
		{
			//효과음 생성
			if (m_bMoveCommand)
			{
				CSoundMgr::GetInst()->LoadSound(L"Barrack_Move.wav", L"Barrack_Move.wav");
				CSoundMgr::GetInst()->Play(L"Barrack_Move.wav");
				//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
				CSoundMgr::GetInst()->SetBGMVolume(100);
			}

			m_cMovePoint->SetDead();
			m_cMovePoint = nullptr;
			CMapMgr::GetInst()->SetClickOption(MAP_SETTING::NONE);
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_arrMySoldier[i] == nullptr || m_arrMySoldier[i]->IsDead())
			continue;
		if (m_arrMySoldier[i]->GetMoving())
		{
			if (i == 0)
			{
				m_arrMySoldier[i]->Move(Vec2(m_arrMySoldier[i]->GetMovingPos().x,
					m_arrMySoldier[i]->GetMovingPos().y), i);
			}
			else if (i == 1)
			{
				m_arrMySoldier[i]->Move(Vec2(m_arrMySoldier[i]->GetMovingPos().x,
					m_arrMySoldier[i]->GetMovingPos().y), i);
			}
			else if (i == 2)
			{
				m_arrMySoldier[i]->Move(Vec2(m_arrMySoldier[i]->GetMovingPos().x,
					m_arrMySoldier[i]->GetMovingPos().y), i);
			}
		}
	}
}

void CBarracks::render(HDC _hdc)
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
	//이동공간을 그린다
	if (nullptr != m_cMovePoint)
	{
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0,255,0));
		HPEN hOriginPen = (HPEN)SelectObject(_hdc, hPen);
		SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Rectangle(_hdc, int(GetPos().x - m_vBoundary.x), int(GetPos().y - m_vBoundary.y)
			, int(GetPos().x + m_vBoundary.x), int(GetPos().y + m_vBoundary.y));
	}

}

void CBarracks::Init()
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
	//이동 아이콘 생성
	CBuildMenu* pMovePoint = new CBuildMenu;
	pMovePoint->SetParent(this);
	pMovePoint->SetTexture(pTex);
	pMovePoint->SetObjType(OBJ_TYPE::UI);
	pMovePoint->SetPos(Vec2(-80.f, 0.f));
	pMovePoint->SetSize(Vec2(64.f, 64.f));
	pMovePoint->SetTexPos(Vec2(627, 595));
	pMovePoint->SetEnable(false);
	pMovePoint->SetSelectType(BUILD_SELETE::BUILD_MOVEPOINT);
	this->AddChild(pMovePoint);
	CreateSoldier(0);

	m_vBoundary = Vec2(200.f, 200.f);
}

void CBarracks::CreateMovePoint()
{
	if (nullptr != m_cMovePoint)
		return;
	m_cMovePoint = new CObj;
	m_cMovePoint->SetObjType(OBJ_TYPE::MAP_INGREDIENT);
	m_cMovePoint->SetPos(Vec2(0, 0));
	CAnimator* pAnimtor = new CAnimator(m_cMovePoint);
	CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_cursering");
	pAnimtor->AddAnimation(L"barrack_cursering", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_point");
	pAnimtor->AddAnimation(L"barrack_point", pAnim);
	pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_disclick");
	pAnimtor->AddAnimation(L"barrack_disclick", pAnim);
	m_cMovePoint->SetAnim(pAnimtor);
	m_cMovePoint->GetAnim()->PlayAnim(L"barrack_cursering", m_cMovePoint, true);
	CStageMgr::GetInst()->GetCurStage()->AddObject(m_cMovePoint, OBJ_TYPE::MAP_INGREDIENT);
}


void CBarracks::CreateSoldier(int _tier, int _amount, int _number)
{
	//if(0 == _tier)

	int amount = 3;
	if (0 != _amount)
		amount = _amount;
	for (UINT i = 0; i < amount; ++i)
	{

		tUnitInfo tInfo = {};
		tInfo.iAtt_pow = 10;
		tInfo.iMaxHealth = 50;
		tInfo.iCurHealth = tInfo.iMaxHealth;
		tInfo.iDef = 10;
		tInfo.eAttType = ATTACK_TYPE::MELEE;

		if (0 != _tier)
		{
			tInfo.iAtt_pow = 20 + 10 * _tier;
		}

		CResMgr::GetInst()->LoadTexture(L"Barracks.bmp", L"Texture\\Barracks.bmp");
		CSoldier* Soldier = new CSoldier;
		Soldier->SetBuild(this);
		Soldier->SetNumber(i);
		Soldier->SetInfo(tInfo);
		Soldier->SetPos(Vec2(this->GetPos().x  + i * 60, this->GetPos().y + 30.f));
		if (i == 1 || nullptr == m_arrMySoldier[1])
			Soldier->SetPos(Vec2(this->GetPos().x  + i * 60, this->GetPos().y + 30.f + 20.f));
		Soldier->SetSize(Vec2{ 0,0 });
		Soldier->SetTier(_tier);
		Soldier->SetObjType(OBJ_TYPE::ALLY_UNIT);
		CAnimator* pAnimtor = new CAnimator(Soldier);
		CAnimation* pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_attack_right");
		pAnimtor->AddAnimation(L"barrack_unit1_attack_right", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_attack_left");
		pAnimtor->AddAnimation(L"barrack_unit1_attack_left", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_move_left");
		pAnimtor->AddAnimation(L"barrack_unit1_move_left", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_move_right");
		pAnimtor->AddAnimation(L"barrack_unit1_move_right", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_idle_left");
		pAnimtor->AddAnimation(L"barrack_unit1_idle_left", pAnim);
		pAnim = CResMgr::GetInst()->LoadAnimation(L"barrack_unit1_idle_right");
		pAnimtor->AddAnimation(L"barrack_unit1_idle_right", pAnim);
		Soldier->SetAnim(pAnimtor);
		Soldier->GetAnim()->PlayAnim(L"barrack_unit1_idle_left", Soldier, true);

		CCollider* pCol = new CCollider(Soldier);
		pCol->SetFinalPos(Soldier->GetPos());
		pCol->SetSize(Vec2(25.f, 25.f));
		pCol->SetColliderType(COLLIDER_TYPE::RECT);
		Soldier->SetCollider(pCol);
		CStageMgr::GetInst()->GetCurStage()->AddObject(Soldier, OBJ_TYPE::ALLY_UNIT);

		CObj_Coll* cObj = new CObj_Coll;
		cObj->SetOwner(Soldier);
		cObj->SetObjType(OBJ_TYPE::ALLY_UNIT_RANGE);
		pCol = new CCollider(cObj);
		pCol->SetFinalPos(Soldier->GetPos());
		pCol->SetSize(Vec2(100.f, 100.f));
		cObj->SetCollider(pCol);
		Soldier->SetObjColl((CObj_Coll*)cObj);
		CStageMgr::GetInst()->GetCurStage()->AddObject(cObj, OBJ_TYPE::ALLY_UNIT_RANGE);
		if(_number == -1)
			m_arrMySoldier[i] = Soldier;
		else
			m_arrMySoldier[_number] = Soldier;
	}
}

void CBarracks::MouseLbtnClicked(Vec2 _vMousePos)
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
		if (nullptr == m_cMovePoint)
			return;
		m_cMovePoint->SetDead();
		m_cMovePoint = nullptr;
	}
}

void CBarracks::UpgradeBuild(int _tier)
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iMaxHealth = 100;
	tInfo.iCurHealth = 100;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;
	tInfo.iAtt_pow = 20 +  10 *_tier;

	for (int i = 0; i < 3; ++i)
	{
		if (nullptr == m_arrMySoldier[i])
			continue;
		m_arrMySoldier[i]->SetInfo(tInfo);
	}
	CAnimation * ani = nullptr;
	switch (_tier)
	{
	case 2:
		ani = CResMgr::GetInst()->LoadAnimation(L"barrack_build2");
		this->GetAnim()->AddAnimation(L"barrack_build2", ani);
		this->GetAnim()->PlayAnim(L"barrack_build2", this, true);
		break;
	case 3:
		ani = CResMgr::GetInst()->LoadAnimation(L"barrack_build3");
		this->GetAnim()->AddAnimation(L"barrack_build3", ani);
		this->GetAnim()->PlayAnim(L"barrack_build3", this, true);
		break;
	case 4:
		ani = CResMgr::GetInst()->LoadAnimation(L"barrack_build4");
		this->GetAnim()->AddAnimation(L"barrack_build4", ani);
		this->GetAnim()->PlayAnim(L"barrack_build4", this, true);
		break;
	case 5:
		ani = CResMgr::GetInst()->LoadAnimation(L"barrack_build5");
		this->GetAnim()->AddAnimation(L"barrack_build5", ani);
		this->GetAnim()->PlayAnim(L"barrack_build5", this, true);
		break;
	}
}