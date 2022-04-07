#pragma once
#include "UI.h"
class CNotBlock :
	public CUI
{
public:
	CNotBlock();
	virtual ~CNotBlock();
	virtual void MouseLbtnClicked(Vec2 _vMousePos);
};

