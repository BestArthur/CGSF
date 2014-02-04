#include "StdAfx.h"
#include "SFLogicEntry.h"
#include "SFPlayer.h"
#include "SFMacro.h"
#include "SFMySQLAdaptorImpl.h"

SFLogicEntry* SFLogicEntry::m_pLogicEntry = NULL;

SFLogicEntry::SFLogicEntry(void)
{
	m_pLogicEntry = this;
}

BOOL SFLogicEntry::Initialize()
{
	SFDatabaseProxy* pProxyLocal = NULL;

	if(_tcscmp(SFDatabase::GetInfo()->szDataSource, _T("hsql")) == 0)
	{
		pProxyLocal = new SFDatabaseProxyLocal<SFMySQLAdaptorImpl>();
	}
	else
	{
		pProxyLocal = new SFDatabaseProxyLocal<SFMySQLAdaptorImpl>();
	}

	m_pDatabaseProxy = new SFDatabaseProxyImpl(pProxyLocal);
	m_pDatabaseProxy->Initialize();

	m_pRoomManager = new SFRoomManager();
	m_pRoomManager->Initialize();

	m_pLobby = new SFLobby();

	m_LogicContents.Load();

	m_pPlayerPool = new SFObjectPool<SFPlayer>(1000);

	CreateDirectoryWathcer();

	return TRUE;
}

BOOL SFLogicEntry::CreateDirectoryWathcer()
{
	m_DirectoryWatcherTask.activate();

	return TRUE;
}

SFLogicEntry::~SFLogicEntry(void)
{
	if(m_pPlayerPool)
		delete m_pPlayerPool;

	if(m_pDatabaseProxy)
		delete m_pDatabaseProxy;

	if(m_pRoomManager)
		delete m_pRoomManager;

	if(m_pLobby)
		delete m_pLobby;
}

BOOL SFLogicEntry::AddGameMode(int Mode, SFGameMode* pMode)
{
	m_GameModeMap.insert(std::make_pair(Mode, pMode));
	return TRUE;
}

BOOL SFLogicEntry::ProcessPacket( BasePacket* pBase )
{
	switch (pBase->GetPacketType())
	{
	case SFPacket_Connect:
		{	
			OnConnectPlayer(pBase->GetOwnerSerial());
		}
		break;

	case SFPacket_Data:
		{	
			OnPlayerData((BasePacket*)pBase);
		}
		break;

	case SFPacket_Timer:
		{	
			OnTimer((BasePacket*)pBase);
		}
		break;

	case SFPacket_Shouter:
		{	
			OnShouter((SFPacket*)pBase);
		}
		break;


	case SFPacket_Disconnect:
		{	
			OnDisconnectPlayer(pBase->GetOwnerSerial());
		}
		break;

	case SFPacket_DB:
		{	
			OnDBResult((SFMessage*)pBase);
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

BOOL SFLogicEntry::OnConnectPlayer( int PlayerSerial )
{
	SFPlayer* pPlayer = m_pPlayerPool->Alloc();

	if(pPlayer == NULL)
		return FALSE;

	pPlayer->Reset();
	pPlayer->SetSerial(PlayerSerial);

	pPlayer->ChangeState(PLAYER_STATE_INIT);

	m_PlayerMap.insert(PlayerMap::value_type(PlayerSerial, pPlayer));

	SendAuthPacket(PlayerSerial);

	return TRUE;
}

BOOL SFLogicEntry::OnDisconnectPlayer( int PlayerSerial )
{
	PlayerMap::iterator iter = m_PlayerMap.find(PlayerSerial);
	
	if(iter == m_PlayerMap.end())
	{
		SFASSERT(0);
		return FALSE;
	}

	SFPlayer* pPlayer = iter->second;

///////////////////////////////////////////////////////////
//20120619 �̷������� ¥�� �Ǽ��� ������ ũ��.... ���߿� ������ �� �ֵ��� �Ѵ�.
///////////////////////////////////////////////////////////
	if (pPlayer->GetPlayerState() == PLAYER_STATE_LOADING ||
		pPlayer->GetPlayerState() == PLAYER_STATE_ROOM ||
		pPlayer->GetPlayerState() == PLAYER_STATE_PLAY ||
		pPlayer->GetPlayerState() == PLAYER_STATE_PLAYEND ||
		pPlayer->GetPlayerState() == PLAYER_STATE_PLAYREADY)
	{
		SFRoomManager* pManager = GetRoomManager();
		SFRoom* pRoom = pManager->GetRoom(pPlayer->GetRoomIndex());
		pRoom->GetRoomFSM()->OnLeaveRoom(pPlayer);
	}

	pPlayer->ChangeState(PLAYER_STATE_NONE);

	m_pPlayerPool->Release(pPlayer);

	m_PlayerMap.erase(iter);

	return TRUE;
}

BOOL SFLogicEntry::OnPlayerData( BasePacket* pPacket )
{
	PlayerMap::iterator iter = m_PlayerMap.find(pPacket->GetOwnerSerial());

	if(iter == m_PlayerMap.end())
	{
		SFASSERT(0);
		return FALSE;
	}

	SFPlayer* pPlayer = iter->second;

	return pPlayer->ProcessPacket(pPacket);
}

BOOL SFLogicEntry::OnDBResult(SFMessage* pMessage)
{
	PlayerMap::iterator iter = m_PlayerMap.find(pMessage->GetOwnerSerial());

	if(iter == m_PlayerMap.end())
	{
		SFASSERT(0);
		return FALSE;
	}

	SFPlayer* pPlayer = iter->second;

	return pPlayer->ProcessDBResult(pMessage);
}

BOOL SFLogicEntry::OnTimer(BasePacket* pPacket)
{
	return TRUE;
}

BOOL SFLogicEntry::OnShouter(BasePacket* pPacket)
{
	return TRUE;
}

BOOL SFLogicEntry::SendRequest(BasePacket* pPacket)
{
	return g_pEngine->SendRequest(pPacket);
}

/*BOOL SFLogicEntry::Send( int Serial, int PacketID, char* pBuffer, int BufferSize )
{
	int HeaderSize = sizeof(SFPacketHeader);

	SFPacket PacketSend;

	PacketSend.SetPacketID(PacketID);

	PacketSend.MakePacket((BYTE*)pBuffer, BufferSize, CGSF_PACKET_OPTION);

	return g_pEngine->GetNetworkEngine()->Send(Serial, (char*)PacketSend.GetHeader(), PacketSend.GetHeaderSize() + PacketSend.GetDataSize());
}*/