#include "PhysicsComponent.h"
#include "Entity.h"
#include "GameClock.h"

namespace Entities
{

	void PhysicsComponent::update()
	{
		velocity += acceleration * gameClock.dt();
		//acceleration is good for one frame then at the end reset
		acceleration = Vector3D();
		getParent()->position += velocity * gameClock.dt();
		getParent()->orientation += angularVelocity;
	}







}