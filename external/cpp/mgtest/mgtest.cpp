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
#include <string>

#include "mgtest_tls_objects.h"
#include "printing.h"
#include "test_ocr.h"

using namespace std;

DWORD gv_dwTlsIndex = 0;
DWORD gvs_dwThreadCount = 0;

/*-------------------------------------------------------------------------*/
/* forward declarations and Magic UDF/UDP stuff ...
/*-------------------------------------------------------------------------*/
extern "C"
{
	__declspec(dllexport) void *MAGIC_BIND(void);
	__declspec(dllexport) const char* mgtest_version();
	__declspec(dllexport) wchar_t* mgtest_printersettings(wchar_t* lpszDriver, wchar_t* lpszPrinter, wchar_t* lpszOutput, long* fetchonly);
	__declspec(dllexport) long* mgtest_mapdrive(wchar_t* lpszLocalname, wchar_t* lpszRemotename, wchar_t* lpszUsername, wchar_t* lpszPassword, long* error_code);
	__declspec(dllexport) long* mgtest_test_ocr(wchar_t* lpszLocalname, wchar_t* lpszRemotename, long* error_code);
}

#define FUNC_CNT     4

static FUNC_DSC fdsc_tbl[FUNC_CNT] =
{
	{(unsigned char *)"mgtest_version", mgtest_version, 0, (unsigned char *) "A" },
	{(unsigned char*)"mgtest_printersettings", mgtest_printersettings, 4, (unsigned char*) "UUULU" },
	{(unsigned char*)"mgtest_mapdrive", mgtest_mapdrive, 5, (unsigned char*) "UUUULL" },
	{(unsigned char*)"mgtest_test_ocr", mgtest_test_ocr, 3, (unsigned char*) "UULL" },
};

static EXT_MODULE ext_module = { 0, NULL_PTR, NULL_PTR, FUNC_CNT, fdsc_tbl, (Uchar *) "mgtest" };

__declspec(dllexport) void *MAGIC_BIND(void)
{
	return (&ext_module);
}

// TODO: read following from version header in resource file
const char* mgtest_version()
{
	return "0.0.1";
}

long* mgtest_test_ocr(wchar_t* lpszLocalname, wchar_t* lpszImagefilename, long* error_code) {
	*error_code = 0;
	int r = testOcr(lpszImagefilename);
	return error_code;
}

long* mgtest_mapdrive(wchar_t* lpszLocalname, wchar_t* lpszRenotename, wchar_t* lpszUsername, wchar_t* lpszPassword, long* error_code) {

	DWORD dwResult;
	NETRESOURCE nr;

	memset(&nr, 0, sizeof(NETRESOURCE));
	nr.dwType = RESOURCETYPE_ANY;
	nr.lpLocalName = lpszLocalname;
	nr.lpRemoteName = lpszRenotename;
	nr.lpProvider = NULL;

	//
	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	//
	*error_code = WNetAddConnection2
	    (&nr, // NETRESOURCE from enumeration 
		(LPCWSTR) NULL,                  // no password 
		(LPCWSTR) NULL,                  // logged-in user 
		CONNECT_UPDATE_PROFILE);       // update profile with connect information 
	return error_code;
}


wchar_t* mgtest_printersettings(wchar_t* lpszDriver, wchar_t* lpszPrinter, wchar_t* lpszOutput, long* fetchonly) {
	wstring driver, printer, output;
	int retval = getPrintOptions(driver, printer, output, *fetchonly>0);
	copy(driver.begin(), driver.end(), lpszDriver);
	copy(printer.begin(), printer.end(), lpszPrinter);
	copy(output.begin(), output.end(), lpszOutput);
    return lpszPrinter;
}
