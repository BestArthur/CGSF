// TestDatabase.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SFDatabaseProxy.h"
#include "SFDatabaseProxyLocal.h"
#include "SFDatabaseProxyImpl.h"
#include "SFFastDBAdaptorImpl.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ACE::init();

	SFDatabaseProxy* pProxyLocal = new SFDatabaseProxyLocal<SFFastDBAdaptorImpl>();
	SFDatabaseProxy* pDatabaseProxy = new SFDatabaseProxyImpl(pProxyLocal);

	pDatabaseProxy->Initialize();

	getchar();

	return 0;
}

