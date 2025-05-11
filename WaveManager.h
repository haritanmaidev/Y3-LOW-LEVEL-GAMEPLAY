#pragma once
class UIManager;
class EntityManager;

class WaveManager

{
public:
	WaveManager(EntityManager& entityManagerRef);
	~WaveManager() = default;

	void Update();
	void StartNextWave();
	void SpawnEntity();

private:
	EntityManager& entityManager;

	float waveDelay = 2.0f;
	float waveDelayTimer = 0.f;
	bool isWaveActive = false;
	bool isWaitingToSpawn = false;

	int gruntsSpawned = 0;
	int gruntsToSpawn = 0;
	int hulksSpawned = 0;
	int hulksToSpawn = 0;

	float spawnInterval = 0.5f;
	float spawnIntervalTimer = 0.f;
};

