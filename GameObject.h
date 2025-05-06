#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject
{
public:
	//Constructor
	GameObject();

	//Destructor
	virtual ~GameObject() = default;

	//Pure functions
	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void OnCollision() = 0;

	//NOTE:Make this Render virtual if I wanna do particle effects for certain classes!
	void Render(sf::RenderWindow &window) { window.draw(sprite); }
	
	//Setters and Getters
	void SetActive(bool status) { isActive = status; }
	void SetTag(const std::string& newTag) { tag = newTag; }
	void SetPosition(float x, float y) { sprite.setPosition(sf::Vector2f(x , y)); }
	void SetScale(float x, float y) { sprite.setScale(sf::Vector2f(x, y)); }
	void SetRotation(sf::Angle angle) { sprite.setRotation(sf::Angle(angle)); }
	void SetSpriteTexture(const sf::Texture& newTexture) { sprite.setTexture(newTexture); }
	void SetVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	bool IsActive() const { return isActive; }
	const std::string& GetTag() const { return tag; }
	sf::Vector2f GetPosition() { return sprite.getPosition(); }
	sf::Vector2f GetScale() const { return sprite.getScale(); }
	sf::Angle GetRotation() const { return sprite.getRotation(); }
	sf::Sprite& GetSprite() { return sprite; }
	const sf::Sprite& GetSpriteConst() const { return sprite; }
	sf::Vector2f GetVelocity() const { return velocity; }

	bool LoadGameObjectTextureFromFile(const std::string& filePath, const std::optional<sf::IntRect>& intrect)
	{
		if (intrect.has_value())
		{
			if (!texture->loadFromFile(filePath, false, intrect.value()))
			{
				std::cout << "Texture didn't load!" << std::endl;
				return false;
			}
		}
		else
		{
			if (!texture->loadFromFile(filePath, false))
			{
				std::cout << "Texture didn't load!" << std::endl;
				return false;
			}
		}

		//std::cout << "Texture loaded!" << std::endl;
		return true;
	}

protected:
	//Class Variables
	sf::Vector2f spawnPoint = sf::Vector2f(0.f, 0.f);
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	sf::Sprite sprite = sf::Sprite(*texture);
	//sf::IntRect drawbox = sf::IntRect({0, 0}, {0, 0});
	sf::IntRect hitbox = sf::IntRect({0, 0} , {0, 0});
	std::string tag;
	int id = 0;
	bool isActive = true;
};