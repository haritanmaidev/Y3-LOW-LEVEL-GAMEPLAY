#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Ellipse.h"
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void BorderCollisionCheck(sf::Sprite& mainCharacter);

int WinMain()
{
    InputHandler inputHandler;
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML works!");

    //Character
    sf::Texture character;
    const sf::Image LoadSprite("assets/walk.png");
    character.loadFromImage(LoadSprite, false, sf::IntRect({ 0, 0 }, {55, 55}));
    sf::Sprite mainCharacter(character);
    sf::Sprite playerCharacter(character);
    playerCharacter.setPosition(sf::Vector2f(100.0f, 100.0f));
    playerCharacter.setScale(sf::Vector2f(1.5f, 1.5f));

    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    //Projectiles
    std::vector<sf::CircleShape> bullets;

    //std::vector <managedObjects> objects;
    while (window.isOpen())
    {
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY]]]:||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //Do physics
            mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;

            inputHandler.MoveCharacter(playerCharacter);
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                inputHandler.isFiring = true;
            }
            else
            {
				inputHandler.isFiring = false;
			}

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
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY]]]:||||--------------------------------*/
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        if (inputHandler.isFiring == true)
        {
			sf::CircleShape newBullet(5.f);
			newBullet.setFillColor(sf::Color::Red);
			newBullet.setPosition(playerCharacter.getPosition());
			bullets.push_back(newBullet);
            inputHandler.isFiring = false;
        }

        for (auto& bullet : bullets)
        {
			bullet.move(inputHandler.lastDirection * 10.f);
			window.draw(bullet);
		}

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
