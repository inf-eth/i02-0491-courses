#include <cstdlib>
#include <OpenSSLCli.h>

int main (int argc, char **argv)
{
	char choice;
	while (true)
	{	
		//system ("clear");
		cout << "===================== Main Menu ========================" << endl;
		cout << "1. Compute hash (e.g. sha1, md5) of an input file." << endl;
		cout << "2. Sign a file using RSA/DSA private key." << endl;
		cout << "3. Symmetric Encryption (e.g. aes, des, des3)." << endl;
		cout << "4. Symmetric Decryption." << endl;
		cout << "5. base64 encode." << endl;
		cout << "6. base64 decode." << endl;
		cout << "e. Exit." << endl;
		cout << "========================================================" << endl;
		cout << "Enter a choice: ";
		cin >> choice;
	
		switch (choice)
		{
			case '1':
			{
				string hashtype, hashfileout, filein;
				cout << "Enter hash type (e.g. sha1): ";
				cin >> hashtype;
				cout << "Enter output hash file ('.' for stdout): ";
				cin >> hashfileout;
				cout << "Enter input file: ";
				cin >> filein;
			
				OpenSSL_dgst (hashtype, hashfileout, filein);
				break;
			}
			case '3':
			{
				string cipher, plaintextfilein, ciphertextfileout;
				cout << "Enter cipher with modes (e.g. aes256, des, des3, des3-ede-ofb): ";
				cin >> cipher;
				cout << "Enter input plaintext file: ";
				cin >> plaintextfilein;
				cout << "Enter output ciphertext file: ";
				cin >> ciphertextfileout;
			
				OpenSSL_enc (cipher, plaintextfilein, ciphertextfileout);
				break;
			}
			case '4':
			{
				string cipher, ciphertextfilein, plaintextfileout;
				cout << "Enter cipher with modes (e.g. aes256, des, des3, des3-ede-ofb): ";
				cin >> cipher;
				cout << "Enter input ciphertext file: ";
				cin >> ciphertextfilein;
				cout << "Enter output plaintext file: ";
				cin >> plaintextfileout;
			
				OpenSSL_dec (cipher, ciphertextfilein, plaintextfileout);
				break;
			}
			case '5':
			{
				string ciphertextbinfilein, base64txtfileout;
				cout << "Enter the binary ciphertext file: ";
				cin >> ciphertextbinfilein;
				cout << "Enter base64 output text file: ";
				cin >> base64txtfileout;
				
				OpenSSL_base64encode (ciphertextbinfilein, base64txtfileout);
				break;
			}
			case '6':
			{
				string base64txtfilein, ciphertextbinfileout;
				cout << "Enter base64 input text file: ";
				cin >> base64txtfilein;
				cout << "Enter the output binary ciphertext file: ";
				cin >> ciphertextbinfileout;
				
				OpenSSL_base64encode (base64txtfilein, ciphertextbinfileout);
				break;
			}
			case 'e':
			{
				return 0;
			}
			default:
			{
				break;
			}		
		}
	}
	return -1;
}
