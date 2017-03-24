#include "Game.h"
#include <cstdlib>
#include <Geometry.h>
#include "MyMenuChoice.h"
#include <KeyInput.h>
#include "GameClock.h"
#include <iostream>
using std::cout;
using std::endl;
using Rendering::Geometry;


//preproccessor pastes this where we defined it down below
#define ARRAYSIZE(a) (sizeof(a) / sizeof(*a))


bool Game::initialize()
{


	//initialize rendering
	if (! theRender.initialize())
		return false;

	//initialize keyboard controls
	if (! input.initialize(&keyMapper, Input::MyMenuChoice::MAX))
		return false;
	
	//initialize singleton gameclock
	if (! gameClock.initialize() )
		return false;

	//targeting crosshairs
	if (!initializeTargetData())
		return false;

	//layout for the boundary data
	if (! initializeBoundaryData())
		return false;

	//initialize player
	if (! initializePlayer())
		return false;

	//initialize lerp points
	if (! initializeLerpData())
		return false;

	//initialize enemy
	if (! initializeSquareEnemy())
		return false;

	

	//game loop begin
	//start calling intervals without wasting time theTimer.start(0);
	//with the specific function -> update();
	//SLOTS -> event handlers (QT version)
	if (!connect(&theTimer, SIGNAL(timeout()), this, SLOT(update())))
		return false;
	//connect the timer and fire my signal timeout, 
	//store the this object and the function update


	return true;
}

bool Game::shutdown()
{
	//if one of these is fall it returns false
	bool good = true;
	good &= mainPlayer.shutdown();
	good &= squareEnemy.shutdown();
	good &= crossHairs.shutdown();
	good &= gameClock.shutdown();
	good &= input.shutdown();
	good &= theRender.shutdown();
	return good;
}

void Game::update()
{
	gameClock.newFrame();
	input.update();
	mainPlayer.update();
	squareEnemy.update();
	crossHairs.update();
	theRender.renderScene();
}

void Game::Go()
{
	theTimer.start();
}

bool Game::initializeTargetData()
{
	Vector3D targetVertData[] =
	{
		Vector3D(-0.03f, +0.0f, +1.0),
		Vector3D(+0.03f, +0.0f, +1.0),
		Vector3D(+0.0f, +0.03f, +1.0),
		Vector3D(+0.0f, -0.03f, +1.0),
	};

	GLushort targetIndicesData[] =
	{
		0, 1,
		2, 3
	};

	//bug checking if our constants == sizefoarray and indices
	if (ARRAYSIZE(targetVertData) != NUM_TARGET_POINTS)
	{
		cout << "Error: Target: Verts" << endl;
		return false;
	}
	if (ARRAYSIZE(targetIndicesData) != NUM_BOUNDTARGET_INDICES)
	{
		cout << "Error: Target: Indices" << endl;
		return false;
	}
	memcpy(targetVerts, targetVertData, sizeof(targetVertData));

	memcpy(targetIndices, targetIndicesData, sizeof(targetIndicesData));

	crossHairs.addComponent(&playerTargetCrossHairs);
	playerTargetCrossHairs.setData(&mainPlayer);

	Geometry* targetGeometry = theRender.addGeometry
		(targetVerts, NUM_TARGET_POINTS, targetIndices, NUM_BOUNDTARGET_INDICES,
		GL_LINES);

	crossPlayerInstance = theRender.addRenderable(targetGeometry);

	crossRenderer.setData(crossPlayerInstance);

	crossHairs.addComponent(&crossRenderer);

	return crossHairs.initialize(Vector3D(0.75f, 0.75f, 0.0f));

}

bool Game::initializePlayer()
{
	
	Vector3D playerVertsData[] =
	{
		//gun
		Vector3D(+0.015f, +0.045f, +1.0f),
		Vector3D(-0.015f, +0.045f, +1.0f),
		Vector3D(-0.015f, +0.0f, +1.0f),
		Vector3D(+0.015f, +0.0f, +1.0f),

		//body
		Vector3D(+0.05f, +0.0f, +1.0f),
		Vector3D(-0.05f, +0.0f, +1.0f),
		Vector3D(-0.05f, -0.05f, +1.0f),
		Vector3D(+0.05f, -0.05f, +1.0f),

	};

	GLushort playerIndicesData[] =
	{
		0, 1, 3,
		1, 3, 2,

		4, 5, 7,
		5, 7, 6
	};

	//bug checking if our constants == sizefoarray and indices
	if (ARRAYSIZE(playerVertsData) != NUM_PLAYER_VERTS)
		return false;

	if (ARRAYSIZE(playerIndicesData) != NUM_PLAYER_INDICES)
		return false;

	memcpy(playerVerts, playerVertsData, sizeof(playerVertsData));
	memcpy(playerIndices, playerIndicesData, sizeof(playerIndicesData));

	//adding components to the entity
	mainPlayer.addComponent(&mainPlayerController);
	mainPlayer.addComponent(&mainPlayerPhysics);
	playerBoundaryHandler.setData(boundaryVerts, NUM_BOUND_VERTS);
	mainPlayer.addComponent(&playerBoundaryHandler);
	

	Geometry* mainPlayerGeometry = theRender.addGeometry
		(playerVerts, NUM_PLAYER_VERTS, playerIndices, NUM_PLAYER_INDICES);

	mainPlayerInstance = theRender.addRenderable(mainPlayerGeometry);

	mainPlayerRenderer.setData(mainPlayerInstance);

	mainPlayer.addComponent(&mainPlayerRenderer);

	return mainPlayer.initialize(Vector3D(0.0f,0.0f,0.0f));

}

bool Game::initializeBoundaryData()
{
	Vector3D diamondBoundaryVertsData[] =
	{
		Vector3D(+1.5f, +0.9f, +0.0),
		Vector3D(-1.5f, +0.9f, +0.0),
		Vector3D(-1.5f, -0.9f, +0.0),
		Vector3D(+1.5f, -0.9f, +0.0),
	};

	GLushort diamondIndicesData[] =
	{
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};


	//bug checking if our constants == sizefoarray and indices
	if (ARRAYSIZE(diamondBoundaryVertsData) != NUM_BOUND_VERTS)
		return false;

	if (ARRAYSIZE(diamondIndicesData) != NUM_BOUND_INDICES)
		return false;

	memcpy(boundaryVerts, diamondBoundaryVertsData, sizeof(diamondBoundaryVertsData));

	memcpy(boundaryIndices, diamondIndicesData, sizeof(diamondIndicesData));


	Geometry* boundaryGeometry = theRender.addGeometry
		(boundaryVerts, NUM_BOUND_VERTS, boundaryIndices, NUM_BOUND_INDICES, 
		GL_LINES);

	theRender.addRenderable(boundaryGeometry);

	return true;

}

bool Game::initializeLerpData()
{

	Vector3D lerpPathData[]
	{
			Vector3D(+0.5f, +0.5f, +0.0f),
			Vector3D(-0.5f, +0.5f, +0.0f),
			Vector3D(-0.5f, -0.5f, +0.5f),
			Vector3D(+0.5f, -0.5f, +0.0f),
	};

	if (ARRAYSIZE(lerpPathData) != NUM_LERP_POINTS)
	{
		cout << "Error: Lerp: VertexData" << endl;
			return false;
	}

	//copy into memory
	memcpy(lerpVerts, lerpPathData, sizeof(lerpPathData));

	return true;
}

bool Game::initializeSquareEnemy()
{
	Vector3D squareEnemyVertData[] =
	{
		Vector3D(+0.025f, +0.025f, +1.0),
		Vector3D(-0.025f, +0.025f, +1.0),
		Vector3D(-0.025f, -0.025f, +1.0),
		Vector3D(+0.025f, -0.025f, +1.0),
	
	};

	GLushort squareEnemyIndices[] =
	{
		0, 1, 3,
		1, 3, 2,
	};

	//bug checking if our constants != sizefoarray and indices/vertdata 
	if (ARRAYSIZE(squareEnemyVertData) != NUM_BOUND_VERTS)
	{
		cout << "Enemy: Failure: VertData";
		return false;
	}

	if (ARRAYSIZE(squareEnemyIndices) != NUM_BOUNDENEMY_INDICES)
	{
		cout << "Enemy: Failure: Indices";
		return false;
	}

	//copy into memory
	memcpy(enemyVerts, squareEnemyVertData, sizeof(squareEnemyVertData));

	memcpy(enemyIndices, squareEnemyIndices, sizeof(squareEnemyIndices));

	//add components to the entity
	squareLerpComponent.setData(lerpVerts, NUM_LERP_POINTS, &mainPlayer);
	squareEnemy.addComponent(&squareLerpComponent);

	//set up geometry
	Geometry* enemyGeometry = theRender.addGeometry
		(enemyVerts, NUM_BOUND_VERTS, enemyIndices, NUM_BOUND_INDICES);

	lerpPlayerInstance = theRender.addRenderable(enemyGeometry);

	squareEnemyRenderer.setData(lerpPlayerInstance);

	squareEnemy.addComponent(&squareEnemyRenderer);

	return squareEnemy.initialize(Vector3D(0.5f, 0.5f, 0.0f));

}

