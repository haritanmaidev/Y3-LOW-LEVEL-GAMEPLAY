#pragma once
#include "Scene.h"
class GameOverScene :public Scene
{
public:
	//Constructor & Destructor
	GameOverScene();
	~GameOverScene() = default;

	//Override Functions
	void Init() override;
	void HandleInput(sf::RenderWindow& window) override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;

private:
	sf::Font font;
	sf::Text gameOverText = sf::Text(font);
	sf::Text restartText = sf::Text(font);
	sf::Text exitText = sf::Text(font);
	sf::Text scoreText = sf::Text(font);
};

