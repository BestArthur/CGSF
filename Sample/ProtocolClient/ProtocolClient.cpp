// ProtocolClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ProtocolCallback.h"
#include "SFNetworkEntry.h"
#include "SFPacketProtocol.h"
#include "SFCGSFPacketProtocol.h"
#include "AvroClientProtocol.h"
#include "ProtocolClientProtocol.h"
#include "SFMsgPackProtocol.h"
#include "input.h"

#pragma comment(lib, "EngineLayer.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	ProtocolCallback* pCallback = new ProtocolCallback();

	SFNetworkEntry::GetInstance()->Initialize(pCallback, new SFPacketProtocol<AvroClientProtocol>(MAX_IO_SIZE, MAX_PACKET_SIZE));
	SFNetworkEntry::GetInstance()->Run();

	ProcessInput(&ProcessAvroInput);

	SFNetworkEntry::GetInstance()->ShutDown();

	return 0;
}