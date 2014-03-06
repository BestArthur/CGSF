#include "StdAfx.h"
#include "ChatPacketEntry.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <SFPacketStore/PacketID.h>
#include <SFPacketStore/ChatPacket.pb.h>
#include "SFSinglton.h"
#include <iostream>
#include "SFEngine.h"
#include "SFProtobufPacket.h"

//extern SFEngine* g_pEngine;

using namespace google;

ChatPacketEntry::ChatPacketEntry(void)
{
}

ChatPacketEntry::~ChatPacketEntry(void)
{
}

BOOL ChatPacketEntry::SendRequest(BasePacket* pPacket)
{
	//g_pEngine->SendRequest(pPacket);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
//ä�� ���� ������ ���� TCP ó�� ������� ���� �����尡 ������ ������ ���� ������
//���������� ó���� �ϰ� �ֽ��ϴ�.
//TCP ó�� �����忡�� ���� ��Ŷ�� ���� ������� �ѱ� ���
//lock free queue�� ����ϸ� �˴ϴ�.(UDP �����忡�� ���� ������� ��Ŷ �ѱ�� �κ� ����)

BOOL ChatPacketEntry::ProcessPacket( BasePacket* pPacket)
{
	if(pPacket->GetPacketID() == CGSF::ChatRes)
	{
		SFProtobufPacket<ChatPacket::Chat>* pChat = (SFProtobufPacket<ChatPacket::Chat>*)pPacket;

		std::cout << pChat->GetData().chatmessage() << std::endl;

		return TRUE;
	}
	else if (pPacket->GetPacketType() == SFPACKET_DISCONNECT)
	{
//		g_pEngine->SetProcessing(FALSE);
		printf("Disconnect Server!!\n");
	}
	else if (pPacket->GetPacketType() == SFPACKET_CONNECT)
	{
		//g_pEngine->SetProcessing(TRUE);
		printf("Connect Server!!\n");

		m_Serial = pPacket->GetOwnerSerial();
	}

	return FALSE;

}