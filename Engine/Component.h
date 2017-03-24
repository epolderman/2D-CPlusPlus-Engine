#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H


namespace Entities
{
	class Entity;
	class _declspec(dllexport) Component
	{
		friend class Entity;
		Entity* parent;
	public:
		virtual void update(){}
		Entity *getParent() const { return parent; }
		virtual bool initialize() { return true; }
		virtual bool shutdown() { return true; }
	};


}


#endif