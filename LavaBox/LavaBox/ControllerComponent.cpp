#include "ControllerComponent.h"
#include <KeyInput.h>
#include "MyMenuChoice.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include <cmath>
#include "Vector3D.h"


namespace Entities
{
	bool ControllerComponent::initialize()
	{
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != 0;
	}

	void ControllerComponent::update()
	{
		const float ANGULAR_VELOCITY = 0.1f;

		if (input.actionsHotThisFrame(Input::RotateLeft))
		{
			physics->angularVelocity = ANGULAR_VELOCITY;
		}
		else if (input.actionsHotThisFrame(Input::RotateRight))
		{
			physics->angularVelocity = -ANGULAR_VELOCITY;
		}
		else
		{
			physics->angularVelocity = 0;
		}

		if (input.actionsHotThisFrame(Input::Accelerate))
		{
			physics->acceleration = Vector3D(-sin(getParent()->orientation), cos(getParent()->orientation));
			//physics->acceleration.setX(-sin(getParent()->orientation));
			//physics->acceleration.setY(cos(getParent()->orientation));
		}

	}



}
