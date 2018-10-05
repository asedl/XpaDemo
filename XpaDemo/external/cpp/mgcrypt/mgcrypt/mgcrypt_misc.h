#pragma once

int GenerateRandom(char** pRandomResult, const unsigned int blocksize);
int Hexencode(char* pRawData, char** pEncodingResult);
int Hexdecode(char* pHexencoded, char** pDecodingResult, size_t&);
int WriteBlobToTempfile(const std::vector<BYTE> &buffer, wstring& filename);
