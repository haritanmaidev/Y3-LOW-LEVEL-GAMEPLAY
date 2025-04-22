#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Ellipse.h"

void BorderCollisionCheck(sf::Sprite& mainCharacter);

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML works!");
    InputHandler inputHandler;
    
    //Circle
    sf::CircleShape shape(70.F);
    sf::Vector2f shapePosition(100, 100);
    shape.setPosition(shapePosition);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(-10.0f);
    shape.setOutlineColor(sf::Color::White);

    //Character
    sf::Texture character;
    const sf::Image LoadGoku("assets/walk.png");
    character.loadFromImage(LoadGoku, false, sf::IntRect({ 0, 0 }, {55, 55}));
    sf::Sprite mainCharacter(character);
    sf::Sprite playerCharacter(character);
    playerCharacter.setPosition(sf::Vector2f(100.0f, 100.0f));
    playerCharacter.setScale(sf::Vector2f(1.5f, 1.5f));

    //PROJECTILE SPAWNING
    sf::Texture playerProjectile;
    const sf::Image projectile("assets/ProjectilesSpriteSheet1.gif");
    playerProjectile.loadFromImage(projectile, false, sf::IntRect({ 50,50 }, { 100,100 }));
    sf::Sprite spawnedProjectile(playerProjectile);
    spawnedProjectile.setScale(sf::Vector2f(0.5f, 0.5f));
    spawnedProjectile.setPosition(mainCharacter.getPosition());

    //TIME UPDATE
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    //std::vector <managedObjects> objects;
    while (window.isOpen())
    {
        /*--------------------------------|||| [[[UPDATE]]] ||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //Do physics
            mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;
            inputHandler.MoveCharacter(playerCharacter);

            BorderCollisionCheck(playerCharacter);
            BorderCollisionCheck(mainCharacter);
            inputHandler.FireProjectile(spawnedProjectile);
            /*for (int i = 0; i < objects.size(); i++)
            {
                for (int j = i + 1; j < objects.size(); j++)
                {
                    checkCollision(object[i], object[j]);
                }
            }*/
        }

        // Event polling section of code - this must be done in the thread which created the window, we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(mainCharacter);
        window.draw(playerCharacter);
        window.draw(spawnedProjectile);
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
