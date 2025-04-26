#pragma once
#include <SFML/Graphics.hpp>

struct Transform
{
	sf::Vector2f position {0.f, 0.f};
	sf::Vector2f scale {1.f, 1.f};
	sf::Angle rotation = sf::Angle::Zero;
};

class GameObject
{
public:
	//Destructor
	virtual ~GameObject() = default;

	//Pure functions
	virtual void Awake() = 0;
	virtual void Update() = 0;
	virtual void OnCollision() = 0;

	//NOTE:Make this Render virtual if I wanna do particle effects for certain classes!
	void Render(sf::RenderWindow& window) { window.draw(sprite);}
	
	//Setters and Getters
	void SetActive(bool status) { isActive = status; }
	void SetTag(const std::string& newTag) { tag = newTag; }
	void SetPosition(float x, float y) { transform.position = { x, y }; sprite.setPosition(transform.position); }
	void SetScale(float x, float y) { transform.scale = { x, y }; sprite.setScale(transform.scale); }
	void SetRotation(sf::Angle angle) { transform.rotation = angle; sprite.setRotation(transform.rotation); }
	bool IsActive() const { return isActive; }
	const std::string& GetTag() const { return tag; }
	sf::Vector2f GetPosition() const { return transform.position; }
	sf::Vector2f GetScale() const { return transform.scale; }
	sf::Angle GetRotation() const { return transform.rotation; }
	Transform& GetTransform() { return transform; }
	const Transform& GetTransform() const { return transform; }

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
			return false;
		}
		sprite.setTexture(texture);
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
