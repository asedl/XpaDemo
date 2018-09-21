//
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
#include "stdafx.h"

#include <string>
#include <iterator>
#include <iostream>

#include "cryptlib.h"
#include "sha.h"
#include "hex.h"

#include "mgcrypt_tls_objects.h"
#include "mgcrypt_sha256.h"

using namespace std;

char* sha256_HexdigitsA(char* lpszData, size_t lInputLength, char* lpszSHA256Buffer, size_t lOutputLenghtMax)
{
	CryptoPP::SHA256 hash;
	CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
	string message(lpszData, lInputLength);

	hash.CalculateDigest(digest, reinterpret_cast<CryptoPP::byte*>(&message[0]), message.length());

	CryptoPP::HexEncoder encoder;
	std::string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	if (output.length() <= lOutputLenghtMax)
		copy(output.begin(), output.end(), lpszSHA256Buffer);
	else
		*lpszSHA256Buffer = 0;
	return lpszSHA256Buffer;
}

