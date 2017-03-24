#include "RendererComponent.h"
#include "Renderable.h"
#include "Matrix2DE.h"
#include "Entity.h"

namespace Entities
{

	void RendererComponent::setData(Rendering::Renderable* renderable)
	{
		this->renderable = renderable;
	}
	void RendererComponent::update()
	{
		renderable->where = Matrix2DE::translate(getParent()->position) *
			Matrix2DE::rotateZ(getParent()->orientation);
		
	}




}