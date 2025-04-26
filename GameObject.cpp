#include "GameObject.h"

GameObject::GameObject()
{
    if (!texture.loadFromFile("assets/Cropped/BasicProjectile.png"))
    {
        std::cout << "Texture didn't load!" << std::endl;
        texture.loadFromFile("assets/GokuSSJ3EditedSpriteSheet.png");
    }
    else
    {
        std::cout << "Texture set successfully!" << std::endl;
    }

    sprite.setTexture(texture);
}