#include "EntityManager.h"

EntityManager::EntityManager()
{
	GameObjectList.reserve(200);
	Player = nullptr;
	Human = nullptr;
}