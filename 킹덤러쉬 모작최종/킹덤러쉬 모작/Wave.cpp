#include "stdafx.h"
#include "Wave.h"
#include "MapMgr.h"
#include "Obj.h"
#include "Goblin.h"
#include "Animation.h"
#include "Animator.h"
#include "ResMgr.h"
#include "Collider.h"
#include "MapMgr.h"
#include "Obj_Coll.h"
#include "StageMgr.h"
#include "Stage.h"
#include "Obj.h"
#include "Stage_Quit.h"
#include "Stage_Try.h"
#include "FatOrc.h"
#include "Bandit.h"
#include "SoundMgr.h"
#include "App.h"

CWave::CWave()
	: m_iCurrentWave(0)
	, m_numfoMon(0)
	, m_fSpawnAccTimer(0.f)
	, m_enable(true)
	, m_StageClear(false)
	, m_bChkStageClear(false)
	, m_bEnd(false)
	, m_fAniValue(0.f)
	, m_iSign(1)
	, m_iStageNum(0)
	, m_vStartPoint(Vec2(0.f, 0.f))
{
}


CWave::~CWave()
{
	m_vWaveInfo.clear();
}



void CWave::update()
{
	CUI::update();
	if (!m_enable)
	{
		m_fSpawnAccTimer += DT;
		if (m_fSpawnAccTimer > 3.f)
		{
			m_fSpawnAccTimer = 0.f;
			for (int i = m_waveStack; i < m_vWaveInfo.size(); ++i)
			{
				//맞는 레벨에 몬스터를 생성한다.
				if (m_vWaveInfo[i].waveLevel == m_iCurrentWave)
				{
					//몬스터 종류에 맞춰서 생성한다.
					if (MONSTER_TYPE::GOBLIN == m_vWaveInfo[i].type)
					{
						//갯수만큼 모두 생성한경우 넘어간다.
						if (m_vWaveInfo[i].done)
							continue;

						if (m_numfoMon == m_vWaveInfo[i].num)
						{
							m_numfoMon = 0;
							m_vWaveInfo[i].done = true;
						}
						CreateGoblin();
						++m_numfoMon;
						return;
					}
					else if (MONSTER_TYPE::OGRE == m_vWaveInfo[i].type)
					{
						//갯수만큼 모두 생성한경우 넘어간다.
						if (m_vWaveInfo[i].done)
							continue;

						if (m_numfoMon == m_vWaveInfo[i].num)
						{
							m_numfoMon = 0;
							m_vWaveInfo[i].done = true;
						}
						CreateFatorc();
						++m_numfoMon;
						return;
					}
					else if (MONSTER_TYPE::BANDIT == m_vWaveInfo[i].type)
					{
						//갯수만큼 모두 생성한경우 넘어간다.
						if (m_vWaveInfo[i].done)
							continue;

						if (m_numfoMon == m_vWaveInfo[i].num)
						{
							m_numfoMon = 0;
							m_vWaveInfo[i].done = true;
						}
						CreateBandit();
						++m_numfoMon;
						return;
					}
				}
				//다음 레벨의 웨이브를 생성해야하는 경우
				else
				{	//이전의 웨이브 스텍을 변경한다.(레벨에 맞게 실행하기 위해서)
					m_waveStack = i;
					m_enable = true;
					return;
				}
			}
			//최종 웨이브의 마지막 몬스터가 소환
			if (m_waveStack + 1 == CMapMgr::GetInst()->GetMaxWave() && m_bChkStageClear == false)
			{
				//스테이지 클리어 여부 체크 변수
				m_bChkStageClear = true;
				return;
			}
		}

		//하트가 다떨어진경우 스테이지 실패
		if (CMapMgr::GetInst()->GetLife() < 1)
		{
			if (!m_bEnd)
			{
				//효과음 생성
				CSoundMgr::GetInst()->LoadSound(L"Sound_QuestFailed.wav", L"Sound_QuestFailed.wav");
				CSoundMgr::GetInst()->PlayBGM(L"Sound_QuestFailed.wav", false);
				//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
				CSoundMgr::GetInst()->SetBGMVolume(100);

				CStageMgr::GetInst()->GetCurStage()->Exit();
				m_bEnd = true;
				CTimeMgr::GetInst()->SetDouble(false);
				CMapMgr::GetInst()->DeleteRoute();
				CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"ResultMaterial.bmp", L"Texture\\ResultMaterial.bmp");
				CObj* DefeatMenu = new CObj;
				DefeatMenu->SetTexture(pTex);
				DefeatMenu->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
				DefeatMenu->SetSize(Vec2{ 613.f, 506.f });
				DefeatMenu->SetTexPos(Vec2(1.f, 518));
				DefeatMenu->SetObjType(OBJ_TYPE::BACKGROUND);
				CStageMgr::GetInst()->GetCurStage()->AddObject(DefeatMenu, OBJ_TYPE::BACKGROUND);

				pTex = CResMgr::GetInst()->FindTexture(L"ResultMaterial.bmp");
				CUI* QuitUI = new CStage_Quit;
				QuitUI->SetTexture(pTex);
				QuitUI->SetPos(Vec2{ float(WINSIZE_X / 2) - 150.f, float(WINSIZE_Y / 2) + 150.f });
				QuitUI->SetSize(Vec2{ 182.f, 80.f });
				QuitUI->SetFinalPos(QuitUI->GetPos());
				SetTexPos(Vec2(437.f, 433.f));
				QuitUI->SetObjType(OBJ_TYPE::UI);
				CStageMgr::GetInst()->GetCurStage()->AddObject(QuitUI, OBJ_TYPE::UI);

				pTex = CResMgr::GetInst()->FindTexture(L"ResultMaterial.bmp");
				CUI* TryUI = new CStage_Try;
				TryUI->SetTexture(pTex);
				TryUI->SetPos(Vec2{ float(WINSIZE_X / 2 + 150.f), float(WINSIZE_Y / 2) + 150.f });
				TryUI->SetSize(Vec2{ 178.f, 77.f });
				TryUI->SetFinalPos(TryUI->GetPos());
				TryUI->SetTexPos(Vec2(544.f, 297));
				TryUI->SetObjType(OBJ_TYPE::UI);
				CStageMgr::GetInst()->GetCurStage()->AddObject(TryUI, OBJ_TYPE::UI);
				return;
			}

		}

		//마지막 몬스터가 죽을경우 스테이지 클리어
		if (m_bChkStageClear)
		{
			vector<CObj*> vObj = CStageMgr::GetInst()->GetCurStage()->GetVecObj(OBJ_TYPE::ENEMY_UNIT);
			for (int i = 0; i < vObj.size(); ++i)
			{
				//모든몬스터의 사망여부 확인 후
				if (!vObj[i]->IsDead())
					return;
			}
			//효과음 생성
			CSoundMgr::GetInst()->LoadSound(L"Sound_QuestCompleted.wav", L"Sound_QuestCompleted.wav");
			CSoundMgr::GetInst()->PlayBGM(L"Sound_QuestCompleted.wav", false);
			//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
			CSoundMgr::GetInst()->SetBGMVolume(100);
			CTimeMgr::GetInst()->SetDouble(false);
			CMapMgr::GetInst()->DeleteRoute();
			CMapMgr::GetInst()->SetClear(m_iStageNum);
			CStageMgr::GetInst()->GetCurStage()->Exit();
			m_bEnd = true;
			CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"ResultMaterial.bmp", L"Texture\\ResultMaterial.bmp");
			CObj* WinMenu = new CObj;
			WinMenu->SetTexture(pTex);
			WinMenu->SetPos(Vec2{ float(WINSIZE_X / 2), float(WINSIZE_Y / 2) });
			WinMenu->SetSize(Vec2{ 533.f, 418.f });
			WinMenu->SetTexPos(Vec2(10.f, 10));
			WinMenu->SetObjType(OBJ_TYPE::BACKGROUND);
			CStageMgr::GetInst()->GetCurStage()->AddObject(WinMenu, OBJ_TYPE::BACKGROUND);

			pTex = CResMgr::GetInst()->FindTexture(L"ResultMaterial.bmp");
			CUI* QuitUI = new CStage_Quit;
			QuitUI->SetTexture(pTex);
			QuitUI->SetPos(Vec2{ float(WINSIZE_X / 2) - 150.f, float(WINSIZE_Y / 2) + 150.f });
			QuitUI->SetSize(Vec2{ 182.f, 80.f });
			QuitUI->SetFinalPos(QuitUI->GetPos());
			SetTexPos(Vec2(437.f, 433.f));
			QuitUI->SetObjType(OBJ_TYPE::UI);
			CStageMgr::GetInst()->GetCurStage()->AddObject(QuitUI, OBJ_TYPE::UI);

			pTex = CResMgr::GetInst()->FindTexture(L"ResultMaterial.bmp");
			CUI* TryUI = new CStage_Try;
			TryUI->SetTexture(pTex);
			TryUI->SetPos(Vec2{ float(WINSIZE_X / 2 + 150.f), float(WINSIZE_Y / 2) + 150.f });
			TryUI->SetSize(Vec2{ 178.f, 77.f });
			TryUI->SetFinalPos(TryUI->GetPos());
			TryUI->SetTexPos(Vec2(544.f, 297));
			TryUI->SetObjType(OBJ_TYPE::UI);
			CStageMgr::GetInst()->GetCurStage()->AddObject(TryUI, OBJ_TYPE::UI);


		}
	}
}

void CWave::render(HDC _hdc)
{
	if (m_enable)
	{
		CUI::render(_hdc);
	
		SetPos(Vec2(GetPos().x, GetPos().y + 0.1f * m_iSign));
		m_fAniValue += 0.1f;
		if (m_fAniValue >= 10.f)
		{
			m_fAniValue = 0.f;
			m_iSign = m_iSign* -1;
		}
	
	}
}

void CWave::AddWave(int _waveNum, MONSTER_TYPE _type, int _num)
{
	tWaveInfo _Info = { _waveNum, _type, _num, false };
	m_vWaveInfo.push_back(_Info);
}

void CWave::MouseLbtnClicked(Vec2 _vMousePos)
{
	if (false == m_enable)
		return;
	else
	{
		m_enable = false;
		++m_iCurrentWave;
		CMapMgr::GetInst()->SetCurrentWave(CMapMgr::GetInst()->GetCurrentWave() + 1);
	}

	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}

void CWave::CreateGoblin()
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iAtt_range = Vec2(0.f, 0.f);
	tInfo.iMaxHealth = 100;
	tInfo.iCurHealth = 100;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;

	CResMgr::GetInst()->LoadTexture(L"Goblin.bmp", L"Texture\\Goblin.bmp");
	CObj* Goblin = new CGoblin;
	((CUnit*)Goblin)->SetInfo(tInfo);
	Goblin->SetPos(m_vStartPoint);
	Goblin->SetSize(Vec2{ 0,0 });
	Goblin->SetObjType(OBJ_TYPE::ENEMY_UNIT);
	CAnimator* pAnimtor = new CAnimator(Goblin);
	CAnimation* pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_move_back");
	pAnimtor->AddAnimation(L"goblin_move_back", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_move_front");
	pAnimtor->AddAnimation(L"goblin_move_front", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_move_right");
	pAnimtor->AddAnimation(L"goblin_move_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_move_left");
	pAnimtor->AddAnimation(L"goblin_move_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_idle_right");
	pAnimtor->AddAnimation(L"goblin_idle_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_idle_left");
	pAnimtor->AddAnimation(L"goblin_idle_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_attack_left");
	pAnimtor->AddAnimation(L"goblin_attack_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"goblin_attack_right");
	pAnimtor->AddAnimation(L"goblin_attack_right", pAnim2);
	Goblin->SetAnim(pAnimtor);

	//몬스터 충돌체
	CCollider* pCol = new CCollider(Goblin);
	pCol->SetFinalPos(Goblin->GetPos());
	pCol->SetSize(Vec2(25.f, 25.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	Goblin->SetCollider(pCol);

	((CGoblin*)Goblin)->SetRoute(CMapMgr::GetInst()->GetRoute());
	CStageMgr::GetInst()->GetCurStage()->AddObject(Goblin, OBJ_TYPE::ENEMY_UNIT);

	//몬스터 범위 충돌체
	CObj* gObj = new CObj_Coll;
	((CObj_Coll*)gObj)->SetOwner(Goblin);
	gObj->SetObjType(OBJ_TYPE::ENEMY_UNIT_RANGE);
	pCol = new CCollider(gObj);
	pCol->SetSize(Vec2(200.f, 200.f));
	pCol->SetFinalPos(Goblin->GetPos());
	gObj->SetCollider(pCol);
	((CUnit*)Goblin)->SetObjColl((CObj_Coll*)gObj);
	CStageMgr::GetInst()->GetCurStage()->AddObject(gObj, OBJ_TYPE::ENEMY_UNIT_RANGE);
	Goblin->GetAnim()->PlayAnim(L"goblin_move_front", Goblin, true);
}

void CWave::CreateFatorc()
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iAtt_range = Vec2(0.f, 0.f);
	tInfo.iMaxHealth = 100;
	tInfo.iCurHealth = 100;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;

	CResMgr::GetInst()->LoadTexture(L"FatOrc.bmp", L"Texture\\FatOrc.bmp");
	CObj* FatOrc = new CFatOrc;
	((CUnit*)FatOrc)->SetInfo(tInfo);
	FatOrc->SetPos(m_vStartPoint);
	FatOrc->SetSize(Vec2{ 0,0 });
	FatOrc->SetObjType(OBJ_TYPE::ENEMY_UNIT);
	CAnimator* pAnimtor = new CAnimator(FatOrc);
	CAnimation* pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_move_back");
	pAnimtor->AddAnimation(L"fatorc_move_back", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_move_front");
	pAnimtor->AddAnimation(L"fatorc_move_front", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_move_right");
	pAnimtor->AddAnimation(L"fatorc_move_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_move_left");
	pAnimtor->AddAnimation(L"fatorc_move_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_idle_right");
	pAnimtor->AddAnimation(L"fatorc_idle_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_idle_left");
	pAnimtor->AddAnimation(L"fatorc_idle_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_attack_left");
	pAnimtor->AddAnimation(L"fatorc_attack_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"fatorc_attack_right");
	pAnimtor->AddAnimation(L"fatorc_attack_right", pAnim2);
	FatOrc->SetAnim(pAnimtor);

	//몬스터 충돌체
	CCollider* pCol = new CCollider(FatOrc);
	pCol->SetFinalPos(FatOrc->GetPos());
	pCol->SetSize(Vec2(30.f, 30.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	FatOrc->SetCollider(pCol);

	((CFatOrc*)FatOrc)->SetRoute(CMapMgr::GetInst()->GetRoute());
	CStageMgr::GetInst()->GetCurStage()->AddObject(FatOrc, OBJ_TYPE::ENEMY_UNIT);

	//몬스터 범위 충돌체
	CObj* gObj = new CObj_Coll;
	((CObj_Coll*)gObj)->SetOwner(FatOrc);
	gObj->SetObjType(OBJ_TYPE::ENEMY_UNIT_RANGE);
	pCol = new CCollider(gObj);
	pCol->SetSize(Vec2(200.f, 200.f));
	pCol->SetFinalPos(FatOrc->GetPos());
	gObj->SetCollider(pCol);
	((CUnit*)FatOrc)->SetObjColl((CObj_Coll*)gObj);
	CStageMgr::GetInst()->GetCurStage()->AddObject(gObj, OBJ_TYPE::ENEMY_UNIT_RANGE);
	FatOrc->GetAnim()->PlayAnim(L"fatorc_move_front", FatOrc, true);
}

void CWave::CreateBandit()
{
	tUnitInfo tInfo = {};
	tInfo.iAtt_pow = 10;
	tInfo.iAtt_range = Vec2(0.f, 0.f);
	tInfo.iMaxHealth = 100;
	tInfo.iCurHealth = 100;
	tInfo.iDef = 10;
	tInfo.eAttType = ATTACK_TYPE::MELEE;

	CResMgr::GetInst()->LoadTexture(L"Bandit.bmp", L"Texture\\Bandit.bmp");
	CObj* Bandit = new CBandit;
	((CUnit*)Bandit)->SetInfo(tInfo);
	Bandit->SetPos(m_vStartPoint);
	Bandit->SetSize(Vec2{ 0,0 });
	Bandit->SetObjType(OBJ_TYPE::ENEMY_UNIT);
	CAnimator* pAnimtor = new CAnimator(Bandit);
	CAnimation* pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_move_front");
	pAnimtor->AddAnimation(L"bandit_move_front", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_move_right");
	pAnimtor->AddAnimation(L"bandit_move_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_move_left");
	pAnimtor->AddAnimation(L"bandit_move_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_idle_right");
	pAnimtor->AddAnimation(L"bandit_idle_right", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_idle_left");
	pAnimtor->AddAnimation(L"bandit_idle_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_attack_left");
	pAnimtor->AddAnimation(L"bandit_attack_left", pAnim2);
	pAnim2 = CResMgr::GetInst()->LoadAnimation(L"bandit_attack_right");
	pAnimtor->AddAnimation(L"bandit_attack_right", pAnim2);
	Bandit->SetAnim(pAnimtor);

	//몬스터 충돌체
	CCollider* pCol = new CCollider(Bandit);
	pCol->SetFinalPos(Bandit->GetPos());
	pCol->SetSize(Vec2(30.f, 30.f));
	pCol->SetColliderType(COLLIDER_TYPE::RECT);
	Bandit->SetCollider(pCol);

	((CFatOrc*)Bandit)->SetRoute(CMapMgr::GetInst()->GetRoute());
	CStageMgr::GetInst()->GetCurStage()->AddObject(Bandit, OBJ_TYPE::ENEMY_UNIT);

	//몬스터 범위 충돌체
	CObj* gObj = new CObj_Coll;
	((CObj_Coll*)gObj)->SetOwner(Bandit);
	gObj->SetObjType(OBJ_TYPE::ENEMY_UNIT_RANGE);
	pCol = new CCollider(gObj);
	pCol->SetSize(Vec2(200.f, 200.f));
	pCol->SetFinalPos(Bandit->GetPos());
	gObj->SetCollider(pCol);
	((CUnit*)Bandit)->SetObjColl((CObj_Coll*)gObj);
	CStageMgr::GetInst()->GetCurStage()->AddObject(gObj, OBJ_TYPE::ENEMY_UNIT_RANGE);
	Bandit->GetAnim()->PlayAnim(L"bandit_move_front", Bandit, true);
}
