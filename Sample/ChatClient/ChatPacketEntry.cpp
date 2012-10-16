#include "StdAfx.h"
#include "ChatPacketEntry.h"
#include "PacketID.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "ChatPacket.pb.h"
#include "SFSinglton.h"
#include <iostream>
#include "SFEngine.h"
#include "GoogleLog.h"

extern SFSYSTEM* g_pEngine;

using namespace google;

ChatPacketEntry::ChatPacketEntry(void)
{
}

ChatPacketEntry::~ChatPacketEntry(void)
{
}

BOOL ChatPacketEntry::Send(USHORT PacketID, char* pBuffer, int BufSize )
{

	g_pEngine->Send(GetSerial(), PacketID, pBuffer, BufSize);

	return TRUE;
}

BOOL ChatPacketEntry::Send(int Serial, USHORT PacketID, char* pBuffer, int BufSize )
{
	g_pEngine->Send(Serial, PacketID, pBuffer, BufSize);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
//ä�� ���� ������ ���� TCP ó�� ������� ���� �����尡 ������ ������ ���� ������
//���������� ó���� �ϰ� �ֽ��ϴ�.
//TCP ó�� �����忡�� ���� ��Ŷ�� ���� ������� �ѱ� ���
//lock free queue�� ����ϸ� �˴ϴ�.(UDP �����忡�� ���� ������� ��Ŷ �ѱ�� �κ� ����)

BOOL ChatPacketEntry::ProcessPacket( SFCommand* pCommand )
{
	SFPacket* pPacket = (SFPacket*)(pCommand);
	if(pPacket->GetPacketID() == CGSF::ChatReq)
	{
		ChatPacket::Chat PktChat;
		protobuf::io::ArrayInputStream is(pPacket->GetDataBuffer(), pPacket->GetDataSize());
		PktChat.ParseFromZeroCopyStream(&is);

		std::cout << PktChat.chatmessage() << std::endl;

		return TRUE;
	}
	else if(pCommand->GetPacketType() == SFCommand_Disconnect)
	{
		g_pEngine->SetProcessing(FALSE);
		printf("Disconnect Server!!\n");
	}
	else if(pCommand->GetPacketType() == SFCommand_Connect)
	{
		g_pEngine->SetProcessing(TRUE);
		printf("Connect Server!!\n");

		m_Serial = pCommand->GetOwnerSerial();
	}

	return FALSE;

}