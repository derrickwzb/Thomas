#pragma once
#include "ScriptUtils.h"
#include "AllScripts.h"

static float g_bulletLifetime;

struct Player : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Player Script Instantiated");
		g_bulletLifetime = 0.f;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		float Cursor_X = Thomas::Input::GetMouseX() - Thomas::Graphics::width / 2;
		float Cursor_Y = -(Thomas::Input::GetMouseY() - Thomas::Graphics::height / 2);

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
		
		if (Thomas::Input::IsMouseButtonPressed(TH_MOUSE_BUTTON_LEFT))
		{
			if (g_bulletLifetime <= 0)
			{
				auto& entity = GetScene()->CreateEntity("Bullet");
				InitBullet(entity, GetSelf());
			}
		}

		if (g_bulletLifetime >= 0.f) {
			g_bulletLifetime -= ts;
		}
	}

	void OnDestroy()
	{

	}

	void InitBullet(Thomas::Entity& entity, Thomas::Entity& player)
	{
		if (g_bulletLifetime <= 0.f) {
			//set transform data
			auto& trans = entity.GetComponent<Thomas::Transform>();
			trans.scaling.x = 0.6f;
			trans.scaling.y = 0.6f;
			trans.translation.x = player.GetComponent<Thomas::Transform>().translation.x;
			trans.translation.y = player.GetComponent<Thomas::Transform>().translation.y;
			trans.rotation = player.GetComponent<Thomas::Transform>().rotation;

			//set texture
			auto& tex = entity.AddComponent<Thomas::Texture>();
			tex.texid = Thomas::stash.Text_Storage["rotten_core_glow_1.png"];
			tex.text_file = 132;
			tex.filename = "rotten_core_glow_1.png";

			//set bounding box data
			auto& box = entity.GetComponent<Thomas::Box_collider>();
			box.box_tog = 0;
			box.box_trans.scaling.x = 0.4f;
			box.box_trans.scaling.y = 0.4f;
			box.box_trans.translation.x = player.GetComponent<Thomas::Transform>().translation.x;
			box.box_trans.translation.y = player.GetComponent<Thomas::Transform>().translation.y;

			auto& bullet_data = entity.AddComponent<Thomas::BulletComponent>();
			bullet_data.speed = 0.5f;
			bullet_data.time = 1.5f;

			auto& type = entity.AddComponent<Thomas::ObjectType>();
			type.type = Thomas::ObjectTypeID::bullet;

			auto& combat = entity.AddComponent<Thomas::CombatComponent>();
			combat.attack = 1.f;

			auto& box_collider2d = entity.AddComponent<Thomas::BoxCollider2D>();
			auto& data = entity.AddComponent<Thomas::RigidBody>();
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);

			//bullet movement direction based on the mouse position and center of the screen
			if (((Thomas::Input::GetMouseX() / Thomas::Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
				bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
				bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
			}
			else if (((Thomas::Input::GetMouseX() / Thomas::Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
				bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
				bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
			}
			g_bulletLifetime += 0.5f;
		}

		float m_speed;
		int m_lives;
	}
};