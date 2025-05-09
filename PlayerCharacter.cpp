#include "PlayerCharacter.h"
#include "UIManager.h"

PlayerCharacter::PlayerCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if(LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(1.25f, 1.25f));
		SetTag("Player");
	}
}

void PlayerCharacter::Awake()
{
}

void PlayerCharacter::Update()
{
	Character::Update();
}

void PlayerCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void PlayerCharacter::OnCollision()
{
	SoundManager::PlayPlayerHurtSound();
	UIManager::SubtractScore(100);
	TakeDamage(1);
}

void PlayerCharacter::TakeDamage(int damage)
{
	Character::TakeDamage(damage);
}

void PlayerCharacter::Die()
{
	SetActive(false);
}