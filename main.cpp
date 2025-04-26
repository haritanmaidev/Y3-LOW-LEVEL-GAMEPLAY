#include <SFML/Graphics.hpp>
#include <math.h>
#include "GameObject.h"
#include "InputHandler.h"
#include "Projectile.h"
#include "Ellipse.h"
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void BorderCollisionCheck(sf::Sprite& mainCharacter);
sf::Vector2f GetMouseDirection(sf::RenderWindow& window, sf::Sprite player);

int main()
{
    InputHandler inputHandler;
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML works!");

    //Character
    sf::Texture character;
    const sf::Image LoadSprite("assets/walk.png");
    bool result = character.loadFromImage(LoadSprite, false, sf::IntRect({ 0, 0 }, {50, 50}));
    sf::Sprite mainCharacter(character);
    sf::Sprite playerCharacter(character);
    playerCharacter.setPosition(sf::Vector2f(100.0f, 100.0f));
    playerCharacter.setScale(sf::Vector2f(1.5f, 1.5f));
    //Goku Character
    sf::Texture Goku;
	const sf::Image LoadGoku("assets/GokuSSJ3EditedSpriteSheet.png");
    //bool resultGoku = Goku.loadFromImage(LoadGoku, false, sf::IntRect({ 0,0 }, {0,0}));
	playerCharacter.setTexture(Goku);


    //Time Update
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;
   
    //Projectiles
    std::vector<std::pair<sf::CircleShape, sf::Vector2f>> bullets;
    std::vector<std::unique_ptr<Projectile>> projectileList;

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
            inputHandler.FireProjectile();
           
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
        /*--------------------------------||||:[[[UPDATE FUNCTIONALITY - END]]]:||||--------------------------------*/
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

		//OLD PROJECTILE CODE LOGIC: WORKING!
  //      if (inputHandler.isFiring == true)
  //      {
  //          sf::CircleShape newBullet(5.f);
  //          newBullet.setFillColor(sf::Color::Red);
  //          newBullet.setPosition(playerCharacter.getPosition());
  //          sf::Vector2f direction = GetMouseDirection(window, playerCharacter);
  //          bullets.push_back(std::make_pair(newBullet, direction));
  //          inputHandler.isFiring = false;
		//}

		//for (auto& bullet : bullets)
		//{
		//	bullet.first.move(bullet.second);
		//	window.draw(bullet.first);
		//}

        // NEW PROJECTILE CODE LOGIC:
        if (inputHandler.isFiring)
        {
            auto newProjectile = std::make_unique<Projectile>
            (window, playerCharacter.getPosition(), GetMouseDirection(window, playerCharacter), 3.f );
            newProjectile->SetActive(true);
            newProjectile->Awake();
            projectileList.push_back(std::move(newProjectile));
            inputHandler.isFiring = false; // Reset fire flag
        }

        for (auto& projectile : projectileList)
        {
            projectile->Update();
            projectile->Render(window);
			window.draw(projectile->GetSprite());
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

sf::Vector2f GetMouseDirection(sf::RenderWindow& window, sf::Sprite player)
{
    //ASK: Is it better to keep this here or in InputHandler?
    //TO-DO: Use PlayerCharacter class instead of Sprite here!
    float angle = atan2(sf::Mouse::getPosition(window).y - player.getPosition().y,
                        sf::Mouse::getPosition(window).x - player.getPosition().x);
    return sf::Vector2f(cos(angle), sin(angle));
}