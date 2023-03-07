/*!*************************************************************************
\file           Entity.h
\author         Chen XinPeng(70%) / Derrick Woo Ze Bin (30%)
\par DP email:  c.xinpeng@digipen.edu(70%) / d.woo@digipen.edu (30%)
\par Programming CSD2400 Game project
\date           28/09/2022
\brief
This file contains functions to create entities and components to make the
game engine a component based architecture. It will store the entities and 
components separately and make it more efficient when getting the data from 
different components.
It also has the Game Object Factory to call the functions so that the user does
not need to call Entity Manager and Component Manager separately 
****************************************************************************/
#pragma once

//#include "Components.h"
#include "Thomas/Collision/Collision.h"
#include "Thomas/Physics/RigidBody.hpp"
#include "Thomas/Renderer/Asset_Manager.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Box_collider.h"
#include "Thomas/Renderer/Fonts.h"

#include "Thomas/Audio/AudioComponent.h"
#include "Thomas/Logic/Logic.h"
#include "Thomas/Scene/Scene.h"

#include "Thomas/AI/AStarPathfindingAgent.h"
#include "Thomas/AI/AStarPathfinding.h"
#include "Thomas/AI/AStarPathfindingObstacle.h"
#include "Thomas/AI/GridSystem.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/AI/Target.h"
#include "Thomas/AI/Spawner.h"
#include "Thomas/AI/SpawnSystem.h"
#include "Thomas/Renderer/Additional_Parts.h"

namespace Thomas {

	using EntityID = uint32_t;
	using ComponentType = std::uint8_t;

	// Define the size using the max component number
	const ComponentType MAX_COMPONENTS = CT_MaxComponents;
	using Signature = std::bitset<MAX_COMPONENTS>;


	class Entity
	{
	public:
		Entity() = default;
		Entity(EntityID handle, Scene* scene);
		Entity(const Entity& other) = default;

		template <typename T>
		T& AddComponent()
		{
			//TH_CORE_ASSERT(not has componnent)
			return m_Scene->m_Registry->AddComponent<T>(m_EntityHandle, T());
		}

		template<typename T>
		T& GetComponent()
		{
			//TH_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry->GetComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry->HasComponent<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			//HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry->RemoveComponent<T>(m_EntityHandle);
		}

		EntityID GetID() { return m_EntityHandle; }
		Scene* GetScene() { return m_Scene; }

		operator bool() const { return m_Scene ; }
		//operator EntityID() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		EntityID m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};


	class ScriptableEntity {
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		Scene* GetScene()
		{
			return m_Entity.GetScene();
		}

		Entity& GetSelf()
		{
			return m_Entity;
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};


	//declaration for functions in EntityManager class
	class EntityManager
	{
	public:
		EntityID CreateEntity();
		void DestroyEntity(EntityID entity);
		void SetSignature(EntityID entity, Signature signature);
		Signature GetSignature(EntityID entity);
		bool HasSignature(EntityID entity, Signature signature);
		virtual EntityID GetId() { return CurrentId; }

		std::map<EntityID, Signature>& Get() { return EntityArray; }

	private:
		//The map for EntityID and Signature
		std::map<EntityID, Signature> EntityArray;
		uint32_t CurrentId;
		uint32_t LivingEntity{};
		uint32_t TotalEntity{};
	};

	//----------------------------------------------//

	//declaration for functions in Component class
	class BaseComponent {
	public:
		virtual ~BaseComponent() = default;
		virtual void EntityDestroyed(EntityID entity) = 0;
	};

	template<typename T>
	class Component : public BaseComponent
	{
	public:
		T& InsertData(EntityID entity, T component);
		void RemoveData(EntityID entity);
		T& GetData(EntityID entity);
		void UpdateData(EntityID entity, T newcomponent);
		void EntityDestroyed(EntityID entity) override;

	private:
		// The map for entity and components.
		inline static std::map<EntityID, T> ComponentArray;
	};

	//-------------------------------------------------------------------------//

	//declaration for functions in Component Manager class
	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent();

		template<typename T>
		ComponentType GetComponentType();

		template<typename T>
		T& AddComponent(EntityID entity, T component);

		template<typename T>
		void RemoveComponent(EntityID entity);

		template<typename T>
		T& GetComponent(EntityID entity);

		template<typename T>
		void UpdateComponent(EntityID entity, T newcomponent);

		void EntityDestroyed(EntityID entity);

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
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<Component<T>>(ComponentArrays[typeName]);
		}
	};

	//-------------------------------------------------------------------------//

	//declaration for functions in GameObjectFactory class
	class GameObjectFactory
	{
	public:

		inline GameObjectFactory();

		//Functions relate to EntityID
		//Create empty entity with no components
		EntityID CreateEmptyComposition();

		//Copy and create a new entity
		EntityID Clone(EntityID entity);

		//remove entity
		void Destroy(EntityID entity);

		//remove all entity
		void DestroyAllObjects(std::vector<EntityID> allentity);

		//Functions relate to Component
		template<typename T>
		void RegisterComponent();

		template<typename T>
		T& AddComponent(EntityID entity, T component);

		template<typename T>
		void RemoveComponent(EntityID entity);

		template<typename T>
		T& GetComponent(EntityID entity);

		template<typename T>
		void UpdateComponent(EntityID entity, T newcomponent);

		template<typename T>
		bool HasComponent(EntityID entity) const;

		template<typename T>
		ComponentType GetComponentType();

		inline std::map<EntityID, Signature>& GetEntities();

	private:
		std::unique_ptr<ComponentManager> ComponentManagers;
		std::unique_ptr<EntityManager> EntityManagers;
		Signature signature;
	};

	//inline static GameObjectFactory factory;

	//------------------------------------------------------------//

	//definition for functions in EntityManager class

	//Create entity with empty signature using the TotalEntity count
	inline EntityID EntityManager::CreateEntity()
	{
		EntityID CurrentId = TotalEntity;
		Signature signature{};
		EntityArray.insert(std::pair<EntityID, Signature>(CurrentId, signature));

		++LivingEntity;
		++TotalEntity;
		return CurrentId;
	}

	//Delete EntityID from entity map
	inline void EntityManager::DestroyEntity(EntityID entity)
	{
		EntityArray[entity].reset();
		EntityArray.erase(entity);
		--LivingEntity;
	}

	//Set signature for the entity into the entity map
	inline void EntityManager::SetSignature(EntityID entity, Signature signature)
	{
		EntityArray[entity] = signature;
	}

	//Get the entity's signature from the entity map
	inline Signature EntityManager::GetSignature(EntityID entity)
	{
		return EntityArray[entity];
	}	

	//Check if the entity has the component using signature
	inline bool EntityManager::HasSignature(EntityID entity, Signature signature)
	{
		if ((EntityArray[entity] & signature) != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//-------------------------------------------------------------------------//

	//definition for functions in Component class

	//Insert the entity and component to the ComponentArray map
	template<typename T>
	inline T& Component<T>::InsertData(EntityID entity, T component)
	{
		ComponentArray.emplace(entity, component);
		return ComponentArray[entity];
	}

	//remove entity and component from ComponentArray map
	template<typename T>
	inline void Component<T>::RemoveData(EntityID entity)
	{
		ComponentArray.erase(entity);
	}

	//Get component data from ComponentArray map using entity number
	template<typename T>
	inline T& Component<T>::GetData(EntityID entity)
	{
		return ComponentArray[entity];
	}

	//change the value of the component in the entity
	template<typename T>
	inline void Component<T>::UpdateData(EntityID entity, T newcomponent)
	{
		ComponentArray[entity] = newcomponent;
	}

	// Remove the entity's component if it existed
	template<typename T>
	inline void Component<T>::EntityDestroyed(EntityID entity)
	{
		if (ComponentArray.find(entity) != ComponentArray.end())
		{
			RemoveData(entity);
		}
	}

	//-------------------------------------------------------------------------//

	//definition for functions in ComponentManager class

	//Register new component
	template<typename T>
	inline void ComponentManager::RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		// Add this component type to the component type map
		ComponentTypes[typeName] = Totalsize;

		// Create a ComponentArray pointer and add it to the component arrays map
		ComponentArrays[typeName] = std::make_shared<Component<T>>();

		// Increment the value so that the next component registered will be different
		++Totalsize;
	}

	//Get the component's type name
	template<typename T>
	inline ComponentType ComponentManager::GetComponentType()
	{
		const char* typeName = typeid(T).name();

		return ComponentTypes[typeName];
	}

	//Add a component to the map for an entity
	template<typename T>
	inline T& ComponentManager::AddComponent(EntityID entity, T component)
	{
		const char* typeName = typeid(T).name();

		return GetComponentArray<T>()->InsertData(entity, component);
	}

	//Remove a component from the map using entity number
	template<typename T>
	inline void ComponentManager::RemoveComponent(EntityID entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	//Get data from the map using entity number
	template<typename T>
	inline T& ComponentManager::GetComponent(EntityID entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	//Change the component data using entity number
	template<typename T>
	inline void ComponentManager::UpdateComponent(EntityID entity, T newcomponent)
	{
		GetComponentArray<T>()->UpdateData(entity, newcomponent);
	}


	inline void ComponentManager::EntityDestroyed(EntityID entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : ComponentArrays)
		{
			auto const& component = pair.second;

			if (component != NULL)
			{
				component->EntityDestroyed(entity);
			}
		}
	}

	//-------------------------------------------------------------------------//

	//definition for functions in GameObjectFactory class

	//Create pointers to each manager
	GameObjectFactory::GameObjectFactory()
	{
		ComponentManagers = std::make_unique<ComponentManager>();
		EntityManagers = std::make_unique<EntityManager>();

		RegisterComponent<TagComponent>();
		RegisterComponent<Transform>();
		RegisterComponent<Shader_manager>();
		RegisterComponent<Mesh>();
		RegisterComponent<Texture>();
		RegisterComponent<Box_collider>();
		RegisterComponent<RigidBody>();
		RegisterComponent<BoxCollider2D>();
		RegisterComponent<AudioComponent>();
		RegisterComponent<ScriptComponent>();
		RegisterComponent<BulletComponent>();
		RegisterComponent<ParticleComponent>();
		RegisterComponent<Particle>(); 
		RegisterComponent<ObjectType>();
		RegisterComponent<CombatComponent>();
		RegisterComponent<DeleteComponent>();
		RegisterComponent<AStarPathfindingAgent>();
		RegisterComponent<Grid>();
		RegisterComponent<AStarPathfindingObstacle>();
		RegisterComponent<Target>();
		RegisterComponent<Fonts>();
		RegisterComponent<Spawner>();
		RegisterComponent<NativeScriptComponent>();
		RegisterComponent<Additional_Parts>();
		
	}

	//Function relate to entity
	inline EntityID GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}
	
	//static std::vector<EntityID> entities;

	inline std::map<EntityID, Signature>& GameObjectFactory::GetEntities()
	{
		return EntityManagers->Get();
	}

	//copy and create a new entity with same component type and data
	inline EntityID GameObjectFactory::Clone(EntityID entity)
	{
		EntityID newentity{};

		if (entity != NULL)
			newentity = GameObjectFactory::CreateEmptyComposition();
		else
			return NULL;

		if (GameObjectFactory::HasComponent<TagComponent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<TagComponent>(entity);
			GameObjectFactory::AddComponent<TagComponent>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Transform>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Transform>(entity);
			GameObjectFactory::AddComponent<Transform>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Shader_manager>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Shader_manager>(entity);
			GameObjectFactory::AddComponent<Shader_manager>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Mesh>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Mesh>(entity);
			GameObjectFactory::AddComponent<Mesh>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Texture>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Texture>(entity);
			GameObjectFactory::AddComponent<Texture>(newentity, data);
		}
		/*if (GameObjectFactory::HasComponent<Camera>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Camera>(entity);
			GameObjectFactory::AddComponent<Camera>(newentity, data);
		}*/
		if (GameObjectFactory::HasComponent<Box_collider>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Box_collider>(entity);
			GameObjectFactory::AddComponent<Box_collider>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<RigidBody>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<RigidBody>(entity);
			GameObjectFactory::AddComponent<RigidBody>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<BoxCollider2D>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<BoxCollider2D>(entity);
			GameObjectFactory::AddComponent<BoxCollider2D>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<BulletComponent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<BulletComponent>(entity);
			GameObjectFactory::AddComponent<BulletComponent>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<ParticleComponent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<ParticleComponent>(entity);
			GameObjectFactory::AddComponent<ParticleComponent>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<ObjectType>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<ObjectType>(entity);
			GameObjectFactory::AddComponent<ObjectType>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<CombatComponent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<CombatComponent>(entity);
			GameObjectFactory::AddComponent<CombatComponent>(newentity, data);
		}

		if (GameObjectFactory::HasComponent<Grid>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Grid>(entity);
			GameObjectFactory::AddComponent<Grid>(newentity, data);
		}

		if (GameObjectFactory::HasComponent<AStarPathfindingObstacle>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<AStarPathfindingObstacle>(entity);
			GameObjectFactory::AddComponent<AStarPathfindingObstacle>(newentity, data);
		}

		if (GameObjectFactory::HasComponent<AStarPathfindingAgent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<AStarPathfindingAgent>(entity);
			GameObjectFactory::AddComponent<AStarPathfindingAgent>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Spawner>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Spawner>(entity);
			GameObjectFactory::AddComponent<Spawner>(newentity, data);
		}
		

		return newentity;
	}

	//Destory entity and components
	inline void GameObjectFactory::Destroy(EntityID gameObject)
	{
		EntityManagers->DestroyEntity(gameObject);
		ComponentManagers->EntityDestroyed(gameObject);
	}

	//Clean up the game world
	inline void GameObjectFactory::DestroyAllObjects(std::vector<EntityID> allentity)
	{
		for (auto const& entity : allentity)
		{
			EntityManagers->DestroyEntity(entity);
			ComponentManagers->EntityDestroyed(entity);
		}
	}

	//Function relate to component

	//calling ComponentManagers to register component
	template<typename T>
	inline void GameObjectFactory::RegisterComponent()
	{
		ComponentManagers->RegisterComponent<T>();
		signature.set(ComponentManagers->GetComponentType<T>());
	}

	//add new component to entity 
	template<typename T>
	inline T& GameObjectFactory::AddComponent(EntityID entity, T component)
	{
		//get the current signature
		auto signature = EntityManagers->GetSignature(entity);

		//set the signature to true
		signature.set(ComponentManagers->GetComponentType<T>(), true);
		EntityManagers->SetSignature(entity, signature);

		//add to ComponentArray map
		return ComponentManagers->AddComponent<T>(entity, component);
	}

	//remove component from entity
	template<typename T>
	inline void GameObjectFactory::RemoveComponent(EntityID entity)
	{
		ComponentManagers->RemoveComponent<T>(entity);

		//get and update signature
		auto signature = EntityManagers->GetSignature(entity);
		signature.set(ComponentManagers->GetComponentType<T>(), false);
		EntityManagers->SetSignature(entity, signature);
	}

	//calling ComponentManagers to get component data
	template<typename T>
	inline T& GameObjectFactory::GetComponent(EntityID entity)
	{
		return ComponentManagers->GetComponent<T>(entity);
	}

	//calling ComponentManagers to change component data
	template<typename T>
	inline void GameObjectFactory::UpdateComponent(EntityID entity, T newcomponent)
	{
		ComponentManagers->UpdateComponent<T>(entity, newcomponent);
	}

	//check if the entity has the component
	template<typename T>
	inline bool GameObjectFactory::HasComponent(EntityID entity) const
	{
		auto getsignature = ComponentManagers->GetComponentType<T>();
		auto bit = pow(2, getsignature);

		return EntityManagers->HasSignature(entity, Signature((size_t)bit));
	}

	//calling ComponentManagers to get component type name
	template<typename T>
	inline ComponentType GameObjectFactory::GetComponentType()
	{
		return ComponentManagers->GetComponentType<T>();
	}

	
}
