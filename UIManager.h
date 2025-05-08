#pragma once

class UIManager
{
public:
	static void Init(const std::string& fontPath)
	{
		if (font.openFromFile(fontPath))
		{
			scoreText.setFont(font);
			scoreText.setCharacterSize(40);
			scoreText.setFillColor(sf::Color::White);
			scoreText.setPosition(sf::Vector2f(15.f, 0.f));
		}
	}

	static void Update()
	{
		scoreText.setString("Score: " + std::to_string(GetScore()));
	}

	static int GetScore()
	{
		return score;
	}

	static void AddScore(int points)
	{
		score += points;
	}

	static void SubtractScore(int points)
	{
		score -= points;
	}

	static void RenderUI(sf::RenderWindow& window)
	{
		window.draw(scoreText);
	}

private:
	inline static int score = 0;
	inline static sf::Font font;
	inline static sf::Text scoreText = sf::Text(font);
};
