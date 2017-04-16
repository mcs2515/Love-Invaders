#pragma once
//Jordan Mato 4/15/17
#include "NPC.h"
class Enemy :
	public NPC
{
public:
	void Draw();
	void Move(float fTImer);
	Enemy();
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd);
	~Enemy();

	static int n_EnemyCount; //can be moved to AppClass later

private:
};

