#pragma once


#include "Components.h"
#include "Thomas/Collision/Collision.hpp"
//#include "ComponentType.h"

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
		inline static std::map<Entity, Signature> EntityArray;
		inline static unsigned int CurrentId;
		inline static unsigned int LivingEntity{};
		inline static unsigned int TotalEntity{};
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
		//void PositionUpdate(float x, float y);

	private:
		// The array of components.
		/*inline static std::vector<T> ComponentArray;*/
		inline static std::map<Entity, T> ComponentArray;

		// Map from an entity ID to an array index.
		//inline static std::map<Entity, size_t> EntityMap;
		//using ComponentVector = std::vector<T>;
		/*inline static std::map<Entity, ComponentArray> EntityMap;*/

		// Total size of valid entries in the array.
		/*inline static size_t Size{};*/
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
		inline static std::map<const char*, ComponentType> ComponentTypes{};

		// Map from type string pointer to a component array
		inline static std::map<const char*, std::shared_ptr<BaseComponent>> ComponentArrays{};

		// The component type to be assigned to the next registered component 
		inline static ComponentType Totalsize{};

		// Convenience function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<Component<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<Component<T>>(ComponentArrays[typeName]);
		}

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
		inline static std::map<const char*, Signature> Signatures{};

		// Map from system type string pointer to a system pointer
		inline static std::map<const char*, std::shared_ptr<System>> Systems{};
	};

	//-------------------------------------------------------------------------//

	class GameObjectFactory
	{
	public:

		void Init();

		//Entity

		///Create and Id a GOC at runtime. Used to dynamically build GOC.
		///After components have been added call GOC->Initialize().
		Entity CreateEmptyComposition();

		///Build a composition and serialize from the data file but do not initialize the GOC.
		///Used to create a composition and then adjust its data before initialization
		///see GameObjectComposition::Initialize for details.
		Entity BuildAndSerialize(const std::string& filename);

		Entity Clone(Entity entity);

		///Add a GOC to the destroy list for delayed destruction.
		void Destroy(Entity entity);

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

		//others
		void Print(std::vector<Entity> allentity);

		//template<typename T>
		//void Position_update(T component);


	private:
		std::unique_ptr<ComponentManager> ComponentManagers;
		std::unique_ptr<EntityManager> EntityManagers;
		std::unique_ptr<SystemManager> SystemManagers;
	};

	//------------------------------------------------------------//

	inline Entity EntityManager::CreateEntity()
	{
		Entity CurrentId = TotalEntity;
		Signature signature{};
		EntityArray.insert(std::pair<Entity, Signature>(CurrentId, signature));

		++LivingEntity;
		++TotalEntity;
		return CurrentId;
	}

	inline void EntityManager::DestroyEntity(Entity entity)
	{
		EntityArray[entity].reset();
		EntityArray.erase(entity);
		--LivingEntity;
	}

	inline void EntityManager::SetSignature(Entity entity, Signature signature)
	{
		// Put this entity's signature into the array
		EntityArray[entity] = signature;
	}

	inline Signature EntityManager::GetSignature(Entity entity)
	{
		// Get this entity's signature from the array
		return EntityArray[entity];
	}

	inline bool EntityManager::HasSignature(Entity entity, Signature signature)
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
	inline void Component<T>::InsertData(Entity entity, T component)
	{
		ComponentArray.emplace(entity, component);
	}

	template<typename T>
	inline void Component<T>::RemoveData(Entity entity)
	{
		ComponentArray.erase(entity);
	}

	template<typename T>
	inline T& Component<T>::GetData(Entity entity)
	{
		// Return a reference to the entity's component
		return ComponentArray[entity];
	}

	template<typename T>
	inline void Component<T>::ChangeData(Entity entity, T newcomponent)
	{
		//change the value of the component in the entity
		ComponentArray[entity] = newcomponent;
	}

	template<typename T>
	inline void Component<T>::EntityDestroyed(Entity entity)
	{
		if (ComponentArray.find(entity) != ComponentArray.end())
		{
			// Remove the entity's component if it existed
			RemoveData(entity);
		}
	}

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

	template<typename T>
	inline ComponentType ComponentManager::GetComponentType()
	{
		const char* typeName = typeid(T).name();

		// Return this component's type - used for creating signatures
		return ComponentTypes[typeName];
	}

	template<typename T>
	inline void ComponentManager::AddComponent(Entity entity, T component)
	{
		const char* typeName = typeid(T).name();

		// Add a component to the array for an entity
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	inline void ComponentManager::RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	inline T& ComponentManager::GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}

	template<typename T>
	inline void ComponentManager::ChangeComponent(Entity entity, T newcomponent)
	{
		// Add a component to the array for an entity
		GetComponentArray<T>()->ChangeData(entity, newcomponent);
	}

	inline void ComponentManager::EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : ComponentArrays)
		{
			auto const& component = pair.second;

			if(component != NULL)
				component->EntityDestroyed(entity);
		}
	}

	//-------------------------------------------------------------------------//

	template<typename T>
	inline std::shared_ptr<T> SystemManager::RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		// Create a pointer to the system and return it so it can be used externally
		std::shared_ptr<T> system = std::make_shared<T>();
		Systems[typeName] = system;
		return system;
	}

	template<typename T>
	inline void SystemManager::SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		// Set the signature for this system
		Signatures[typeName] = signature;
	}

	inline void SystemManager::EntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all system lists
		// mEntities is a set so no check needed
		for (auto const& pair : Systems)
		{
			auto const& system = pair.second;

			system->Entities.erase(entity);
		}
	}

	inline void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
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

	inline void GameObjectFactory::Init()
	{
		// Create pointers to each manager
		ComponentManagers = std::make_unique<ComponentManager>();
		EntityManagers = std::make_unique<EntityManager>();
		SystemManagers = std::make_unique<SystemManager>();
	}

	inline Entity GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}

	inline Entity GameObjectFactory::BuildAndSerialize(const std::string& filename)
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
				stream >> newcirclecollider.mass;

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
			else if (text == "LineSegment")
			{
				LineSegment newlinesegment;
				stream >> newlinesegment.point0.x;
				stream >> newlinesegment.point0.y;
				stream >> newlinesegment.point1.x;
				stream >> newlinesegment.point1.y;
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

	inline Entity GameObjectFactory::Clone(Entity entity)
	{
		Entity newentity{};

		if (entity != NULL)
			newentity = GameObjectFactory::CreateEmptyComposition();
		else
			return NULL;

		if (GameObjectFactory::HasComponent<Position>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Position>(entity);
			GameObjectFactory::AddComponent<Position>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Colour>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Colour>(entity);
			GameObjectFactory::AddComponent<Colour>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Triangle>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Triangle>(entity);
			GameObjectFactory::AddComponent<Triangle>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Rigidbody2DComponent>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Rigidbody2DComponent>(entity);
			GameObjectFactory::AddComponent<Rigidbody2DComponent>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Bounds>(entity))
		{
			const auto& data = GameObjectFactory::GetComponent<Bounds>(entity);
			GameObjectFactory::AddComponent<Bounds>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<BoxCollider2D>(entity))
		{
			auto data = GameObjectFactory::GetComponent<BoxCollider2D>(entity);
			GameObjectFactory::AddComponent<BoxCollider2D>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<CircleCollider2D>(entity))
		{
			auto data = GameObjectFactory::GetComponent<CircleCollider2D>(entity);
			GameObjectFactory::AddComponent<CircleCollider2D>(newentity, data);
		}

		return newentity;
	}

	inline void GameObjectFactory::Destroy(Entity gameObject)
	{
		EntityManagers->DestroyEntity(gameObject);

		ComponentManagers->EntityDestroyed(gameObject);

		SystemManagers->EntityDestroyed(gameObject);
	}

	//Clean up the game world
	inline void GameObjectFactory::DestroyAllObjects(std::vector<Entity> allentity)
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
	inline void GameObjectFactory::RegisterComponent()
	{
		ComponentManagers->RegisterComponent<T>();
	}

	template<typename T>
	inline void GameObjectFactory::AddComponent(Entity entity, T component)
	{
		ComponentManagers->AddComponent<T>(entity, component);

		auto signature = EntityManagers->GetSignature(entity);

		signature.set(ComponentManagers->GetComponentType<T>(), true);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	inline void GameObjectFactory::RemoveComponent(Entity entity)
	{
		ComponentManagers->RemoveComponent<T>(entity);

		auto signature = EntityManagers->GetSignature(entity);
		signature.set(ComponentManagers->GetComponentType<T>(), false);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	inline T& GameObjectFactory::GetComponent(Entity entity)
	{
		return ComponentManagers->GetComponent<T>(entity);
	}

	template<typename T>
	inline void GameObjectFactory::ChangeComponent(Entity entity, T newcomponent)
	{
		ComponentManagers->ChangeComponent<T>(entity, newcomponent);
	}

	template<typename T>
	inline bool GameObjectFactory::HasComponent(Entity entity) const
	{
		auto getsignature = ComponentManagers->GetComponentType<T>();
		auto bit = pow(2, getsignature);

		return EntityManagers->HasSignature(entity, Signature(bit));
	}

	template<typename T>
	inline ComponentType GameObjectFactory::GetComponentType()
	{
		return ComponentManagers->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	inline std::shared_ptr<T> GameObjectFactory::RegisterSystem()
	{
		return SystemManagers->RegisterSystem<T>();
	}

	template<typename T>
	inline void GameObjectFactory::SetSystemSignature(Signature signature)
	{
		SystemManagers->SetSignature<T>(signature);
	}


	inline void GameObjectFactory::Print(std::vector<Entity> allentity) {

		std::cout << "test print point (component 1)\n";
		for (auto const& entity : allentity)
		{
			if (HasComponent<Position>(entity))
			{
				auto print = GetComponent<Position>(entity);
				std::cout << "entity " << entity << ": "
					<< print.x << ", " << print.y << std::endl;
			}
		}

		std::cout << "test print colour (component 2)\n";
		for (auto const& entity : allentity)
		{
			if (HasComponent<Colour>(entity))
			{
				auto print = GetComponent<Colour>(entity);
				std::cout << "entity " << entity << ": "
					<< print.r << ", " << print.g << ", " << print.b << ", " << print.a << std::endl;
			}
		}

		std::cout << "test print triangle (component 3)\n";
		for (auto const& entity : allentity)
		{
			if (HasComponent<Triangle>(entity))
			{
				auto print2 = GetComponent<Triangle>(entity);
				std::cout << "entity " << entity << ": "
					<< print2.positionx << ", " << print2.positiony << ", " << print2.positionz << std::endl;
			}
		}
	}
}
