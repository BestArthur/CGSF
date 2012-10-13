#include "stdafx.h"
#include "SFSendDBRequest.h"
#include "SFPlayer.h"
#include "DBMsg.h"

///////////////////////////////////////////////////////////////////////////////////////
//Internal Function
///////////////////////////////////////////////////////////////////////////////////////
SFMessage* SFSendDBRequest::GetInitMessage(int RequestMsg, DWORD PlayerSerial)
{
	SFMessage* pMessage = LogicEntrySingleton::instance()->GetDBMessage();

	SFASSERT(pMessage != NULL);
	pMessage->Initialize(RequestMsg);
	pMessage->SetOwnerSerial(PlayerSerial);
	pMessage->SetPacketType(SFCommand_DB);

	return pMessage;
}

BOOL SFSendDBRequest::Send(SFMessage* pMessage)
{
	return SFLogicEntry::GetLogicEntry()->GetDataBaseProxy()->SendDBRequest(pMessage);
}

///////////////////////////////////////////////////////////////////////////////////////
//Default DB Request
///////////////////////////////////////////////////////////////////////////////////////
BOOL SFSendDBRequest::SendRequest(int RequestMsg, DWORD PlayerSerial, SFPacket* pPacket)
{
	SFMessage* pMessage = GetInitMessage(RequestMsg, PlayerSerial);
	pMessage->Write(pPacket->GetDataBuffer(), pPacket->GetDataSize());
	SFLogicEntry::GetLogicEntry()->GetDataBaseProxy()->SendDBRequest(pMessage);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//���������� ������Ʈ�� �ۼ��ؾ� �� ��
//////////////////////////////////////////////////////////////////////////////////////////////
BOOL SFSendDBRequest::RequestLogin(SFPlayer* pPlayer, SFPacket* pPacket)
{
	SFMessage* pMessage = GetInitMessage(DBMSG_LOGIN, pPlayer->GetSerial());
	pMessage->Write(pPacket->GetDataBuffer(), pPacket->GetDataSize());

	return Send(pMessage);
}