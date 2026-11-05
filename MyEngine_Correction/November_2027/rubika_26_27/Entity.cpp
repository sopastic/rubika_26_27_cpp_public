#include "Entity.h"

#include <IComponent.h>
#include <iostream>
#include <RenderComponent.h>
#include <Imgui/imgui.h>

#include "DynamicColliderComponent.h"
#include "Logger.h"


Entity::Entity(std::string friendlyName) : FriendlyName(friendlyName)
{
}

Entity::~Entity()
{
	for (const IComponent* component : Components)
	{
		delete component;
	}

	Components.clear();
}

void Entity::Start()
{
	for (IComponent* c : Components)
	{
		c->Start();
	}
}

void Entity::Update(float fDeltaTime)
{
	for (IComponent* c : Components)
	{
		c->Update(fDeltaTime);
	}
}

void Entity::Destroy()
{
	for (IComponent* c : Components)
	{
		c->Destroy();
	}
}

void Entity::AddTag(unsigned int tag)
{
	if (!HasTag(tag)) Tags |= tag;
}

void Entity::RemoveTag(unsigned int tag)
{
	if (HasTag(tag)) Tags &= ~tag;
}

bool Entity::HasTag(unsigned int tag)
{
	unsigned int tagsTemp = Tags;
	tagsTemp &= tag;
	bool hasTag = tagsTemp == tag;
	return hasTag;
}


void Entity::Draw(sf::RenderWindow& window) const
{
	RenderComponent* r = GetComponent<RenderComponent>();
	if (r)
	{
		r->Draw(window);
	}
	DynamicColliderComponent* dcc = GetComponent<DynamicColliderComponent>();
	if (dcc)
	{
		dcc->Draw(window);
	}
}

void Entity::DrawDebug()
{
#ifdef _USE_IMGUI
	for (IComponent* c : Components)
	{
		if (ImGui::TreeNode(c->GetName()))
		{
			c->DrawDebug();
			ImGui::TreePop();
		}
	}
#endif
}
