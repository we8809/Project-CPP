#include <iostream>
#include <cassert>
#include "IceCube.h"
#include "ObjectPool.h"
#include "Game.h"

using namespace lab9;

int main()
{
	Game game(1, 4);
	const std::vector<IceCube*>& activeGameObjects = game.GetActiveGameObjects();
	assert(activeGameObjects.size() == 0);

	game.Spawn();
	game.Spawn();
	game.Spawn();
	game.Spawn();
	game.Spawn();

	assert(activeGameObjects.size() == 5);
	assert(activeGameObjects[0]->IsActive());
	assert(activeGameObjects[1]->IsActive());
	assert(activeGameObjects[2]->IsActive());
	assert(activeGameObjects[3]->IsActive());
	assert(activeGameObjects[4]->IsActive());

	const IceCube* i5 = activeGameObjects[3];

	game.Update();

	const std::vector<IceCube*>& activeGameObjects2 = game.GetActiveGameObjects();
	assert(activeGameObjects2.size() == 4);
	assert(activeGameObjects[0] == activeGameObjects2[0]);
	assert(activeGameObjects[1] == activeGameObjects2[1]);
	assert(activeGameObjects[2] == activeGameObjects2[2]);
	assert(activeGameObjects[3] == activeGameObjects2[3]);

	auto& op2 = game.GetObjectPool();
	IceCube* i6 = op2.Get();

	assert(i6 == i5);

	op2.Return(i6);

	return 0;
}