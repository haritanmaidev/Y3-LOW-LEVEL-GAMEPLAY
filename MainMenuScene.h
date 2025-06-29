#pragma once
#include "Scene.h"

class MainMenuScene : public Scene
{
public:
	//Constructor & Destructor
    MainMenuScene();
	~MainMenuScene() = default;

    //Override Functions
	void Init() override;
    void HandleInput(sf::RenderWindow& window) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;


private:
    sf::Font font;
	sf::Text titleText = sf::Text(font);
	sf::Text startText = sf::Text(font);
	sf::Text exitText = sf::Text(font);
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite = sf::Sprite(backgroundTexture);
};

