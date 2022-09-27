
#include "thpch.h"
#include "Entity.h"

namespace Thomas {


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


	template<typename T>
	void ComponentManager::RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		// Add this component type to the component type map
		ComponentTypes[typeName] = Totalsize;

		// Create a ComponentArray pointer and add it to the component arrays map
		ComponentArrays[typeName] = std::make_shared<Component<T>>();

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

	//GameObjectFactory factory;
	
	void GameObjectFactory::Init()
	{
		// Create pointers to each manager
		ComponentManagers = std::make_unique<ComponentManager>();
		EntityManagers = std::make_unique<EntityManager>();
		SystemManagers = std::make_unique<SystemManager>();
	}

	Entity GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}

	Entity GameObjectFactory::BuildAndSerialize(const std::string& filename)
	{

		//Open the text file stream serializer
		std::ifstream stream;
		stream.open(filename.c_str(), std::ios_base::in);
		if (!stream)
		{
			std::cout << "File " << filename
				<< " not found." << "\n";
		}
		std::string line;
		std::string text;
		//std::string componentName{};
		int i = 0;
		float f = 0;

		Entity gameObject = GameObjectFactory::CreateEmptyComposition();

		while (!stream.eof())
		{
			//std::getline(stream, line);
			//std::istringstream line_name{ line };
			//get component type
			stream >> text;

			if (text == "Position")
			{
				Position newpos;
				stream >> f;
				newpos.x = f;
				stream >> f;
				newpos.y = f;

				GameObjectFactory::AddComponent<Position>(gameObject, newpos);
			}
			else if (text == "Colour")
			{
				Colour newcolour;
				stream >> newcolour.r;
				stream >> newcolour.g;
				stream >> newcolour.b;
				stream >> newcolour.a;

				GameObjectFactory::AddComponent<Colour>(gameObject, newcolour);
			}
			else if (text == "Rigidbody2DComponent")
			{
				Rigidbody2DComponent newrigidbody;
				stream >> newrigidbody.posCurr.x;
				stream >> newrigidbody.posCurr.y;
				stream >> newrigidbody.velCurr.x;
				stream >> newrigidbody.velCurr.y;
				stream >> newrigidbody.dirCurr;

				GameObjectFactory::AddComponent<Rigidbody2DComponent>(gameObject, newrigidbody);
			}
			else if (text == "Bounds")
			{
				Bounds newbounds;
				stream >> newbounds.centre.x;
				stream >> newbounds.centre.y;
				stream >> newbounds.extents.x;
				stream >> newbounds.extents.y;
				stream >> newbounds.max.x;
				stream >> newbounds.max.y;
				stream >> newbounds.min.x;
				stream >> newbounds.min.y;
				stream >> newbounds.size.x;
				stream >> newbounds.size.y;

				GameObjectFactory::AddComponent<Bounds>(gameObject, newbounds);
			}
			else if (text == "Bounds")
			{
				Bounds newbounds;
				stream >> newbounds.centre.x;
				stream >> newbounds.centre.y;
				stream >> newbounds.extents.x;
				stream >> newbounds.extents.y;
				stream >> newbounds.max.x;
				stream >> newbounds.max.y;
				stream >> newbounds.min.x;
				stream >> newbounds.min.y;
				stream >> newbounds.size.x;
				stream >> newbounds.size.y;

				GameObjectFactory::AddComponent<Bounds>(gameObject, newbounds);
			}
			else if (text == "Collider2D")
			{
				Collider2D newcollider;
				stream >> newcollider.bounciness;
				stream >> newcollider.offset.x;
				stream >> newcollider.offset.y;
				stream >> newcollider.isTrigger;
				stream >> newcollider.friction;

				GameObjectFactory::AddComponent<Collider2D>(gameObject, newcollider);
			}
			else if (text == "BoxCollider2D")
			{
				BoxCollider2D newboxcollider;
				stream >> newboxcollider.bounciness;
				stream >> newboxcollider.offset.x;
				stream >> newboxcollider.offset.y;
				stream >> newboxcollider.isTrigger;
				stream >> newboxcollider.friction;
				stream >> newboxcollider.size.x;
				stream >> newboxcollider.size.y;

				GameObjectFactory::AddComponent<BoxCollider2D>(gameObject, newboxcollider);
			}
			else if (text == "BoxCollider2D")
			{
				BoxCollider2D newboxcollider;
				stream >> newboxcollider.bounciness;
				stream >> newboxcollider.offset.x;
				stream >> newboxcollider.offset.y;
				stream >> newboxcollider.isTrigger;
				stream >> newboxcollider.friction;
				stream >> newboxcollider.size.x;
				stream >> newboxcollider.size.y;

				GameObjectFactory::AddComponent<BoxCollider2D>(gameObject, newboxcollider);
			}
			else if (text == "CircleCollider2D")
			{
				CircleCollider2D newcirclecollider;
				stream >> newcirclecollider.bounciness;
				stream >> newcirclecollider.offset.x;
				stream >> newcirclecollider.offset.y;
				stream >> newcirclecollider.isTrigger;
				stream >> newcirclecollider.friction;
				stream >> newcirclecollider.radius;
				//stream >> newcirclecollider.mass;

				GameObjectFactory::AddComponent<CircleCollider2D>(gameObject, newcirclecollider);
			}
			else if (text == "ColliderDistance2D")
			{
				ColliderDistance2D newcolliderdistance;
				stream >> newcolliderdistance.distance;
				stream >> newcolliderdistance.isOverlapped;
				stream >> newcolliderdistance.isValid;
				stream >> newcolliderdistance.normal.x;
				stream >> newcolliderdistance.normal.y;
				stream >> newcolliderdistance.pointA.x;
				stream >> newcolliderdistance.pointA.y;
				stream >> newcolliderdistance.pointB.x;
				stream >> newcolliderdistance.pointB.y;

				GameObjectFactory::AddComponent<ColliderDistance2D>(gameObject, newcolliderdistance);
			}
			else if (text == "Collision2D")
			{
			Collision2D newcollision;
			stream >> newcollision.relativeVelocity.x;
			stream >> newcollision.relativeVelocity.y;
			stream >> newcollision.enabled;

			GameObjectFactory::AddComponent<Collision2D>(gameObject, newcollision);
			}
			else if (text == "LineSegment")
			{
			LineSegment newlinesegment;
			stream >> newlinesegment.pt0.x;
			stream >> newlinesegment.pt0.y;
			stream >> newlinesegment.pt1.x;
			stream >> newlinesegment.pt1.y;
			stream >> newlinesegment.normal.x;
			stream >> newlinesegment.normal.y;

			GameObjectFactory::AddComponent<LineSegment>(gameObject, newlinesegment);
			}
			else if (text == "Ray")
			{
			Ray newray;
			stream >> newray.direction.x;
			stream >> newray.direction.x;
			stream >> newray.origin.x;
			stream >> newray.origin.x;

			GameObjectFactory::AddComponent<Ray>(gameObject, newray);
			}
			
		}

		return gameObject;
	}

	Entity GameObjectFactory::Clone(Entity entity) 
	{
		Entity newentity = GameObjectFactory::CreateEmptyComposition();

		if (GameObjectFactory::HasComponent<Position>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Position>(entity);
			GameObjectFactory::AddComponent<Position>(newentity, data);
		}
		else if (GameObjectFactory::HasComponent<Colour>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Colour>(entity);
			GameObjectFactory::AddComponent<Colour>(newentity, data);
		}
		else if (GameObjectFactory::HasComponent<Triangle>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Triangle>(entity);
			GameObjectFactory::AddComponent<Triangle>(newentity, data);
		}
		else if (GameObjectFactory::HasComponent<Rigidbody2DComponent>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Rigidbody2DComponent>(entity);
			GameObjectFactory::AddComponent<Rigidbody2DComponent>(newentity, data);
		}

		return newentity;
	}

	void GameObjectFactory::Destroy(Entity gameObject)
	{
		EntityManagers->DestroyEntity(gameObject);

		ComponentManagers->EntityDestroyed(gameObject);

		SystemManagers->EntityDestroyed(gameObject);
	}

	//Clean up the game world
	void GameObjectFactory::DestroyAllObjects(std::vector<Entity> allentity)
	{

		for (auto const& entity : allentity)
		{
			EntityManagers->DestroyEntity(entity);

			ComponentManagers->EntityDestroyed(entity);

			SystemManagers->EntityDestroyed(entity);
		}
	}

	//Component
	// Component methods
	template<typename T>
	void GameObjectFactory::RegisterComponent()
	{
		ComponentManagers->RegisterComponent<T>();
	}

	template<typename T>
	void GameObjectFactory::AddComponent(Entity entity, T component)
	{
		ComponentManagers->AddComponent<T>(entity, component);

		auto signature = EntityManagers->GetSignature(entity);

		signature.set(ComponentManagers->GetComponentType<T>(), true);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void GameObjectFactory::RemoveComponent(Entity entity)
	{
		ComponentManagers->RemoveComponent<T>(entity);

		auto signature = EntityManagers->GetSignature(entity);
		signature.set(ComponentManagers->GetComponentType<T>(), false);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GameObjectFactory::GetComponent(Entity entity)
	{
		return ComponentManagers->GetComponent<T>(entity);
	}

	template<typename T>
	void GameObjectFactory::ChangeComponent(Entity entity, T newcomponent)
	{
		ComponentManagers->ChangeComponent<T>(entity, newcomponent);
	}

	template<typename T>
	bool GameObjectFactory::HasComponent(Entity entity) const
	{
		auto getsignature = ComponentManagers->GetComponentType<T>();
		auto bit = pow(2, getsignature);

		return EntityManagers->HasSignature(entity, Signature(bit));
	}

	template<typename T>
	ComponentType GameObjectFactory::GetComponentType()
	{
		return ComponentManagers->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> GameObjectFactory::RegisterSystem()
	{
		return SystemManagers->RegisterSystem<T>();
	}

	template<typename T>
	void GameObjectFactory::SetSystemSignature(Signature signature)
	{
		SystemManagers->SetSignature<T>(signature);
	}

}
