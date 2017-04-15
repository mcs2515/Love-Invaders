#pragma once
//Jordan Mato 4/15/17
#include "NPC.h"
class Enemy :
	public NPC
{
public:
	Enemy();
	Enemy(vector3 initialPosition, vector3 initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd);
	~Enemy();

	static int n_enemyCount; //can be moved to AppClass later
};

