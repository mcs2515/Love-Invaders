#ifndef UILABELS_H
#define UILABELS_H
#include "RE\ReEngAppClass.h"


class UILabels
{
public:
	UILabels();
	~UILabels();

	MeshManagerSingleton* m_pMeshMngr = nullptr;

	void DisplayTotalScore(int ts); //method to display total score
	
	void DisplayCurrentScore(int cs); //method to display current score
	
	void DisplayAmmoCount(int a); //method to display current bullet count

	void DisplayGoal(int g); //method to display current goal

	void DisplayLives(int l); //method to display current lives

	void DisplayCurrentTime(int t); //method diplays current time

	void DisplayMainMenu();
	void DisplayCredits();
	void GenericSingleLine(String string);
private:



};
#endif
