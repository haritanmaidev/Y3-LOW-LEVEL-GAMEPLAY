#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	Character();
	~Character() = default;

	int GetHealth() const { return health; }
	void SetHealth(int newHealth) { this->health = newHealth; }
	void TakeDamage(int damage);

	virtual void Move(const sf::Vector2f& direction);
	virtual void Die();

	void Awake() override
	{
		LoadGameObjectTexture("assets/walk.png");
		sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(1.25f, 1.25f));
		//sprite.setPosition(0, 0);
		SetActive(true);
	}
	
	void OnCollision() override
	{
		SetActive(false);
	}

private:
	int health = 100;
	float speed = 10.f;
};

