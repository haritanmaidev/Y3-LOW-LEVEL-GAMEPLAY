#include "PlayerCharacter.h"
#include "UIManager.h"

PlayerCharacter::PlayerCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if(LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(2.25f, 2.25f));
		SetTag("Player");
		health = 100;
	}
}

void PlayerCharacter::Update()
{
	Character::Update();
}

void PlayerCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void PlayerCharacter::OnCollision(const std::string& tag)
{
	if (tag == "Enemy")
	{
		TakeDamage(1);
	}
	else if (tag == "EnemyHulk")
	{
		TakeDamage(1);
	}
}

void PlayerCharacter::TakeDamage(int damage)
{
	Character::TakeDamage(damage);
	SoundManager::PlayPlayerHurtSound();
}

void PlayerCharacter::Die()
{
	UIManager::SubtractScore(1000);
	//SoundManager::PlayPlayerDeathSound();
	Character::Die();
}