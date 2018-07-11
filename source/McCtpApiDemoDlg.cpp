
// McCtpApiDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "McCtpApiDemo.h"
#include "McCtpApiDemoDlg.h"
#include "afxdialogex.h"
#include "CONFIG.H"
#include "..\CMcPublic\WstrAndMstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef HRZG
    #pragma comment(lib, "thosttraderapi_hrzg.lib")
#else
    #pragma comment(lib, "thosttraderapi.lib")
#endif

CMcCtpApiDemoDlg *g_pclDlg = NULL;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


char * const CMcCtpApiDemoDlg::GetCurTimeByChar(void)
{

    SYSTEMTIME hstTmLocal;
    ::GetLocalTime(&hstTmLocal);
    _snprintf_s((char*)m_szCurLogTime, sizeof(m_szCurLogTime), _TRUNCATE, "[%02d:%02d:%02d:%03d]", hstTmLocal.wHour, hstTmLocal.wMinute, hstTmLocal.wSecond, hstTmLocal.wMilliseconds);
    return (char*)m_szCurLogTime;
}

CMcCtpApiDemoDlg::CMcCtpApiDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CMcCtpApiDemoDlg::IDD, pParent)
    , m_strTitle(_T(""))
    , m_strPwd(_T(""))
    , m_strCtpServerIP(_T(""))
    , m_strCtpServerPort(_T(""))
    , m_strSubscribeType(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_strDirection = _T("");
    m_strHegeFlag = _T("");
    m_strInstrumentID = _T("");
    m_strInvestorID = _T("");
    m_strJysdm = _T("");
    m_strOffsetFlag = _T("");
    m_strPriceType = _T("");
    m_strUseID = _T("");

    m_strWithRefNumExt = _T("");
    m_strBrokerID = _T("");
    m_dWtjg = 0.0;
    m_iWtsl = 0;
    m_pclUserApi  = NULL;
    m_pclUseSpi = NULL;
    m_bServerStart = false;
}

CMcCtpApiDemoDlg::~CMcCtpApiDemoDlg()
{
    m_strDirection.Empty();
    m_strHegeFlag.Empty();
    m_strInstrumentID.Empty();
    m_strInvestorID.Empty();
    m_strJysdm.Empty();
    m_strOffsetFlag.Empty();
    m_strPriceType.Empty();
    m_strUseID.Empty();
    m_strWithRefNumExt.Empty();
    m_strBrokerID.Empty();
    m_dWtjg = 0.0;
    m_iWtsl = 0;
    m_bServerStart = false;

    CheckResource();
}

void CMcCtpApiDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBOX_DIRECTION, m_strDirection);
    DDX_CBString(pDX, IDC_COMBOX_HEDGEFLAG, m_strHegeFlag);
    DDX_CBString(pDX, IDC_COMBOX_INSTRUMENTID, m_strInstrumentID);
    DDX_CBString(pDX, IDC_COMBOX_INVESTORID, m_strInvestorID);
    DDX_CBString(pDX, IDC_COMBOX_JYSDM, m_strJysdm);
    DDX_CBString(pDX, IDC_COMBOX_OffsetFlag, m_strOffsetFlag);
    DDX_CBString(pDX, IDC_COMBOX_PRICETYPE, m_strPriceType);
    DDX_CBString(pDX, IDC_COMBOX_USERID, m_strUseID);
    DDX_Text(pDX, IDC_WTHREFNUMEXT, m_strWithRefNumExt);
    DDX_CBString(pDX, IDC_COMBOX_BROKERID, m_strBrokerID);
    DDX_Control(pDX, IDC_COMBOX_BROKERID, m_ctrlBrokerID);
    DDX_Control(pDX, IDC_COMBOX_DIRECTION, m_ctrlDirection);
    DDX_Control(pDX, IDC_COMBOX_HEDGEFLAG, m_ctrlHedgeFlag);
    DDX_Control(pDX, IDC_COMBOX_INSTRUMENTID, m_ctrlInstrunentID);
    DDX_Control(pDX, IDC_COMBOX_INVESTORID, m_ctrlInvestorID);
    DDX_Control(pDX, IDC_COMBOX_JYSDM, m_ctrlJysdm);
    DDX_Control(pDX, IDC_COMBOX_OffsetFlag, m_ctrlOffsetFlag);
    DDX_Control(pDX, IDC_COMBOX_PRICETYPE, m_ctrlPriceType);
    DDX_Control(pDX, IDC_COMBOX_USERID, m_ctrlUseID);
    DDX_Text(pDX, IDC_EDIT_WTJG, m_dWtjg);
    DDX_Text(pDX, IDC_EDIT_WTSL, m_iWtsl);
    DDX_Control(pDX, IDC_LIST_DISPLAY, m_pclCtrlListDisplay);
    DDX_Control(pDX, IDC_BUTTON_START, m_clButStart);
    DDX_Control(pDX, IDC_BUTTON_STOP, m_clButStop);
    DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
    DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlTitle);
    DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
    DDX_Text(pDX, IDC_EDIT_CTPSERVER_IP, m_strCtpServerIP);
    DDX_Text(pDX, IDC_EDIT_CTPSERVER_PORT, m_strCtpServerPort);
    DDX_Control(pDX, IDC_COMBOX_SUBSCRIBETYPE, m_ctrSubscribeType);
    DDX_CBString(pDX, IDC_COMBOX_SUBSCRIBETYPE, m_strSubscribeType);
}

BEGIN_MESSAGE_MAP(CMcCtpApiDemoDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_CBN_SELCHANGE(IDC_COMBOX_INSTRUMENTID, &CMcCtpApiDemoDlg::OnCbnSelchangeComboxInstrumentid)
    ON_BN_CLICKED(IDC_BUTTON_START, &CMcCtpApiDemoDlg::OnBnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CMcCtpApiDemoDlg::OnBnClickedButtonStop)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMcCtpApiDemoDlg::OnBnClickedButtonExit)
    ON_BN_CLICKED(IDC_BUTTON_ORDER, &CMcCtpApiDemoDlg::OnBnClickedButtonOrder)
    ON_BN_CLICKED(IDC_BUTTON_WITHDRAW, &CMcCtpApiDemoDlg::OnBnClickedButtonWithdraw)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMcCtpApiDemoDlg::OnBnClickedButtonClear)
    ON_LBN_DBLCLK(IDC_LIST_DISPLAY, &CMcCtpApiDemoDlg::OnLbnDblclkListDisplay)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_QryInvestorPosition, &CMcCtpApiDemoDlg::OnBnClickedButtonQryInvestorPosition)
    ON_BN_CLICKED(IDC_BUTTON_QRYTRADINGACCOUNT, &CMcCtpApiDemoDlg::OnBnClickedButtonQryTradingAccount)
    ON_BN_CLICKED(IDC_BUTTON_QRYEXCHANGE, &CMcCtpApiDemoDlg::OnBnClickedButtonQryExchange)
    ON_BN_CLICKED(IDC_BUTTON_QUERYINSTRUMENT, &CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrument)
    ON_BN_CLICKED(IDC_BUTTON_QRYINSTRUMENTMARGINRATE, &CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrumentMarginRate)
    ON_BN_CLICKED(IDC_BUTTON_QRYINSTRUMENTCOMMISSIONRATE, &CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrumentCommissionRate)
    ON_BN_CLICKED(IDC_BUTTON_QRYBROKERTRADINGPARAMS, &CMcCtpApiDemoDlg::OnBnClickedButtonQryBrokerTradingParams)
    ON_BN_CLICKED(IDC_BUTTON_QRYBROKERTRADINGALGOS, &CMcCtpApiDemoDlg::OnBnClickedButtonQryBrokerTradingAlgos)
    ON_BN_CLICKED(IDC_BUTTON_QRYCFMMCTRADINGACCOUNTKEY, &CMcCtpApiDemoDlg::OnBnClickedButtonQryCFMMCTradingAccountKey)
    ON_BN_CLICKED(IDC_BUTTON_QRYORDER, &CMcCtpApiDemoDlg::OnBnClickedButtonQryOrder)
    ON_BN_CLICKED(IDC_BUTTON_QRYTRADE, &CMcCtpApiDemoDlg::OnBnClickedButtonQryTrade)
END_MESSAGE_MAP()


BOOL CMcCtpApiDemoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    m_clTitleFont.CreatePointFont(355, "华文行楷");
    m_clButStop.EnableWindow(FALSE);

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
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

    // App title
    CString hstrSysVer = "";
    CString hstrVer = "";
    GetFileVersion(hstrVer, NULL);
    CString hstrAppName = "";
    hstrAppName.LoadString(IDS_APPNAME);
    CString hstrName = "";
    hstrName.Format("%s %s", hstrAppName, hstrVer);
    this->SetWindowText(hstrName);
    m_strAppCaption.Format("%s", hstrAppName);

#if defined(_DEBUG)
    hstrName.Format("%s %s", m_strAppCaption, hstrSysVer);
#else
    hstrName.Format("%s %s", m_strAppCaption, hstrSysVer);
#endif

    g_clConfig.Open();
    m_strTitle = hstrName;
    UpdateData(FALSE);

    m_ctrSubscribeType.AddString("0-当天第一条开始接收");
    m_ctrSubscribeType.AddString("1-上次断线处开始接收");
    m_ctrSubscribeType.AddString("2-本次登录后开始接收");
    m_ctrSubscribeType.SetCurSel(0);

    m_ctrlBrokerID.AddString(LPCTSTR("1004-GFFUTURES"));
    m_ctrlBrokerID.SetCurSel(0);

    m_ctrlInvestorID.AddString(LPCTSTR("6006"));
    m_ctrlInvestorID.AddString(g_clConfig.m_szTzzdm);
    m_ctrlInvestorID.SetCurSel(0);

    m_ctrlJysdm.AddString(LPCTSTR("CFFEX-中金所"));
    m_ctrlJysdm.AddString(LPCTSTR("CZCE-郑商所"));
    m_ctrlJysdm.AddString(LPCTSTR("DCE-大商所"));
    m_ctrlJysdm.AddString(LPCTSTR("SHFE-上期所"));
    m_ctrlJysdm.SetCurSel(0);

    m_ctrlInstrunentID.AddString(g_clConfig.m_szHydm);
    m_ctrlInstrunentID.SetCurSel(0);

    m_ctrlUseID.AddString(g_clConfig.m_szUserName);
    m_ctrlUseID.SetCurSel(0);

    m_ctrlPriceType.AddString(LPCTSTR("2-限价"));
    m_ctrlPriceType.AddString(LPCTSTR("1-任意价"));
    m_ctrlPriceType.SetCurSel(1);

    m_ctrlDirection.AddString(LPCTSTR("0-买"));
    m_ctrlDirection.AddString(LPCTSTR("1-卖"));
    m_ctrlDirection.SetCurSel(0);

    m_ctrlOffsetFlag.AddString(LPCTSTR("0-开仓"));
    m_ctrlOffsetFlag.AddString(LPCTSTR("1-平仓"));
    m_ctrlOffsetFlag.AddString(LPCTSTR("2-强平"));
    m_ctrlOffsetFlag.AddString(LPCTSTR("3-平今"));
    m_ctrlOffsetFlag.AddString(LPCTSTR("4-平昨"));
    m_ctrlOffsetFlag.AddString(LPCTSTR("5-强减"));
    m_ctrlOffsetFlag.SetCurSel(0);

    m_ctrlHedgeFlag.AddString(LPCTSTR("1-投机"));
    m_ctrlHedgeFlag.AddString(LPCTSTR("2-套利"));
    m_ctrlHedgeFlag.AddString(LPCTSTR("3-套保"));
    m_ctrlHedgeFlag.SetCurSel(0);

    m_pclCtrlListDisplay.InitStorage(MQT_MAINDLG_MSGCOUNT + 3, sizeof(MCQTTD_ERRMSG));
    m_pclCtrlListDisplay.SetHorizontalExtent(1000);
    UpdateData(TRUE);
    m_strCtpServerIP = g_clConfig.m_szIP;
    m_strCtpServerPort = g_clConfig.m_szPort;
    this->m_dWtjg = 2356.0;
    this->m_iWtsl = 1;
    this->m_strWithRefNumExt.Format("%s", "000000000000");
    this->m_strPwd = g_clConfig.m_szPassWord;
    UpdateData(FALSE);

    m_nRequestID = 0;
    m_bStoping = false;

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMcCtpApiDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMcCtpApiDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMcCtpApiDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMcCtpApiDemoDlg::OnCbnSelchangeComboxInstrumentid()
{
}

//////////////////////////////////////////////////////////////////////
//ShowListboxMsg
//以倒序的方式显示信息
//////////////////////////////////////////////////////////////////////
void CMcCtpApiDemoDlg::ShowSpiMsg(const char* const tpszMsg)
{
    if (m_bStoping)
    {
        return;
    }

    OutputDebugString(tpszMsg);
    OutputDebugString("\n");
}

void CMcCtpApiDemoDlg::ShowListboxMsg(const char* const tpszMsg)
{
    if (m_bStoping)
    {
        return;
    }
    //空的消息不显示
    if (tpszMsg == NULL || strlen(tpszMsg) <= 0)
    {
        return;
    }

    m_pclCtrlListDisplay.InsertString(0, tpszMsg);

    return;
}

//////////////////////////////////////////////////////////////////////
//GetFileVersion
//////////////////////////////////////////////////////////////////////
bool CMcCtpApiDemoDlg::GetFileVersion(CString& tstrVersion, LPCTSTR tstrFile)
{
    TCHAR szVersionBuffer[4096] = _T("");
    DWORD dwVerSize;
    DWORD dwHandle;

    //获取文件名
    char hszFilename[1024];
    if (tstrFile == NULL)
    {
        int hiLen = ::GetModuleFileName(NULL, (char*)hszFilename, sizeof(hszFilename));
    }
    else
    {
        _snprintf_s((char*)hszFilename, sizeof(hszFilename), _TRUNCATE, "%s", (char*)tstrFile);
    }

    //获取版本信息
    dwVerSize = GetFileVersionInfoSize((char*)hszFilename, &dwHandle);
    if (dwVerSize == 0 || dwVerSize >= 4096)
        return false;

    if (GetFileVersionInfo((char*)hszFilename, 0, dwVerSize, szVersionBuffer))
    {
        VS_FIXEDFILEINFO * pInfo;        
        unsigned int nInfoLen;

        if (VerQueryValue((char*)szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))
        {
#ifdef _DEBUG
            tstrVersion.Format(_T(" Build %u.%u.%u.%u Debug"),
                HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),
                HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
#else
            tstrVersion.Format(_T(" Build %u.%u.%u.%u Release"),
                HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),
                HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
#endif
            return true;
        }
    }

    return false;
}

//开启启动
void CMcCtpApiDemoDlg::OnBnClickedButtonStart()
{
     //Check
    if (m_bServerStart)
    {
        return;
    }
    m_pclCtrlListDisplay.ResetContent();

    UpdateData(TRUE);

    char szFrontAddress[64] = { 0 };
    
    CheckResource();

    m_pclUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    m_pclUseSpi = new CUserTraderSpi();
    if (NULL == m_pclUserApi)
    {
        MessageBox("创建API实例失败。", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    } 
    if (NULL == m_pclUseSpi)
    {
        CheckResource();
        MessageBox("创建Spi实例失败。", "提示", MB_OK | MB_ICONINFORMATION);
        return ;
    }    

    //注册Api
    m_pclUserApi->RegisterSpi((CThostFtdcTraderSpi*)m_pclUseSpi);
    //订阅私有流
    CString strValue = "";
    GetValue(m_strSubscribeType, strValue);
    m_pclUserApi->SubscribePrivateTopic((THOST_TE_RESUME_TYPE)atoi((LPCSTR)strValue));
    //m_pclUserApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
    //订阅公有流
    m_pclUserApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
    // 设置前置机的地址，可以注册多个地址备用
    if (m_strCtpServerIP.GetLength() > 0 && m_strCtpServerPort.GetLength() > 0)
    {
        _snprintf_s(szFrontAddress, sizeof(szFrontAddress), _TRUNCATE, "tcp://%s:%s", (LPCSTR)m_strCtpServerIP, (LPCSTR)m_strCtpServerPort);
    }
    else
    {
        _snprintf_s(szFrontAddress, sizeof(szFrontAddress), _TRUNCATE, "%s", "tcp://127.0.0.1:2100");
    }
    m_pclUserApi->RegisterFront(szFrontAddress);


    // 使客户端开始与前置机建立连接
    m_pclUserApi->Init();

    //UpdateData(TRUE);
    //开始等待前置机
    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"调用初始化完成 API Init", "等待异步返回");
    this->ShowListboxMsg(m_szErrMsg);

    // 客户端等待前置机完成
    DWORD dwRet =WaitForSingleObject(m_pclUseSpi->m_hEvent, 30000);
    if (dwRet != WAIT_OBJECT_0)
    {
        CheckResource();
        MessageBox("注册上期前置机成功失败,等待超时.", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(), "异步返回前置机注册完成 SPi OnFrontConnected", "异步返回成功");
    this->ShowListboxMsg(m_szErrMsg);
    //设置登录用户编号
    CThostFtdcReqUserLoginField loginfield ;

    memset(&loginfield,0,sizeof(CThostFtdcReqUserLoginField));

    CThostFtdcQryInvestorField stQryInvestorField;

    memset(&stQryInvestorField, 0, sizeof(stQryInvestorField));
    //经纪人代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(loginfield.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    _snprintf_s(stQryInvestorField.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //用户代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(loginfield.UserID, sizeof(TThostFtdcUserIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    _snprintf_s(stQryInvestorField.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //密码
    _snprintf_s(loginfield.Password, sizeof(TThostFtdcPasswordType), _TRUNCATE, "%s", LPCTSTR(m_strPwd));
    
    if (m_pclUserApi->ReqUserLogin(&loginfield, m_nRequestID) < 0)
    {
        CheckResource();
        MessageBox("用户登录请求发送失败.", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }

    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(), "调用用户登陆完成 API ReqUserLogin", "等待异步返回");
    this->ShowListboxMsg(m_szErrMsg);
    if (WAIT_OBJECT_0 != WaitForSingleObject(m_pclUseSpi->m_hEvent, 30000))
    {
        CheckResource();
        MessageBox("用户登录等待响应超时.", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }

    m_pclUserApi->ReqQryInvestor(&stQryInvestorField, m_nRequestID);

    m_clButStart.EnableWindow(FALSE);
    m_bServerStart = true;
    m_bStoping = false;
    m_clButStop.EnableWindow(TRUE);
}

void CMcCtpApiDemoDlg::UserSettlementConfirm()
{
    CThostFtdcQrySettlementInfoConfirmField stReqData;
    memset(&stReqData, 0, sizeof(CThostFtdcQrySettlementInfoConfirmField));
    _snprintf_s(stReqData.BrokerID, sizeof(stReqData.BrokerID), _TRUNCATE, "%s",  LPCTSTR(m_strBrokerID.Left(m_strBrokerID.Find('-'))));
    _snprintf_s(stReqData.InvestorID, sizeof(stReqData.InvestorID), _TRUNCATE, "%s", "9999");
    CThostFtdcSettlementInfoConfirmField stReqData1;
    memset(&stReqData1, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
    _snprintf_s(stReqData1.BrokerID, sizeof(stReqData1.BrokerID), _TRUNCATE, "%s",  LPCTSTR(m_strBrokerID.Left(m_strBrokerID.Find('-'))));
    _snprintf_s(stReqData1.InvestorID, sizeof(stReqData1.InvestorID), _TRUNCATE, "%s", "9999");


    ////用户结算确认查询     
 //   int iResult = m_pclUserApi->ReqQrySettlementInfoConfirm(&stReqData, m_nRequestID);
    //if (iResult != 0)
    //{
    //    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"查询结算是否确认请求失败 API ReqQrySettlementInfoConfirm", "等待异步返回");
    //    this->ShowListboxMsg(m_szErrMsg);
    //    return;
    //}
    //sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"查询结算是否确认请求成功 API ReqQrySettlementInfoConfirm", "等待异步返回");
    //this->ShowListboxMsg(m_szErrMsg);
    //if (WAIT_OBJECT_0 != WaitForSingleObject(m_pclUseSpi->m_hEvent, 10000))                                                                    //等待超时
 //   {
 //       sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"查询结算是否确认请求等待超时 SPI ReqQrySettlementInfoConfirm", "等待异步超时");
    //    this->ShowListboxMsg(m_szErrMsg);
 //       return;
 //   }
    //_snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s %s", GetCurTimeByChar(), "                    异步返回查询结算是否确认请求响应成功 SPI OnRspSettlementInfoConfirm");
    //this->ShowListboxMsg(m_szErrMsg);

 //   //用户结算确认 
 //   iResult = m_pclUserApi->ReqSettlementInfoConfirm(&stReqData1, m_nRequestID);
    //if (0 != iResult)
    //{
    //    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"结算结果确认请求发送失败 API ReqSettlementInfoConfirm", "等待异步返回");
    //    this->ShowListboxMsg(m_szErrMsg);
    //    return;
    //}
    //sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"结算结果确认发送成功 API ReqSettlementInfoConfirm", "等待异步返回");
    //this->ShowListboxMsg(m_szErrMsg);
    //if (WAIT_OBJECT_0 != WaitForSingleObject(m_pclUseSpi->m_hEvent, 10000))
 //   {
 //       sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s,%s,%s", GetCurTimeByChar(),"结算结果确认请求等待超时 API ReqSettlementInfoConfirm", "等待异步超时");
    //    this->ShowListboxMsg(m_szErrMsg);
 //       return;
 //   }
    //_snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s %s", GetCurTimeByChar(), "                  异步返回结算结果确认成功 SPI OnReqSettlementInfoConfirm");
    //this->ShowListboxMsg(m_szErrMsg);
    return;
}

//停止按钮
void CMcCtpApiDemoDlg::OnBnClickedButtonStop()
{
      //Check
    if (!m_bServerStart)
    {
        return;
    }

    CThostFtdcUserLogoutField stField;
    memset(&stField, 0, sizeof(stField));
    //经纪人代码
    CString strValue = "";
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(stField.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //用户代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(stField.UserID, sizeof(TThostFtdcUserIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    m_pclUserApi->ReqUserLogout(&stField, m_nRequestID);

    Sleep(500);
    
    CheckResource();
    UpdateData(TRUE);
    CString strIP, strPort, strUserName, strTzzdm, strPassWord, strHydm;
    GetValue(m_strCtpServerIP, strIP);
    GetValue(m_strCtpServerPort, strPort);
    GetValue(m_strUseID, strUserName);
    GetValue(m_strInvestorID, strTzzdm);
    GetValue(m_strPwd, strPassWord);
    GetValue(m_strInstrumentID, strHydm);
    CStringToChar(strIP, g_clConfig.m_szIP, sizeof(g_clConfig.m_szIP));
    CStringToChar(strPort, g_clConfig.m_szPort, sizeof(g_clConfig.m_szPort));
    CStringToChar(strUserName, g_clConfig.m_szUserName, sizeof(g_clConfig.m_szUserName));
    CStringToChar(strTzzdm, g_clConfig.m_szTzzdm, sizeof(g_clConfig.m_szTzzdm));
    CStringToChar(strPassWord, g_clConfig.m_szPassWord, sizeof(g_clConfig.m_szPassWord));
    CStringToChar(strHydm, g_clConfig.m_szHydm, sizeof(g_clConfig.m_szHydm));
    g_clConfig.SaveBase();
    m_bStoping = true;
    m_pclCtrlListDisplay.ResetContent();
    m_clButStop.EnableWindow(FALSE);
    m_bServerStart = false;
    m_bStoping = false;
    m_clButStart.EnableWindow(TRUE);
}

//退出按钮
void CMcCtpApiDemoDlg::OnBnClickedButtonExit()
{
    CheckResource();
    //Sleep(1000);
    UpdateData(TRUE);
    CString strIP, strPort, strUserName, strTzzdm, strPassWord, strHydm;
    GetValue(m_strCtpServerIP, strIP);
    GetValue(m_strCtpServerPort, strPort);
    GetValue(m_strUseID, strUserName);
    GetValue(m_strInvestorID, strTzzdm);
    GetValue(m_strPwd, strPassWord);
    GetValue(m_strInstrumentID, strHydm);
    CStringToChar(strIP, g_clConfig.m_szIP, sizeof(g_clConfig.m_szIP));
    CStringToChar(strPort, g_clConfig.m_szPort, sizeof(g_clConfig.m_szPort));
    CStringToChar(strUserName, g_clConfig.m_szUserName, sizeof(g_clConfig.m_szUserName));
    CStringToChar(strTzzdm, g_clConfig.m_szTzzdm, sizeof(g_clConfig.m_szTzzdm));
    CStringToChar(strPassWord, g_clConfig.m_szPassWord, sizeof(g_clConfig.m_szPassWord));
    CStringToChar(strHydm, g_clConfig.m_szHydm, sizeof(g_clConfig.m_szHydm));
    g_clConfig.SaveBase();
    CMcCtpApiDemoDlg::OnClose();
    CDialogEx::OnCancel();
}

void CMcCtpApiDemoDlg::OnBnClickedButtonOrder()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcInputOrderField InputOrder;
    memset(&InputOrder,0,sizeof(CThostFtdcInputOrderField));
    //经纪人代码
    CString strValue = "";

    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(InputOrder.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(InputOrder.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(InputOrder.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //获取个唯一报单引用
    _snprintf_s(InputOrder.OrderRef, sizeof(TThostFtdcOrderRefType), _TRUNCATE,"%s%u", InputOrder.BrokerID, GetTickCount64());
    //用户代码
    strValue = ((m_strUseID.Find('-') != -1) ? (m_strUseID.Left(m_strUseID.Find('-'))) : m_strUseID);
    _snprintf_s(InputOrder.UserID, sizeof(TThostFtdcUserIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //报价价格条件
    strValue = ((m_strPriceType.Find('-') != -1) ? (m_strPriceType.Left(m_strPriceType.Find('-'))) : m_strPriceType);
    InputOrder.OrderPriceType = strValue[0];
    //买卖方向
    strValue = ((m_strDirection.Find('-') != -1) ? (m_strDirection.Left(m_strDirection.Find('-'))) : m_strDirection);
    InputOrder.Direction = strValue[0];
    //组合开平标志
    strValue = ((m_strOffsetFlag.Find('-') != -1) ? (m_strOffsetFlag.Left(m_strOffsetFlag.Find('-'))) : m_strOffsetFlag);
    _snprintf_s(InputOrder.CombOffsetFlag, sizeof(TThostFtdcCombOffsetFlagType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //组合投机投保标志
    strValue = ((m_strHegeFlag.Find('-') != -1) ? (m_strHegeFlag.Left(m_strHegeFlag.Find('-'))) : m_strHegeFlag);
    _snprintf_s(InputOrder.CombHedgeFlag, sizeof(TThostFtdcCombHedgeFlagType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //委托价格
    InputOrder.LimitPrice = m_dWtjg;
    //委托数量
    InputOrder.VolumeTotalOriginal = m_iWtsl;
    //以下 可以不进行设置
    //有效期类型
    if (m_dWtjg <= 0)
    {
        InputOrder.TimeCondition = THOST_FTDC_TC_IOC;
    } 
    else
    {
        InputOrder.TimeCondition = THOST_FTDC_TC_GFD;
    }

    //GTD日期
    strcpy_s(InputOrder.GTDDate, "");
    //成交量类型
    InputOrder.VolumeCondition = THOST_FTDC_VC_AV;
    //最小成交量
    InputOrder.MinVolume = 0;
    //触发条件
    InputOrder.ContingentCondition = THOST_FTDC_CC_Immediately;
    //止损价
    InputOrder.StopPrice = 0;
    //强平原因
    InputOrder.ForceCloseReason  = THOST_FTDC_FCC_NotForceClose;
    //自动挂起标志
    InputOrder.IsAutoSuspend = 0;
    InputOrder.RequestID = GetTickCount();

    if (m_pclUserApi->ReqOrderInsert(&InputOrder, ++m_nRequestID)<0)
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: 报单号->%s，订单状态->%s", GetCurTimeByChar(), InputOrder.OrderRef, "期货订单下单失败");
        ShowListboxMsg(m_szErrMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: 报单号->%s，订单状态->%s", GetCurTimeByChar(), InputOrder.OrderRef, "期货订单发送成功");
        ShowListboxMsg(m_szErrMsg);

        m_strWithRefNumExt.Format("%s", InputOrder.OrderRef);
        UpdateData(FALSE);
    }
}


void CMcCtpApiDemoDlg::OnBnClickedButtonWithdraw()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }

    UpdateData(TRUE);

    CThostFtdcInputOrderActionField InputOrderAction;
    memset(&InputOrderAction,0,sizeof(CThostFtdcInputOrderActionField));

    //经纪人代码
    CString strValue = "";

    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(InputOrderAction.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(InputOrderAction.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(InputOrderAction.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    _snprintf_s(InputOrderAction.OrderSysID, sizeof(TThostFtdcOrderSysIDType), _TRUNCATE, "%d", 0);
    //报单编号
    _snprintf_s(InputOrderAction.OrderRef, sizeof(TThostFtdcOrderRefType), _TRUNCATE, "%s", LPCTSTR(m_strWithRefNumExt));
    InputOrderAction.RequestID = GetTickCount();

    if (m_pclUserApi->ReqOrderAction(&InputOrderAction, ++m_nRequestID)<0)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 报单号->%s, 订单状态->%s", GetCurTimeByChar(),InputOrderAction.OrderRef, "期货订单撤单失败");
        ShowListboxMsg(m_szErrMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 报单号->%s，订单状态->%s", GetCurTimeByChar(),InputOrderAction.OrderRef, "期货订单已发送成功");
        ShowListboxMsg(m_szErrMsg);
    }
}


void CMcCtpApiDemoDlg::OnBnClickedButtonClear()
{
    m_pclCtrlListDisplay.ResetContent();
}


void CMcCtpApiDemoDlg::OnLbnDblclkListDisplay()
{
    CString hstrBuf;
    m_pclCtrlListDisplay.GetText(m_pclCtrlListDisplay.GetCurSel(), hstrBuf);
    ::MessageBox(m_hWnd, hstrBuf, "详细信息", MB_OK | MB_ICONINFORMATION);
    return;
}


HBRUSH CMcCtpApiDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
    if (GetDlgItem(IDC_STATIC_TITLE) == pWnd)
    {
        pDC->SelectObject(&m_clTitleFont);
    }
    return hbr;
}


void CMcCtpApiDemoDlg::OnDestroy()
{
    CheckResource();

    CDialogEx::OnDestroy();
}


void CMcCtpApiDemoDlg::OnBnClickedButtonQryInvestorPosition()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);
    
    CThostFtdcQryInvestorPositionField InvestorPosition;
    memset(&InvestorPosition, 0, sizeof(CThostFtdcQryInvestorPositionField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(InvestorPosition.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(InvestorPosition.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(InvestorPosition.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    
    m_pclUserApi->ReqQryInvestorPosition(&InvestorPosition, 1);
}


void CMcCtpApiDemoDlg::OnBnClickedButtonQryTradingAccount()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }

    UpdateData(TRUE);

    CThostFtdcQryTradingAccountField TradingAccount;
    memset(&TradingAccount, 0, sizeof(CThostFtdcQryTradingAccountField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(TradingAccount.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(TradingAccount.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryTradingAccount(&TradingAccount, 1);
}

// 查询交易所信息
void CMcCtpApiDemoDlg::OnBnClickedButtonQryExchange()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryExchangeField Exchange;
    memset(&Exchange, 0, sizeof(CThostFtdcQryExchangeField));

    CString strValue = "";

    strValue = ((m_strJysdm.Find('-') != -1) ? (m_strJysdm.Left(m_strJysdm.Find('-'))) : m_strJysdm);
    _snprintf_s(Exchange.ExchangeID, sizeof(TThostFtdcExchangeIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryExchange(&Exchange, 1);
}

// 查询合约信息
void CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrument()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryInstrumentField Instrument;
    memset(&Instrument, 0, sizeof(CThostFtdcQryInstrumentField));

    CString strValue = "";
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(Instrument.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    _snprintf_s(Instrument.ExchangeInstID, sizeof(TThostFtdcExchangeInstIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    strValue = ((m_strJysdm.Find('-') != -1) ? (m_strJysdm.Left(m_strJysdm.Find('-'))) : m_strJysdm);
    _snprintf_s(Instrument.ExchangeID, sizeof(TThostFtdcExchangeIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    _snprintf_s(Instrument.ProductID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", "IF");
    
    m_pclUserApi->ReqQryInstrument(&Instrument, 1);
}

// 查询合约保证金率信息
void CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrumentMarginRate()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryInstrumentMarginRateField InstrumentMarginRate;
    memset(&InstrumentMarginRate, 0, sizeof(CThostFtdcQryInstrumentMarginRateField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(InstrumentMarginRate.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(InstrumentMarginRate.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(InstrumentMarginRate.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    InstrumentMarginRate.HedgeFlag = '1';

    m_pclUserApi->ReqQryInstrumentMarginRate(&InstrumentMarginRate, 1);
}


void CMcCtpApiDemoDlg::OnBnClickedButtonQryInstrumentCommissionRate()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryInstrumentCommissionRateField InstrumentCommissionRate;
    memset(&InstrumentCommissionRate, 0, sizeof(CThostFtdcQryInstrumentCommissionRateField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(InstrumentCommissionRate.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(InstrumentCommissionRate.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //合约代码
    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(InstrumentCommissionRate.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    
    m_pclUserApi->ReqQryInstrumentCommissionRate(&InstrumentCommissionRate, 1);
}


void CMcCtpApiDemoDlg::OnBnClickedButtonQryBrokerTradingParams()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);
    
    CThostFtdcQryBrokerTradingParamsField BrokerTradingParams;
    memset(&BrokerTradingParams, 0, sizeof(CThostFtdcQryBrokerTradingParamsField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(BrokerTradingParams.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(BrokerTradingParams.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryBrokerTradingParams(&BrokerTradingParams, 1);
}


void CMcCtpApiDemoDlg::OnBnClickedButtonQryBrokerTradingAlgos()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryBrokerTradingAlgosField BrokerTradingAlgos;
    memset(&BrokerTradingAlgos, 0, sizeof(CThostFtdcQryBrokerTradingAlgosField));

    CString strValue = "";

    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(BrokerTradingAlgos.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    strValue = ((m_strJysdm.Find('-') != -1) ? (m_strJysdm.Left(m_strJysdm.Find('-'))) : m_strJysdm);
    _snprintf_s(BrokerTradingAlgos.ExchangeID, sizeof(TThostFtdcExchangeIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    strValue = ((m_strInstrumentID.Find('-') != -1) ? (m_strInstrumentID.Left(m_strInstrumentID.Find('-'))) : m_strInstrumentID);
    _snprintf_s(BrokerTradingAlgos.InstrumentID, sizeof(TThostFtdcInstrumentIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    
    m_pclUserApi->ReqQryBrokerTradingAlgos(&BrokerTradingAlgos, 1);
}


// 资金账号密钥查询
void CMcCtpApiDemoDlg::OnBnClickedButtonQryCFMMCTradingAccountKey()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryCFMMCTradingAccountKeyField CFMMCTradingAccountKeyField;
    memset(&CFMMCTradingAccountKeyField, 0, sizeof(CThostFtdcQryCFMMCTradingAccountKeyField));

    CString strValue = "";
    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(CFMMCTradingAccountKeyField.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(CFMMCTradingAccountKeyField.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryCFMMCTradingAccountKey(&CFMMCTradingAccountKeyField, 1);
}

// 指令委托查询
void CMcCtpApiDemoDlg::OnBnClickedButtonQryOrder()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryOrderField stQryOrderField;
    memset(&stQryOrderField, 0, sizeof(CThostFtdcQryOrderField));

    CString strValue = "";
    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(stQryOrderField.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(stQryOrderField.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryOrder(&stQryOrderField, 0);
}

// 指令成交查询
void CMcCtpApiDemoDlg::OnBnClickedButtonQryTrade()
{
    if (!m_bServerStart)
    {
        MessageBox("需要启动程序后才能执行!", "提示", MB_OK | MB_ICONINFORMATION);
        return;
    }
    UpdateData(TRUE);

    CThostFtdcQryTradeField stQryTradeField;
    memset(&stQryTradeField, 0, sizeof(CThostFtdcQryTradeField));

    CString strValue = "";
    //经纪公司代码
    strValue = ((m_strBrokerID.Find('-') != -1) ? (m_strBrokerID.Left(m_strBrokerID.Find('-'))) : m_strBrokerID);
    _snprintf_s(stQryTradeField.BrokerID, sizeof(TThostFtdcBrokerIDType), _TRUNCATE, "%s", LPCTSTR(strValue));
    //投资者代码
    strValue = ((m_strInvestorID.Find('-') != -1) ? (m_strInvestorID.Left(m_strInvestorID.Find('-'))) : m_strInvestorID);
    _snprintf_s(stQryTradeField.InvestorID, sizeof(TThostFtdcInvestorIDType), _TRUNCATE, "%s", LPCTSTR(strValue));

    m_pclUserApi->ReqQryTrade(&stQryTradeField, 0);
}

bool CMcCtpApiDemoDlg::CheckResource()
{
    try
    {
        if (m_pclUserApi != NULL)
        {
            m_pclUserApi->RegisterSpi(NULL);
            m_pclUserApi->Release();
            Sleep(100);
            m_pclUserApi = NULL;
        }
        if (m_pclUseSpi != NULL)
        {
            delete m_pclUseSpi;
            m_pclUseSpi = NULL;
        }
    }
    catch (...)
    {
        m_pclUserApi = NULL;
        m_pclUseSpi = NULL;
    }

    return true;
}


void CMcCtpApiDemoDlg::GetValue(const CString &strSrc, CString &strDest, CString strDelim)
{
    strDest = "";
    if (strSrc.IsEmpty())
    {
        return;
    }

    int iPos = strSrc.Find(strDelim);
    if (iPos <= 0)
    {
        strDest = strSrc;
    }
    else
    {
        strDest = strSrc.Left(iPos);
    }
}