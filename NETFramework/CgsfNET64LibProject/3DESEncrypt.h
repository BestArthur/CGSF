#pragma once

using namespace System;

namespace CgsfNET64Lib {
	class _3DESEncrypt
	{
	public:
		static array<Byte>^ Encrypt(array<Byte>^ sourceData, array<Byte>^ key)
		{
			array<Byte>^ encrypted;

			// Step 1. MD5 �ؽ��� ����ؼ� ��ȣȭ�ϰ�,	   
			// MD5 �ؽ� �����⸦ ����ؼ� ����� 128 ��Ʈ ����Ʈ �迭�ε�,          
			// 3DES ���ڵ��� ���� �ùٸ� ���̰� ��.

			auto HashProvider = gcnew System::Security::Cryptography::MD5CryptoServiceProvider();
			auto TDESKey = HashProvider->ComputeHash(key);

			// Step 2. TripleDESCryptoServiceProvider object ����            
			auto TDESAlgorithm = gcnew System::Security::Cryptography::TripleDESCryptoServiceProvider();

			// Step 3. Encoder ����
			TDESAlgorithm->Key = TDESKey;
			TDESAlgorithm->Mode = System::Security::Cryptography::CipherMode::ECB;
			TDESAlgorithm->Padding = System::Security::Cryptography::PaddingMode::PKCS7;

			
			// Step 4. ������ ���ڿ��� ��ȣȭ      
			try
			{
				auto Encryptor = TDESAlgorithm->CreateEncryptor();
				encrypted = Encryptor->TransformFinalBlock(sourceData, 0, sourceData->Length);
			}
			finally
			{
				// �߿��� 3DES, Hashprovider�� �Ӽ��� ����       
				TDESAlgorithm->Clear();
				HashProvider->Clear();
			}

			return encrypted;
		}


		static array<Byte>^ Decrypt(array<Byte>^ sourceData, array<Byte>^ key)
		{
			array<Byte>^ decrypted;

			auto HashProvider = gcnew System::Security::Cryptography::MD5CryptoServiceProvider();
			auto TDESKey = HashProvider->ComputeHash(key);

			auto TDESAlgorithm = gcnew System::Security::Cryptography::TripleDESCryptoServiceProvider();
			TDESAlgorithm->Key = TDESKey;
			TDESAlgorithm->Mode = System::Security::Cryptography::CipherMode::ECB;
			TDESAlgorithm->Padding = System::Security::Cryptography::PaddingMode::PKCS7;

			
			try
			{
				auto Decryptor = TDESAlgorithm->CreateDecryptor();
				decrypted = Decryptor->TransformFinalBlock(sourceData, 0, sourceData->Length);
			}
			finally
			{
				// �߿��� 3DES, Hashprovider�� �Ӽ��� ����
				TDESAlgorithm->Clear();
				HashProvider->Clear();
			}

			return decrypted;
		}

	};
}