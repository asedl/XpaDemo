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
#include <locale>
#include <string>

#include "mgcrypt_tls_objects.h"
#include "mgcrypt_sha256.h"
#include "mgcrypt_aes.h"
#include "mgcrypt_misc.h"
#include "mgcrypt_strutil.h"

using namespace std;

DWORD gv_dwTlsIndex = 0;
DWORD gvs_dwThreadCount = 0;

typedef struct  {
	DWORD      dwBlobType; // reserved for type information
	BYTE       *pbBlob;    // pointer to the actual (Blob) data / BYTE Array
	DWORD      cbData;     // size/length of BYTE Array at *pbBlob
} MGCBLOB, *PMGCBLOB;

/*-------------------------------------------------------------------------*/
/* forward declarations and Magic UDF/UDP stuff ...
/*-------------------------------------------------------------------------*/
extern "C"
{
	__declspec(dllexport) void *MAGIC_BIND(void);
	__declspec(dllexport) const char* mgcrypt_version();
	__declspec(dllexport) long* mgcrypt_GetTempfilename(char* lpszBuffer, long* lpdwBuffersize, long* lpdwndxTempfile);
	__declspec(dllexport) char* mgcrypt_GenerateRandom(long* lpdwBlocksize);
	__declspec(dllexport) char* mgcrypt_Hexencode(char* pRawData, long* lpdwLength);
	__declspec(dllexport) char* mgcrypt_Hexdecode(char* pHexencoded, long* lpdwLength);
	__declspec(dllexport) char* mgcrypt_HexdecodeToFile(char* pHexencoded, long* lpdwLength, char* lpszFilename, LONG* lpdwFilenameMaxLength);
	__declspec(dllexport) char* mgcrypt_sha256_HexdigitsA(char* lpszBuffer, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen);
	__declspec(dllexport) char* mgcrypt_sha256_HexdigitsB(char* lpszBuffer, long* lpdwBufferLen, char* lpszData, long* lpdwDataLen);
	__declspec(dllexport) long* mgcrypt_AES_Encrypt(char* lpszPlaintext, long* lpdwPlaintextLength, char* lpszKey, char* lpszIV, char* lpszMode, char*lpszFilename, long* lpdwFilenameLengthMax, char* lpszOutputencoding, long* lpdwError);
	__declspec(dllexport) long* mgcrypt_AES_Decrypt(char* lpszCiphertext, long* lpdwCiphertextLength, char* lpszKey, char* lpszIV, char* lpszMode, char*lpszFilename, long* lpdwFilenameLengthMax, long* lpdwError);
	__declspec(dllexport) char* mgcrypt_AES_DeriveKey(char* lpszPassphrase, char* lpszIV, char* lpszKeyBuffer, long* lpdwKeybufferLength, long* lpdwKeyLength, long* error);
	__declspec(dllexport) PMGCBLOB mgcrypt_Blobtest1(PMGCBLOB pBlobIn);
	}

#define FUNC_CNT     12

static FUNC_DSC fdsc_tbl[FUNC_CNT] =
{
	{ (unsigned char *) "mgcrypt_version", mgcrypt_version, 0, (unsigned char *) "A" },
	{ (unsigned char *) "mgcrypt_GetTempfilename", mgcrypt_GetTempfilename, 3, (unsigned char *) "ALLL" },
	{ (unsigned char *) "mgcrypt_GenerateRandom", mgcrypt_GenerateRandom, 1, (unsigned char *) "LA" },
	{ (unsigned char *) "mgcrypt_Hexencode", mgcrypt_Hexencode, 2, (unsigned char *) "TLB" },
	{ (unsigned char *) "mgcrypt_Hexdecode", mgcrypt_Hexdecode, 2, (unsigned char *) "TLB" },
	{ (unsigned char *) "mgcrypt_HexdecodeToFile", mgcrypt_HexdecodeToFile, 4, (unsigned char *) "TLALA" },
	{ (unsigned char *) "mgcrypt_sha256_HexdigitsA", mgcrypt_sha256_HexdigitsA, 4, (unsigned char *) "ALALA" },
	{ (unsigned char *) "mgcrypt_sha256_HexdigitsB", mgcrypt_sha256_HexdigitsB, 4, (unsigned char *) "ALTLA" },
	{ (unsigned char *) "mgcrypt_AES_Encrypt", mgcrypt_AES_Encrypt, 9, (unsigned char *) "TLTTAALALL" },
	{ (unsigned char *) "mgcrypt_AES_Decrypt", mgcrypt_AES_Decrypt, 8, (unsigned char *) "TLTTAALLL" },
	{ (unsigned char *) "mgcrypt_AES_DeriveKey", mgcrypt_AES_DeriveKey, 6, (unsigned char *) "AAALLLA" },
	{ (unsigned char *) "mgcrypt_Blobtest1", mgcrypt_Blobtest1, 1, (unsigned char *) "TT" }
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
	The required memory for the ciphertext is allocated dynamically in TLS, no need to do this in Magic and pass a paramter which points to it.
	The ciphertext is the return value of this function. In case of an error an empty string will be returned.
**/

long* mgcrypt_AES_Encrypt(char* lpszPlaintext, long* lpdwPlaintextLength, char* lpszKey, char* lpszIV, char* lpszMode, char*lpszFilename, long* lpdwFilenameLengthMax, 
	char* lpszOutputFormat, long* lpdwError)
{
	*lpdwError = 0;
	int encryption_result = 0;
	string mode(lpszMode);
	string outputformat(lpszOutputFormat);
	string cipertextencoded;

	TlsObject* pData = (TlsObject*)TlsGetValue(gv_dwTlsIndex);
	if (pData)
	{
		// delete encryption result of a previous run ...
		if (pData->m_pBuffer_Ciphertext) {
			delete[] pData->m_pBuffer_Ciphertext;
			pData->m_pBuffer_Ciphertext = 0;
		}

		if (mode.compare("GCM") == 0)
			encryption_result = AES_Encrypt(lpszPlaintext, *lpdwPlaintextLength, lpszKey, lpszMode, &pData->m_pBuffer_Ciphertext, lpszIV);

		else if (mode.compare("ECB") == 0)
			encryption_result = AES_Encrypt_ECB(lpszPlaintext, *lpdwPlaintextLength, lpszKey, cipertextencoded);

		else if (mode.compare("CBC") == 0)
			encryption_result = AES_Encrypt_CBC(lpszPlaintext, *lpdwPlaintextLength, lpszKey, lpszIV, cipertextencoded);

		else if (mode.compare("CFB") == 0)
			encryption_result = AES_Encrypt_CFB(lpszPlaintext, *lpdwPlaintextLength, lpszKey, lpszIV, cipertextencoded);

		else
			*lpdwError = 1; // invalid encryption mode / mode of operation
	}
	else
		*lpdwError = 2; // failed to access TLS object

	if (*lpdwError == 0 && outputformat.size() > 0) {
		if (outputformat.compare("HEXDIGITS")) {
			cipertextencoded = hexencode(cipertextencoded);
		}
		else if (outputformat.compare("BASE64")) {
			cipertextencoded = base64encode(cipertextencoded);
		}
	}

	if (*lpdwError == 0) {
		wstring tempfilename;
		size_t nBytesResult;
		std::vector<BYTE> v(cipertextencoded.c_str(), cipertextencoded.c_str() + cipertextencoded.size());
		int write_result = WriteBlobToTempfile(v, tempfilename);
		if (write_result == 0) {
			string tempfilename_ansi = mgc_wstrtostr(tempfilename);
			if (tempfilename_ansi.length() < (size_t)*lpdwFilenameLengthMax) {
				memcpy_s(lpszFilename, *lpdwFilenameLengthMax, tempfilename_ansi.c_str(), tempfilename_ansi.length());
			}
		}
	}

	return lpdwError;
}

long* mgcrypt_AES_Decrypt(char* lpszCiphertext, long* lpdwCiphertextLength, char* lpszKey, char* lpszIV, char* lpszMode, char*lpszFilename, long* lpdwFilenameLengthMax, long* lpdwError)
{
	*lpdwError = 0;
	int result = 0;
	string mode(lpszMode);
	string plaintext;

	if (mode.compare("CBC") == 0)
		result = AES_Decrypt_CBC(lpszCiphertext, *lpdwCiphertextLength, lpszKey, lpszIV, plaintext);
	else if (mode.compare("CFB") == 0)
		result = AES_Decrypt_CFB(lpszCiphertext, *lpdwCiphertextLength, lpszKey, lpszIV, plaintext);
	else {
		*lpdwError = 1; // invalid encryption mode / mode of operation
		return lpdwError;
	}

	if (result == 0) {
		wstring tempfilename;
		size_t nBytesResult;
		std::vector<BYTE> v(plaintext.data(), plaintext.data() + plaintext.size());
		int write_result = WriteBlobToTempfile(v, tempfilename);
		if (write_result == 0) {
			string tempfilename_ansi = mgc_wstrtostr(tempfilename);
			if (tempfilename_ansi.length() < (size_t)*lpdwFilenameLengthMax) {
				memcpy_s(lpszFilename, *lpdwFilenameLengthMax, tempfilename_ansi.c_str(), tempfilename_ansi.length());
			}
		}
	}
	else {
		*lpdwError = 2; // Encrypotion failed
		return lpdwError;
	}

	return lpdwError;
}

/**
 * mgcrypt_AES_DeriveKey() allows to derive an AES encryption key from a passphrase. 
 */
char* mgcrypt_AES_DeriveKey(char* lpszPassphrase, char* lpszIV, char* lpszKeyBuffer, long* lpdwKeybufferLength, long* lpdwKeyLength, long* error)
{
	*error = -9999;
	char* keybuffer = DeriveKey(lpszPassphrase, lpszIV, lpszKeyBuffer, *lpdwKeybufferLength, *lpdwKeyLength);
	if (keybuffer) {
		*error = 0;
		return keybuffer;
	}

	return 0;
}

char* mgcrypt_GenerateRandom(long* lpdwBlocksize) {

	TlsObject* pData = (TlsObject*) TlsGetValue(gv_dwTlsIndex);
	if (pData)
	{
		if (pData->m_pBuffer_Random) {
			delete[] pData->m_pBuffer_Random;
			pData->m_pBuffer_Random = 0;
		}

		int encryption_result = GenerateRandom(&pData->m_pBuffer_Random, (const unsigned int) *lpdwBlocksize);
		if (encryption_result == 0)
			return pData->m_pBuffer_Random;
	}

	return (char *) "";
}


char* mgcrypt_Hexencode(char* pRawData, long* lpdwLength) {
	TlsObject* pData = (TlsObject*)TlsGetValue(gv_dwTlsIndex);
	if (pData)
	{
		if (pData->m_pBuffer_Hexencode) {
			delete[] pData->m_pBuffer_Hexencode;
			pData->m_pBuffer_Hexencode = 0;
		}

		string stoencode(pRawData, *lpdwLength);


		int encryption_result = Hexencode(stoencode, &pData->m_pBuffer_Hexencode);
		if (encryption_result == 0)
			return pData->m_pBuffer_Hexencode;
	}

	return (char *) "";
}

char* mgcrypt_Hexdecode(char* pHexencoded, long* lpdwLength) {
	TlsObject* pData = (TlsObject*)TlsGetValue(gv_dwTlsIndex);
	if (pData)
	{
		if (pData->m_pBuffer_Hexencode) {
			delete[] pData->m_pBuffer_Hexencode;
			pData->m_pBuffer_Hexencode = 0;
		}

		string hexencoded(pHexencoded, *lpdwLength);

		size_t nResultBytes;
		int encryption_result = Hexdecode(hexencoded, &pData->m_pBuffer_Hexencode, nResultBytes);
		if (encryption_result == 0)
			return pData->m_pBuffer_Hexencode;
	}

	return (char *) "";
}

/**
  * Decode hexencoded data (Blob). Since there's problems with binary data returned in Blobs(may have 0 bytes in the middle)
  * we actually write the result of the encoding to a (temporary) file and retrun pathname of that instead.
  * In Magic one can read it with File2Blb() into a binary Blob and delete it afterwards.
  */
char* mgcrypt_HexdecodeToFile(char* pHexencoded, long* lpdwLength, char* lpszFilename, LONG* lpdwFilenameMaxLength) {
	wstring tempfilename;
	size_t nBytesResult;

	string hexencoded(pHexencoded, *lpdwLength);

	char* pBuffer_Hexencode = 0;
	int encryption_result = Hexdecode(hexencoded, &pBuffer_Hexencode, nBytesResult);
	if (encryption_result == 0) {
		std::vector<BYTE> v (pBuffer_Hexencode, pBuffer_Hexencode + nBytesResult);
		int write_result = WriteBlobToTempfile(v, tempfilename);
		if (write_result == 0) {
			string tempfilename_ansi = mgc_wstrtostr(tempfilename);
			if (tempfilename_ansi.length() < (size_t) *lpdwFilenameMaxLength) {
				memcpy_s(lpszFilename, *lpdwFilenameMaxLength, tempfilename_ansi.c_str(), tempfilename_ansi.length());
				return lpszFilename;
			}
		}
	}

	return 0;

}

long* mgcrypt_GetTempfilename(char* lpszBuffer, long* lpdwBuffersize, long* lpdwndxTempfile) {
	wchar_t wszTempFileName[MAX_PATH];

	*lpdwndxTempfile = 0;
	int ndxTempfile = GetTempfilename(&wszTempFileName[0]);
	if (ndxTempfile != 0) {
		std::string stempfilename = mgc_wstrtostr(wszTempFileName);
		if (stempfilename.length() < (size_t)*lpdwBuffersize) {
			memcpy_s(lpszBuffer, *lpdwBuffersize, stempfilename.c_str(), stempfilename.length());
			*lpdwndxTempfile = ndxTempfile;
		}
	}

	return lpdwndxTempfile;
}


// This is a testfunction which allocates enough memory for a copy of *pBlobIn, copies the content of it
// to there and then returns a pointer to that exact copy. 
// NOTE: Do not do this in production code since this is not thread safe Synchronize access to that buffer
// or allocate the required storage in TLS
PMGCBLOB mgcrypt_Blobtest1 (PMGCBLOB pBlobIn) {
	static PMGCBLOB pBlobRet = new MGCBLOB;
	pBlobRet->dwBlobType = pBlobIn->dwBlobType;
	pBlobRet->pbBlob = new BYTE[pBlobIn->cbData];
	memcpy_s(pBlobRet->pbBlob, pBlobIn->cbData * sizeof(BYTE), pBlobIn->pbBlob, pBlobIn->cbData * sizeof(BYTE));
	pBlobRet->cbData = pBlobIn->cbData * sizeof(BYTE);

	return pBlobRet;
}

