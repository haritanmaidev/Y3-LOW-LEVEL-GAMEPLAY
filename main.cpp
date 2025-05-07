#include <math.h>
#include "Ellipse.h"
#include "InputHandler.h"
#include "EntityManager.h"
#include "PlayerCharacter.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void DrawDebugLines(sf::RenderWindow& window, const sf::Sprite& sprite);

int main()
{
    InputHandler inputHandler;
	EntityManager entityManager;
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
            //Do physics
            timeSinceLastPhysicsLoop -= physicsTimeStep;

            entityManager.UpdateAllProjectiles();
            entityManager.UpdateAllEntities();
            entityManager.UpdateAllCharacters(window, inputHandler);
            entityManager.EnemySpawner();
            //entityManager.ProjectileToEnemyCollisionCheck();

            /*for (int i = 0; i < objects.size(); i++)
            {
                for (int j = i + 1; j < objects.size(); j++)
                {
                    checkCollision(object[i], object[j]);
                }
            }*/
        }
        /*--------------------------------:||||[[[UPDATE FUNCTIONALITY - END]]]||||:--------------------------------*/
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //-------------------------------------:||||[[[[DRAWING ON WINDOW]]]||||:-------------------------------------
        window.clear();
		entityManager.RenderAllProjectiles(window);
        entityManager.RenderAllCharacters(window);
		//entityManager.RenderAllGameObjects(window);
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