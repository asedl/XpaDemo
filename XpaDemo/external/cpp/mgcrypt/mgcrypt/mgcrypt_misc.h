#pragma once

int GenerateRandom(char** pRandomResult, const unsigned int blocksize);
char* DeriveKey(char* lpszPassphrase, char* lpszIV, char* lpszKeyBuffer, size_t lKeybufferLength, size_t Keylength);
int Hexencode(char* pRawData, char** pEncodingResult);
int Hexdecode(char* pHexencoded, char** pDecodingResult, size_t&);
int WriteBlobToTempfile(const std::vector<BYTE> &buffer, wstring& filename);
int GetTempfilename(wchar_t* szTempfilename);
