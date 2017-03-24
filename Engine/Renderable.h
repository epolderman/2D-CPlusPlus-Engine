#ifndef ENGINE_RENDERABLE_H
#define ENGINE_RENDERABLE_H
#include "Matrix2DE.h"


//Renderable is rendered twice -> Ship and Lerper.

namespace Rendering
{
	class Geometry;

	class Renderable
	{
		friend class Renderer;
		const Geometry* what;
		//what we want to render(geometry(index + indexes))
	public:
		Matrix2DE where;
		//key difference of where the lerper vs mainPlayer ship is rendered
		//is WHERE? via the matrix(the matrix moves the players der der)
	};
}

#endif