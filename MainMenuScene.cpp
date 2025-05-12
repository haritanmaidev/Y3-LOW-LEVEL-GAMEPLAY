#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
    if (font.openFromFile("Fonts/GODOFWAR.ttf")) 
    {
        titleText.setFont(font);
        titleText.setString("ROBOTRON: 2025");
        titleText.setCharacterSize(50);
        titleText.setPosition(sf::Vector2f(200.f, 200.f));

        startText.setFont(font);
        startText.setString("Press [ENTER] to Start");
        startText.setCharacterSize(30);
        startText.setPosition(sf::Vector2f(250.f, 300.f));

        exitText.setFont(font);
        exitText.setString("Press [ESC] to Quit");
        exitText.setCharacterSize(30);
        exitText.setPosition(sf::Vector2f(250.f, 350.f));
    }
}

void MainMenuScene::HandleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        isFinished = true;
        nextScene = "GameScene";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        window.close();
    }
}

void MainMenuScene::Update()
{
	// No update logic needed for the main menu
}

void MainMenuScene::Render(sf::RenderWindow& window)
{
	window.draw(titleText);
	window.draw(startText);
	window.draw(exitText);
}
