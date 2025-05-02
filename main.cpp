#include <math.h>
#include "Ellipse.h"
#include "InputHandler.h"
#include "EntityManager.h"
#include "PlayerCharacter.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

void BorderCollisionCheck(sf::Sprite& mainCharacter);
sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player);
void DrawDebugLines(sf::RenderWindow& window, const sf::Sprite& sprite);

int main()
{
    InputHandler inputHandler;
	EntityManager entityManager;
    auto player = std::make_unique<PlayerCharacter>();
    //ASK: Comment this to make it work!
	entityManager.AddCharacter(std::move(player));
	//entityManager.SpawnPlayerCharacter(sf::Vector2f(100.f, 100.f));
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "CODING GLADIATOR!");
    //ASK: WHY DOESN'T THIS WORK???
	//PlayerCharacter Player = std::make_unique<PlayerCharacter>();

    //Characterd
    //sf::Texture character;
    //const sf::Image LoadSprite("assets/walk.png");
    //bool result = character.loadFromImage(LoadSprite, false, sf::IntRect({ 10, 10 }, {45, 45}));
    //sf::Sprite mainCharacter(character);

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
            //mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;

            inputHandler.MoveCharacter(*player);
            inputHandler.FireProjectile(entityManager, player->GetSprite().getPosition(), GetMouseDirection(window, *player), 10.f, deltaTime);
            entityManager.UpdateAllProjectiles();
            //entityManager.UpdateAllCharacters();

            BorderCollisionCheck(player->GetSprite());
            //BorderCollisionCheck(mainCharacter);

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
        //window.draw(mainCharacter);
        window.draw(player->GetSprite());
        //entityManager.RenderAllCharacters(window);
		entityManager.RenderAllProjectiles(window);
        DrawDebugLines(window, player->GetSprite());
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
        mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 1000 - mainCharacter.getGlobalBounds().size.y));
    }
}

sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player)
{
    //ASK: Is it better to keep this here or in InputHandler?
    //TO-DO: Use PlayerCharacter class instead of Sprite here!
    float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
                        sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

    return sf::Vector2f(cos(angle), sin(angle));
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