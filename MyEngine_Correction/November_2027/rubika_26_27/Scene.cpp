#include "Scene.h"

#include <Entity.h>
#include <iostream>

#include "Player.h"

#include <Imgui/imgui.h>
#include "DynamicColliderComponent.h"

Scene::Scene(const std::string& name) : Name(name)
{
	Hash = std::hash<std::string>{}(Name);
}

Scene::~Scene()
{}

void Scene::Start()
{
	for (Entity* e : Entities)
	{
		e->Start();
	}
}

void Scene::Update(float fDeltaTime)
{
	for (Entity* e : Entities)
	{
		e->Update(fDeltaTime);
	}
	
	for (Entity* e1 : Entities)
	{
		DynamicColliderComponent* e1C = e1->GetComponent<DynamicColliderComponent>();
		unsigned int e1Tags = e1->GetTags();
		
		if (e1C == nullptr) break;
		
		for (Entity* e2 : Entities)
		{
			DynamicColliderComponent* e2C = e2->GetComponent<DynamicColliderComponent>();
			unsigned int e2Tags = e2->GetTags();
			
			if (e1 != e2 && e2C != nullptr && e1C->GetCollisionMask() == e2Tags)
			{
				std::optional<sf::Rect<float>> intersection = e1C->GetCollider().findIntersection(e2C->GetCollider());
				if (intersection != std::nullopt)
				{
					std::cout << "TOUCHED" << std::endl;
				}
			}
		}
	}
}

void Scene::Destroy()
{
	for (Entity* e : Entities)
	{
		e->Destroy();
	}
}

Entity* Scene::CreateEntity(const std::string& entityName)
{
	Entity* e = new Entity(entityName);
	Entities.push_back(e);
	return e;
}

Player* Scene::CreatePlayer(const std::string& playerName)
{
	Player* p = new Player(playerName);
	Entities.push_back(p);
	GamePlayer = p;
	return p;
}

Obstacle* Scene::CreateObstacle(const std::string& ObstacleName)
{
	Obstacle* o = new Obstacle(ObstacleName);
	Entities.push_back(o);
	return o;
}

void Scene::RemoveEntity(Entity* entity)
{
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		if (entity == *it)
		{
			entity->Destroy();
			it = Entities.erase(it);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for (Entity* e : Entities)
	{
		e->Draw(window);
	}
}

void Scene::DrawDebug()
{
	for (Entity* e : Entities)
	{
		ImGui::PushID(e);

		const char* preview = e->GetName().size() ? e->GetName().c_str() : "Entity";
		if (ImGui::TreeNode(preview))
		{
			e->DrawDebug();
			ImGui::TreePop();
		}

		ImGui::PopID();
	}
}

