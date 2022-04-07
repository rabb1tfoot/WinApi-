#include "stdafx.h"
#include "CollisionMgr.h"

#include "StageMgr.h"
#include "Stage.h"
#include "Obj.h"
#include "Collider.h"


CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (UINT j = i; j < (UINT)OBJ_TYPE::END; ++j)
		{
			if (m_arrCheck[i] & (1 << j))
			{
				CollisionGroup(i, j);
			}
		}
	}
}

void CCollisionMgr::CollisionCheck(OBJ_TYPE _Left, OBJ_TYPE _Right)
{
	UINT iIdx = (UINT)(_Left < _Right ? _Left : _Right);
	UINT iBitIdx = iIdx == (UINT)_Left ? (UINT)_Right : (UINT)_Left;
	m_arrCheck[iIdx] |= (1 << iBitIdx);
}

void CCollisionMgr::CollisionGroup(UINT _left, UINT _right)
{
	const CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();

	const vector<CObj*>& vecLeft = pCurStage->GetVecObj((OBJ_TYPE)_left);
	const vector<CObj*>& vecRight = pCurStage->GetVecObj((OBJ_TYPE)_right);
	COL_ID colID;
	for (UINT i = 0; i < vecLeft.size(); ++i)
	{
		for (UINT j = 0; j < vecRight.size(); ++j)
		{
			if (vecLeft[i]->GetCollider() == nullptr || vecRight[j]->GetCollider() == nullptr)
				continue;
			//�ڽŰ� �浹�Ұ�� �Ѿ��
			if (vecLeft[i] == vecRight[j])
				continue;
			colID.left = vecLeft[i]->GetCollider()->GetID();
			colID.right = vecRight[j]->GetCollider()->GetID();

			map<unsigned long long, bool>::iterator iter = m_mapID.find(colID.ID);

			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				if (iter == m_mapID.end())
				{
					// �浹 ���� ��ϵ��� ���� ==> �浹���� ����					
					vecLeft[i]->GetCollider()->OnCollisionEnter(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionEnter(vecLeft[i]->GetCollider());
					m_mapID.insert(make_pair(colID.ID, true));
				}
				else if (false == iter->second)
				{
					//ù�浹
					vecLeft[i]->GetCollider()->OnCollisionEnter(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionEnter(vecLeft[i]->GetCollider());
					iter->second = true;
				}
				else
				{
					//�浹��
					vecLeft[i]->GetCollider()->OnCollision(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollision(vecLeft[i]->GetCollider());
				}
			}
			else
			{
				if (iter != m_mapID.end() && true == iter->second)
				{
					//���������ӿ��� �浹�ϰ� ���� �����ӿ����� �浹 ���
					vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}
}


bool CCollisionMgr::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	float fDist = abs(_pLeft->GetFinalPos().x - _pRight->GetFinalPos().x);
	float fSize = _pLeft->GetSize().x / 2.f + _pRight->GetSize().x / 2.f;

	if (fDist < fSize)
	{
		// x ������ ��ģ��.
		fDist = abs(_pLeft->GetFinalPos().y - _pRight->GetFinalPos().y);
		fSize = _pLeft->GetSize().y / 2.f + _pRight->GetSize().y / 2.f;

		if (fDist < fSize)
		{
			// y������ ��ģ��.
			return true;
		}
	}

	return false;
}
