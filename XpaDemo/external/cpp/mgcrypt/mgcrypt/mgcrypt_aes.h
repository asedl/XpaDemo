#pragma once

int AES_Encrypt(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszMode, char**lpszCiphertext, char* lpszIV);
int AES_Encrypt_ECB(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char**lpszCiphertext);

