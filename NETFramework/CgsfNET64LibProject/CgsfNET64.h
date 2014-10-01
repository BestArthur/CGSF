// EngineLayerNET.h

#pragma once

#include "SFNETPacket.h"
#include "FRAMEWORK_ERROR_CODE.h"
#include "ConcurrencyPacketQueue.h"

using namespace System;
using namespace System::Collections;


namespace CgsfNET64Lib {

	class ServerLogicEntry;
	class SFNETDispatcher;
	class ServerConnectCallback;
	ref class ConcurrencyPacketQueue;

	public ref class CgsfNET64
	{
	public:
		CgsfNET64();
		~CgsfNET64();

		/// <summary>
		/// ��Ʈ��ũ �ʱ�ȭ
		/// </summary>
		/// <param name="config">��Ʈ��ũ ���� ����</param>
		/// <param name="connectInfoList">�ٸ� ������ �����ϱ� ���� ����</param>
		/// <param name="listneInfoList">config�� ������ Port �̿��� �߰� listen ����</param>
		/// <returns>�����ڵ�. NET_ERROR_CODE_N::SUCCESS �ܴ̿� ����</returns>
		NET_ERROR_CODE_N Init(NetworkConfig^ config, 
								Generic::List<RemoteServerConnectInfo^>^ connectInfoList,
								Generic::List<MultiListenNetworkInfo^>^ listneInfoList);
				

		/// <summary>
		/// ��Ʈ��ũ ���� ����. ������ �ްų� �ٸ� ������ ������ �� �� �ִ�.
		/// </summary>
		/// <param name="protocolID">��Ʈ��ũ ������ Port�� �����ϴ� ���ǿ��� ����� ��������ID</param>
		/// <returns></returns>
		bool Start(int protocolID);
		
		/// <summary>
		/// ��Ʈ��ũ ���� �ߴ�.
		/// </summary>
		void Stop();
			
		/// <summary>
		/// remote���� ���� ��Ŷ�� ��������.
		/// </summary>
		/// <returns>C++ SFPacket�� ������� �ٲ� ��Ŷ ������</returns>
		SFNETPacket^ GetPacket();

		/// <summary>
		/// ��Ŷ ����ҿ� ��Ŷ�� �ִ´�. ��Ʈ��ũ�� ���� ��Ŷ�� ���� �������� ó���ϱ� ���� �� ����Ѵ�.
		/// </summary>
		/// <param name="packet">��Ŷ</param>
		void InnerPacket(SFNETPacket^ packet);

		/// <summary>
		/// ��Ŷ ������.
		/// </summary>
		/// <param name="sessionID">��Ŷ�� ���� ����</param>
		/// <param name="packetID">��Ŷ ID</param>
		/// <param name="data">���� ������. ��Ŷ�� body �κ�</param>
		/// <returns>true�̸� ������ ����</returns>
		bool SendPacket(int sessionID, UINT16 packetID, array<Byte>^ data);

		/// <summary>
		/// ���� ������ ��Ʈ��ũ ���� ������ ��´�.
		/// </summary>
		/// <returns>��Ʈ��ũ ���� ����</returns>
		NetworkConfig^ GetNetworkConfig() { return m_networkConfig; }

		/// <summary>
		/// ������ ���������� ¥����.
		/// </summary>
		/// <param name="sessionID">����</param>
		void ForceDisConnect(int sessionID);
				
		/// <summary>
		/// ����Ʈ ������ ������ �õ��Ѵ�. �ֱ������� ���� ���� ���� ������ �ִٸ� �� �׶���� ������ �õ��Ѵ�.
		/// </summary>
		/// <returns>true�� �ƴϸ� ����</returns>
		bool SetupServerReconnectSys();


		
	private:
		/// <summary>
		/// ��Ʈ��ũ ������ �����Ѵ�. C++�� �ٸ��� ���������� ���� �ʰ� ���� �����Ѵ�.
		/// </summary>
		/// <param name="config">��Ʈ��ũ ����</param>
		void SetNetworkConfig(NetworkConfig^ config);
		
		/// <summary>
		/// ��Ŷ �������� �߰�
		/// </summary>
		/// <param name="protocolID">�������� ID</param>
		/// <param name="maxBufferSize">�ִ� ���� ũ��</param>
		/// <param name="maxPacketSize">��Ŷ �ϳ��� �ִ� ũ��</param>
		/// <param name="option">��Ŷ �ɼ�</param>
		/// <returns>true�� �ƴϸ� �߰� ����</returns>
		bool AddPacketProtocol(int protocolID, int maxBufferSize, int maxPacketSize, int option);
		
		/// <summary>
		/// �������� ID�� ����ũ���� �����Ѵ�.
		/// </summary>
		/// <param name="��������������">��Ʈ��ũ ������ Port�� �����ϴ� ���ǿ��� ����� ��������ID</param>
		/// <returns></returns>
		bool CheckingUniqueProtocolID(int protocolID);
		
		/// <summary>
		/// �ٸ� �������� ���� ������ ���. �� ������ ����Ͽ� �ٸ� ������ ������ �õ��Ѵ�.
		/// </summary>
		/// <param name="connectInfo">���� ����</param>
		/// <returns>�����ڵ�. NET_ERROR_CODE_N::SUCCESS �ܴ̿� ����</returns>
		NET_ERROR_CODE_N RegistConnectInfo(RemoteServerConnectInfo^ connectInfo);
		
		

		/// <summary>
		/// ���� ���� ��Ʈ��. ��κ� ��Ʈ��ũ ���� �κ�
		/// </summary>
		ServerLogicEntry* m_pLogicEntry = nullptr;
		
		/// <summary>
		/// ��Ʈ��ũ �������� ��Ŷ�� �������� Ŭ����
		/// </summary>
		SFNETDispatcher* m_pDispatcher = nullptr;

		/// <summary>
		/// �ٸ� ������ ������ �� ����, ������ �� ��Ŷ�� ���� ȣ��Ǵ� �ݹ�
		/// </summary>
		ServerConnectCallback* m_pServerConnectCallback = nullptr;
		
		/// <summary>
		/// ��Ŷ ���� ť. ������ ������ �ϴ�
		/// </summary>
		ConcurrencyPacketQueue^ m_packetQueue = gcnew ConcurrencyPacketQueue();

		/// <summary>
		/// ��Ʈ��ũ ���� ����
		/// </summary>
		NetworkConfig^ m_networkConfig = gcnew NetworkConfig();
		
		/// <summary>
		/// �ٸ� �������� ���� ����
		/// </summary>
		Generic::List<RemoteServerConnectInfo^>^ m_RemoteServerConnectInfoList = gcnew Generic::List<RemoteServerConnectInfo^>();

		/// <summary>
		/// ��Ƽ listen�� ���� ����
		/// </summary>
		Generic::List<MultiListenNetworkInfo^>^ m_ListneInfoList = gcnew Generic::List<MultiListenNetworkInfo^>();

		/// <summary>
		/// �ߺ����� ���� �������� ID ����
		/// </summary>
		Generic::List<int>^ m_UseProtocolIDList = gcnew Generic::List<int>();
	};
}
