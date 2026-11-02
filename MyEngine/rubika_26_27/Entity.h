#pragma once

#include <string>
#include <vector>

#include "TransformComponent.h"

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity(std::string friendlyName = "") : m_name(friendlyName){}
	virtual ~Entity();
	
	//----- Getters -----
	std::string getName() {return m_name;}
	
	bool operator==(Entity& entity)
	{
		return (m_name == entity.getName());
	}

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();
	
	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
	void DrawDebug();
	
protected:
	std::string m_name;
	std::vector<IComponent*> m_components;
};

#include <Entity.hxx>