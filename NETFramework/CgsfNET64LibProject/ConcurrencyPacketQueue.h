#pragma once 

#include "stdafx.h"
#include "SFNETPacket.h"


using namespace System;
using namespace System::Collections::Concurrent;

namespace CgsfNET64Lib {

	/// <summary>
	/// ������ �������� ��Ŷ ���� ť
	/// </summary>
	ref class ConcurrencyPacketQueue
	{
	public:
		ConcurrencyPacketQueue() {}
		~ConcurrencyPacketQueue() {}

		/// <summary>
		/// ť�� ��Ŷ�� �ִ´�.
		/// </summary>
		/// <param name="isServerConnect">true�̸� ������ ����</param>
		/// <param name="pPacket">��Ʈ��ũ ������ ���ؼ� ���� ��Ŷ. C++ Ÿ��</param>
		void Enqueue(bool isServerConnect, BasePacket* pPacket)
		{
			auto packet = MakeNetPacket(isServerConnect, pPacket);
			m_packetQueue->Enqueue(packet);
		}

		/// <summary>
		/// ť�� ��Ŷ�� �ִ´�. ��Ʈ��ũ ������ �ƴ� ���ο��� �ִ� ���
		/// </summary>
		/// <param name="packet">��Ŷ. .NET Ÿ��</param>
		void Enqueue(SFNETPacket^ packet)
		{
			m_packetQueue->Enqueue(packet);
		}

		/// <summary>
		/// ť���� ��Ŷ�� ������.
		/// </summary>
		/// <returns>��Ŷ�� ���ٸ� null ��ȯ.</returns>
		SFNETPacket^ Dequeue()
		{
			SFNETPacket^ packet = nullptr;

			m_packetQueue->TryDequeue(packet);

			return packet;
		}
		

	private:
		/// <summary>
		/// C++ Ÿ���� ��Ŷ�� .NET�� Ÿ���� ��Ŷ���� �����.
		/// </summary>
		/// <param name="isServerConnect">true�̸� ������ ����</param>
		/// <param name="pPacket">��Ʈ��ũ ������ ���ؼ� ���� ��Ŷ. C++ Ÿ��</param>
		/// <returns>��Ŷ. .NET Ÿ��</returns>
		SFNETPacket^ MakeNetPacket(bool isServerConnect, BasePacket* pPacket)
		{
			SFPacket* pSFPacket = (SFPacket*)pPacket;

			auto packet = gcnew SFNETPacket();
			packet->SetData(isServerConnect, pSFPacket);

			return packet;
		}
		
		/// <summary>
		/// ��Ŷ ť
		/// </summary>
		ConcurrentQueue<SFNETPacket^>^ m_packetQueue = gcnew ConcurrentQueue<SFNETPacket^>();
	};
}