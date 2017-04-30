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
	NPC(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> vertexList, float startPercent);
	~NPC();

	vector3 GetStart();
	void SetStart(vector3 start);
	vector3 GetEnd();
	void SetEnd(vector3 end);

	//get time for lerping for each bullet
	float GetTime();

	//add delta time to each bullets timer
	void TimeTick(float deltaTime);
protected:
	vector3 v3_Start;
	vector3 v3_End;
	float timer; //local timer
};
#endif

