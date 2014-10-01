#pragma once 

#include "stdafx.h"
#include "SFNETPacket.h"

#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Concurrent;

namespace CgsfNET64Lib {

	/// <summary>
	/// ���� ����� ��� ���� Ŭ����
	/// </summary>
	ref class Helper
	{
	public:
		/// <summary>
		/// ��Ʈ��ũ ���̺귯���� �α׸� ����Ͽ� �޽����� ���Ͽ� ��� �����.
		/// </summary>
		/// <param name="logLevel">�α׷���</param>
		/// <param name="logMessage">�α� �޽���</param>
		static void WriteLog(int logLevel, String^ logMessage)
		{
			auto log = msclr::interop::marshal_as<std::string>(logMessage);

			switch (logLevel)
			{
			case google::GLOG_INFO:
				LOG(INFO) << log.data();
				google::FlushLogFiles(google::GLOG_INFO);
				break;
			case google::GLOG_ERROR:
				LOG(ERROR) << log.data();
				google::FlushLogFiles(google::GLOG_ERROR);
				break;
			}
			
		}
	};
}