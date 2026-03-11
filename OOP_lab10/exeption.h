#pragma once

#include <string>
#include <exception>

using std::string;

class Exception : public std::exception {
protected:
	string errorMessage;

public:
	explicit Exception(string message) : errorMessage{ message } {}

	const char* what() const noexcept override {
		return errorMessage.c_str();
	}

	virtual ~Exception() = default;
};
