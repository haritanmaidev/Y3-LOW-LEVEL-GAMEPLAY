#include "Scene.h"

Scene::Scene() 
{
	SetBackground();
}

void Scene::SetBackground()
{
	if (backgroundTexture.loadFromFile("assets/backgroundgrass.png"))
	{
		backgroundSprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(backgroundTexture.getSize())));
		backgroundSprite.setOrigin(sf::Vector2f(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f));
		backgroundSprite.setPosition(sf::Vector2f(500.f, 500.f));
		backgroundSprite.setScale(sf::Vector2f(1.65f, 1.65f));
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setColor(sf::Color(255, 255, 255, 100)); //Semi-transparent background
	}
}

void Scene::Render(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
}