#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H
#include "Typedefs.h"
class Vector3D; ///<--keep the header files lean and mean so do not include "Vector3D.h"





//This class helps the Render manage the geometry
//Data Dumb Class

namespace Rendering
{
	
	class Geometry
	{
		friend class Renderer;



		//Vertex Information
		//Why a pointer? They are the exact same size doesnt matter what data
		//it is pointing to. Telling the compiler there is a vector3D pointer to this. 
		//we cannot call functions with no #include "Vector3D.h" in it. 
		const Vector3D *vertices;
		typedefz::uint numVerts;
		//end Vertex information



		//Index Information
		const ushort* indices;
		typedefz::uint numIndices;
		//end index information



		GLenum renderMode;
		//= GL_TRIANGLES
	};
}

#endif