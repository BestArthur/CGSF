#include "stdafx.h"
#include "SFEngine.h"
#include <conio.h>
#include "SFLogicEntry.h"
#include "P2PServer.h"
#include "SFServer.h"
#include "GoogleLog.h"
#include "SFTraining.h"
#include "SFFreeForAll.h"
#include "SFShouter.h"
#include "SFUtil.h"
#include "SFMGFramework.h"

SFSYSTEM_SERVER* g_pEngine = NULL;

#ifdef _DEBUG
#pragma comment(lib, "aced.lib")
#else
#pragma comment(lib, "ace.lib")
#endif

#pragma comment(lib, "CasualGame.lib")
#pragma comment(lib, "EngineLayer.lib")

#define GAMEMODE_NONE 0
#define GAMEMODE_TRAINING 1
#define GAMEMODE_DEATHMATCH 2
#define GAMEMODE_FREEFORALL 3
#define GAMEMODE_SUDDENDEATH 4

HINSTANCE g_pP2PHandle = 0;


int _tmain(int argc, _TCHAR* argv[])
{
	ACE::init();

	g_pEngine = new SFSYSTEM_SERVER();
	g_pEngine->CreateSystem();

	g_pP2PHandle = ::LoadLibrary(L"P2PServer.dll");

	if(g_pP2PHandle == NULL)
		return 0;

	ACTIVATEP2P_FUNC *pfuncActivate;
	pfuncActivate = (ACTIVATEP2P_FUNC *)::GetProcAddress( g_pP2PHandle, "ActivateP2P" );
	int Result = pfuncActivate();

	if(Result != 0)
		return 0;

	SFUtil::SetCurDirToModuleDir();
	
	/*SFShouter Shouter;
	_ShouterInfo* pInfo = Shouter.GetShouterInfo();
	pInfo->ShouterTitle = L"Notification";
	pInfo->StartTime = 0;
	pInfo->RepeatCount = 5;
	pInfo->SentenceInterval = 3000;
	pInfo->MessageInterval = 10000;
	pInfo->SentenceList.push_back(L"�ȳ��ϼ���");
	pInfo->SentenceList.push_back(L"������� �׽�Ʈ ���Դϴ�");
	pInfo->SentenceList.push_back(L"Korea Game Conference");

	Shouter.Write(L"Shouter.xml");*/


	SFLogicEntry* pLogicEntry = new SFLogicEntry();

////////////////////////////////////////////////////////////////////
//Timer
////////////////////////////////////////////////////////////////////
	_TimerInfo Timer;
	Timer.TimerID = TIMER_1_SEC;
	Timer.Period = 1000;
	Timer.StartDelay = 5000;

	pLogicEntry->AddTimer(Timer);

////////////////////////////////////////////////////////////////////
//Game Mode
////////////////////////////////////////////////////////////////////
	pLogicEntry->AddGameMode(GAMEMODE_TRAINING, new SFTraining(GAMEMODE_TRAINING));
	pLogicEntry->AddGameMode(GAMEMODE_FREEFORALL, new SFFreeForAll(GAMEMODE_FREEFORALL));

	pLogicEntry->Initialize();
	g_pEngine->Run(pLogicEntry);

	_getch();

	DEACTIVATEP2P_FUNC *pfuncDeactivate;
	pfuncDeactivate = (DEACTIVATEP2P_FUNC *)::GetProcAddress( g_pP2PHandle, "DeactivateP2P" );
	Result = pfuncDeactivate();

	::FreeLibrary(g_pP2PHandle);

	g_pEngine->Stop();

	ACE::fini();

	return 0;
}