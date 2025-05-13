#include "EnemyBrain.h"
#include "EntityManager.h"

EnemyBrain::EnemyBrain(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef)
	: EnemyCharacter(spawn, player, randomDir), playerRef(player), entityManager(EntityManagerRef), humanRef(nullptr)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/EnemyBrain.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.05f, .05f));
		SetTag("EnemyBrain");
		score = 500;
		speed = 11.5f;
		health = 3;
		MaxHealth = health;
		humanRef = entityManager.GetActiveHumanForBrain();
	}
}

void EnemyBrain::Update()
{
	Character::Update();

	if (humanRef == nullptr || humanRef->isCorrupt)
	{
		humanRef = entityManager.GetActiveHumanForBrain();
	}
	else if (humanRef) 
	{
		sf::Vector2f humanPos = humanRef->GetPositionConst();
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f direction = humanPos - position;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;
		MoveCharacter(direction);
	}

	fireTimer += 0.1f;
	if (fireTimer > fireRate)
	{
		sf::Vector2f playerPos = playerRef.GetPositionConst();
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f direction = playerPos - position;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;
		fireRate = entityManager.GetRandomNumber(5.5f, 6.5f);
		//entityManager.SpawnProjectileBrain(sprite.getPosition(), direction, 4.f);
		fireTimer = 0.f;
	}
}

void EnemyBrain::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void EnemyBrain::OnCollision(const std::string& tag)
{
	if (tag == "Player")
	{
		TakeDamage(1, "Player");
	}
	else if (tag == "Projectile")
	{
		TakeDamage(1, "Projectile");
	}
	else if (tag == "Human") 
	{
		//SoundManager::PlayHumanCorruptSound();
		humanRef = nullptr;
	}
}

void::EnemyBrain::TakeDamage(int damage, const std::string& damageBy)
{
	SoundManager::PlayEnemyHurtSound();
	Character::TakeDamage(damage, damageBy);
}

void EnemyBrain::Die(const std::string& killedBy)
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