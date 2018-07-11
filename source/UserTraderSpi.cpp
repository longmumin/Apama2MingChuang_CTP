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

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void CUserTraderSpi:: OnFrontConnected()
{
    //����
    //SetEvent(m_hEvent);

    sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"�첽����ǰ�û�ע����� SPi OnFrontConnected", "�첽���سɹ�");

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);

}
    
///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
void CUserTraderSpi:: OnFrontDisconnected(int nReason)
{
    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s", GetCurTimeByChar(), "����ǰ�û��ж� SPi OnFrontDisconnected");

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}
        
///��¼������Ӧ
void CUserTraderSpi:: OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if ((pRspUserLogin == NULL) || (pRspInfo->ErrorID < 0))
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"�첽���ص�½ʧ�� SPi OnRspUserLogin", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,%s", GetCurTimeByChar(),"�첽���ص�½��� SPi OnRspUserLogin", "�첽���سɹ�");
    }

    //SetEvent(m_hEvent);

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�ǳ�������Ӧ
void CUserTraderSpi:: OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

}

///����¼��������Ӧ
void CUserTraderSpi:: OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pInputOrder != NULL) ? pInputOrder->OrderRef : "");

    if ((pInputOrder == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ������%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "�µ�����,", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,������%s,%s", GetCurTimeByChar(),"�첽�����µ���� SPi OnRspOrderInsert", pInputOrder->OrderRef,"�첽���سɹ�");

    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///��������������Ӧ
void CUserTraderSpi:: OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pInputOrderAction != NULL) ? pInputOrderAction->OrderRef : "");

    if ((pInputOrderAction == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ������%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "��������,", pRspInfo->ErrorMsg);
    }
    else
    {
        sprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), "%s: %s,������%s,%s", GetCurTimeByChar(),"�첽���س������ SPi OnRspOrderInsert",pInputOrderAction->OrderRef, "�첽���سɹ�");
    }

    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}



///�����ѯ������Ӧ
void CUserTraderSpi:: OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pOrder != NULL) ? pOrder->OrderRef : "");

    if ((pOrder == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���� ������%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "��ѯ����ʧ��,", pRspInfo->ErrorMsg);
    }
    else
    {
        char szOrderStatus[30] = { 0 };
        char szOrderSubmitStatus[30] = { 0 };
        GetOrderStatus(pOrder->OrderStatus, szOrderStatus, sizeof(szOrderStatus));
        GetOrderSubmitStatus(pOrder->OrderSubmitStatus, szOrderSubmitStatus, sizeof(szOrderSubmitStatus));
        //_snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���� ������%s %s ί��״̬:%c", GetCurTimeByChar(),pOrder->OrderRef, "��ѯ�����ɹ�", pOrder->OrderStatus);
        _snprintf_s(m_szErrMsg, sizeof(m_szErrMsg), _TRUNCATE, "%s: ��ѯ���� ������->%s, ����״̬->%s, �ύ״̬->%s, ί������->%d,ʣ������->%d", GetCurTimeByChar(), pOrder->OrderRef,
            szOrderStatus, szOrderSubmitStatus, pOrder->VolumeTotalOriginal, pOrder->VolumeTotal);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯ�ɽ���Ӧ
void CUserTraderSpi:: OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strOrderRef = ((pTrade != NULL) ? pTrade->OrderRef : "");

    if ((pTrade == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ�ɽ� ������%s %s%s", GetCurTimeByChar(), strOrderRef.c_str(), "��ѯ�ɽ�ʧ��,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ�ɽ� ������%s %s", GetCurTimeByChar(),pTrade->OrderRef, "��ѯ�ɽ��ɹ�");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯͶ���ֲ߳���Ӧ
void CUserTraderSpi:: OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strInvestorID = ((pInvestorPosition != NULL) ? pInvestorPosition->InvestorID : "");

    if ((pInvestorPosition == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯͶ���ֲ߳� Ͷ����%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "��ѯͶ���ֲ߳�ʧ��,",pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯͶ���ֲ߳� Ͷ����%s %s", GetCurTimeByChar(), pInvestorPosition->InvestorID, "��ѯͶ���ֲֳ߳ɹ�");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯ�ʽ��˻���Ӧ
void CUserTraderSpi:: OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    std::string strInvestorID = ((pTradingAccount != NULL) ? pTradingAccount->AccountID : "");

    if ((pTradingAccount == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ�ʽ��˺� �˺�%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "��ѯ�ʽ��˺�ʧ��,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ�ʽ��˺� �˺�%s %s", GetCurTimeByChar(),pTradingAccount->AccountID, "��ѯ�ʽ��˺ųɹ�");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}


void CUserTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInvestorID = ((pInvestor != NULL) ? pInvestor->InvestorID : "");

    if ((pInvestor == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯBrokerID �˺�%s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "��ѯ�ʽ��˺�ʧ��,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯInvestorID �˺�%s %s", GetCurTimeByChar(),pInvestor->InvestorID, "��ѯ�ʽ��˺ųɹ�");
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}



///Ͷ���߽�����ȷ����Ӧ
void CUserTraderSpi:: OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if (NULL == pSettlementInfoConfirm)
    {
         _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽����%s, %s", GetCurTimeByChar(), "Ͷ���߽�����ȷ��ʧ��,", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽����%s, %s", GetCurTimeByChar(), pSettlementInfoConfirm->BrokerID, "Ͷ���߽�����ȷ�ϳɹ�");

    }
    //SetEvent(m_hEvent);
    //g_pclDlg->ShowSpiMsg(m_szErrMsg);
    return;
}

///�����ѯͶ���߽�������Ӧ
void CUserTraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (NULL == pSettlementInfoConfirm)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s, %s", GetCurTimeByChar(), "�첽���������ѯͶ���߽�������Ӧʧ��,", pRspInfo->ErrorMsg);    
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: %s, %s", GetCurTimeByChar(), pSettlementInfoConfirm->BrokerID, "�첽���������ѯͶ���߽�������Ӧ�ɹ�");
    }

    //SetEvent(m_hEvent);

    m_bIsSettlement = true;

    //g_pclDlg->ShowSpiMsg(m_szErrMsg);

    return;
}

///�����ѯ�����������Ӧ
void CUserTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strExchangeID = ((pExchange != NULL) ? pExchange->ExchangeID : "");

    if ((pExchange == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ������ %s %s%s", GetCurTimeByChar(), strExchangeID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ�������ɹ�: ExchangeID= %s, ExchangeName = %s, ExchangeProperty = %c", GetCurTimeByChar(), pExchange->ExchangeID, pExchange->ExchangeName, pExchange->ExchangeProperty);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯ��Լ�����Ӧ
void CUserTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrument != NULL) ? pInstrument->InstrumentID : "");

    if ((pInstrument == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ��Լ %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: ��ѯ��Լ�ɹ�: InstrumentID = %s|ExchangeID = %s|InstrumentName = %s|ExchangeInstID = %s|ProductID = %s|ProductClass = %c| DeliveryYear = %d|DeliveryMonth = %d|MaxMarketOrderVolume = %d|MinMarketOrderVolume = %d", 
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

///�����ѯ��Լ��֤������Ӧ
void CUserTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrumentMarginRate != NULL) ? pInstrumentMarginRate->InstrumentID : "");

    if ((pInstrumentMarginRate == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ��Լ��֤���� %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: ��ѯ��Լ��֤���ʳɹ�: InstrumentID = %s|InvestorRange = %c|BrokerID = %s|InvestorID = %s|HedgeFlag = %c", 
                    GetCurTimeByChar(), 
                    pInstrumentMarginRate->InstrumentID, 
                    pInstrumentMarginRate->InvestorRange,
                    pInstrumentMarginRate->BrokerID, 
                    pInstrumentMarginRate->InvestorID, 
                    pInstrumentMarginRate->HedgeFlag);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯ��Լ����������Ӧ
void CUserTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInstrumentID = ((pInstrumentCommissionRate != NULL) ? pInstrumentCommissionRate->InstrumentID : "");

    if ((pInstrumentCommissionRate == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ��Լ�������� %s %s%s", GetCurTimeByChar(), strInstrumentID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: ��ѯ��Լ�������ʳɹ�: InstrumentID = %s|InvestorRange = %c|BrokerID = %s|InvestorID = %s|OpenRatioByMoney = %f|OpenRatioByVolume = %f|CloseRatioByMoney = %f|CloseRatioByVolume = %f|CloseTodayRatioByMoney = %f|CloseTodayRatioByVolume = %f", 
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

///�����ѯ���͹�˾���ײ���
void CUserTraderSpi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strInvestorID = ((pBrokerTradingParams != NULL) ? pBrokerTradingParams->InvestorID : "");

    if ((pBrokerTradingParams == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���͹�˾���ײ��� %s %s%s", GetCurTimeByChar(), strInvestorID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���͹�˾���ײ����ɹ�: InvestorID = %s, MarginPriceType = %c", GetCurTimeByChar(), pBrokerTradingParams->InvestorID, pBrokerTradingParams->MarginPriceType);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///�����ѯ���͹�˾�����㷨
void CUserTraderSpi::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strExchangeID = ((pBrokerTradingAlgos != NULL) ? pBrokerTradingAlgos->ExchangeID : "");

    if ((pBrokerTradingAlgos == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���͹�˾�����㷨 %s %s%s", GetCurTimeByChar(), strExchangeID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ���͹�˾�����㷨�ɹ�: ExchangeID = %s, InstrumentID = %s", GetCurTimeByChar(), pBrokerTradingAlgos->ExchangeID, pBrokerTradingAlgos->InstrumentID);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
void CUserTraderSpi::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::string strBrokerID = ((pCFMMCTradingAccountKey != NULL) ? pCFMMCTradingAccountKey->BrokerID : "");

    if ((pCFMMCTradingAccountKey == NULL) || (pRspInfo->ErrorID < 0))
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: ��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ %s %s%s", GetCurTimeByChar(), strBrokerID.c_str(), "ʧ��, ������Ϣ:", pRspInfo->ErrorMsg);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, 
                    "%s: ��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ�ɹ�: BrokerID = %s, ParticipantID = %s, AccountID = %s, KeyID = %d, CurrentKey = %s", 
                    GetCurTimeByChar(), 
                    pCFMMCTradingAccountKey->BrokerID, 
                    pCFMMCTradingAccountKey->ParticipantID,
                    pCFMMCTradingAccountKey->AccountID, 
                    pCFMMCTradingAccountKey->KeyID, 
                    pCFMMCTradingAccountKey->CurrentKey);
    }
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///����Ӧ��
void CUserTraderSpi:: OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
    if (pRspInfo == NULL)
    {
        return;
    }

    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s������Ϣ%s", GetCurTimeByChar(), pRspInfo->ErrorMsg);
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�ȡ�õ�ǰʱ��
//���룺��
//������ַ�����ʽ��ʱ��(�зָ���) HH:MM:SS
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
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽���� ������->%s, ����״̬->%s, �ύ״̬->%s, ί������->%d", GetCurTimeByChar(), pOrder->OrderRef,
            szOrderStatus, szOrderSubmitStatus, pOrder->VolumeTotal);
    }
    else
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽���� ������->%s, ����״̬->%s, �ύ״̬->%s, ί������->%d, ��Ϣ->%s", GetCurTimeByChar(), pOrder->OrderRef,
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

    _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽���� ������->%s, �ɽ�״̬->%s, �ɽ�����->%d, �ɽ��۸�->%f", 
                                                  GetCurTimeByChar(),pTrade->OrderRef,
                                                  "�ڻ������ѳɽ�",pTrade->Volume,
                                                  pTrade->Price);
    //g_pclDlg->ShowListboxMsg(m_szErrMsg);
}

///����¼�����ر�
void CUserTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    if ((pInputOrder == NULL) || (pRspInfo == NULL))
    {
        return;
    }

    if (pRspInfo->ErrorID<0)
    {
        _snprintf_s(m_szErrMsg, sizeof(MCQTTD_ERRMSG), _TRUNCATE, "%s: �첽���� ������->%s, ������Ϣ->%s, ��ϸ��Ϣ->%s", 
                                                    GetCurTimeByChar(),pInputOrder->OrderRef,
                                                    "��Ч���ڻ�����",pRspInfo->ErrorMsg);
        //g_pclDlg->ShowListboxMsg(m_szErrMsg);
    }
}

///������������ر�
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
        ///ȫ���ɽ�
    case THOST_FTDC_OST_AllTraded:
        {
            strncpy_s(pszStatus, iLen,"ȫ���ɽ�", _TRUNCATE);
            break;
        }
        ///���ֳɽ����ڶ�����
    case THOST_FTDC_OST_PartTradedQueueing:
        {
            strncpy_s(pszStatus, iLen, "���ֳɽ����ڶ�����", _TRUNCATE);
            break;
        }
        ///���ֳɽ����ڶ�����
    case THOST_FTDC_OST_PartTradedNotQueueing:
        {
            strncpy_s(pszStatus, iLen, "���ֳɽ����ڶ�����", _TRUNCATE);
            break;
        }
        ///δ�ɽ����ڶ�����
    case THOST_FTDC_OST_NoTradeQueueing:
        {
            strncpy_s(pszStatus, iLen, "δ�ɽ����ڶ�����", _TRUNCATE);
            break;
        }
        ///δ�ɽ����ڶ�����
    case THOST_FTDC_OST_NoTradeNotQueueing:
        {
            strncpy_s(pszStatus, iLen, "δ�ɽ����ڶ�����", _TRUNCATE);
            break;
        }
        ///����
    case THOST_FTDC_OST_Canceled:
        {
            strncpy_s(pszStatus, iLen, "����", _TRUNCATE);
            break;
        }
        ///δ֪
    case THOST_FTDC_OST_Unknown:
        {
            strncpy_s(pszStatus, iLen, "δ֪", _TRUNCATE);
            break;
        }
        ///��δ����
    case THOST_FTDC_OST_NotTouched:
        {
            strncpy_s(pszStatus, iLen, "��δ����", _TRUNCATE);
            break;
        }
        ///�Ѵ���
    case THOST_FTDC_OST_Touched:
        {
            strncpy_s(pszStatus, iLen, "�Ѵ���", _TRUNCATE);
            break;
        }
    default:
        {
            strncpy_s(pszStatus, iLen, "δ֪", _TRUNCATE);
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
        ///�Ѿ��ύ
    case THOST_FTDC_OSS_InsertSubmitted :
        {
            strncpy_s(pszStatus,iLen, "�Ѿ��ύ", _TRUNCATE);
            break;
        }
        ///�����Ѿ��ύ
    case THOST_FTDC_OSS_CancelSubmitted :
        {
            strncpy_s(pszStatus,iLen, "�����Ѿ��ɽ�", _TRUNCATE);
            break;
        }
        ///�޸��Ѿ��ύ
    case THOST_FTDC_OSS_ModifySubmitted :
        {
            strncpy_s(pszStatus,iLen, "�޸��Ѿ��ύ", _TRUNCATE);
            break;
        }
        ///�Ѿ�����
    case THOST_FTDC_OSS_Accepted :
        {
            strncpy_s(pszStatus,iLen, "�Ѿ�����", _TRUNCATE);
            break;
        }
        ///�����Ѿ����ܾ�
    case THOST_FTDC_OSS_InsertRejected :
        {
            strncpy_s(pszStatus,iLen, "�����Ѿ����ܾ�", _TRUNCATE);
            break;
        }
        ///�����Ѿ����ܾ�
    case THOST_FTDC_OSS_CancelRejected :
        {
            strncpy_s(pszStatus,iLen, "�����Ѿ����ܾ�", _TRUNCATE);
            break;
        }
        ///�ĵ��Ѿ����ܾ�
    case THOST_FTDC_OSS_ModifyRejected :
        {
            strncpy_s(pszStatus,iLen, "�ĵ��Ѿ����ܾ�", _TRUNCATE);
            break;
        }
    }
}

