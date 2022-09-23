#pragma once


#include "thpch.h"
#include "Entity.h"

namespace Thomas {

	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		~GameObjectFactory();

		///Create and Id a GOC at runtime. Used to dynamically build GOC.
		///After components have been added call GOC->Initialize().
		Entity CreateEmptyComposition();

		///Build a composition and serialize from the data file but do not initialize the GOC.
		///Used to create a composition and then adjust its data before initialization
		///see GameObjectComposition::Initialize for details.
		//Entity BuildAndSerialize(const std::string& filename);

		///Create initialize and Id a GOC from the data file.
		//Entity Create(const std::string& filename);

		///Add a GOC to the destroy list for delayed destruction.
		void Destroy(Entity gameObject);

		///Destroy all the GOCs in the world. Used for final shutdown.
		void DestroyAllObjects(std::vector<Entity> allentity);

		//Component
		template<typename T>
		void RegisterComponent();

		template<typename T>
		void AddComponent(Entity entity, T component);

		template<typename T>
		void RemoveComponent(Entity entity);

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename T>
		void ChangeComponent(Entity entity, T newcomponent);

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename T>
		ComponentType GetComponentType();

		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem();

		template<typename T>
		void SetSystemSignature(Signature signature);


	private:
		std::unique_ptr<ComponentManager> ComponentManagers;
		std::unique_ptr<EntityManager> EntityManagers;
		std::unique_ptr<SystemManager> SystemManagers;
	};
}


