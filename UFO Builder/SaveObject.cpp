#include "SaveObject.h"

using namespace tinyxml2;

SaveObject::SaveObject()
{
	m_imageFile = "";
	m_name = "";
	m_objectID = "";
}


SaveObject::~SaveObject()
{

}

bool SaveObject::load(std::string objectID)
{
	XMLDocument doc;

	// load XML file
	if(doc.LoadFile(("objects\\" + objectID + ".xml").c_str()) != XMLError::XML_SUCCESS)
		return false;

	// get object node
	
	XMLElement* objectNode = doc.RootElement();
	if(objectNode == NULL)
		return false;

	// parse attributes
	if(objectNode->Attribute("id") == NULL)
		return false;
	m_objectID = objectNode->Attribute("id");

	if(objectNode->Attribute("name") != NULL)
		m_name = objectNode->Attribute("name");

	if(objectNode->Attribute("image") != NULL)
		m_imageFile = objectNode->Attribute("image");

	// get physics node
	XMLElement* physicsNode = objectNode->FirstChildElement("physics");

	// parse body type
	if(physicsNode->Attribute("type") == "dynamic")
		m_physProps.setBodyType(PhysBodyType::Dynamic);
	else
		m_physProps.setBodyType(PhysBodyType::Static);

	// parse fixtures
	m_physProps.getFixtures()->clear();

	XMLElement* fixtureNode = physicsNode->FirstChildElement("fixture");
	while(fixtureNode != NULL)
	{
		StorableFixture fixture;

		// parse fixture type
		std::string type = fixtureNode->Attribute("type");
		if(type == "line")
			fixture.setType(Line);
		else if(type == "polygon")
			fixture.setType(Poly);
		else if(type == "circle")
			fixture.setType(Circle);
		else
			fixture.setType(Chain);

		// parse fixture position
		fixture.setPosition(b2Vec2(std::stof(fixtureNode->Attribute("x")), std::stof(fixtureNode->Attribute("y"))));

		// parse fixture friction
		fixture.setFriction(std::stof(fixtureNode->Attribute("friction")));

		// parse fixture density
		fixture.setDensity(std::stof(fixtureNode->Attribute("density")));

		// parse fixture vertices
		XMLElement* pointNode = fixtureNode->FirstChildElement("point");
		while(pointNode != NULL)
		{			
			fixture.getVertices()->push_back(b2Vec2(std::stof(pointNode->Attribute("x")), std::stof(pointNode->Attribute("y"))));
			pointNode = pointNode->NextSiblingElement("point");
		}

		m_physProps.getFixtures()->push_back(fixture);

		// get next node
		fixtureNode = fixtureNode->NextSiblingElement("fixture");
	}
	return true;
}

bool SaveObject::save()
{
	//TODO: save the object

	// example
	XMLDocument doc;
	
	XMLElement* node = doc.NewElement("object");
	node->SetAttribute("id", m_objectID.c_str());
	node->SetAttribute("name", m_objectID.c_str());
	node->SetAttribute("image", m_objectID.c_str());

	XMLElement* physicsNode = doc.NewElement("physics");
	physicsNode->SetAttribute("type", "dynamic");
	node->InsertEndChild(physicsNode);

	XMLElement* fixtureNode = doc.NewElement("fixture");
	fixtureNode->SetAttribute("type", "polygon");
	fixtureNode->SetAttribute("x", "0");
	fixtureNode->SetAttribute("y", "0");
	fixtureNode->SetAttribute("density", "1.5");
	fixtureNode->SetAttribute("friction", "0.5");
	physicsNode->InsertEndChild(fixtureNode);

	XMLElement* fixPointNode = doc.NewElement("point");
	fixPointNode->SetAttribute("x", "0");
	fixPointNode->SetAttribute("y", "0");
	fixtureNode->InsertEndChild(fixPointNode);

	doc.InsertEndChild(node);

	XMLError error = doc.SaveFile(("objects\\" + m_objectID + ".xml").c_str());

	if(error == XMLError::XML_SUCCESS)
		return true;
	
	return false;
}
