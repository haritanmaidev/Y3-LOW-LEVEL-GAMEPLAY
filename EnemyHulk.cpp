#include "EnemyHulk.h"
#include "EntityManager.h"

EnemyHulk::EnemyHulk(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, const EntityManager& EntityManagerRef) 
: EnemyCharacter(spawn, player, randomDir), entityManager(EntityManagerRef)
{
	//sf::IntRect drawbox = sf::IntRect({ 2,2 }, { 40, 40 });
	if(LoadGameObjectTextureFromFile("assets/Cropped/EnemyHulk.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		SetScale(.15f, .15f);
		SetTag("EnemyHulk");
		speed = 1.f;
		health = 1000;
		randomDirection = entityManager.GetRandomVector(-1, 1);
	}
}

void EnemyHulk::Update() 
{
	Character::Update();

	randomMoveTimer += 0.1f;
	static float randomMoveRate = 25.f;
	if (randomMoveTimer > randomMoveRate)
	{
		randomDirection = entityManager.GetRandomVector(-3, 3);
		randomMoveTimer = 0.f;
	}
	else
	{
		MoveCharacter(randomDirection);
	}
}

void EnemyHulk::MoveCharacter(const sf::Vector2f& direction) 
{
	Character::MoveCharacter(direction);
}

void EnemyHulk::OnCollision(const std::string& tag)
{
	if(tag == "Player")
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

void::EnemyHulk::TakeDamage(int damage, const std::string& damageBy)
{
}

void EnemyHulk::Die(const std::string& killedBy)
{

}