#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	//Constructor & Destructor
	Character();

	~Character() = default;

	//Override Functions
	void OnCollision() override;

	//Inline Functions
	void SetHealth(int newHealth) { this->health = newHealth; }
	void SetSpeed(float newSpeed) { this->speed = newSpeed; }
	int GetHealth() const { return health; }
	float GetSpeed() const { return speed; }

	//Class Functions
	virtual void TakeDamage(int& damage);
	virtual void Move(const sf::Vector2f& direction);
	virtual void Die();

protected:
	int health = 100;
	float speed = 10.f;
	//sf::Vector2f PlayerSpawnPoint = sf::Vector2f(0.f, 0.f);
};