#include <GL\glew.h> 
#include "myGLwindow.h" //need this to happen after including glew.h
#include <cassert>
#include <QtGui\QKeyEvent>
#include <Qt\qdebug.h>
#include <Vector3D.h>
#include <Matrix2DE.h>
#include <Profiler.h>
#include <Profile.h>

///TRANSLATION NOTES//
///You cannot move the ship via translation when using 2D matrices.
///You must use the 3D matrices.
///END TRANSLATION NOTES//

//BREAKDOWN of UPDATE and REPAINT and PROFILER notes//
//in a perfect game world UPDATE then DRAW is ideal..
//since we are working with Qt and OpenGL..
//Qt is a windowing system, uses events(called signals and slots)
//repaint runs paintGL() -> paint is being called by more than one thing else than us..(paintGL deems necessary)
//Windowing systems form a queue(FIFO -> mouse movement, repaint(requires a paint), paint, paint,
//mouse move, etc.) -> feeds into a thread which handles the mouse move, repaint, etc..
//Timer class is running myUpdate which runs paint, our system is intertwined in
//event signal, mouse move, paint, ->causing inconsistencies within the profiler
//THEFIX -> put the update in the paint function with then calls update -> paint
//END BREAKDOWN NOTES//

//NOTES ABOUT THE TIMING PLAYER POSITION
//
	////basing time off real time and NOT frame time
	//playerPosition = playerPosition + velocity * mainClock.lastLapTime();
//end notes

//RANDOM NOTES
//painGL only runs when it needs to repaint(clicking on console..etcc)
//Qt is calling the rendering Opengl initz(graphics)

//C++ global(lerpAlpha) variables take on default value of 0
//defined a varaible on stack it does not!

namespace
{	

	//every frame we send the vertices down to the graphics card
	//code transforms the vertices OP * scale etc..



	//if nothing is pass through it initializes to 0
	Vector3D playerVerts[] =
	{
		//vertices of each triangle have to have z of 1(so translation 
		//can be turned on via the plane of z)
		
		//position (of 3 floats)
		Vector3D(+0.0f, +0.141421235623f, 1.0f),
		Vector3D(-0.1f, -0.1f , 1.0f),
		Vector3D(+0.1f, -0.1f, 1.0f),
	};

	Vector3D diamondBound[] = 
	{
		Vector3D(+0.0f, +1.0f, +0.0),
		Vector3D(-1.0f, +0.0f, +0.0),
		Vector3D(+0.0f, -1.0f, +0.0),
		Vector3D(+1.0f, +0.0f, +0.0),
	};

	GLushort diamondIndices[] = 
	{
		0,1,
		1,2,
		2,3,
		3,0
	};

	Vector3D lerpPath[]
	{
		Vector3D(+0.5f, +0.5f, +0.0f),
		Vector3D(-0.5f, +0.5f, +0.0f),
		Vector3D(-0.5f, -0.5f, +0.5f),
		Vector3D(+0.5f, -0.5f, +0.0f),
	};

	const uint NUM_LERP_POINTS = sizeof(lerpPath) / sizeof(*lerpPath);
	uint lerpSourcePoint;
	uint lerpDestinationPoint;
	float lerpAlpha;
	Vector3D lerpCurrentPosition;

	const unsigned int NUM_VERTS = sizeof(playerVerts) / sizeof(*playerVerts);
	// takes the size in bytes(sizeof(playerVerts)
	// divided by the size of 1 element in the array(sizeof(*playerVerts)

	const unsigned int NUM_BOUND_VERTS = sizeof(diamondBound) / sizeof(*diamondBound);
	Vector3D transformedVerts[NUM_VERTS];
	Vector3D playerPosition;
	Vector3D playerVelocity;
	Vector3D oldplayerPosition;
	float shipOrient = 0.0f;

	Clock mainClock;
	GLuint diamondBufferID;
	GLuint vertexBufferID;
	GLuint diamondIndicesID;
}
bool myGLwindow::initialize()
{
	bool yee = true;

	Pro.initialize("profiles.csv");

	yee &= mainClock.initialize();

	if (NUM_LERP_POINTS > 1)
	{
		lerpSourcePoint = 0;

		lerpDestinationPoint = 1;

		lerpAlpha = 0.0f;
	}
	else
	{
		yee = false;
	}

	return yee;
}
void myGLwindow::initializeGL()
{

	GLenum errorCode = glewInit();
	assert(errorCode == 0);

	glEnableVertexAttribArray(0);

	//create buffer for playerPosition vertices
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playerVerts), NULL, GL_DYNAMIC_DRAW);

	//create buffer for diamond boundary vertices
	//please generate a buffer openGL at address diamondBufferID and i need 1 of them.
	glGenBuffers(1, &diamondBufferID);
	//bind buffer to the array binding point.(the buffer object is located on the
	//graphics card) the binding point diamondbufferID is a point to store
	//small attributes between the array binding point and the graphics card
	glBindBuffer(GL_ARRAY_BUFFER, diamondBufferID);
	///(binding buffer data point, this much memory, copy that memory from this pointer, 
	///are we changing the data?(dynamic) or is it not changing(static)
	glBufferData(GL_ARRAY_BUFFER, sizeof(diamondBound), diamondBound, GL_STATIC_DRAW);

	//create buffer for boundary
	glGenBuffers(1, &diamondIndicesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, diamondIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(diamondIndices), diamondIndices, GL_STATIC_DRAW);


	//game loop begin
	//start calling intervals without wasting time theTimer.start(0);
	//with the specific function -> update();
	//SLOTS -> event handlers (QT version)
	connect(&theTimer, SIGNAL(timeout()), this, SLOT(theUpdate()));
	theTimer.start(0);

}
void myGLwindow::update()
{
	//update
	mainClock.lap();
	Pro.newFrame();
	rotation();
	updateVelocity();
	oldplayerPosition = playerPosition;
	playerPosition += playerVelocity * mainClock.lastLapTime();
	checkBoundaries();
	pathfindingLerper();
}
void myGLwindow::setGLstate()
{
	//DRAW

	//Notes about aspect ratio
	//aspect ratio
	//formula(ratio) = width / height
	//which term dominates each term

	//setup viewport
	glViewport(0, 0, width(), height());

	//setup data pointers
	//main player
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//attrib pointer describes the data to OpenGL(vertices, color, surface normals)
	//(attribute location, how many of what data, type of data, stride(amount of bytes
	//between each attribute)distance from position verts to next position verts, offset of
	//the position into the buffer (void*) <- cast as a pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//send data to openGL
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	//diamond
	glBindBuffer(GL_ARRAY_BUFFER, diamondBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, 0);

}
void myGLwindow::draw()
{

	float aspectRatio = static_cast<float>(width()) / height();
	Matrix2DE translator = Matrix2DE::translate(playerPosition.getX(), playerPosition.getY());
	Matrix2DE rotator = Matrix2DE::rotateZ(shipOrient);
	Matrix2DE scale;


	//if width is greater than height(basic vector x needs to scale down)
	//why 1/aspect ratio -> height(1) / width

	if (aspectRatio > 1)
		scale = Matrix2DE::scale(1 / aspectRatio, 1);//squishing by the width
	else
		scale = Matrix2DE::scale(1, aspectRatio);//squishing by the height


	//main player
	Matrix2DE Op;
	{
		PROFILE("Matrix Multiplcation");
		//order matters
		Op = translator * scale * rotator;
	}
	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_VERTS; i++)
			transformedVerts[i] = (Op * playerVerts[i]);

	}

	//clear screen
	glClear(GL_COLOR_BUFFER_BIT);

	//draw it main player
	setGLstate();

	//for lerper 
	translator = Matrix2DE::translate(lerpCurrentPosition.getX(), 
									  lerpCurrentPosition.getY());
	Op = translator * scale;
	for (unsigned int i = 0; i < NUM_VERTS; i++)
		transformedVerts[i] = (Op * playerVerts[i]);

	//draw the lerper
	setGLstate();
	
}
//updates vertice positions
void myGLwindow::paintGL()
{
	update();
	draw();
}
//poll for key inputs > GUI events
//update hooked to the timer
void myGLwindow::theUpdate()
{
	repaint();
}
bool myGLwindow::shutdown()
{
	bool yee = true;

	Pro.shutdown();

	yee &= mainClock.shutdown();

	return yee;
}
//needs windows for polling GUD GUD GUD
void myGLwindow::rotation()
{
	
	const float ANGULAR_MOVEMENT = 0.1f;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		//playerVelocity.setX(playerVelocity.getX() + ANGULAR_MOVEMENT);
		shipOrient -= ANGULAR_MOVEMENT;
	}
	
	if (GetAsyncKeyState(VK_LEFT))
	{
		//playerVelocity.setX(playerVelocity.getX() - ANGULAR_MOVEMENT);
		shipOrient += ANGULAR_MOVEMENT;
	}

}
void myGLwindow::updateVelocity()
{
	//magnitude(length)
	const float ACCELERATION = 0.3f * mainClock.lastLapTime();

	Vector3D directionAccelerate(-sin(shipOrient), cos(shipOrient));

	//getasyncstate is a short but treating it as a boolean for 0 == not pressed 
	//anything else pressed

	if (GetAsyncKeyState(VK_UP))
	{
		playerVelocity += directionAccelerate * ACCELERATION;
	}


}
void myGLwindow::pathfindingLerper()
{
	lerpAlpha += mainClock.lastLapTime(); //speed of 1 per second
	if (lerpAlpha >= 1.0f)
	{
		lerpAlpha = 0.0f;
		targetNextLerpPoint();
	}
	Vector3D source = lerpPath[lerpSourcePoint];
	Vector3D destination = lerpPath[lerpDestinationPoint];
	lerpCurrentPosition = source.lerp(lerpAlpha, destination);

		
}
void myGLwindow::targetNextLerpPoint()
{
	lerpSourcePoint = lerpDestinationPoint;
	lerpDestinationPoint = (lerpDestinationPoint + 1) % NUM_LERP_POINTS;
	//modulus value can cause issues if the game is ran for a long time
	//may cause player to jump
}
void myGLwindow::checkBoundaries()
{
	
	for (uint i = 0; i < NUM_BOUND_VERTS; i++)
	{
		Vector3D first = diamondBound[i];
		Vector3D second = diamondBound[(i + 1) % NUM_BOUND_VERTS];

		//normal means perpindicular
		Vector3D wall = second - first;
		Vector3D normal = wall.CounterClockWisePerp();
		Vector3D respectiveShipPosition = playerPosition - first;

		float dResult = normal.Dot(respectiveShipPosition);
		//anyColissions = anyColissions || (dResult < 0);
		//any collisions = false || is dot product on any walls < 0
	

		if (dResult < 0)
		{
			playerVelocity = playerVelocity + (playerVelocity.projectOnto(normal) * -2);
			playerPosition = oldplayerPosition;
		}

	}
	
	
	
	
	///***OLD WAY OF CALCULATING THE PROJECT ONTO METHOD FOR HITTING THE WALL WITH
	///EXPENSIVE SQUARE ROOT///
	//Vector3D normalScaled;
	////bool anyColissions = false;
	//for (uint i = 0; i < NUM_BOUND_VERTS; i++)
	//{
	//	Vector3D first = diamondBound[i];
	//	Vector3D second = diamondBound[(i + 1) % NUM_BOUND_VERTS];

	//	//normal means perpindicular
	//	Vector3D wall = second - first;
	//	Vector3D normal = wall.CounterClockWisePerp().Normalize();
	//	Vector3D respectiveShipPosition = playerPosition - first;

	//	float dResult = normal.Dot(respectiveShipPosition);
	//	//anyColissions = anyColissions || (dResult < 0);
	//	//any collisions = false || is dot product on any walls < 0
	//	normalScaled = normal;

	//	if (dResult < 0)
	//	{
	//		normalScaled = normal * -2;
	//		playerVelocity = playerVelocity + (normalScaled * playerVelocity.Dot(normal));
	//		playerPosition = oldplayerPosition;
	//	}

	//}

	/*if (playerPosition.getX() < -1 || playerPosition.getX() > 1)
	{
	playerVelocity.setX(playerVelocity.getX() * -1);
	}
	if (playerPosition.getY() < -1 || playerPosition.getY() > 1)
	{
	playerVelocity.setY(playerVelocity.getY() * -1);
	}*/


	
}





//gui libraries have a pause(event driven)...right arrow is down..held down well lets fire these events rapidly
//pushing to qt BAD BAD BAD
//void myGLwindow::keyPressEvent(QKeyEvent *k)
//{
//
//	const float SPEED = 0.02f;
//
//	if (k->key() == Qt::Key_Up)
//	{
//		playerPosition.setY(playerPosition.getY() + SPEED);
//	}
//	else if (k->key() == Qt::Key_Down)
//	{
//		playerPosition.setY(playerPosition.getY() - SPEED);
//	}
//	else if (k->key() == Qt::Key_Right)
//	{
//		playerPosition.setX(playerPosition.getX() + SPEED);
//	}
//	else if (k->key() == Qt::Key_Left)
//	{
//		playerPosition.setX(playerPosition.getX() - SPEED);
//	}
//}
