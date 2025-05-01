#include "Character.h"

Character::Character() : GameObject()
{
	drawbox = sf::IntRect({ 0, 0 }, { 10045, 10045 });
	if(LoadGameObjectTextureFromFile("assets/errorcharacter.png", drawbox))
	{
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetActive(true);
	}
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