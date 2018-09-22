#include "stdafx.h"

#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <commdlg.h >

#include <string>

using namespace std;

int getPrintOptions(wstring& pdriver, wstring& pname, wstring& poutput, bool fetchonly) {

	pdriver.empty();
	pname.empty();
	poutput.empty();

	// Allocate the PRINTDLGEX structure.
	LPPRINTDLG pPD = (LPPRINTDLG) GlobalAlloc(GPTR, sizeof(PRINTDLG));
	memset(pPD, 0, sizeof(PRINTDLG));

	//  Initialize the PRINTDLGEX structure.
	pPD->lStructSize = sizeof(PRINTDLG);
	pPD->Flags = PD_RETURNDC;
	if (fetchonly)
		pPD->Flags = pPD->Flags | PD_RETURNDEFAULT;

	if (PrintDlg(pPD) == TRUE)
	{
		const LPDEVMODE devmode = (LPDEVMODE)GlobalLock(pPD->hDevMode);
		const LPDEVNAMES devnames = (LPDEVNAMES)GlobalLock(pPD->hDevNames);
		LPCTSTR driver = LPCTSTR(devnames) + devnames->wDriverOffset;
		LPCTSTR device = LPCTSTR(devnames) + devnames->wDeviceOffset;
		LPCTSTR output = LPCTSTR(devnames) + devnames->wOutputOffset;

		pdriver.append(driver);
		pname.append(device);
		poutput.append(output);

		GlobalUnlock(pPD->hDevNames);
		GlobalUnlock(pPD->hDevMode);
	}

	GlobalFree(pPD);

	return 0;
}