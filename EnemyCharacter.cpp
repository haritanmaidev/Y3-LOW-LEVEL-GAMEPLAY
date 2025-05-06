#include "EnemyCharacter.h"
#include "PlayerCharacter.h"

EnemyCharacter::EnemyCharacter(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir) : Character(spawn), playerref(player), travelDir(randomDir)
{
	//sf::IntRect drawbox = sf::IntRect({ 8, 8 }, { 24, 38 });
	if (LoadGameObjectTextureFromFile("assets/Cropped/BasicEnemy.png", std::nullopt))
	{
		//sprite.setTextureRect(drawbox);
		sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetTag("Enemy");
		SetActive(true);
		speed = 2.f;
	}
}

void EnemyCharacter::Awake()
{

}

void EnemyCharacter::Update()
{
	//std::cout << "Enemy Update is called!" << std::endl;
	if (IsActive()) 
	{
		sf::Vector2f playerPosition = playerref.GetSpriteConst().getPosition();
		sf::Vector2f enemyPosition = sprite.getPosition();
		sf::Vector2f direction = playerPosition - enemyPosition;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if(mag < detectionRadius && mag != 0.f)
		{
			direction /= mag;
			MoveCharacter(direction);
		}
		else
		{
			//Move towards random Direction
			MoveCharacter(velocity);
		}
	}
}

void EnemyCharacter::OnCollision()
{
	std::cout << "Enemy got Collided!" << std::endl;
	sf::Vector2f currentPosition = sprite.getPosition();

	// Determine the direction to move based on the intersection
	//if (intersection.size.x > intersection.size.y)
	//{
	//	// Vertical overlap: move up or down
	//	if (currentPosition.y < intersection.size.y)
	//	{
	//		sprite.move(sf::Vector2f(0.f, -intersection.size.y)); // Move up
	//	}
	//	else
	//	{
	//		sprite.move(sf::Vector2f(0.f, intersection.size.y)); // Move down
	//	}
	//}
	//else
	//{
	//	// Horizontal overlap: move left or right
	//	if (currentPosition.x < intersection.size.x)
	//	{
	//		sprite.move(sf::Vector2f(-intersection.size.x, 0.f)); // Move left
	//	}
	//	else
	//	{
	//		sprite.move(sf::Vector2f(intersection.size.x, 0.f)); // Move right
	//	}
	//}
}

void EnemyCharacter::TakeDamage(int& damage)
{
	Character::TakeDamage(damage);
}

void EnemyCharacter::MoveCharacter(const sf::Vector2f& direction)
{
	sprite.move(direction * speed);
}

void EnemyCharacter::Die()
{
	SetActive(false);
	std::cout << "Player is dead!" << std::endl;
}
