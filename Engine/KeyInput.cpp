#include <Windows.h>
#include "KeyInput.h"
#include "InputKeyMapper.h"


namespace Input
{

	KeyInput KeyInput::instance; //define static memory; //singleton pattern

	bool KeyInput::initialize(InputKeyMapper* map, int maxActionValue)
	{
		if (map == 0 || maxActionValue < 0)
			return false;
		this->map = map;
		this->maxActionValue = maxActionValue;
		return true;
	}
	bool KeyInput::shutdown()
	{
		return true;
	}
	void KeyInput::update()
	{
		//initialize bits to 0 in array
		actionsRequested = 0;
		//put 0,0,0,1 in array
		int possibleAction = 1;

		while (possibleAction != maxActionValue)
		{
			int key = map->getKeyFor(possibleAction);
			if (GetAsyncKeyState(key))
			{
				//ORing the accelerated value 0001 vs 0000 which returns true then 0001
				actionsRequested |= possibleAction;
			}

			possibleAction <<= 1;
		}
	}


	//bitwise && bit arrays(computer architecture)
	bool KeyInput::actionsHotThisFrame(int actions) const
	{
		return actionsRequested & actions;
	}
	int KeyInput::actionsThisFrame() const
	{
		return actionsRequested;
	}
	KeyInput& KeyInput::getInstance()
	{
		return instance;
	}

	

}