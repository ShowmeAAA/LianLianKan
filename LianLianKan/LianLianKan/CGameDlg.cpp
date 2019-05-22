/*原理：
首先将背景图片装入m_dcMem；将元素图片和掩码图片复制给m_dcElement和m_dcMask。
然后根据游戏二维地图用BitBlt函数对这三者进行位操作：
	比如，UpdateMap()函数
*/

// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LianLianKan.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_GAME, m_btnEdit);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START_GAME, &CGameDlg::OnBnClicked_StartGame)
//	ON_WM_SYSCOMMAND()
ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	UpdateWindow();	//这个函数改变了窗口 会调用OnPaint()重绘窗口

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//重绘窗口时调用的函数
//每次窗口重绘都会显示m_dcMem的内容
void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	/*
	BitBlt()函数是用于改变它所属的对象dc
	最后一个参数SRCCOPY,说明这个函数执行完后 dc=m_dcMem

	CPaintDC类是CDC类的一个派生类。
	如果在OnPaint函数内定义了CPaintDC类的对象，
	通过这个类对象就可以使用CDC类的成员函数完成视图客户区中的图形绘制操作。

	dc这个设备上下文在每次调用这个函数时会将其中内容显示在屏幕上
	将m_dcMem复制给dc
	*/
	dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}

// 调整窗口大小
//重载后的UpdateWindow()何时调用
void CGameDlg::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
	// 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
	// 设置对话框显示是，在 windows 窗口正中央。
	CenterWindow();
}

//初始化m_dcMem：将背景图片赋值给m_dcMem
void CGameDlg::InitBackground()
{
	CBitmap bmpGame;
	bmpGame.LoadBitmapW(IDB_GAME_BG);
	// 获得当前对话框的视频内存
	CClientDC dc(this);
	//……

	//创建内存设备上下文，与另一个设备上下文匹配。可以用它在内存中准备图像
	m_dcMem.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMem.SelectObject(bmpGame);
}

//初始化m_dcElement和m_dcMask
//将元素图片和掩码图片复制给m_dcElement和m_dcMask
//m_dcElement和m_dcMask被初始化后，整个游戏期间都不用再改变
void CGameDlg::InitElement()
{
	// 获得当前对话框的视频内存
	CClientDC dc(this);
	// 加载 BMP 图片资源
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 创建与视频内存兼容的内存 DC
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcElement.SelectObject(hBmp);


	// 加载掩码 BMP 图片资源
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 创建与视频内存兼容的内存 DC
	m_dcMask.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMask.SelectObject(hMask);
}

//根据已更新的游戏地图二维数组更新m_dcMem
//而m_dcMem就是要显示的设备上下文
//所以执行完这个函数后需要重绘窗口 how??
void CGameDlg::UpdateMap()
{
	//游戏地图的起始点为客户区中的(20,50)
	int nLeft = 20;
	int nTop = 50;

	//图片大小
	int nElemW = 40;
	int nElemH = 40;

	//获取行数和列数
	int nRows = m_GameControl.s_nRows;
	int nCols = m_GameControl.s_nCols;

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			// 得到图片编号的值并将对应的图片区域的数据绘制到m_dcMem中的相应位置
			int nElemVal = m_GameControl.GetElement(i, j);
			// 将背景与掩码相或，边保留，图像区域为 1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			// 与元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}

}


//开始游戏按钮事件响应
//初始化地图
//显示地图

/*
BUG 5/17
多次按开始游戏按钮时，水果图标会重叠出现
因为此时的m_dcMem不再是背景图了，而是第一次点击开始游戏后产生的图
所以先将m_dcMem设为背景图
所以将开始游戏按钮设为只能按一次，之后需要重玩，要按重排按钮
*/
void CGameDlg::OnBnClicked_StartGame()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameControl.StartGame();
	UpdateMap();
	Invalidate();
}


void CGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);
	if (nID == SC_CLOSE)
		CGameDlg::OnCancel();
}
