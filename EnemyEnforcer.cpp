#include "EnemyEnforcer.h"
#include "EntityManager.h"

EnemyEnforcer::EnemyEnforcer(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef)
: EnemyCharacter(spawn, player, randomDir), PlayerRef(player), entityManager(EntityManagerRef)
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
	randomMoveTimer += 0.1f;
	sf::Vector2f playerPosition = PlayerRef.GetPosition();
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f direction = playerPosition - position;
	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (mag < detectionRadius && mag != 0.f)
	{
		//Move towards Player
		direction /= mag;
		MoveCharacter(direction);
		FireMine(direction);
	}
	else
	{
		//Move towards random Direction
		MoveCharacter(velocity);
		std::cout << "EnemyCharacter Velocity: " << velocity.x << ", " << velocity.y << std::endl;
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

void EnemyEnforcer::FireMine(const sf::Vector2f& dir)
{
	fireTimer += 0.1f;
	if (fireTimer > fireRate)
	{
		//REFACTOR: USE HOMING MISSLE
		entityManager.SpawnProjectile(sprite.getPosition(), dir, 8.f);
		fireTimer = 0.f;
	}
}