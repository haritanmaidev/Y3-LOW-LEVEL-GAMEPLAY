#pragma once
#include "Character.h"
class PlayerCharacter : public Character
{
public:
	//Constructor & Destructor
	PlayerCharacter();
	~PlayerCharacter() = default;

	//Override Functions
	void TakeDamage(int& damage) override;
	void Move(const sf::Vector2f& direction) override;
	void Die() override;

	//Class Functions
	void AddScore(int points) { this->score += points; }
	void SetScore(int newScore) { this->score = newScore; }

private:
	int score = 0;
};

