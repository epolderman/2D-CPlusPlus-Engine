#define WIN32_LEAN_AND_MEAN
#include "MyKeyMapper.h"
#include "MyMenuChoice.h"
#include <Windows.h>
#include <cassert>

namespace Input
{
	//if making another game with different controls you alter this .cpp
	//so new code can call old code(keyinput.cpp)
	int MyKeyMapper::getKeyFor(int action) const 
	{
		switch (action)
		{
		case Accelerate:
			return VK_UP;
		case RotateLeft:
			return VK_LEFT;
		case RotateRight:
			return VK_RIGHT;
		}

		assert(false);
		return -1;

	}


}