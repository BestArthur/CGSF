// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFNetworkEntry.h"
#include "TCPCallback.h"
#include "UDPCallback.h"

#pragma comment(lib, "EngineLayer.lib")
#pragma comment(lib, "ClientInterface.lib")

#ifdef _DEBUG
#pragma comment(lib, "aced.lib")
#else
#pragma comment(lib, "ace.lib")
#endif

SFNetworkEntry* g_pNetworkEntry = NULL;

///////////////////////////////////////////////////////////////////////////////////
//�� ������ TCP�� ���� �����忡�� �����ϰ�, UDP�� ������ �����忡�� �����ϸ鼭 ��Ŷ�� ���� ������� �ѱ�� �����Դϴ�.
//���� TCP�� ������ ������� �и��ؼ� TCP/UDP/������ ������ ������� ���ư� �� �ֵ��� ������ ���Դϴ�.
///////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	g_pNetworkEntry = new SFNetworkEntry();

	TCPCallback* pCallback = new TCPCallback();
	UDPCallback* pUDPCallback = new UDPCallback(); 

	g_pNetworkEntry->Initialize(pCallback, pUDPCallback);

	g_pNetworkEntry->Run();

	while(1)
	{
		g_pNetworkEntry->Update();
	
		Sleep(1);
	}

	return 0;
}