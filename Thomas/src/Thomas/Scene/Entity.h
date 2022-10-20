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
#include "Thomas/Collision/Collision.h"
#include "Thomas/Renderer/Graphics.h"
#include "Thomas/Physics/RigidBody.hpp"
#include "Thomas/Serialisation/Serializer.h"

/* notes
	get access to the entity / component map directly
*/

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
		virtual Entity GetId() { return CurrentId; }

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
		std::vector<Entity> BuildAndSerialize(const std::string& filename);

		//Save data to file using RapidJson
		void SaveToFile(std::vector<Entity> allentity, const std::string& filename);

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
	inline std::vector<Entity> GameObjectFactory::BuildAndSerialize(const std::string& filename)
	{
		std::vector<Entity> entities;

		//Open the text file stream serializer
		std::ifstream ifs(filename);
		if (!ifs) {
			GameObjectFactory::SaveToFile(entities, filename);
			return GameObjectFactory::BuildAndSerialize(filename);
		}
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		ifs.close();
		
		//rapidjson parse
		rapidjson::Document doc;
		doc.Parse(buffer.str().c_str());

		//if has error
		if (doc.HasParseError()) {
			std::cout << "GetParseError" << doc.GetParseError() << std::endl;
		}

		const rapidjson::Value& object = doc["entity"];
		assert(object.IsArray());

		for (int i = 0; i < object.Capacity(); ++i) {
			const rapidjson::Value& component = object[i];

			//create new entity
			Entity gameObject = GameObjectFactory::CreateEmptyComposition();
		
		//graphic component
		if (component.HasMember("Transform")) {
			Transform new_trans;

			const rapidjson::Value& trans = component["Translation"];
			new_trans.translation.x = trans[0].GetFloat();
			new_trans.translation.y = trans[1].GetFloat();

			new_trans.rotation = (component["Rotation"].GetFloat());

			const rapidjson::Value& scale = component["Scaling"];
			new_trans.scaling.x = scale[0].GetFloat();
			new_trans.scaling.y = scale[1].GetFloat();

			new_trans.compute_mdl_to_ndc_xform();

			factory.AddComponent<Transform>(gameObject, new_trans);
		}

		if (component.HasMember("Shader_manager")) {
			Shader_manager shader;
			shader.setup_shdr_pgm();
			factory.AddComponent<Shader_manager>(gameObject, shader);
		}

		if (component.HasMember("Mesh")) {
			Mesh mesh;
			mesh.setup_vao();
			factory.AddComponent<Mesh>(gameObject, mesh);
		}

		if (component.HasMember("Texture")) {
			Texture text;
			factory.AddComponent<Texture>(gameObject, text);
		}

		if (component.HasMember("Camera")) {
			Camera cam;
			factory.AddComponent<Camera>(gameObject, cam);
		}

		if (component.HasMember("Box_collider")) {
			Box_collider bb_box;

			const rapidjson::Value& b_trans = component["Box_trans"];
			bb_box.box_trans.translation.x = b_trans[0].GetFloat();
			bb_box.box_trans.translation.y = b_trans[1].GetFloat();

			bb_box.box_trans.rotation = (component["Box_rotate"].GetFloat());

			const rapidjson::Value& b_scale = component["Box_scale"];
			bb_box.box_trans.scaling.x = b_scale[0].GetFloat();
			bb_box.box_trans.scaling.y = b_scale[1].GetFloat();

			bb_box.box_trans.compute_mdl_to_ndc_xform();
			bb_box.box_shader.setup_shdr_pgm();
			bb_box.box_mesh.setup_vao();

			factory.AddComponent<Box_collider>(gameObject, bb_box);
		}

		//physics component
		if (component.HasMember("RigidBody")) {
			RigidBody new_rigid;

			const rapidjson::Value& pos = component["Position"];
			new_rigid.m_Position.x = pos[0].GetFloat();
			new_rigid.m_Position.y = pos[1].GetFloat();

			const rapidjson::Value& vel = component["Velocity"];
			new_rigid.Velocity.x = vel[0].GetFloat();
			new_rigid.Velocity.y = vel[1].GetFloat();

			factory.AddComponent<RigidBody>(gameObject, new_rigid);
		}

		if (component.HasMember("BoxCollider2D")) {
			BoxCollider2D new_boxcollider2d;

			const rapidjson::Value& bmin = component["Bound_min"];
			new_boxcollider2d.bounds.min.x = bmin[0].GetFloat();
			new_boxcollider2d.bounds.min.y = bmin[1].GetFloat();

			const rapidjson::Value& bmax = component["Bound_max"];
			new_boxcollider2d.bounds.max.x = bmax[0].GetFloat();
			new_boxcollider2d.bounds.max.y = bmax[1].GetFloat();

			factory.AddComponent<BoxCollider2D>(gameObject, new_boxcollider2d);
		}
			entities.push_back(gameObject);
		}
		

		////Open the text file stream serializer
		//std::ifstream stream;
		//stream.open(filename.c_str(), std::ios_base::in);
		//if (!stream)
		//{
		//	std::cout << "File " << filename
		//		<< " not found." << "\n";
		//}
		//std::string line;
		//std::string text;
		//int i = 0;
		//float f = 0;

		//

		//while (!stream.eof())
		//{
		//	stream >> text;

		//	if (text == "Position")
		//	{
		//		Position newpos;
		//		stream >> f;
		//		newpos.x = f;
		//		stream >> f;
		//		newpos.y = f;

		//		GameObjectFactory::AddComponent<Position>(gameObject, newpos);
		//	}
		//	else if (text == "Colour")
		//	{
		//		Colour newcolour;
		//		stream >> newcolour.r;
		//		stream >> newcolour.g;
		//		stream >> newcolour.b;
		//		stream >> newcolour.a;

		//		GameObjectFactory::AddComponent<Colour>(gameObject, newcolour);
		//	}
		//	else if (text == "Triangle")
		//	{
		//		Triangle newtriangle;
		//		stream >> newtriangle.positionx;
		//		stream >> newtriangle.positiony;
		//		stream >> newtriangle.positionz;

		//		GameObjectFactory::AddComponent<Triangle>(gameObject, newtriangle);
		//	}
		//	else if (text == "Rigidbody2DComponent")
		//	{
		//		Rigidbody2DComponent new_rigidbody;
		//		stream >> new_rigidbody.posCurr.x;
		//		stream >> new_rigidbody.posCurr.y;
		//		stream >> new_rigidbody.velCurr.x;
		//		stream >> new_rigidbody.velCurr.y;
		//		stream >> new_rigidbody.dirCurr;

		//		GameObjectFactory::AddComponent<Rigidbody2DComponent>(gameObject, new_rigidbody);
		//	}
		//	else if (text == "Bounds")
		//	{
		//		Bounds newbounds;
		//		stream >> newbounds.centre.x;
		//		stream >> newbounds.centre.y;
		//		stream >> newbounds.extents.x;
		//		stream >> newbounds.extents.y;
		//		stream >> newbounds.max.x;
		//		stream >> newbounds.max.y;
		//		stream >> newbounds.min.x;
		//		stream >> newbounds.min.y;
		//		stream >> newbounds.size.x;
		//		stream >> newbounds.size.y;

		//		GameObjectFactory::AddComponent<Bounds>(gameObject, newbounds);
		//	}
		//	else if (text == "BoxCollider2D")
		//	{
		//		BoxCollider2D new_boxcollider2d;
		//		stream >> new_boxcollider2d.bounciness;
		//		stream >> new_boxcollider2d.offset.x;
		//		stream >> new_boxcollider2d.offset.y;
		//		stream >> new_boxcollider2d.isTrigger;
		//		stream >> new_boxcollider2d.friction;
		//		stream >> new_boxcollider2d.size.x;
		//		stream >> new_boxcollider2d.size.y;

		//		GameObjectFactory::AddComponent<BoxCollider2D>(gameObject, new_boxcollider2d);
		//	}
		//	else if (text == "BoxCollider2D")
		//	{
		//		BoxCollider2D new_boxcollider2d;
		//		stream >> new_boxcollider2d.bounciness;
		//		stream >> new_boxcollider2d.offset.x;
		//		stream >> new_boxcollider2d.offset.y;
		//		stream >> new_boxcollider2d.isTrigger;
		//		stream >> new_boxcollider2d.friction;
		//		stream >> new_boxcollider2d.size.x;
		//		stream >> new_boxcollider2d.size.y;

		//		GameObjectFactory::AddComponent<BoxCollider2D>(gameObject, new_boxcollider2d);
		//	}
		//	else if (text == "CircleCollider2D")
		//	{
		//		CircleCollider2D newcirclecollider;
		//		stream >> newcirclecollider.bounciness;
		//		stream >> newcirclecollider.offset.x;
		//		stream >> newcirclecollider.offset.y;
		//		stream >> newcirclecollider.isTrigger;
		//		stream >> newcirclecollider.friction;
		//		stream >> newcirclecollider.radius;
		//		stream >> newcirclecollider.mass;

		//		GameObjectFactory::AddComponent<CircleCollider2D>(gameObject, newcirclecollider);
		//	}
		//	else if (text == "LineSegment")
		//	{
		//		LineSegment newlinesegment;
		//		stream >> newlinesegment.point0.x;
		//		stream >> newlinesegment.point0.y;
		//		stream >> newlinesegment.point1.x;
		//		stream >> newlinesegment.point1.y;
		//		stream >> newlinesegment.normal.x;
		//		stream >> newlinesegment.normal.y;

		//		GameObjectFactory::AddComponent<LineSegment>(gameObject, newlinesegment);
		//	}
		//	else if (text == "Ray")
		//	{
		//		Ray newray;
		//		stream >> newray.direction.x;
		//		stream >> newray.direction.x;
		//		stream >> newray.origin.x;
		//		stream >> newray.origin.x;

		//		GameObjectFactory::AddComponent<Ray>(gameObject, newray);
		//	}
		//}

		return entities;
	}

	inline void GameObjectFactory::SaveToFile(std::vector<Entity> allentity, const std::string& filename) 
	{
		std::ofstream ofs(filename);

		//set document and allocator
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

		//create array to contain entity data, this array will
		//contain another component array data
		rapidjson::Value objects(rapidjson::kArrayType);

		//id
		int i = 0;

		//loop through entities
		for (auto const& entity : allentity) {
			//create a object type (rapidjson type) so that all the component array 
			//data for one entity can be add inside to this object type
			rapidjson::Value components(rapidjson::kObjectType);
			//add id
			components.AddMember("id", i, allocator);

			//graphic component
			if (factory.HasComponent<Transform>(entity)) {
				//add component name
				components.AddMember("Transform", true, allocator);

				//get component data from current entity
				auto write_trans = factory.GetComponent<Transform>(entity);

				//create a array to contain translation data and add to the object
				rapidjson::Value trans(rapidjson::kArrayType);
				trans.PushBack(write_trans.translation.x, allocator);
				trans.PushBack(write_trans.translation.y, allocator);
				components.AddMember("Translation", trans, allocator);

				//add data directly without array
				components.AddMember("Rotation", write_trans.rotation, allocator);

				rapidjson::Value scale(rapidjson::kArrayType);
				scale.PushBack(write_trans.scaling.x, allocator);
				scale.PushBack(write_trans.scaling.y, allocator);
				components.AddMember("Scaling", scale, allocator);
			}

			if (factory.HasComponent<Shader_manager>(entity)) {
				components.AddMember("Shader_manager", true, allocator);
			}

			if (factory.HasComponent<Mesh>(entity)) {
				components.AddMember("Mesh", true, allocator);
			}

			if (factory.HasComponent<Texture>(entity)) {
				components.AddMember("Texture", true, allocator);
			}

			if (factory.HasComponent<Camera>(entity)) {
				components.AddMember("Camera", true, allocator);
			}

			if (factory.HasComponent<Box_collider>(entity)) {
				components.AddMember("Box_collider", true, allocator);

				auto write_bb_box = factory.GetComponent<Box_collider>(entity);

				rapidjson::Value b_trans(rapidjson::kArrayType);
				b_trans.PushBack(write_bb_box.box_trans.translation.x, allocator);
				b_trans.PushBack(write_bb_box.box_trans.translation.y, allocator);
				components.AddMember("Box_trans", b_trans, allocator);

				components.AddMember("Box_rotate", write_bb_box.box_trans.rotation, allocator);

				rapidjson::Value b_scale(rapidjson::kArrayType);
				b_scale.PushBack(write_bb_box.box_trans.scaling.x, allocator);
				b_scale.PushBack(write_bb_box.box_trans.scaling.y, allocator);
				components.AddMember("Box_scale", b_scale, allocator);
			}

			if (factory.HasComponent<RigidBody>(entity)) {
				components.AddMember("RigidBody", true, allocator);

				auto write_rigid = factory.GetComponent<RigidBody>(entity);

				rapidjson::Value pos(rapidjson::kArrayType);
				pos.PushBack(write_rigid.m_Position.x, allocator);
				pos.PushBack(write_rigid.m_Position.y, allocator);
				components.AddMember("Position", pos, allocator);

				rapidjson::Value vel(rapidjson::kArrayType);
				vel.PushBack(write_rigid.Velocity.x, allocator);
				vel.PushBack(write_rigid.Velocity.y, allocator);
				components.AddMember("Velocity", vel, allocator);
			}

			if (factory.HasComponent<BoxCollider2D>(entity)) {
				components.AddMember("BoxCollider2D", true, allocator);

				auto write_boxcollider2d = factory.GetComponent<BoxCollider2D>(entity);

				rapidjson::Value bmin(rapidjson::kArrayType);
				bmin.PushBack(write_boxcollider2d.bounds.min.x, allocator);
				bmin.PushBack(write_boxcollider2d.bounds.min.y, allocator);
				components.AddMember("Bound_min", bmin, allocator);

				rapidjson::Value bmax(rapidjson::kArrayType);
				bmax.PushBack(write_boxcollider2d.bounds.max.x, allocator);
				bmax.PushBack(write_boxcollider2d.bounds.max.y, allocator);
				components.AddMember("Bound_max", bmax, allocator);
			}

			//add all the component data to entity array
			objects.PushBack(components, allocator);
			++i;
		}

		//add the entity array to document
		doc.AddMember("entity", objects, allocator);

		//Stringify the data
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		//write to file
		const char* out = buffer.GetString();
		ofs << out << std::endl;
		ofs.flush();
		ofs.close();
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

	static void ecs_init() {

		Signature signature;

		factory.Init();

		//components for graphic
		factory.RegisterComponent<Transform>();
		factory.RegisterComponent<Shader_manager>();
		factory.RegisterComponent<Mesh>();
		factory.RegisterComponent<Texture>();
		factory.RegisterComponent<Camera>();
		factory.RegisterComponent<Box_collider>();

		signature.set(factory.GetComponentType<Transform>());
		signature.set(factory.GetComponentType<Shader_manager>());
		signature.set(factory.GetComponentType<Mesh>());
		signature.set(factory.GetComponentType<Texture>());
		signature.set(factory.GetComponentType<Camera>());
		signature.set(factory.GetComponentType<Box_collider>());


		//component for physic
		factory.RegisterComponent<RigidBody>();
		factory.RegisterComponent<BoxCollider2D>();

		signature.set(factory.GetComponentType<RigidBody>());
		signature.set(factory.GetComponentType<BoxCollider2D>());
	}
}
