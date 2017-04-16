#pragma once
//Jordan Mato 4/15/17
#include "NPC.h"
class Enemy :
	public NPC
{
public:
<<<<<<< HEAD
	void Draw(MeshManagerSingleton* meshManager);
=======
	void Draw();
	void Move(float fTImer);
>>>>>>> 55df603c1262d03c0ef3ec9423b5613e265b4a6e
	Enemy();
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd);
	~Enemy();

	static int n_EnemyCount; //can be moved to AppClass later

private:
};

