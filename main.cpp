#include <iostream>
#include <iomanip>
#include <string>

#include "AES.h"

using namespace std;

int main()
{
	string key;
	string text;

	getline(cin, key);

	while (key.size() != 16 && key.size() != 24 && key.size() != 32)
	{
		clog << "Invalid key, please input key again.\n";
		getline(cin, key);
	}

	getline(cin, text);

	clog << hex << setfill('0') << uppercase;

	clog << "Key: ";
	for (char c : key)
		clog << setw(2) << ((size_t)c & 0xFFu);
	clog << endl;

	clog << "Text: ";
	for (char c : text)
		clog << setw(2) << ((size_t)c & 0xFFu);
	clog << endl;

	string cipher;

	switch (key.size())
	{
	case 16:
		cipher = AES_128::Encrypt(text, key);
		break;
	case 24:
		cipher = AES_192::Encrypt(text, key);
		break;
	case 32:
		cipher = AES_256::Encrypt(text, key);
		break;
	default:
		break;
	}

	clog << "Cipher: ";
	for (char c : cipher)
		clog << setw(2) << ((size_t)c & 0xFFu);
	clog << endl;

	clog << "Decrypted: ";
	string decrypted;
	switch (key.size())
	{
	case 16:
		decrypted = AES_128::Decrypt(cipher, key);
		break;
	case 24:
		decrypted = AES_192::Decrypt(cipher, key);
		break;
	case 32:
		decrypted = AES_256::Decrypt(cipher, key);
		break;
	default:
		break;
	}
	for (char c : decrypted)
		clog << setw(2) << ((size_t)c & 0xFFu);
	clog << endl;

	clog << nouppercase;

	clog << decrypted << endl;
}
