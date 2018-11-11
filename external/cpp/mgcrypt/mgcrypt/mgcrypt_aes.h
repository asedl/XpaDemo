#pragma once

int AES_Encrypt(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszMode, char**lpszCiphertext, char* lpszIV);
int AES_Encrypt_ECB(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, string& encoded);
int AES_Encrypt_CBC(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszIV, string& encoded);
int AES_Decrypt_CBC(const char* lpszCiphertext, long lpdwCiphertextLength, char* lpszKey, char* lpszIV, string& plaintext);
int AES_Encrypt_CFB(const char* lpszPlaintext, long lpdwPlaintextLength, char* lpszKey, char* lpszIV, string& ciphertext);
int AES_Decrypt_CFB(const char* lpszCiphertext, long lpdwCiphertextLength, char* lpszKey, char* lpszIV, string& plaintext);



