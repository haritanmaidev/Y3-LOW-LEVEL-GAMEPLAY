#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void HandleInput(sf::RenderWindow& window) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual bool IsFinsihed() const { return false; }
	virtual std::string NextScene() const { return ""; }
};

