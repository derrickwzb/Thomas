/*!*************************************************************************
\file           EntityID.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
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
#include "Thomas/Physics/RigidBody.hpp"
#include "Thomas/Renderer/Asset_Manager.h"
#include "Thomas/Renderer/Texture.h"
#include "Thomas/Renderer/Box_collider.h"


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/prettywriter.h"

#include "Thomas/Audio/AudioComponent.h"
#include "Thomas/Logic/Logic.h"
#include "Thomas/Scene/Scene.h"

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
			//HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
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

		operator bool() const { return m_Scene ; }
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
		inline static std::map<EntityID, Signature> EntityArray;
		inline static uint32_t CurrentId;
		inline static uint32_t LivingEntity{};
		inline static uint32_t TotalEntity{};
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

		inline GameObjectFactory();

		//Functions relate to EntityID
		//Create empty entity with no components
		EntityID CreateEmptyComposition();

		///Build a composition and serialize from the data file
		///Used to create a composition and then adjust its data before initialization
		std::vector<EntityID> BuildAndSerialize(const std::string& filename);

		//Save data to file using RapidJson
		void SaveToFile(std::vector<EntityID> allentity, const std::string& filename);

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
		RegisterComponent<Camera>();
		RegisterComponent<Box_collider>();
		RegisterComponent<RigidBody>();
		RegisterComponent<BoxCollider2D>();
		RegisterComponent<AudioComponent>();
		RegisterComponent<Logic01>();
		RegisterComponent<Logic02>();
	}

	//Function relate to entity
	inline EntityID GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}
	
	//static std::vector<EntityID> entities;

	std::map<EntityID, Signature>& GameObjectFactory::GetEntities()
	{
		return EntityManagers->Get();
	}


	//Create new entities by reading data from files using rapidjson
	//inline std::vector<EntityID> GameObjectFactory::BuildAndSerialize(const std::string& filename)
	//{
	//	//std::vector<EntityID> entities;

	//	//Open the text file stream serializer
	//	std::ifstream ifs(filename);
	//	if (!ifs) {
	//		//GameObjectFactory::SaveToFile(entities, filename);
	//		return GameObjectFactory::BuildAndSerialize(filename);
	//	}
	//	std::stringstream buffer;
	//	buffer << ifs.rdbuf();
	//	ifs.close();
	//	
	//	//rapidjson parse
	//	rapidjson::Document doc;
	//	doc.Parse(buffer.str().c_str());

	//	//if has error
	//	if (doc.HasParseError()) {
	//		std::cout << "GetParseError" << doc.GetParseError() << std::endl;
	//	}

	//	const rapidjson::Value& object = doc["entity"];
	//	assert(object.IsArray());

	//	for (rapidjson::SizeType i = 0; i < object.Capacity(); ++i) {
	//		const rapidjson::Value& component = object[i];

	//		//create new entity
	//		EntityID gameObject = GameObjectFactory::CreateEmptyComposition();
	//	
	//	//graphic component
	//	if (component.HasMember("Transform")) {
	//		Transform new_trans;

	//		const rapidjson::Value& trans = component["Translation"];
	//		new_trans.translation.x = trans[0].GetFloat();
	//		new_trans.translation.y = trans[1].GetFloat();

	//		new_trans.rotation = (component["Rotation"].GetFloat());

	//		const rapidjson::Value& scale = component["Scaling"];
	//		new_trans.scaling.x = scale[0].GetFloat();
	//		new_trans.scaling.y = scale[1].GetFloat();

	//		new_trans.compute_mdl_to_ndc_xform();

	//		factory.AddComponent<Transform>(gameObject, new_trans);
	//	}

	//	if (component.HasMember("Shader_manager")) {
	//		Shader_manager shader;
	//		auto vert = stash.Shader_Storage.find("engine.vert");
	//		
	//		auto frag = stash.Shader_Storage.find("engine.frag");
	//		shader.setup_shdr_pgm(vert->second, frag->second);

	//		factory.AddComponent<Shader_manager>(gameObject, shader);
	//	}

	//	if (component.HasMember("Mesh")) {
	//		Mesh mesh;
	//		mesh.setup_vao();
	//		factory.AddComponent<Mesh>(gameObject, mesh);
	//	}

	//	if (component.HasMember("Texture")) {
	//		Texture text;
	//		text.text_file = (int)(component["Text_file"].GetFloat());
	//		factory.AddComponent<Texture>(gameObject, text);
	//	}

	//	//if (component.HasMember("Camera")) {
	//	//	Camera cam;
	//	//	cam.Camera2D_Init();
	//	//	factory.AddComponent<Camera>(gameObject, cam);
	//	//}

	//	if (component.HasMember("Box_collider")) {
	//		Box_collider bb_box;
	//		const rapidjson::Value& b_trans = component["Box_trans"];
	//		bb_box.box_trans.translation.x = b_trans[0].GetFloat();
	//		bb_box.box_trans.translation.y = b_trans[1].GetFloat();

	//		bb_box.box_trans.rotation = (component["Box_rotate"].GetFloat());

	//		const rapidjson::Value& b_scale = component["Box_scale"];
	//		bb_box.box_trans.scaling.x = b_scale[0].GetFloat();
	//		bb_box.box_trans.scaling.y = b_scale[1].GetFloat();

	//		bb_box.box_trans.compute_mdl_to_ndc_xform();
	//		auto vert = stash.Shader_Storage.find("collider.vert");
	//		auto frag = stash.Shader_Storage.find("collider.frag");
	//		bb_box.box_shader.setup_shdr_pgm(vert->second, frag->second);
	//		bb_box.box_mesh.setup_vao();

	//		factory.AddComponent<Box_collider>(gameObject, bb_box);
	//	}

	//	//physics component
	//	if (component.HasMember("RigidBody")) {
	//		RigidBody new_rigid;

	//		const rapidjson::Value& pos = component["Position"];
	//		new_rigid.m_Position.x = pos[0].GetFloat();
	//		new_rigid.m_Position.y = pos[1].GetFloat();

	//		//const rapidjson::Value& vel = component["Velocity"];
	//		new_rigid.Velocity = (component["Velocity"].GetFloat());

	//		factory.AddComponent<RigidBody>(gameObject, new_rigid);
	//	}

	//	if (component.HasMember("BoxCollider2D")) {
	//		BoxCollider2D new_boxcollider2d;
	//		
	//		const rapidjson::Value& bmin = component["Bound_min"];
	//		new_boxcollider2d.bounds.min.x = bmin[0].GetFloat();
	//		new_boxcollider2d.bounds.min.y = bmin[1].GetFloat();

	//		const rapidjson::Value& bmax = component["Bound_max"];
	//		new_boxcollider2d.bounds.max.x = bmax[0].GetFloat();
	//		new_boxcollider2d.bounds.max.y = bmax[1].GetFloat();

	//		std::array<float, 2> temp_vertices;
	//		std::array<std::array<float, 2>, 4> temp_result;
	//		const rapidjson::Value& bvertice = component["Vertices"];

	//		for (rapidjson::SizeType i = 0; i < bvertice.Size(); ++i) {
	//			const rapidjson::Value& bvertice_pos = bvertice[i];
	//			temp_vertices[0] = bvertice_pos[0].GetFloat();
	//			temp_vertices[1] = bvertice_pos[1].GetFloat();
	//			temp_result[i] = temp_vertices;
	//		}

	//		new_boxcollider2d.vertices = temp_result;
	//		new_boxcollider2d.ArrayToVector();

	//		factory.AddComponent<BoxCollider2D>(gameObject, new_boxcollider2d);
	//	}

	//	//Audio
	//	if (component.HasMember("AudioComponent")) {
	//		AudioComponent Audio_Component;
	//		factory.AddComponent<AudioComponent>(gameObject, Audio_Component);
	//	}

	//	if (component.HasMember("Logic01")) {
	//		Logic01 new_logic01;
	//		factory.AddComponent<Logic01>(gameObject, new_logic01);
	//	}

	//	if (component.HasMember("Logic02")) {
	//		Logic02 new_logic02;
	//		factory.AddComponent<Logic02>(gameObject, new_logic02);
	//	}


	//		//entities.push_back(gameObject);
	//	}

	//	//return entities;
	//	return;
	//}

	//save the data to file using rapidjson
	//inline void GameObjectFactory::SaveToFile(std::vector<EntityID> allentity, const std::string& filename) 
	//{
	//	std::ofstream ofs(filename);

	//	//set document and allocator
	//	rapidjson::Document doc;
	//	doc.SetObject();
	//	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	//	//create array to contain entity data, this array will
	//	//contain another component array data
	//	rapidjson::Value objects(rapidjson::kArrayType);

	//	//id
	//	int i = 0;

	//	//loop through entities
	//	for (auto const& entity : allentity) {
	//		//create a object type (rapidjson type) so that all the component array 
	//		//data for one entity can be add inside to this object type
	//		rapidjson::Value components(rapidjson::kObjectType);
	//		//add id
	//		components.AddMember("id", i, allocator);

	//		//graphic component
	//		if (factory.HasComponent<Transform>(entity)) {
	//			//add component name
	//			components.AddMember("Transform", true, allocator);

	//			//get component data from current entity
	//			auto write_trans = factory.GetComponent<Transform>(entity);

	//			//create a array to contain translation data and add to the object
	//			rapidjson::Value trans(rapidjson::kArrayType);
	//			trans.PushBack(write_trans.translation.x, allocator);
	//			trans.PushBack(write_trans.translation.y, allocator);
	//			components.AddMember("Translation", trans, allocator);

	//			//add data directly without array
	//			components.AddMember("Rotation", write_trans.rotation, allocator);

	//			rapidjson::Value scale(rapidjson::kArrayType);
	//			scale.PushBack(write_trans.scaling.x, allocator);
	//			scale.PushBack(write_trans.scaling.y, allocator);
	//			components.AddMember("Scaling", scale, allocator);
	//		}

	//		if (factory.HasComponent<Shader_manager>(entity)) {
	//			components.AddMember("Shader_manager", true, allocator);
	//		}

	//		if (factory.HasComponent<Mesh>(entity)) {
	//			components.AddMember("Mesh", true, allocator);
	//		}

	//		if (factory.HasComponent<Texture>(entity)) {
	//			auto write_tex = factory.GetComponent<Texture>(entity);
	//			components.AddMember("Texture", true, allocator);
	//			components.AddMember("Text_file", write_tex.text_file, allocator);
	//		}

	//		if (factory.HasComponent<Camera>(entity)) {
	//			components.AddMember("Camera", true, allocator);
	//		}

	//		if (factory.HasComponent<Box_collider>(entity)) {
	//			components.AddMember("Box_collider", true, allocator);

	//			auto write_bb_box = factory.GetComponent<Box_collider>(entity);

	//			rapidjson::Value b_trans(rapidjson::kArrayType);
	//			b_trans.PushBack(write_bb_box.box_trans.translation.x, allocator);
	//			b_trans.PushBack(write_bb_box.box_trans.translation.y, allocator);
	//			components.AddMember("Box_trans", b_trans, allocator);

	//			components.AddMember("Box_rotate", write_bb_box.box_trans.rotation, allocator);

	//			rapidjson::Value b_scale(rapidjson::kArrayType);
	//			b_scale.PushBack(write_bb_box.box_trans.scaling.x, allocator);
	//			b_scale.PushBack(write_bb_box.box_trans.scaling.y, allocator);
	//			components.AddMember("Box_scale", b_scale, allocator);
	//		}

	//		if (factory.HasComponent<RigidBody>(entity)) {
	//			components.AddMember("RigidBody", true, allocator);

	//			auto write_rigid = factory.GetComponent<RigidBody>(entity);

	//			rapidjson::Value pos(rapidjson::kArrayType);
	//			pos.PushBack(write_rigid.m_Position.x, allocator);
	//			pos.PushBack(write_rigid.m_Position.y, allocator);
	//			components.AddMember("Position", pos, allocator);

	//			components.AddMember("Velocity", write_rigid.Velocity, allocator);
	//		}

	//		if (factory.HasComponent<BoxCollider2D>(entity)) {
	//			components.AddMember("BoxCollider2D", true, allocator);

	//			auto write_boxcollider2d = factory.GetComponent<BoxCollider2D>(entity);

	//			rapidjson::Value bmin(rapidjson::kArrayType);
	//			bmin.PushBack(write_boxcollider2d.bounds.min.x, allocator);
	//			bmin.PushBack(write_boxcollider2d.bounds.min.y, allocator);
	//			components.AddMember("Bound_min", bmin, allocator);

	//			rapidjson::Value bmax(rapidjson::kArrayType);
	//			bmax.PushBack(write_boxcollider2d.bounds.max.x, allocator);
	//			bmax.PushBack(write_boxcollider2d.bounds.max.y, allocator);
	//			components.AddMember("Bound_max", bmax, allocator);

	//			rapidjson::Value bvertice(rapidjson::kArrayType);

	//			rapidjson::Value bvertice_pos0(rapidjson::kArrayType);
	//			bvertice_pos0.PushBack(write_boxcollider2d.vertices[0][0], allocator);
	//			bvertice_pos0.PushBack(write_boxcollider2d.vertices[0][1], allocator);
	//			bvertice.PushBack(bvertice_pos0, allocator);

	//			rapidjson::Value bvertice_pos1(rapidjson::kArrayType);
	//			bvertice_pos1.PushBack(write_boxcollider2d.vertices[1][0], allocator);
	//			bvertice_pos1.PushBack(write_boxcollider2d.vertices[1][1], allocator);
	//			bvertice.PushBack(bvertice_pos1, allocator);

	//			rapidjson::Value bvertice_pos2(rapidjson::kArrayType);
	//			bvertice_pos2.PushBack(write_boxcollider2d.vertices[2][0], allocator);
	//			bvertice_pos2.PushBack(write_boxcollider2d.vertices[2][1], allocator);
	//			bvertice.PushBack(bvertice_pos2, allocator);

	//			rapidjson::Value bvertice_pos3(rapidjson::kArrayType);
	//			bvertice_pos3.PushBack(write_boxcollider2d.vertices[3][0], allocator);
	//			bvertice_pos3.PushBack(write_boxcollider2d.vertices[3][1], allocator);
	//			bvertice.PushBack(bvertice_pos3, allocator);

	//			components.AddMember("Vertices", bvertice, allocator);
	//		}

	//		//Audio Component
	//		if (factory.HasComponent<AudioComponent>(entity)) {
	//			components.AddMember("AudioComponent", true, allocator);
	//		}

	//		if (factory.HasComponent<Logic01>(entity)) {
	//			components.AddMember("Logic01", true, allocator);
	//		}

	//		if (factory.HasComponent<Logic02>(entity)) {
	//			components.AddMember("Logic02", true, allocator);
	//		}

	//		//add all the component data to entity array
	//		objects.PushBack(components, allocator);
	//		++i;
	//	}

	//	//add the entity array to document
	//	doc.AddMember("entity", objects, allocator);

	//	//Stringify the data
	//	rapidjson::StringBuffer buffer;
	//	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	//	doc.Accept(writer);

	//	//write to file
	//	const char* out = buffer.GetString();
	//	ofs << out << std::endl;
	//	ofs.flush();
	//	ofs.close();
	//}

	//copy and create a new entity with same component type and data
	inline EntityID GameObjectFactory::Clone(EntityID entity)
	{
		EntityID newentity{};

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
		if (GameObjectFactory::HasComponent<Transform>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Transform>(entity);
			GameObjectFactory::AddComponent<Transform>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Shader_manager>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Shader_manager>(entity);
			GameObjectFactory::AddComponent<Shader_manager>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Mesh>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Mesh>(entity);
			GameObjectFactory::AddComponent<Mesh>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<Texture>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Texture>(entity);
			GameObjectFactory::AddComponent<Texture>(newentity, data);
		}
		/*if (GameObjectFactory::HasComponent<Camera>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Camera>(entity);
			GameObjectFactory::AddComponent<Camera>(newentity, data);
		}*/
		if (GameObjectFactory::HasComponent<Box_collider>(entity))
		{
			auto data = GameObjectFactory::GetComponent<Box_collider>(entity);
			GameObjectFactory::AddComponent<Box_collider>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<RigidBody>(entity))
		{
			auto data = GameObjectFactory::GetComponent<RigidBody>(entity);
			GameObjectFactory::AddComponent<RigidBody>(newentity, data);
		}
		if (GameObjectFactory::HasComponent<BoxCollider2D>(entity))
		{
			auto data = GameObjectFactory::GetComponent<BoxCollider2D>(entity);
			GameObjectFactory::AddComponent<BoxCollider2D>(newentity, data);
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
