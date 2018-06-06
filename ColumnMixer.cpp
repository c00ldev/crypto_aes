#include "ColumnMixer.h"

unsigned char mul(unsigned char a, unsigned char b)
{
	unsigned char p = 0;
	for (size_t i = 0; i < 8; ++i)
	{
		p ^= -(b & 1u) & a;
		int mask = -((a >> 7u) & 1u);
		a = (a << 1u) ^ (0b100011011 & mask);
		b >>= 1u;
	}
	return p;
}

const unsigned char ColumnMixer::matrix[4][4] =
	{
		{ 2, 3, 1, 1 },
		{ 1, 2, 3, 1 },
		{ 1, 1, 2, 3 },
		{ 3, 1, 1, 2 }
	};

void ColumnMixer::operator()(std::array<Block<std::byte, 4>, 4> & state) const
{
	unsigned char result[4][4] = {};
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			for (size_t k = 0; k < 4; ++k)
				result[i][j] ^= mul(matrix[i][k], std::to_integer<unsigned char>(state[k][j]));
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			state[i][j] = std::byte(result[i][j]);
}

const unsigned char ColumnMixer_Inverse::matrix[4][4] =
	{
		{ 14, 11, 13, 9 },
		{ 9, 14, 11, 13 },
		{ 13, 9, 14, 11 },
		{ 11, 13, 9, 14 }
	};

void ColumnMixer_Inverse::operator()(std::array<Block<std::byte, 4>, 4> & state) const
{
	unsigned char result[4][4] = {};
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			for (size_t k = 0; k < 4; ++k)
				result[i][j] ^= mul(matrix[i][k], std::to_integer<unsigned char>(state[k][j]));
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			state[i][j] = std::byte(result[i][j]);
}
