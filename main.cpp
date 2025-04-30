#include <math.h>
#include "Ellipse.h"
#include "InputHandler.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void BorderCollisionCheck(sf::Sprite& mainCharacter);
sf::Vector2f GetMouseDirection(sf::RenderWindow& window, sf::Sprite player);

int main()
{
    InputHandler inputHandler;
	EntityManager entityManager;
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML works!");

    //Character
    sf::Texture character;
    const sf::Image LoadSprite("assets/walk.png");
    bool result = character.loadFromImage(LoadSprite, false, sf::IntRect({ 0, 0 }, {50, 50}));
    sf::Sprite mainCharacter(character);
    sf::Sprite playerCharacter(character);
    playerCharacter.setPosition(sf::Vector2f(100.0f, 100.0f));
    playerCharacter.setScale(sf::Vector2f(1.5f, 1.5f));

    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    //std::vector <managedObjects> objects;
    while (window.isOpen())
    {
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY - START]]]:||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //Do physics
            mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;

            inputHandler.MoveCharacter(playerCharacter);
            inputHandler.FireProjectile(entityManager, playerCharacter.getPosition(), GetMouseDirection(window, playerCharacter), 10.f);
            entityManager.UpdateAllProjectiles();

            BorderCollisionCheck(playerCharacter);
            BorderCollisionCheck(mainCharacter);

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

        //[[[DRAWING ON WINDOW]]]||||:--------------------------------------------------------------------------
        window.clear();
		entityManager.RenderAllProjectiles(window);
        window.draw(mainCharacter);
        window.draw(playerCharacter);
        window.display();
    }
}

void BorderCollisionCheck(sf::Sprite &mainCharacter)
{
    //Right Collision
    if (mainCharacter.getPosition().x < 0)
    {
        mainCharacter.setPosition(sf::Vector2f(0, mainCharacter.getPosition().y));
    }
    //Left Collision
    if (mainCharacter.getPosition().x + mainCharacter.getGlobalBounds().size.x > 1000)
    {
        mainCharacter.setPosition(sf::Vector2f(1000 - mainCharacter.getGlobalBounds().size.x, mainCharacter.getPosition().y));
    }
    //Top Collision
    if (mainCharacter.getPosition().y < 0)
    {
        mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 0));
    }
    //Bottom Collision
    if (mainCharacter.getPosition().y + mainCharacter.getGlobalBounds().size.y > 1000)
    {
        mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 1000 -mainCharacter.getGlobalBounds().size.y));
    }
}

sf::Vector2f GetMouseDirection(sf::RenderWindow& window, sf::Sprite player)
{
    //ASK: Is it better to keep this here or in InputHandler?
    //TO-DO: Use PlayerCharacter class instead of Sprite here!
    float angle = atan2(sf::Mouse::getPosition(window).y - player.getPosition().y,
                        sf::Mouse::getPosition(window).x - player.getPosition().x);

    return sf::Vector2f(cos(angle), sin(angle));
}