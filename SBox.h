#pragma once

#include <cstddef>

class SBox
{
	static const std::byte table[256];
public:
	void operator()(std::byte & b) const;
};

class SBox_Inverse
{
	static const std::byte table[256];
public:
	void operator()(std::byte & b) const;
};
