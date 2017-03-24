#ifndef ENGINE_RENDERER_COMPONENT_H
#define ENGINE_RENDERER_COMPONENT_H
#include "Component.h"
namespace Rendering{ class Renderable; }

namespace Entities
{

	class _declspec(dllexport) RendererComponent : public Component
	{

		Rendering::Renderable* renderable;
	public:
		
		void setData(Rendering::Renderable* renderable);
		//inlining buys us speed and execution within the stackframe of the callstack
		void update();
	};
}

#endif