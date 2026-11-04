#pragma once

#include <functional>
#include <string>
#include <SFML/Window/Keyboard.hpp>

class InputAction
{
public:
	struct sCallbackInfo
	{
		std::string DebugName;
		std::function<void(float)> Callback;
		void* Owner = nullptr;
	};
	
	InputAction() = default;
	InputAction(const std::string& name);
	void SetActionName(const std::string& name);
	void SetValue(float value);
	void RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner);
	void UnregisterCallbacks(void* owner);
	void RunCallbacks();
	
	void AddKey(sf::Keyboard::Key key);
	//void RemoveKey(sf::Keyboard::Key key);
	
	std::size_t GetHash() const { return ActionNameHash; }
	std::vector<sf::Keyboard::Key> GetKeys() const { return Keys; }
	float GetValue() const { return Value; }
	std::string GetActionName() const { return ActionName; }
	std::vector<sCallbackInfo> GetCallbacks() const { return Callbacks; }

private:
	

	std::string ActionName;
	std::size_t ActionNameHash;
	float Value = 0.f;
	std::vector<sCallbackInfo> Callbacks;
	std::vector<sf::Keyboard::Key> Keys;
};
