#include "EnemyTank.h"
#include "EntityManager.h"

EnemyTank::EnemyTank(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef)
: EnemyCharacter(spawn, player, randomDir), playerRef(player), entityManager(EntityManagerRef)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/EnemyTank.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.3f, .3f));
		SetTag("EnemyTank");
		score = 1000;
		speed = 1.f;
		health = 10;
		MaxHealth = health;
	}
}

void EnemyTank::Update()
{
	Character::Update();

	sf::Vector2f playerPosition = playerRef.GetPositionConst();
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f direction = playerPosition - position;
	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= mag;

	if (mag > 800) MoveCharacter(direction);

	fireTimer += 0.1f;
	static float fireRate = 10.5f;
	if (fireTimer > fireRate)
	{
		entityManager.SpawnProjectileShell(sprite.getPosition(), direction, 10.f);
		fireTimer = 0.f;
	}
}

void EnemyTank::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void EnemyTank::OnCollision(const std::string& tag)
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

void::EnemyTank::TakeDamage(int damage, const std::string& damageBy)
{
	SoundManager::PlayEnemyHurtSound();
	Character::TakeDamage(damage, damageBy);
}

void EnemyTank::Die(const std::string& killedBy)
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