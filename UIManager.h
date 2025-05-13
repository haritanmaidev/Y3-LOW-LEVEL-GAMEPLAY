#pragma once
class UIManager
{
public:
	static void Init(const std::string& fontPath)
	{
		if (font.openFromFile(fontPath))
		{
			healthBar.setSize(sf::Vector2f(200.f, 20.f));
			healthBar.setFillColor(sf::Color(255, 0, 0, 50));
			healthBar.setPosition(sf::Vector2f(15.f, 10.f));
			healthBar.setOutlineColor(sf::Color::White);
			healthBar.setOutlineThickness(2.f);

			healthBarFill.setSize(sf::Vector2f(200.f, 20.f));
			healthBarFill.setFillColor(sf::Color(0, 255, 30));
			healthBarFill.setPosition(sf::Vector2f(15.f, 10.f));

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
			waveText.setPosition(sf::Vector2f(415.f, 0.f));
			waveMessageText.setFont(font);
			waveMessageText.setCharacterSize(50);
			waveMessageText.setFillColor(sf::Color::White);
			waveMessageText.setPosition(sf::Vector2f(200.f, 200.f));
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
	}

	static void RenderUI(sf::RenderWindow& window)
	{
		window.draw(healthBar);
		window.draw(healthBarFill);
		window.draw(livesCountText);
		window.draw(scoreText);
		window.draw(waveText);
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
		score += points;
		if (score >= 9999) scoreText.setPosition(sf::Vector2f(775.f, 0.f));
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
};
