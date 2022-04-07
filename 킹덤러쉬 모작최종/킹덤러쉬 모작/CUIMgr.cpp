#include "stdafx.h"
#include "CUIMgr.h"
#include "Stage.h"
#include "StageMgr.h"
#include "KeyMgr.h"
#include "UI.h"


CUIMgr::CUIMgr()
	:m_bOnElderUI(false)
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::update()
{
	const CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
	const vector<CObj*>& vecUI = pCurStage->GetVecObj(OBJ_TYPE::UI);
	const vector<CObj*>& vecHeroUI = pCurStage->GetVecObj(OBJ_TYPE::ALLY_HERO);
	const vector<CObj*>& vecElderUI = pCurStage->GetVecObj(OBJ_TYPE::ELDER_UI);

	//Vec2 vMousePos = MOUSEPOS;
	Vec2 vMousePos;
	vMousePos.x = (float)MOUSEPOS.x;
	vMousePos.y = (float)MOUSEPOS.y;

	if (!m_bOnElderUI)
	{
		for (UINT i = 0; i < vecUI.size(); ++i)
		{
			CUI* pTargetUI = FindTargetUI((CUI*)vecUI[i]);
			if (nullptr != pTargetUI)
			{
				if (!pTargetUI->GetEnable())
					return;
				pTargetUI->MouseOn(vMousePos);

				if (KEYTAB(KEY_TYPE::KEY_LBTN))
				{
					pTargetUI->MouseLbtnDown(vMousePos);
				}
				else if (KEYAWAY(KEY_TYPE::KEY_LBTN))
				{
					// UI 위에서 왼쪽 마우스를 뗀 경우
					pTargetUI->MouseLbtnUp(vMousePos);

					// 이젠에 UI 위에서 왼쪽버튼 누른적이 있었다.
					if (pTargetUI->IsMouseLbtnDown())
					{
						pTargetUI->MouseLbtnClicked(vMousePos);
						if (false == pTargetUI->GetLayer())
							return;
					}
				}
			}
			else
			{
				((CUI*)vecUI[i])->MouseOff();
			}
		}
	}

	for (UINT i = 0; i < vecHeroUI.size(); ++i)
	{
		CUI* pTargetUI = FindElderTargetUI((CUI*)vecHeroUI[i]);
		if (nullptr != pTargetUI)
		{
			if (!pTargetUI->GetEnable())
				return;
			pTargetUI->MouseOn(vMousePos);

			if (KEYTAB(KEY_TYPE::KEY_LBTN))
			{
				pTargetUI->MouseLbtnDown(vMousePos);
			}
			else if (KEYAWAY(KEY_TYPE::KEY_LBTN))
			{
				// UI 위에서 왼쪽 마우스를 뗀 경우
				pTargetUI->MouseLbtnUp(vMousePos);

				// 이젠에 UI 위에서 왼쪽버튼 누른적이 있었다.
				if (pTargetUI->IsMouseLbtnDown())
				{
					pTargetUI->MouseLbtnClicked(vMousePos);
					return;
				}
			}
		}
		else
		{
			((CUI*)vecHeroUI[i])->MouseOff();
		}
	}

	for (UINT i = 0; i < vecElderUI.size(); ++i)
	{
		CUI* pTargetUI = FindElderTargetUI((CUI*)vecElderUI[i]);

		if (nullptr != pTargetUI)
		{
			if (!pTargetUI->GetEnable())
				return;
			pTargetUI->MouseOn(vMousePos);

			if (KEYTAB(KEY_TYPE::KEY_LBTN))
			{
				pTargetUI->MouseLbtnDown(vMousePos);
			}
			else if (KEYAWAY(KEY_TYPE::KEY_LBTN))
			{
				// UI 위에서 왼쪽 마우스를 뗀 경우
				pTargetUI->MouseLbtnUp(vMousePos);

				// 이젠에 UI 위에서 왼쪽버튼 누른적이 있었다.
				if (pTargetUI->IsMouseLbtnDown())
				{
					pTargetUI->MouseLbtnClicked(vMousePos);
					return;
				}
			}
		}
		else
		{
			((CUI*)vecElderUI[i])->MouseOff();
		}
	}

}


CUI * CUIMgr::FindTargetUI(CUI * _pParentUI)
{
	CUI* pTargetUI = nullptr;
	Vec2 vMousePos;
	vMousePos.x = (float)MOUSEPOS.x;
	vMousePos.y = (float)MOUSEPOS.y;

	list<CUI*> queue;

	queue.push_back(_pParentUI);

	while (true)
	{

		if (queue.empty())
			break;

		CUI* pUI = queue.front();
		queue.pop_front();
		if (((CObj*)pUI)->GetEnable())
		{
			if (pUI->IsOn(vMousePos))
			{
				pTargetUI = pUI;
			}
			else
			{
				pUI->MouseOff();
			}
			vector<CUI*> vecChild = pUI->GetChild();
			for (int i = 0; i < vecChild.size(); ++i)
			{
				queue.push_back(vecChild[i]);
			}
		}
	}
	return pTargetUI;
}

CUI * CUIMgr::FindElderTargetUI(CUI * _pParentUI)
{
	CUI* pTargetUI = nullptr;
	CUI* pUI = _pParentUI;
	Vec2 vMousePos;
	vMousePos.x = (float)MOUSEPOS.x;
	vMousePos.y = (float)MOUSEPOS.y;

	if (pUI->IsOn(vMousePos))
	{
		pTargetUI = pUI;
	}
	else
	{
		pUI->MouseOff();
	}
	return pTargetUI;
}
