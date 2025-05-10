#pragma once

class UIManager
{
public:
	static void InitBorder(int width, int height) 
	{
		border.setSize(sf::Vector2f(width * 0.875f, height * 0.875f));
		border.setOrigin(sf::Vector2f(border.getSize().x / 2.f, border.getSize().y / 2.f));
		border.setPosition(sf::Vector2f(width/2, height/2));
		border.setOutlineColor(sf::Color::Red);
		border.setOutlineThickness(4.f);
		border.setFillColor(sf::Color::Transparent);
	}

	static void InitScore(const std::string& fontPath, int width, int height)
	{
		if (font.openFromFile(fontPath))
		{
			scoreText.setOrigin(sf::Vector2f(scoreText.getCharacterSize()/2, scoreText.getCharacterSize()/2));
			scoreText.setPosition(sf::Vector2f(width/2, height/100));
			scoreText.setFont(font);
			scoreText.setCharacterSize(30);
			scoreText.setFillColor(sf::Color::White);
		}
	}

	static void Update() { scoreText.setString("Score: " + std::to_string(GetScore())); }
	static int GetScore() { return score; }
	static void AddScore(int points){ score += points; }
	static void SubtractScore(int points) { score -= points; }
	static void ResetScore() { score = 0; }
	static void RenderUI(sf::RenderWindow& window)
	{ 
		window.draw(scoreText);
		window.draw(border);
	}

private:
	inline static int score = 0;
	inline static sf::Font font;
	inline static sf::Text scoreText = sf::Text(font);
	inline static sf::RectangleShape border;
};
