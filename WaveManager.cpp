#include "WaveManager.h"
#include "EntityManager.h"
#include "UIManager.h"

WaveManager::WaveManager(EntityManager& entityManagerRef) : entityManager(entityManagerRef)
{
	StartNextWave();
}

void WaveManager::Update()
{
	//Waiting cuz of UI displaying wave message
	if (isWaitingToSpawn) 
	{
		waveDelayTimer += 0.1f;
		if (waveDelay < waveDelayTimer)
		{
			isWaitingToSpawn = false;
			isWaveActive = true;
		}
	}

	//Stop if wave can't be active yet
	if (!isWaveActive) return;

	spawnIntervalTimer += 0.1f;
	if (spawnInterval < spawnIntervalTimer)
	{
		spawnIntervalTimer = 0.f;
		SpawnEntity();
	}

	//Check if all enemies are spawned and if none are active to start new wave
	if (gruntsSpawned >= gruntsToSpawn && hulksSpawned >= hulksToSpawn)
	{
		if (!entityManager.AreEnemiesActive()) 
		{
			StartNextWave();
		}
	}
}

void WaveManager::StartNextWave()
{
	std::cout << "StartNextWave called" << std::endl;
	UIManager::IncrementWave();
	int wave = UIManager::GetWave();

	isWaveActive = false;
	isWaitingToSpawn = true;
	waveDelayTimer = 0.f;
	spawnIntervalTimer = 0.f;

	gruntsSpawned = 0;
	hulksSpawned = 0;
	gruntsToSpawn = 5 + wave * 2;
	hulksToSpawn += (wave >= 3) ? (wave - 2) / 2 : 0;

	UIManager::DisplayWaveMessage(wave);
}

//REASON: Easily exapandle
void WaveManager::SpawnEntity()
{
	if (gruntsSpawned < gruntsToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(250, 750), entityManager.GetRandomNumber(0, 200));
		entityManager.SpawnEnemyCharacter(pos);
		gruntsSpawned++;
	}
	else if (hulksSpawned < hulksToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(250, 750), entityManager.GetRandomNumber(0, 200));
		entityManager.SpawnEnemyHulk(pos);
		hulksSpawned++;
	}
}