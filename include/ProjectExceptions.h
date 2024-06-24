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

class RequestsFileMissingException : public std::exception
{
public:
	const char* what() const noexcept
	{
		return "Requests file is missing!!!";
	}
};

class AnswersEmptyException : public std::exception
{
public:
	const char* what() const noexcept
	{
		return "Answers data is empty!!!";
	}
};