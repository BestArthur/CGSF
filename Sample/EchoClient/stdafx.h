// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "CommonHeader.h"

#include <windows.h>
#include <SFPacketStore/SFPacketStore.pb.h>

#ifdef _DEBUG
#pragma comment(lib, "aced.lib")
#else
#pragma comment(lib, "ace.lib")
#endif

#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "liblzf.lib")
#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "BaseLayer.lib")
#pragma comment(lib, "EngineLayer.lib")
#pragma comment(lib, "DatabaseLayer.lib")