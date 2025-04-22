#pragma once
#include <SFML/Graphics.hpp>

struct Transform
{
	sf::Vector2f position {0.f, 0.f};
	sf::Vector2f scale {1.f, 1.f};
	float rotation = 0.f;

	//Transform() : position(0, 0), scale(1, 1), rotation(0) {}
	//Transform(sf::Vector2f pos, sf::Vector2f scl, float rot) : position(pos), scale(scl), rotation(rot) {}
};

class GameObject
{
public:
	//ASK: Why is this a pure virtual function? & What is this for?
	virtual ~GameObject() = default;

	//ASK: Why is there 0?
	virtual void Awake() = 0;
	virtual void Update(float dt) = 0;

	//ASK: Do this need to be virtual?
	virtual void Render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	virtual void OnCollision() = 0;
	
	//ASK: What else must be done in the destructor?
	virtual void Destroy() 
	{
		isActive = false;
	}

	//ASK: What are these?
	Transform& GetTransform() { return transform; }
	const Transform& GetTransform() const { return transform; }

	//Unsure functions:
	//void SetPosition(float x, float y) { transform.position = { x, y }; }
	//void SetScale(float x, float y) { transform.scale = { x, y }; }
	//void SetRotation()
	//{
	//	 sprite.setRotation(transform.rotation);
	//}

protected:
	Transform transform;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect hitbox;
	std::string tag;
	int ID = 0;
	bool isActive = true;
};
