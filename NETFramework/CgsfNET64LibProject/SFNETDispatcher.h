#pragma once
#include "ILogicDispatcher.h"

namespace CgsfNET64Lib {
	
	/// <summary>
	/// ��Ʈ��ũ �������� ��Ŷ�� �����´�.
	/// </summary>
	class SFNETDispatcher : public ILogicDispatcher
	{
	public:
		SFNETDispatcher(void);
		virtual ~SFNETDispatcher(void);

		/// <summary>
		/// �ʱ�ȭ. ������ ���� �����Ѵ�.
		/// </summary>
		/// <param name="threadCount">������ ��</param>
		void Init(int threadCount);

		/// <summary>
		/// ��Ŷ�� �����ͼ� ť�� ��´�
		/// </summary>
		/// <param name="pPacket">��Ŷ</param>
		virtual void Dispatch(BasePacket* pPacket) override;

		/// <summary>
		/// ��Ŷ ����ó�� �� �����带 �����Ѵ�.
		/// </summary>
		/// <param name="pLogicEntry">��Ŷ�� ó���� ��ü</param>
		/// <returns>������ true ��ȯ</returns>
		virtual bool CreateLogicSystem(ILogicEntry* pLogicEntry) override;

		/// <summary>
		/// ��Ŷ ����ó�� �����Ѵ�. ���� ���� ���� �ÿ� ȣ���Ѵ�.
		/// </summary>
		/// <returns>������ true ��ȯ</returns>
		virtual bool ShutDownLogicSystem() override;

		/// <summary>
		/// ��Ŷ ��ü�� �޸� ����
		/// </summary>
		/// <param name="pPacket">�޸� ������ ��Ŷ ��ü</param>
		/// <returns>���ǵ��� ���� ��Ŷ Ÿ���� ��� false ��ȯ</returns>
		static bool ReleasePacket(BasePacket* pPacket);


	private:
		/// <summary>
		/// ��Ŷ ����ó�� ������
		/// </summary>
		static void LogicThreadProc(void* Args);

		/// <summary>
		/// LogicThreadProc ������ Ȱ�� ���θ� ����. false�� �Ǹ� LogicThreadProc �����带 �����Ѵ�.
		/// </summary>
		static bool m_bLogicEnd;

		/// <summary>
		/// LogicThreadProc ������ ����
		/// </summary>
		int m_nLogicThreadCnt;
	};
}
