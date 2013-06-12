#pragma once

#include "LevelObject.h"

#include "UfoCatalogPart.h"
#include "CatalogObject.h"

class UfoPart : public LevelObject
{
public:
	UfoPart();
	UfoPart(UfoCatalogPart gameObject);
	UfoPart(UfoCatalogPart gameObject, int layer, sf::Vector2f position, float scale, float opacity, float angle);
	~UfoPart();
};
