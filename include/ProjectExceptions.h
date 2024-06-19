#pragma once

#include <exception>

class ConfigFileMissingException : public std::exception
{
public:
	const char* what() const noexcept
	{
		return "Config file is missing!!!";
	}
};

class ConfigFileEmptyException : public std::exception
{
public:
	const char* what() const noexcept
	{
		return "Config file is empty!!!";
	}
};