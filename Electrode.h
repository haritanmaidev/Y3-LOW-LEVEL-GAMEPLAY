#pragma once
#include "Character.h"
class Electrode : public Character
{
public:
	//Constructor & Destructor
	Electrode(const sf::Vector2f& spawn);
	~Electrode() = default;

	//Override Functions
	void Update() override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& taggedBy) override;

private:

	
};

