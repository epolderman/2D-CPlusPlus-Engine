#ifndef ENGINE_PHYSICS_COMPONENT_H
#define ENGINE_PHYSICS_COMPONENT_H
#include "Component.h"
#include "Vector3D.h"


namespace Entities{

	class _declspec(dllexport) PhysicsComponent : public Component
	{

	public:
		PhysicsComponent() { angularVelocity = 0; }
		Vector3D velocity;
		void update();
		float angularVelocity;
		Vector3D acceleration;

	};
}


#endif