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
}
