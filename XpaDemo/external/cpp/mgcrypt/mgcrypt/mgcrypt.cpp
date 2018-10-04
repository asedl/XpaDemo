 //
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
#include "stdafx.h"
#include "userdll.h"

#include <windows.h>
#include <fstream>

#include "mgcrypt_tls_objects.h"
#include "mgcrypt_sha256.h"
#include "mgcrypt_aes.h"

DWORD gv_dwTlsIndex = 0;
DWORD gvs_dwThreadCount = 0;

/*-------------------------------------------------------------------------*/
/* forward declarations and Magic UDF/UDP stuff ...
/*-------------------------------------------------------------------------*/
extern "C"
{
	__declspec(dllexport) void *MAGIC_BIND(void);
	__declspec(dllexport) const char* mgcrypt_version();
	__declspec(dllexport) char* mgcrypt_sha256_HexdigitsA(char* lpszBuffer, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen);
	__declspec(dllexport) char* mgcrypt_sha256_HexdigitsB(char* lpszBuffer, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen);
	__declspec(dllexport) char* mgcrypt_AES_Encrypt(char* lpszPlaintext, long* lpdwPlaintextLength, char* lpszKey, char* lpszMode, char* lpszIV);

}

#define FUNC_CNT     5

static FUNC_DSC fdsc_tbl[FUNC_CNT] =
{
	{(unsigned char *)"mgcrypt_version", mgcrypt_version, 0, (unsigned char *) "A" },
	{(unsigned char *)"mgcrypt_sha256_HexdigitsA", mgcrypt_sha256_HexdigitsA, 4, (unsigned char *) "ALALA" },
	{(unsigned char *)"mgcrypt_sha256_HexdigitsB", mgcrypt_sha256_HexdigitsB, 4, (unsigned char *) "ALTLA" },
    {(unsigned char *)"mgcrypt_AES_EncryptA", mgcrypt_AES_Encrypt, 5, (unsigned char *) "ALAAAA" },
    {(unsigned char *)"mgcrypt_AES_EncryptB", mgcrypt_AES_Encrypt, 5, (unsigned char *) "TLAAAA" }
};

static EXT_MODULE ext_module = { 0, NULL_PTR, NULL_PTR, FUNC_CNT, fdsc_tbl, (Uchar *) "mgcrypt" };

__declspec(dllexport) void *MAGIC_BIND(void)
{
	return (&ext_module);
}

// TODO: read following from version header in resource file
const char* mgcrypt_version ()
{
	return "0.0.1";
}

/*
    Calculates the SHA-256 hash for a message of any size and codes the hash bytes as hexadecimal digits.
	A SHA-256 message digest (hash) is 256 Bit (as the name suggests), thats 32 Bytes.
	mgcrypt_sha256_HexdigitsA generates a hexadecimal representation of the (binary) hash where each digit (0..F) codes 4 Bit.
	The buffer which will receive the result (lpszHash) therefore needs to be large enough to get filled with 64 digits (characters).
	mgcrypt_sha256_HexdigitsA will not add a trailling 0 character.
*/
char* mgcrypt_sha256_HexdigitsA(char* lpszHash, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen) {
	return sha256_HexdigitsA (lpszData, *lpdwDataLen, lpszHash, *lpdwBufferLen);
}

char* mgcrypt_sha256_HexdigitsB(char* lpszHash, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen) {
	return sha256_HexdigitsA(lpszData, *lpdwDataLen, lpszHash, *lpdwBufferLen);
}

/** 
	mgcrypt_AES_Encrypt encrypts plain text (binary data) with AES algorithm.
**/
char* mgcrypt_AES_Encrypt(char* lpszPlaintext, long* lpdwPlaintextLength, char* lpszKey, char* lpszMode, char* lpszIV)
{

	TlsObject* pData = (TlsObject*) TlsGetValue (gv_dwTlsIndex);
	if (pData)
	{
		// delete encryption result of a previous run ...
		if (pData->m_pBuffer_Ciphertext) {
			delete[] pData->m_pBuffer_Ciphertext;
			pData->m_pBuffer_Ciphertext = 0;
		}

		int encryption_result =
			AES_Encrypt(lpszPlaintext, *lpdwPlaintextLength, lpszKey, lpszMode, &pData->m_pBuffer_Ciphertext, lpszIV);

		return pData->m_pBuffer_Ciphertext;

	}

	return (char *) "";
}
