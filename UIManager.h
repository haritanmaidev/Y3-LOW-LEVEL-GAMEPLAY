#pragma once
#include <iostream>

class UIManager
{
public:
	static void Init(const std::string& fontPath)
	{
		if (font.openFromFile(fontPath))
		{
			healthBar.setSize(sf::Vector2f(200.f, 20.f));
			healthBar.setFillColor(sf::Color(255, 0, 0, 50));
			healthBar.setPosition(sf::Vector2f(15.f, 9.f));
			healthBar.setOutlineColor(sf::Color::White);
			healthBar.setOutlineThickness(2.f);

			healthBarFill.setSize(sf::Vector2f(200.f, 20.f));
			healthBarFill.setFillColor(sf::Color(0, 255, 30));
			healthBarFill.setPosition(sf::Vector2f(15.f, 9.f));

			livesCountText.setCharacterSize(30);
			livesCountText.setFillColor(sf::Color::White);
			livesCountText.setPosition(sf::Vector2f(220.f, 0.f));
			livesCountText.setString("x" + std::to_string(lives));

			scoreText.setFont(font);
			scoreText.setCharacterSize(30);
			scoreText.setFillColor(sf::Color::White);
			scoreText.setPosition(sf::Vector2f(790.f, 0.f));

			waveText.setFont(font);
			waveText.setCharacterSize(30);
			waveText.setFillColor(sf::Color::White);
			waveText.setPosition(sf::Vector2f(425.f, 0.f));
			waveMessageText.setFont(font);
			waveMessageText.setCharacterSize(50);
			waveMessageText.setFillColor(sf::Color::White);
			waveMessageText.setPosition(sf::Vector2f(200.f, 200.f));

			border.setSize(sf::Vector2f(996.f, 996.f));
			border.setPosition(sf::Vector2f(500.f, 500.f));
			border.setFillColor(sf::Color::Transparent);
			border.setOutlineColor(sf::Color::White);
			border.setOutlineThickness(2.f);
			border.setOrigin(sf::Vector2f(border.getSize().x / 2.f, border.getSize().y / 2.f));

			borderTop.setSize({ 999.f, 32.f });
			borderTop.setPosition({ 500.f, 19.f });
			borderTop.setFillColor(sf::Color::Transparent);
			borderTop.setOutlineColor(sf::Color::White);
			borderTop.setOutlineThickness(2.f);
			borderTop.setOrigin(sf::Vector2f(borderTop.getSize().x / 2.f, borderTop.getSize().y / 2.f));

		}
	}

	static void Update()
	{
		float healthPercent = (float)currentHealth / (float)maxHealth;
		healthBarFill.setSize(sf::Vector2f(200.f * healthPercent, 20.f));

		livesCountText.setString("x " + std::to_string(lives));
		scoreText.setString("Score: " + std::to_string(GetScore()));
		waveText.setString("Wave: " + std::to_string(GetWave()));
		if (isWaveMessageActive)
		{
			waveMessageTimer += 0.1f;
			if (waveMessageTimer > waveMessageInterval) { isWaveMessageActive = false; }
		}

		GetFlashColor();
		FlashText(livesCountText);
		FlashText(scoreText);
		FlashText(waveText);
		FlashText(waveMessageText);
		border.setOutlineColor(GetFlashColor());
		borderTop.setOutlineColor(GetFlashColor());
		healthBar.setOutlineColor(GetFlashColor());
	}

	static void RenderUI(sf::RenderWindow& window)
	{
		window.draw(healthBar);
		window.draw(healthBarFill);
		window.draw(livesCountText);
		window.draw(scoreText);
		window.draw(waveText);
		window.draw(border);
		window.draw(borderTop);
		if (isWaveMessageActive) { window.draw(waveMessageText); }
	}

	static void GetFont(sf::Font& fontRef) { fontRef = font; }

	//Health Stuff
	static int GetLives() { return lives; }
	static void DecrementLives() { lives--; }
	static void IncrementLives() { lives++; }
	static void SetLives(int livesCount) { lives = livesCount; }
	static void ResetHealth() { currentHealth = maxHealth; }
	static void SetHealthValues(int playerCurrentHealth, int playerMaxHealth)
	{
		currentHealth = playerCurrentHealth;
		maxHealth = playerMaxHealth;
	}

	//Score Stuff
	static int GetScore() { return score; }
	static void ResetScore() { score = 0; }
	static void SubtractScore(int points) { score -= points; }
	static void AddScore(int points)
	{
		static int extraLifeScore = 10000;
		const int extraLifeInterval = 10000;
		score += points;
		if (score >= 10000) scoreText.setPosition(sf::Vector2f(775.f, 0.f));

		if (score >= extraLifeScore)
		{
			IncrementLives();
			extraLifeScore += extraLifeInterval;
		}
	}

	//Wave Stuff
	static int GetWave() { return wave; }
	static float GetWaveDelayTime() { return waveMessageInterval; }
	static void ResetWave() { wave = 0; }
	static void IncrementWave() { wave++; }
	static void DisplayWaveMessage()
	{
		waveMessageText.setString("WAVE " + std::to_string(wave) + " IS STARTING!!!");
		waveMessageTimer = 0.f;
		isWaveMessageActive = true;
	}

	//Color Flashing Text & bORDER
	static sf::Color GetFlashColor()
	{
		static int red = 255, green = 0, blue = 0;
		static float flashTime = 0.5f;
		static float flashTimer = 0.f;
		flashTimer += 0.1f;
		if (flashTimer > flashTime) 
		{
			static int phase = 0;
			const int step = 1;

			switch (phase)
			{
			case 0: green += step; if (green >= 255) { green = 255; phase = 1; } break;
			case 1: red -= step; if (red <= 0) { red = 0; phase = 2; } break;
			case 2: blue += step; if (blue >= 255) { blue = 255; phase = 3; } break;
			case 3: green -= step; if (green <= 0) { green = 0; phase = 4; } break;
			case 4: red += step; if (red >= 255) { red = 255; phase = 5; } break;
			case 5: blue -= step; if (blue <= 0) { blue = 0; phase = 0; } break;
			}

			flashTimer = 0.f;
		}

		return sf::Color(red, green, blue);
	}

	static void FlashText(sf::Text& text) 
	{
		text.setFillColor(GetFlashColor());
	}
	
private:
	inline static int lives = 0;
	inline static int currentHealth = 100;
	inline static int maxHealth = 100;
	inline static int score = 0;
	inline static int wave = 0;
	inline static bool isWaveMessageActive = false;
	inline static float waveMessageTimer = 0.f;
	inline static float waveMessageInterval = 5.f;
	inline static sf::Font font;
	inline static sf::Text livesCountText = sf::Text(font);
	inline static sf::Text scoreText = sf::Text(font);
	inline static sf::Text waveText = sf::Text(font);
	inline static sf::Text waveMessageText = sf::Text(font);
	inline static sf::RectangleShape healthBar;
	inline static sf::RectangleShape healthBarFill;
	inline static sf::RectangleShape border;
	inline static sf::RectangleShape borderTop;
};
