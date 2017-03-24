#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#include <QtOpenGL\qglwidget>
#include "Typedefs.h"
#include "Geometry.h"
#include "Renderable.h"
#include "Matrix2DE.h"



//*******THE RENDERING SYSTEM MAIN CORE***************//
//GEOMETRY
//Vertex Data->Specific triangle vertices
//Vertex Data->(These specific vertices are the beginning triangles)(1.0f, 2.0f, Vector3D, etc..)
//Index Data -> Indexes of specific triangles (i.e. 0, 1, 2 glushorts)

//Renderable -> (Instances) Vertex Data + Index Data = 2 Renderables per 1 Geometry

//Renderer -> Manages the geometries and renderables to draw onto the screen

namespace Rendering
{

	

	class _declspec(dllexport) Renderer : public QGLWidget
	{
		
		//advantage -> doesnt have to call new
		//advantage -> more cache friendly
		//advantage -> no fragmentation
		//advantage -> array is embedded into our renderer class
		//disadvantage -> we are stuck with 10 so we are limited
		static const uint NUM_MAX_GEMS = 10; 
		//can define a const in a class header as long as its static
		//compiler copies and pastes the const value around
		//if not static it becomes a memebr of a class -> have to initialize that const per instance of the class
		Geometry GEMS[NUM_MAX_GEMS];

		//(1 for the diamond, 2 for the ships) number of geometries we are sending to the
		//renderable
		static const uint NUM_MAX_RENDERABLES = 10;
		Renderable RENS[NUM_MAX_RENDERABLES];

		typedefz::uint numGEMS;
		typedefz::uint numRENDS;
		static const uint MAX_BUFFER_SIZE = 1024;
		//create buffers 1000 bytes larrge
		GLuint vertexbufferID;
		GLuint indexbufferID;
		static const uint MAX_VERTS = 10;
		QCursor cursor;
		Matrix2DE Renderer::getAspectCorrectionMatrix() const;
	protected:
		//paintEvent overrides the QT event paint paint paint call and gives us control over
		//the rendering
		void paintEvent();
		void paintGL();
		void initializeGL();
		
	public:
		bool initialize();
		bool shutdown();
		Geometry* addGeometry(Vector3D* vertices, uint numVerts,
							  ushort* indices, uint numIndices, GLenum renderMode = GL_TRIANGLES);

		//gl rendermode -> ie lines, triangles, etc..

		Renderable* addRenderable(Geometry* geometry);
		void renderScene();


	};
}
#endif