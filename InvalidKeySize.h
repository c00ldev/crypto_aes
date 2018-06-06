#pragma once

#include <exception>

class InvalidKeySize : public std::exception
{
public:
	const char * what() const noexcept override;
};
