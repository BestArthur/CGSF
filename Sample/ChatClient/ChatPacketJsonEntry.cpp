#include "StdAfx.h"
#include "ChatPacketJsonEntry.h"
#include <SFPacketStore/PacketID.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <SFPacketStore/ChatPacket.pb.h>
#include "SFSinglton.h"
#include <iostream>
#include "SFEngine.h"
#include "SFJsonPacket.h"

//extern SFEngine* g_pEngine;


ChatPacketJsonEntry::ChatPacketJsonEntry(void)
{
}

ChatPacketJsonEntry::~ChatPacketJsonEntry(void)
{
}

BOOL ChatPacketJsonEntry::SendRequest(BasePacket* pPacket)
{
	//g_pEngine->SendRequest(pPacket);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
//ä�� ���� ������ ���� TCP ó�� ������� ���� �����尡 ������ ������ ���� ������
//���������� ó���� �ϰ� �ֽ��ϴ�.
//TCP ó�� �����忡�� ���� ��Ŷ�� ���� ������� �ѱ� ���
//lock free queue�� ����ϸ� �˴ϴ�.(UDP �����忡�� ���� ������� ��Ŷ �ѱ�� �κ� ����)

BOOL ChatPacketJsonEntry::ProcessPacket( BasePacket* pPacket)
{
	switch (pPacket->GetPacketType())
	{
	case SFPACKET_CONNECT:
		{	
			OnConnectPlayer(pPacket->GetOwnerSerial());
		}
		break;

	case SFPACKET_DATA:
		{	
			OnPlayerData(pPacket);
		}
		break;

	case SFPACKET_DISCONNECT:
		{	
			OnDisconnectPlayer(pPacket->GetOwnerSerial());
		}
		break;

	case SFPACKET_TIMER:
		{	
			//OnTimer(pCommand->GetOwnerSerial());
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

BOOL ChatPacketJsonEntry::OnConnectPlayer( int Serial )
{
	printf("Connect Server!!\n");
	m_Serial = Serial;
	return TRUE;
}

BOOL ChatPacketJsonEntry::OnDisconnectPlayer( int Serial )
{
	printf("Disconnect Server!!\n");

	return TRUE;
}

BOOL ChatPacketJsonEntry::OnPlayerData( BasePacket* pPacket )
{
	SFJsonPacket* pJsonPacket = (SFJsonPacket*)pPacket;
	int PacketID = pJsonPacket->GetData().GetValue<int>("PacketId");

	if(PacketID == 1234)
	{
		std::cout << pJsonPacket->GetData().GetValue<tstring>("chat") << std::endl;

		return TRUE;
	}

	return FALSE;
}