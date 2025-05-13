#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "UIManager.h"

EnemyCharacter::EnemyCharacter(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir) 
: Character(spawn), PlayerRef(player), travelDir(randomDir)
{
	//sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if (LoadGameObjectTextureFromFile("assets/Cropped/BasicEnemy.png", std::nullopt))
	{
		//sprite.setTextureRect(drawbox);
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Enemy");
		speed = 2.f;
		health = 2;
		MaxHealth = health;
		score = 100;
	}
}

void EnemyCharacter::Update()
{
	Character::Update();

	sf::Vector2f playerPosition = PlayerRef.GetPosition();
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f direction = playerPosition - position;
	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (mag < detectionRadius && mag != 0.f)
	{
		//Move towards Player
		direction /= mag;
		MoveCharacter(direction);
	}
	else
	{
		//Move towards random Direction
		MoveCharacter(velocity);
	}
}

void EnemyCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void EnemyCharacter::OnCollision(const std::string& tag)
{
	if (tag == "Player") 
	{
		TakeDamage(1, "Player");
	}
	else if (tag == "Projectile")
	{
		TakeDamage(1, "Projectile");
	}
}

void EnemyCharacter::TakeDamage(int damage, const std::string& damageBy)
{
	SoundManager::PlayEnemyHurtSound();
	Character::TakeDamage(damage, damageBy);
}

void EnemyCharacter::Die(const std::string& killedBy)
{
	SetPosition(-2000, 2000);

	if (killedBy == "Projectile") 
	{
		UIManager::AddScore(score);
	}
	else if (killedBy == "Player")
	{
		UIManager::SubtractScore(score);
	}

	SoundManager::PlayEnemyDeathSound();
	Character::Die(killedBy);
}
