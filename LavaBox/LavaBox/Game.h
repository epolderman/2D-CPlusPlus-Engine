#ifndef GAME_H
#define GAME_H
#include <Renderer.h>
#include <Qt\qobject.h>
#include <Entity.h>
#include <RendererComponent.h>
#include <Qt\qtimer.h>
#include <PhysicsComponent.h>
#include "MyKeyMapper.h"
#include "ControllerComponent.h"
#include "BoundaryComponent.h"
#include "LerpComponent.h"
#include "TargetComponent.h"




//GAME PRODUCTION NOTE/RULE//
//we turn off exceptions(costly and a lot of runtime overhead)
//we dont want that which is why we use true or false bool initialize()
//if we use a constructor we cannot report an error

class Game : public QObject
{

	Q_OBJECT; //in order to use signals and slots you must declare that our game
	//is a QOBJECT(copy paste macro)

	QTimer theTimer;

	Input::MyKeyMapper keyMapper;

	//data for cache coherency
	Entities::Entity mainPlayer;
	Entities::RendererComponent mainPlayerRenderer;
	Entities::PhysicsComponent mainPlayerPhysics;
	Entities::ControllerComponent mainPlayerController;
	Entities::BoundaryComponent playerBoundaryHandler;
	
	//enemy
	Entities::Entity squareEnemy;
	Entities::RendererComponent squareEnemyRenderer;
	Entities::LerpComponent squareLerpComponent;

	//crosshair
	Entities::Entity crossHairs;
	Entities::RendererComponent crossRenderer;
	Entities::TargetComponent playerTargetCrossHairs;
	
	//main render property
	Rendering::Renderer theRender;
	Rendering::Renderable* mainPlayerInstance;
	Rendering::Renderable* lerpPlayerInstance;
	Rendering::Renderable* crossPlayerInstance;

	//mainplayer static data
	static const uint NUM_PLAYER_VERTS = 8;
	Vector3D playerVerts[NUM_PLAYER_VERTS];
	static const uint NUM_PLAYER_INDICES = 12;
	ushort playerIndices[NUM_PLAYER_INDICES];

	//boundary static data
	static const uint NUM_BOUND_VERTS = 4;
	Vector3D boundaryVerts[NUM_BOUND_VERTS];
	static const uint NUM_BOUND_INDICES = 8;
	ushort boundaryIndices[NUM_BOUND_INDICES];

	//square enemy static data
	static const uint NUM_BOUNDENEMY_INDICES = 6;
	Vector3D enemyVerts[NUM_BOUND_VERTS];
	ushort enemyIndices[NUM_BOUNDENEMY_INDICES];

	//lerp static data
	static const uint NUM_LERP_POINTS = 4;
	Vector3D lerpVerts[NUM_LERP_POINTS];

	//target data (crosshairs)
	static const uint NUM_TARGET_POINTS = 4;
	Vector3D targetVerts[NUM_TARGET_POINTS];
	static const uint NUM_BOUNDTARGET_INDICES = 4;
	ushort targetIndices[NUM_BOUNDTARGET_INDICES];

	//initilazation scheme we are following
	bool initializePlayer();
	bool initializeBoundaryData();
	bool initializeSquareEnemy();
	bool initializeLerpData();
	bool initializeTargetData();

	private slots:
		void update(); //30-60 times a second
	public:
		bool initialize();
		bool shutdown();
		void Go();



};

#endif