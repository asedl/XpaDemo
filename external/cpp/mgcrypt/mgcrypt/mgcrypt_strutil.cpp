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

#include <iostream>
#include <fstream>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptlib.h"

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;


#include "osrng.h"
#include "base64.h"

#include "assert.h"

#include "mgcrypt_tls_objects.h"
#include "mgcrypt_strutil.h"

using namespace std;
using namespace CryptoPP;


std::string mgc_wstrtostr(const std::wstring &wstr)
{
	std::string strTo;
	char *szTo = new char[wstr.length() + 1];
	szTo[wstr.size()] = '\0';
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
	strTo = szTo;
	delete[] szTo;
	return strTo;
}

string hexencode(string& sdecoded) {
	string hexencoded;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(hexencoded));
	encoder.Put((const byte*)sdecoded.data(), sdecoded.size());
	encoder.MessageEnd();
	return hexencoded;
}

string base64encode(string& sdecoded) {
	string base64encoded;
	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(base64encoded));
	encoder.Put((const byte*)sdecoded.data(), sdecoded.size());
	encoder.MessageEnd();
	return base64encoded;
}
