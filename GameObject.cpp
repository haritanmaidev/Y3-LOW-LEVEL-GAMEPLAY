#include "GameObject.h"

GameObject::GameObject()
{
    if(LoadGameObjectTextureFromFile("assets/error.png", drawbox))
    {
        sprite.setScale(sf::Vector2f(.25f, .25f));
        sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    }
}