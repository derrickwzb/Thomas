/*!*************************************************************************
\file           SceneSerializer.cpp
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains declaration for functions used in a sceneSerializer
****************************************************************************/
#include "thpch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"
#include "Thomas/Renderer/Graphics.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace Thomas
{
	SceneSerializer::SceneSerializer(Scene* context)
	{
		m_Scene = context;
	}


	void SceneSerializer::Serialize(const std::string& filepath)
	{
		std::ofstream ofs(filepath);

		//set document and allocator
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

		rapidjson::Value cam_trans(rapidjson::kArrayType);
		cam_trans.PushBack(Graphics::cam_stuff.translation.x, allocator);
		cam_trans.PushBack(Graphics::cam_stuff.translation.y, allocator);
		doc.AddMember("Camera_Translation", cam_trans, allocator);

		doc.AddMember("Camera_Rotation", Graphics::cam_stuff.rotation, allocator);

		rapidjson::Value cam_scale(rapidjson::kArrayType);
		cam_scale.PushBack(Graphics::cam_stuff.scaling.x, allocator);
		cam_scale.PushBack(Graphics::cam_stuff.scaling.y, allocator);
		doc.AddMember("Camera_Scale", cam_scale, allocator);
		
		doc.AddMember("Camera_c_Width", Graphics::cam_stuff.c_width, allocator);
		doc.AddMember("Camera_c_Height", Graphics::cam_stuff.c_height, allocator);
		doc.AddMember("Camera_Aspect_Ratio", Graphics::cam_stuff.c_ar, allocator);

		doc.AddMember("Camera_Height", Graphics::cam_stuff.height, allocator);
		//create array to contain entity data, this array will
		//contain another component array data
		rapidjson::Value objects(rapidjson::kArrayType);

		//id
		int i = 0;

		const auto entities = m_Scene->m_Registry->GetEntities();
		//loop through entities
		for (const auto& e : entities)
		{

			//create a object type (rapidjson type) so that all the component array 
			//data for one entity can be add inside to this object type
			rapidjson::Value components(rapidjson::kObjectType);

			Entity entity{ e.first , m_Scene };
			components.AddMember("id", e.first, allocator);
			std::string tag = entity.GetComponent<TagComponent>().tag;
			rapidjson::Value value;
			value.SetString(tag.c_str(), allocator);
			components.AddMember("name", value, allocator);


			if (entity.HasComponent<Transform>())
			{
				components.AddMember("Transform", true, allocator);
				auto transdata = entity.GetComponent<Transform>();
				rapidjson::Value trans(rapidjson::kArrayType);
				trans.PushBack(transdata.translation.x, allocator);
				trans.PushBack(transdata.translation.y, allocator);
				components.AddMember("Translation", trans, allocator);

				components.AddMember("Rotation", transdata.rotation, allocator);

				rapidjson::Value scale(rapidjson::kArrayType);
				scale.PushBack(transdata.scaling.x, allocator);
				scale.PushBack(transdata.scaling.y, allocator);
				components.AddMember("Scaling", scale, allocator);

				components.AddMember("Layer", transdata.z_axis, allocator);
				components.AddMember("Blend", transdata.alpha_val, allocator);

				rapidjson::Value color(rapidjson::kArrayType);
				color.PushBack(transdata.color.r, allocator);
				color.PushBack(transdata.color.g, allocator);
				color.PushBack(transdata.color.b, allocator);
				components.AddMember("Color", color, allocator);
			}
			if (entity.HasComponent<Shader_manager>())
			{
				components.AddMember("Shader_manager", true, allocator);
			}
			if (entity.HasComponent<Mesh>())
			{
				components.AddMember("Mesh", true, allocator);
			}

			if (entity.HasComponent<Texture>()) {
				auto write_tex = entity.GetComponent<Texture>();
				components.AddMember("Texture", true, allocator);
				components.AddMember("Text_texid", write_tex.texid, allocator);
				components.AddMember("Text_file", write_tex.text_file, allocator);

				rapidjson::Value filename;
				filename.SetString(write_tex.filename.c_str(), allocator);
				components.AddMember("Text_filename", filename, allocator);

				components.AddMember("Text_animation_but", write_tex.animation_but, allocator);
				components.AddMember("Text_counter", write_tex.counter, allocator);
				components.AddMember("Text_speed", write_tex.speed, allocator);
				components.AddMember("Text_slices", write_tex.slices, allocator);
				components.AddMember("Text_switch_text", write_tex.switch_text, allocator);
			}
			if (entity.HasComponent<Box_collider>()) {
				components.AddMember("Box_collider", true, allocator);

				auto write_bb_box = entity.GetComponent<Box_collider>();

				rapidjson::Value b_trans(rapidjson::kArrayType);
				b_trans.PushBack(write_bb_box.box_trans.translation.x, allocator);
				b_trans.PushBack(write_bb_box.box_trans.translation.y, allocator);
				components.AddMember("Box_trans", b_trans, allocator);

				components.AddMember("Box_rotate", write_bb_box.box_trans.rotation, allocator);

				rapidjson::Value b_scale(rapidjson::kArrayType);
				b_scale.PushBack(write_bb_box.box_trans.scaling.x, allocator);
				b_scale.PushBack(write_bb_box.box_trans.scaling.y, allocator);
				components.AddMember("Box_scale", b_scale, allocator);

				components.AddMember("Box_tog", 0, allocator);
			}

			if (entity.HasComponent<RigidBody>()) {
				components.AddMember("RigidBody", true, allocator);

				auto write_rigid = entity.GetComponent<RigidBody>();

				rapidjson::Value pos(rapidjson::kArrayType);
				pos.PushBack(write_rigid.m_Position.x, allocator);
				pos.PushBack(write_rigid.m_Position.y, allocator);
				components.AddMember("Position", pos, allocator);

				components.AddMember("Velocity", write_rigid.Velocity, allocator);
			}

			if (entity.HasComponent<BoxCollider2D>()) {
				components.AddMember("BoxCollider2D", true, allocator);

				auto write_boxcollider2d = entity.GetComponent<BoxCollider2D>();

				rapidjson::Value bmin(rapidjson::kArrayType);
				bmin.PushBack(write_boxcollider2d.bounds.min.x, allocator);
				bmin.PushBack(write_boxcollider2d.bounds.min.y, allocator);
				components.AddMember("Bound_min", bmin, allocator);

				rapidjson::Value bmax(rapidjson::kArrayType);
				bmax.PushBack(write_boxcollider2d.bounds.max.x, allocator);
				bmax.PushBack(write_boxcollider2d.bounds.max.y, allocator);
				components.AddMember("Bound_max", bmax, allocator);

				rapidjson::Value bvertice(rapidjson::kArrayType);

				rapidjson::Value bvertice_pos0(rapidjson::kArrayType);
				bvertice_pos0.PushBack(write_boxcollider2d.vertices[0][0], allocator);
				bvertice_pos0.PushBack(write_boxcollider2d.vertices[0][1], allocator);
				bvertice.PushBack(bvertice_pos0, allocator);

				rapidjson::Value bvertice_pos1(rapidjson::kArrayType);
				bvertice_pos1.PushBack(write_boxcollider2d.vertices[1][0], allocator);
				bvertice_pos1.PushBack(write_boxcollider2d.vertices[1][1], allocator);
				bvertice.PushBack(bvertice_pos1, allocator);

				rapidjson::Value bvertice_pos2(rapidjson::kArrayType);
				bvertice_pos2.PushBack(write_boxcollider2d.vertices[2][0], allocator);
				bvertice_pos2.PushBack(write_boxcollider2d.vertices[2][1], allocator);
				bvertice.PushBack(bvertice_pos2, allocator);

				rapidjson::Value bvertice_pos3(rapidjson::kArrayType);
				bvertice_pos3.PushBack(write_boxcollider2d.vertices[3][0], allocator);
				bvertice_pos3.PushBack(write_boxcollider2d.vertices[3][1], allocator);
				bvertice.PushBack(bvertice_pos3, allocator);

				components.AddMember("Vertices", bvertice, allocator);
			}

			//Audio Component
			if (entity.HasComponent<AudioComponent>()) {
				components.AddMember("AudioComponent", true, allocator);
			}
			 //TO DO Cherno 51.16 near there for serialising scripts
			//Scripting Component
			if (entity.HasComponent<ScriptComponent>()) {
				components.AddMember("ScriptComponent", true, allocator);

				auto& scriptComponent = entity.GetComponent<ScriptComponent>();
				rapidjson::Value class_name;
				class_name.SetString(scriptComponent.ClassName.c_str(), allocator);
				components.AddMember("ClassName", class_name, allocator);

			}
			
			//Particle component
			if (entity.HasComponent<ParticleComponent>()) {
				components.AddMember("ParticleComponent", true, allocator);
			}
			if (entity.HasComponent<Particle>()) {
				continue;
			}

			if (entity.HasComponent<ObjectType>()) {
				components.AddMember("ObjectType", true, allocator);

				const auto& write_object_type = entity.GetComponent<ObjectType>();
				if (write_object_type.type == ObjectTypeID::nil) {
					components.AddMember("ObjectType_IDname", "Nil", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::player) {
					components.AddMember("ObjectType_IDname", "Player", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::enemy) {
					components.AddMember("ObjectType_IDname", "Enemy", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::obstacle) {
					components.AddMember("ObjectType_IDname", "Obstacle", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::bullet) {
					components.AddMember("ObjectType_IDname", "Bullet", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::pickup) {
					components.AddMember("ObjectType_IDname", "Pickup", allocator);
				}
				else if (write_object_type.type == ObjectTypeID::goal) {
					components.AddMember("ObjectType_IDname", "Goal", allocator);
				}
			}

			if (entity.HasComponent<CombatComponent>()) {
				components.AddMember("CombatComponent", true, allocator);

				const auto& write_combat = entity.GetComponent<CombatComponent>();
				components.AddMember("CombatComponent_Attack", write_combat.attack, allocator);
				components.AddMember("CombatComponent_Attack_Interval", write_combat.attack_interval, allocator);
				components.AddMember("CombatComponent_Health", write_combat.health, allocator);
				components.AddMember("CombatComponent_Death_Timer", write_combat.death_timer, allocator);
			}

			if (entity.HasComponent<Grid>()) {
				components.AddMember("Grid", true, allocator);
				const auto& write_grid = entity.GetComponent<Grid>();

				rapidjson::Value gridWorldSize(rapidjson::kArrayType);
				gridWorldSize.PushBack(write_grid.gridWorldSize.x, allocator);
				gridWorldSize.PushBack(write_grid.gridWorldSize.y, allocator);
				components.AddMember("Grid_GridWorldSize", gridWorldSize, allocator);

				components.AddMember("Grid_NodeRadius", write_grid.nodeRadius, allocator);

				rapidjson::Value origin(rapidjson::kArrayType);
				origin.PushBack(write_grid.origin.x, allocator);
				origin.PushBack(write_grid.origin.y, allocator);
				components.AddMember("Grid_Origin", origin, allocator);
			}

			if (entity.HasComponent<AStarPathfindingObstacle>()) {
				components.AddMember("AStarPathfindingObstacle", true, allocator);
				const auto& write_asp_obstacle = entity.GetComponent<AStarPathfindingObstacle>();

				rapidjson::Value position(rapidjson::kArrayType);
				position.PushBack(write_asp_obstacle.position.x, allocator);
				position.PushBack(write_asp_obstacle.position.y, allocator);
				components.AddMember("ASP_Obstacle_Position", position, allocator);

				rapidjson::Value size(rapidjson::kArrayType);
				size.PushBack(write_asp_obstacle.size.x, allocator);
				size.PushBack(write_asp_obstacle.size.y, allocator);
				components.AddMember("ASP_Obstacle_Size", size, allocator);

				components.AddMember("ASP_Obstacle_ID", write_asp_obstacle.ID, allocator);
			}

			if (entity.HasComponent<AStarPathfindingAgent>()) {
				components.AddMember("AStarPathfindingAgent", true, allocator);
			}
			
			if (entity.HasComponent<Target>()) {
				components.AddMember("Target", true, allocator);
			}

			//add all the component data to entity array
			objects.PushBack(components, allocator);
		}

		//add the entity array to document
		doc.AddMember("Untitled", objects, allocator);

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
	/*void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
	}*/
	void SceneSerializer::Deserialize(const std::string& filepath)
	{
		//Open the text file stream serializer
		std::ifstream ifs(filepath);
		if (!ifs) {
			return SceneSerializer::Deserialize(filepath);
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

		const rapidjson::Value& object = doc["Untitled"];
		assert(object.IsArray());

		const rapidjson::Value& cam_trans = doc["Camera_Translation"];
		Graphics::cam_stuff.translation.x = cam_trans[0].GetFloat();
		Graphics::cam_stuff.translation.y = cam_trans[1].GetFloat();

		Graphics::cam_stuff.rotation = doc["Camera_Rotation"].GetFloat();

		const rapidjson::Value& cam_scale = doc["Camera_Scale"];
		Graphics::cam_stuff.scaling.x = cam_scale[0].GetFloat();
		Graphics::cam_stuff.scaling.y = cam_scale[1].GetFloat();

		Graphics::cam_stuff.c_width = doc["Camera_c_Width"].GetFloat();
		Graphics::cam_stuff.c_height = doc["Camera_c_Height"].GetFloat();
		Graphics::cam_stuff.c_ar = doc["Camera_Aspect_Ratio"].GetFloat();

		Graphics::cam_stuff.height = doc["Camera_Height"].GetFloat();


		auto entities = m_Scene->m_Registry->GetEntities();
		for (auto e : entities)
		{
			Entity entity = { e.first ,m_Scene };
			m_Scene->DestroyEntity(entity);
		}


		for (rapidjson::SizeType i = 0; i < object.Capacity(); ++i) {
			const rapidjson::Value& component = object[i];

			//create new entity
			Entity entity = m_Scene->CreateEntity(component["name"].GetString());

			//graphic component
			if (component.HasMember("Transform")) {

				auto& e = entity.GetComponent<Transform>();

				const rapidjson::Value& trans = component["Translation"];
				e.translation.x = trans[0].GetFloat();
				e.translation.y = trans[1].GetFloat();

				e.rotation = (component["Rotation"].GetFloat());

				const rapidjson::Value& scale = component["Scaling"];
				e.scaling.x = scale[0].GetFloat();
				e.scaling.y = scale[1].GetFloat();

				e.z_axis = (component["Layer"].GetFloat());
				e.alpha_val = (component["Blend"].GetFloat());

				const rapidjson::Value& color = component["Color"];
				e.color.r = color[0].GetFloat();
				e.color.g = color[1].GetFloat();
				e.color.b = color[2].GetFloat();
			}

			if (component.HasMember("Texture")) {
				auto& e = entity.AddComponent<Texture>();
				//e.texid = component["Text_texid"].GetInt();
				e.text_file = (int)(component["Text_file"].GetFloat());
				e.filename = component["Text_filename"].GetString();
				e.texid = stash.Text_Storage[e.filename.c_str()];

				e.animation_but = component["Text_animation_but"].GetInt();
				e.counter = component["Text_counter"].GetFloat();
				e.speed = component["Text_speed"].GetFloat();
				e.slices = component["Text_slices"].GetFloat();
				e.switch_text = component["Text_switch_text"].GetFloat();
			}

			if (component.HasMember("Box_collider")) {

				auto& e = entity.AddComponent<Box_collider>();


				const rapidjson::Value& b_trans = component["Box_trans"];
				e.box_trans.translation.x = b_trans[0].GetFloat();
				e.box_trans.translation.y = b_trans[1].GetFloat();

				e.box_trans.rotation = (component["Box_rotate"].GetFloat());

				const rapidjson::Value& b_scale = component["Box_scale"];
				e.box_trans.scaling.x = b_scale[0].GetFloat();
				e.box_trans.scaling.y = b_scale[1].GetFloat();

				e.box_trans.compute_mdl_to_ndc_xform();

				auto vert = stash.Shader_Storage.find("collider.vert");
				auto frag = stash.Shader_Storage.find("collider.frag");

				e.box_shader.setup_shdr_pgm(vert->first, vert->second);
				e.box_mesh.setup_vao();

				e.box_tog = 0;
			}

			//physics component
			if (component.HasMember("RigidBody")) {

				auto& e = entity.AddComponent<RigidBody>();

				const rapidjson::Value& pos = component["Position"];
				e.m_Position.x = pos[0].GetFloat();
				e.m_Position.y = pos[1].GetFloat();

				//const rapidjson::Value& vel = component["Velocity"];
				e.Velocity = (component["Velocity"].GetFloat());
			}

			if (component.HasMember("BoxCollider2D")) {

				auto& e = entity.AddComponent<BoxCollider2D>();

				const rapidjson::Value& bmin = component["Bound_min"];
				e.bounds.min.x = bmin[0].GetFloat();
				e.bounds.min.y = bmin[1].GetFloat();

				const rapidjson::Value& bmax = component["Bound_max"];
				e.bounds.max.x = bmax[0].GetFloat();
				e.bounds.max.y = bmax[1].GetFloat();

				std::array<float, 2> temp_vertices;
				std::array<std::array<float, 2>, 4> temp_result;
				const rapidjson::Value& bvertice = component["Vertices"];

				for (rapidjson::SizeType i = 0; i < bvertice.Size(); ++i) {
					const rapidjson::Value& bvertice_pos = bvertice[i];
					temp_vertices[0] = bvertice_pos[0].GetFloat();
					temp_vertices[1] = bvertice_pos[1].GetFloat();
					temp_result[i] = temp_vertices;
				}

				e.vertices = temp_result;
				e.ArrayToVector();
			}
			//TO DO Cherno 51.16 near there for serialising scripts
			//ScriptComponent
			if (component.HasMember("ScriptComponent"))
			{
				auto& sc = entity.AddComponent<ScriptComponent>();

				sc.ClassName = component["ClassName"].GetString();
			}
			
			if (component.HasMember("ParticleComponent")) {
				auto& e = entity.AddComponent<ParticleComponent>();
			}

			if (component.HasMember("ObjectType")) {
				auto& e = entity.AddComponent<ObjectType>();

				const std::string idname = component["ObjectType_IDname"].GetString();
				if (idname == "Nil") {
					e.type = ObjectTypeID::nil;
				}
				else if (idname == "Player") {
					e.type = ObjectTypeID::player;
				}
				else if (idname == "Enemy") {
					e.type = ObjectTypeID::enemy;
				}
				else if (idname == "Obstacle") {
					e.type = ObjectTypeID::obstacle;
				}
				else if (idname == "Bullet") {
					e.type = ObjectTypeID::bullet;
				}
				else if (idname == "Pickup") {
					e.type = ObjectTypeID::pickup;
				}
				else if (idname == "Goal") {
					e.type = ObjectTypeID::goal;
				}
			}

			if (component.HasMember("CombatComponent")) {
				auto& e = entity.AddComponent<CombatComponent>();
				e.attack = component["CombatComponent_Attack"].GetFloat();
				e.attack_interval = component["CombatComponent_Attack_Interval"].GetFloat();
				e.health = component["CombatComponent_Health"].GetFloat();
			}

			if (component.HasMember("Grid")) {
				auto& e = entity.AddComponent<Grid>();
			
				auto & gridData = entity.GetComponent<Grid>();
				
				aStarSystem.grid = &gridData;

				const rapidjson::Value& gridWorldSize = component["Grid_GridWorldSize"];

				e.gridWorldSize.x = gridWorldSize[0].GetFloat();
				e.gridWorldSize.y = gridWorldSize[1].GetFloat();

				e.nodeRadius = component["Grid_NodeRadius"].GetFloat();

				const rapidjson::Value& origin = component["Grid_Origin"];
				e.origin.x = origin[0].GetFloat();
				e.origin.y = origin[1].GetFloat();
				std::cout << "Start Size Nodes: " << aStarSystem.grid->nodeGrids.size() << "\n";
				
				gridSystem.obstacles.clear();
				std::cout << "Start Size Obstacles " << gridSystem.obstacles.size() << "\n";
				//std::cout
				//gridSystem.ClearGrid(*aStarSystem.grid);

				aStarSystem.once = false;
				gridSystem.SetGridParameters(*aStarSystem.grid, e.gridWorldSize, e.nodeRadius);
				
				//gridSystem.ClearGrid(e);
				
				gridSystem.CreateGrid(*aStarSystem.grid);
				gridSystem.AddNeighboursToGrid(*aStarSystem.grid);

				gridData = *aStarSystem.grid;
			}

			if (component.HasMember("AStarPathfindingObstacle")) 
			{
				auto& e = entity.AddComponent<AStarPathfindingObstacle>();

				const rapidjson::Value& position = component["ASP_Obstacle_Position"];
				e.position.x = position[0].GetFloat();
				e.position.y = position[1].GetFloat();

				const rapidjson::Value& size = component["ASP_Obstacle_Size"];
				e.size.x = size[0].GetFloat();
				e.size.y = size[1].GetFloat();

				e.ID = component["ASP_Obstacle_ID"].GetInt();

			}

			if (component.HasMember("AStarPathfindingAgent")) {
				auto& e = entity.AddComponent<AStarPathfindingAgent>();
			}
			
			
			if (component.HasMember("Target")) {
				auto& e = entity.AddComponent<Target>();
			}

			//Audio
			/*if (component.HasMember("AudioComponent")) {
				AudioComponent Audio_Component;
				factory.AddComponent<AudioComponent>(gameObject, Audio_Component);
			}

				entities.push_back(gameObject);
			}*/

		}
		//bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
		//{
		//	//not implemented
		//	TH_CORE_ASSERT(false , "notimplemented");
		//}

			//entities.push_back(gameObject);
		
		/*return true;*/
	}
}