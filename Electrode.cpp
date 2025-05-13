#include "Electrode.h"
#include "UIManager.h"

Electrode::Electrode(const sf::Vector2f& spawn) : Character(spawn)
{
	if (LoadGameObjectTextureFromFile("assets/Cropped/Electrode.png", std::nullopt))
	{
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Electrode");
		score = 1000;
		speed = 0.f;
		health = 3;
		MaxHealth = health;
	}
}

void Electrode::Update()
{
	Character::Update();
}

void Electrode::OnCollision(const std::string& tag)
{
	if (tag == "Projectile")
	{
		TakeDamage(1, "Projectile");
	}
}

void Electrode::TakeDamage(int damage, const std::string& damageBy)
{
	Character::TakeDamage(damage, damageBy);
}

void Electrode::Die(const std::string& killedBy)
{
	UIManager::AddScore(score);
	Character::Die(killedBy);
}