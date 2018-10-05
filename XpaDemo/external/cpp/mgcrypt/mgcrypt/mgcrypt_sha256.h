#pragma once

char* sha256_HexdigitsA(char* lpszData, size_t lInputLength, char* lpszSHA256Buffer, size_t lOutputLenghtMax);
char* AES_DeriveKey(char* lpszPassphrase, char* lpszIV, char* lpszKeyBuffer, size_t lKeybufferLength);
