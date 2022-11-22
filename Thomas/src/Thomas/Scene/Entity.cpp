/*!*************************************************************************
\file				Entity.cpp
\author				Derrick Woo
\par DP email:		d.woo@digipen.edu
\par Programming	CSD2400
\date				22/11/22
\brief
Constructor for entity class
****************************************************************************/
#include "thpch.h"
#include "Thomas/Scene/Entity.h"

namespace Thomas
{
	Entity::Entity(EntityID handle, Scene* scene)
		: m_EntityHandle(handle) , m_Scene(scene)
	{

	}
}