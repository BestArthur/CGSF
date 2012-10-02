#pragma once
#include "SFLogicContents.h"
#include "SFObjectPool.h"
#include "ILogicEntry.h"
#include "SFDataBaseProxy.h"
#include "SFDirectoryWatcherTask.h"
#include "SFPacketStore.pb.h"

///////////////////////////////////////////////////////////////////////////
//Logic Entry
//��� ������ ó���� �����Դϴ�.
//���� : �� Ŭ������ �̱������� ���Դϴ�.
///////////////////////////////////////////////////////////////////////////
class SFPlayer;
class SFMessage;
class SFRoomManager;
class SFLobby;
class SFCommand;
class SFGameMode;

#include <map>

class SFLogicEntry : public ILogicEntry
{
public:
	typedef std::map<int, SFPlayer*> PlayerMap;
	typedef std::map<int, SFGameMode*> GameModeMap;

	SFLogicEntry(void);
	virtual ~SFLogicEntry(void);

	static SFLogicEntry* GetLogicEntry(){return m_pLogicEntry;}

	BOOL Initialize();
	BOOL CreateDirectoryWathcer();

	virtual BOOL ProcessPacket(SFCommand* pBase) override;
	
	SFRoomManager* GetRoomManager(){return m_pRoomManager;}
	SFLobby* GetLobby(){return m_pLobby;}

	BOOL Send(SFPlayer* pPlayer, SFPacket* pPacket);
	BOOL Send( int Serial, USHORT PacketID, char* pBuffer, int BufferSize );

	SFDatabaseProxy* GetDataBaseProxy(){return m_pDatabaseProxy;}

	BOOL AddGameMode(int Mode, SFGameMode* pMode);
	GameModeMap* GetGameModeMap(){return &m_GameModeMap;}

protected:
	BOOL OnConnectPlayer(int PlayerSerial);
	BOOL OnPlayerData(SFPacket* pPacket);
	BOOL OnTimer(SFPacket* pPacket);
	BOOL OnShouter(SFPacket* pPacket);

	BOOL OnDBResult(SFMessage* pMessage);
	BOOL OnDisconnectPlayer(int PlayerSerial);

private:
	static SFLogicEntry* m_pLogicEntry;

	SFObjectPool<SFPlayer>* m_pPlayerPool;
	PlayerMap m_PlayerMap;

	GameModeMap m_GameModeMap;
	
	SFRoomManager* m_pRoomManager;
	SFLobby* m_pLobby;

	SFDatabaseProxy* m_pDatabaseProxy;
	SFDirectoryWatcherTask m_DirectoryWatcherTask;

/////////////////////////////////////////////////////////////////////////////////////////////
//20120619 ���� ó�� ���� �ʼ� �����͸� ��� Ŭ����
//���� ���۽� �ѹ� �ε�ǰ� �ٽô� ������� ���� ���̱⿡ ������ ������
//SFLogicEntry�� �̱������� ���̰� ������ ������ �����ȴٸ� SFLogicContents�� ���� ����� �̱������� ���� �ʿ� ����
/////////////////////////////////////////////////////////////////////////////////////////////
	SFLogicContents m_LogicContents;
};
