#pragma once
#include "Scene.h"

class EntityManager;
class InputHandler;
class WaveManager;

class GameScene : public Scene
{
public:
	GameScene(sf::RenderWindow& windowRef, InputHandler& inputRef, EntityManager& entityManRef, WaveManager& waveRef);
	~GameScene() = default;

	void HandleInput(sf::RenderWindow& window) override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;

private:
	sf::RenderWindow& window;
	InputHandler& inputHandler;
	EntityManager& entityManager;
	WaveManager& waveManager;
};

