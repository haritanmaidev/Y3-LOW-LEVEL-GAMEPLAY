#pragma once
class UIManager
{
public:
	static void InitText(const std::string& fontPath)
	{
		if (font.openFromFile(fontPath))
		{
			scoreText.setFont(font);
			scoreText.setCharacterSize(30);
			scoreText.setFillColor(sf::Color::White);
			scoreText.setPosition(sf::Vector2f(405.f, 0.f));

			waveText.setFont(font);
			waveText.setCharacterSize(30);
			waveText.setFillColor(sf::Color::White);
			waveText.setPosition(sf::Vector2f(10.f, 0.f));

			waveMessage.setFont(font);
			waveMessage.setCharacterSize(50);
			waveMessage.setFillColor(sf::Color::White);
			waveMessage.setPosition(sf::Vector2f(200.f, 200.f));
		}
	}

	static void Update() 
	{ 
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
		window.draw(scoreText);
		window.draw(waveText);
		if(isWaveMessageActive) { window.draw(waveMessage); }
	}	

	static void DisplayWaveMessage() 
	{
		waveMessage.setString("WAVE " + std::to_string(wave) + " IS STARTING!!!");
		waveMessageTimer = 0.f;
		isWaveMessageActive = true;
	}

	static int GetScore() { return score; }
	static void AddScore(int points){ score += points; }
	static void SubtractScore(int points) { score -= points; }
	static void ResetScore() { score = 0; }

	static int GetWave() { return wave; }
	static void IncrementWave() { wave++; }
	static void ResetWave() { wave = 0; }

	static float GetWaveDelayTime() { return waveMessageInterval; }

private:
	inline static int score = 0;
	inline static int wave = 0;

	inline static sf::Font font;
	inline static sf::Text scoreText = sf::Text(font);
	inline static sf::Text waveText = sf::Text(font);

	inline static sf::Text waveMessage = sf::Text(font);
	inline static bool isWaveMessageActive = false;
	inline static float waveMessageTimer = 0.f;
	inline static float waveMessageInterval = 5.f;
};
