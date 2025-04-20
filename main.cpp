#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Ellipse.h"

void BorderCollisionCheck(sf::Sprite& mainCharacter);

int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");
    InputHandler inputHandler;
    
    //SHAPES SECTION
    //Circle
    sf::CircleShape shape(70.F);
    sf::Vector2f shapePosition(100, 100);
    shape.setPosition(shapePosition);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(-10.0f);
    shape.setOutlineColor(sf::Color::White);

    //Ellipse
    EllipseShape shapeEllipse;
    shapeEllipse.setRadius(sf::Vector2f(50, 10));
    shapeEllipse.setPosition(sf::Vector2f(300, 300));
    shapeEllipse.setFillColor(sf::Color::Blue);
    shapeEllipse.setOutlineThickness(-2.0f);
    shapeEllipse.setOutlineColor(sf::Color::White);

    //TEXT SECTION
    sf::Font font("Arial.ttf"); // Throws sf::Exception if an error occurs
    sf::Text text(font); // a font is required to make a text object
    text.setString("CALLING ALL AUTOBOTS!");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    //Character
    sf::Texture character;
    const sf::Image LoadGoku("assets/walk.png");
    character.loadFromImage(LoadGoku, false, sf::IntRect({ 0, 0 }, {65, 80}));
    sf::Sprite mainCharacter(character);
    sf::Sprite otherCharacter(character);
    otherCharacter.setPosition(sf::Vector2f(100.0f, 100.0f));
    otherCharacter.setScale(sf::Vector2f(1.5f, 1.5f));

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
        /*--------------------------------|||| [[[UPDATE]] ] ||||--------------------------------*/
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //Do physics
            mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;
            inputHandler.MoveCharacter(otherCharacter);

            BorderCollisionCheck(otherCharacter);
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
        window.draw(shapeEllipse);
        //window.draw(text);
        window.draw(mainCharacter);
        window.draw(otherCharacter);
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
    if (mainCharacter.getPosition().x + mainCharacter.getGlobalBounds().size.x > 400)//window.getSize().x)
    {
        mainCharacter.setPosition(sf::Vector2f(400 - mainCharacter.getGlobalBounds().size.x, mainCharacter.getPosition().y));
    }
    //Top Collision
    if (mainCharacter.getPosition().y < 0)
    {
        mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 0));
    }
    //Bottom Collision
    if (mainCharacter.getPosition().y + mainCharacter.getGlobalBounds().size.y > 400)
    {
        mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 400-mainCharacter.getGlobalBounds().size.y));
    }
}
