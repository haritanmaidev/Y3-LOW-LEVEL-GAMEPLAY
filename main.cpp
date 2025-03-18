#include <SFML/Graphics.hpp>
#include "Ellipse.h"
#include "InputHandler.h"

int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");
    
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
    const sf::Image packedSheetCharacters("assets/GokuSSJ3SpriteSheet.jpg");
    bool result = character.loadFromImage(packedSheetCharacters, false, sf::IntRect({ 0, 0 }, {65, 90}));

    sf::Sprite mainCharacter(character);
    sf::Sprite otherCharacter(character);
    otherCharacter.setPosition(sf::Vector2(100.0f, 100.0f));

    //PROJECTILE SPAWNING
    sf::Texture playerProjectile;
    const sf::Image projectile("assets/ProjectilesSpriteSheet1");
    bool resultProj = character.loadFromImage(projectile, false, sf::IntRect({ 50,50 }, { 100,100 }));
    
    sf::Sprite spawnedProjectile(playerProjectile);
    spawnedProjectile.setPosition(mainCharacter.getPosition());
    InputHandler::FireProjectile(spawnedProjectile);

    //TIME UPDATE

    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0;
    float timeSinceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 20000;

    while (window.isOpen())
    {
        //TIME UPDATE
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSinceLastPhysicsLoop += deltaTime;
        while(timeSinceLastPhysicsLoop > physicsTimeStep)
        {
            //Do physics
            mainCharacter.setPosition(mainCharacter.getPosition() + sf::Vector2f{ 1.f, 1.f });
            timeSinceLastPhysicsLoop -= physicsTimeStep;
            InputHandler::MoveCharacter(otherCharacter);
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
        window.draw(text);
        window.draw(mainCharacter);
        window.draw(otherCharacter);
        window.draw(spawnedProjectile);
        window.display();
    }
}
