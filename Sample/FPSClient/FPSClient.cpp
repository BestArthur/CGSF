// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFNetworkEntry.h"
#include "TCPCallback.h"
#include "UDPCallback.h"
#include "FPSClientProtocol.h"
#include "SFPacketProtocol.h"
#include "SFCasualGameDispatcher.h"

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

	g_pNetworkEntry->Initialize("CGSFEngine.dll", pCallback, pUDPCallback);

	IPacketProtocol* pProtocol = new SFPacketProtocol<FPSClientProtocol>;
	g_pNetworkEntry->SetPacketProtocol(pProtocol);

	ILogicDispatcher* pDispatcher = new SFCasualGameDispatcher();
	g_pNetworkEntry->SetLogicDispatcher(pDispatcher);


	g_pNetworkEntry->Run();

	while(1)
	{
		g_pNetworkEntry->Update();
	
		Sleep(1);
	}

	return 0;
}