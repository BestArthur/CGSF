#include "stdafx.h"
#include "CppUnitTest.h"

#include "SFCompressLzf.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseLayerTest
{
	TEST_CLASS(SFCompressLzfTest)
	{
	public:
		TEST_METHOD(TestCompressUnCompress)
		{
			// [�غ�]
			char szSource[] = "dsdsd1223098978������";
			int sourceLen = (int)(strlen(szSource));

			char szDest1[256] = { 0, };
			int destLen1 = 256;

			SFCompressLzf Lzf;

			// [���� - ����]
			auto compressRelust = Lzf.Compress((BYTE*)&szDest1, destLen1, (BYTE*)&szSource, sourceLen);
			// [����]
			Assert::AreEqual(true, compressRelust);

			
			char szDest2[256] = { 0, };
			int destLen2 = 256;

			// [���� - ���� ����]
			auto unCompressRelust = Lzf.Uncompress((BYTE*)&szDest2, destLen2, (BYTE*)&szDest1, destLen1);
			// [����]
			Assert::AreEqual(true, unCompressRelust);
			
			// [���� - ���� ������ �����͸� �� �����Ϳ� ��]
			Assert::AreEqual(szSource, szDest2);
		}

	};
}