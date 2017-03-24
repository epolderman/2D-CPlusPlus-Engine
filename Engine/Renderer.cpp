#include <gl\glew.h>
#include "Renderer.h"
#include <cassert>
#include "Vector3D.h"
#include <iostream>
#include "Vector.h"
#include <QtGui\QMouseEvent>
#include <QtGui\\qkeyevent>
using std::cout;
using std::endl;

//for the weekend
//NOTES -> look up references(specifically this) vs pointers again
//NOTES -> look up static const variables within C++ classes
//Notes -> look up direction rotation matrix vector again(y = -sin(theta), cos(theta)

//DO NOT MODIFY THE ORIGINAL VERTICES of the player -> 
//apply matrices onto the vertices and save them elsewhere & do operations


namespace Rendering
{
	bool Renderer::initialize()
	{
		
		vertexbufferID = -1;
		indexbufferID = -1;
		numGEMS = 0;
		numRENDS = 0;
		show();
		return true;
	}

	//creates buffer and initialize
	void Renderer::initializeGL()
	{
		GLenum status = glewInit();
		assert(status == 0);
		glClearColor(0, 0, 0, 1);
		//alpha value is how much you can see through a color

		//generate
		glGenBuffers(1, &vertexbufferID);
		glGenBuffers(1, &indexbufferID);

		//bind to retrospective binding points
		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferID);

		//take buffers and allocate some room(ram)
		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		setMouseTracking(true);

	}

	Geometry* Renderer::addGeometry(Vector3D* vertices, uint numVerts,
		ushort* indices, uint numIndices, GLenum renderMode)
	{
		//break if we are at the max number geometries
		assert(numGEMS != NUM_MAX_GEMS);
		assert(numVerts <= MAX_VERTS);
		Geometry& pointerGem = GEMS[numGEMS++];
		pointerGem.vertices = vertices;
		pointerGem.numVerts = numVerts;
		pointerGem.indices = indices;
		pointerGem.numIndices = numIndices;
		pointerGem.renderMode = renderMode;
		return &pointerGem; //return the address(pointer)

		//if we were returning a reference its up the caller to convert it to a pointer
	}

	Renderable* Renderer::addRenderable(Geometry* geometry)
	{
		assert(numRENDS != NUM_MAX_RENDERABLES);
		Renderable& pointerRen = RENS[numRENDS++];
		pointerRen.what = geometry;
		return &pointerRen;
	}

	//for our Game to call render when we want
	void Renderer::renderScene()
	{
		glViewport(0, 0, width(), height());
		glDraw(); //go do the openGL schtuff
	}

	//overriding the paintEvent from qt so it doesnt call 50 million times
	void Renderer::paintEvent()
	{

	}

	Matrix2DE Renderer::getAspectCorrectionMatrix() const
	{
		float aspectRatio = static_cast<float>(width()) / height();
		
		//if width is greater than height(basic vector x needs to scale down)
		//why 1/aspect ratio -> height(1) / width

		Matrix2DE scale;

		if (aspectRatio > 1)
			return scale = Matrix2DE::scale(1 / aspectRatio, 1);//squishing by the width
		else
			return scale = Matrix2DE::scale(1, aspectRatio);//squishing by the height


	}
	//all the magic happens here
	//we render all the renderables here
	void Renderer::paintGL()
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		//2d clear the array of colors
		//if painting all pixels then dont do it
		
		Vector3D transformedVerts[MAX_VERTS];

		for (uint i = 0; i < numRENDS; i++)
		{
			const Renderable& r = RENS[i];

			//indices
			//send data to a buffer ive already told you to allocate
			//indices are for the element array buffer
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
				sizeof(ushort) * r.what->numIndices, r.what->indices);

			//Vertices
			Matrix2DE op = getAspectCorrectionMatrix() * r.where;
			for (uint j = 0; j < r.what->numVerts; j++)
			{
				transformedVerts[j] = op * r.what->vertices[j];
			}
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector3D) * r.what->numVerts,
				transformedVerts);

			glDrawElements(r.what->renderMode, r.what->numIndices, GL_UNSIGNED_SHORT, 0);


		}
		

	}

	bool Renderer::shutdown()
	{
		if (vertexbufferID != -1)
			glDeleteBuffers(1, &vertexbufferID);

		if (indexbufferID != -1)
			glDeleteBuffers(1, &indexbufferID);

		return true;
	}






}




