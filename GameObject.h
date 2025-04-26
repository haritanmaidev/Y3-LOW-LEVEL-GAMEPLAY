#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Transform
{
	sf::Vector2f position {0.f, 0.f};
	sf::Vector2f scale {1.f, 1.f};
	sf::Angle rotation = sf::Angle::Zero;
};

class GameObject
{
public:
	//Constructor
	GameObject(sf::Texture ConsTexture) : texture(ConsTexture), sprite(texture)
	{

		if (!texture.loadFromFile("assets/Cropped/BasicProjectile.png"))
		{
			std::cout << "Texture didn't load!" << std::endl;
		}
		else
		{
			sprite.setTexture(texture);
		}
	}

	sf::CircleShape newCircle;

	//Destructor
	virtual ~GameObject() = default;

	//Pure functions
	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void OnCollision() = 0;

	//NOTE:Make this Render virtual if I wanna do particle effects for certain classes!
	void Render(sf::RenderWindow& window) { window.draw(sprite); }
	
	//Setters and Getters
	void SetActive(bool status) { isActive = status; }
	void SetTag(const std::string& newTag) { tag = newTag; }
	void SetPosition(float x, float y) { transform.position = { x, y }; sprite.setPosition(transform.position); }
	void SetScale(float x, float y) { transform.scale = { x, y }; sprite.setScale(transform.scale); }
	void SetRotation(sf::Angle angle) { transform.rotation = angle; sprite.setRotation(transform.rotation); }
	void SetSpriteTexture(const sf::Texture& newTexture) { sprite.setTexture(newTexture); }
	bool GetActiveStatus() const { return isActive; }
	const std::string& GetTag() const { return tag; }
	sf::Vector2f GetPosition() const { return transform.position; }
	sf::Vector2f GetScale() const { return transform.scale; }
	sf::Angle GetRotation() const { return transform.rotation; }
	Transform& GetTransform() { return transform; }
	const Transform& GetTransform() const { return transform; }
	sf::Sprite& GetSprite() { return sprite; }

	void SyncTransformWithSprite()
	{
		transform.position = sprite.getPosition();
		transform.scale = sprite.getScale();
		transform.rotation = sprite.getRotation();
	}

	bool LoadGameObjectTexture(const std::string& filePath)
	{
		if (!texture.loadFromFile(filePath))
		{
			std::cout << "Projectile's Texture didn't load!" << std::endl;
			return false;
		}

		sprite.setTexture(texture);
		std::cout << "Texture set!" << std::endl;
		return true;
	}

protected:
	Transform transform;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect hitbox;
	std::string tag;
	int ID = 0;
	bool isActive = true;
};