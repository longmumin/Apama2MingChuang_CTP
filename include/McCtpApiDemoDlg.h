
// McCtpApiDemoDlg.h : header file
//

#pragma once
#include "UserTraderSpi.h"
#include"resource.h"
#include "afxwin.h"

        
// CMcCtpApiDemoDlg dialog
class CMcCtpApiDemoDlg : public CDialogEx
{
// Construction
public:
    CMcCtpApiDemoDlg(CWnd* pParent = NULL);    // standard constructor
    ~CMcCtpApiDemoDlg();
// Dialog Data
    enum { IDD = IDD_McCtpApiDemo_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
protected:
    
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    CThostFtdcTraderApi* m_pclUserApi;    
    CUserTraderSpi* m_pclUseSpi;  
    int m_nRequestID;
    bool m_bStoping;                             // 准备结束线程
    bool m_bServerStart;                         // 服务是否启动  
    char m_szErrMsg[512];
    char m_szCurLogTime[56];
    CFont m_clTitleFont;  
public:
    static const unsigned int MQT_MAINDLG_MSGCOUNT = 800;
    typedef char MCQTTD_ERRMSG[512];
    void ShowListboxMsg(const char* const tpszMsg);
    void ShowSpiMsg(const char* const tpszMsg);
    char* const GetCurTimeByChar(void);
    void UserSettlementConfirm();
    bool GetFileVersion(CString& tstrVersion, LPCTSTR tstrFile);
    bool CheckResource();
    void GetValue(const CString &strSrc, CString &strDest, CString strDelim = "-");

public:

    CString m_strTitle;
    CStatic m_ctrlTitle;
    CString m_strAppCaption;

    CButton m_clButStart;
    CButton m_clButStop;
    CString m_strDirection;
    CString m_strHegeFlag;
    CString m_strInstrumentID;
    CString m_strInvestorID;
    CString m_strJysdm;
    CString m_strOffsetFlag;
    CString m_strPriceType;
    CString m_strUseID;
    CString m_strWithRefNumExt;
    CString m_strCtpServerIP;
    CString m_strCtpServerPort;
    CString m_strPwd;
    
    CString m_strBrokerID;
    CComboBox m_ctrlBrokerID;
    CComboBox m_ctrlDirection;
    CComboBox m_ctrlHedgeFlag;
    CComboBox m_ctrlInstrunentID;
    CComboBox m_ctrlInvestorID;
    CComboBox m_ctrlJysdm;
    CComboBox m_ctrlOffsetFlag;
    CComboBox m_ctrlPriceType;
    CComboBox m_ctrlUseID;
    CListBox m_pclCtrlListDisplay;
    CComboBox m_ctrSubscribeType;
    double m_dWtjg;
    int m_iWtsl;

    afx_msg void OnBnClickedButtonStart();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnBnClickedButtonExit();
    afx_msg void OnBnClickedButtonOrder();
    afx_msg void OnBnClickedButtonWithdraw();
    afx_msg void OnBnClickedButtonClear();
    afx_msg void OnCbnSelchangeComboxInstrumentid();
    afx_msg void OnLbnDblclkListDisplay();

    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedButtonQryInvestorPosition();
    afx_msg void OnBnClickedButtonQryTradingAccount();
    afx_msg void OnBnClickedButtonQryExchange();
    afx_msg void OnBnClickedButtonQryInstrument();
    afx_msg void OnBnClickedButtonQryInstrumentMarginRate();
    afx_msg void OnBnClickedButtonQryInstrumentCommissionRate();
    afx_msg void OnBnClickedButtonQryBrokerTradingParams();
    afx_msg void OnBnClickedButtonQryBrokerTradingAlgos();
    afx_msg void OnBnClickedButtonQryCFMMCTradingAccountKey();    
    afx_msg void OnBnClickedButtonQryOrder();
    afx_msg void OnBnClickedButtonQryTrade();
    CString m_strSubscribeType;
};

extern CMcCtpApiDemoDlg *g_pclDlg;