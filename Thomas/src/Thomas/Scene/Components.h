#pragma once
#include "Thomas/Math/Math.hpp"
#include "ScriptableEntity.h"

namespace Thomas {

	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		CT_Point,
		CT_Colour,
		CT_Triangle,
		CT_Transform,
		CT_Shader_manager,
		CT_Mesh,
		CT_Texture,
		CT_Camera,
		CT_Box_collider,
		CT_RigidBody,
		CT_BoxCollider2D,
		CT_Logic01,
		CT_Logic02,

		//Max component number
		CT_MaxComponents
	};

	struct Position
	{
		float x;
		float y;
		Position() = default;
		Position(const Position&) = default;
	};

	struct Colour 
	{
		float r;
		float g;
		float b;
		float a;
		Colour() = default;
		Colour(const Colour&) = default;
	};

	struct Triangle {
		float positionx;
		float positiony;
		float positionz;
	};

	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	//using Entity = unsigned int;
	//static float change = 5.f;
	//static int w = Graphics::width;
	//static int h = Graphics::height;
	//static bool logic02_run = false;

	//class Logic01
	//{
	//public:

	//	void update(Entity entity) {
	//		auto trans_data = factory.GetComponent<Transform>(entity);
	//		auto box_data = factory.GetComponent<Box_collider>(entity);

	//		if (trans_data.translation.x >= w) {
	//			trans_data.translation.x -= change;
	//		}
	//		if (trans_data.translation.x <= w) {
	//			trans_data.translation.x += change;
	//		}
	//		if (trans_data.translation.y >= h) {
	//			trans_data.translation.y -= change;
	//		}
	//		if (trans_data.translation.y <= h) {
	//			trans_data.translation.y += change;
	//		}

	//		factory.ChangeComponent<Transform>(entity, trans_data);
	//		factory.ChangeComponent<Box_collider>(entity, box_data);
	//	}

	//private:

	//};

	//class Logic02 {
	//public:
	//	void update(Entity entity) {
	//		auto trans_data = factory.GetComponent<Transform>(entity);
	//		auto box_data = factory.GetComponent<Box_collider>(entity);

	//		if (Input::IsKeyPressed(TH_KEY_SPACE)) {
	//			if (logic02_run == false) {
	//				logic02_run = true;
	//			}
	//			else {
	//				logic02_run = false;
	//			}

	//		}

	//		if (logic02_run == true) {
	//			if (trans_data.translation.x >= Input::GetMouseX()) {
	//				trans_data.translation.x -= change;
	//			}
	//			if (trans_data.translation.x <= Input::GetMouseX()) {
	//				trans_data.translation.x += change;
	//			}
	//			if (trans_data.translation.y >= Input::GetMouseY()) {
	//				trans_data.translation.y -= change;
	//			}
	//			if (trans_data.translation.y <= Input::GetMouseY()) {
	//				trans_data.translation.y += change;
	//			}
	//		}

	//		factory.ChangeComponent<Transform>(entity, trans_data);
	//		factory.ChangeComponent<Box_collider>(entity, box_data);

	//	}
	//};
}
