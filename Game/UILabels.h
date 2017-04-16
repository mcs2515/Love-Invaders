#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>


class UILabels
{
public:
	UILabels();
	~UILabels();

	//method to display total score
	String DisplayTotalScore(int ts);

	//method to display current score
	String DisplayCurrentScore(int cs);


	//method to display current bullet count
	String DisplayAmmoCount(int a);


	//method to display current goal
	String DisplayGoal(int g);


private:



};

