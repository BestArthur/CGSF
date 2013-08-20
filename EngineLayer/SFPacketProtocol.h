#pragma once
#include "IPacketProtocol.h"
#include "SFChecksum.h"
#include "SFPacketIOBuffer.h"
#include "SFEncryption.h"
#include "SFEncryptionXOR.h"

#include "Macro.h"

class BasePacket;

void SendDummy(BasePacket* pPacket);

template <typename T>
class SFPacketProtocol : public IPacketProtocol
{
public:
	SFPacketProtocol(){}
	virtual ~SFPacketProtocol(void){}

	BOOL OnReceive(int Serial, char* pBuffer, DWORD dwTransferred) override;
	BOOL SendRequest(ISession* pSession, BasePacket* pPacket) override;

	virtual IPacketProtocol* Clone(){return new SFPacketProtocol<T>();}

	void SendPacketLogicLayer(BasePacket* pPacket);

private:
	T m_Analyzer;
};

template <typename T>
BOOL SFPacketProtocol<T>::OnReceive(int Serial, char* pBuffer, DWORD dwTransferred)
{
	BOOL bRet = m_Analyzer.AddTransferredData(pBuffer, dwTransferred);

	if(FALSE == bRet)
	{
		SFASSERT(0);
		return FALSE;
	}

	int iErrorCode = PACKETIO_ERROR_NONE;
	
	do
	{
		BasePacket* pPacket = m_Analyzer.GetPacket(iErrorCode);
		
		if(NULL == pPacket)
			break;

		pPacket->SetPacketType(SFPacket_Data);
		pPacket->SetOwnerSerial(Serial);

		SendPacketLogicLayer(pPacket);
	}
	while(TRUE);
	
	if(iErrorCode != PACKETIO_ERROR_NONE)
	{
		return false;
	}

	return TRUE;
}

template <typename T>
BOOL SFPacketProtocol<T>::SendRequest(ISession* pSession, BasePacket* pPacket)
{
	BOOL bRet = m_Analyzer.SendRequest(pSession, pPacket);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//������ ������ �𸣰�����....
//ĳ��� ���� ������ �ϼ��ϰ� �� �� MMO ������ �����Ѵٸ�
//�� �κ��� ������ ���̴�...
//20121121 -> ???????
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SFPacketProtocol<T>::SendPacketLogicLayer(BasePacket* pPacket)
{
	SendDummy(pPacket);
}