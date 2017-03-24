#include "BoundaryComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"

namespace Entities
{
	BoundaryComponent::BoundaryComponent()
	{
		diamondBound = 0;
		physics = 0;
	}
	bool BoundaryComponent::initialize()
	{
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != 0 && diamondBound != 0;
	}
	void BoundaryComponent::setData(Vector3D* diamondBounds, uint numbBoundVerts)
	{
		NUM_BOUND_VERTS = numbBoundVerts;
		this->diamondBound = diamondBounds;
	}
	void BoundaryComponent::update()
	{
		for (uint i = 0; i < NUM_BOUND_VERTS; i++)
		{
			Vector3D first = diamondBound[i];
			Vector3D second = diamondBound[(i + 1) % NUM_BOUND_VERTS];

			//normal means perpindicular
			Vector3D wall = second - first;
			Vector3D normal = wall.CounterClockWisePerp().Normalize();
			Vector3D respectiveShipPosition = getParent()->position - first;

			float dResult = normal.Dot(respectiveShipPosition);
		
			if (dResult < 0)
			{
				physics->velocity = physics->velocity + (physics->velocity.projectOnto(normal) * -2);
				getParent()->position = oldplayerPosition;
			}

			oldplayerPosition = getParent()->position;

		}

	
	}


}