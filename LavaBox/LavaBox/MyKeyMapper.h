#ifndef MY_KEY_MAPPER_H
#define MY_KEY_MAPPER_H
#include <InputKeyMapper.h>

namespace Input
{
	
	class MyKeyMapper : public InputKeyMapper
	{
	public:
		int getKeyFor(int action) const override;

	};
}


#endif