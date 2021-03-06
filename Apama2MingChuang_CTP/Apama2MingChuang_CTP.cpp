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


// UserApi对象
CThostFtdcTraderApi* pUserApi;

char  FRONT_ADDR[] = "tcp://111.207.179.10:51205";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "1004";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "180125";			// 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType  PASSWORD = "12345678";			// 注意输入你自己的simnow仿真用户密码


TThostFtdcInstrumentIDType INSTRUMENT_ID = "T1809";	// 合约代码 ，注意与时俱进改变合约ID,避免使用过时合约
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// 买卖方向
TThostFtdcPriceType	LIMIT_PRICE = 2380;				// 价格

													// 请求编号
int iRequestID = 0;

int main()
{
	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
 	CUserTraderSpi* pUserSpi = new CUserTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
	//pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);					// 注册私有流
	pUserApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	pUserApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();
	//pUserSpi->OnFrontConnected();
	pUserApi->Join();

	//设置登录用户编号
	CThostFtdcReqUserLoginField loginfield;

	memset(&loginfield, 0, sizeof(loginfield));
	strcpy_s(loginfield.BrokerID, BROKER_ID);
	strcpy_s(loginfield.UserID, INVESTOR_ID);
	strcpy_s(loginfield.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&loginfield, ++iRequestID);
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
	while (1);

    return 0;
}

