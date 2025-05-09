#include "HumanCharacter.h"
#include "EntityManager.h"
#include "UIManager.h"

HumanCharacter::HumanCharacter(const sf::Vector2f& spawn, const EntityManager& EntityManagerRef) : Character(spawn), entityManager(EntityManagerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/Human.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Human");
		SetActive(true);
		SoundManager::PlayEnemySpawnSound();
		speed = 2.f;
		score = 500;
		randomDirection = entityManager.GetRandomDirection(-1.f, 1.f);
	}
}

void HumanCharacter::Awake()
{
}

void HumanCharacter::Update()
{
	if (IsActive())
	{
		randomMoveTimer += 0.1f;
		static float randomMoveRate = 10.f;
		if (randomMoveTimer > randomMoveRate)
		{
			randomDirection = entityManager.GetRandomDirection(-1.f, 1.f);
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

void HumanCharacter::OnCollision()
{
	Die();
	//TakeDamage(1);
}

void HumanCharacter::TakeDamage(int damage)
{
	Character::TakeDamage(damage);
}

//Techically Rescue
void HumanCharacter::Die()
{
	SoundManager::PlayHumanRescueSound();
	UIManager::AddScore(score);
	SetActive(false);
}