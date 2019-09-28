#ifndef ASPRISE_OCR_API_H
#define ASPRISE_OCR_API_H

/** 
 * Asprise OCR API for C/C++: ALL RIGHTS RESERVED (c) Asprise.com
 * 
 * Read <a href = "http://asprise.com/ocr/docs/html/?src=c_cpp">developer's guide to C/C++ OCR SDK API</a>.
 * 
 * For evaluation only: 
 * 1) Using this file with or without modification in any application is strictly prohibited unless you 
 *    have obtained a license from Asprise.
 *
 * 2) Distributing this file in any way is prohibited.
 *
 * Visit <a href="http://asprise.com/royalty-free-library/c-c++-ocr-sdk-api-overview.html">Asprise OCR SDK C/C++ API</a>
 */

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#define CALL_CONVENTION __stdcall
#include <Windows.h>
#else
#define EXPORT_API
#define CALL_CONVENTION
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define OCR_SPEED_FASTEST "fastest"
#define OCR_SPEED_FAST "fast"
#define OCR_SPEED_SLOW "slow"

#define OCR_RECOGNIZE_TYPE_TEXT "text"
#define OCR_RECOGNIZE_TYPE_BARCODE "barcode"
#define OCR_RECOGNIZE_TYPE_ALL "all"

#define OCR_OUTPUT_FORMAT_PLAINTEXT "text"
#define OCR_OUTPUT_FORMAT_XML "xml"
#define OCR_OUTPUT_FORMAT_PDF "pdf"
#define OCR_OUTPUT_FORMAT_RTF "rtf"

//#define OCR_PROP_INCLUDE_EMPTY_BLOCK "PROP_INCLUDE_EMPTY_BLOCK"

#define OCR_PROP_LIMIT_TO_CHARSET "PROP_LIMIT_TO_CHARSET"

#define OCR_PROP_PAGE_TYPE "PROP_PAGE_TYPE"
#define OCR_PROP_PAGE_TYPE_AUTO_DETECT "auto"
#define OCR_PROP_PAGE_TYPE_SINGLE_BLOCK "single_block"
#define OCR_PROP_PAGE_TYPE_SINGLE_COLUMN "single_column"
#define OCR_PROP_PAGE_TYPE_SINGLE_LINE "single_line"
#define OCR_PROP_PAGE_TYPE_SINGLE_WORD "single_word"
#define OCR_PROP_PAGE_TYPE_SINGLE_CHARACTOR "single_char"
#define OCR_PROP_PAGE_TYPE_SCATTERED "scattered"

#define OCR_PROP_OUTPUT_SEPARATE_WORDS "PROP_OUTPUT_SEPARATE_WORDS"

/** The DPI to be used to render the PDF file; default is 300 if not specified */
#define OCR_PROP_INPUT_PDF_DPI "PROP_INPUT_PDF_DPI"

// -------- Dictionary related ---------
/** set to 'true' to skip using the default built in dict. Default value: 'false' */
#define OCR_START_PROP_DICT_SKIP_BUILT_IN_DEFAULT "START_PROP_DICT_SKIP_BUILT_IN_DEFAULT"
/** set to 'true' to skip using all built-in dicts. Default value: 'false' */
#define OCR_START_PROP_DICT_SKIP_BUILT_IN_ALL "START_PROP_DICT_SKIP_BUILT_IN_ALL"
/** Path to your custom dictionary (words are separated using line breaks). Default value: null */
#define OCR_START_PROP_DICT_CUSTOM_DICT_FILE "START_PROP_DICT_CUSTOM_DICT_FILE" 
/** Path to your custom templates (templates are separated using line breaks). Default value: null */
#define OCR_START_PROP_DICT_CUSTOM_TEMPLATES_FILE "START_PROP_DICT_CUSTOM_TEMPLATES_FILE" 

/** Percentage measuring the importance of the dictionary (0: not at all; 100: extremely important; default: 10) */
#define OCR_PROP_DICT_DICT_IMPORTANCE "PROP_DICT_DICT_IMPORTANCE"

// -------- PDF output related ---------

#define OCR_PROP_PDF_OUTPUT_FILE "PROP_PDF_OUTPUT_FILE"
#define OCR_PROP_PDF_OUTPUT_IMAGE_DPI "PROP_PDF_OUTPUT_IMAGE_DPI"
#define OCR_PROP_PDF_OUTPUT_FONT "PROP_PDF_OUTPUT_FONT"
#define OCR_PROP_PDF_OUTPUT_TEXT_VISIBLE "PROP_PDF_OUTPUT_TEXT_VISIBLE"
#define OCR_PROP_PDF_OUTPUT_IMAGE_FORCE_BW "PROP_PDF_OUTPUT_IMAGE_FORCE_BW"

#define OCR_PROP_PDF_OUTPUT_PDFA "PROP_PDF_OUTPUT_PDFA"
#define OCR_PROP_PDF_OUTPUT_PDFA_FONT_FILE "PROP_PDF_OUTPUT_PDFA_FONT_FILE"

/** Text recognized below or above confidence will be highlighted in different colors. */
#define OCR_PROP_PDF_OUTPUT_CONF_THRESHOLD "PROP_PDF_OUTPUT_CONF_THRESHOLD"

/** Return text in 'text' or 'xml' format */
#define OCR_PROP_PDF_OUTPUT_RETURN_TEXT "PROP_PDF_OUTPUT_RETURN_TEXT"

// -------- RTF output related ---------

#define OCR_PROP_RTF_OUTPUT_FILE "PROP_RTF_OUTPUT_FILE"

/** Return text in 'text' or 'xml' format */
#define OCR_PROP_RTF_OUTPUT_RETURN_TEXT "PROP_RTF_OUTPUT_RETURN_TEXT"

/** default is LETTER, may set to A4. */
#define OCR_PROP_RTF_PAPER_SIZE "PROP_RTF_PAPER_SIZE"

/** set to false to disable rendering table cells borders into black. Default is true. */
#define OCR_PROP_RTF_SHOW_TABLE_CELL_BORDER "PROP_RTF_SHOW_TABLE_CELL_BORDER"

// -------- image processing related ---------

/** Image pre-processing type */
#define OCR_PROP_IMG_PREPROCESS_TYPE "PROP_IMG_PREPROCESS_TYPE"
#define OCR_PROP_IMG_PREPROCESS_TYPE_DEFAULT "default"
#define OCR_PROP_IMG_PREPROCESS_TYPE_DEFAULT_WITH_ORIENTATION_DETECTION "default_with_orientation_detection"
#define OCR_PROP_IMG_PREPROCESS_TYPE_CUSTOM "custom"

/** Image pre-processing command */
#define OCR_PROP_IMG_PREPROCESS_CUSTOM_CMDS "PROP_IMG_PREPROCESS_CUSTOM_CMDS"

// -------- table related ---------
/** table will be detected by default; set this property to true to skip detection. */
#define OCR_PROP_TABLE_SKIP_DETECTION "PROP_TABLE_SKIP_DETECTION"

/** default is 32 if not specified */
#define OCR_PROP_TABLE_MIN_SIDE_LENGTH "PROP_TABLE_MIN_SIDE_LENGTH"

/** Save intermediate images generated for debug purpose - don't specify or empty string to skip saving */
#define OCR_PROP_SAVE_INTERMEDIATE_IMAGES_TO_DIR "PROP_SAVE_INTERMEDIATE_IMAGES_TO_DIR"

/** Set to true if there is only one image per page on the input PDF file; potentially speed up of the process */
#define OCR_PROP_INPUT_PDF_SINGLE_IMG_PER_PAGE "PROP_INPUT_PDF_SINGLE_IMG_PER_PAGE"

// ------------------------- Functions exposed -------------------------
/** Returns the version of the library. */
EXPORT_API const char * CALL_CONVENTION com_asprise_ocr_version();

/** Returns 0 if setup required; 1 if setup has been done; or negative error code. */
EXPORT_API int CALL_CONVENTION com_asprise_ocr_setup(bool queryOnly);

/** Call after setup; list all supported langs separated by comma; please delete returned char[] after use. */
EXPORT_API char * CALL_CONVENTION com_asprise_ocr_list_supported_langs();

/** returns the ocr engine handle or negative error code. */
EXPORT_API long long CALL_CONVENTION com_asprise_ocr_start(const char * lang, const char * speed, const char * propSpec, const char * propSeparator, const char * propKeyValueSpeparator);

/** returns the recognized text or error message in format like '<error: ...' */
EXPORT_API char * CALL_CONVENTION com_asprise_ocr_recognize
(long long handle, const char * imgFiles, int pageIndex, int startX, int startY, int width, int height, const char * recognizeType, const char * outputFormat, const char * propSpec, const char * propSeparator, const char * propKeyValueSpeparator);

/** Destroies the OCR engine. */
EXPORT_API void CALL_CONVENTION com_asprise_ocr_stop(long long handle);

/** Inputs the license information */
EXPORT_API void CALL_CONVENTION com_asprise_ocr_input_license(const char * licenseeName, const char * licenseCode);

/** Util function that perform C delete/delete[] */
EXPORT_API void CALL_CONVENTION com_asprise_ocr_util_delete(long long handle, bool isArray);

// pyd
/** call setup */
EXPORT_API void CALL_CONVENTION initaocr(void);
EXPORT_API void CALL_CONVENTION initaocr_x64(void);

#ifdef __cplusplus
}
#endif

// ------------------------- Run-time Dynamic Linking -------------------------
#ifndef SKIP_AOCR_DYNAMIC
typedef void(*FUNC_TYPE)(void *);
#ifdef _WIN32
	typedef HMODULE LIBRARY_HANDLE;
	#define snprintf _snprintf
#else
	typedef void * LIBRARY_HANDLE;
#endif

#if defined(_WIN32) && !defined(_WIN64)
#define FUNC_NAME_com_asprise_ocr_version		"_com_asprise_ocr_version@0"
#define FUNC_NAME_com_asprise_ocr_setup			"_com_asprise_ocr_setup@4"
#define FUNC_NAME_com_asprise_ocr_list_supported_langs "_com_asprise_ocr_list_supported_langs@0"
#define FUNC_NAME_com_asprise_ocr_start			"_com_asprise_ocr_start@20"
#define FUNC_NAME_com_asprise_ocr_stop			"_com_asprise_ocr_stop@8"
#define FUNC_NAME_com_asprise_ocr_recognize		"_com_asprise_ocr_recognize@52"
#define FUNC_NAME_com_asprise_ocr_util_delete	"_com_asprise_ocr_util_delete@12"
#define FUNC_NAME_com_asprise_ocr_input_license "_com_asprise_ocr_input_license@8"
#else
#define FUNC_NAME_com_asprise_ocr_version		"com_asprise_ocr_version"
#define FUNC_NAME_com_asprise_ocr_setup			"com_asprise_ocr_setup"
#define FUNC_NAME_com_asprise_ocr_list_supported_langs "com_asprise_ocr_list_supported_langs"
#define FUNC_NAME_com_asprise_ocr_start			"com_asprise_ocr_start"
#define FUNC_NAME_com_asprise_ocr_stop			"com_asprise_ocr_stop"
#define FUNC_NAME_com_asprise_ocr_recognize		"com_asprise_ocr_recognize"
#define FUNC_NAME_com_asprise_ocr_util_delete	"com_asprise_ocr_util_delete"
#define FUNC_NAME_com_asprise_ocr_input_license "com_asprise_ocr_input_license"
#endif

	typedef const char * (CALL_CONVENTION * func_type_com_asprise_ocr_version) ();
	typedef int(CALL_CONVENTION * func_type_com_asprise_ocr_setup) (bool);
	typedef char * (CALL_CONVENTION * func_type_com_asprise_ocr_list_supported_langs) ();
	typedef long long(CALL_CONVENTION * func_type_com_asprise_ocr_start) (const char *, const char *, const char *, const char *, const char *);
	typedef void(CALL_CONVENTION * func_type_com_asprise_ocr_stop) (long long);
	typedef char * (CALL_CONVENTION * func_type_com_asprise_ocr_recognize) (long long, const char *, int, int, int, int, int, const char *, const char *, const char *, const char *, const char *);
	typedef void(CALL_CONVENTION * func_type_com_asprise_ocr_util_delete) (long long, bool);
	typedef void(CALL_CONVENTION * func_type_com_asprise_ocr_input_license) (const char *, const char *);

	func_type_com_asprise_ocr_input_license func_com_asprise_ocr_input_license = NULL;
	func_type_com_asprise_ocr_list_supported_langs func_com_asprise_ocr_list_supported_langs = NULL;
	func_type_com_asprise_ocr_recognize func_com_asprise_ocr_recognize = NULL;
	func_type_com_asprise_ocr_setup func_com_asprise_ocr_setup = NULL;
	func_type_com_asprise_ocr_start func_com_asprise_ocr_start = NULL;
	func_type_com_asprise_ocr_stop func_com_asprise_ocr_stop = NULL;
	func_type_com_asprise_ocr_util_delete func_com_asprise_ocr_util_delete = NULL;
	func_type_com_asprise_ocr_version func_com_asprise_ocr_version = NULL;

	bool checkIfFuncFound(bool funcFound, const char * funcName) {
		if (funcFound) {
			return true;
		} else {
			printf("ERROR: Failed to look up function in the library: %s\n", funcName);
			return false;
		}
	}

	/** Dynamically load aocr library; return the loaded library handle or NULL if failed.  */
	LIBRARY_HANDLE dynamic_load_aocr_library(const char * pathToFolderContainingAocrLibrary) {
		LIBRARY_HANDLE handle = NULL;
		char libFilePath[256];
		bool isWindows = false;
	#ifdef WIN32
		#ifdef _WIN64
		const char * libName = "aocr_x64.dll";
		#else
		const char * libName = "aocr.dll";
		#endif
		isWindows = true;
	#else
		#ifdef __APPLE__
			const char * libName = "libaocr_x64.dylib";
		#else
			#if defined(__LP64__) || defined(_LP64)
				const char * libName = "libaocr_x64.so";
			#else
				const char * libName = "libaocr.so";
			#endif
		#endif
		isWindows = false;
	#endif

		const char * separator = strlen(pathToFolderContainingAocrLibrary) > 0 && (pathToFolderContainingAocrLibrary[strlen(pathToFolderContainingAocrLibrary) - 1] == '/' || pathToFolderContainingAocrLibrary[strlen(pathToFolderContainingAocrLibrary) - 1] == '\\')
			? "" : "/";
		snprintf(libFilePath, 256, "%s%s%s", pathToFolderContainingAocrLibrary, separator, libName);
		for (size_t i = 0; i < strlen(libFilePath); i++) { // correct slash directions
			if (libFilePath[i] == '/' || libFilePath[i] == '\\') {
				libFilePath[i] = isWindows ? '\\' : '/';
			}
		}

	#ifdef WIN32
		handle = LoadLibraryA(libFilePath);
		if(handle == NULL) {
			printf("ERROR: GetLastError() returns: %lu\n", GetLastError());
			return NULL;
		}
		func_com_asprise_ocr_input_license = (func_type_com_asprise_ocr_input_license) GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_input_license);
		func_com_asprise_ocr_list_supported_langs = (func_type_com_asprise_ocr_list_supported_langs)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_list_supported_langs);
		func_com_asprise_ocr_recognize = (func_type_com_asprise_ocr_recognize)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_recognize);
		func_com_asprise_ocr_setup = (func_type_com_asprise_ocr_setup)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_setup);
		func_com_asprise_ocr_start = (func_type_com_asprise_ocr_start)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_start);
		func_com_asprise_ocr_stop = (func_type_com_asprise_ocr_stop)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_stop);
		func_com_asprise_ocr_util_delete = (func_type_com_asprise_ocr_util_delete)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_util_delete);
		func_com_asprise_ocr_version = (func_type_com_asprise_ocr_version)GetProcAddress(handle, FUNC_NAME_com_asprise_ocr_version);
	#else
		handle = dlopen(libFilePath, RTLD_LAZY);
		if (handle == NULL) {
			printf("ERROR: dlerror(): %s\n", dlerror());
			return NULL;
		}
		func_com_asprise_ocr_input_license = (func_type_com_asprise_ocr_input_license)dlsym(handle, FUNC_NAME_com_asprise_ocr_input_license);
		func_com_asprise_ocr_list_supported_langs = (func_type_com_asprise_ocr_list_supported_langs)dlsym(handle, FUNC_NAME_com_asprise_ocr_list_supported_langs);
		func_com_asprise_ocr_recognize = (func_type_com_asprise_ocr_recognize)dlsym(handle, FUNC_NAME_com_asprise_ocr_recognize);
		func_com_asprise_ocr_setup = (func_type_com_asprise_ocr_setup)dlsym(handle, FUNC_NAME_com_asprise_ocr_setup);
		func_com_asprise_ocr_start = (func_type_com_asprise_ocr_start)dlsym(handle, FUNC_NAME_com_asprise_ocr_start);
		func_com_asprise_ocr_stop = (func_type_com_asprise_ocr_stop)dlsym(handle, FUNC_NAME_com_asprise_ocr_stop);
		func_com_asprise_ocr_util_delete = (func_type_com_asprise_ocr_util_delete)dlsym(handle, FUNC_NAME_com_asprise_ocr_util_delete);
		func_com_asprise_ocr_version = (func_type_com_asprise_ocr_version)dlsym(handle, FUNC_NAME_com_asprise_ocr_version);
	#endif
		if (handle == NULL) {
			printf("ERROR: failed to dynamically load the library: %s\nMake sure it exists. Contact support@asprise.com if you need any assistance.\n", libFilePath);
		}

		if (checkIfFuncFound(func_com_asprise_ocr_input_license != NULL, FUNC_NAME_com_asprise_ocr_input_license) &&
			checkIfFuncFound(func_com_asprise_ocr_list_supported_langs != NULL, FUNC_NAME_com_asprise_ocr_list_supported_langs) &&
			checkIfFuncFound(func_com_asprise_ocr_recognize != NULL, FUNC_NAME_com_asprise_ocr_recognize) &&
			checkIfFuncFound(func_com_asprise_ocr_setup != NULL, FUNC_NAME_com_asprise_ocr_setup) &&
			checkIfFuncFound(func_com_asprise_ocr_start != NULL, FUNC_NAME_com_asprise_ocr_start) &&
			checkIfFuncFound(func_com_asprise_ocr_stop != NULL, FUNC_NAME_com_asprise_ocr_stop) &&
			checkIfFuncFound(func_com_asprise_ocr_util_delete != NULL, FUNC_NAME_com_asprise_ocr_util_delete) &&
			checkIfFuncFound(func_com_asprise_ocr_version != NULL, FUNC_NAME_com_asprise_ocr_version)) {
			// all found
		}
		else {
			printf("ERROR: at lease one function is not found in the library.\n");
			return NULL;
		}

		return handle;
	}

	/** unload aocr library; return true if successful or false if failed. */
	bool dynamic_unload_aocr_library(LIBRARY_HANDLE handle) {
		int errorCode = 0;
		if (handle == NULL) {
			return false;
		}
#ifdef WIN32
		return FreeLibrary(handle) != 0;
#else
		errorCode = dlclose(handle);
		if(errorCode != 0) {
			printf("dlclose() returns error code: %d\n", errorCode);
		}
		return errorCode == 0;
#endif
	}

	bool assertFuncExists(bool exists) {
		if (exists) {
			return true;
		} else {
			printf("Function is NULL. Please call dynamic_load_aocr_library first.\n");
			return false;
		}
	}

	/** Returns the version of the library. */
	const char * c_com_asprise_ocr_version() {
		if (!assertFuncExists(func_com_asprise_ocr_version != NULL)) {
			return NULL;
		}
		return func_com_asprise_ocr_version();
	}

	/** Returns 0 if setup required; 1 if setup has been done; or negative error code. */
	int CALL_CONVENTION c_com_asprise_ocr_setup(bool queryOnly) {
		if (!assertFuncExists(func_com_asprise_ocr_setup != NULL)) {
			return 0;
		}
		return func_com_asprise_ocr_setup(queryOnly);
	}

	/** Call after setup; list all supported langs separated by comma; please delete returned char[] after use. */
	char * c_com_asprise_ocr_list_supported_langs() {
		if (!assertFuncExists(func_com_asprise_ocr_list_supported_langs != NULL)) {
			return NULL;
		}
		return func_com_asprise_ocr_list_supported_langs();
	}

	/** returns the ocr engine handle or negative error code. */
	long long c_com_asprise_ocr_start(const char * lang, const char * speed, const char * propSpec, const char * propSeparator, const char * propKeyValueSpeparator) {
		if (!assertFuncExists(func_com_asprise_ocr_start != NULL)) {
			return 0;
		}
		return func_com_asprise_ocr_start(lang, speed, propSpec, propSeparator, propKeyValueSpeparator);
	}

	/** returns the recognized text or error message in format like '<error: ...' */
	char * c_com_asprise_ocr_recognize
		(long long handle, const char * imgFiles, int pageIndex, int startX, int startY, int width, int height, const char * recognizeType, const char * outputFormat, const char * propSpec, const char * propSeparator, const char * propKeyValueSpeparator) {
		if (!assertFuncExists(func_com_asprise_ocr_recognize != NULL)) {
			return NULL;
		}
		return func_com_asprise_ocr_recognize(handle, imgFiles, pageIndex, startX, startY, width, height, recognizeType, outputFormat, propSpec, propSeparator, propKeyValueSpeparator);
	}

	/** Destroys the OCR engine. */
	void c_com_asprise_ocr_stop(long long handle) {
		if (!assertFuncExists(func_com_asprise_ocr_stop != NULL)) {
			return;
		}
		func_com_asprise_ocr_stop(handle);
	}

	/** Inputs the license information */
	void c_com_asprise_ocr_input_license(const char * licenseeName, const char * licenseCode) {
		if (!assertFuncExists(func_com_asprise_ocr_input_license != NULL)) {
			return;
		}
		func_com_asprise_ocr_input_license(licenseeName, licenseCode);
	}

	/** Util function that perform C delete/delete[] */
	void c_com_asprise_ocr_util_delete(long long handle, bool isArray) {
		if (!assertFuncExists(func_com_asprise_ocr_util_delete != NULL)) {
			return;
		}
		func_com_asprise_ocr_util_delete(handle, isArray);
	}

	/**
	// ==== Sample program: testocr.cpp - runs on Windows, Linux and Mac OS X. 
	// 1) Download aocr libraries:
	//  - For Windows:  Download http://asprise.com/ocr/files/downloads/latest/lib/aocr.dll (32bit) and/or http://asprise.com/ocr/files/downloads/latest/lib/aocr_x64.dll (64bit)
	//  - For Linux:    wget http://asprise.com/ocr/files/downloads/latest/lib/libaocr.so; wget http://asprise.com/ocr/files/downloads/latest/lib/libaocr_x64.so
	//  - For Mac OS X: curl -O http://asprise.com/ocr/files/downloads/latest/lib/libaocr_x64.dylib
	//
	// 2) Compile and run - save the sample code as 'testocr.cpp' then:
	//  - For Windows:  cl testocr.cpp & testocr.exe  (you may need to run in VS Tools Command Prompt)
	//  - For Unix:     g++ testocr.cpp -ldl; ./a.out

	#include <iostream>
	#include "asprise_ocr_api.h"

	using namespace std;

	void testOcr() {
		const char * libFolder = "PATH/TO/LIB/FOLDER";   // CHANGE TO THE REAL PATH - where the aocr.dll or aocr.so locates
		const char * fileImg = "PATH/TO/image.png"; // CHANGE TO THE REAL PATH - the input image, can be jpeg, gif, png, tiff or pdf.

		LIBRARY_HANDLE libHandle = dynamic_load_aocr_library(libFolder);
		cout << "Version: " << c_com_asprise_ocr_version() << endl;

		int setup = c_com_asprise_ocr_setup(false);
		if (setup != 1) {
			cerr << "Failed to setup. code: " << setup << endl;
			return;
		}

		// must be of long long type
		long long ptrToApi = c_com_asprise_ocr_start("eng", OCR_SPEED_FAST, NULL, NULL, NULL);
		if (ptrToApi == 0) {
			cerr << "Failed to start." << endl;
			return;
		}

		cout << "OCR engine started. " << endl;

		char * s = c_com_asprise_ocr_recognize(ptrToApi, fileImg, -1, -1, -1, -1, -1, OCR_RECOGNIZE_TYPE_ALL, OCR_OUTPUT_FORMAT_PDF,
			"PROP_PDF_OUTPUT_FILE=result.pdf,PROP_PDF_OUTPUT_TEXT_VISIBLE=true,PROP_PDF_OUTPUT_IMAGE_FORCE_BW=true,PROP_OUTPUT_SEPARATE_WORDS=false,PROP_PDF_OUTPUT_RETURN_TEXT=text", ",", "=");

		cout << "Returned: " << s << std::endl;

		c_com_asprise_ocr_stop(ptrToApi);

		cout << "Unload: " << (dynamic_unload_aocr_library(libHandle) ? "OK" : "Failed") << endl;
	}

	int main() {
		testOcr();

		std::cout << "Press ENTER to exit: ";
		std::cin.ignore();
		return 0;
	}
	// ====
	*/

#endif // #ifndef SKIP_AOCR_DYNAMIC

#endif // ASPRISE_OCR_API_H