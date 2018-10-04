//
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <vector>

using namespace std;

class TlsObject
{
public:
	TlsObject()
	{
		m_pBuffer_Ciphertext = 0;
	}

	virtual ~TlsObject()
	{
		delete[] m_pBuffer_Ciphertext;
	}

	char* m_pBuffer_Ciphertext;

	DWORD   m_dwThreadId, m_dwThreadIndex;
};

extern DWORD gvs_dwThreadCount;
extern DWORD gv_dwTlsIndex;

