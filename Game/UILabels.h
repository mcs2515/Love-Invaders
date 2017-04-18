#ifndef UILABELS_H
#define UILABELS_H
#include "RE\ReEngAppClass.h"


class UILabels
{
public:
	UILabels();
	~UILabels();

	
	String DisplayTotalScore(int ts); //method to display total score
	
	String DisplayCurrentScore(int cs); //method to display current score
	
	String DisplayAmmoCount(int a); //method to display current bullet count

	String DisplayGoal(int g); //method to display current goal

	String DisplayLives(int l); //method to display current lives

	String DisplayCurrentTime(int t); //method siplays current time


private:



};
#endif
