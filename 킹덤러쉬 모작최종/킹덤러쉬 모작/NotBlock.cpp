#include "stdafx.h"
#include "NotBlock.h"
#include "MapMgr.h"


CNotBlock::CNotBlock()
{
}


CNotBlock::~CNotBlock()
{
}

void CNotBlock::MouseLbtnClicked(Vec2 _vMousePos)
{
	if (CMapMgr::GetInst()->GetClickMode())
	{
		CMapMgr::GetInst()->SetClickOption(MAP_SETTING::MAP_NOTBLOCK);
	}
}
