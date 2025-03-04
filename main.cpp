#include <SFML/Graphics.hpp>

/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Font font("Arial.ttf"); // Throws sf::Exception if an error occurs
    sf::Text text(font); // a font is required to make a text object
    text.setString("Scunthorpe Problem!");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen())
    {
        // Event polling section of code - this must be done in the thread which created the window
        // we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }
}