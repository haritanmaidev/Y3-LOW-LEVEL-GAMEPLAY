#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "UIManager.h"

EnemyCharacter::EnemyCharacter(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir) : Character(spawn), playerref(player), travelDir(randomDir)
{
	//sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if (LoadGameObjectTextureFromFile("assets/Cropped/BasicEnemy.png", std::nullopt))
	{
		//sprite.setTextureRect(drawbox);
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Enemy");
		SetActive(true);
		SoundManager::PlayEnemySpawnSound();
		speed = 2.f;
	}
}

void EnemyCharacter::Awake()
{

}

void EnemyCharacter::Update()
{
	Character::Update();

	if (IsActive()) 
	{
		sf::Vector2f playerPosition = playerref.GetSpriteConst().getPosition();
		sf::Vector2f enemyPosition = sprite.getPosition();
		sf::Vector2f direction = playerPosition - enemyPosition;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if(mag < detectionRadius && mag != 0.f)
		{
			//Move towards Player
			direction /= mag;
			MoveCharacter(direction);
		}
		else
		{
			//Move towards random Direction
			MoveCharacter(velocity);
		}
	}
}

void EnemyCharacter::OnCollision()
{
	SoundManager::PlayEnemyHurtSound();
	TakeDamage(1);
}

void EnemyCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void EnemyCharacter::TakeDamage(int damage)
{
	Character::TakeDamage(damage);
}

void EnemyCharacter::Die()
{
	SoundManager::PlayEnemyDeathSound();
	UIManager::AddScore(score);
	SetPosition(-2000, 2000);
	SetActive(false);
}
