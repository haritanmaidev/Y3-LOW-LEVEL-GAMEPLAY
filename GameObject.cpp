#include "GameObject.h"

GameObject::GameObject()
{
    //sf::IntRect drawbox = sf::IntRect({ 0, 0 }, { 0, 0 });
    LoadGameObjectTextureFromFile("assets/error.png", std::nullopt);
}