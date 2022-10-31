#pragma once
#include "thpch.h"
#include "ScriptableEntity.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"
#include "Thomas/Physics/physicsSystem.h"

namespace Thomas {

	class CameraController : public ScriptableEntity {
	public:

		void OnCreate() {
		}

		void OnDestory() {
		}

		void OnUpdate(Timestep ts) {
			//auto& transform = factory.GetComponent<Transform>(entity);
			//float speed = 5.0f;
			//if (Input::IsKeyPressed(TH_KEY_W)) {
			//	transform.translation.y += speed * ts;
			//}
			//if (Input::IsKeyPressed(TH_KEY_A)) {
			//	transform.translation.x -= speed * ts;
			//}
			//if (Input::IsKeyPressed(TH_KEY_S)) {
			//	transform.translation.y -= speed * ts;
			//}
			//if (Input::IsKeyPressed(TH_KEY_D)) {
			//	transform.translation.x += speed * ts;
			//}
		}

		//GameObjectFactory::AddComponent<NativeScriptComponent>(entity).Bind<CameraController>();

	private:
		Entity entity;
	};

	//CameraController temp;
	//factory.AddComponent<NativeScriptComponent>(entity, temp).Bind<CameraController>();
	/*
	void UpdatePhysic(Entity entity, Timestep ts) {
		auto transform = factory.GetComponent<Transform>(entity);
		auto rigidbody = factory.GetComponent<RigidBody>(entity);
		float force = 0.005f;
		float acceleration = force / rigidbody.GetMass();
		rigidbody.Velocity = rigidbody.Velocity + acceleration * ts;

		if (Input::IsKeyPressed(TH_KEY_W)) {

			physicsSystem.temp(transform.translation.y, -rigidbody.Velocity);
			//std::cout << "move w\n";
		}
		if (Input::IsKeyPressed(TH_KEY_A)) {
			physicsSystem.temp(transform.translation.x, -rigidbody.Velocity);
			//std::cout << "move a\n";
		}
		if (Input::IsKeyPressed(TH_KEY_S)) {
			physicsSystem.temp(transform.translation.y, rigidbody.Velocity);
			//std::cout << "move s\n";
		}
		if (Input::IsKeyPressed(TH_KEY_D)) {
			physicsSystem.temp(transform.translation.x, rigidbody.Velocity);
			//std::cout << "move d\n";
		}

		factory.UpdateComponent<Transform>(entity, transform);
		factory.UpdateComponent<RigidBody>(entity, rigidbody);
	}
	*/
}
