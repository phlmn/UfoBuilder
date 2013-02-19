#pragma once

#include "main.h"

#ifndef STRINGHELPER_H
#define STRINGHELPER_H

class StringHelper
{
public:
	static std::string toString(double value);
	static std::string toString(float value);
	static std::string toString(int value);
};

#endif
