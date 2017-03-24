#include "TargetComponent.h"

namespace Entities
{
	TargetComponent::TargetComponent()
	{
		mainPlayer = 0;
	}
	bool TargetComponent::initialize()
	{
		return true;
	}
	void TargetComponent::setData(Entity* mainplayer)
	{
		this->mainPlayer = mainplayer;
	}
	void TargetComponent::update()
	{
		Vector3D direction = Vector3D(-sin(mainPlayer->orientation), cos(mainPlayer->orientation)).Normalize();
		direction = direction * .3;
		Vector3D playPos = mainPlayer->position;
		Vector3D augPosition = playPos + direction;
		getParent()->orientation = mainPlayer->orientation;
		getParent()->position = augPosition;
	}














}