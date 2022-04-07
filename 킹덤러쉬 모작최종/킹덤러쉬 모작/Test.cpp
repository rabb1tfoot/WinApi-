#include "stdafx.h"
#include "Test.h"
#include "Animator.h"
#include "StageMgr.h"
#include "CStage_Tool.h"
#include "Stage.h"


void CTest::update()
{
	CStage_Tool* curStage = (CStage_Tool*)(CStageMgr::GetInst()->GetCurStage());
	if (curStage->GetPlay())
	{
		GetAnim()->update();
	}
}

void CTest::render(HDC _hdc)
{
	//툴 스테이지일 경우, 갯플레이를 통해 애니메이션을 출력할지 정한다.
	if (STAGE_TYPE::TOOL == CStageMgr::GetInst()->GetCurStageType())
	{
		CStage_Tool* curStage = (CStage_Tool*)(CStageMgr::GetInst()->GetCurStage());
		if (curStage->GetPlay())
		{
			GetAnim()->render(_hdc);
			return;
		}
		else
		{
			CObj::render(_hdc);
			return;
		}
	}

	GetAnim()->render(_hdc);

}

CTest::CTest()
{
}


CTest::~CTest()
{
}
