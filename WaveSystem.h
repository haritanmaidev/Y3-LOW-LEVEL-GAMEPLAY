#pragma once
#include "EntityManager.h"
#include "UIManager.h"

class WaveSystem
{
public:
	// Constructor & Destructor
	WaveSystem(EntityManager& manager) : entityManager(manager){}
	~WaveSystem() = default;

	void Init() 
	{
		UIManager::IncrementWave();
		//currentWave = 1;
		enemiesToSpawn = 5;
		spawnInterval = 0.5f;
		spawnTimer = 0.f;
		waveInProgress = true;
	}

	void Update() 
	{
		if (!waveInProgress) return;

		spawnTimer += 0.1f;
		if (spawnTimer >= spawnInterval && enemiesSpawned < enemiesToSpawn) 
		{
			SpawnEnemy();
			spawnTimer = 0.f;
		}

		std::cout << "Enemies Existing: " << entityManager.AreEnemiesActive() << std::endl;
		if (enemiesSpawned >= enemiesToSpawn && entityManager.AreEnemiesActive() == 0)
		{
			StartNextWave();
		}
	}

private:
	EntityManager& entityManager;
	int enemiesToSpawn = 5;
	int enemiesSpawned = 0;
	float spawnInterval = 0.5f;
	float spawnTimer = 0.f;
	bool waveInProgress = true;

	void SpawnEnemy() 
	{
		std::cout << "Spawning enemy at wave: " << UIManager::GetWave() << std::endl;
		entityManager.SpawnEnemyCharacter(sf::Vector2f(entityManager.GetRandomNumber(250, 750), entityManager.GetRandomNumber(0, 200)));
		enemiesSpawned++;
	}

	void StartNextWave() 
	{
		std::cout << "Wave " << UIManager::GetWave() << " completed!" << std::endl;
		waveInProgress = false;
		UIManager::IncrementWave();
		enemiesToSpawn += 3;
		enemiesSpawned = 0;
		spawnTimer = 0.f;
		waveInProgress = true;
	}
};

