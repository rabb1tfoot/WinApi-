#pragma once
#include "Building.h"

class CMagician;
class CTexture;

class CMage :
	public CBuilding
{
private:
	bool			m_bClicked;
	CMagician*		m_cMyMagician;
	CTexture*		m_pSelectTex;

private:
	void CreateMagician(int _tier);

public:
	void Init();

public:
	virtual void update();
	virtual void render(HDC _hdc);
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
	virtual void UpgradeBuild(int _tier);


public:
	CMage();
	virtual ~CMage();
};

