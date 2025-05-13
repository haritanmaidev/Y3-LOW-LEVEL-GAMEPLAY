#include "EnemyEnforcer.h"
#include "EntityManager.h"

EnemyEnforcer::EnemyEnforcer(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef)
: EnemyCharacter(spawn, player, randomDir), entityManager(EntityManagerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/EnemyEnforcer.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("EnemyEnforcer");
		speed = 1.f;
		health = 5;
		MaxHealth = health;
		score = 100;
		randomDirection = entityManager.GetRandomVector(1,-1);
	}
}

void EnemyEnforcer::Update()
{
	if (IsActive())
	{
		randomMoveTimer += 0.1f;
		if (randomMoveTimer > randomMoveRate)
		{
			randomDirection = entityManager.GetRandomVector(-3, 3);
			MoveCharacter(randomDirection);
			randomMoveTimer = 0.f;
		}
		else
		{
			MoveCharacter(randomDirection);
		}
	}
}

void EnemyEnforcer::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void EnemyEnforcer::OnCollision(const std::string& tag)
{
	if (tag == "Player")
	{
		SoundManager::PlayEnemyHitSound();
	}
	else if (tag == "Projectile")
	{
		SoundManager::PlayEnemyHitSound();
	}
	else if (tag == "Human")
	{
		SoundManager::PlayEnemyHitSound();
	}
}

void::EnemyEnforcer::TakeDamage(int damage, const std::string& damageBy)
{
}

void EnemyEnforcer::Die(const std::string& killedBy)
{

}

void EnemyEnforcer::FireMine() 
{
	//REFACTOR: USE HOMING MISSLE
	entityManager.SpawnProjectile(sprite.getPosition(), entityManager.GetRandomVector(1, -1), 20.f);
}