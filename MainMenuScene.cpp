#include "MainMenuScene.h"
#include "UIManager.h"

MainMenuScene::MainMenuScene()
{
    if (font.openFromFile("Fonts/GODOFWAR.ttf")) 
    {
        titleText.setFont(font);
        titleText.setString("ROBOTRON: 2025");
        titleText.setCharacterSize(85);
        titleText.setPosition(sf::Vector2f(500.f, 70.f));
		titleText.setOrigin(sf::Vector2f(titleText.getGlobalBounds().size.x / 2.f, titleText.getGlobalBounds().size.y / 2.f));

        startText.setFont(font);
        startText.setString("Press [ENTER] to Start");
        startText.setCharacterSize(50);
        startText.setPosition(sf::Vector2f(500.f, 590.f));
		startText.setOrigin(sf::Vector2f(startText.getGlobalBounds().size.x / 2.f, startText.getGlobalBounds().size.y / 2.f));
       
        exitText.setFont(font);
        exitText.setString("Press [ESC] to Quit");
        exitText.setCharacterSize(50);
        exitText.setPosition(sf::Vector2f(500.f, 650.f));
		exitText.setOrigin(sf::Vector2f(exitText.getGlobalBounds().size.x / 2.f, exitText.getGlobalBounds().size.y / 2.f));
    }
}

void MainMenuScene::Init()
{
	isFinished = false;
}

void MainMenuScene::HandleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        isFinished = true;
        nextScene = "Game";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        window.close();
    }
}

void MainMenuScene::Update()
{
	UIManager::FlashText(titleText);
    UIManager::FlashText(startText);
    UIManager::FlashText(exitText);

}

void MainMenuScene::Render(sf::RenderWindow& window)
{
	window.draw(titleText);
	window.draw(startText);
	window.draw(exitText);
}
