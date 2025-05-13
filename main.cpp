#include <math.h>
#include "EntityManager.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "WaveManager.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "CODING GLADIATOR");
	UIManager::Init("Fonts/GODOFWAR.ttf");
    //SoundManager::PlayBackgroundMenuMusic();

    //Game Systems
    InputHandler inputHandler;
	EntityManager entityManager;
	WaveManager waveManager(entityManager, UIManager::GetWaveDelayTime());

    //Scene Management
    SceneManager sceneManager;
    sceneManager.AddScene("MainMenu", std::make_unique<MainMenuScene>());
    sceneManager.AddScene("Game", std::make_unique<GameScene>(window, inputHandler, entityManager, waveManager));
	sceneManager.AddScene("GameOver", std::make_unique<GameOverScene>());
    sceneManager.SwitchTo("MainMenu");

    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
  
    while (window.isOpen())
    {
        /*--------------------------------||||:[[[FIXED UPDATE FUNCTIONALITY]]]:||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //DO UPDATE HERE!
            timeSinceLastPhysicsLoop -= physicsTimeStep;
			sceneManager.HandleInput(window);
			sceneManager.Update();
        }
        /*--------------------------------:||||[[[FIXED UPDATE FUNCTIONALITY]]]||||:--------------------------------*/
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
		sceneManager.Render(window);
        window.display();
    }
}