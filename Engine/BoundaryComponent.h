#ifndef BOUNDARY_HANDLER_COMPONENT_H
#define BOUNDARY_HANDLER_COMPONENT_H
#include "Component.h"
#include "Vector3D.h"
#include "Typedefs.h"
using typedefz::uint;

namespace Entities
{
	class PhysicsComponent;
	class _declspec(dllexport) BoundaryComponent : public Component
	{
		uint NUM_BOUND_VERTS;
		const Vector3D* diamondBound;
		PhysicsComponent* physics;
		Vector3D oldplayerPosition;
	public:
		BoundaryComponent();
		bool initialize();
		void update();
		void setData(Vector3D* diamondBound, uint numbBoundVerts);
		
	};
}

#endif