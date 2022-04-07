#include "stdafx.h"
#include "UI.h"
#include "KeyMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Collider.h"
#include "SoundMgr.h"
#include "CUIMgr.h"

CUI::CUI()
	: CObj::CObj()
	, m_pParentUI(nullptr)
	, m_bButtonDown(false)
	, m_bLayer(false)
{
}

CUI::CUI(Vec2 _vPos)
	: CObj::CObj(_vPos)
	, m_pParentUI(nullptr)
	, m_bButtonDown(false)
	, m_bLayer(false)

{
}


CUI::~CUI()
{
	vector<CUI*>::iterator iter = m_vecChildUI.begin();

	for (; m_vecChildUI.end() != iter; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_vecChildUI.clear();
}


void CUI::update()
{
	if (!GetEnable())
		return;
	if (nullptr != m_pParentUI)
	{
		m_vFinalPos = m_pParentUI->GetFinalPos() + GetPos();
	}
	else
	{
		m_vFinalPos = GetPos();
	}

	if (KEYAWAY(KEY_TYPE::KEY_LBTN))
		m_bButtonDown = false;

	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render(HDC _hdc)
{
	if (!GetEnable())
		return;
	if (nullptr != GetCollider())
		GetCollider()->render(_hdc);

	if (nullptr != this->GetAnim())
	{
		this->GetAnim()->render(_hdc);
		return;
	}

	if (OBJ_TYPE::UI != GetObjType())
	{
		CObj::render(_hdc);
		return;
	}

	Vec2 vPos = m_vFinalPos;
	Vec2 vSize = GetSize();
	CTexture* pTex = GetTexture();

	if (nullptr == pTex)
		return;

	/*Rectangle(_hdc, vPos.x - vSize.x / 2, vPos.y - vSize.y / 2
		, vPos.x + vSize.x / 2, vPos.y + vSize.y / 2);*/

	TransparentBlt(_hdc
		, (int)(vPos.x - vSize.x / 2)
		, (int)(vPos.y - vSize.y / 2)
		, (int)vSize.x
		, (int)vSize.y
		, pTex->GetDC()
		, (int)this->GetTexPos().x
		, (int)(this->GetTexPos().y)
		, (int)vSize.x
		, (int)vSize.y
		, RGB(255, 0, 255));


	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_hdc);
	}
}

void CUI::MouseOff()
{
	if (OBJ_TYPE::ELDER_UI == this->GetObjType())
	{
		CUIMgr::GetInst()->SetOnElderUI(false); 
	}
}

void CUI::MouseOn(Vec2 _vMousePos)
{
	if (OBJ_TYPE::ELDER_UI == this->GetObjType())
	{
		CUIMgr::GetInst()->SetOnElderUI(true);
	}
}

void CUI::MouseLbtnClicked(Vec2 _vMousePos)
{
	//효과음 생성
	CSoundMgr::GetInst()->LoadSound(L"Sound_UIButton.wav", L"Sound_UIButton.wav");
	CSoundMgr::GetInst()->Play(L"Sound_UIButton.wav");
	//CSoundMgr::GetInst()->PlayBGM(L"BGM_01");
	CSoundMgr::GetInst()->SetBGMVolume(100);
}


bool CUI::IsOn(Vec2 _vCoordinate)
{

	Vec2 vPos = GetFinalPos();
	Vec2 vSize = GetSize();

	if (vPos.x - vSize.x / 2.f < _vCoordinate.x && _vCoordinate.x < vPos.x + vSize.x / 2
		&& vPos.y - vSize.y / 2.f < _vCoordinate.y && _vCoordinate.y < vPos.y + vSize.y / 2)
	{
		return true;
	}
	return false;
}

void CUI::AddChild(CUI * _pChildUI)
{
	_pChildUI->m_pParentUI = this;
	m_vecChildUI.push_back(_pChildUI);
}