#pragma once

using namespace System;
using System::StringComparer;

namespace CgsfNET64Lib {
	public class AESEncrypt
	{
	public:
		// 128bit(16byte)�� IV���ʱ�ȭ ���ͣ��� Key(��ȣŰ��
		//static private string AesIV = @"!QAZ2WSX#EDC4RFV";
		//static private string AesKey = @"5TGB&YHN7UJM(IK<";

		/// <summary>
		/// ���ڿ��� AES�� ��ȣȭ �Ѵ�
		/// </summary>
		static array<Byte>^ Encrypt(array<Byte>^ sourceData, array<Byte>^ aesKey, array<Byte>^ aesIV)
		{
			// AES ��ȣȭ ���� ���ι��̴�. System.Core.Dll�� �߰��ؾ� �Ѵ�.
			auto aes = gcnew System::Security::Cryptography::AesCryptoServiceProvider();
			aes->BlockSize = 128;
			aes->KeySize = 128;
			aes->IV = aesIV;
			aes->Key = aesKey;
			aes->Mode = System::Security::Cryptography::CipherMode::CBC;
			aes->Padding = System::Security::Cryptography::PaddingMode::PKCS7;
						
			auto encrypt = aes->CreateEncryptor();
			auto encrypted = encrypt->TransformFinalBlock(sourceData, 0, sourceData->Length);

			encrypt->Dispose();

			return encrypted;
		}

		/// <summary>
		/// ���ڿ��� AES�� ��ȣȭ �Ѵ�
		/// </summary>
		static array<Byte>^ Decrypt(array<Byte>^ sourceData, array<Byte>^ aesKey, array<Byte>^ aesIV)
		{
			// AES ��ȣȭ ���� ���ι��̴�
			auto aes = gcnew System::Security::Cryptography::AesCryptoServiceProvider();
			aes->BlockSize = 128;
			aes->KeySize = 128;
			aes->IV = aesIV;
			aes->Key = aesKey;
			aes->Mode = System::Security::Cryptography::CipherMode::CBC;
			aes->Padding = System::Security::Cryptography::PaddingMode::PKCS7;

			auto decrypt = aes->CreateDecryptor();
			auto decrypted = decrypt->TransformFinalBlock(sourceData, 0, sourceData->Length);
			return decrypted;
		}
	};
}