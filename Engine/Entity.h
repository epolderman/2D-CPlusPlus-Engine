#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
#include "Typedefs.h"
#include "Vector3D.h"
#include "Component.h"




namespace Entities
{
	

	class _declspec(dllexport) Entity
	{
		typedefz::uint static const NUM_MAX_COMPONENTS = 10;
		Component* theComponents[NUM_MAX_COMPONENTS];
		typedefz::uint numComponents;

	public:
		Entity();
		bool initialize(Vector3D& position);
		bool shutdown();
		void addComponent(Component* comp);
		//2 elite members
		Vector3D position;
		float orientation;
		//end
		void update();
		//grabbing other components
		template <class T>
		T* getComponent() const;
	};

	template<class T>
	T* Entity::getComponent() const
	{
		for (typedefz::uint i = 0; i < numComponents; i++)
		{
			T* ret = dynamic_cast<T*>(theComponents[i]);
			if (ret != 0)
				return ret;
		}
			return 0;
		
	}

}
#endif