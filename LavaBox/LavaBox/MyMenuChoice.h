#ifndef MY_MENU_CHOICE_H
#define MY_MENU_CHOICE_H

namespace Input
{

	enum MyMenuChoice
	{
		Accelerate = 0x00000001,
		RotateLeft = 0x00000002,
		RotateRight = 0x00000004,
		MAX = 0x00000008,
	};

}



#endif