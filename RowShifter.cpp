#include "RowShifter.h"

#include <algorithm>

void RowShifter::operator()(Block<std::byte, 4> & row, size_t count) const
{
	for (size_t i = 0; i < count; ++i)
		for (size_t j = 0; j < row.size() - 1; ++j)
			std::swap(row[0], row[row.size() - 1 - j]);
}

void RowShifter_Inverse::operator()(Block<std::byte, 4> & row, size_t count) const
{
	for (size_t i = 0; i < count; ++i)
		for (size_t j = 1; j < row.size(); ++j)
			std::swap(row[0], row[j]);
}
