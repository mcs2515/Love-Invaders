#include "MovableObjects.h"

void MovableObjects::Move()
{
}

void MovableObjects::Draw()
{
}


MovableObjects::MovableObjects(vector3 ip, boolean ir, vector3 is, MeshManagerSingleton* iMeshManager, std::vector<vector3> vertexList, ObjectType it)
{
	meshManager = iMeshManager;
	position = ip;
	rotation = ir;
	size = is;
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);

	m_bColliding = false;
	m_v3CenterGlobal = vector3(0.0f);

	type = it;

	if (vertexList.size() < 1)
		return;

	//finding the min corner and max corner
	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;

	m_v3MaxSurrounding = m_v3Max;
	m_v3MinSurrounding = m_v3Min;

	m_v3SurroundingSize = m_v3MaxSurrounding - m_v3MinSurrounding;

	if (m_fRadius < m_v3SurroundingSize.x)
	{
		m_fRadius = m_v3SurroundingSize.x;
	}
	if (m_fRadius < m_v3SurroundingSize.y)
	{
		m_fRadius = m_v3SurroundingSize.y;
	}
	if (m_fRadius < m_v3SurroundingSize.z)
	{
		m_fRadius = m_v3SurroundingSize.z;
	}
}

MovableObjects::~MovableObjects()
{
}

//Collision stuff


void MovableObjects::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;


	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));

	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	std::vector<vector3> vectorList;

	//8 local points
	vectorList.push_back(vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z)); //min
	vectorList.push_back(vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z));
	vectorList.push_back(vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z));
	vectorList.push_back(vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z));

	vectorList.push_back(vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z));
	vectorList.push_back(vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z));
	vectorList.push_back(vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z));
	vectorList.push_back(vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z)); //max

																	//turn all 8 points to global
	for (int i = 0; i < 8; i++)
	{
		vectorList[i] = vector3(m_m4ToWorld * vector4(vectorList[i], 1.0f));
	}

	//set minLargest and maxLargest to the first point
	m_v3MaxSurrounding = vectorList[0];
	m_v3MinSurrounding = m_v3MaxSurrounding;

	for (int i = 1; i < 8; i++)
	{
		if (m_v3MinSurrounding.x > vectorList[i].x)
		{
			m_v3MinSurrounding.x = vectorList[i].x;
		}
		else if (m_v3MaxSurrounding.x < vectorList[i].x)
		{
			m_v3MaxSurrounding.x = vectorList[i].x;
		}

		if (m_v3MinSurrounding.y > vectorList[i].y)
		{
			m_v3MinSurrounding.y = vectorList[i].y;
		}
		else if (m_v3MaxSurrounding.y < vectorList[i].y)
		{
			m_v3MaxSurrounding.y = vectorList[i].y;
		}

		if (m_v3MinSurrounding.z > vectorList[i].z)
		{
			m_v3MinSurrounding.z = vectorList[i].z;
		}
		else if (m_v3MaxSurrounding.z < vectorList[i].z)
		{
			m_v3MaxSurrounding.z = vectorList[i].z;
		}
	}

	m_v3SurroundingSize = m_v3MaxSurrounding - m_v3MinSurrounding;
	if (m_fRadius < m_v3SurroundingSize.x)
	{
		m_fRadius = m_v3SurroundingSize.x;
	}
	if (m_fRadius < m_v3SurroundingSize.y)
	{
		m_fRadius = m_v3SurroundingSize.y;
	}
	if (m_fRadius < m_v3SurroundingSize.z)
	{
		m_fRadius = m_v3SurroundingSize.z;
	}
}

void MovableObjects::RenderSphere()
{
	vector3 v3Color = GetSphereColor();
	int value = 0; //NONE

	if (GetGeneralVisibility()) {
		value = 2; //WIRE
	}

	if (true == m_bColliding)
		v3Color = RERED;

	m_pMeshMngr->AddSphereToRenderList(
		glm::translate(m_v3CenterGlobal) *
		glm::scale(vector3(m_fRadius / 2) * 2.0f), v3Color, value);
}

void MovableObjects::RenderBox()
{
	vector3 v3Color = GetColor();
	int value = 0; //NONE

	if (GetGeneralVisibility()) {
		value = 2; //WIRE
	}

	if (true == m_bColliding)
		v3Color = RERED;

	if (value == 2) {
		if (!GetAABBVisibility())
		{
			value = 0;
		}

		// Personal cube
		//m_pMeshMngr->AddCubeToRenderList(
		//	m_m4ToWorld *
		//	glm::translate(m_v3CenterGlobal) *
		//	glm::scale(m_v3Size),
		//	v3Color, value);

		// All-encompassing cube
		m_pMeshMngr->AddCubeToRenderList(
			glm::translate(m_v3CenterGlobal) *
			glm::scale(m_v3SurroundingSize),
			REGREEN, value);
	}
}

bool MovableObjects::IsColliding(MovableObjects * a_other)
{
	//check for sphere collision first
	if (CheckSphereCollision(a_other)) {
		//then check for box collision
		return SeparatingAxisTest(a_other);
	}

	//else return false for collision
	return false;
}


bool MovableObjects::CheckBoxCollision(MovableObjects* a_other)
{
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	//else return true
	return true;
}

bool MovableObjects::CheckBoxCollision(BoundingObject * a_other)
{
	if (this->m_v3MaxG.x < a_other->GetMin().x)
		return false;
	if (this->m_v3MinG.x > a_other->GetMax().x)
		return false;

	if (this->m_v3MaxG.y < a_other->GetMin().y)
		return false;
	if (this->m_v3MinG.y > a_other->GetMax().y)
		return false;

	if (this->m_v3MaxG.z < a_other->GetMin().z)
		return false;
	if (this->m_v3MinG.z > a_other->GetMax().z)
		return false;

	//else return true
	return true;
}


bool MovableObjects::CheckSphereCollision(MovableObjects* a_other)
{
	float fDistance = glm::distance(m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	float fRadiiSum = m_fRadius + a_other->m_fRadius;
	//return t/f
	return fDistance < fRadiiSum;

	//else return true
	return true;
}

bool MovableObjects::SeparatingAxisTest(MovableObjects * a_other)
{
	float ra, rb;
	matrix3 R, AbsR;
	// t_e = This_e  -  contains half the lengths on the x, y, and z sides, respectively
	float t_e[3];
	t_e[0] = (m_v3Max.x - m_v3Min.x) / 2;
	t_e[1] = (m_v3Max.y - m_v3Min.y) / 2;
	t_e[2] = (m_v3Max.z - m_v3Min.z) / 2;

	// a_e = A_other_e  -  contains half the lengths on the x, y, and z sides, respectively
	float a_e[3];
	a_e[0] = (a_other->GetMax().x - a_other->GetMin().x) / 2;
	a_e[1] = (a_other->GetMax().y - a_other->GetMin().y) / 2;
	a_e[2] = (a_other->GetMax().z - a_other->GetMin().z) / 2;

	// t_u = This_u  -  contains 
	vector3 t_u[3];
	t_u[0] = vector3(GetModelMatrix()[0][0], GetModelMatrix()[0][1], GetModelMatrix()[0][2]);
	t_u[1] = vector3(GetModelMatrix()[1][0], GetModelMatrix()[1][1], GetModelMatrix()[1][2]);
	t_u[2] = vector3(GetModelMatrix()[2][0], GetModelMatrix()[2][1], GetModelMatrix()[2][2]);

	// a_u = A_other_u
	vector3 a_u[3];
	a_u[0] = vector3(a_other->GetModelMatrix()[0][0], a_other->GetModelMatrix()[0][1], a_other->GetModelMatrix()[0][2]);
	a_u[1] = vector3(a_other->GetModelMatrix()[1][0], a_other->GetModelMatrix()[1][1], a_other->GetModelMatrix()[1][2]);
	a_u[2] = vector3(a_other->GetModelMatrix()[2][0], a_other->GetModelMatrix()[2][1], a_other->GetModelMatrix()[2][2]);

	// Compute rotation matrix expressing b in a’s coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R[i][j] = glm::dot(a_u[i], t_u[j]);
	// Compute translation vector t
	vector3 t = GetCenterGlobal() - a_other->GetCenterGlobal();
	// Bring translation into a’s coordinate frame
	t = vector3(glm::dot(t, a_u[0]), glm::dot(t, a_u[1]), glm::dot(t, a_u[2]));
	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = glm::abs(R[i][j]) + FLT_EPSILON;
	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = a_e[i];
		rb = t_e[0] * AbsR[i][0] + t_e[1] * AbsR[i][1] + t_e[2] * AbsR[i][2];
		if (glm::abs(t[i]) > ra + rb) return 0;
	}
	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = a_e[0] * AbsR[0][i] + a_e[1] * AbsR[1][i] + a_e[2] * AbsR[2][i];
		rb = t_e[i];
		if (glm::abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
	}
	// Test axis L = A0 x B0
	ra = a_e[1] * AbsR[2][0] + a_e[2] * AbsR[1][0];
	rb = t_e[1] * AbsR[0][2] + t_e[2] * AbsR[0][1];
	if (glm::abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;
	// Test axis L = A0 x B1
	ra = a_e[1] * AbsR[2][1] + a_e[2] * AbsR[1][1];
	rb = t_e[0] * AbsR[0][2] + t_e[2] * AbsR[0][0];
	if (glm::abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;
	// Test axis L = A0 x B2
	ra = a_e[1] * AbsR[2][2] + a_e[2] * AbsR[1][2];
	rb = t_e[0] * AbsR[0][1] + t_e[1] * AbsR[0][0];
	if (glm::abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;
	// Test axis L = A1 x B0
	ra = a_e[0] * AbsR[2][0] + a_e[2] * AbsR[0][0];
	rb = t_e[1] * AbsR[1][2] + t_e[2] * AbsR[1][1];

	if (glm::abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;
	// Test axis L = A1 x B1
	ra = a_e[0] * AbsR[2][1] + a_e[2] * AbsR[0][1];
	rb = t_e[0] * AbsR[1][2] + t_e[2] * AbsR[1][0];

	if (glm::abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;
	// Test axis L = A1 x B2
	ra = a_e[0] * AbsR[2][2] + a_e[2] * AbsR[0][2];
	rb = t_e[0] * AbsR[1][1] + t_e[1] * AbsR[1][0];
	if (glm::abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;
	// Test axis L = A2 x B0
	ra = a_e[0] * AbsR[1][0] + a_e[1] * AbsR[0][0];
	rb = t_e[1] * AbsR[2][2] + t_e[2] * AbsR[2][1];
	if (glm::abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;
	// Test axis L = A2 x B1
	ra = a_e[0] * AbsR[1][1] + a_e[1] * AbsR[0][1];
	rb = t_e[0] * AbsR[2][2] + t_e[2] * AbsR[2][0];
	if (glm::abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;
	// Test axis L = A2 x B2
	ra = a_e[0] * AbsR[1][2] + a_e[1] * AbsR[0][2];
	rb = t_e[0] * AbsR[2][1] + t_e[1] * AbsR[2][0];
	if (glm::abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;

	// Since no separating axis is found, the OBBs must be intersecting
	return 1;
	return false;
}

//properties
void MovableObjects::SetColor(vector3 color) { objColor = color; }
vector3 MovableObjects::GetColor(void) { return objColor; }
void MovableObjects::SetSphereColor(vector3 color) { ObjSphereColor = color; }
vector3 MovableObjects::GetSphereColor(void) { return ObjSphereColor; }
void MovableObjects::SetGeneralVisibility(bool value) { m_bVisible = value; }
bool MovableObjects::GetGeneralVisibility(void) { return m_bVisible; }
void MovableObjects::SetAABBVisibility(bool value) { m_bAVisible = value; }
bool MovableObjects::GetAABBVisibility(void) { return m_bAVisible; }
void MovableObjects::SetColliding(bool input) { m_bColliding = input; }
bool MovableObjects::GetColliding(void) { return m_bColliding; }
void MovableObjects::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MovableObjects::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
vector3 MovableObjects::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MovableObjects::GetCenterGlobal(void) { return m_v3CenterGlobal; }
void MovableObjects::SetRadius(float input) { m_fRadius = input; }
float MovableObjects::GetRadius(void) { return m_fRadius; }
matrix4 MovableObjects::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 MovableObjects::GetMin() { return m_v3Min; }
vector3 MovableObjects::GetMax() { return m_v3Max; }
ObjectType MovableObjects::GetType() { return type; }