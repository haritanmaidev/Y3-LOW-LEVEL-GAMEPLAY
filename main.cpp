#include <math.h>
#include "EntityManager.h"
#include "SoundManager.h"
#include "UIManager.h"
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void DrawDebugLines(sf::RenderWindow& window, const sf::Sprite& sprite);

int main()
{
    InputHandler inputHandler;
	EntityManager entityManager;
	UIManager::InitScore("Fonts/GODOFWAR.ttf");
	SoundManager::PlayBackgroundMusic();

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "CODING GLADIATOR!");

    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    while (window.isOpen())
    {
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY - START]]]:||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
			//std::cout << "Time Since Last Physics Loop: " << timeSinceLastPhysicsLoop << std::endl;
            timeSinceLastPhysicsLoop -= physicsTimeStep;

            entityManager.UpdateAllEntities(window, inputHandler);
            entityManager.HumanSpawner(8.f);
            entityManager.EnemySpawner(4.f);
            entityManager.EnemyHulkSpawner(5.f);
            entityManager.RemoveEntityFromList();
			SoundManager::CleanUpSounds();
			UIManager::Update();
        }
        /*--------------------------------:||||[[[UPDATE FUNCTIONALITY - END]]]||||:--------------------------------*/
        
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

void DrawDebugLines(sf::RenderWindow& window, const sf::Sprite& sprite) {
    sf::IntRect textureRect = sprite.getTextureRect();

    sf::RectangleShape debugRect;
    debugRect.setSize(sf::Vector2f(static_cast<float>(textureRect.size.x), static_cast<float>(textureRect.size.y)));
    debugRect.setPosition(sprite.getPosition());
    debugRect.setOrigin(sprite.getOrigin());
    debugRect.setScale(sprite.getScale());
    debugRect.setOutlineColor(sf::Color::Red);
    debugRect.setOutlineThickness(1.0f);
    debugRect.setFillColor(sf::Color::Transparent);

    window.draw(debugRect);
}