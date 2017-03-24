#include "Entity.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

namespace Entities
{
	Entity::Entity()
	{
		orientation = 0;
		numComponents = 0;
	}
	bool Entity::initialize(Vector3D& position)
	{
		this->position = position;

		for (typedefz::uint i = 0; i < numComponents; i++)
		{
			if (!theComponents[i]->initialize())
				return false;
		}
		return true;
	}
	bool Entity::shutdown()
	{
		for (typedefz::uint i = 0; i < numComponents; i++)
		{
			if (!theComponents[i]->shutdown())
				return false;
		}
		return true;
	}
	void Entity::addComponent(Component* comp)
	{
		//add to our entity
		assert(numComponents != NUM_MAX_COMPONENTS);
		theComponents[numComponents++] = comp;
		comp->parent = this;
	}
	void Entity::update()
	{
		//cout << "orientation " << orientation << endl;
		//cout << "position is " << position.getX() << position.getY() << position.getZ() << endl;
		for (typedefz::uint i = 0; i < numComponents; i++)
			theComponents[i]->update();

	}




}