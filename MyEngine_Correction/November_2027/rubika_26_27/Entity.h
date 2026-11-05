#pragma once

#define ENTITY_TAG_NONE          0
#define ENTITY_TAG_STATIC        1 << 0
#define ENTITY_TAG_DYNAMIC       1 << 1
#define ENTITY_TAG_NEUTRAL       1 << 2
#define ENTITY_TAG_ENEMY         1 << 3
#define ENTITY_TAG_PLAYER        1 << 4

#include <string>
#include <vector>

#include <Windows.h>

class IComponent;

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity(std::string friendlyName = "");
	~Entity();

	virtual void Start();
	void Update(float fDeltaTime);
	void Destroy();

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;
	
	void AddTag(unsigned int tag);
	void RemoveTag(unsigned int tag);
	bool HasTag(unsigned int tag);
	unsigned int GetTags() const { return Tags; }

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
	void DrawDebug();

	const std::string& GetName() const { return FriendlyName; }

protected:
	std::string FriendlyName;
	std::vector<IComponent*> Components;
	unsigned int Tags;
};

#include <Entity.hxx>
