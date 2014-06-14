#include "stdafx.h"
#include "SFCasualGameDispatcher.h"
#include "SFEngine.h"
#include "SFDatabase.h"
#include "IRPCService.h"
#include "SFPacket.h"
#include "SFEngine.h"

bool SFCasualGameDispatcher::m_bLogicEnd = false;

//���� ������ ���� �޼ҵ� ���� �� ������������ ���� ����
SFCasualGameDispatcher::SFCasualGameDispatcher(void)
: m_LogicThreadGroupId(-1)
{
	m_nLogicThreadCnt = 1;
	m_funcLogicThread = (void*)SFCasualGameDispatcher::LogicThread;
	m_funcRPCThread = (void*)SFCasualGameDispatcher::RPCThread;
}

SFCasualGameDispatcher::~SFCasualGameDispatcher(void)
{
}

//��������Ʈ���� ť�� ��Ŷ�� ť���Ѵ�.
void SFCasualGameDispatcher::Dispatch(BasePacket* pPacket)
{
	if (pPacket->GetPacketType() == SFPACKET_RPC && SFEngine::GetInstance()->IsServer())
	{
		RPCGatewaySingleton::instance()->PushPacket(pPacket);
	}
	else
	{
		LogicGatewaySingleton::instance()->PushPacket(pPacket);
	}
}

void SFCasualGameDispatcher::LogicThread(void* Args)
{
	SFEngine* pEngine = (SFEngine*)Args;
	while (m_bLogicEnd == false)
	{
//��������Ʈ���� ť���� ��Ŷ�� ������.
		BasePacket* pPacket = LogicGatewaySingleton::instance()->PopPacket();
//������Ʈ�� ��ü�� ProcessPacket �޼ҵ带 ȣ���ؼ� ��Ŷ ó���� �����Ѵ�.
		LogicEntrySingleton::instance()->ProcessPacket(pPacket);

//����� ��Ŷ�� �����Ѵ�. ��Ŷ�� Ÿ�Կ� ���� ������ ���°� �ٸ�
		switch (pPacket->GetPacketType())
		{
		case SFPACKET_DATA:
			pEngine->ReleasePacket(pPacket);
			break;
		case SFPACKET_CONNECT:
		case SFPACKET_DISCONNECT:
		case SFPACKET_TIMER:
		case SFPACKET_SHOUTER:
			delete pPacket;
			break;

		case SFPACKET_DB:
			SFDatabase::RecallDBMsg((SFMessage*)pPacket);
			break;

		case SFPACKET_SERVERSHUTDOWN:
			return;

		default:
			SFASSERT(0);
		}
	}
}

void SFCasualGameDispatcher::RPCThread(void* Args)
{
	SFCasualGameDispatcher* pDisPatcher = (SFCasualGameDispatcher*)Args;
	while (m_bLogicEnd == false)
	{
		//��������Ʈ���� ť���� ��Ŷ�� ������.
		//BasePacket* pPacket = RPCGatewaySingleton::instance()->PopPacket();

//20140608 �ӽ�..
		SFPacket* pPacket = (SFPacket*)RPCGatewaySingleton::instance()->PopPacket();
	
		pDisPatcher->m_pRPCService->ProcessRPCService(pPacket);

		delete pPacket;
	}
}

bool SFCasualGameDispatcher::CreateLogicSystem(ILogicEntry* pLogicEntry)
{	
	m_LogicThreadGroupId = ACE_Thread_Manager::instance()->spawn_n(GetLogicThreadCount(), (ACE_THR_FUNC)GetLogicThreadFunc(), this, THR_NEW_LWP, ACE_DEFAULT_THREAD_PRIORITY);

	LogicEntrySingleton::instance()->SetLogic(pLogicEntry);

	ACE_Thread_Manager::instance()->spawn_n(4, (ACE_THR_FUNC)GetRPCThreadFunc(), this, THR_NEW_LWP, ACE_DEFAULT_THREAD_PRIORITY);

	return true;
}

bool SFCasualGameDispatcher::ShutDownLogicSystem()
{
	m_bLogicEnd = true;

	BasePacket* pCommand = PacketPoolSingleton::instance()->Alloc();
	pCommand->SetPacketType(SFPACKET_SERVERSHUTDOWN);
	PacketSendSingleton::instance()->PushPacket(pCommand);

	pCommand = PacketPoolSingleton::instance()->Alloc();
	pCommand->SetOwnerSerial(-1);
	pCommand->SetPacketType(SFPACKET_SERVERSHUTDOWN);
	LogicGatewaySingleton::instance()->PushPacket(pCommand);

	ACE_Thread_Manager::instance()->wait_grp(m_LogicThreadGroupId);

	return true;
}

bool SFCasualGameDispatcher::AddRPCService(IRPCService* pService)
{
	m_pRPCService = pService;
	return true;
}

