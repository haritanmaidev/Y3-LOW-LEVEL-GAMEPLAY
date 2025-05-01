#include "Character.h"

Character::Character() : GameObject()
{
	LoadGameObjectTextureFromFile("assets/errorcharacter.png", drawbox);
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