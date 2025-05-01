#pragma once
#include "Character.h"
class PlayerCharacter : public Character
{
public:
	//Constructor
	PlayerCharacter();

	void TakeDamage(int& damage) override;
	void Move(const sf::Vector2f& direction) override;
	void Die() override;

private:
	int score = 0;

};

