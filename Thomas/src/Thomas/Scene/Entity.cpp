#include "thpch.h"
#include "Thomas/Scene/Entity.h"

namespace Thomas
{
	Entity::Entity(EntityID handle, Scene* scene)
		: m_EntityHandle(handle) , m_Scene(scene)
	{

	}
}