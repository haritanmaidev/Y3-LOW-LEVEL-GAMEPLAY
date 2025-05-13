#include "HumanCharacter.h"
#include "EntityManager.h"
#include "UIManager.h"

HumanCharacter::HumanCharacter(const sf::Vector2f& spawn, const EntityManager& EntityManagerRef) 
: Character(spawn), entityManager(EntityManagerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/Human.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Human");
		speed = 2.f;
		score = 500;
		health = 1;
		randomDirection = entityManager.GetRandomVector(-1.f, 1.f);
	}
}

void HumanCharacter::Update()
{
	if (IsActive())
	{
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
		SoundManager::PlayHumanRescueSound();
		UIManager::AddScore(score);
	}

	Character::Die(killedBy);
}