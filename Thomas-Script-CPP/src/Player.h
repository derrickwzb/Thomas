#pragma once
#include "ScriptUtils.h"

struct Player : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Player Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		float Cursor_X = Thomas::Input::GetMouseX() - Thomas::Graphics::width / 2;
		float Cursor_Y = -(Thomas::Input::GetMouseY() - Thomas::Graphics::height / 2);

		//Thomas::Scene* sc = GetScene();

		auto& trans = GetComponent<Thomas::Transform>();
		auto& tag_c = GetComponent<Thomas::TagComponent>();
		auto& box_data = GetComponent<Thomas::Box_collider>();

		//sync camera with player
		Thomas::Graphics::cam_stuff.translation.x = trans.translation.x;
		Thomas::Graphics::cam_stuff.translation.y = trans.translation.y;


		// Mouse Following
		glm::vec2 A = glm::vec2(0, 1.f);
		glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
		B.x -= trans.translation.x;
		B.y -= trans.translation.y;
		float dot_product = glm::dot(A, B);
		float angle = -acos(dot_product / (glm::length(A) * glm::length(B)));
		if ((B.x + trans.translation.x) < trans.translation.x)
			angle *= -1;
		trans.rotation = angle;
		Thomas::Graphics::cam_stuff.rotation = (angle * -1.f);


		if (Thomas::Input::IsKeyPressed(TH_KEY_W)) {
			trans.translation.y -= 1.f * ts;
			box_data.box_trans.translation.y -= 1.f * ts;
		}
		if (Thomas::Input::IsKeyPressed(TH_KEY_S)) {
			trans.translation.y += 1.f * ts;
			box_data.box_trans.translation.y += 1.f * ts;
		}
		if (Thomas::Input::IsKeyPressed(TH_KEY_A)) {
			trans.translation.x -= 1.f * ts;
			box_data.box_trans.translation.x -= 1.f * ts;
		}
		if (Thomas::Input::IsKeyPressed(TH_KEY_D)) {
			trans.translation.x += 1.f * ts;
			box_data.box_trans.translation.x += 1.f * ts;
		}

		
	}

	void OnDestroy()
	{

	}

	float m_speed;
	int m_lives;
};