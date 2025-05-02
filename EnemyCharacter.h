#pragma once
#include "Character.h"
class EnemyCharacter :public Character
{
public:
	//Constructor & Destructor
	EnemyCharacter();
	~EnemyCharacter() = default;

	//Override Functions
	void Awake() override;
	void OnCollision() override;
	void Update() override;
	void TakeDamage(int& damage) override;
	void Move(const sf::Vector2f& direction) override;
	void Die() override;

};

