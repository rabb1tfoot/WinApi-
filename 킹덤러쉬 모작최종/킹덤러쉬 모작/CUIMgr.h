#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	bool m_bOnElderUI;

public:
	void SetOnElderUI(bool _elder) { m_bOnElderUI = _elder; };
	bool GetOnElderUI() { return m_bOnElderUI; }
	void update();

private:
	CUI * FindTargetUI(CUI* _pParentUI);
	CUI * FindElderTargetUI(CUI* _pParentUI);
};

