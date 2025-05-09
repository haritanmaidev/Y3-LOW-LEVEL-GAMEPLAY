#include "Character.h"

Character::Character(const sf::Vector2f& spawn) : GameObject(), spawnPoint(spawn)
{
	//sf::IntRect drawbox = sf::IntRect({ 0 , 0 }, { 0 , 0 });
	LoadGameObjectTextureFromFile("assets/errorcharacter.png", std::nullopt);
	//hitbox.findIntersection()
	sprite.setScale(sf::Vector2f(.25f, .25f));
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
	sprite.setPosition(spawnPoint);
}

void Character::Update()
{
	if (isFlashing)
	{
		SpriteFlash();
	}
}

void Character::OnCollision()
{
}

void Character::MoveCharacter(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void Character::TakeDamage(int damage)
{
	if (health <= 0) return;
	isFlashing = true;
	sprite.setColor(sf::Color::Red);
	health -= damage;
	if (health <= 0) Die();
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
}