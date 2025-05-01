#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	LoadGameObjectTexture("assets/walk.png");
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	sprite.setScale(sf::Vector2f(1.25f, 1.25f));
	SetActive(true);
}

void PlayerCharacter::TakeDamage(int& damage)
{
	health -= damage;
	if (health <= 0) Die();
}

void PlayerCharacter::Move(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void PlayerCharacter::Die()
{
	SetActive(false);
	std::cout << "Player is dead!" << std::endl;
}