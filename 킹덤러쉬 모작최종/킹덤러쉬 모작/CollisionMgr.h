#pragma once

union COL_ID
{
	struct {
		DWORD left;
		DWORD right;
	};
	unsigned long long ID;
};

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	UINT m_arrCheck[(UINT)OBJ_TYPE::END];
	map<unsigned long long, bool> m_mapID;

public:
	void update();

public:
	void CollisionCheck(OBJ_TYPE _Left, OBJ_TYPE _Right);
	void ClearCheck() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJ_TYPE::END); }
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

private:
	void CollisionGroup(UINT _left, UINT _right);
};

