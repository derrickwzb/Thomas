#pragma once
#include "Entity.h"
#include "Thomas/Core/Timestep.h"

namespace Thomas {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}
		template<typename T>
		T& GetComponent(unsigned int entity)
		{
			return factory.GetComponent<T>(entity);
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
	};
}
