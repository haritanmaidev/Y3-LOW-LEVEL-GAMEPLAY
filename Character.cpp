#include "Character.h"

Character::Character(const sf::Vector2f& spawn) : GameObject(), spawnPoint(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 0 , 0 }, { 0 , 0 });
	LoadGameObjectTextureFromFile("assets/errorcharacter.png", drawbox);
	sprite.setPosition(spawnPoint);
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