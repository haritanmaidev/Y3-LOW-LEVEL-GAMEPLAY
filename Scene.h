#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	Scene();
	~Scene() = default;

	//Overridable Functions
	virtual void SetBackground();

	//Pure Functions
	virtual void Init() = 0;
	virtual void HandleInput(sf::RenderWindow& window) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& window);

	//Class Functions
	bool IsFinished() const { return isFinished; }
	std::string GetNextScene() const { return nextScene; }

protected:
	bool isFinished = false;
	std::string nextScene = "";
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite = sf::Sprite(backgroundTexture);
};

