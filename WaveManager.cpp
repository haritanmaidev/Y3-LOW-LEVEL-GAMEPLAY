#include "WaveManager.h"
#include "EntityManager.h"
#include "UIManager.h"

WaveManager::WaveManager(EntityManager& entityManagerRef, const float& waveDelayRef) : entityManager(entityManagerRef), waveDelay(waveDelayRef)
{
	//StartNextWave();
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

	//Check if all enemies are spawned and also if none are active before starting new wave
	if (gruntsSpawned >= gruntsToSpawn && hulksSpawned >= hulksToSpawn && entityManager.AreEnemiesDead())
	{
		StartNextWave();
	}
}

void WaveManager::StartNextWave()
{
	std::cout << "StartNextWave called" << std::endl;
	entityManager.ResetSceneForWaves();
	UIManager::IncrementWave();
	UIManager::DisplayWaveMessage();

	int wave = UIManager::GetWave();

	isWaitingToSpawn = true;
	isWaveActive = false;
	waveDelayTimer = 0.f;
	spawnIntervalTimer = 0.f;

	humansSpawned = 0;
	gruntsSpawned = 0;
	hulksSpawned = 0;
	brainsSpawned = 0;
	enforcersSpawned = 0;
	tanksSpawned = 0;

	//Didn't want like 10000 if statements here so I made them shorter and readable :)
	humansToSpawn = (wave <= 3) ? wave + 2 : 3;
	gruntsToSpawn = 3 + wave * 2;
	hulksToSpawn = (wave >= 2) ? (wave - 2) / 2 : 1;
	brainsToSpawn = (wave % 2 == 0) ? wave - 1 : 0;
	enforcersToSpawn = (wave % 3 == 0) ? (wave/2) : 0;
	tanksToSpawn = (wave % 4 == 0) ? (wave / 4) : 0;

	if(humansToSpawn > 10) humansToSpawn = 10;
	if(gruntsToSpawn > 30) gruntsToSpawn = 20;
	if(hulksToSpawn > 6) hulksToSpawn = 6;
	if(brainsToSpawn > 3) brainsToSpawn = 3;
	if(enforcersToSpawn > 5) enforcersToSpawn = 5;
	if (tanksToSpawn > 3) tanksToSpawn = 2;
}

void WaveManager::SpawnEntity()
{
	if(humansSpawned < humansToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(450, 650), entityManager.GetRandomNumber(200, 300));
		entityManager.SpawnHumanCharacter(pos);
		humansSpawned++;
	}

	if(gruntsSpawned < gruntsToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(250, 750), entityManager.GetRandomNumber(10, 400));
		entityManager.SpawnEnemyCharacter(pos);
		gruntsSpawned++;
	}

	if(hulksSpawned < hulksToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(350, 650), entityManager.GetRandomNumber(10, 200));
		entityManager.SpawnEnemyHulk(pos);
		hulksSpawned++;
	}

	if (brainsSpawned < brainsToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(50, 950), entityManager.GetRandomNumber(500, 750));
		entityManager.SpawnEnemyBrain(pos);
		brainsSpawned++;
	}

	if(enforcersSpawned < enforcersToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(50, 950), entityManager.GetRandomNumber(10, 100));
		entityManager.SpawnEnemyEnforcer(pos);
		enforcersSpawned++;
	}

	if (tanksSpawned < tanksToSpawn)
	{
		sf::Vector2f pos = sf::Vector2f(entityManager.GetRandomNumber(50, 950), entityManager.GetRandomNumber(10, 100));
		entityManager.SpawnEnemyTank(pos);
		tanksSpawned++;
	}
}