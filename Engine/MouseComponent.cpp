#include "MouseComponent.h"
#include <iostream>
#include "PhysicsComponent.h"
using std::cout;
using std::endl;

namespace Entities
{
	bool MouseComponent::initialize()
	{
		lastMousePosition.setX(0);
		lastMousePosition.setY(0);
		latestMousePosition.setX(0);
		latestMousePosition.setY(0);
		mouseDelta.setX(0);
		mouseDelta.setY(0);
		physics = getParent()->getComponent<PhysicsComponent>();
		return physics != 0;
	}

	void MouseComponent::update()
	{


		//const float ANGULAR_VELOCITY = 0.1f;
		//Vector3D temp;
		//temp = mouseDelta - physics->getParent()->position;
		//float dot = temp.Dot(Vector3D(-sin(getParent()->orientation), cos(getParent()->orientation)));
		//cout << "Dot: " << dot << endl;
		
		//cout << "X:" << mouseDelta.getX() << endl;
		//cout << "Y:" << mouseDelta.getY() << endl;
		//cout << "Angular Physics: " << physics->angularVelocity << endl;

		//cout << "Angular change: " << (mouseDelta.getY() / 10) << endl;

		/*if (mouseDelta.getX() != lastMousePosition.getX())
			physics->angularVelocity = (mouseDelta.getY() / 10);*/


	


		//mouseDelta.setX(0);
		//mouseDelta.setY(0);
		//cout << "Angular Physics after: " << physics->angularVelocity << endl;
		

		
	}

	void MouseComponent::grabMouse(const Vector& data)
	{
		mouseDelta.setX(data.getX());
		mouseDelta.setY(data.getY());
		//update();
		Vector3D temp;
		temp = mouseDelta - physics->getParent()->position;
		float dot = temp.Dot(Vector3D(-sin(getParent()->orientation), cos(getParent()->orientation)));
		cout << "Dot: " << dot << endl;


	}
	
}