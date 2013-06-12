#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "StorablePhysProps.h"
#include "StorableFixture.h"
#include "tinyxml2.h"

class CatalogObject
{
public:
private:
	std::string m_objectID;
	std::string m_name;
	std::string m_imageFile;

	StorablePhysProps m_physProps;

public:
	CatalogObject();
	~CatalogObject();

	bool save();
	bool load(std::string objectID);
};

