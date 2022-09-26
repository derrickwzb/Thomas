#pragma once

#include <bitset>
#include <queue>
#include <array>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include "Collision2D.hpp"

enum ComponentTypeId
{
	//Invalid component id
	CT_None = 0,
	CT_Point,
	CT_Colour,
	CT_Triangle,
	CT_Rigid,

	//Max
	CT_MaxComponents
};

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

Entity EntityManager::CreateEntity()
{
	Entity CurrentId = TotalEntity;
	Signature signature{};
	EntityArray.insert(std::pair<Entity, Signature>(CurrentId, signature));

	++LivingEntity;
	++TotalEntity;
	return CurrentId;
}

void EntityManager::DestroyEntity(Entity entity)
{
	EntityArray.erase(entity);
	--LivingEntity;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	// Put this entity's signature into the array
	EntityArray[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	// Get this entity's signature from the array
	return EntityArray[entity];
}

bool EntityManager::HasSignature(Entity entity, Signature signature)
{
	//check if the entity have the component
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

template<typename T>
void Component<T>::InsertData(Entity entity, T component) 
{
	size_t newIndex = Size;
	EntityMap[entity] = newIndex;
	ComponentArray.push_back(component);
	++Size;
}

template<typename T>
void Component<T>::RemoveData(Entity entity)
{
	// Copy element at end into deleted element's place to maintain density
	size_t temp = EntityMap[entity];
	ComponentArray[EntityMap[entity]] = ComponentArray[Size - 1];
	//EntityMap.end() = EntityMap[entity];
	//EntityMap.at(EntityMap.end()) = EntityMap[entity];
	auto it = EntityMap.end();
	--it;
	(*it).second = temp;

	EntityMap.erase(entity);
	--Size;
}

template<typename T>
T& Component<T>::GetData(Entity entity)
{
	// Return a reference to the entity's component
	return ComponentArray[EntityMap[entity]];
}

template<typename T>
void Component<T>::ChangeData(Entity entity, T newcomponent)
{
	//change the value of the component in the entity
	ComponentArray[entity] = newcomponent;
}

template<typename T>
void Component<T>::EntityDestroyed(Entity entity)
{
	if (EntityMap.find(entity) != EntityMap.end())
	{
		// Remove the entity's component if it existed
		RemoveData(entity);
	}
}

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

template<typename T>
void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();

	// Add this component type to the component type map
	ComponentTypes[typeName] = Totalsize;

	// Create a ComponentArray pointer and add it to the component arrays map
	ComponentArrays[typeName] = std::make_shared<Component<T>>();
	//ComponentArrays.insert(std::pair<const char*, std::vector<T>>(typeName, ComponentArray.push_back(component);
	//std::shared_ptr<Component<T>> ComponentArrays[typeName](new Component<T>);
	//ComponentArrays[typeName] = (new Component<T>);

	// Increment the value so that the next component registered will be different
	++Totalsize;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(T).name();

	// Return this component's type - used for creating signatures
	return ComponentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
	const char* typeName = typeid(T).name();
	
	//Component<T>	ComponentArrays[typeName];
	// Add a component to the array for an entity
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	// Remove a component from the array for an entity
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	// Get a reference to a component from the array for an entity
	return GetComponentArray<T>()->GetData(entity);
}

template<typename T>
void ComponentManager::ChangeComponent(Entity entity, T newcomponent)
{
	// Add a component to the array for an entity
	GetComponentArray<T>()->ChangeData(entity, newcomponent);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
	// Notify each component array that an entity has been destroyed
	// If it has a component for that entity, it will remove it
	for (auto const& pair : ComponentArrays)
	{
		auto const& component = pair.second;

		component->EntityDestroyed(entity);
	}
}

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


template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();

	// Create a pointer to the system and return it so it can be used externally
	std::shared_ptr<T> system = std::make_shared<T>();
	Systems.insert({ typeName, system });
	return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	// Set the signature for this system
	Signatures.insert({ typeName, signature });
}

void SystemManager::EntityDestroyed(Entity entity)
{
	// Erase a destroyed entity from all system lists
	// mEntities is a set so no check needed
	for (auto const& pair : Systems)
	{
		auto const& system = pair.second;

		system->Entities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : Systems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = Signatures[type];

		// Entity signature matches system signature - insert into set
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->Entities.insert(entity);
		}
		// Entity signature does not match system signature - erase from set
		else
		{
			system->Entities.erase(entity);
		}
	}
}

//-------------------------------------------------------------------------//

class Coordinator
{
public:
	void Init();

	// Entity methods
	Entity CreateEntity();

	void DestroyEntity(Entity entity);

	// Component methods
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
	//std::vector<std::unique_ptr<EntityManager>> Entities;
};

// Entity methods
void Coordinator::Init()
{
	// Create pointers to each manager
	ComponentManagers = std::make_unique<ComponentManager>();
	//std::unique_ptr<ComponentManager> ComponentManagers(new ComponentManager);
	EntityManagers = std::make_unique<EntityManager>();
	//std::unique_ptr<EntityManager> EntityManagers(new EntityManager);
	SystemManagers = std::make_unique<SystemManager>();
}

Entity Coordinator::CreateEntity()
{
	return EntityManagers->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity)
{
	EntityManagers->DestroyEntity(entity);

	ComponentManagers->EntityDestroyed(entity);

	SystemManagers->EntityDestroyed(entity);
}


// Component methods
template<typename T>
void Coordinator::RegisterComponent()
{
	ComponentManagers->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity entity, T component)
{
	ComponentManagers->AddComponent<T>(entity, component);

	auto signature = EntityManagers->GetSignature(entity);

	signature.set(ComponentManagers->GetComponentType<T>(), true);
	EntityManagers->SetSignature(entity, signature);

	SystemManagers->EntitySignatureChanged(entity, signature);
}

template<typename T>
void Coordinator::RemoveComponent(Entity entity)
{
	ComponentManagers->RemoveComponent<T>(entity);

	auto signature = EntityManagers->GetSignature(entity);
	signature.set(ComponentManagers->GetComponentType<T>(), false);
	EntityManagers->SetSignature(entity, signature);

	SystemManagers->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& Coordinator::GetComponent(Entity entity)
{
	return ComponentManagers->GetComponent<T>(entity);
}

template<typename T>
void Coordinator::ChangeComponent(Entity entity, T newcomponent)
{
	ComponentManagers->ChangeComponent<T>(entity, newcomponent);
}

template<typename T>
bool Coordinator::HasComponent(Entity entity) const
{
	auto getsignature = ComponentManagers->GetComponentType<T>();
	auto bit = pow(2, getsignature);

	return EntityManagers->HasSignature(entity, Signature(bit));
}

template<typename T>
ComponentType Coordinator::GetComponentType()
{
	return ComponentManagers->GetComponentType<T>();
}

// System methods
template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
	return SystemManagers->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature signature)
{
	SystemManagers->SetSignature<T>(signature);
}

//-------------------------------------------------------------------------//

struct Point {
	float positionx;
	float positiony;
};

struct Colour {
	float r;
	float g;
	float b;
	float a;
};

struct Triangle {
	float positionx;
	float positiony;
	float positionz;
};

//struct Rigidbody2DComponent
//{
//	//enum class BodyType { Static = 0, Dynamic, Kinematic };
//	//BodyType Type = BodyType::Static;
//	//bool FixedRotation = false;
//
//	// object current position
//	Vec2 posCurr = { 0.f, 0.f };
//	// object current velocity
//	Vec2 velCurr = { 0.f, 0.f };
//	// object current direction
//	float dirCurr = { 0.f };
//
//	// Storage for runtime
//	void* RuntimeBody = nullptr;
//
//	Rigidbody2DComponent() = default;
//	Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
//};
