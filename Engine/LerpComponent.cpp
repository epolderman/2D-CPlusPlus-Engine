#include "LerpComponent.h"
#include "GameClock.h"


namespace Entities
{

	LerpComponent::LerpComponent()
	{
		lerpPath = 0;
		mainPlayer = 0;
	}
	bool LerpComponent::initialize()
	{
		bool ready = true;

		if (NUM_LERP_POINTS > 1)
		{
			lerpSourcePoint = 0;

			lerpDestinationPoint = 1;

			lerpAlpha = 0.0f;
		}
		else
		{	
			ready = false;
		}

		return lerpPath != 0 && mainPlayer != 0 && ready;
	}
	void LerpComponent::setData(Vector3D* theVerts, uint numPoints, Entity* mainPlayerz)
	{
		NUM_LERP_POINTS = numPoints;
		this->lerpPath = theVerts;
		this->mainPlayer = mainPlayerz;
	}
	//pathfinding to the main player
	void LerpComponent::update()
	{
		
		lerpAlpha += 0.00001f;
		if (lerpAlpha >= 0.015f 
			|| (getParent()->position.getX() == mainPlayer->position.getX())
			|| (getParent()->position.getY() == mainPlayer->position.getY()))
		{
			lerpAlpha = 0.0f;
		}
		Vector3D source = getParent()->position;
		Vector3D destination = mainPlayer->position;
		lerpCurrentPosition = source.lerp(lerpAlpha, destination);
		getParent()->position = lerpCurrentPosition;

	}
	void LerpComponent::targetNextLerpPoint()
	{
		lerpSourcePoint = lerpDestinationPoint;
		lerpDestinationPoint = (lerpDestinationPoint + 1) % NUM_LERP_POINTS;
	}

	//for pathfinding between fixed points
	void LerpComponent::pathfindingLerper()
	{
		lerpAlpha += (gameClock.dt() / 2); //speed of 1 per second
		if (lerpAlpha >= 1.0f)
		{
			lerpAlpha = 0.0f;
			targetNextLerpPoint();
		}
		Vector3D source = lerpPath[lerpSourcePoint];
		Vector3D destination = lerpPath[lerpDestinationPoint];
		lerpCurrentPosition = source.lerp(lerpAlpha, destination);
		getParent()->position = lerpCurrentPosition;
	}



}