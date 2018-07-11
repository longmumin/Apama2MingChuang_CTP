#include "stdafx.h"
#include "UserTraderSpi.h"
//#include "McCtpApiDemoDlg.h"
#include <string>

CUserTraderSpi::CUserTraderSpi(void)
{
    //m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    m_bIsSettlement  = false;
}

CUserTraderSpi::~CUserTraderSpi(void)
{
    /*if (NULL != m_hEvent)
    {
        CloseHandle(m_hEvent);
        m_hEvent = NULL;
    }*/
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CUserTraderSpi:: OnFrontConnected()
{
    //设置
    //SetEvent(m_hEvent);

    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"异步返回前置机注册完成 SPi OnFrontConnected", "异步返回成功");

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);

}
    
///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void CUserTraderSpi:: OnFrontDisconnected(int nReason)
{
    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s", GetCurTimeByChar(), "连接前置机中断 SPi OnFrontDisconnected");

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}
        
///登录请求响应
void CUserTraderSpi:: OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if ((pRspUserLogin == NULL) || (pRspInfo->ErrorID < 0))
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"异步返回登陆失败 SPi OnRspUserLogin", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"异步返回登陆完成 SPi OnRspUserLogin", "异步返回成功");
    }

    //SetEvent(m_hEvent);

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///登出请求响应
void CUserTraderSpi:: OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

}

///报单录入请求响应
void CUserTraderSpi:: OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pInputOrder != NULL) ? pInputOrder->OrderRef : "");

    if ((pInputOrder == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 报单号%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "下单错误,", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,报单号%s,%s", GetCurTimeByChar(),"异步返回下单完成 SPi OnRspOrderInsert", pInputOrder->OrderRef,"异步返回成功");

    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///报单操作请求响应
void CUserTraderSpi:: OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pInputOrderAction != NULL) ? pInputOrderAction->OrderRef : "");

    if ((pInputOrderAction == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 报单号%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "撤单错误,", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,报单号%s,%s", GetCurTimeByChar(),"异步返回撤单完成 SPi OnRspOrderInsert",pInputOrderAction->OrderRef, "异步返回成功");
    }

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}



///请求查询报单响应
void CUserTraderSpi:: OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pOrder != NULL) ? pOrder->OrderRef : "");

    if ((pOrder == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询报单 报单号%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "查询报单失败,", pRspInfo->ErrorMsg);
    }
    else
    {
        char szOrderStatus[30] = { 0 };
        char szOrderSubmitStatus[30] = { 0 };
        GetOrderStatus(pOrder->OrderStatus, szOrderStatus, sizeof(szOrderStatus));
        GetOrderSubmitStatus(pOrder->OrderSubmitStatus, szOrderSubmitStatus, sizeof(szOrderSubmitStatus));
        //_snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询报单 报单号%s %s 委托状态:%c", GetCurTimeByChar(),pOrder->OrderRef, "查询报单成功", pOrder->OrderStatus);
        _snprintf_s(m_szErrMsg, sizeof(m_szErrMsg), _TRUNCATE, "%s: 查询报单 报单号->%s, 订单状态->%s, 提交状态->%s, 委托数量->%d,剩余数量->%d", GetCurTimeByChar(), pOrder->OrderRef,
            szOrderStatus, szOrderSubmitStatus, pOrder->VolumeTotalOriginal, pOrder->VolumeTotal);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询成交响应
void CUserTraderSpi:: OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pTrade != NULL) ? pTrade->OrderRef : "");

    if ((pTrade == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询成交 报单号%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "查询成交失败,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询成交 报单号%s %s", GetCurTimeByChar(),pTrade->OrderRef, "查询成交成功");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询投资者持仓响应
void CUserTraderSpi:: OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strInvestorID = ((pInvestorPosition != NULL) ? pInvestorPosition->InvestorID : "");

    if ((pInvestorPosition == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询投资者持仓 投资者%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "查询投资者持仓失败,",pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询投资者持仓 投资者%s %s", GetCurTimeByChar(), pInvestorPosition->InvestorID, "查询投资者持仓成功");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询资金账户响应
void CUserTraderSpi:: OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strInvestorID = ((pTradingAccount != NULL) ? pTradingAccount->AccountID : "");

    if ((pTradingAccount == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询资金账号 账号%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "查询资金账号失败,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询资金账号 账号%s %s", GetCurTimeByChar(),pTradingAccount->AccountID, "查询资金账号成功");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}


void CUserTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInvestorID = ((pInvestor != NULL) ? pInvestor->InvestorID : "");

    if ((pInvestor == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询BrokerID 账号%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "查询资金账号失败,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询InvestorID 账号%s %s", GetCurTimeByChar(),pInvestor->InvestorID, "查询资金账号成功");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}



///投资者结算结果确认响应
void CUserTraderSpi:: OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if (NULL == pSettlementInfoConfirm)
    {
         _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回%s, %s", GetCurTimeByChar(), "投资者结算结果确认失败,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回%s, %s", GetCurTimeByChar(), pSettlementInfoConfirm->BrokerID, "投资者结算结果确认成功");

    }
    //SetEvent(m_hEvent);
    //g_pclDlg->ShowSpiMsg(m_szErrMsg);
    return;
}

///请求查询投资者结算结果响应
void CUserTraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (NULL == pSettlementInfoConfirm)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s, %s", GetCurTimeByChar(), "异步返回请求查询投资者结算结果响应失败,", pRspInfo->ErrorMsg);    
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s, %s", GetCurTimeByChar(), pSettlementInfoConfirm->BrokerID, "异步返回请求查询投资者结算结果响应成功");
    }

    //SetEvent(m_hEvent);

    m_bIsSettlement = true;

    //g_pclDlg->ShowSpiMsg(m_szErrMsg);

    return;
}

///请求查询交易所结果响应
void CUserTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strExchangeID = ((pExchange != NULL) ? pExchange->ExchangeID : "");

    if ((pExchange == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询交易所 %s %s%s", GetCurTimeByChar(), strExchangeID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询交易所成功: ExchangeID= %s, ExchangeName = %s, ExchangeProperty = %c", GetCurTimeByChar(), pExchange->ExchangeID, pExchange->ExchangeName, pExchange->ExchangeProperty);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询合约结果响应
void CUserTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrument != NULL) ? pInstrument->InstrumentID : "");

    if ((pInstrument == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询合约 %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: 查询合约成功: InstrumentID = %s|ExchangeID = %s|InstrumentName = %s|ExchangeInstID = %s|ProductID = %s|ProductClass = %c| DeliveryYear = %d|DeliveryMonth = %d|MaxMarketOrderVolume = %d|MinMarketOrderVolume = %d", 
                    GetCurTimeByChar(), 
                    pInstrument->InstrumentID, 
                    pInstrument->ExchangeID, 
                    pInstrument->InstrumentName,
                    pInstrument->ExchangeInstID, 
                    pInstrument->ProductID, 
                    pInstrument->ProductClass, 
                    pInstrument->DeliveryYear, 
                    pInstrument->DeliveryMonth, 
                    pInstrument->MaxMarketOrderVolume, 
                    pInstrument->MinMarketOrderVolume);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询合约保证金率响应
void CUserTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrumentMarginRate != NULL) ? pInstrumentMarginRate->InstrumentID : "");

    if ((pInstrumentMarginRate == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询合约保证金率 %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: 查询合约保证金率成功: InstrumentID = %s|InvestorRange = %c|BrokerID = %s|InvestorID = %s|HedgeFlag = %c", 
                    GetCurTimeByChar(), 
                    pInstrumentMarginRate->InstrumentID, 
                    pInstrumentMarginRate->InvestorRange,
                    pInstrumentMarginRate->BrokerID, 
                    pInstrumentMarginRate->InvestorID, 
                    pInstrumentMarginRate->HedgeFlag);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询合约手续费率响应
void CUserTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrumentCommissionRate != NULL) ? pInstrumentCommissionRate->InstrumentID : "");

    if ((pInstrumentCommissionRate == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询合约手续费率 %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: 查询合约手续费率成功: InstrumentID = %s|InvestorRange = %c|BrokerID = %s|InvestorID = %s|OpenRatioByMoney = %f|OpenRatioByVolume = %f|CloseRatioByMoney = %f|CloseRatioByVolume = %f|CloseTodayRatioByMoney = %f|CloseTodayRatioByVolume = %f", 
                    GetCurTimeByChar(), 
                    pInstrumentCommissionRate->InstrumentID, 
                    pInstrumentCommissionRate->InvestorRange, 
                    pInstrumentCommissionRate->BrokerID, 
                    pInstrumentCommissionRate->InvestorID, 
                    pInstrumentCommissionRate->OpenRatioByMoney, 
                    pInstrumentCommissionRate->OpenRatioByVolume, 
                    pInstrumentCommissionRate->CloseRatioByMoney, 
                    pInstrumentCommissionRate->CloseRatioByVolume, 
                    pInstrumentCommissionRate->CloseTodayRatioByMoney, 
                    pInstrumentCommissionRate->CloseTodayRatioByVolume);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询经纪公司交易参数
void CUserTraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInvestorID = ((pBrokerTradingParams != NULL) ? pBrokerTradingParams->InvestorID : "");

    if ((pBrokerTradingParams == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询经纪公司交易参数 %s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询经纪公司交易参数成功: InvestorID = %s, MarginPriceType = %c", GetCurTimeByChar(), pBrokerTradingParams->InvestorID, pBrokerTradingParams->MarginPriceType);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///请求查询经纪公司交易算法
void CUserTraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strExchangeID = ((pBrokerTradingAlgos != NULL) ? pBrokerTradingAlgos->ExchangeID : "");

    if ((pBrokerTradingAlgos == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询经纪公司交易算法 %s %s%s", GetCurTimeByChar(), strExchangeID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询经纪公司交易算法成功: ExchangeID = %s, InstrumentID = %s", GetCurTimeByChar(), pBrokerTradingAlgos->ExchangeID, pBrokerTradingAlgos->InstrumentID);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///查询保证金监管系统经纪公司资金账户密钥响应
void CUserTraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strBrokerID = ((pCFMMCTradingAccountKey != NULL) ? pCFMMCTradingAccountKey->BrokerID : "");

    if ((pCFMMCTradingAccountKey == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 查询保证金监管系统经纪公司资金账户密钥 %s %s%s", GetCurTimeByChar(), strBrokerID.c_str(), "失败, 错误信息:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: 查询保证金监管系统经纪公司资金账户密钥成功: BrokerID = %s, ParticipantID = %s, AccountID = %s, KeyID = %d, CurrentKey = %s", 
                    GetCurTimeByChar(), 
                    pCFMMCTradingAccountKey->BrokerID, 
                    pCFMMCTradingAccountKey->ParticipantID,
                    pCFMMCTradingAccountKey->AccountID, 
                    pCFMMCTradingAccountKey->KeyID, 
                    pCFMMCTradingAccountKey->CurrentKey);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///错误应答
void CUserTraderSpi:: OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if (pRspInfo == NULL)
    {
        return;
    }

    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s错误信息%s", GetCurTimeByChar(), pRspInfo->ErrorMsg);
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

//////////////////////////////////////////////////////////////////////////
//功能：取得当前时间
//输入：无
//输出：字符串形式的时间(有分隔符) HH:MM:SS
//////////////////////////////////////////////////////////////////////////
char* const CUserTraderSpi::GetCurTimeByChar(void)
{

   // SYSTEMTIME hstTmLocal;

    //::GetLocalTime(&hstTmLocal);
    //_snprintf_s((char*)m_szCurLogTime, sizeof(m_szCurLogTime), _TRUNCATE, "[%02d:%02d:%02d:%03d]", hstTmLocal.wHour, hstTmLocal.wMinute, hstTmLocal.wSecond, hstTmLocal.wMilliseconds);

    //return (char*)m_szCurLogTime;
	return NULL;
}

void CUserTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    if (pOrder == NULL)
    {
        return;
    }

    char szOrderStatus[30]={0};
    char szOrderSubmitStatus[30]={0};

    GetOrderStatus(pOrder->OrderStatus, szOrderStatus, sizeof(szOrderStatus));
    GetOrderSubmitStatus(pOrder->OrderSubmitStatus, szOrderSubmitStatus, sizeof(szOrderSubmitStatus));

    if (strlen(pOrder->StatusMsg) <= 0)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回 报单号->%s, 订单状态->%s, 提交状态->%s, 委托数量->%d", GetCurTimeByChar(), pOrder->OrderRef,
            szOrderStatus, szOrderSubmitStatus, pOrder->VolumeTotal);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回 报单号->%s, 订单状态->%s, 提交状态->%s, 委托数量->%d, 信息->%s", GetCurTimeByChar(), pOrder->OrderRef,
            szOrderStatus, szOrderSubmitStatus, pOrder->VolumeTotal, pOrder->StatusMsg);
    }

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

void CUserTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    if (pTrade == NULL)
    {
        return;
    }

    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回 报单号->%s, 成交状态->%s, 成交笔数->%d, 成交价格->%f", 
                                                  GetCurTimeByChar(),pTrade->OrderRef,
                                                  "期货订单已成交",pTrade->Volume,
                                                  pTrade->Price);
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///报单录入错误回报
void CUserTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    if ((pInputOrder == NULL) || (pRspInfo == NULL))
    {
        return;
    }

    if (pRspInfo->ErrorID<0)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: 异步返回 报单号->%s, 错误信息->%s, 详细信息->%s", 
                                                    GetCurTimeByChar(),pInputOrder->OrderRef,
                                                    "无效的期货订单",pRspInfo->ErrorMsg);
        //g_pclDlg->ShowListboxMsg(m_szErrMsg);
    }
}

///报单操作错误回报
void CUserTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{

}

void CUserTraderSpi::GetOrderStatus(char cOrderStatus, char *pszStatus,int iLen)
{
    if ((pszStatus == NULL) || (iLen <= 0))
    {
        return;
    }

    switch (cOrderStatus)
    {
        ///全部成交
    case THOST_FTDC_OST_AllTraded:
        {
            strncpy_s(pszStatus, iLen,"全部成交", _TRUNCATE);
            break;
        }
        ///部分成交还在队列中
    case THOST_FTDC_OST_PartTradedQueueing:
        {
            strncpy_s(pszStatus, iLen, "部分成交还在队列中", _TRUNCATE);
            break;
        }
        ///部分成交不在队列中
    case THOST_FTDC_OST_PartTradedNotQueueing:
        {
            strncpy_s(pszStatus, iLen, "部分成交不在队列中", _TRUNCATE);
            break;
        }
        ///未成交还在队列中
    case THOST_FTDC_OST_NoTradeQueueing:
        {
            strncpy_s(pszStatus, iLen, "未成交还在队列中", _TRUNCATE);
            break;
        }
        ///未成交不在队列中
    case THOST_FTDC_OST_NoTradeNotQueueing:
        {
            strncpy_s(pszStatus, iLen, "未成交不在队列中", _TRUNCATE);
            break;
        }
        ///撤单
    case THOST_FTDC_OST_Canceled:
        {
            strncpy_s(pszStatus, iLen, "撤单", _TRUNCATE);
            break;
        }
        ///未知
    case THOST_FTDC_OST_Unknown:
        {
            strncpy_s(pszStatus, iLen, "未知", _TRUNCATE);
            break;
        }
        ///尚未触发
    case THOST_FTDC_OST_NotTouched:
        {
            strncpy_s(pszStatus, iLen, "尚未触发", _TRUNCATE);
            break;
        }
        ///已触发
    case THOST_FTDC_OST_Touched:
        {
            strncpy_s(pszStatus, iLen, "已触发", _TRUNCATE);
            break;
        }
    default:
        {
            strncpy_s(pszStatus, iLen, "未知", _TRUNCATE);
            break;
        }
    }
}
void CUserTraderSpi::GetOrderSubmitStatus(char cSubmitStatus, char *pszStatus, int iLen)
{
    if ((pszStatus == NULL) || (iLen <= 0))
    {
        return;
    }

    switch(cSubmitStatus)
    {
        ///已经提交
    case THOST_FTDC_OSS_InsertSubmitted :
        {
            strncpy_s(pszStatus,iLen, "已经提交", _TRUNCATE);
            break;
        }
        ///撤单已经提交
    case THOST_FTDC_OSS_CancelSubmitted :
        {
            strncpy_s(pszStatus,iLen, "撤单已经成交", _TRUNCATE);
            break;
        }
        ///修改已经提交
    case THOST_FTDC_OSS_ModifySubmitted :
        {
            strncpy_s(pszStatus,iLen, "修改已经提交", _TRUNCATE);
            break;
        }
        ///已经接受
    case THOST_FTDC_OSS_Accepted :
        {
            strncpy_s(pszStatus,iLen, "已经接受", _TRUNCATE);
            break;
        }
        ///报单已经被拒绝
    case THOST_FTDC_OSS_InsertRejected :
        {
            strncpy_s(pszStatus,iLen, "报单已经被拒绝", _TRUNCATE);
            break;
        }
        ///撤单已经被拒绝
    case THOST_FTDC_OSS_CancelRejected :
        {
            strncpy_s(pszStatus,iLen, "撤单已经被拒绝", _TRUNCATE);
            break;
        }
        ///改单已经被拒绝
    case THOST_FTDC_OSS_ModifyRejected :
        {
            strncpy_s(pszStatus,iLen, "改单已经被拒绝", _TRUNCATE);
            break;
        }
    }
}

