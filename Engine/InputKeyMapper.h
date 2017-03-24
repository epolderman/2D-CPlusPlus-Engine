#ifndef ENGINE_INPUT_KEY_MAPPER_H
#define ENGINE_INPUT_KEY_MAPPER_H


namespace Input

{

	class InputKeyMapper
	{

	public://abstract
		virtual int getKeyFor(int action) const = 0;
				
	};


}



#endif