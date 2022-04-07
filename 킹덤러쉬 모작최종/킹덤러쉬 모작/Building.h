#pragma once
#include "UI.h"
class CBuilding :
	public CUI
{
private:
	bool m_bClicked;
	CTexture * m_pSelectTex;
	BUILD_SELETE m_eBuildType;
	int			m_iBuildTier;

protected:
	bool		m_bframeEnter;

public:
	CBuilding();
	virtual ~CBuilding();
	void SetBuildType(BUILD_SELETE _etpye) {m_eBuildType = _etpye;};
	void SetBuildTier(int _tier) { m_iBuildTier = _tier; }
	bool GetClick() { return m_bClicked; }
	void SetClick(bool _click) { m_bClicked = _click; }
	BUILD_SELETE GetBuildType() { return m_eBuildType; }
	int GetBuildTier() { return m_iBuildTier; }
	virtual void update();
	virtual void render(HDC _hdc);

private:
	void Init();
public:
	virtual void UpgradeBuild(int _tier) {};

public:
	virtual void MouseOn(Vec2 _vMousePos);
	virtual void MouseOff();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

