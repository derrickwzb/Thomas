#include "ecs2.h"
#include <iostream>

Coordinator gCoordinator;
//
//void Print(std::vector<Entity> allentity) {
//
//	for (auto const& entity : allentity) {
//
//		if (gCoordinator.HasComponent<Rigidbody2DComponent>(entity))
//		{
//			auto print = gCoordinator.GetComponent<Rigidbody2DComponent>(entity);
//			std::cout << "entity " << entity << ": "
//				<< print.posCurr.x << ", " << print.posCurr.y << "; "
//				<< print.velCurr.x << ", " << print.velCurr.y << "; "
//				<< print.dirCurr << std::endl;
//		}
//	}
//
//	std::cout << std::endl;
//}
//
//const float	 SHIP_ACCEL_FORWARD = 40.f;
//float g_dt = 5;
//
//struct Movement
//{
//	static void moveUp(Entity object, float dirCurr = 0.f, Vec2 velCurr = {}, float acceleration = 0.f)
//	{
//		Vec2 added;
//		auto data = gCoordinator.GetComponent<Rigidbody2DComponent>(object);
//		Vector2DSet(added, cosf(data.dirCurr), sinf(data.dirCurr));//calculate the direction of the ship
//
//		// Find the velocity according to the acceleration 
//		Vector2DScale(added, added, SHIP_ACCEL_FORWARD); //scale the vector by the the acceleration forward
//		Vector2DScale(added, added, g_dt); //scale the vector by the the delta time
//		Vector2DAdd(data.velCurr, data.velCurr, added); //add the current ship velocity to the vector
//
//		// Limit your speed over here
//		Vector2DScale(data.velCurr, data.velCurr, 0.99f); //speed * 0.99 to simulate friction
//
//		gCoordinator.ChangeComponent<Rigidbody2DComponent>(object, data);
//	}
//	/*
//	static void moveDown(GameObjInst* object = nullptr, float dirCurr = 0.f, CSD1130::Vec2 velCurr = {}, float acceleration = 0.f)
//	{
//		CSD1130::Vec2 added;
//		CSD1130::Vector2DSet(added, -cosf(spShip->dirCurr), -sinf(spShip->dirCurr));//calculate the direction of the ship
//
//		// Find the velocity according to the acceleration 
//		CSD1130::Vector2DScale(added, added, SHIP_ACCEL_BACKWARD); //scale the vector by the the acceleration backward
//		CSD1130::Vector2DScale(added, added, g_dt); //scale the vector by the the delta time
//		CSD1130::Vector2DAdd(spShip->velCurr, spShip->velCurr, added); //add the current ship velocity to the vector
//
//		// Limit your speed over here
//		CSD1130::Vector2DScale(spShip->velCurr, spShip->velCurr, 0.99f); //speed * 0.99 to simulate friction
//
//	}
//
//	static void moveLeft(GameObjInst* object = nullptr, float speed_rot = 0.f)
//	{
//		spShip->dirCurr += SHIP_ROT_SPEED * (float)(AEFrameRateControllerGetFrameTime());
//		spShip->dirCurr = AEWrap(spShip->dirCurr, -PI, PI);
//	}
//
//	static void moveRight(GameObjInst* object = nullptr, float speed_rot = 0.f)
//	{
//		spShip->dirCurr -= SHIP_ROT_SPEED * (float)(AEFrameRateControllerGetFrameTime());
//		spShip->dirCurr = AEWrap(spShip->dirCurr, -PI, PI);
//	}*/
//};

int main()
{
	gCoordinator.Init();

	gCoordinator.RegisterComponent<Collision2D>();

	Signature signature;
	signature.set(gCoordinator.GetComponentType<Collision2D>());

	Entity object = gCoordinator.CreateEntity();
	Entity object2 = gCoordinator.CreateEntity();

	Collision2D newc;
	Collision2D newc2;

	newc.temp.max.x = 15.f;
	newc.temp.max.y = 15.f;
	newc.temp.min.x = 10.f;
	newc.temp.min.y = 10.f;
	newc.relativeVelocity.x = 10.f;
	newc.relativeVelocity.y = 10.f;

	newc2.temp.max.x = 8.f;
	newc2.temp.max.y = 8.f;
	newc2.temp.min.x = 5.f;
	newc2.temp.min.y = 5.f;
	newc2.relativeVelocity.x = 1.f;
	newc2.relativeVelocity.y = 1.f;

	gCoordinator.AddComponent<Collision2D>(object, newc);
	gCoordinator.AddComponent<Collision2D>(object2, newc2);


	auto data = gCoordinator.GetComponent<Collision2D>(object);
	auto data2 = gCoordinator.GetComponent<Collision2D>(object2);


	bool result = CollisionIntersection_RectRect(data.temp, data.relativeVelocity,
		data2.temp, data.relativeVelocity);

	std::cout << result << std::endl;
	//std::vector<Entity> entities;
	//Entity object = gCoordinator.CreateEntity();

	//Rigidbody2DComponent newrigid;

	//newrigid.posCurr.x = 1.f;
	//newrigid.posCurr.y = 1.f;

	//newrigid.velCurr.x = 1.f;
	//newrigid.velCurr.y = 1.f;

	//newrigid.dirCurr = 1.f;


	//gCoordinator.AddComponent<Rigidbody2DComponent>(object, newrigid);

	//entities.push_back(object);

	//Print(entities);


	//Movement::moveUp(object, 10.f, Vec2(10.f, 10.f), 10.f);

	//Print(entities);

	return 0;

}
