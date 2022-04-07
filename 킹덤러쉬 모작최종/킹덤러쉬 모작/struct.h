#pragma once

#include <assert.h>

struct Vec2
{
	float x;
	float y;

public:
	float Distance(const Vec2& _vecOther)
	{
		return sqrt(pow(_vecOther.x - x, 2) + pow(_vecOther.y - y, 2));
	}

	void Normalize()
	{
		float fDist = sqrt(pow(x, 2) + pow(y, 2));
		x /= fDist;
		y /= fDist;
	}

public:

	void operator= (const POINT& _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (const Vec2& _vOther) const // �ɹ��� �ٲٴ� �ڵ尡 �ش� �Լ��� ����.
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (const Vec2& _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator + (float _f) const
	{
		return Vec2(x + _f, y + _f);
	}

	Vec2 operator - (const Vec2& _vOther) const
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (const Vec2& _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator - (float _f) const
	{
		return Vec2(x - _f, y - _f);
	}

	Vec2 operator * (const Vec2& _vOther) const
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	void operator *= (const Vec2& _vOther)
	{
		x *= _vOther.x;
		y *= _vOther.y;
	}

	Vec2 operator * (float _f) const
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator / (const Vec2& _vOther) const
	{
		assert(_vOther.x); assert(_vOther.y);
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (const Vec2& _vOther)
	{
		assert(_vOther.x); assert(_vOther.y);

		x /= _vOther.x;
		y /= _vOther.y;
	}

	Vec2 operator / (float _f) const
	{
		assert(_f);
		return Vec2(x / _f, y / _f);
	}

	Vec2()
		: x(0.f), y(0.f)
	{}
	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}
};

class CTexture;
struct tAnimFrm
{
	CTexture*	pTex;	// �������� ��ġ�ϴ� �̹���
	Vec2		vLT;	// ������ �»�� ��ǥ
	Vec2		vSize;  // ������ ũ��
	Vec2		vOffset;		// ������
	float       fTerm;  // ������ �̹��� �����ð�
};

struct tSaveAnimFrm
{
	wchar_t     pTexName[255];	// �������� ��ġ�ϴ� �̹���
	Vec2		vLT;			// ������ �»�� ��ǥ
	Vec2		vSize;			// ������ ũ��
	Vec2		vOffset;		// ������
	float       fTerm;			// ������ �̹��� �����ð�
};

struct tBuildingInfo
{
	int iCost;
	int iAtt_pow;
	int iAtt_speed;
	Vec2 iAtt_range;
};

struct tUnitInfo
{
	int iAtt_pow;
	Vec2 iAtt_range;
	int iDef;
	int iMaxHealth;
	int iCurHealth;
	ATTACK_TYPE eAttType;
};

struct tMapInfo
{
	wchar_t		wTex[50];
	Vec2		vLT;		// ������ �»�� ��ǥ
	Vec2		vSize;		// ������ ũ��
	MAP_SETTING	tSetting;	//����̸�
};

struct tWaveInfo
{
	int waveLevel;			//���̺극��
	MONSTER_TYPE type;		//���� �̸�
	int num;				//���� ����
	bool done;				//��� ���Ͱ� ��������� Ȯ��
};