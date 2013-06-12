#pragma once

#include <list>
#include <SFML\Graphics.hpp>
#include "UfoPart.h"

class Ufo
{
private:
	std::list<UfoPart*> m_parts;
public:
	Ufo();
	~Ufo();

	void addPart();
	void removePart();
};
