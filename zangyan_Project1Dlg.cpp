
// zangyan_Project1Dlg.cpp: 实现文件
//
//#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "pch.h"
#include "framework.h"
#include "zangyan_Project1.h"
#include "zangyan_Project1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CzangyanProject1Dlg 对话框



CzangyanProject1Dlg::CzangyanProject1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZANGYAN_PROJECT1_DIALOG, pParent)
	, m_ip1(_T(""))
	, m_url1(_T(""))
	, m_ip2(_T(""))
	, m_url2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CzangyanProject1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_ip1);
	DDX_Text(pDX, IDC_EDIT1, m_url1);
	DDX_Text(pDX, IDC_EDIT4, m_ip2);
	DDX_Text(pDX, IDC_EDIT3, m_url2);
}

BEGIN_MESSAGE_MAP(CzangyanProject1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CzangyanProject1Dlg::OnBnClickedButton1)
	ON_NOTIFY(BCN_DROPDOWN, IDC_BUTTON1, &CzangyanProject1Dlg::ok1)
	ON_BN_CLICKED(IDC_BUTTON2, &CzangyanProject1Dlg::ok2)
END_MESSAGE_MAP()


// CzangyanProject1Dlg 消息处理程序

BOOL CzangyanProject1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CzangyanProject1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CzangyanProject1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CzangyanProject1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CzangyanProject1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	WSADATA wsaData;
	LPHOSTENT lpHostEnt;//该结构包含主机的ip；

	if (WSAStartup(0X0101, &wsaData))//若初始化成功则返回0；相当于应用程序与dll
		//之间的连接初始化，然后才能使用winsock api的函数
		MessageBox("Could not load windows sockets dll", NULL, MB_OK | MB_ICONSTOP);
	else
	{
		UpdateData(TRUE);//用于将屏幕上控件中的数据交换到变量中。

		//TODO: 此处需要自己添加函数，由对话框中输入的主机名m_Url1得到对应的包含主机ip的结构变量lpHostEnt
		//例如：输入的是www.seu.edu.cn，得到包含对应IP为11000000001000000100000000000010的结构变量
		lpHostEnt = gethostbyname( m_url1);
		m_ip1= inet_ntoa(*(LPIN_ADDR) * (lpHostEnt->h_addr_list));
		UpdateData(FALSE);//用于将数据在屏幕中对应控件中显示出来。
	}


	WSACleanup();

}


void CzangyanProject1Dlg::ok1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CzangyanProject1Dlg::ok2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	WSADATA wsaData;
	LPHOSTENT lpHostEnt;
	DWORD dwIPAddr;

	if (WSAStartup(0x0101, &wsaData))
		MessageBox("Could not load windows sockets dll.", NULL, MB_OK | MB_ICONSTOP);
	else
	{
		UpdateData(TRUE);//用于将屏幕上控件中的数据交换到变量中。

		//TODO: 此处需要自己添加函数，由对话框中输入的点间隔格式的IP地址m_Ip2转化为一个以网络字节顺序表示的32位二进制IP地址dwIPAddr
		//例如，原来为192.32.64.2，转化后为11000000001000000100000000000010
		dwIPAddr = inet_addr(m_ip2);
		if (dwIPAddr == INADDR_NONE)
			MessageBox("Invalid Internet Address.", NULL, MB_OK | MB_ICONSTOP);
		else
		{

			//TODO: 此处需要自己添加函数，把IP地址dwIPAddr转化为对应的包含网络名称的结构变量lpHostEnt
			//例如：输入的是11000000001000000100000000000010，得到www.seu.edu.cn
			lpHostEnt = gethostbyaddr((char FAR*) & dwIPAddr, 4, PF_INET);

			if (!lpHostEnt)
				MessageBox("Could not get host name.", NULL, MB_OK | MB_ICONSTOP);
			else
			{

				//TODO: 添加函数，从结构变量lpHostEnt中取得对应IP名称的成员变量h_name，并赋给m_Url2变量以供显示
				m_url2 = lpHostEnt->h_name;


				UpdateData(FALSE);//用于将数据在屏幕中对应控件中显示出来。
			}
		}
	}

	WSACleanup();


}
