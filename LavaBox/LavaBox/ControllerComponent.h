#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H
#include <Component.h>

namespace Entities
{
	class PhysicsComponent;

	class ControllerComponent : public Component
	{
		PhysicsComponent* physics;
	public:
		void update();
		bool initialize();


	};
}
#endif

