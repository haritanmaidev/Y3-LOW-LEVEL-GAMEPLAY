#include "GameScene.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "EntityManager.h"
#include "WaveManager.h"

GameScene::GameScene(sf::RenderWindow& windowRef, InputHandler& inputRef, EntityManager& entityManRef, WaveManager& waveRef)
: window(windowRef), inputHandler(inputRef), entityManager(entityManRef), waveManager(waveRef)
{
	UIManager::ResetScore();
	UIManager::ResetWave();
	UIManager::SetLives(3);
	SoundManager::PlayBackgroundMusic();
}

void GameScene::HandleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window.close();
	}
}

void GameScene::Update()
{
	//if(entityManager)
	entityManager.GameObjectListCollisionCheck();
	entityManager.UpdateAllEntities(window, inputHandler);
	entityManager.RemoveEntityFromList();
	waveManager.Update();
	SoundManager::CleanUpSounds();
	UIManager::Update();
}

void GameScene::Render(sf::RenderWindow& window)
{
	entityManager.RenderAllGameObjects(window);
	UIManager::RenderUI(window);
}