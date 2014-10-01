#pragma once

//#include "Stdafx.h"
#include "ILogicEntry.h"
#include "ConcurrencyPacketQueue.h"

#include <gcroot.h>


//class BasePacket;

using namespace System;

namespace CgsfNET64Lib {

	/// <summary>
	/// ��Ʈ��ũ ó���� �ϴ� Ŭ����
	/// </summary>
	class ServerLogicEntry : public ILogicEntry
	{
	public:
		ServerLogicEntry(void) {}
		virtual ~ServerLogicEntry(void) {}

		/// <summary>
		/// �ʱ�ȭ. �ƹ��� ���� ���� ����
		/// </summary>
		/// <returns>������ true ��ȯ</returns>
		virtual bool Initialize() override
		{
			return true;
		}

		/// <summary>
		/// ��Ŷ�� ����
		/// </summary>
		/// <param name="pPacket">��Ʈ��ũ ������ ���ؼ� �޴� ��Ŷ ������</param>
		/// <returns>������ true ��ȯ</returns>
		virtual bool ProcessPacket(BasePacket* pPacket) override
		{
			m_refPacketQueue->Enqueue(false, pPacket);
			return true;
		}
		
		/// <summary>
		/// ��Ŷ�� ������
		/// </summary>
		/// <param name="pPacket">��Ʈ��ũ ������ ���� ���� ��Ŷ ������</param>
		/// <returns>true�� �ƴϸ� ������ ����</returns>
		virtual bool SendPacket(BasePacket* pPacket)
		{
			auto result = SFEngine::GetInstance()->SendRequest(pPacket);
			return result;
		}
		

		/// <summary>
		/// ��Ŷ ť. �ܺο��� �Ҵ� �޴´�.
		/// </summary>
		gcroot<ConcurrencyPacketQueue^> m_refPacketQueue;
		
	};
}