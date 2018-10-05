# AES_Encrypt

AES_Encrypt is a Magic XPA program in xpacrypt component which demonstrates encryption with AES algorithm by using functionality from mgcrypt.dll. mgcrypt.dll uses Crypto++ library in order to implement most of the required functionality. More about AES encryption by Crypto++ library can be found here: [Advanced encryption standard](https://www.cryptopp.com/wiki/Advanced_encryption_standard) .  

## Parameters

AES_Encrypt has following parameters

### pi.Plaintext (Blob Binary)

Plaintext (data) / Message which should be encrypted

### pi.Keylength (Numeric)  

AES can use 16, 24, or 32 Byte keys (128, 192, 256 bits respectively). The default key length (when none resp. 0 is specified is 16)

### pi.Encyrption Key

Secret key which is used for the encryption. The length of this key has to match the value specified in parameter pi.Keylength (16, 24 or 32 Bytes), AES_Encrypt does however expect pi.EncryptionKey to be encoded with hexdigits so the length of the key passed in here as parameter will be actually pi.Keylength * 2 (since hexdigits encodes 4 Bit into one Byte of 8 bits).  

You can derive an encryption Key of required length from a secret (password, passphrase, ...) by invocation of program [AES_DeriveKey](./AES_DeriveKey.md). AES_Derive Key will also aready encode the key it derived from your passphrase with hexdigits so that you can use it as is for AES_Encrypt. More information about key derivation and some security aspects regarding key storage and exchange you can find here: (./)KeyConsiderations.md)  

### pio.IV

Some of the operation modes for AES encryption do require an initialization vector (IV) which is another piece of random data which is used to get a unique encryption result different from an encryption with no IV at all, or a different IV. This is to mitigate some attacks on your cipher text. The IV you need to store together with the encrypted data (ciphertext) and you do not need to keep it private.  

As with parameter pi.EncryptionKey the size of the IV needs to macth the specified keylength and AES_Encrypt expects the IV to be encoded with hexdigits. You can use program/function [AES_Random](./AES_Random.md) in order to get a random IV with required length, encoded with hexdigits.  

If you leave pi.IV empty and the selected mode of encryption requires aN IV then AES_Encrypt will generate the IV automatically from random data and return the value (encoded with hexdigits in parameter pi.IV). You need to store the value of this IV in order to be able to decrypt the result of the encryption.  

### pi.EncryptionMode (tEncryptionMode)

Encryption mode (mode of operation). Following is a list of possible values. Those modes which are not printed in bold below are listed here for the sake of completeness, may (and most likely are) not yet implemented. Specifying one of them will result in an error code <> 0 (and empty encryption result).  

- *ECB*
- *GCM*

### pi.Cipherencoding (tEncoding)

Result of an AES encryption is binary data which can be stored in a file. Often encrypted data is however exchanged by other means or as Text. For that purpose you can specify a encoding option in parameter pi.Cipherencodeing. Currently supported values for pi.Cipherencoding are:  

- NONE (no encoding)
- HEXDIGITS (concatenation of hexadecimal digits 0..F where each encodes 4 bit of the binary data)
- BASE64

### po.Ciphertext (Blob Binary)

Result of the AES encryption with specified encryption parameters  

### po.Error (tEncraptionError)

Numeric error code <> 0 in case of a problem

## Sample programs

Sample programs in xpacrypt application which do demonstrate usage of AES_Encrypt:

- [TST002_AES_Encrypt](./TST002_AES_Encrypt.md)
