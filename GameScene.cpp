#include "GameScene.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "EntityManager.h"
#include "WaveManager.h"

GameScene::GameScene(sf::RenderWindow& windowRef, InputHandler& inputRef, EntityManager& entityManRef, WaveManager& waveRef)
: window(windowRef), inputHandler(inputRef), entityManager(entityManRef), waveManager(waveRef) {}

void GameScene::Init()
{
	UIManager::SetLives(3);
	UIManager::ResetScore();
	UIManager::ResetWave();
	UIManager::ResetHealth();
	entityManager.SpawnPlayerCharacter(sf::Vector2f(700.f, 950.f));
	waveManager.StartNextWave();	
	isFinished = false;
}

void GameScene::HandleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		waveManager.StartNextWave();
	}
}

void GameScene::Update()
{
	entityManager.UpdateAllEntities(window, inputHandler);
	entityManager.GameObjectListCollisionCheck();
	entityManager.RemoveEntityFromList();
	waveManager.Update();
	SoundManager::CleanUpSounds();
	UIManager::Update();

	if (!entityManager.GetPlayer().IsActive())
	{
		entityManager.ClearAll();
		isFinished = true;
		nextScene = "GameOver";
	}
}

void GameScene::Render(sf::RenderWindow& window)
{
	entityManager.RenderAllGameObjects(window);
	UIManager::RenderUI(window);
}