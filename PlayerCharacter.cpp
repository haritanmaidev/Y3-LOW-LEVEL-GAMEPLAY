#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const sf::Vector2f& spawn) : Character(spawn)
{
	sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if(LoadGameObjectTextureFromFile("assets/walk.png", drawbox))
	{
		sprite.setTextureRect(drawbox);
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(2.25f, 2.25f));
		SetTag("Player");
		playerHealth = 100;
		playerMaxHealth = playerHealth;
	}
}

void PlayerCharacter::Update()
{
	Character::Update();
}

void PlayerCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	Character::MoveCharacter(direction);
}

void PlayerCharacter::OnCollision(const std::string& tag)
{
	if (tag == "Enemy" || tag == "ProjectileEnforcer" || tag == "ProjectileSnake")
	{
		TakeDamage(5, "Enemy");
	}
	else if (tag == "EnemyHulk")
	{
		TakeDamage(10, "EnemyHulk");
	}
	else if (tag == "HumanCorrupted") 
	{
		TakeDamage(10, "HumanCorrupted");
	}
}

void PlayerCharacter::TakeDamage(int damage, const std::string& damageBy)
{
	isFlashing = true;
	sprite.setColor(sf::Color::Red);
	playerHealth -= damage;
	SoundManager::PlayPlayerHurtSound();
	UIManager::SetHealthValues(playerHealth, playerMaxHealth);
	if (playerHealth <= 0 || damage >= playerMaxHealth) Die(damageBy); //Instant kill if damage is very high
	//Character::TakeDamage(damage, damageBy);
}

void PlayerCharacter::Die(const std::string& killedBy)
{
	UIManager::DecrementLives();

	if (UIManager::GetLives() > 0)
	{
		//Respawn Logic
		playerHealth = playerMaxHealth;
		SetPosition(PlayerSpawnPoint.x , PlayerSpawnPoint.y);
		UIManager::SetHealthValues(playerHealth, playerMaxHealth);
		UIManager::SubtractScore(1000);
		std::cout << "Player Died!" << std::endl;
	}
	else 
	{
		//SoundManager::PlayPlayerDeathSound();
		SoundManager::PlayPlayerHurtSound();
		Character::Die(killedBy);
		std::cout << "Game Over!" << std::endl;
	}
}