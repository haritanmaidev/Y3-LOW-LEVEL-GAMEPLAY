#include "GameOverScene.h"
#include "UIManager.h"

GameOverScene::GameOverScene() 
{
	if (font.openFromFile("Fonts/GODOFWAR.ttf"))
	{
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(85);
		gameOverText.setPosition(sf::Vector2f(500.f, 70.f));
		gameOverText.setOrigin(sf::Vector2f(gameOverText.getGlobalBounds().size.x / 2.f, gameOverText.getGlobalBounds().size.y / 2.f));
		
		restartText.setFont(font);
		restartText.setString("Press [R] to Restart");
		restartText.setCharacterSize(30);
		restartText.setPosition(sf::Vector2f(500.f, 590.f));
		restartText.setOrigin(sf::Vector2f(restartText.getGlobalBounds().size.x / 2.f, restartText.getGlobalBounds().size.y / 2.f));
		
		exitText.setFont(font);
		exitText.setString("Press [ESC] to Quit");
		exitText.setCharacterSize(30);
		exitText.setPosition(sf::Vector2f(500.f, 650.f));
		exitText.setOrigin(sf::Vector2f(exitText.getGlobalBounds().size.x / 2.f, exitText.getGlobalBounds().size.y / 2.f));
	}
}

void GameOverScene::Init()
{
	isFinished = false;

}

void GameOverScene::HandleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		isFinished = true;
		nextScene = "Game";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window.close();
	}
}

void GameOverScene::Update()
{
	UIManager::FlashText(gameOverText);
	UIManager::FlashText(restartText);
	UIManager::FlashText(exitText);
}

void GameOverScene::Render(sf::RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(restartText);
	window.draw(exitText);
}