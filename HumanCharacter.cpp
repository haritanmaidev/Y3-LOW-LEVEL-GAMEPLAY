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
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Human");
		score = 500;
		speed = 2.f;
		health = 1;
		randomDirection = entityManager.GetRandomVector(-1.f, 1.f);
	}
}

void HumanCharacter::Update()
{
	//SpriteFlash();

	if (!isCorrupt)
	{
		std::cout << "isnt corrupted" << std::endl;
		randomMoveTimer += 0.1f;
		static float randomMoveRate = 10.f;
		if (randomMoveTimer > randomMoveRate)
		{
			randomDirection = entityManager.GetRandomVector(-1.f, 1.f);
			MoveCharacter(randomDirection);
			randomMoveTimer = 0.f;
		}
		else 
		{
			MoveCharacter(randomDirection);
		}
	}
	else 
	{
		std::cout << "is corrupted" << std::endl;

		sf::Vector2f playerPos = player.GetPositionConst();
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f direction = playerPos - position;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;

		Character::MoveCharacter(direction);
		//MoveCharacter();

		//MoveCharacter(direction);
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
}

void HumanCharacter::TakeDamage(int damage, const std::string& damageBy)
{
	Character::TakeDamage(damage, damageBy);
}

//Techically Rescue
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