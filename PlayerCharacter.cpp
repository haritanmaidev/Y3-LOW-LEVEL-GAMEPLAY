#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter() : Character()
{
	drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if(LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setScale(sf::Vector2f(25.f, 25.f));
		sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(1.25f, 1.25f));
		SetActive(true);
		Awake();
	}
}

void PlayerCharacter::Awake()
{
}

void PlayerCharacter::Update()
{
}

void PlayerCharacter::OnCollision()
{
	std::cout << "Player collided!" << std::endl;
	SetActive(false);
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