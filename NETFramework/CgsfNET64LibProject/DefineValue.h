#pragma once

#include "BasePacket.h"
#include "SFConstant.h"

using namespace System;

namespace CgsfNET64Lib { 
	
	/// <summary>
	/// ��Ŷ Ÿ��
	/// </summary>
	public enum class SFPACKET_TYPE : short
	{ 
		NONE = SFPACKET_NONE,
		CONNECT = SFPACKET_CONNECT,
		DATA = SFPACKET_DATA,
		RPC = SFPACKET_RPC,
		TIMER = SFPACKET_TIMER,
		SHOUTER = SFPACKET_SHOUTER,
		DISCONNECT = SFPACKET_DISCONNECT,
		DB = SFPACKET_DB,
		SERVERSHUTDOWN = SFPACKET_SERVERSHUTDOWN,
	};
	
	/// <summary>
	/// ��Ŷ �ɼ�
	/// </summary>
	public enum class PACKET_OPTION_TYPE : short
	{
		NONE = 0,
		DATACRC = PACKET_OPTION_DATACRC,
		COMPRESS = PACKET_OPTION_COMPRESS,
		ENCRYPTION = PACKET_OPTION_ENCRYPTION,
		CRC_DEFAULT = PACKET_OPTION_CRC_DEFAULT,
		CRC_MD5 = PACKET_OPTION_CRC_MD5,
		ENCRYPTION_DES = PACKET_OPTION_ENCRYPTION_DES,
		ENCRYPTION_3DES = PACKET_OPTION_ENCRYPTION_3DES,
		ENCRYPTION_AES = PACKET_OPTION_ENCRYPTION_AES,
	};

	/// <summary>
	/// �������� Ÿ��
	/// </summary>
	public enum class PACKET_PROTOCOL_TYPE : short
	{
		JSON = PACKET_PROTOCOL_JSON, 
		CGSF = PACKET_PROTOCOL_CGSF,
		PROTO_BUF = PACKET_PROTOCOL_PROTO_BUF,
		MSG_PACK = PACKET_PROTOCOL_MSG_PACK,
		AVRO = PACKET_PROTOCOL_AVRO,
	};



	/// <summary>
	/// ��Ʈ��ũ ����
	/// </summary>
	public ref struct NetworkConfig
	{
		String^ IP;
		UINT16 Port;
		
		/// ��Ʈ��ũ ���� dll ���� �̸�
		String^ EngineDllName;
		
		/// ��Ŷ ������ ������ ��
		int ThreadCount;

		/// �ִ� ���� ��� ��
		int MaxAcceptCount;
		int ProtocolOption;
		int ProtocolID;
		int MaxBufferSize;
		int MaxPacketSize;
	};

	/// <summary>
	/// �ٸ� ���� ������ ���� ��Ʈ��ũ ����
	/// </summary>
	public ref struct RemoteServerConnectInfo
	{
		String^ IP;
		UINT16 Port;
		/// ���� ID. �ߺ��Ǹ� �ȵȴ�
		int ConnectID;
		String^ Description;

		int ProtocolOption;
		int ProtocolID;
		int MaxBufferSize;
		int MaxPacketSize;
	};

	/// <summary>
	/// ��Ƽ listen ��Ʈ��ũ ����
	/// </summary>
	public ref struct MultiListenNetworkInfo
	{
		/// listen ID. �ý��ۿ��� �Ҵ��Ѵ�.
		int ListenID;		
				
		UINT16 Port;
		
		int ProtocolOption;
		int ProtocolID;
		int MaxBufferSize;
		int MaxPacketSize;
	};

	/// ��Ŷ �ɼ� ����
	const int CGSF_PACKET_OPTION_NONE = 0;

	/// ���� ������ ID�� �ּ� ��. �̰ͺ��� ������ �ȵȴ�.
	const int MIN_SERVER_CONNECTOR_ID = 1001;
}