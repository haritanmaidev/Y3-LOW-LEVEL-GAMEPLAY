#include "EnemyHulk.h"
#include "EntityManager.h"

EnemyHulk::EnemyHulk(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, const EntityManager& EntityManagerRef) 
: EnemyCharacter(spawn, player, randomDir), entityManager(EntityManagerRef)
{
	sf::IntRect drawbox = sf::IntRect({ 2,2 }, { 40, 40 });
	if(LoadGameObjectTextureFromFile("assets/Cropped/EnemyHulk.png", drawbox))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		SetTag("EnemyHulk");
		SoundManager::PlayEnemySpawnSound();
		speed = 5.f;
		health = 1000;
	}
}

void EnemyHulk::Update() 
{

}

void EnemyHulk::MoveCharacter(const sf::Vector2f& direction) 
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

void EnemyHulk::OnCollision() 
{
	SoundManager::PlayEnemyHurtSound();
}

void::EnemyHulk::TakeDamage(int damage)
{

}

void EnemyHulk::Die() 
{

}