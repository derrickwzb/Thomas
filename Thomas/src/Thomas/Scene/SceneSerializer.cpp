#include "thpch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/prettywriter.h"

namespace Thomas
{
	SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& context)
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

				Entity entity{ e.first , m_Scene.get() };
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
					components.AddMember("Text_file", write_tex.text_file, allocator);
				}
				if (entity.HasComponent<Camera>()) {
					components.AddMember("Camera", true, allocator);
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

	bool SceneSerializer::Deserialize(const std::string& filepath)
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
		}

		if (component.HasMember("Texture")) {
			auto& e = entity.AddComponent<Texture>();
			e.text_file = (int)(component["Text_file"].GetFloat());
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

		////Audio
		//if (component.HasMember("AudioComponent")) {
		//	AudioComponent Audio_Component;
		//	factory.AddComponent<AudioComponent>(gameObject, Audio_Component);
		//}

			//entities.push_back(gameObject);
		}

	}
}