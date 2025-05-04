#include "EnemyCharacter.h"
#include "PlayerCharacter.h"


EnemyCharacter::EnemyCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	//sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if (LoadGameObjectTextureFromFile("assets/Cropped/BasicEnemy.png", std::nullopt))
	{
		//sprite.setTextureRect(drawbox);
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(1.f, 1.f));
		SetActive(true);
	}
}

void EnemyCharacter::Awake()
{

}

void EnemyCharacter::Update()
{
	//std::cout << "Enemy Update is called!" << std::endl;
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
