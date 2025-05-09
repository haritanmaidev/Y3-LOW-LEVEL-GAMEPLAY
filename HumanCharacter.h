#pragma once
#include "Character.h"

class EntityManager;

class HumanCharacter : public Character
{
public:
	//Constructor & Destructor
	HumanCharacter(const sf::Vector2f& spawn, const EntityManager& EntityManagerRef);
	~HumanCharacter() = default;

	//Override Functions
	void Awake() override;
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision() override;
	void TakeDamage(int damage) override;	
	void Die() override;

	//Class Functions
	bool isRescued() const { return rescued; }

private:
	bool rescued = false;
	float randomMoveTimer = 0.f;
	const EntityManager& entityManager;
	sf::Vector2f randomDirection = sf::Vector2f(0.f, 0.f);
};

