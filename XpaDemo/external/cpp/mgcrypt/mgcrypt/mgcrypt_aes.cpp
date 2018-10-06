//
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
#include "stdafx.h"

#include <string>
using std::string;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptlib.h"
using CryptoPP::BufferedTransformation;
using CryptoPP::AuthenticatedSymmetricCipher;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;

#include "aes.h"
using CryptoPP::AES;

#include "gcm.h"
using CryptoPP::GCM;
using CryptoPP::GCM_TablesOption;

#include "osrng.h"
#include "sha.h"
#include "hkdf.h"
#include "base64.h"

#include "assert.h"

#include "mgcrypt_tls_objects.h"
#include "mgcrypt_aes.h"

using namespace std;
using namespace CryptoPP;


int AES_Encrypt (const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszMode, char**lpszCiphertext, char* lpszIV) {

	string plaintext(lpszPlaintext, lpdwPlaintextLength);
	string ciphertext;

	//KEY 0000000000000000000000000000000000000000000000000000000000000000
	//IV  000000000000000000000000
	//HDR 00000000000000000000000000000000
	//PTX 00000000000000000000000000000000
	//CTX cea7403d4d606b6e074ec5d3baf39d18
	//TAG ae9b1771dba9cf62b39be017940330b4

	// Test Vector 003
	byte key[32];
	memset(key, 0, sizeof(key));
	byte iv[12];
	memset(iv, 0, sizeof(iv));

	string adata(16, (char)0x00);

	const int TAG_SIZE = 16;

	// Encrypted, with Tag
	string cipher, encoded;


	try
	{
		GCM< AES >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
		// Not required for GCM mode (but required for CCM mode)
		// e.SpecifyDataLengths( adata.size(), pdata.size(), 0 );

		StringSource ss1(plaintext, true,
			new AuthenticatedEncryptionFilter(e,
				new StringSink(cipher), false, TAG_SIZE
			) // AuthenticatedEncryptionFilter
		); // StringSource


		// Pretty print
		StringSource(cipher, true,
			new HexEncoder(new StringSink(encoded), true, 16, " "));
	}
	catch (CryptoPP::BufferedTransformation::NoChannelSupport& e)
	{
	}
	catch (CryptoPP::AuthenticatedSymmetricCipher::BadState& e)
	{
	}
	catch (CryptoPP::InvalidArgument& e)
	{
	}


	*lpszCiphertext = new char[encoded.length() + 1];
	copy(encoded.begin(), encoded.end(), stdext::checked_array_iterator<char*>(*lpszCiphertext, encoded.length()));
	(*lpszCiphertext)[encoded.length()] = 0;

	return 0;

}

int AES_Encrypt_ECB (const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, string& encoded) {

	string plaintext(lpszPlaintext, lpdwPlaintextLength), ciphertext;

	SecByteBlock key(0);
	key.Assign((const byte*) lpszKey, 16);

	try
	{
		ECB_Mode< AES >::Encryption e;
		e.SetKey(key.begin(), key.size());

		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource ss1(plaintext, true,
			new StreamTransformationFilter(e,
				new StringSink(ciphertext)
			) // StreamTransformationFilter      
		); // StringSource

		// Pretty print
		StringSource(ciphertext, true,
			new HexEncoder(new StringSink(encoded), true, 0, ""));

	}
	catch (CryptoPP::BufferedTransformation::NoChannelSupport& e)
	{
	}
	catch (CryptoPP::AuthenticatedSymmetricCipher::BadState& e)
	{
	}
	catch (CryptoPP::InvalidArgument& e)
	{
	}
	
	return 0;

}

int AES_Encrypt_CBC(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszIV, string& ciphertext) {

	string plaintext(lpszPlaintext, lpdwPlaintextLength);

	SecByteBlock key(0), iv(0);
	key.Assign((const byte*)lpszKey, 16);
	iv.Assign((const byte*)lpszIV, 16);

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key.begin(), key.size(), iv);

		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource ss1(plaintext, true,
			new StreamTransformationFilter(e,
				new StringSink(ciphertext)
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch (CryptoPP::BufferedTransformation::NoChannelSupport& e)
	{
	}
	catch (CryptoPP::AuthenticatedSymmetricCipher::BadState& e)
	{
	}
	catch (CryptoPP::InvalidArgument& e)
	{
	}

	return 0;

}

int AES_Decrypt_CBC(const char* lpszCiphertext, long lpdwCiphertextLength, char* lpszKey, char* lpszIV, string& plaintext) {

	string ciphertext(lpszCiphertext, lpdwCiphertextLength);

	SecByteBlock key(0), iv(0);
	key.Assign((const byte*)lpszKey, 16);
	iv.Assign((const byte*)lpszIV, 16);

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key.begin(), key.size(), iv);

		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource ss1(ciphertext, true,
			new StreamTransformationFilter(d,
				new StringSink(plaintext)
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch (CryptoPP::InvalidCiphertext& e) {
		return 1;
	}
	catch (CryptoPP::BufferedTransformation::NoChannelSupport& e) {
		return 2;
	}
	catch (CryptoPP::AuthenticatedSymmetricCipher::BadState& e) {
		return 3;
	}
	catch (CryptoPP::InvalidArgument& e) {
		return 4;
	}
	return 0;

}


char* DeriveKey(char* lpszPassphrase, char* lpszIV, char* lpszKeyBuffer, size_t lKeybufferLength, size_t Keylength) {

	SecByteBlock key(Keylength);
	string password(lpszPassphrase), iv(lpszIV);

	try {
		HKDF<SHA256> hkdf;
		hkdf.DeriveKey(key, key.size(), (const byte*) password.data(), password.size(), (const byte*) iv.data(), iv.size(), NULL, 0);

		string encoded;
		CryptoPP::HexEncoder encoder;
		encoder.Attach(new CryptoPP::StringSink(encoded));
		encoder.Put(key, key.size());
		encoder.MessageEnd();

		int lencoded = encoded.size();
		if (lencoded + 1 <= lKeybufferLength) {
			copy(encoded.begin(), encoded.end(), stdext::checked_array_iterator<char*>(lpszKeyBuffer, lKeybufferLength));
			lpszKeyBuffer[lencoded] = 0;
		}
		else
			*lpszKeyBuffer = 0;
		return lpszKeyBuffer;

	}
	catch (const Exception& ex)
	{
		return 0;
	}
}