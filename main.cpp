#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include "BigInteger.h"
#include "AES.h"

using namespace std;

int main()
{
	using AES_K = AES_256;

	string key = "0123456789abcdef0123456789abcdef";
	string text = "abcdefghijklmnopqrstuvwxyz";

	cout << key << endl << text << endl;

	cout << hex << setfill('0') << uppercase;

	cout << "Text: ";
	for (char c : text)
		cout << setw(2) << ((size_t)c & 0xFFu);
	cout << endl;

	cout << "Key: ";
	for (char c : key)
		cout << setw(2) << ((size_t)c & 0xFFu);
	cout << endl;

	string cipher = AES_K::Encrypt(text, key);

	cout << "Cipher: ";
	for (char c : cipher)
		cout << setw(2) << ((size_t)c & 0xFFu);
	cout << endl;

	cout << "Decrypted: ";
	string decrypted = AES_K::Decrypt(cipher, key);
	for (char c : decrypted)
		cout << setw(2) << ((size_t)c & 0xFFu);
	cout << endl;

	cout << nouppercase;

	cout << decrypted << endl;
}

//int main()
//{
//	const size_t gen_size = 64;
//
//	std::mt19937 gen;
//	std::uniform_int_distribution<size_t> rnd;
//
//	std::vector<size_t> n_data(gen_size / (sizeof(size_t) * 8));
//	for (size_t & num : n_data)
//		num = rnd(gen);
//
//	std::vector<size_t> g_data(gen_size / (sizeof(size_t) * 8));
//	for (size_t & num : g_data)
//		num = rnd(gen);
//
//	BigInteger n(n_data);
//	BigInteger g(g_data);
//	g %= n;
//
//
//
//	std::vector<size_t> a_data(gen_size / (sizeof(size_t) * 8));
//	for (size_t & num : a_data)
//		num = rnd(gen);
//
//	BigInteger a(a_data);
//	a %= n;
//
//
//	std::vector<size_t> b_data(gen_size / (sizeof(size_t) * 8));
//	for (size_t & num : b_data)
//		num = rnd(gen);
//
//	BigInteger b(b_data);
//	b %= n;
//
//	BigInteger ga = ModularExp(g, a, n);
//	cout << "ga is" << endl << ga << endl;
//
//	cout << endl;
//
//	BigInteger gb = ModularExp(g, b, n);
//	cout << "gb is" << endl << gb << endl;
//
//	cout << endl;
//
//	BigInteger gab1 = ModularExp(gb, a, n);
//	cout << "gab1 is" << endl << gab1 << endl;
//
//	cout << endl;
//
//	BigInteger gab2 = ModularExp(ga, b, n);
//	cout << "gab2 is" << endl << gab2 << endl;
//}

//int main()
//{
//	BigInteger a = 3;
//	BigInteger b = 100;
//	BigInteger n = 15;
//	BigInteger res = ModularExp(a, b, n);
//	cout << a << endl;
//	cout << b << endl;
//	cout << n << endl;
//	cout << res << endl;
//}

//int main()
//{
//	using AES_K = AES_256;
//
//	string key = "0123456789abcdef0123456789abcdef";
//	string text = "abcdefghijklmnopqrstuvwxyz";
//
//	cout << key << endl << text << endl;
//
//	cout << hex << setfill('0') << uppercase;
//
//	cout << "Text: ";
//	for (char c : text)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//
//	cout << "Key: ";
//	for (char c : key)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//
//	string cipher = AES_K::Encrypt(text, key);
//
//	cout << "Cipher: ";
//	for (char c : cipher)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//
//	cout << "Decrypted: ";
//	string decrypted = AES_K::Decrypt(cipher, key);
//	for (char c : decrypted)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//
//	cout << nouppercase;
//
//	cout << decrypted << endl;
//}

//#define o(y) std::byte(0x ## y)
//
//int main()
//{
////	vector<byte> v =
////		{
////			(byte)0x32, (byte)0x43, (byte)0xf6, (byte)0xa8,
////			(byte)0x88, (byte)0x5a, (byte)0x30, (byte)0x8d,
////			(byte)0x31, (byte)0x31, (byte)0x98, (byte)0xa2,
////			(byte)0xe0, (byte)0x37, (byte)0x07, (byte)0x34
////		};
////
////	vector<byte> k =
////		{
////			(byte)0x2b, (byte)0x7e, (byte)0x15, (byte)0x16,
////			(byte)0x28, (byte)0xae, (byte)0xd2, (byte)0xa6,
////			(byte)0xab, (byte)0xf7, (byte)0x15, (byte)0x88,
////			(byte)0x09, (byte)0xcf, (byte)0x4f, (byte)0x3c
////		};
////
////	auto res = AES_128::Encrypt(v, k);
////
////	cout << hex << setfill('0') << uppercase;
////
////	for (size_t i = 0; i < res.size(); ++i)
////		cout << setw(2) << to_integer<size_t>(res[i]) << " ";
//
//	string text = "abcdefghijklmnopqrstuvwxyz";
//	string key = "0123456789abcdef";
//	cout << text << "\n" << key << "\n";
//	string res = AES_128::Encrypt(text, key);
//	cout << hex << setfill('0') << uppercase;
//	for (char c : text)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//	for (char c : key)
//		cout << setw(2) << ((size_t)c & 0xFFu);
//	cout << endl;
//	for (size_t i = 0; i < res.size(); ++i)
//		cout << setw(2) << ((size_t)res[i] & 0xFFu);
//	cout << endl;
//
////	KeySchedule<16, 10> keys({ o(2b), o(7e), o(15), o(16), o(28), o(ae), o(d2), o(a6), o(ab), o(f7), o(15), o(88), o(09), o(cf), o(4f), o(3c)});
////
////	cout << hex << setfill('0');
////
////	for (size_t i = 0; i < keys.keys.size(); ++i)
////	{
////		for (size_t j = 0; j < keys.keys[i].size(); ++j)
////			cout << setw(2) << to_integer<size_t>(keys.keys[i][j]);
////		cout << "\n";
////	}
////
////	for (size_t i = 0; i < 11; ++i)
////	{
////		auto key = keys[i];
////		for (size_t j = 0; j < 16; ++j)
////			cout << setw(2) << to_integer<size_t>(key[j]);
////		cout << "\n";
////	}
//
////	aes.encrypt();
//
////	BigInteger n = { "10000000 00000000 00000000 00000000", 0b10 };
////	BigInteger k = { "10000000 00000000 00000000 00000000", 0b10 };
////	cout << n.pow(k) << endl;
//////	cout << BigInteger(2).pow(384) << endl;
//}