#pragma once

#include "thpch.h"
#include "Thomas/Core/Timestep.h"
//#include "Thomas/Scene/Entity.h"
//#include "BehaviourFCT.h"

namespace Thomas {
	using Entity = unsigned int;
	//static float change = 5.f;
	//static int w = Graphics::width;
	//static int h = Graphics::height;

	//static bool logic02_run = false;

	class GameObjectFactory;

	//class LogicSystem
	//{
	//public:
	//	void Init() {
	//		//Thomas::Application& app = Thomas::Application::Get();
	//		//GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
	//		//glfwGetWindowSize(window, &width, &height);
	//	}

	//	void Update() {
	//		for (auto& iter : m_BehaviourComponent) {
	//			m_behaviour[iter->GetBehaviourIndex()]->m_UpdateBehaviour(iter->GetOwner());
	//		}
	//	}

	//	void End() {
	//	}

	//	void AddBehaviour(BehaviourFCT* behaviour);
	//	~Logic();
	//private:
	//	//inline static int width{};
	//	//inline static int height{};

	//	std::vector<BehaviourFCT*> m_behaviour;
	//	std::vector<BehaviourComponent*> m_BehaviourComponent;
	//};

	class Logic01
	{
	public:

		void update(Entity entity, Timestep ts);

	private:

	};

	class Logic02 {
	public:
		void update(Entity entity, Timestep ts);
	};

	class Logic {
	public:
		void Init();
		void Update(std::vector<Entity> allentity, Timestep ts);
	};

	inline static Logic logic;

}
