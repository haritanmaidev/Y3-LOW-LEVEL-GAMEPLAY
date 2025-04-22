#pragma once
#include <SFML/Graphics.hpp>

struct Transform
{
	sf::Vector2f position {0.f, 0.f};
	sf::Vector2f scale {1.f, 1.f};
	float rotation = 0.f;

	Transform() : position(0, 0), scale(1, 1), rotation(0) {}
	Transform(sf::Vector2f pos, sf::Vector2f scl, float rot) : position(pos), scale(scl), rotation(rot) {}
};

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Awake() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	Transform& GetTransform() { return transform; }
	const Transform& GetTransform() const { return transform; }

protected:
	Transform transform;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string tag;
	int ID = 0;
	bool isActive = true;
};
