// EchoServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SFEngine.h"
#include "EchoLogicEntry.h"
#include "SFJsonProtocol.h"
#include "SFCasualGameDispatcher.h"

SFEngine* g_pEngine = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
	g_pEngine = new SFEngine(argv[0]);

////////////////////////////////////////////////////////////////////
//Game Mode
////////////////////////////////////////////////////////////////////
	EchoLogicEntry* pLogicEntry = new EchoLogicEntry();
	
/////////////////////////////////////////////////////////////////////
	if (FALSE == g_pEngine->Intialize(pLogicEntry, new SFPacketProtocol<SFJsonProtocol>, new SFCasualGameDispatcher()) ||
		FALSE == g_pEngine->Start())
	{
		google::FlushLogFiles(google::GLOG_INFO);
		google::FlushLogFiles(google::GLOG_ERROR);
		delete g_pEngine;
		return 0;
	}

	google::FlushLogFiles(google::GLOG_INFO);

	getchar();
	g_pEngine->ShutDown();

	return 0;
}

