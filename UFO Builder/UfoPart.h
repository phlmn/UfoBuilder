#pragma once

#include "LevelObject.h"

#include "UfoCatalogPart.h"
#include "CatalogObject.h"

class UfoPart : public LevelObject
{
public:
	UfoPart();
	UfoPart(UfoCatalogPart gameObject);
	~UfoPart();
};
