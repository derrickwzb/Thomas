/*!*************************************************************************
\file           Entity.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Course:    CSD2125
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

#include "Components.h"
#include "Thomas/Collision/Collision.hpp"
#include "Thomas/Renderer/Graphics.h"

namespace Thomas {

	using Entity = unsigned int;
	using ComponentType = std::uint8_t;

	// Define the size using the max component number
	const ComponentType MAX_COMPONENTS = CT_MaxComponents;
	using Signature = std::bitset<MAX_COMPONENTS>;

	//declaration for functions in EntityManager class
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
		//The map for Entity and Signature
		inline static std::map<Entity, Signature> EntityArray;
		inline static unsigned int CurrentId;
		inline static unsigned int LivingEntity{};
		inline static unsigned int TotalEntity{};
	};

	//----------------------------------------------//

	//declaration for functions in Component class
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
		// The map for entity and components.
		inline static std::map<Entity, T> ComponentArray;
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

	//declaration for functions in GameObjectFactory class
	class GameObjectFactory
	{
	public:

		void Init();

		//Functions relate to Entity
		//Create empty entity with no components
		Entity CreateEmptyComposition();

		///Build a composition and serialize from the data file
		///Used to create a composition and then adjust its data before initialization
		Entity BuildAndSerialize(const std::string& filename);

		//Copy and create a new entity
		Entity Clone(Entity entity);

		//remove entity
		void Destroy(Entity entity);

		//remove all entity
		void DestroyAllObjects(std::vector<Entity> allentity);

		//Functions relate to Component
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

		//other functions
		void Print(std::vector<Entity> allentity);

	private:
		std::unique_ptr<ComponentManager> ComponentManagers;
		std::unique_ptr<EntityManager> EntityManagers;
	};

	inline static GameObjectFactory factory;

	//------------------------------------------------------------//

	//definition for functions in EntityManager class

	//Create entity with empty signature using the TotalEntity count
	inline Entity EntityManager::CreateEntity()
	{
		Entity CurrentId = TotalEntity;
		Signature signature{};
		EntityArray.insert(std::pair<Entity, Signature>(CurrentId, signature));

		++LivingEntity;
		++TotalEntity;
		return CurrentId;
	}

	//Delete Entity from entity map
	inline void EntityManager::DestroyEntity(Entity entity)
	{
		EntityArray[entity].reset();
		EntityArray.erase(entity);
		--LivingEntity;
	}

	//Set signature for the entity into the entity map
	inline void EntityManager::SetSignature(Entity entity, Signature signature)
	{
		EntityArray[entity] = signature;
	}

	//Get the entity's signature from the entity map
	inline Signature EntityManager::GetSignature(Entity entity)
	{
		return EntityArray[entity];
	}

	//Check if the entity has the component using signature
	inline bool EntityManager::HasSignature(Entity entity, Signature signature)
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
	inline void Component<T>::InsertData(Entity entity, T component)
	{
		ComponentArray.emplace(entity, component);
	}

	//remove entity and component from ComponentArray map
	template<typename T>
	inline void Component<T>::RemoveData(Entity entity)
	{
		ComponentArray.erase(entity);
	}

	//Get component data from ComponentArray map using entity number
	template<typename T>
	inline T& Component<T>::GetData(Entity entity)
	{
		return ComponentArray[entity];
	}

	//change the value of the component in the entity
	template<typename T>
	inline void Component<T>::ChangeData(Entity entity, T newcomponent)
	{
		ComponentArray[entity] = newcomponent;
	}

	// Remove the entity's component if it existed
	template<typename T>
	inline void Component<T>::EntityDestroyed(Entity entity)
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
	inline void ComponentManager::AddComponent(Entity entity, T component)
	{
		const char* typeName = typeid(T).name();

		GetComponentArray<T>()->InsertData(entity, component);
	}

	//Remove a component from the map using entity number
	template<typename T>
	inline void ComponentManager::RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	//Get data from the map using entity number
	template<typename T>
	inline T& ComponentManager::GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	//Change the component data using entity number
	template<typename T>
	inline void ComponentManager::ChangeComponent(Entity entity, T newcomponent)
	{
		GetComponentArray<T>()->ChangeData(entity, newcomponent);
	}


	inline void ComponentManager::EntityDestroyed(Entity entity)
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
	inline void GameObjectFactory::Init()
	{
		ComponentManagers = std::make_unique<ComponentManager>();
		EntityManagers = std::make_unique<EntityManager>();
	}

	//Function relate to entity
	inline Entity GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}

	//Create new entity using data reading from files
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
		int i = 0;
		float f = 0;

		//create new entity
		Entity gameObject = GameObjectFactory::CreateEmptyComposition();

		while (!stream.eof())
		{
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
			else if (text == "Triangle")
			{
				Triangle newtriangle;
				stream >> newtriangle.positionx;
				stream >> newtriangle.positiony;
				stream >> newtriangle.positionz;

				GameObjectFactory::AddComponent<Triangle>(gameObject, newtriangle);
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

	//copy and create a new entity with same component type and data
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

	//Destory entity and components
	inline void GameObjectFactory::Destroy(Entity gameObject)
	{
		EntityManagers->DestroyEntity(gameObject);
		ComponentManagers->EntityDestroyed(gameObject);
	}

	//Clean up the game world
	inline void GameObjectFactory::DestroyAllObjects(std::vector<Entity> allentity)
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
	}

	//add new component to entity 
	template<typename T>
	inline void GameObjectFactory::AddComponent(Entity entity, T component)
	{
		//add to ComponentArray map
		ComponentManagers->AddComponent<T>(entity, component);

		//get the current signature
		auto signature = EntityManagers->GetSignature(entity);

		//set the signature to true
		signature.set(ComponentManagers->GetComponentType<T>(), true);
		EntityManagers->SetSignature(entity, signature);
	}

	//remove component from entity
	template<typename T>
	inline void GameObjectFactory::RemoveComponent(Entity entity)
	{
		ComponentManagers->RemoveComponent<T>(entity);

		//get and update signature
		auto signature = EntityManagers->GetSignature(entity);
		signature.set(ComponentManagers->GetComponentType<T>(), false);
		EntityManagers->SetSignature(entity, signature);
	}

	//calling ComponentManagers to get component data
	template<typename T>
	inline T& GameObjectFactory::GetComponent(Entity entity)
	{
		return ComponentManagers->GetComponent<T>(entity);
	}

	//calling ComponentManagers to change component data
	template<typename T>
	inline void GameObjectFactory::ChangeComponent(Entity entity, T newcomponent)
	{
		ComponentManagers->ChangeComponent<T>(entity, newcomponent);
	}

	//check if the entity has the component
	template<typename T>
	inline bool GameObjectFactory::HasComponent(Entity entity) const
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

	//test function to print the components data to the output stream
	inline void GameObjectFactory::Print(std::vector<Entity> allentity) {

		std::cout << std::endl;
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

		std::cout << std::endl;
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

		std::cout << std::endl;
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
