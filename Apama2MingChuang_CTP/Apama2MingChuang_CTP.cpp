// Apama2MingChuang_CTP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <atlstr.h>
#include "UserTraderSpi.h"

using namespace std;

CThostFtdcTraderApi* m_pclUserApi = NULL;
CUserTraderSpi* m_pclUseSpi = NULL;
CString m_strSubscribeType;


void CONNECT_CTP()
{
	m_pclUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	m_pclUseSpi = new CUserTraderSpi();
	if (NULL == m_pclUserApi)
	{
		cout << "创建API实例失败。" << endl;
		//MessageBox("创建API实例失败。", "提示", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (NULL == m_pclUseSpi)
	{
		//CheckResource();
		cout << "创建Spi实例失败。" << endl;
		//MessageBox("创建Spi实例失败。", "提示", MB_OK | MB_ICONINFORMATION);
		return;
	}

	//注册Api
	m_pclUserApi->RegisterSpi((CThostFtdcTraderSpi*)m_pclUseSpi);
	//订阅私有流
	CString strValue = "";
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
	sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(), "调用初始化完成 API Init", "等待异步返回");
	this->ShowListboxMsg(m_szErrMsg);

	// 客户端等待前置机完成
	DWORD dwRet = WaitForSingleObject(m_pclUseSpi->m_hEvent, 30000);
	if (dwRet != WAIT_OBJECT_0)
	{
		CheckResource();
		MessageBox("注册上期前置机成功失败,等待超时.", "提示", MB_OK | MB_ICONINFORMATION);
		return;
	}
	sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(), "异步返回前置机注册完成 SPi OnFrontConnected", "异步返回成功");
	this->ShowListboxMsg(m_szErrMsg);
	//设置登录用户编号
	CThostFtdcReqUserLoginField loginfield;

	memset(&loginfield, 0, sizeof(CThostFtdcReqUserLoginField));

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

int main()
{
    return 0;
}

