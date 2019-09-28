//
// Copyright (c) 2018 Andreas Sedlmeier (sedlmeier@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
#include "stdafx.h"

#include <iostream>
#include "asprise_ocr_api.h"
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int testOcr(wchar_t* filenameImage) {

	// CHANGE TO THE ACTUAL PATH to the folder where the aocr.dll or aocr.so locates in
	const char* libFolder = "LIB_FOLDER";

	// CHANGE TO THE ACTUAL PATH to the input image, can be jpeg, gif, png, tiff or pdf.
	const char* fileImg = "PATH/image.png";

	vector<wchar_t> pathBuf;
	DWORD copied = 0;
	do {
		pathBuf.resize(pathBuf.size() + MAX_PATH);
		copied = GetModuleFileName(0, &pathBuf.at(0), pathBuf.size());
	} while (copied >= pathBuf.size());
	pathBuf.resize(copied);
	wstring path(pathBuf.begin(), pathBuf.end());
	std::filesystem::path pathObj(path);
	pathObj.remove_filename();


	char mbbuff[MAX_PATH + 1];
	int retVal = wcstombs(mbbuff, pathObj.c_str(), copied);
	mbbuff[copied] = 0;
	LIBRARY_HANDLE h = dynamic_load_aocr_library(mbbuff);

	// one time setup
	int setup = c_com_asprise_ocr_setup(false);
	if (setup != 1) {
		cerr << "Failed to setup. code: " << setup << endl;
		return 0;
	}

	// starts the ocr engine; the pointer must be of long long type
	long long ptrToApi = c_com_asprise_ocr_start("eng", OCR_SPEED_FAST, NULL, NULL, NULL);
	if (ptrToApi == 0) {
		cerr << "Failed to start." << endl;
		return 0;
	}
	


	std::wstring wstrImageFile(filenameImage);
	std::string cstrImageFile (wstrImageFile.begin(), wstrImageFile.end());
	char* s = c_com_asprise_ocr_recognize(ptrToApi, cstrImageFile.c_str(), -1, -1, -1, -1, -1,
		OCR_RECOGNIZE_TYPE_ALL, OCR_OUTPUT_FORMAT_PLAINTEXT,
		"PROP_PDF_OUTPUT_FILE=result.pdf|PROP_PDF_OUTPUT_TEXT_VISIBLE=true|\
      PROP_PDF_OUTPUT_RETURN_TEXT=text", "|", "=");

	cout << "Returned: " << s << endl;

	std::ofstream out("output.txt");
	out << s;
	out.close();



	// do more recognition here ...

	// finally, stops the OCR engine.
	c_com_asprise_ocr_stop(ptrToApi);

	cout << "Unload: " << (dynamic_unload_aocr_library(h) ? "OK" : "Failed") << endl;

	return 0;
}

