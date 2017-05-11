#pragma once
#include "RE\ReEng.h"

class BoundingObject
{
public:
	//has functions and varibles to create sphere and or box collision
	~BoundingObject();

	BoundingObject();

	BoundingObject(std::vector<vector3> vertexList); //Constructor, needs a vertex list

	void SetCenterLocal(vector3 input); //Sets Center of the sphere in local space
	vector3 GetCenterLocal(void); //Gets center of the sphere in local space

	void SetCenterGlobal(vector3 input); //Sets Center of the sphere in global space
	vector3 GetCenterGlobal(void); //Gets center of the sphere in global space

	void SetColliding(bool input); //Sets Colliding
	bool GetColliding(void); //Gets Colliding

	void SetModelMatrix(matrix4 a_m4ToWorld); //Sets the transform from the local to world matrix
	matrix4 GetModelMatrix(void); //Gets model to world matrix of the sphere

	float GetRadius(void); //Sets the radius of the sphere
	void SetRadius(float input); //Gets radius of the sphere

	void RenderSphere();
	void RenderBox(); //Renders the box based on the center in global space

	bool IsColliding(BoundingObject* a_other); //Will check the collision with another object
	bool CheckBoxCollision(BoundingObject* a_other);
	bool CheckSphereCollision(BoundingObject* a_other);

	bool SeparatingAxisTest(BoundingObject* a_other);

	void SetGeneralVisibility(bool value); //Sets Visibilty
	bool GetGeneralVisibility(void);

	void SetAABBVisibility(bool value); //Sets Visibilty
	bool GetAABBVisibility(void);

	void SetColor(vector3 color);
	vector3 GetColor(void);

	void SetSphereColor(vector3 color);
	vector3 GetSphereColor(void);

	vector3 GetMin();
	vector3 GetMax();

private:
	bool m_bVisible = true; //turn off/on bounding obj 
	bool m_AABBVisible = true; //turn off/on bounding obj 
	bool m_bColliding = false;
	vector3 m_v3CenterLocal = vector3(0.0f); //center  in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center  in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the obj
	float m_fRadius = 0.0f; //radius of the sphere

	vector3 objColor;
	vector3 ObjSphereColor;

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;

	vector3 m_v3MaxSurrounding;
	vector3 m_v3MinSurrounding;
	vector3 m_v3SurroundingSize;
};

