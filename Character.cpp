#include "Character.h"

Character::Character(const sf::Vector2f& spawn) : GameObject(), spawnPoint(spawn)
{
	LoadGameObjectTextureFromFile("assets/errorcharacter.png", std::nullopt);
	sprite.setScale(sf::Vector2f(.25f, .25f));
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
	sprite.setPosition(spawnPoint);
	MaxHealth = health;
}

void Character::Update()
{
	if (isFlashing)
	{
		SpriteFlash();
	}
}

void Character::MoveCharacter(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void Character::OnCollision(const std::string& tag)
{
}

void Character::TakeDamage(int damage)
{
	//if (health < 0) return; //Safety measure since I ran into getting like 20 collisions in half a second.
	isFlashing = true;
	sprite.setColor(sf::Color::Red);
	health -= damage;
	if (health <= 0 || damage >= MaxHealth) Die(); //Instant kill if damage is very high
}

void Character::SpriteFlash()
{
	static float flashTime = 0.3f;
	static float flashTimer = 0.f;
	flashTimer += 0.1f;
	if (flashTime < flashTimer)
	{
		std::cout << "Flashing!" << std::endl;
		sprite.setColor(sf::Color::White);
		flashTimer = 0.f;
		isFlashing = false;
	}
}

void Character::Die()
{
	SetActive(false);
	std::cout << "Character is dead!" << std::endl;
}