#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	//Constructor & Destructor
	Character(const sf::Vector2f& spawn);
	~Character() = default;

	//Override Functions
	void Update() override;
	void OnCollision(const std::string& tag) override;

	//Inline Functions
	void SetHealth(int newHealth) { this->health = newHealth; }
	void SetSpeed(float newSpeed) { this->speed = newSpeed; }
	int GetHealth() const { return health; }
	float GetSpeed() const { return speed; }
	int GetScore() const { return score; }

	//Class Functions
	virtual void TakeDamage(int damage);
	virtual void MoveCharacter(const sf::Vector2f& direction);
	virtual void SpriteFlash();
	virtual void Die();

protected:
	int health = 3;
	int score = 100;
	float speed = 10.f;
	bool isFlashing = false;
	sf::Vector2f spawnPoint = sf::Vector2f(0.f, 0.f);
};