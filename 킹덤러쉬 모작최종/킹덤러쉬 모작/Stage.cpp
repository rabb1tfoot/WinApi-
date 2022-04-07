#include "stdafx.h"
#include "Stage.h"
#include "Obj.h"
#include "Animation.h"
#include "Animator.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end(); ++iter)
		{
			//SAFE_DELETE((*iter));
			if (nullptr != *iter)
			{ delete *iter; *iter = nullptr; }
		}
	}
	m_arrObj->clear();

	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		vector<CAnimation*>::iterator iter = m_arrAnim.begin();
		for (; iter != m_arrAnim.end(); ++iter)
		{
			SAFE_DELETE((*iter));
		}
	}
	m_arrAnim.clear();
}


void CStage::update()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (nullptr != m_arrObj[i][j]->GetAnim())
				m_arrObj[i][j]->GetAnim()->update();
			m_arrObj[i][j]->update();
		}
	}
}

void CStage::eventUpdate()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j]->IsDead())
			{
				SAFE_DELETE(m_arrObj[i][j]);
				m_arrObj[i].erase(m_arrObj[i].begin() + j);
			}
		}
	}
}

void CStage::render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j]->IsDead())
				return;
			m_arrObj[i][j]->render(_hdc);
		}
	}
}

void CStage::ClearObject()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end(); ++iter)
		{
			SAFE_DELETE((*iter));
		}
		m_arrObj[i].clear();
	}
}

void CStage::ClearObject(OBJ_TYPE _etype)
{
	vector<CObj*>::iterator iter = m_arrObj[(UINT)_etype].begin();
	for (; iter != m_arrObj[(UINT)_etype].end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
}

int CStage::FindDigitSize(int _num)
{
	if (_num < 10)
		return 1;
	else if (_num < 100)
		return 2;
	else if (_num < 1000)
		return 3;
	else if (_num < 10000)
		return 4;

	assert(nullptr);
	
}

void CStage::AddObject(CObj * _pObj, OBJ_TYPE _etype)
{
	_pObj->SetObjType(_etype);
	m_arrObj[(UINT)_etype].push_back(_pObj);
}

void CStage::AddAnim(CAnimation * _pAnim)
{
	m_arrAnim.push_back(_pAnim);
}

CAnimation * CStage::GetAnim(const wchar_t * _name)
{
	for (UINT i = 0; i < m_arrAnim.size(); ++i)
	{
		wchar_t wName[100] = L"";
		wcscpy_s(wName,100, m_arrAnim[i]->GetName());
		if (!wcscmp(m_arrAnim[i]->GetName(), _name))
		{
			return m_arrAnim[i];
			break;
		}
	}
	return nullptr;
}
