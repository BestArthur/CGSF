#pragma once
// ============================================================================
// SFPacketProtocol Ŭ����
// author : pdpdds
// desc : ������ ������ ��Ʈ��ũ �����͸� �����ϰ� ��Ŷ�� ���� �� ó��, �׸��� �������� ��Ŷ�� �����ϴ� ������ ����ϴ� ���ø� Ŭ�����Դϴ�.
// ���� �������� ó���� ���ø����� ������ Ŭ������ ����մϴ�.
// ============================================================================

#include <EngineInterface/IPacketProtocol.h>
#include "SFConstant.h"
#include "SFChecksum.h"
#include "SFPacketIOBuffer.h"
#include "SFEncryption.h"
#include "SFEncryptionXOR.h"
#include "SFBaseProtocol.h"

#include "Macro.h"

class BasePacket;

void SendLogicLayer(BasePacket* pPacket);

template <typename T>
class SFPacketProtocol : public IPacketProtocol, public SFBaseProtocol 
{
public:
	SFPacketProtocol();
	SFPacketProtocol(INT bufferIOSize, USHORT packetDataSize);
	virtual ~SFPacketProtocol(void) {}

	// ----------------------------------------------------------------
	//  Name:           OnReceive
	//  Description:    ������ ������ �����͸� ó���Ѵ�. 	
	// ----------------------------------------------------------------
	bool OnReceive(INT serial, char* pBuffer, UINT dwTransferred, INT acceptorId) override;
	
	// ----------------------------------------------------------------
	//  Name:           SendRequest
	//  Description:    Ÿ�ٿ��� ��Ŷ�� �����Ѵ�.
	// ----------------------------------------------------------------
	virtual bool SendRequest(BasePacket* pPacket) override;	

	// ----------------------------------------------------------------
	//  Name:           DisposePacket
	//  Description:    ���� ������ ��Ŷ�� �����Ѵ�.
	// ----------------------------------------------------------------
	virtual bool DisposePacket(BasePacket* pPacket) override;

	// ----------------------------------------------------------------
	//  Name:           Clone
	//  Description:    ��Ŷ�������� Ŭ���� ��ü�� �����Ѵ�.
	// ----------------------------------------------------------------
	virtual IPacketProtocol* Clone() { return new SFPacketProtocol<T>(); }
	
	//virtual BasePacket* CreatePacket() override;

private:

	// ----------------------------------------------------------------
	//  Name:           ���ø� Ŭ����
	//  Description:    ���� ��Ŷ ���������� ó���ϴ� Ŭ����
	//					AddTransferredData, DisposePacket, SendRequest GetPacket �޼ҵ带 �ݵ�� �����ؾ� �ȴ�.
	//					GetPacketData �޼ҵ�� �� �޼ҵ�� ����� �ε��� �Ѵ�.
	// ----------------------------------------------------------------
	T m_Analyzer;	
};

template <typename T>
SFPacketProtocol<T>::SFPacketProtocol()
{
	m_Analyzer.Initialize(m_ioSize, m_packetSize);
}

template <typename T>
SFPacketProtocol<T>::SFPacketProtocol(INT bufferIOSize, USHORT packetDataSize)
{
	if (bufferIOSize > MAX_IO_SIZE)
		bufferIOSize = MAX_IO_SIZE;

	if (packetDataSize > MAX_PACKET_SIZE)
		packetDataSize = MAX_PACKET_SIZE;

	if (packetDataSize > bufferIOSize)
		packetDataSize = bufferIOSize;

	m_ioSize = bufferIOSize;
	m_packetSize = packetDataSize;

	m_Analyzer.Initialize(m_ioSize, m_packetSize);
}

template <typename T>
bool SFPacketProtocol<T>::DisposePacket(BasePacket* pPacket)
{
	return m_Analyzer.DisposePacket(pPacket);
}

template <typename T>
bool SFPacketProtocol<T>::SendRequest(BasePacket* pPacket)
{
	return m_Analyzer.SendRequest(pPacket);
}

template <typename T>
bool SFPacketProtocol<T>::OnReceive(INT serial, char* pBuffer, UINT dwTransferred, INT acceptorId)
{
	auto bRet = m_Analyzer.AddTransferredData(pBuffer, dwTransferred);

	if(false == bRet)
	{
		SFASSERT(0);
		return false;
	}

	auto iErrorCode = PACKETIO_ERROR_NONE;
	
	do
	{
		BasePacket* pPacket = m_Analyzer.GetPacket(iErrorCode);
		
		if(NULL == pPacket)
			break;

		if (SFPACKET_RPC_PACKET == pPacket->GetPacketID())
			pPacket->SetPacketType(SFPACKET_RPC);
		else
			pPacket->SetPacketType(SFPACKET_DATA);

		pPacket->SetSerial(serial);	
		pPacket->SetAcceptorId(acceptorId);
		
		SendLogicLayer(pPacket);
	}
	while(true);
	
	if(iErrorCode != PACKETIO_ERROR_NONE)
	{
		return false;
	}

	return true;
}

/*
template <typename T>
BasePacket* SFPacketProtocol<T>::CreatePacket()
{
return m_Analyzer.CreatePacket();
}*/