#include "stdafx.h"
#include "CStage_Tool.h"
#include "Obj.h"
#include "Test.h"
#include "ResMgr.h"
#include "StageMgr.h"
#include "Resource.h"
#include "Stage.h"
#include "Texture.h"
#include "App.h"
#include "KeyMgr.h"
#include "UI.h"
#include "PathMgr.h"
#include "Animator.h"
#include "Collider.h"

extern int g_CurrentScrollx;
extern int g_CurrentScrolly;

int RightScroll = 0;
int bottomScroll = 0;

CStage_Tool::CStage_Tool()
	: m_eType(TOOL_TYPE::END)
	, m_eMouseMode(MOUSE_MODE::NONE)
	, m_bCromakeyColor(false)
	, m_CromakeyColor(0)
{
}


CStage_Tool::~CStage_Tool()
{
	CStage::~CStage();
}

void CStage_Tool::update()
{
	CStage::update();

	//마우스가 눌릴때 좌표를 기록한다.
	if (KEY(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_HOLD))
	{
		m_iSelectLTposx = CLICKMOUSEPOS.x;
		m_iSelectLTposy = CLICKMOUSEPOS.y;
		m_iSelectSizex = MOUSEPOS.x;
		m_iSelectSizey = MOUSEPOS.y;
	}
	//마우스를 뗏을경우 좌표구해서 edit에 넣는다.
	if (KEY(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_AWAY))
	{
		SetObjPosSize();
		EditObjPosSize();
	}

}

void CStage_Tool::CreateAnimator(tSaveAnimFrm * tAnimFrm, int Frm, wchar_t* wName)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(tAnimFrm->pTexName);
	CStage_Tool* pStage = (CStage_Tool*)CStageMgr::GetInst()->GetCurStage();
	vector<CObj*> vObj = pStage->GetVecObj(OBJ_TYPE::SALMPLEANIM);
	CAnimator* anim;
	//애니메이터가 있다면 기존의 애니메이터를 지워준다.
	if (nullptr != vObj[0]->GetAnim())
	{
		delete vObj[0]->GetAnim();
	}
	anim = new CAnimator(vObj[0]);
	anim->SetName(wName);
	anim->AddAnimation(wName, pTex, tAnimFrm, Frm);

	vObj[0]->SetAnim(anim);
}

void CStage_Tool::render(HDC _hdc)
{
	CStage::render(_hdc);

	//마우스가 드래그 되는경우 새로운 사각형그리기
	if (KEY(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_HOLD))
	{
		DrawMouseDrag(_hdc);
	}
	//이전 사각형을 그려준다.
	MoveToEx(_hdc, m_iSelectLTposx, m_iSelectLTposy, NULL);
	LineTo(_hdc, m_iSelectSizex, m_iSelectLTposy);
	MoveToEx(_hdc, m_iSelectSizex, m_iSelectLTposy, NULL);
	LineTo(_hdc, m_iSelectSizex, m_iSelectSizey);
	MoveToEx(_hdc, m_iSelectSizex, m_iSelectSizey, NULL);
	LineTo(_hdc, m_iSelectLTposx, m_iSelectSizey);
	MoveToEx(_hdc, m_iSelectLTposx, m_iSelectSizey, NULL);
	LineTo(_hdc, m_iSelectLTposx, m_iSelectLTposy);	
}


void CStage_Tool::Enter()
{
	m_eType = TOOL_TYPE::END;

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"Texture\\Mado.bmp");
	CObj* pObj = new CTest;
	pObj->SetPos(Vec2{ 100, 340 });
	pObj->SetSize(Vec2{ 100, 100 });
	pObj->SetObjType(OBJ_TYPE::SALMPLEANIM);
	pObj->SetTexture(pTex);
	m_bPlay = false;
	m_bPaint = false;

	AddObject(pObj, pObj->GetObjType());


}


void CStage_Tool::DrawMouseDrag(HDC _hdc)
{
	RECT rt;
	rt.left = m_iSelectLTposx;
	rt.top = m_iSelectLTposy;
	rt.right = m_iSelectSizex;
	rt.bottom = m_iSelectSizey;

	MoveToEx(_hdc, rt.left, rt.top, NULL);
	LineTo(_hdc, rt.right, rt.top);
	MoveToEx(_hdc, rt.right, rt.top, NULL);
	LineTo(_hdc, rt.right, rt.bottom);
	MoveToEx(_hdc, rt.right, rt.bottom, NULL);
	LineTo(_hdc, rt.left, rt.bottom);
	MoveToEx(_hdc, rt.left, rt.bottom, NULL);
	LineTo(_hdc, rt.left, rt.top);


}

void CStage_Tool::EditObjPosSize()
{
	SetDlgItemInt(CApp::GetInst()->GetAnimHWND(), IDC_EDIT3, m_iSelectLTposx - 300 , FALSE);
	SetDlgItemInt(CApp::GetInst()->GetAnimHWND(), IDC_EDIT4, m_iSelectLTposy - 60 , FALSE);
	SetDlgItemInt(CApp::GetInst()->GetAnimHWND(), IDC_EDIT5, m_iSelectSizex - m_iSelectLTposx , FALSE);
	SetDlgItemInt(CApp::GetInst()->GetAnimHWND(), IDC_EDIT6, m_iSelectSizey - m_iSelectLTposy , FALSE);

	SetDlgItemInt(CApp::GetInst()->GetMapHWND(), IDC_EDIT2, m_iSelectLTposx - 300, FALSE);
	SetDlgItemInt(CApp::GetInst()->GetMapHWND(), IDC_EDIT3, m_iSelectLTposy - 60, FALSE);
	SetDlgItemInt(CApp::GetInst()->GetMapHWND(), IDC_EDIT4, m_iSelectSizex - m_iSelectLTposx, FALSE);
	SetDlgItemInt(CApp::GetInst()->GetMapHWND(), IDC_EDIT5, m_iSelectSizey - m_iSelectLTposy, FALSE);
}

void CStage_Tool::SetObjPosSize()
{
	int Ltx = CLICKMOUSEPOS.x +1;
	int Lty = CLICKMOUSEPOS.y +1;
	int Rbx = MOUSEPOS.x -1;
	int Rby = MOUSEPOS.y -1;
	bool bFind = false;

	//그냥클릭인경우
	if (Ltx == Rbx || Lty == Rby)
		return;

	COLORREF Color, OldColor;
	//조정된 Lt x값구하기
	OldColor = GetPixel(CApp::GetInst()->GetHDC(), Ltx, Lty);

	if (OldColor != m_CromakeyColor)
	{
		return;
	}

	for (int i = Ltx; i <= Rbx; i++)
	{
		for (int j = Lty; j <= Rby; j++)
		{
			Color = GetPixel(CApp::GetInst()->GetHDC(), i, j);
			if (Color != OldColor)
			{
				m_iSelectLTposx = i;
				bFind = true;
				break;
			}
		}
		if (bFind)
		{
			bFind = false;
			break;
		}
	}
	//조정된 Lt y값구하기
	for (int i = Lty; i <= Rby; i++)
	{
		for (int j = Ltx; j <= Rbx; j++)
		{
			Color = GetPixel(CApp::GetInst()->GetHDC(), j, i);
			if (Color != OldColor)
			{
				m_iSelectLTposy = i;
				bFind = true;
				break;
			}
		}
		if (bFind)
		{
			bFind = false;
			break;
		}
	}
	//조정된 size x값구하기
	for (int i = Rbx; i >= Ltx; i--)
	{
		for (int j = Lty; j <= Rby; j++)
		{
			Color = GetPixel(CApp::GetInst()->GetHDC(), i, j);
			if (Color != OldColor)
			{
				m_iSelectSizex = i;
				bFind = true;
				break;
			}
		}
		if (bFind)
		{
			bFind = false;
			break;
		}
	}
	//조정된 size y값구하기
	for (int i = Rby; i >= Lty; i--)
	{
		for (int j = Ltx; j <= Rbx; j++)
		{
			Color = GetPixel(CApp::GetInst()->GetHDC(), j, i);
			if (Color != OldColor)
			{
				m_iSelectSizey = i;
				bFind = true;
				break;
			}
		}
		if (bFind)
		{
			bFind = false;
			break;
		}
	}
}

DWORD CStage_Tool::GetCromakeyColor()
{
	int mousex = (int)CLICKMOUSEPOS.x; //+ 300;
	int mousey = (int)CLICKMOUSEPOS.y; //+ 60;
	m_CromakeyColor = GetPixel(CApp::GetInst()->GetHDC(), mousex, mousey);
	return m_CromakeyColor;
}

void CStage_Tool::Exit()
{
}

//대화상자 열기

HWND g_SprListCtrl = NULL;
void SetScrollbar(CTexture* _pTex);

INT_PTR CALLBACK Tool_Anim(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t arrFileName[255] = L"";;
	LVCOLUMN lvColumn;
	CApp::GetInst()->AnimInit(hDlg);
	UNREFERENCED_PARAMETER(lParam);
	LVITEM ListItem;
	switch (message)
	{
	case WM_INITDIALOG:
		g_SprListCtrl = GetDlgItem(hDlg, IDC_LIST5);
		ListView_SetExtendedListViewStyle(g_SprListCtrl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;
		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"현재프레임";
		ListView_InsertColumn(g_SprListCtrl, 0, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"LT좌표x";
		ListView_InsertColumn(g_SprListCtrl, 1, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"LT좌표y";
		ListView_InsertColumn(g_SprListCtrl, 2, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"Size좌표x";
		ListView_InsertColumn(g_SprListCtrl, 3, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"Size좌표y";
		ListView_InsertColumn(g_SprListCtrl, 4, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"유지시간";
		ListView_InsertColumn(g_SprListCtrl, 5, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"오프셋x";
		ListView_InsertColumn(g_SprListCtrl, 6, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"오프셋y";
		ListView_InsertColumn(g_SprListCtrl, 7, &lvColumn);
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		CStage_Tool * pCurStage = (CStage_Tool*)CStageMgr::GetInst()->GetCurStage();

		//택스처 불러오기 버튼
		if (LOWORD(wParam) == IDC_BUTTON5)
		{
			wchar_t TotalFileName[255] = L"";
			wchar_t wKeyID[100] = L"";
			GetDlgItemText(hDlg, IDC_EDIT1, arrFileName, 50); 

			CTexture* pTex = CResMgr::GetInst()->LoadFromToolTex(arrFileName);

			//불러오기 실패
			if (nullptr == pTex)
				break;

			//스크롤바 세팅
			SetScrollbar(pTex);

		}
		//배경값 추출하기 버튼
		if (LOWORD(wParam) == IDC_BUTTON4)
		{
			DWORD CromakeyColor;

			CromakeyColor = pCurStage->GetCromakeyColor();

			SetDlgItemInt(hDlg, IDC_EDIT10, GetRValue(CromakeyColor), FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT11, GetGValue(CromakeyColor), FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT12, GetBValue(CromakeyColor), FALSE);
		}
		//프레임추가
		if (LOWORD(wParam) == IDC_BUTTON6)
		{
			ListItem.mask = LVIF_TEXT;
			ListItem.state = 0;
			ListItem.stateMask = 0;
			ListItem.iSubItem = 0;

			int idx = ListView_GetItemCount(g_SprListCtrl);
			wchar_t buffer[20];

			//추가하려는 프레임의 순서에 맞춰서 생성시킨다.
			for (int i = 0; i <= idx; ++i)
			{
				ListView_GetItemText(g_SprListCtrl, i, 0, buffer, 10);
				int iframe = _wtoi(buffer);
				if (i != iframe)
				{
					idx = i;
					break;
				}
			}

			ListItem.iItem = idx;
			wsprintf(buffer, L"%d", idx);
			ListItem.pszText = buffer;
			ListView_InsertItem(g_SprListCtrl, &ListItem);

			GetDlgItemText(hDlg, IDC_EDIT9, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 0, buffer);

			GetDlgItemText(hDlg, IDC_EDIT3, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 1, buffer);

			GetDlgItemText(hDlg, IDC_EDIT4, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 2, buffer);

			GetDlgItemText(hDlg, IDC_EDIT5, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 3, buffer);

			GetDlgItemText(hDlg, IDC_EDIT6, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 4, buffer);

			GetDlgItemText(hDlg, IDC_EDIT8, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 5, buffer);

			GetDlgItemText(hDlg, IDC_EDIT13, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 6, buffer);

			GetDlgItemText(hDlg, IDC_EDIT14, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 7, buffer);

		}
		//프레임삭제
		if (LOWORD(wParam) == IDC_BUTTON7)
		{
			int idx = ListView_GetNextItem(g_SprListCtrl, -1, LVNI_ALL | LVNI_SELECTED);

			if (idx == -1)
				MessageBox(hDlg, L"삭제할 항목을 먼저 선택해 주세요", L"주의", MB_OK);
			else
			{
				ListView_DeleteItem(g_SprListCtrl, idx);
			}
			return (INT_PTR)TRUE;
		}
		//anim불러오기
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			wstring strResPath = CPathMgr::GetResPath();
			strResPath += L"Data\\Anim\\";
			wchar_t FileName[50];
			GetDlgItemText(hDlg, IDC_EDIT7, FileName, 50);
			strResPath += FileName;

			FILE* pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"rb");

			// 파일 입출력 실패
			if (nullptr == pFile)
			{
				MessageBox(nullptr, L"파일이 존재하지 않습니다.", L"타일 읽기 실패", MB_OK);
				break;
			}
			int Frmidx;
			fread(&Frmidx, sizeof(int), 1, pFile);

			tSaveAnimFrm* frm  = new tSaveAnimFrm[Frmidx];
			ListItem.mask = LVIF_TEXT;
			ListItem.state = 0;
			ListItem.stateMask = 0;
			ListItem.iSubItem = 0;
			wchar_t buffer2[10] = L"";
			for (int i = 0; i < Frmidx; ++i)
			{
				ListItem.iItem = i;
				wsprintf(buffer2, L"%d", i);
				ListItem.pszText = buffer2;
				ListView_InsertItem(g_SprListCtrl, &ListItem);
				fread(&frm[i], sizeof(tSaveAnimFrm), 1, pFile);
				wsprintf(buffer2, L"%d", i);
				ListView_SetItemText(g_SprListCtrl, i, 0, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vLT.x);
				ListView_SetItemText(g_SprListCtrl, i, 1, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vLT.y);
				ListView_SetItemText(g_SprListCtrl, i, 2, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vSize.x);
				ListView_SetItemText(g_SprListCtrl, i, 3, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vSize.y);
				ListView_SetItemText(g_SprListCtrl, i, 4, buffer2);
				_stprintf_s(buffer2, L"%f", frm[i].fTerm);
				ListView_SetItemText(g_SprListCtrl, i, 5, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vOffset.x);
				ListView_SetItemText(g_SprListCtrl, i, 6, buffer2);
				wsprintf(buffer2, L"%d", (int)frm[i].vOffset.y);
				ListView_SetItemText(g_SprListCtrl, i, 7, buffer2);
				SetDlgItemText(hDlg, IDC_EDIT1, frm[i].pTexName);
			}
			fclose(pFile);

			//텍스처를 등록하고 불러온다.
			vector<CObj*> arrObj = pCurStage->GetVecObj(OBJ_TYPE::TEST);
			CTexture* pTex = CResMgr::GetInst()->LoadFromToolTex(frm->pTexName);
			if (nullptr == pTex)
				break;
			SetScrollbar(pTex);
			pCurStage->CreateAnimator(frm, Frmidx, FileName);

			delete frm;

		}
		//anim저장하기
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			wstring strResPath = CPathMgr::GetResPath();
			strResPath += L"Data\\Anim\\";
			wchar_t FileName[50];
			wchar_t FileTextureName[50];
			GetDlgItemText(hDlg, IDC_EDIT7, FileName, 50);
			GetDlgItemText(hDlg, IDC_EDIT1, FileTextureName, 50);
			strResPath += FileName;

			bool bExist = false;
			FILE* pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"rb");

			//파일 입출력 실패
			if (nullptr != pFile)
			{
				bExist = true;
				fclose(pFile);
			}

			if (bExist)
			{
				int id = MessageBox(nullptr, L"파일이 이미 있습니다. 덮어 쓰시겠습니까?", L"파일 이름 중복", MB_YESNO);
				if (id == IDNO)
					break;
			}

			pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"wb");

			//필요한 정보들 리스트에서 가져오고 파일저장
			int Frmidx = ListView_GetItemCount(g_SprListCtrl);
			fwrite(&Frmidx, sizeof(int), 1, pFile);
			tSaveAnimFrm* frm = new tSaveAnimFrm[Frmidx];
			GetDlgItemText(hDlg, IDC_EDIT1, arrFileName, 255);

			for (int i = 0; i < Frmidx; ++i)
			{
				wchar_t wLtx[10];
				wchar_t wLty[10];
				wchar_t wSizex[10];
				wchar_t wSizey[10];
				wchar_t wTerm[10];
				wchar_t wOffsetx[10];
				wchar_t wOffsety[10];

				ListView_GetItemText(g_SprListCtrl, i, 1, wLtx, 10);
				ListView_GetItemText(g_SprListCtrl, i, 2, wLty, 10);
				ListView_GetItemText(g_SprListCtrl, i, 3, wSizex, 10);
				ListView_GetItemText(g_SprListCtrl, i, 4, wSizey, 10);
				ListView_GetItemText(g_SprListCtrl, i, 5, wTerm, 10);
				ListView_GetItemText(g_SprListCtrl, i, 6, wOffsetx, 10);
				ListView_GetItemText(g_SprListCtrl, i, 7, wOffsety, 10);

				float fLTx= (float)_wtof(wLtx);
				float fLTy = (float)_wtof(wLty);
				float fSizex = (float)_wtof(wSizex);
				float fSizey = (float)_wtof(wSizey);
				float fTerm = (float)_wtof(wTerm);
				float fOffsetx = (float)_wtof(wOffsetx);
				float fOffsety = (float)_wtof(wOffsety);

				Vec2 vLT(fLTx, fLTy);
				Vec2 vSize(fSizex, fSizey);
				Vec2 vOffset(fOffsetx, fOffsety);

				frm[i].vLT = vLT;
				frm[i].vSize = vSize;
				frm[i].fTerm = fTerm;
				frm[i].vOffset = vOffset;
				wcscpy_s(frm[i].pTexName, arrFileName);
				fwrite(&frm[i], sizeof(tSaveAnimFrm), 1, pFile);
			}

			fclose(pFile);
			pCurStage->CreateAnimator(frm, Frmidx, FileName);
			delete frm;
		}
		//플레이 버튼
		if (LOWORD(wParam) == IDC_BUTTON3)
		{
			pCurStage->SetPlay();
			wchar_t FileName[50];
			GetDlgItemText(hDlg, IDC_EDIT7, FileName, 50);
			vector<CObj*> vObj = pCurStage->GetVecObj(OBJ_TYPE::SALMPLEANIM);
			vObj[0]->GetAnim()->PlayAnim(FileName, vObj[0], true);
		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void SetScrollbar(CTexture* _pTex)
{
	if (_pTex->GetHeight() > WINSIZE_Y)
	{
		HWND mainHwnd = CApp::GetInst()->GetWINHWND();
		RightScroll = (int)_pTex->GetWidth();
		ShowScrollBar(mainHwnd, SB_VERT, TRUE);
		SetScrollRange(mainHwnd, SB_VERT, 0,
			RightScroll, FALSE);
		SetScrollPos(mainHwnd, SB_VERT, 0, FALSE);
	}
	if (_pTex->GetWidth() > WINSIZE_X)
	{
		HWND mainHwnd = CApp::GetInst()->GetWINHWND();
		bottomScroll = (int)_pTex->GetHeight();
		ShowScrollBar(mainHwnd, SB_HORZ, TRUE);
		SetScrollRange(mainHwnd, SB_HORZ, 0,
			bottomScroll, FALSE);
		SetScrollPos(mainHwnd, SB_HORZ, 0, FALSE);
	}
}

INT_PTR CALLBACK Tool_Map(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t arrFileName[255] = L"";
	UNREFERENCED_PARAMETER(lParam);
	LVCOLUMN lvColumn;
	CApp::GetInst()->MapInit(hDlg);
	LVITEM ListItem;
	int checked = 0;
	switch (message)
	{
	case WM_INITDIALOG:
		g_SprListCtrl = GetDlgItem(hDlg, IDC_LIST4);
		ListView_SetExtendedListViewStyle(g_SprListCtrl, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvColumn.fmt = LVCFMT_CENTER;

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"LT좌표x";
		ListView_InsertColumn(g_SprListCtrl, 1, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"LT좌표y";
		ListView_InsertColumn(g_SprListCtrl, 2, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"Size좌표x";
		ListView_InsertColumn(g_SprListCtrl, 3, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"Size좌표y";
		ListView_InsertColumn(g_SprListCtrl, 4, &lvColumn);

		lvColumn.cx = 50;
		lvColumn.pszText = (LPWSTR)L"종류";
		ListView_InsertColumn(g_SprListCtrl, 5, &lvColumn);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO1)
		{
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO2)
		{
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO3)
		{
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO3);
			return (INT_PTR)TRUE;
		}

		CStage_Tool * pCurStage = (CStage_Tool*)CStageMgr::GetInst()->GetCurStage();

		//택스처 불러오기 버튼
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			wchar_t TotalFileName[255] = L"";
			wchar_t wKeyID[100] = L"";
			GetDlgItemText(hDlg, IDC_EDIT1, arrFileName, 50);

			CTexture* pTex = CResMgr::GetInst()->LoadFromToolTex(arrFileName);

			//불러오기 실패
			if (nullptr == pTex)
				break;
		}

		//세이브
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			wstring strResPath = CPathMgr::GetResPath();
			strResPath += L"Data\\Map\\";
			wchar_t FileName[50];
			wchar_t FileTextureName[50];
			GetDlgItemText(hDlg, IDC_EDIT7, FileName, 50);
			GetDlgItemText(hDlg, IDC_EDIT1, FileTextureName, 50);
			strResPath += FileName;

			bool bExist = false;
			FILE* pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"rb");

			//파일 입출력 실패
			if (nullptr != pFile)
			{
				bExist = true;
				fclose(pFile);
			}

			if (bExist)
			{
				int id = MessageBox(nullptr, L"파일이 이미 있습니다. 덮어 쓰시겠습니까?", L"파일 이름 중복", MB_YESNO);
				if (id == IDNO)
					break;
			}

			pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"wb");

			//필요한 정보들 리스트에서 가져오고 파일저장
			int Frmidx = ListView_GetItemCount(g_SprListCtrl);
			fwrite(&Frmidx, sizeof(int), 1, pFile);
			tMapInfo* frm = new tMapInfo[Frmidx];
			GetDlgItemText(hDlg, IDC_EDIT1, arrFileName, 255);

			for (int i = 0; i < Frmidx; ++i)
			{
				wchar_t wLtx[10];
				wchar_t wLty[10];
				wchar_t wSizex[10];
				wchar_t wSizey[10];
				wchar_t wKind[10];

				ListView_GetItemText(g_SprListCtrl, i, 0, wLtx, 10);
				ListView_GetItemText(g_SprListCtrl, i, 1, wLty, 10);
				ListView_GetItemText(g_SprListCtrl, i, 2, wSizex, 10);
				ListView_GetItemText(g_SprListCtrl, i, 3, wSizey, 10);
				ListView_GetItemText(g_SprListCtrl, i, 4, wKind, 10);


				float fLTx = (float)_wtof(wLtx);
				float fLTy = (float)_wtof(wLty);
				float fSizex = (float)_wtof(wSizex);
				float fSizey = (float)_wtof(wSizey);
				UINT iKind = (int)_wtoi(wKind);

				Vec2 vLT(fLTx, fLTy);
				Vec2 vSize(fSizex, fSizey);
				MAP_SETTING eType = (MAP_SETTING)iKind;

				wcscpy_s(frm[i].wTex, arrFileName);
				frm[i].vLT = vLT;
				frm[i].vSize = vSize;
				frm[i].tSetting = eType;
				fwrite(&frm[i], sizeof(tMapInfo), 1, pFile);
			}
			delete frm;
			fclose(pFile);

		}
		//로드
		if (LOWORD(wParam) == IDC_BUTTON3)
		{
			wstring strResPath = CPathMgr::GetResPath();
			strResPath += L"Data\\Map\\";
			wchar_t FileName[50];
			GetDlgItemText(hDlg, IDC_EDIT7, FileName, 50);
			strResPath += FileName;

			FILE* pFile = nullptr;
			_wfopen_s(&pFile, strResPath.c_str(), L"rb");

			// 파일 입출력 실패
			if (nullptr == pFile)
			{
				MessageBox(nullptr, L"파일이 존재하지 않습니다.", L"타일 읽기 실패", MB_OK);
				break;
			}
			int Frmidx;
			wchar_t FrmTex[50];
			fread(&Frmidx, sizeof(int), 1, pFile);

			tMapInfo* frm = new tMapInfo[Frmidx];
			ListItem.mask = LVIF_TEXT;
			ListItem.state = 0;
			ListItem.stateMask = 0;
			ListItem.iSubItem = 0;
			wchar_t buffer2[10] = L"";
			wchar_t wLTx[10] = L"";
			wchar_t wLTy[10] = L"";
			wchar_t wSizex[10] = L"";
			wchar_t wSizey[10] = L"";
			wchar_t wKind[10] = L"";
			for (int i = 0; i < Frmidx; ++i)
			{
				ListItem.iItem = i;
				wsprintf(buffer2, L"%d", i);
				ListItem.pszText = buffer2;
				ListView_InsertItem(g_SprListCtrl, &ListItem);
				fread(&frm[i], sizeof(tMapInfo), 1, pFile);

				wsprintf(wLTx, L"%d", (int)frm[i].vLT.x);
				ListView_SetItemText(g_SprListCtrl, i, 0, wLTx);
				wsprintf(wLTy, L"%d", (int)frm[i].vLT.y);
				ListView_SetItemText(g_SprListCtrl, i, 1, wLTy);
				wsprintf(wSizex, L"%d", (int)frm[i].vSize.x);
				ListView_SetItemText(g_SprListCtrl, i, 2, wSizex);
				wsprintf(wSizey, L"%d", (int)frm[i].vSize.y);
				ListView_SetItemText(g_SprListCtrl, i, 3, wSizey);
				wsprintf(wKind, L"%d", (int)frm[i].tSetting);
				ListView_SetItemText(g_SprListCtrl, i, 4, wKind);

				float fLx = (float)_wtof(wLTx);
				float fLy = (float)_wtof(wLTy);
				float fsizex = (float)_wtof(wSizex);
				float fsizey = (float)_wtof(wSizex);
				int   find = _wtoi(wKind);

				CObj* obj = new CObj(Vec2(fLx, fLy));
				obj->SetObjType(OBJ_TYPE::MAP_INGREDIENT);
				if (0 == find)
					obj->SetMapSetting(MAP_SETTING::MAP_BLOCK);
				else if (1 == find)
					obj->SetMapSetting(MAP_SETTING::MAP_NOTBLOCK);
				else
					obj->SetMapSetting(MAP_SETTING::MAP_GROUND);

				CCollider* pCol = new CCollider(obj);
				pCol->SetSize(Vec2(fsizex, fsizey));
				pCol->SetFinalPos(Vec2(obj->GetPos().x + 300.f, obj->GetPos().y + 60.f));
				pCol->SetColliderType(COLLIDER_TYPE::RECT);
				pCol->SetDrow(false);
				obj->SetCollider(pCol);

				pCurStage->AddObject(obj, obj->GetObjType());
				vector<CObj*> myObj = pCurStage->GetMapObj();
				myObj.push_back(obj);
				pCurStage->SetMapObj(myObj);
			}
			SetDlgItemText(hDlg, IDC_EDIT1, FileName);
			//텍스처를 등록하고 불러온다.
			CTexture* pTex = CResMgr::GetInst()->LoadFromToolTex(frm[0].wTex);

			delete frm;
		}
		//추가
		if (LOWORD(wParam) == IDC_BUTTON4)
		{
			ListItem.mask = LVIF_TEXT;
			ListItem.state = 0;
			ListItem.stateMask = 0;
			ListItem.iSubItem = 0;

			int idx = ListView_GetItemCount(g_SprListCtrl);
			wchar_t buffer[20];

			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
				checked = 0;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
				checked = 1;
			else
				checked = 2;

			ListItem.iItem = idx;
			wsprintf(buffer, L"%d", idx);
			ListItem.pszText = buffer;
			ListView_InsertItem(g_SprListCtrl, &ListItem);

			GetDlgItemText(hDlg, IDC_EDIT2, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 0, buffer);
			float fLx = _wtof(buffer);

			GetDlgItemText(hDlg, IDC_EDIT3, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 1, buffer);
			float fLy = _wtof(buffer);

			GetDlgItemText(hDlg, IDC_EDIT4, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 2, buffer);
			float fsizex = _wtof(buffer);

			GetDlgItemText(hDlg, IDC_EDIT5, buffer, 10);
			ListView_SetItemText(g_SprListCtrl, idx, 3, buffer);
			float fsizey = _wtof(buffer);

			wsprintf(buffer, L"%d", checked);
			ListView_SetItemText(g_SprListCtrl, idx, 4, buffer);
			int find = _wtoi(buffer);

			CObj* obj = new CObj(Vec2(fLx, fLy));
			obj->SetObjType(OBJ_TYPE::MAP_INGREDIENT);
			if(0 == find)
				obj->SetMapSetting(MAP_SETTING::MAP_BLOCK);
			else if(1 == find)
				obj->SetMapSetting(MAP_SETTING::MAP_NOTBLOCK);
			else
				obj->SetMapSetting(MAP_SETTING::MAP_GROUND);

			CCollider* pCol = new CCollider(obj);
			pCol->SetSize(Vec2(fsizex, fsizey));
			pCol->SetFinalPos(Vec2(obj->GetPos().x + 300.f, obj->GetPos().y + 60.f));
			pCol->SetColliderType(COLLIDER_TYPE::RECT);
			pCol->SetDrow(false);
			obj->SetCollider(pCol);

			pCurStage->AddObject(obj, obj->GetObjType());
			vector<CObj*> myObj = pCurStage->GetMapObj();
			myObj.push_back(obj);
			pCurStage->SetMapObj(myObj);

		}
		//삭제
		if (LOWORD(wParam) == IDC_BUTTON5)
		{
			int idx = ListView_GetNextItem(g_SprListCtrl, -1, LVNI_ALL | LVNI_SELECTED);

			if (idx == -1)
				MessageBox(hDlg, L"삭제할 항목을 먼저 선택해 주세요", L"주의", MB_OK);
			else
			{
				ListView_DeleteItem(g_SprListCtrl, idx);
			}
			vector<CObj*> mapObj = pCurStage->GetMapObj();
			vector<CObj*>::iterator iter = mapObj.begin();
			int i = 0;
			for (iter; iter != mapObj.end();++iter)
			{
				if (i == idx)
				{
					mapObj.erase(iter);
					pCurStage->SetMapObj(mapObj);
					vector<CObj*> vMap_ingred = pCurStage->GetVecObj(OBJ_TYPE::MAP_INGREDIENT);
					vMap_ingred[i]->SetDead();	
					return (INT_PTR)TRUE;
				}
				++i;
			}
			return (INT_PTR)TRUE;
		}
		//작업물보기
		if (LOWORD(wParam) == IDC_BUTTON6)
		{
			vector<CObj*> mapObj = pCurStage->GetMapObj();
			pCurStage->SetPaint();
			for (UINT i = 0; i < mapObj.size(); ++i)
			{
				mapObj[i]->GetCollider()->SetDrow(pCurStage->GetPaint());
				mapObj[i]->GetCollider()->SetFinalPos(
					Vec2(mapObj[i]->GetPos().x + 300.f, mapObj[i]->GetPos().y + 60.f));
			}
		}
	}
	return (INT_PTR)FALSE;
}