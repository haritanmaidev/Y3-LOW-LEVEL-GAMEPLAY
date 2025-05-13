#include "EnemyEnforcer.h"
#include "EntityManager.h"

EnemyEnforcer::EnemyEnforcer(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef)
: EnemyCharacter(spawn, player, randomDir), PlayerRef(player), entityManager(EntityManagerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/EnemyEnforcer.png", std::nullopt))
	{
		std::cout << "EnemyEnforcer Texture Loaded" << std::endl;
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.05f, .05f));
		SetTag("EnemyEnforcer");
		speed = 1.5f;
		health = 1;
		MaxHealth = health;
		score = 150;
		SetActive(true);
	}
}

void EnemyEnforcer::Update()
{
	sf::Vector2f playerPosition = PlayerRef.GetPosition();
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f direction = playerPosition - position;
	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= mag;

	if (mag < detectionRadius && mag != 0.f)
	{
		//Move towards Player
		MoveCharacter(-direction);
	}
	else
	{
		MoveCharacter(direction);
	}

	fireTimer += 0.1f;
	if (fireTimer > fireRate)
	{
		//REFACTOR: USE HOMING MISSLE LATER, MISSE WORTH IS 25 PTS
		fireRate = entityManager.GetRandomNumber(5.5f, 6.5f);
		entityManager.SpawnProjectile(sprite.getPosition(), direction, 8.f);
		fireTimer = 0.f;
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
		TakeDamage(1, "Player");
	}
	else if (tag == "Projectile")
	{
		TakeDamage(1, "Projectile");
	}
}

void::EnemyEnforcer::TakeDamage(int damage, const std::string& damageBy)
{
	SoundManager::PlayEnemyHurtSound();
	Character::TakeDamage(damage, damageBy);
}

void EnemyEnforcer::Die(const std::string& killedBy)
{
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