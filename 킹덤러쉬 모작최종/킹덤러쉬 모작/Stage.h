#pragma once

class CObj;
class CAnimation;
class CWave;
#include "ResMgr.h"


class CStage
{
private:
	vector<CObj*> m_arrObj[(UINT)OBJ_TYPE::END];
	vector<CAnimation*> m_arrAnim;

protected:
	wchar_t m_wGold[10];
	wchar_t m_wLife[10];
	wchar_t m_wWave[10];
	int		m_iGoldArrSize;
	int		m_iLifeArrSize;
	int		m_iCurWaveArrSize;
	int		m_iWaveArrSize;

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void update();
	virtual void eventUpdate();
	virtual void render(HDC _hdc);

protected:
	vector<CObj*>& GetVecObj(OBJ_TYPE _etype) { return m_arrObj[(UINT)_etype]; }
	void ClearObject();
	void ClearObject(OBJ_TYPE _etype);

public:
	int FindDigitSize(int _num);
	const vector<CObj*>& GetVecObj(OBJ_TYPE _etype) const { return m_arrObj[(UINT)_etype]; }
	void AddObject(CObj* _pObj, OBJ_TYPE _etype);
	void AddAnim(CAnimation* _pAnim);
	CAnimation* GetAnim(const wchar_t* _name);

public:
	CStage();
	virtual ~CStage();
	friend INT_PTR CALLBACK Tool_Anim(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	friend INT_PTR CALLBACK Tool_Map(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	friend CTexture * CResMgr::LoadFromToolTex(wchar_t* _strKey);
	friend class CWave;

};

