#pragma once

#include "EngineInterface/INetworkCallback.h"
#include "ConcurrencyPacketQueue.h"
#include <gcroot.h>


namespace CgsfNET64Lib {

	/// <summary>
	/// ����������
	/// </summary>
	class ServerConnectCallback : public INetworkCallback
	{
	public:
		ServerConnectCallback()
		{
		}

		virtual ~ServerConnectCallback()
		{
		}

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="serial">���� ID</param>
		/// <param name="m_sessiondesc">���� ����</param>
		virtual void HandleConnect(int serial, _SessionDesc m_sessiondesc) override
		{
			INetworkCallback::HandleConnect(serial, m_sessiondesc);

			SFNETPacket^ packet = gcnew SFNETPacket();
			packet->SetSystemData(SFPACKET_TYPE::CONNECT, serial, m_sessiondesc.identifier);
			m_refPacketQueue->Enqueue(packet);
		}

		/// <summary>
		/// ������ ������
		/// </summary>
		/// <param name="serial">���� ID</param>
		/// <param name="m_sessiondesc">���� ����</param>
		virtual void HandleDisconnect(int serial, _SessionDesc m_sessiondesc) override
		{
			INetworkCallback::HandleDisconnect(serial, m_sessiondesc);

			SFNETPacket^ packet = gcnew SFNETPacket();
			packet->SetSystemData(SFPACKET_TYPE::DISCONNECT, serial, m_sessiondesc.identifier);
			m_refPacketQueue->Enqueue(packet);
		}

		/// <summary>
		/// ��Ŷ�� ����
		/// </summary>
		/// <param name="pPacket">��Ʈ��ũ ������ ���ؼ� �޴� ��Ŷ ������</param>
		/// <returns>������ true ��ȯ</returns>
		virtual bool HandleNetworkMessage(BasePacket* pPacket) override
		{
			m_refPacketQueue->Enqueue(true, pPacket);
			return true;
		}
		


		/// <summary>
		/// ��Ŷ ť. �ܺο��� �Ҵ� �޴´�.
		/// </summary>
		gcroot<ConcurrencyPacketQueue^> m_refPacketQueue;

	};
}