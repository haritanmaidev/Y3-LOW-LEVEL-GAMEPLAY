#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	LoadGameObjectTexture("assets/walk.png");
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	sprite.setScale(sf::Vector2f(1.25f, 1.25f));
	SetActive(true);
}
