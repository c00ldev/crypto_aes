#pragma once

#include "Block.h"

#include "SBox.h"
#include "RowShifter.h"

#include <cstddef>
#include <array>

template<size_t KeySize = 16, size_t Rounds = 10>
class KeySchedule
{
public:
	using Word = Block<std::byte, 4>;
	static SBox subByte;
	static RowShifter rotWord;
	static const Word Rcon[256];
	std::array<Word, 4 * (Rounds + 1)> keys;
public:
	KeySchedule(const Block<std::byte, KeySize> & key);
	Block<std::byte, 16> operator[](size_t round) const;
};

template<size_t KeySize, size_t Rounds>
SBox KeySchedule<KeySize, Rounds>::subByte;

template<size_t KeySize, size_t Rounds>
RowShifter KeySchedule<KeySize, Rounds>::rotWord;

#define o(y) { std::byte(0x ## y) }

template<size_t KeySize, size_t Rounds>
const typename KeySchedule<KeySize, Rounds>::Word KeySchedule<KeySize, Rounds>::Rcon[256] =
	{
		o(8d), o(01), o(02), o(04), o(08), o(10), o(20), o(40), o(80), o(1b), o(36), o(6c), o(d8), o(ab), o(4d), o(9a),
		o(2f), o(5e), o(bc), o(63), o(c6), o(97), o(35), o(6a), o(d4), o(b3), o(7d), o(fa), o(ef), o(c5), o(91), o(39),
		o(72), o(e4), o(d3), o(bd), o(61), o(c2), o(9f), o(25), o(4a), o(94), o(33), o(66), o(cc), o(83), o(1d), o(3a),
		o(74), o(e8), o(cb), o(8d), o(01), o(02), o(04), o(08), o(10), o(20), o(40), o(80), o(1b), o(36), o(6c), o(d8),
		o(ab), o(4d), o(9a), o(2f), o(5e), o(bc), o(63), o(c6), o(97), o(35), o(6a), o(d4), o(b3), o(7d), o(fa), o(ef),
		o(c5), o(91), o(39), o(72), o(e4), o(d3), o(bd), o(61), o(c2), o(9f), o(25), o(4a), o(94), o(33), o(66), o(cc),
		o(83), o(1d), o(3a), o(74), o(e8), o(cb), o(8d), o(01), o(02), o(04), o(08), o(10), o(20), o(40), o(80), o(1b),
		o(36), o(6c), o(d8), o(ab), o(4d), o(9a), o(2f), o(5e), o(bc), o(63), o(c6), o(97), o(35), o(6a), o(d4), o(b3),
		o(7d), o(fa), o(ef), o(c5), o(91), o(39), o(72), o(e4), o(d3), o(bd), o(61), o(c2), o(9f), o(25), o(4a), o(94),
		o(33), o(66), o(cc), o(83), o(1d), o(3a), o(74), o(e8), o(cb), o(8d), o(01), o(02), o(04), o(08), o(10), o(20),
		o(40), o(80), o(1b), o(36), o(6c), o(d8), o(ab), o(4d), o(9a), o(2f), o(5e), o(bc), o(63), o(c6), o(97), o(35),
		o(6a), o(d4), o(b3), o(7d), o(fa), o(ef), o(c5), o(91), o(39), o(72), o(e4), o(d3), o(bd), o(61), o(c2), o(9f),
		o(25), o(4a), o(94), o(33), o(66), o(cc), o(83), o(1d), o(3a), o(74), o(e8), o(cb), o(8d), o(01), o(02), o(04),
		o(08), o(10), o(20), o(40), o(80), o(1b), o(36), o(6c), o(d8), o(ab), o(4d), o(9a), o(2f), o(5e), o(bc), o(63),
		o(c6), o(97), o(35), o(6a), o(d4), o(b3), o(7d), o(fa), o(ef), o(c5), o(91), o(39), o(72), o(e4), o(d3), o(bd),
		o(61), o(c2), o(9f), o(25), o(4a), o(94), o(33), o(66), o(cc), o(83), o(1d), o(3a), o(74), o(e8), o(cb), o(8d)
	};

#undef o

template<size_t KeySize, size_t Rounds>
KeySchedule<KeySize, Rounds>::KeySchedule(const Block<std::byte, KeySize> & key)
{
	constexpr size_t Nk = KeySize / 4;
	Word temp;
	size_t i = 0;
	for (; i < Nk; ++i)
		keys[i] = { key[i * 4 + 0], key[i * 4 + 1], key[i * 4 + 2], key[i * 4 + 3] };
	for (; i < 4 * (Rounds + 1); ++i)
	{
		temp = keys[i - 1];
		if (i % Nk == 0)
		{
			rotWord(temp, 1);
			for (size_t j = 0; j < 4; ++j)
				subByte(temp[j]);
			temp ^= Rcon[i / Nk];
		}
		else if (Nk > 6 && i % Nk == 4)
			for (size_t j = 0; j < 4; ++j)
				subByte(temp[j]);
		keys[i] = keys[i - Nk] ^ temp;
	}
}

template<size_t KeySize, size_t Rounds>
Block<std::byte, 16> KeySchedule<KeySize, Rounds>::operator[](size_t round) const
{
	union
	{
		Block<std::byte, 16> res;
		std::array<Block<std::byte, 4>, 4> words;
	} unn;
	for (size_t i = 0; i < 4; ++i)
		unn.words[i] = keys[round * 4 + i];
	return unn.res;
}
