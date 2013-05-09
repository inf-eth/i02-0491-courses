#include <string>
#include <fstream>
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

/* Compute message digest.
First argument is hash type, e.g. sha1.
Second argument is output file, an empty filename will output to stdout.
Third argument is input file whose hash is to be computed.
*/
int OpenSSL_dgst (string, string, string);

/* Sign message digest.
Frist argument is hash type, e.g. sha1 for RSA and dss1 for DSA.
Second argument is the filename containing private key.
Third argument is the output filename which will contain the signature.
Fourth argument is the input file whose hash is to be computed and signed.
*/
int OpenSSL_dgst_sign (string, string, string, string);

/* Symmetric Encryption.
arg1 = cipher e.g., aes256, des, des3.
arg2 = plaintext input file.
arg3 = ciphertext output file.
*/
int OpenSSL_enc (string, string, string);

/* Symmetric Decryption.
arg1 = cipher e.g., aes256, des, des3.
arg2 = ciphertext input file.
arg3 = plaintext output file.
*/
int OpenSSL_dec (string, string, string);

/* base64 encode
Takes input ciphertext in binary mode and outputs text file
*/
int OpenSSL_base64encode (string, string);

/* base64 decode
Takes input base64 encoded file and outputs binary ciphertext file.
*/
int OpenSSL_base64decode (string, string);
