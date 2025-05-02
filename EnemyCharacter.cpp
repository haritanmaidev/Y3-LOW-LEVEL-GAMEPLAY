#include "EnemyCharacter.h"


EnemyCharacter::EnemyCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 200, 200 }, { 220, 230 });
	if (LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setScale(sf::Vector2f(5.f, 5.f));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		SetActive(true);
	}
}

void EnemyCharacter::Awake()
{

}

void EnemyCharacter::Update()
{
	std::cout << "Player Update is called!" << std::endl;
}

void EnemyCharacter::OnCollision()
{
	std::cout << "Player collided!" << std::endl;
	SetActive(false);
}

void EnemyCharacter::TakeDamage(int& damage)
{
	Character::TakeDamage(damage);
}


void EnemyCharacter::Move(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void EnemyCharacter::Die()
{
	SetActive(false);
	std::cout << "Player is dead!" << std::endl;
}
