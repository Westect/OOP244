// Final Project Milestone 2
// Version 1.0
// Date	
// Author	
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
#include <string>
#include "ErrorMessage.h"

namespace sict
{
	ErrorMessage::ErrorMessage(const char* errorMessage)
	{
		if (errorMessage == nullptr)
		{
			errormsg = nullptr;
		}
		else if (errorMessage[0] != '\0')
		{
			int size = strlen(errorMessage);
			errormsg = new char[size + 1];
			snprintf(errormsg, size + 1, "%s", errorMessage);
		}
	}

	ErrorMessage::~ErrorMessage()
	{
		delete[] errormsg;
	}

	void ErrorMessage::clear()
	{
		delete[] errormsg;
		errormsg = nullptr;
	}

	bool ErrorMessage::isClear() const
	{
		if (errormsg == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ErrorMessage::message(const char * str)
	{
		clear();
		int size = strlen(str);
		errormsg = new char[size + 1];
		snprintf(errormsg, size + 1, "%s", str);
	}

	const char * ErrorMessage::message() const
	{
		return errormsg;
	}

	std::ostream & operator<<(std::ostream& ostr, const ErrorMessage& str)
	{
		if (str.errormsg != nullptr && str.errormsg [0] != '\0')
		{
			ostr << str.errormsg;
			return ostr;
		}
		else
		{
			return ostr;
		}
	}

}