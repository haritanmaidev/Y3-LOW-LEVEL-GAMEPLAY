#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	void AddScene(const std::string& name, std::unique_ptr<Scene> scene)
	{
		scenes[name] = std::move(scene);
	}

	void SwitchTo(const std::string& name) 
	{
		if (scenes.find(name) != scenes.end())
		{
			currentScene = scenes[name].get();
			currentScene->Init();
			std::cout << "Switched to scene: " << name << std::endl;
		}
		else
		{
			std::cerr << "Scene not found: " << name << std::endl;
		}
	}

	void HandleInput(sf::RenderWindow& window)
	{
		if (currentScene)
		{
			currentScene->HandleInput(window);
		}
	}

	void Update()
	{
		if(!currentScene) return;

		currentScene->Update();

		if (currentScene->IsFinished())
		{
			std::string next = currentScene->GetNextScene();
			SwitchTo(next);
		}
	}

	void Render(sf::RenderWindow& window)
	{
		if (currentScene)
		{
			currentScene->Render(window);
		}
	}

private:
	std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
	Scene* currentScene = nullptr;
};

