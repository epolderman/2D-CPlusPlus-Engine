#ifndef LERP_COMPONENT_H
#define LERP_COMPONENT_H
#include "Component.h"
#include "Vector3D.h"
#include "Typedefs.h"
#include "Entity.h"
using typedefz::uint;

namespace Entities
{

	class __declspec(dllexport) LerpComponent : public Component
	{
		uint NUM_LERP_POINTS;
		uint lerpSourcePoint;
		uint lerpDestinationPoint;
		Vector3D lerpCurrentPosition;
		const Vector3D* lerpPath;
		float lerpAlpha;
		Entity* mainPlayer;
	public:
		LerpComponent();
		bool initialize();
		void setData(Vector3D* theVerts, uint numPoints, Entity* mainPlayer);
		void update();
		void targetNextLerpPoint();
		void pathfindingLerper();
	};


}

#endif