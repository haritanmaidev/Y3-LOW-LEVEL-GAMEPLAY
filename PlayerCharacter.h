#pragma once
#include "Character.h"
#include "UIManager.h"

class PlayerCharacter : public Character
{
public:
	//Constructor & Destructor
	PlayerCharacter(const sf::Vector2f& spawn);
	~PlayerCharacter() = default;

	//Override Functions
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& damageBy) override;

	//Class Functions
	int GetLives() const { return lives; }

private:
	int lives = 3;
	int playerHealth = 100;
	int playerMaxHealth = 100;
	sf::Vector2f PlayerSpawnPoint = sf::Vector2f(500.f, 800.f);
};