#pragma once

#include <cstddef>
#include <array>
#include <vector>
#include <initializer_list>
#include <string>

template<class T, size_t Size>
class Block
{
	std::array<T, Size> block;
public:
	Block() = default;
	Block(const std::vector<T> & v)
		: block{}
	{
		for (size_t i = 0; i < Size && i < v.size(); ++i)
			block[i] = v[i];
	}

	Block(const std::initializer_list<T> & il)
		: block{}
	{
		for (size_t i = 0; i < Size && i < il.size(); ++i)
			block[i] = il.begin()[i];
	}

	Block(const std::string & s)
		: block{}
	{
		for (size_t i = 0; i < Size && i < s.size(); ++i)
			block[i] = T(s[i]);
	}

	T & operator[](size_t i)
	{
		return block[i];
	}

	const T & operator[](size_t i) const
	{
		return block[i];
	}

	size_t size() const
	{
		return Size;
	}

	Block<T, Size> & operator^=(const Block<T, Size> & rhs)
	{
		for (size_t i = 0; i < Size; ++i)
			block[i] ^= rhs.block[i];
		return *this;
	};

	friend Block<T, Size> operator^(Block<T, Size> lhs, const Block<T, Size> & rhs)
	{
		lhs ^= rhs;
		return lhs;
	};
};
