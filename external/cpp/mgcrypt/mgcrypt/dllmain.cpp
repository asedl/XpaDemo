//
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
#include "stdafx.h"

#include "mgcrypt_tls_objects.h"

BOOL WINAPI DllMain(HINSTANCE hDllInst, DWORD fdwReason, LPVOID lpvReserved)
{
	TlsObject* pData;
	BOOL bResult = TRUE;


	// Dispatch this main call based on the reason it was called.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// The DLL is being loaded for the first time by a given process.
		// Perform per-process initialization here.  If the initialization
		// is successful, return TRUE; if unsuccessful, return FALSE.
		if ((gv_dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
			return FALSE;

		// no break: fall thru to initialize data for first thread ...

	case DLL_THREAD_ATTACH:
		// A thread is being created in a process that has already loaded
		// this DLL.  Perform any per-thread initialization here.  The
		// return value is ignored.

		// new thread attached; increment thread count by 1
		InterlockedIncrement(&gvs_dwThreadCount);

		pData = new TlsObject;
		if (!TlsSetValue(gv_dwTlsIndex, pData))
		{
			// 
		}
		else
		{
			// for debugging purposes we store the thread identifier of the calling thread
			pData->m_dwThreadId = GetCurrentThreadId();
		}


		break;



	case DLL_PROCESS_DETACH:
		// The DLL is being unloaded by a given process.  Do any
		// per-process clean up here, such as undoing what was done in
		// DLL_PROCESS_ATTACH.  The return value is ignored.
		TlsFree(gv_dwTlsIndex);
		break;


	case DLL_THREAD_DETACH:
		// A thread is exiting cleanly in a process that has already
		// loaded this DLL.  Perform any per-thread clean up here.  The
		// return value is ignored.
		pData = (TlsObject*)TlsGetValue(gv_dwTlsIndex);
		if (pData != 0)
			delete pData;;

		InterlockedDecrement(&gvs_dwThreadCount);


		break;

	default:
		break;
	}

	return (bResult);
}
