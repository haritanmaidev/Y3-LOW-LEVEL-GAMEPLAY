#pragma once
#include "EntityManager.h"
#include "UIManager.h"
class EntityManager;
class UIManager;

class WaveManager
{
public:
	// Constructor & Destructor
	WaveManager(EntityManager& manager) : entityManager(manager)
	{
	}
	~WaveManager() = default;

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

		if (enemiesSpawned >= enemiesToSpawn && entityManager.GetLivingEnemyCount() == 0)
		{
			waveInProgress = false;
			UIManager::IncrementWave();
			//currentWave++;
			enemiesToSpawn += 5;
			spawnInterval *= 0.9f;
			waveInProgress = true;
		}
	}

	//int GetWave() const { return currentWave; }

private:
	EntityManager& entityManager;
	//int currentWave = 1;
	int enemiesToSpawn = 5;
	int enemiesSpawned = 0;
	float spawnInterval = 0.5f;
	float spawnTimer = 0.f;
	bool waveInProgress = true;

	void SpawnEnemy() 
	{
		std::cout << "Spawning enemy at wave: " << UIManager::GetWave() << std::endl;
		entityManager.SpawnEnemyCharacter(entityManager.GetRandomVector(200,200));
		enemiesSpawned++;
	}

	void StartNextWave() 
	{
		//currentWave++;
		UIManager::IncrementWave();
		enemiesToSpawn += 3;
		enemiesSpawned = 0;
		spawnTimer = 0.f;
		waveInProgress = true;
	}
};

