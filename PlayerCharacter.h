#pragma once
#include "Character.h"
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
	void TakeDamage(int damage) override;
	void Die() override;

	//Class Functions
	void AddScore(int points) { this->score += points; }
	void SetScore(int newScore) { this->score = newScore; }

private:
	int score = 0;
	sf::Vector2f PlayerSpawnPoint = sf::Vector2f(0.f, 0.f);
};

