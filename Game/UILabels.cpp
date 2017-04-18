#include "UILabels.h"
using namespace ReEng;


UILabels::UILabels()
{
}

// displays total score (including all rounds)
String UILabels::DisplayTotalScore(int ts) {
	return "Total Score: " + std::to_string(ts);
}


//displays players current score in current round
String UILabels::DisplayCurrentScore(int cs ) {
	return "Current Score: " + std::to_string(cs);
}

//displays how many enemies player needs to shoot in current round
String UILabels::DisplayGoal(int g) {
	return "Goal: " + std::to_string(g);
}

//displays how many bullets player has in current round
String UILabels::DisplayAmmoCount(int a) {
	return "Bullet Count: " + std::to_string(a);
}

//displays how many lives player has left
String UILabels::DisplayLives(int l) {
	return "Lives: " + std::to_string(l);
}

//displays how many lives player has left
String UILabels::DisplayCurrentTime(int t) {
	return "CurrentTime: " + std::to_string(t);
}


UILabels::~UILabels()
{
}
