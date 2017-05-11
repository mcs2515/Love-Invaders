#include "UILabels.h"
using namespace ReEng;


UILabels::UILabels()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

// displays total score (including all rounds)
void UILabels::DisplayTotalScore(int ts) {
	m_pMeshMngr -> PrintLine("Total Score: " + std::to_string(ts));
}


//displays players current score in current round
void UILabels::DisplayCurrentScore(int cs ) {
	m_pMeshMngr->PrintLine("Current Score: " + std::to_string(cs));
}

//displays how many enemies player needs to shoot in current round
void UILabels::DisplayGoal(int g) {
	m_pMeshMngr->PrintLine("Goal: " + std::to_string(g));
}

//displays how many bullets player has in current round
void UILabels::DisplayAmmoCount(int a) {
	m_pMeshMngr->PrintLine("Bullet Count: " + std::to_string(a));
}

//displays how many lives player has left
void UILabels::DisplayLives(int l) {
	m_pMeshMngr->PrintLine("Lives: " + std::to_string(l));
}

//displays how many lives player has left
void UILabels::DisplayCurrentTime(int t) {
	m_pMeshMngr->PrintLine("CurrentTime: " + std::to_string(t));
}

void UILabels::DisplayMainMenu()
{
	m_pMeshMngr->PrintLine("Love Invaders");
	m_pMeshMngr->PrintLine("Developed By: JUM");
}

void UILabels::DisplayCredits()
{
	m_pMeshMngr->PrintLine("Developers:");
	m_pMeshMngr->PrintLine("Samantha Levey, Jordan Mato");
	m_pMeshMngr->PrintLine("Megan Smith, James Spinelli");
}

void UILabels::GenericSingleLine(String string)
{
	m_pMeshMngr->PrintLine(string);
}


UILabels::~UILabels()
{
}
