#pragma once
#include "AllScripts.h"
#include "ScriptUtils.h"

struct Bullet : public Thomas::ScriptableEntity
{
	static float g_bulletLifetime;

	void OnCreate()
	{
		g_bulletLifetime = 0.f;
		TH_CORE_INFO("Bullet Script Instantiated. ");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if (g_bulletLifetime >= 0.f) {
			g_bulletLifetime -= ts;
		}
	}

	void OnDestroy()
	{

	}

	/*static Thomas::Entity CreateBulletEntity(Thomas::Scene* scene)
	{
		Thomas::Entity bullet = scene->CreateEntity("Bullet");
		bullet.AddComponent<Thomas::NativeScriptComponent>().Bind<Bullet>();
	}*/

	static void InitBullet(Thomas::Entity& entity, Thomas::Entity& player)
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
	}
	
};
