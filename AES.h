#pragma once

#include "SBox.h"
#include "RowShifter.h"
#include "ColumnMixer.h"

#include "KeySchedule.h"

#include "Block.h"

#include "InvalidKeySize.h"

#include <cstddef>
#include <array>
#include <string>

template<size_t KeySize = 16, size_t Rounds = 10>
class AES
{
	static SBox subByte;
	static RowShifter shiftRow;
	static ColumnMixer mixColumns;
	static ColumnMixer_Inverse invMixColumns;
	static RowShifter_Inverse invShiftRow;
	static SBox_Inverse invSubByte;
public:
	static Block<std::byte, 16> Encrypt(const Block<std::byte, 16> & input, const Block<std::byte, KeySize> & key);
	static std::string Encrypt(std::string plainText, const std::string & key);
	static Block<std::byte, 16> Decrypt(const Block<std::byte, 16> & input, const Block<std::byte, KeySize> & key);
	static std::string Decrypt(std::string cipher, const std::string & key);
private:
	using Word = Block<std::byte, 4>;
	using StateType = std::array<Word, 4>;
private:
	static void SubBytes(StateType & state);
	static void ShiftRows(StateType & state);
	static void MixColumns(StateType & state);
	static void AddRoundKey(StateType & state, const Block<std::byte, 16> & key);
	static void InvMixColumns(StateType & state);
	static void InvShiftRows(StateType & state);
	static void InvSubBytes(StateType & state);
};

using AES_128 = AES<16, 10>;
using AES_192 = AES<24, 12>;
using AES_256 = AES<32, 14>;




template<size_t KeySize, size_t Rounds>
SBox AES<KeySize, Rounds>::subByte;

template<size_t KeySize, size_t Rounds>
RowShifter AES<KeySize, Rounds>::shiftRow;

template<size_t KeySize, size_t Rounds>
ColumnMixer AES<KeySize, Rounds>::mixColumns;

template<size_t KeySize, size_t Rounds>
ColumnMixer_Inverse AES<KeySize, Rounds>::invMixColumns;

template<size_t KeySize, size_t Rounds>
RowShifter_Inverse AES<KeySize, Rounds>::invShiftRow;

template<size_t KeySize, size_t Rounds>
SBox_Inverse AES<KeySize, Rounds>::invSubByte;

template<size_t KeySize, size_t Rounds>
Block<std::byte, 16> AES<KeySize, Rounds>::Encrypt(const Block<std::byte, 16> & input, const Block<std::byte, KeySize> & key)
{
	KeySchedule<KeySize, Rounds> keySchedule(key);

	StateType state = {};
	for (size_t i = 0; i < 16; ++i)
		state[i % 4][i / 4] = input[i];

	AddRoundKey(state, keySchedule[0]);

	for (size_t round = 1; round < Rounds; ++round)
	{
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, keySchedule[round]);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, keySchedule[Rounds]);

	Block<std::byte, 16> result = {};
	for (size_t i = 0; i < 16; ++i)
		result[i] = state[i % 4][i / 4];
	return result;
}

template<size_t KeySize, size_t Rounds>
std::string AES<KeySize, Rounds>::Encrypt(std::string plainText, const std::string & key)
{
	if (key.size() != KeySize)
		throw InvalidKeySize();
	std::string result;
	result.reserve(plainText.size());
	while (!plainText.empty())
	{
		Block<std::byte, 16> input = plainText;
		auto res = Encrypt(input, key);
		for (size_t i = 0; i < res.size(); ++i)
			result.push_back(std::to_integer<char>(res[i]));
		if (plainText.size() > 16)
			plainText = plainText.substr(16, plainText.npos);
		else
			plainText = "";
	}
	return result;
}

template<size_t KeySize, size_t Rounds>
Block<std::byte, 16> AES<KeySize, Rounds>::Decrypt(const Block<std::byte, 16> & input, const Block<std::byte, KeySize> & key)
{
	KeySchedule<KeySize, Rounds> keySchedule(key);

	StateType state = {};
	for (size_t i = 0; i < 16; ++i)
		state[i % 4][i / 4] = input[i];

	AddRoundKey(state, keySchedule[Rounds]);

	for (size_t round = Rounds - 1; round > 0; --round)
	{
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, keySchedule[round]);
		InvMixColumns(state);
	}

	InvShiftRows(state);
	InvSubBytes(state);
	AddRoundKey(state, keySchedule[0]);

	Block<std::byte, 16> result = {};
	for (size_t i = 0; i < 16; ++i)
		result[i] = state[i % 4][i / 4];
	return result;
}

template<size_t KeySize, size_t Rounds>
std::string AES<KeySize, Rounds>::Decrypt(std::string cipher, const std::string & key)
{
	if (key.size() != KeySize)
		return "";
	std::string result;
	result.reserve(cipher.size());
	while (!cipher.empty())
	{
		Block<std::byte, 16> input = cipher;
		auto res = Decrypt(input, key);
		for (size_t i = 0; i < res.size(); ++i)
			result.push_back(std::to_integer<char>(res[i]));
		if (cipher.size() > 16)
			cipher = cipher.substr(16, cipher.npos);
		else
			cipher = "";
	}
	return result;
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::SubBytes(StateType & state)
{
	for (size_t i = 0; i < 16; ++i)
		subByte(state[i / 4][i % 4]);
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::ShiftRows(StateType & state)
{
	for (size_t i = 0; i < 4; ++i)
		shiftRow(state[i], i);
//	switch (KeySize)
//	{
//	case 16:
//	case 24:
//		for (size_t i = 0; i < 4; ++i)
//			shiftRow(state[i], i);
//		break;
//	case 32:
//		shiftRow(state[0], 0);
//		shiftRow(state[1], 1);
//		shiftRow(state[2], 3);
//		shiftRow(state[3], 4);
//		break;
//	default:
//		break;
//	}
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::MixColumns(StateType & state)
{
	mixColumns(state);
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::AddRoundKey(StateType & state, const Block<std::byte, 16> & key)
{
	for (size_t i = 0; i < 16; ++i)
		state[i % 4][i / 4] ^= key[i];
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::InvMixColumns(AES::StateType & state)
{
	invMixColumns(state);
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::InvShiftRows(AES::StateType & state)
{
	for (size_t i = 0; i < 4; ++i)
		invShiftRow(state[i], i);
//	switch (KeySize)
//	{
//	case 16:
//	case 24:
//		for (size_t i = 0; i < 4; ++i)
//			invShiftRow(state[i], i);
//		break;
//	case 32:
//		invShiftRow(state[0], 0);
//		invShiftRow(state[1], 1);
//		invShiftRow(state[2], 3);
//		invShiftRow(state[3], 4);
//		break;
//	default:
//		break;
//	}
}

template<size_t KeySize, size_t Rounds>
void AES<KeySize, Rounds>::InvSubBytes(AES::StateType & state)
{
	for (size_t i = 0; i < 16; ++i)
		invSubByte(state[i / 4][i % 4]);
}
