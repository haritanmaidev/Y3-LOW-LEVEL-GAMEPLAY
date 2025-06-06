#include "HumanCharacter.h"
#include "EntityManager.h"
#include "UIManager.h"

HumanCharacter::HumanCharacter(const sf::Vector2f& spawn, const PlayerCharacter& playerRef, EntityManager& EntityManagerRef)
: Character(spawn), entityManager(EntityManagerRef), player(playerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/Human.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.30f, .30f));
		SetTag("Human");
		score = 500;
		speed = 2.f;
		health = 1;
		randomDirection = entityManager.GetRandomVector(-1.f, 1.f);
	}
}

void HumanCharacter::Update()
{
	if (!isCorrupt)
	{
		randomMoveTimer += 0.1f;
		static float randomMoveRate = 15.f;
		if (randomMoveTimer > randomMoveRate)
		{
			velocity = entityManager.GetRandomVector(-1.f, 1.f);
			randomMoveTimer = 0.f;
		}
		else 
		{
			MoveCharacter(velocity);
		}
	}
	else 
	{
		sf::Vector2f playerPos = player.GetPositionConst();
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f direction = playerPos - position;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;

		Character::MoveCharacter(direction);
	}
}

void HumanCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void HumanCharacter::OnCollision(const std::string& tag)
{
	if (tag == "Player")
	{
		TakeDamage(1, "Player");
	}
	else if (tag == "Enemy") 
	{
		speed = 1.f;
		return;
	}
	else if (tag == "EnemyHulk")
	{
		TakeDamage(1, "EnemyHulk");
	}
	else if (tag == "EnemyBrain") 
	{
		isCorrupt = true;
		SetTag("HumanCorrupted");
		sprite.setColor(sf::Color::Red);
	}
	else if (tag == "Projectile" && isCorrupt) 
	{
		TakeDamage(1, "Projectile");
	}
	
	speed = 2.f;
}

void HumanCharacter::TakeDamage(int damage, const std::string& damageBy)
{
	Character::TakeDamage(damage, damageBy);
}

void HumanCharacter::Die(const std::string& killedBy)
{
	//SoundManager::PlayHumanHurtSound();
	if (killedBy == "EnemyHulk") 
	{
		SoundManager::PlayPlayerHurtSound();
		UIManager::SubtractScore(score);
	}
	else if(killedBy == "Player")
	{
		if (!isCorrupt)
		{
			//Rescue Family
			UIManager::AddScore(score);
			SoundManager::PlayHumanRescueSound();
		}
		else
		{
			UIManager::SubtractScore(score);
			SoundManager::PlayEnemyDeathSound();
		}
	}
	else if (killedBy == "Projectile" && isCorrupt) 
	{
		UIManager::AddScore(score);
		SoundManager::PlayEnemyDeathSound();
	}

	Character::Die(killedBy);
}