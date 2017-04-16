#pragma once
//Jordan Mato 4/15/17
#include "NPC.h"
class Enemy :
	public NPC
{
public:
	void Draw();
	Enemy();
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd);
	~Enemy();

	static int n_enemyCount; //can be moved to AppClass later
};

