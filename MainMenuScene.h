#pragma once
#include "Scene.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene();
	~MainMenuScene() = default;

    void HandleInput(sf::RenderWindow& window) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;


private:
    sf::Font font;
	sf::Text titleText = sf::Text(font);
	sf::Text startText = sf::Text(font);
	sf::Text exitText = sf::Text(font);
};

