#ifndef TARGET_COMPONENT_H
#define TARGET_COMPONENT_H
#include "Component.h"
#include "Entity.h"

namespace Entities
{
	class __declspec(dllexport) TargetComponent : public Component
	{
	private:
		Entity* mainPlayer;
	public:
		TargetComponent();
		bool initialize();
		void setData(Entity* mainplayer);
		void update();
	};
}


#endif