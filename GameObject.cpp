#include "GameObject.h"

GameObject::GameObject()
{
    if (!texture.loadFromFile("assets/Cropped/BasicProjectile.png"))
    {
        std::cout << "Texture didn't load! Assigning placeholder texture." << std::endl;
    }
    else
    {
        //std::cout << "Texture set successfully!" << std::endl;
        sprite.setTexture(texture);
    }

    // Assign the texture to the sprite after ensuring it is valid
}