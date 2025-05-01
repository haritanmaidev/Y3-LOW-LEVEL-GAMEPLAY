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
	void SetPosition(float x, float y) { transform.position = { x, y }; sprite.setPosition(transform.position); }
	void SetScale(float x, float y) { transform.scale = { x, y }; sprite.setScale(transform.scale); }
	void SetRotation(sf::Angle angle) { transform.rotation = angle; sprite.setRotation(transform.rotation); }
	void SetSpriteTexture(const sf::Texture& newTexture) { sprite.setTexture(newTexture); }
	bool IsActive() const { return isActive; }
	const std::string& GetTag() const { return tag; }
	sf::Vector2f GetPosition() const { return transform.position; }
	sf::Vector2f GetScale() const { return transform.scale; }
	sf::Angle GetRotation() const { return transform.rotation; }
	Transform& GetTransform() { return transform; }
	const Transform& GetTransform() const { return transform; }
	sf::Sprite& GetSprite() { return sprite; }

	//Extra functions
	void SyncTransformWithSprite()
	{
		transform.position = sprite.getPosition();
		transform.scale = sprite.getScale();
		transform.rotation = sprite.getRotation();
	}

	bool LoadGameObjectTextureFromFile(const std::string& filePath, const sf::IntRect& intrect)
	{
		if (!texture.loadFromFile(filePath, false, intrect))
		{
			std::cout << "Texture didn't load!" << std::endl;
			return false;
		}
		else
		{
			sprite.setTexture(texture);	
			std::cout << "Texture loaded successfully!" << std::endl;
			return true;
		}

	}

protected:
	//ASK:Sprite variable was throwing annoying errors, set this up as a quick fix.
	sf::Sprite& MakeSprite()
	{
		sf::Texture texture;
		bool result = texture.loadFromFile("assets/walk.png");
		sf::Sprite playersprite(texture);
		return playersprite;
	}

	//Class Variables
	Transform transform;
	sf::Vector2f spawnPoint {0.f, 0.f};
	sf::Texture texture;
	sf::Sprite sprite = MakeSprite();
	sf::IntRect drawbox = sf::IntRect({0, 0}, {0, 0});
	sf::IntRect hitbox = sf::IntRect({0, 0} , {0, 0});
	std::string tag;
	int id = 0;
	bool isActive = true;
};