#include "Character.h"

Character::Character() 
{
	LoadGameObjectTexture("assets/errorcharacter.png");
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	sprite.setScale(sf::Vector2f(1.25f, 1.25f));
	SetActive(true);
}

void Character::OnCollision()
{
	std::cout << "Character collided!" << std::endl;
	SetActive(false);
}

void Character::TakeDamage(int& damage)
{
	health -= damage;
	if (health <= 0) Die();
}

void Character::Move(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void Character::Die()
{
	SetActive(false);
	std::cout << "Character is dead!" << std::endl;
}