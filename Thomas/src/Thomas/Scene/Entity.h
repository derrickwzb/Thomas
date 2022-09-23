#pragma once

#include "thpch.h"
#include "Components.h"
#include "ComponentType.h"

namespace Thomas {

	using Entity = unsigned int;
	using ComponentType = std::uint8_t;

	// Define the size
	const ComponentType MAX_COMPONENTS = CT_MaxComponents;

	// Setting bit for signature
	using Signature = std::bitset<MAX_COMPONENTS>;

	class EntityManager
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void SetSignature(Entity entity, Signature signature);
		Signature GetSignature(Entity entity);
		bool HasSignature(Entity entity, Signature signature);
		Entity GetId() { return CurrentId; }

	private:
		std::map<Entity, Signature> EntityArray;
		unsigned int CurrentId;
		unsigned int LivingEntity{};
		unsigned int TotalEntity{};
	};

	//----------------------------------------------//


	class BaseComponent {
	public:
		virtual ~BaseComponent() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class Component : public BaseComponent
	{
	public:
		void InsertData(Entity entity, T component);
		void RemoveData(Entity entity);
		T& GetData(Entity entity);
		void ChangeData(Entity entity, T newcomponent);
		void EntityDestroyed(Entity entity) override;

	private:
		// The array of components.
		std::vector<T> ComponentArray;

		// Map from an entity ID to an array index.
		std::map<Entity, size_t> EntityMap;

		// Total size of valid entries in the array.
		size_t Size;
	};

	//-------------------------------------------------------------------------//

	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent();

		template<typename T>
		ComponentType GetComponentType();

		template<typename T>
		void AddComponent(Entity entity, T component);

		template<typename T>
		void RemoveComponent(Entity entity);

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename T>
		void ChangeComponent(Entity entity, T newcomponent);

		void EntityDestroyed(Entity entity);

	private:
		// Map from type string pointer to a component type
		std::map<const char*, ComponentType> ComponentTypes{};

		// Map from type string pointer to a component array
		std::map<const char*, std::shared_ptr<BaseComponent>> ComponentArrays{};

		// The component type to be assigned to the next registered component 
		ComponentType Totalsize{};

		// Convenience function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<Component<T>> GetComponentArray()
			//std::shared_ptr<Component<T>> GetComponentArray(Type id)
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<Component<T>>(ComponentArrays[typeName]);
			//return std::static_pointer_cast<Component<T>>(ComponentArrays[id])
		}

		//std::shared_ptr<Component<T>> GetComponentArray(Type id)
		//return std::static_pointer_cast<Component<T>>(ComponentArrays[id])
		// 
		//register with id, which is position of bit
	};

	//-------------------------------------------------------------------------//

	class System
	{
	public:
		std::set<Entity> Entities;
	};


	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem();

		template<typename T>
		void SetSignature(Signature signature);

		void EntityDestroyed(Entity entity);

		void EntitySignatureChanged(Entity entity, Signature entitySignature);

	private:
		// Map from system type string pointer to a signature
		std::map<const char*, Signature> Signatures{};

		// Map from system type string pointer to a system pointer
		std::map<const char*, std::shared_ptr<System>> Systems{};
	};

	//-------------------------------------------------------------------------//

	class GameObjectFactory
	{
	public:

		void Init();

		///Create and Id a GOC at runtime. Used to dynamically build GOC.
		///After components have been added call GOC->Initialize().
		Entity CreateEmptyComposition();

		///Build a composition and serialize from the data file but do not initialize the GOC.
		///Used to create a composition and then adjust its data before initialization
		///see GameObjectComposition::Initialize for details.
		Entity BuildAndSerialize(const std::string& filename);

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
