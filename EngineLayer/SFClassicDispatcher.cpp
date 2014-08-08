#include "stdafx.h"
#include "SFClassicDispatcher.h"
#include "SFEngine.h"
#include "SFDatabase.h"

SFClassicDispatcher::SFClassicDispatcher()
{
}

SFClassicDispatcher::~SFClassicDispatcher()
{
}

void SFClassicDispatcher::Dispatch(BasePacket* pPacket)
{
	LogicEntrySingleton::instance()->ProcessPacket(pPacket);
	ReleasePacket(pPacket);
}

bool SFClassicDispatcher::CreateLogicSystem(ILogicEntry* pLogicEntry)
{
	LogicEntrySingleton::instance()->SetLogic(pLogicEntry);
	return true;
}

bool SFClassicDispatcher::ShutDownLogicSystem()
{
	return true;
}

bool SFClassicDispatcher::ReleasePacket(BasePacket* pPacket)
{
	//����� ��Ŷ�� �����Ѵ�. ��Ŷ�� Ÿ�Կ� ���� ������ ���°� �ٸ�
	switch (pPacket->GetPacketType())
	{
	case SFPACKET_DATA:
		SFEngine::GetInstance()->ReleasePacket(pPacket);
		break;
	case SFPACKET_CONNECT:
	case SFPACKET_DISCONNECT:
	case SFPACKET_TIMER:
	case SFPACKET_SHOUTER:
	case SFPACKET_SERVERSHUTDOWN:
		delete pPacket;
		break;

	case SFPACKET_DB:
		SFDatabase::RecallDBMsg((SFMessage*)pPacket);
		break;

	default:
		SFASSERT(0);
		return false;
	}

	return true;
}