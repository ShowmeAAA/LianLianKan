﻿#pragma once
#define GAMEWND_WIDTH 800
#define GAMEWND_HEIGHT 600
#include"CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

private:
	CDC m_dcMem;          // 内存 DC
	CDC m_dcBG;           // 背景 DC
	CDC m_dcElement;      // 元素内存 DC
	CDC m_dcMask;         // 掩码内存 DC
	CPoint m_ptGameTop;   //游戏区起始点（游戏第一张图片的顶点坐标,
						  //坐标相对于窗口客户区）

	CSize m_sizeElem;     // 元素图片的大小
	CRect m_rtGameRect;   //游戏区域大小(该区域为游戏更新区域大小，
					      //考虑到后面画的线，可能会超出图片区域一定范围)

	CGameControl m_GameControl; //游戏控制类

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitBackground();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClicked_StartGame();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CButton m_btnEdit;
};
