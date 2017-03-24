#ifndef MOUSE_COMPONENT_H
#define MOUSE_COMPONENT
#include "Vector.h"
#include "Vector3D.h"
#include "Component.h"
#include "Entity.h"


namespace Entities
{
	class PhysicsComponent;
	class __declspec(dllexport) MouseComponent : public Component
	{

	private:
		PhysicsComponent* physics;
		Vector lastMousePosition;
		Vector latestMousePosition;
		Vector3D mouseDelta;
	public:
		bool initialize();
		void update();
		void grabMouse(const Vector& data);
	};

}

#endif