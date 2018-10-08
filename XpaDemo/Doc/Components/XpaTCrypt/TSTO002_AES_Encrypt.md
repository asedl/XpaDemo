# TSTO002_AES_Encrypt

TSTO002_AES_Encrypt is an online (screen mode) Magic program which demonstrates some of the XpaTCrypt AES encryption/decryption functionality and features. AES (Advanced Encryption Standard), also known by it's original name Rijndael is a symmetric-key block cipher (encryption algorithm) which was chosen by the U.S. government to protect classiefied information in November 2001 and supersedes DES (Data encryption standard) which was in use before. It's implemented in hard- and software worldwide and for this and other reasons it's probably a good choice when you need to protect data with a symmetric-key encryption too.  

![TSTO002_AES_Encrypt](./assets/TSTO002_AES_Encrypt.png)
  
## Screen elements 
### Editfield: Encytion key
Here you can enter the (secret) key which is used for AES encryption, when you click one of the AES encryption buttons. AES is a symmetic key so the key is used for encryption and decryption. The key length has to match the block size which is chosen, for AES this is either 16 (default), 24 or 32 Bytes (128, 192 or 256 Bits respectively)  
> Note This first version of XpaTCrypt supports only 128 Bit for block- resp. keysize. Support for Key length 192 and 256 Bit will be added to a future version
  
If you type or paste a key to this field it will be automatically hexencoded to the field below (Encryption key hexencoded) since that's the format which is typically used for AES key exchange. This is only a textual representation of your (binary) key. Hexncoding does not encrypt your kea at all and its reversible.  

You can also derive a key for AES encryption from a password or a password phrase and thereby automatically get an encryption key of required length. For details see the explanation of button "Generate key from passphrase" below in this document. If you enter a key with a length different from the chosen AES blocksize/keylength you will get a warning when you try to use it for encryption/decryption.  

### Edit field IV / Salt
AES is basically only about the encryption of a single block. If you have data / plain text which is longer (or shorter) than this you need to choose a mode of operation / encryption mode. Some of them require an initialization vector IV in addition to the key. The IV needs to be random and undpredictable, unlike the encryption key it does however not have to be kept as a secret (after the encryption!). For more information see the links to additional information at the end of this document.  

When you enter a IV in this field it will be automatically hexencoded and if you choose to generate an encryption key from a passphrase an IV with required length wil be created and filled with random data. If you chosse to run AES in a mode which requires an IV you need to store it's value, if it's a mode which does not require an IV the value entered here is simply ignored. Sole pupose of an IV is to get a different encryption result when you encrypt data with your secret key in order to better protect from certain kind of attacks (dictionary attack, ...). Be however aware that it might not be needed to decrypt your message since it might (depending on encryption mode) only have an impact on the first block of the encryption result.  

### Key length (in Bytes)
Here you can specify keylength, resp. blocksize for AES encryption. Currently only 16 Bytes (128 Bit) is supported. Also check the notes for "Encryption key" above.  

### Encryption mode
Here you can choose the encryption mode (block cipher mode of oiperation) from a list of supported modes. For more information check the documentation about Encryption modes.

### Plaintext
Text / Data which you do want to encrypt

### Ciphertext
Result of the encryption (in hexadecimal representation)  

#### Button: AES Encrypt
Calls program XpaTCrypt.AES_Encrypt in order to AES encrypt the data in field "Plaintext"  

### Button: AES Decrypt
Calls program XpaTCrypt.AES_Decrypt in order to AES decrypt the data in field "Ciphertext". Before actual decryption the content of field Ciphertext will be hexdecoded and the result of that stored in a binary Blob.  

### Button: Encrypt (Magic)
Uses Magic's built-in Cipher() function to AES encrypt the data in field "Plaintext" (for testing purposes basically)  

### Button: Decrypt (Magic)
Uses Magic's built-in Decipher() function to AES decrypt the data in field "Ciphertext". Before the ectual decryption the value of field Ciphertext will be hexdecoded.  

### Save Plaintext (Blob)
Saves the content of field Plaintext to a file on disk. This is basically for testing purposes to reveal some problems around padding by looking into the result of the decryption with a hew viewer. On the bottom of the screen is a status field where the filename gets displayed which was chosen to save the Blob.  

### Edit field: Plaintext (hexencoded)
Here you can paste hexencoded text / data as you get it often by othere. f.i. in AES test vectors. The text entered here will be automatically hexdecoded and the result of that will be used to update the content of field "Plaintext".  

