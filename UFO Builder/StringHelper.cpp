#include "StringHelper.h"

std::string StringHelper::toString(double value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string StringHelper::toString(float value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string StringHelper::toString(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}
