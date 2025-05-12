#include <math.h>
#include "EntityManager.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "WaveManager.h"
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

int main()
{
    InputHandler inputHandler;
	EntityManager entityManager;
	WaveManager waveManager(entityManager, UIManager::GetWaveDelayTime());
	UIManager::Init("Fonts/GODOFWAR.ttf");
	SoundManager::PlayBackgroundMusic();

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "CODING GLADIATOR!");

    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    while (window.isOpen())
    {
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY]]]:||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //DO UPDATE HERE!
			//std::cout << "Time Since Last Physics Loop: " << timeSinceLastPhysicsLoop << std::endl;
            timeSinceLastPhysicsLoop -= physicsTimeStep;

			entityManager.GameObjectListCollisionCheck();
            entityManager.UpdateAllEntities(window, inputHandler);
            entityManager.RemoveEntityFromList();
			waveManager.Update();
			SoundManager::CleanUpSounds();
			UIManager::Update();

        }
        /*--------------------------------:||||[[[UPDATE FUNCTIONALITY]]]||||:--------------------------------*/
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
		UIManager::RenderUI(window);
		entityManager.RenderAllGameObjects(window);
        window.display();
    }
}