#pragma once

#include "Block.h"

#include <cstddef>

class RowShifter
{
public:
	void operator()(Block<std::byte, 4> & row, size_t count) const;
};

class RowShifter_Inverse
{
public:
	void operator()(Block<std::byte, 4> & row, size_t count) const;
};
