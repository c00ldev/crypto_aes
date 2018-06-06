#pragma once

#include "Block.h"

#include <array>
#include <cstddef>

class ColumnMixer
{
	static const unsigned char matrix[4][4];
public:
	void operator()(std::array<Block<std::byte, 4>, 4> & state) const;
};

class ColumnMixer_Inverse
{
	static const unsigned char matrix[4][4];
public:
	void operator()(std::array<Block<std::byte, 4>, 4> & state) const;
};
