#pragma once
#include "Stage.h"
class CAnimator;

enum class TOOL_TYPE
{
	TOOL_ANIM,
	TOOL_MAP,
	END
};

enum class MOUSE_MODE
{
	SET_CROMA,
	SET_LOCATION,
	NONE
};

class CStage_Tool :
	public CStage
{
private:
	TOOL_TYPE   m_eType;
	MOUSE_MODE  m_eMouseMode;
	bool		m_bCromakeyColor;
	DWORD		m_CromakeyColor;
	int			m_iSelectLTposx;
	int			m_iSelectLTposy;
	int			m_iSelectSizex;
	int			m_iSelectSizey;
	bool		m_bPlay;
	bool		m_bPaint;
	vector<CObj*> m_vMapObj;
public:
	vector<CObj*>& GetMapObj() { return m_vMapObj; }
	void SetMapObj(vector<CObj*>& _vObj) { m_vMapObj = _vObj; }
	bool GetPlay() { return m_bPlay; }
	void SetPlay() { m_bPlay = !m_bPlay; }
	bool GetPaint() { return m_bPaint; }
	void SetPaint() { m_bPaint = !m_bPaint; }
	void DrawMouseDrag(HDC _hdc);
	void EditObjPosSize();
	void SetObjPosSize();
	DWORD GetCromakeyColor();
	void SetCromakeyMode() { m_bCromakeyColor = !m_bCromakeyColor; }
	bool GetCromakeyMode() { return m_bCromakeyColor; }

public:
	void CreateAnimator(tSaveAnimFrm* tAnimFrm, int Frm, wchar_t* wName);

public:
	virtual void render(HDC _hdc);
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CStage_Tool();
	virtual ~CStage_Tool();

};

