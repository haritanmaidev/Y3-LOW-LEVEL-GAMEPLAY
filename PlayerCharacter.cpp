#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if(LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(1.25f, 1.25f));
		SetTag("Player");
		SetActive(true);
	}
}

void PlayerCharacter::Awake()
{
}

void PlayerCharacter::Update()
{
	std::cout << "Player Update is called!" << std::endl;
}

void PlayerCharacter::OnCollision()
{
	std::cout << "Player collided!" << std::endl;

	SetActive(false);
}

void PlayerCharacter::TakeDamage(int& damage)
{
	Character::TakeDamage(damage);
}

void PlayerCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void PlayerCharacter::Die()
{
	SetActive(false);
	std::cout << "Player is dead!" << std::endl;
}