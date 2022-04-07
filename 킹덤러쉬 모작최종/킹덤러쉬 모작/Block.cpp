#include "stdafx.h"
#include "Block.h"
#include "MapMgr.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::MouseLbtnClicked(Vec2 _vMousePos)
{
	if (CMapMgr::GetInst()->GetClickMode())
	{
		CMapMgr::GetInst()->SetClickOption(MAP_SETTING::MAP_BLOCK);
	}
}
