#pragma once

using namespace System;

namespace CgsfNET64Lib {

	public enum class ERROR_CODE_N : short
	{
		// �߿�!!!
		// ���ǵ� ���� CommonLayer�� ErrorCode.h�� ���ǵ� �Ͱ� ���ƾ� �Ѵ�.
		SUCCESS = 0,

		ENGINE_INIT_LOGIC_ENTRY_FAIL = 101,
		ENGINE_INIT_NULL_CONFIG_INFO = 102,
		ENGINE_INIT_CREAT_ENGINE_FAIL = 103,
		ENGINE_INIT_CREAT_LOGIC_SYSTEM_FAIL = 104,
	};
}