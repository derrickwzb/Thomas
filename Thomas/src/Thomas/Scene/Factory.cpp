#include "thpch.h"
#include "Factory.h"

namespace Thomas {

	GameObjectFactory factory;

	GameObjectFactory::GameObjectFactory()
	{
		// Create pointers to each manager
		ComponentManagers = std::make_unique<ComponentManager>();
		EntityManagers = std::make_unique<EntityManager>();
		SystemManagers = std::make_unique<SystemManager>();
	}

	GameObjectFactory::~GameObjectFactory()
	{

	}

	Entity GameObjectFactory::CreateEmptyComposition()
	{
		return EntityManagers->CreateEntity();
	}

	//Entity GameObjectFactory::BuildAndSerialize(const std::string& filename)
	//{
	//	//Open the text file stream serializer
	//	std::ifstream stream;
	//	stream.open(filename.c_str(), std::ios_base::in);
	//	if (!stream)
	//	{
	//		perror("Error opening file");
	//	}
	//	std::string text;
	//	//std::string componentName{};
	//	int i = 0;
	//	float f = 0;

	//	Entity gameObject = factory.CreateEmptyComposition();

	//	while (!stream.eof())
	//	{
	//		//std::getline(stream, text);

	//		//get component type
	//		stream >> i;

	//		if (i == CT_Point)
	//		{
	//			Point newpoint = Point();
	//		}

	//		factory.AddComponent<componentName.c_str()>(gameObject, )
	//	}
	//}

	//Entity GameObjectFactory::Create(const std::string& filename)
	//{
		//Entity entity = BuildAndSerialize(filename);
		//if (entity)
		//{
		//	gCoordinator.CreateEntity();
		//}
		//return entity;
	//}

	void GameObjectFactory::Destroy(Entity gameObject)
	{
		EntityManagers->DestroyEntity(gameObject);

		ComponentManagers->EntityDestroyed(gameObject);

		SystemManagers->EntityDestroyed(gameObject);
	}

	//Clean up the game world
	void GameObjectFactory::DestroyAllObjects(std::vector<Entity> allentity)
	{
		std::vector<Entity> entity;

		for (auto const& entity : allentity)
		{
			EntityManagers->DestroyEntity(entity);

			ComponentManagers->EntityDestroyed(entity);

			SystemManagers->EntityDestroyed(entity);
		}
	}

	//Component
	// Component methods
	template<typename T>
	void GameObjectFactory::RegisterComponent()
	{
		ComponentManagers->RegisterComponent<T>();
	}

	template<typename T>
	void GameObjectFactory::AddComponent(Entity entity, T component)
	{
		ComponentManagers->AddComponent<T>(entity, component);

		auto signature = EntityManagers->GetSignature(entity);

		signature.set(ComponentManagers->GetComponentType<T>(), true);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void GameObjectFactory::RemoveComponent(Entity entity)
	{
		ComponentManagers->RemoveComponent<T>(entity);

		auto signature = EntityManagers->GetSignature(entity);
		signature.set(ComponentManagers->GetComponentType<T>(), false);
		EntityManagers->SetSignature(entity, signature);

		SystemManagers->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GameObjectFactory::GetComponent(Entity entity)
	{
		return ComponentManagers->GetComponent<T>(entity);
	}

	template<typename T>
	void GameObjectFactory::ChangeComponent(Entity entity, T newcomponent)
	{
		ComponentManagers->ChangeComponent<T>(entity, newcomponent);
	}

	template<typename T>
	bool GameObjectFactory::HasComponent(Entity entity) const
	{
		auto getsignature = ComponentManagers->GetComponentType<T>();
		auto bit = pow(2, getsignature);

		return EntityManagers->HasSignature(entity, Signature(bit));
	}

	template<typename T>
	ComponentType GameObjectFactory::GetComponentType()
	{
		return ComponentManagers->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> GameObjectFactory::RegisterSystem()
	{
		return SystemManagers->RegisterSystem<T>();
	}

	template<typename T>
	void GameObjectFactory::SetSystemSignature(Signature signature)
	{
		SystemManagers->SetSignature<T>(signature);
	}

}
