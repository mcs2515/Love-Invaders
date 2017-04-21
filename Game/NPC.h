#ifndef NPC_H
#define NPC_H
//Jordan Mato 4/15/17

#include "MovableObjects.h"
class NPC :
	public MovableObjects
{
public:
	virtual void Draw();
	virtual void Move(float fTimer);
	NPC(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> vertexList);
	~NPC();
protected:
	vector3 v3_Start;
	vector3 v3_End;
};
#endif

