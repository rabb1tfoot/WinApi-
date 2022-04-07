#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"

CAnimator::CAnimator(CObj * _Obj)
	: m_pOwner(_Obj)
	, m_pCurAnim(nullptr)
{
}

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	for (; iter != m_mapAnim.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapAnim.clear();
}


void CAnimator::update()
{
	if (nullptr == this->m_pCurAnim)
		return;
	m_pCurAnim->upate();

	if (m_pCurAnim->IsEnd() && m_bRepeat)
	{
		m_pCurAnim->SetFrame(0);
	}
}

void CAnimator::render(HDC _hdc)
{
	if (nullptr == this->m_pCurAnim)
		return;
	m_pCurAnim->render(_hdc);
}

void CAnimator::AddAnimation(const wstring & _strName, CTexture * _pTex, tAnimFrm* _frm, int _iMaxFrm)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Create(_strName, _pTex, _frm,  _iMaxFrm);

	pAnim->SetOwner(m_pOwner);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::AddAnimation(const wstring & _strName, CTexture * _pTex, tSaveAnimFrm * _frm, int _iMaxFrm)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Create(_strName, _pTex, _frm, _iMaxFrm);

	pAnim->SetOwner(m_pOwner);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::AddAnimation(const wstring & _strName, CAnimation * _pAnim)
{
	m_mapAnim.insert(make_pair(_strName, _pAnim));
}

void CAnimator::PlayAnim(const wstring & _strKey, CObj* _obj, bool _bRepeat, Vec2 _off)
{
	m_bRepeat = _bRepeat;

	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);
	if (m_pCurAnim == iter->second)
		return;
	assert(iter != m_mapAnim.end());

	m_pCurAnim = iter->second;
	m_pCurAnim->SetOwner(_obj);
	m_pCurAnim->SetFrame(0);
	m_pCurAnim->SetOffset(_off);
}
